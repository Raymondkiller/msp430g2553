#include <msp430.h>
#include "stdbool.h"
#include "function.h"

/*
 *     clock_summer2016
 *
 *  Created on: Jul 14, 2016
 *      Author: K.V.D.T
 *
 *      boss: anh Lam
 */

//#define Velocity 10
//#define but_up BIT5
//#define but_down BIT4
//#define but_setup BIT3
//#define but_onl BIT2
volatile unsigned int k = 0, j = 0, count = 0;
volatile unsigned char start = 0, catch = 0, ref = 10, countbut = 0;
volatile unsigned char temp[8];
volatile unsigned char ma_1[10][8] = { { 0x00, 0x7E, 0xFF, 0x81, 0x81, 0xFF,
		0x7E, 0x00 }, { 0x00, 0x82, 0x82, 0xFF, 0xFF, 0x80, 0x80, 0x00 }, {
		0x00, 0xC6, 0xE7, 0xF1, 0xB9, 0x9F, 0x8E, 0x00 }, { 0x00, 0x66, 0xE7,
		0x81, 0x89, 0xFF, 0x76, 0x00 }, { 0x00, 0x38, 0x24, 0xA2, 0xFF, 0xFF,
		0xA0, 0x00 }, { 0x00, 0x6F, 0xEF, 0x89, 0x89, 0xF9, 0x71, 0x00 }, {
		0x00, 0x7E, 0xFF, 0x89, 0x89, 0xFB, 0x72, 0x00 }, { 0x00, 0x01, 0xF1,
		0xF9, 0x0D, 0x07, 0x03, 0x00 }, { 0x00, 0x76, 0xFF, 0x89, 0x89, 0xFF,
		0x76, 0x00 }, { 0x00, 0x4E, 0xDF, 0x91, 0x91, 0xFF, 0x7E, 0x00 } }; //cot
volatile unsigned char ma_2[8] = { 0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf,
		0x7f };
volatile unsigned char ma_3[32] = { 0, 0, 0, 0, 0, 0, 0, 0, 0x00, 0x7E, 0x4A,
		0x4A, 0x34, 0x00, 0x7E, 0x00, 0x7E, 0x04, 0x08, 0x7E, 0x00, 0x3C, 0x42,
		0x42, 0x74, 0x00, 0x3C, 0x42, 0x42, 0x3C, 0x00, 0x5E };
volatile unsigned char data[8];
volatile char m = 0, i;
bool Shift_en, select = 0, restart = 0;

void Scan_led(void) {
	if (((count % Velocity) == 0) && (start == 1)) {
		if (j < 9)
			j++;
		else {
			j = 0;
			count = 0;
		}
	}
}

void shift_matrix(void) {
	int i, j;
	for (j = 0; j < 32; j++) {
		if (j < 25) {
			for (i = 0; i < 8; i++)
				data[i] = ma_3[j + i];
			for (k = 0; k < 8; k++) {
				shiftout_1(data[k], ma_2[k]);
				__delay_cycles(50000);
			}
		} else {
			int a = 31 - j;
			int b = 7 - a;
			for (i = 0; i <= a; i++)
				data[i] = ma_3[j + i];
			for (i = 0; i < b; i++)
				data[i + a + 1] = ma_3[i];
			for (k = 0; k < 8; k++) {
				shiftout_1(data[k], ma_2[k]);
				__delay_cycles(50000);
			}

		}
	}
}
int main(void) {
//	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
//	BCSCTL1 = CALBC1_8MHZ; 		// CAI DAT TAN SO 16MHZ
//	DCOCTL = CALDCO_8MHZ;
	config();
//	__bis_SR_register(GIE);		//cho phep ngat toan cuc
	for (i = 0; i < 8; i++)
		data[i] = ma_3[i];

	while (1) {
//for (k=0; k<8; k++)
//	shiftout_1(ma_1[k], ma_2[k]);
//	__delay_cycles(3000000);
		if ( catch != ref)
			for (k = 0; k < 8; k++)
				shiftout_1(ma_1[j][k], ma_2[k]);
		else {
			restart = 1;
			countbut = 0;
			for (k = 0; k < 8; k++)
				ma_3[k] = ma_1[ catch][k];
			shift_matrix();
		}
//	shift_matrix();
	}
}
#pragma vector = PORT2_VECTOR
__interrupt void interrup(void) {
	switch (P2IFG & (but_up + but_down + but_setup + but_onl)) {
	case but_up: {
		if (select == 0)
			catch = j;
		select = 1;
		start = (start == 0);
		countbut++;
		if (countbut > 2)
			ref = j;
		P2IFG &= ~but_up;
		break;
	}
	case but_down: {
		if (select == 1)
			start = 0;
		select = 0;
		if (j < 9)
			j++;
		else
			j = 0;
		if (restart == 1) {
			ref = 10;
			restart = 0;
		}
		P2IFG &= ~ but_down;
		break;
	}
//	case but_setup: {
//		break;
//	}
//	case but_onl: {
//		break;
//	}
	}
}
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TAIV_Interrupt(void) {
	switch (TA0IV) {
	case 0x0a:
		count++;
		Scan_led();
		break;
	}
}
