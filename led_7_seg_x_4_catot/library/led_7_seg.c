/*
 * led_7_seg.c
 *
 *  Created on: 26-09-2017
 *      Author: KILLER
 */

/*
 * function.c
 *
 *  Created on: Jul 30, 2016
 *      Author: K.V.D.T
 */

#include <msp430.h>
#include "led_7_seg.h"


void pinwrite(unsigned int bit, unsigned char code)
{
	if (code)				//neu code khac 0 thi gan P1OUT=1
	{
		PORT_LED |= bit;
	}		//nguoc lai thi gan bang 0
	else
	{
		PORT_LED &= ~bit;
	}
}

void pulse(void)		//ham tao xung dong bo
{
	PORT_LED |= CLK_LED;

	PORT_LED &= ~CLK_LED;
}

void shiftout(unsigned char number_shift)
{
	char number_led_shift;
	for (number_led_shift = 0; number_led_shift < 8; number_led_shift++)
	{
		pinwrite( DATA_LED, number_shift & (0x80 >> number_led_shift)); //dich tung bit trong ma_1 vao 595
		pulse();								// MSP truoc
	}
//	__delay_cycles(200);
	PORT_LED |= LATCH_LED; //keo xung xuat du lieu len 1 de xuat du lieu ra led
//	__delay_cycles(200);
	PORT_LED &= ~LATCH_LED;
}

void out_led7seg (unsigned char hour, unsigned char minute)
{
	char time_out[4];
	char number_led_out;
	time_out[1] = minute/10;
	time_out[0] = minute - time_out[1]*10;
	time_out[3] = hour/10;
	time_out[2] = hour - time_out[3]*10;

	for(number_led_out = 0; number_led_out < 4; number_led_out++)
	{
		PORT_LED &=~ (0x08 << number_led_out);
		shiftout(led_number[time_out[number_led_out]]);
		__delay_cycles(4000);
		PORT_LED |= LED_HOUR + LED_MINU;
		shiftout(0x00);
		__delay_cycles(5);

	}
}

void config_LED7SEG(void)
{
	//CONFIG SWITCH
	PSEL_SWITCH &=~ SWITCH;
	PSEL2_SWITCH &=~ SWITCH;
	PDIR_SWITCH &=~ SWITCH;				//set ngo vao
	PREN_SWITCH |= SWITCH; 				//CHO PHEP TRO TREO
	POUT_SWITCH |= SWITCH; 				//TRO TREO LEN NGUON
	PIE_SWITCH |= SWITCH;					//cho phep ngat
	PIES_SWITCH |= SWITCH;				//ngat canh xuong
	PIFG_SWITCH &=~ SWITCH;        		//xoa co ngat
//	__bis_SR_register(GIE);		//cho phep ngat toan cuc

	//CONFIG LED 7 SEG
	PSEL_LED &= ~(DATA_LED + CLK_LED + LATCH_LED + LED_HOUR + LED_MINU);
	PSEL2_LED &= ~(DATA_LED + CLK_LED + LATCH_LED + LED_HOUR + LED_MINU);
	PORT_LED_DIR |= (DATA_LED + CLK_LED + LATCH_LED + LED_HOUR + LED_MINU);
	PORT_LED &= ~(DATA_LED + CLK_LED + LATCH_LED);
	PORT_LED |= LED_HOUR + LED_MINU;

}




