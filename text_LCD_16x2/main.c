#include "msp430g2553.h"
#include "stdio.h"
#include "LCD_16x2.h"

void LCDdisplay (void);
void main(void)
{

    WDTCTL= WDTPW|WDTHOLD;
        BCSCTL1= CALBC1_1MHZ;   //clock DCO= 1Mhz
        DCOCTL= CALDCO_1MHZ;    // mac dinh clock cap cho CPU (MCLK) chon =DCO
//        TA0CCR0= 10000;         //10ms
//        TA0CTL |= TASSEL_2 + MC_1 +TAIE; //CLOCK timer(SMCLK)=DCO(default), dem len den TA0CCR0, ENABLE ngat TA
//       _BIS_SR(GIE);     //cho phep ngat

       while(1)
       {

//}
//
//#pragma vector= TIMER0_A0_VECTOR
//__interrupt void Test_temperature(void)
//{   LCDdisplay();
//    TACCTL0 &= ~ BIT0;  //xoa co ngat
//}

//void LCDdisplay (void)
       int nhietdo=28;
        LCD_Init();
        LCD_Clear();
        LCD_Home();
        if (nhietdo >30 )
            LCD_PrintString(" HOT");
        else if (nhietdo <25)
            LCD_PrintString(" COLD");
        else
            LCD_PrintString(" NORMAL");
//}
}
}
