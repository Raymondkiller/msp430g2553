/*
 * Main.c
 *
 *  Created on: 05-03-2016
 *      Author: Mr.TUAN
 */

#include <msp430g2553.h>
#include "config.h"
#include "effect.h"

//This variable is used in P1's ISR
volatile char i = 0;

//P1's ISR
#pragma vector = PORT1_VECTOR
__interrupt void p1_int(void)
{
	delay(100);
	//Checking whether button1 or button2 or button1 + button2
	switch (P1IFG & 0X09)
	{
	//If button1
	case BIT0:
		{
			i = 1;
			break;
		}
	//If button2
	case BIT3:
		{
			i = 2;
			break;
		}
	case (BIT0 + BIT3):
		{
			i = 3;
			break;
		}
	}
	P1IFG &= 0XF6;
}

void main (void)
{
	//Stop watchdog timer
	WDTCTL = WDTPW + WDTHOLD;
	//Configure GPIO
	io_conf();
	//Global Interrupt Enable
	_BIS_SR(GIE);
	while (1)
	{
		switch (i)
		{
		case 1:
			{
				mode1();
				break;
			}
		case 2:
			{
				mode2();
				break;
			}
		case 3:
			{
				mode3();
				break;
			}
		default:
			{
				break;
			}
		}
	}
}
