#include <msp430.h>
#include "library/clock.h"
#include "library/LCD16x2.h"
#include "library/LM35_ADC.h"
#include "library/sim800l.h"
#include "library/UART_library.h"

volatile float temp;

void main()
{
	WDTCTL = WDTPW | WDTHOLD;	//Stop Watchdog
	config_clock_MHz(1);
	config_switch_interup();
	UART_Init();
	config_ADC10(VCC);
	config_LCD();
	LCD_Clear();
	LCD_Home();
	LCD_PrintString("temp:  ");
	Sim800l_Init("19200","1");
	config_LED();
	while(1)
	{
		LCD_Home();
		LCD_PrintString("temp:  ");
		temp = 330*ADC10_read_temp(11)/1024;
		LCD_PrintFloat(temp,5,2);
		if(temp>40)
		{
			LCD_Goto(2, 0);
			LCD_PrintString("hot...->call... ");
			Sim800l_Call("0965619712");
			LED_OUT |= LED;
			__delay_cycles(1000000);
		}
		else
		{
			LCD_Goto(2, 0);
			LCD_PrintString("have a nice day!");
			LED_OUT &=~ LED;
		}
		__delay_cycles(1000000);
	}
}

#pragma vector = PORT_VECTOR_SWITCH
__interrupt void interrup(void) {

	LCD_Goto(2, 0);
	LCD_PrintString("sms...          ");

	Sim800l_Sms("0965619712","temp: ",temp);
	PIFG_SWITCH &= ~ SWITCH;
}



