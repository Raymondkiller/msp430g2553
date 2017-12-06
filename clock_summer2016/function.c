/*
 * function.c
 *
 *  Created on: Jul 30, 2016
 *      Author: K.V.D.T
 */

#include <msp430.h>
#include "function.h"

void pinwrite_1(unsigned int bit, unsigned char code) {
	if (code)				//neu code khac 0 thi gan P1OUT=1
	{
		P1OUT |= bit;
	}		//nguoc lai thi gan bang 0
	else {
		P1OUT &= ~bit;
	}
}
void pulse_1(void)		//ham tao xung dong bo
{
	P1OUT |= SCK_1;

	P1OUT &= ~SCK_1;
}
void pulse_2(void) {
	P1OUT |= SCK_2;

	P1OUT &= ~SCK_2;
}
void shiftout_1(unsigned char ma1, unsigned char ma2) {
	char i;
	for (i = 0; i < 8; i++) {
		pinwrite_1( DATA_1, ma1 & (0x80 >> i)); //dich tung bit trong ma_1 vao 595
		pulse_1();								// MSP truoc

		pinwrite_1( DATA_2, ma2 & (0x80 >> i)); //dich tung bit trong ma_2 vao 595
		pulse_2();
	}
	//__delay_cycles(200);
	P1OUT |= LATCH_1; //keo xung xuat du lieu len 1 de xuat du lieu ra led
	//__delay_cycles(200);
	P1OUT &= ~LATCH_1;
	//__delay_cycles(2000);
	P1OUT |= LATCH_2; //keo xung xuat du lieu len 1 de xuat du lieu ra led
	//__delay_cycles(200);
	P1OUT &= ~LATCH_2;
}
void config(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	BCSCTL1 = CALBC1_8MHZ; 		// CAI DAT TAN SO 16MHZ
	DCOCTL = CALDCO_8MHZ;

	P2DIR &= ~(but_up + but_down + but_setup + but_onl);				//set ngo vao
	P2REN |= but_up + but_down + but_setup + but_onl; 				//CHO PHEP TRO TREO
	P2OUT |= but_up + but_down + but_setup + but_onl; 				//TRO TREO LEN NGUON
	P2IE |= but_up + but_down + but_setup + but_onl;				//cho phep ngat
	P2IES |= but_up + but_down + but_setup + but_onl;				//ngat canh xuong
	P2IFG &= ~(but_up + but_down + but_setup + but_onl);        		//xoa co ngat
	__bis_SR_register(GIE);		//cho phep ngat toan cuc
	P1DIR |= DATA_1 + LATCH_1 + SCK_1 + DATA_2 + LATCH_2 + SCK_2; //SET NGO RA
	P1OUT &= ~(DATA_1 + LATCH_1 + SCK_1 + DATA_2 + LATCH_2 + SCK_2);

	TA0CTL = TASSEL_2 + MC_2 + TAIE;
}

