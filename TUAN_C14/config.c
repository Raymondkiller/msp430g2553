/*
 * config.c
 *
 *  Created on: 05-03-2016
 *      Author: Mr.TUAN
 */

#include <msp430g2553.h>
#include "config.h"

void io_conf (void)
{
	//P1.0 and P1.3 are two buttons, pull up resistor
	P1SEL = P1SEL2 = 0;
	P1DIR = 0;
	P1REN = BIT0 + BIT3;
	P1OUT = BIT0 + BIT3;

	//P1.0 and P1.3's interrupt, high-to-low transition
	P1IE  = BIT0 + BIT3;
	P1IES = BIT0 + BIT3;
	P1IFG &= 0XF6;

	//P2 is output mode, turn off 8 LEDs
	P2SEL = P2SEL2 = 0;
	P2DIR = 0XFF;
	P2OUT = 0XFF;
}

void delay(unsigned int ms)
{
	unsigned int i;
	for (i = 0; i < ms; i++)
	{
		_delay_cycles(1000);
	}
}
