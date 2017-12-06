/*
 * effect.c
 *
 *  Created on: 05-03-2016
 *      Author: Mr.TUAN
 */

#include <msp430g2553.h>
#include "effect.h"
#include "config.h"

void mode1 (void)
{
	P2OUT = 0XFF;
	delay(100);
	char i;
	for (i = 0; i < 8; i++)
	{
		P2OUT = 0X7F >> i;
		delay(100);
	}
}

void mode2 (void)
{
	unsigned char M[9] = {0XFF, 0X7F, 0X7E, 0X3E, 0X3C, 0X1C, 0X18, 0X08, 0};
	char i;
	for (i = 0; i < 9; i++)
	{
		P2OUT = M[i];
		delay(200);
	}
}

void mode3 (void)
{
	P2OUT ^= 0XFF;
	delay(100);
}
