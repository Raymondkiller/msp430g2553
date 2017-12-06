//******************************************************************************
//  MSP430G2553 - Capacitive Touch, Pin Oscillator Method, 4-buttons
//
//  Description: Basic 4-button input using the built-in pin oscillation feature
//  on GPIO input structure. PinOsc signal feed into TA0CLK. Difference in measurements indicate button touch.
//  LEDs flash if input is touched.
//
//               MSP430G2xx3
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.2|<--Capacitive Touch Input 1
//            |                 |
//  LED 2  <--|P1.6         P1.3|<--Capacitive Touch Input 2
//            |                 |
//  LED 1  <--|P1.0         P1.4|<--Capacitive Touch Input 3
//            |                 |
//            |             P1.5|<--Capacitive Touch Input 4
//
//   Built with CCS version: 5.10
//******************************************************************************
#include <msp430g2553.h>

#include "uart.h"

int count_default[5], count_edge[5], k;
char touch[4], touch_rem[4], touch_count[4], j, i, key, speed = 1, mode = 0, proximity = 0, slider = 0;
const char sensivity = 30;	//Threshold

void Init(void)
{
	P1DIR |= (BIT6 + BIT3 + BIT4 + BIT5 + BIT7);
	P1SEL &= ~(BIT6 + BIT3 + BIT4 + BIT5 + BIT7);	// Pin-Osc: PxSEL.x = 0; PxSEL2.x = 1;
	P1OUT &= ~(BIT6 + BIT3 + BIT4 + BIT5 +BIT7);

	P2DIR = 0xff;
	P2OUT &= ~BIT6;
	P2SEL &= ~BIT6;							// Pin-Osc: PxSEL.x = 0; PxSEL2.x = 1;
	//Config timer A
	TA0CTL = TASSEL_3+MC_2;                 // TACLK, cont mode
	TA0CCTL1 = CM_3+CCIS_3+CAP;             // Pos&Neg,GND,Cap
}

void Get_info(void)
{
	P2SEL2 &= ~BIT6;	//P2.6 -> Output
	P2OUT &= ~BIT6;		//P2.6 -> Ground

	for (j = 0; j < 5; j++)
	{
		P1SEL2 &= ~(BIT6 + BIT3 + BIT4 + BIT5 + BIT7);
		P1SEL2 |= 0x08 << j;		// Pin-Osc: PxSEL.x = 0; PxSEL2.x = 1;
		TA0CTL |= TACLR;			// Clear Timer_A TAR
		_delay_cycles(300);			// Delay to count
		TA0CCTL1 ^= CCIS0;			// Create SW capture of CCR1
		count_edge[j] = TACCR1;		// Save result
	}
	// Set P2.6 : Pin-Osc (Proximity)
	// Set P1.2 -> P1.5 are output, Turn off Pin-Osc
	P1SEL2 &= ~(BIT6 + BIT3 + BIT4 + BIT5 + BIT7);
	P1DIR |= BIT3 + BIT4 + BIT5 + BIT6 + BIT7;
	P1OUT &= ~(BIT6 + BIT3 + BIT4 + BIT5 + BIT7);	// Set P1.2 -> P1.5 = 0;

	P2SEL2 |= BIT6;
	TA0CTL |= TACLR;                        // Clear Timer_A TAR
	_delay_cycles(10000);
	TA0CCTL1 ^= CCIS0;                      // Create SW capture of CCR1
	count_edge[4] = TACCR1;                 // Save result

}

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;				//Stop Watchdog Timer
	Init();									//
	UART_Init();
	UART_Write_String("tuan");

//	touch_count[0]=1;

	for (i = 0; i < 10; i++)
	{
		Get_info();
		for (j = 0; j < 5; j++)
			count_default[j] = (count_default[j] + count_edge[j]) /2;
	}

	while (1)
	{
		Get_info();

		for (i = 0; i < 5; i++)
		{
			touch_rem[i] = touch[i];

			if ((count_edge[i] + sensivity) < count_default[i])		//
			{
				if (touch_count[i] > 0)
					touch_count[i]++;
				touch[i] = 1;
			}
			else
			{
				touch[i] = 0;
				touch_count[i] = 1;
			}

			if (touch_count[0] > 100)
			{
				touch_count[0] = 0;
//				proximity = ++proximity % 2;
//				P1OUT ^= BIT0;
			}

			if ((touch[i] != touch_rem[i]) && (touch[i] == 1))
			{
//				if (touch_rem[(i-1) % 4] == 1)
//					slider =1;
//				if (touch_rem[(i+1) % 4] == 1)
//					slider = 2;
				switch (i)
				{
				case 0:
					UART_Write_String("a");
					break;
				case 1:
					UART_Write_String("s");
//					speed++;
//					if (speed > 10)
//						speed = 10;
					break;
				case 2:
					UART_Write_String("d");
//					mode = ++mode % 3;
//					if (mode == 2)
//					{
//						P1OUT &= ~0x41;
//						P1OUT |= BIT0;
//					}
					break;
				case 3:
					UART_Write_String("w");
//					speed--;
//					if (speed < 1)
//						speed = 1;
					break;
				case 4:
					UART_Write_String("e");
					break;
				}
			}
		}
//
//		if (slider == 1)
//		{
////			P1OUT &= ~0x41;
////			for (i = 0; i < 29; i++)
////			{
////				P1OUT ^= BIT0;
//				_delay_cycles(100000);
////			}
//		}
//		else if (slider == 2)
//		{
////			P1OUT &= ~0x41;
////			for (i = 0; i < 29; i++)
////			{
////				P1OUT ^= BIT6;
//				_delay_cycles(100000);
////			}
//		}
//		switch (proximity)
//		{
//		case 0:
//		{
//			switch (mode)
//			{
//			case 0:
//				P1OUT &= ~BIT6;
//				P1OUT |= BIT0;
//				break;
//			case 1:
//				P1OUT &= ~BIT0;
//				P1OUT |= BIT6;
//				break;
//			case 2:
//				k = ++k % (3 * speed);
//				if (k == 0)
//					P1OUT ^= 0x41;
//				break;
//			}
//			_delay_cycles(2000);
//		}
//			break;
//		case 1:
//			if (count_edge[4] > count_default[4])
//				count_default[4] = (count_default[4] + count_edge[4])/2;
//			for (i = 0; i < 150; i++)
//			{
//				if (i < count_default[4] - count_edge[4] - 10)
////					P1OUT |= BIT0 + BIT6;
////				else
////					P1OUT &= ~(BIT0 +  BIT6);
//				__delay_cycles(15);
//			}
//			break;
//		}
//		slider = 0;
	}
}
/****************************************************************
 * END OF main.c
 ****************************************************************/

