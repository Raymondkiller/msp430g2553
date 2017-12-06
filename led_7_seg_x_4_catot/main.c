#include <msp430.h> 
#include "library/led_7_seg.h"
#include "library/clock.h"
#include "library/LM35_ADC.h"
#include "library/LCD16x2.h"

/*
 * main.c
 */
void LCD_display_temp(float temp_in);

int main(void) {
	config_clock_MHz(1);	//CHON CLK = 1MHZ
	config_timerA0();
//	config_timerA1();
    config_LED7SEG();
    config_ADC10(VCC);
    config_LCD();
    config_buzzer();
    LCD_Clear();
    LCD_Home();
    LCD_PrintString("nhiet do: ");
	__bis_SR_register(GIE);		//cho phep ngat toan cuc
	while(1)
	{

//		LCD_display_temp(temp);
		out_led7seg(clk_hour,clk_minu);
//		temp = ADC10_read_temp(0)*330/1024;
//		LCD_display_temp(temp);
//		__delay_cycles(1000);
	}
}

void LCD_display_temp(float temp_in)
{
//    LCD_Clear();
//    LCD_Home();
//    LCD_PrintString("nhiet do: ");
    LCD_Goto(1,10);
    LCD_PrintFloat(temp,5,2);
    LCD_Goto(2,0);
    if (temp > 50 )
    {
        LCD_PrintString("HOT...danger...!!!");
    	POUT_BUZZER |= buzzer;
    }
    else if (temp < 20)
    {
        LCD_PrintString("COLD...!!!");
    	POUT_BUZZER |= buzzer;
    }
    else
    {
        LCD_PrintString("HAVE A NICE DAY!");
    	POUT_BUZZER &=~ buzzer;
    }
}

#pragma vector = PORT_VECTOR_SWITCH
__interrupt void interrup(void) {

	clk_minu++;

	PIFG_SWITCH &= ~ SWITCH;
}


#pragma vector=TIMER0_A1_VECTOR
__interrupt void TAIV_Interrupt(void)
{
	switch (TA0IV)
	{
	case 10:
	{
//		LCD_display_temp(temp);
		if(dem_clk < 19)
			dem_clk++;
		else
		{
			dem_clk=0;
			if(clk_sec<60)
			{
				clk_sec++;
				if(clk_minu>60)
				{
					clk_minu=0;
					clk_hour++;
				}
				if(clk_hour>12)
					clk_hour=1;
				temp = ADC10_read_temp(0)*330/1024;
				LCD_display_temp(temp);
			}
			else
			{
				clk_sec=0;
				if(clk_minu<60)
					clk_minu++;
				else
				{
					clk_minu=0;
					clk_hour++;
					if(clk_hour>12)
						clk_hour=1;

				}
			}
		}
		break;
	}
	}
}



