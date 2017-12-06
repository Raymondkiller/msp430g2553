#include <msp430.h>
#include "library_DC.h"

/*
 * library_DC.c
 *
 *  Created on: Jul 22, 2016
 *      Author: K.V.D.T
 */

unsigned long count, recount;
unsigned long respeed;
unsigned long timer_us = 0;

/******************************************************************************\
*					     Function (noi dung ham)	                           *
 \******************************************************************************/
void config_motor() {
//	if (CALBC1_1MHZ == 0xFF) {
//		while (1);
//	}
//	DCOCTL = 0;
	BCSCTL1 = CALBC1_1MHZ;        //2 thanh ghi cài đặt tần số hoạt động
	DCOCTL = CALDCO_1MHZ;        //Ở đây là 16 Mhz

//Config_Interrupt
	P2SEL = 0;
	P2SEL2 = 0;
	P2DIR &= ~(Encoder + Dir_encoder);	 // BIT5 chanel A, BIT4 chanel B
	P2REN |= Encoder + Dir_encoder;		//cho phep tro keo
	P2OUT |= Encoder + Dir_encoder;
	P2IE |= Encoder;	//cho phep ngat encoder
	P2IES |= Encoder;	//ngat suon xuong
	P2IFG &= ~Encoder;
	_BIS_SR(GIE);

//config_Timer
	TA1CTL |= TASSEL_2 + MC_1 + TAIE;	//mode2 dem 0 -> Ta0CCR0
//	TA1CCTL2 /|= CCIE;
	TA1CCR0 = Time_Ecoder;		//chon thoi gian lay mau

//config_PWM
	P2SEL = 0;
	P2SEL2 = 0;
	P2SEL |= PWM_add;		// BIT6 address PWM, BIT7 direction
	P2DIR |= PWM_add + Dir_motor;
	P2OUT &= ~ Dir_motor;
//	TA1CTL |= TASSEL_2 + MC_1;		//mode1
	TA1CCTL1 = OUTMOD_7;
	TA1CCR0 = Large_pulse;		//do rong xung

}

void control(unsigned long speed, char direction) { // tim he so k roi bo vao day
	switch (direction) {
	case 1: {
		unsigned int Large_pulse_1 = 0;
		Large_pulse_1 = (Large_pulse - speed);  // speed * k
		TA1CCR1 = Large_pulse_1; // PWM
		P2OUT |= Dir_motor; // right direction
		break;
	}
	case 0: {
		TA1CCR1 = speed; // PWM					// speed * k
		P2OUT &= ~Dir_motor; // opposite direction
		break;
	}
	}
}

void CONST_k() {    // ham tim he so k cua ham control
// de ham chay can #include "library_UART.h"
// ham nay truyen ra 2 day so
// day so 1: la TA1CCR1 dat vao
// day so 2: = respeed ; respeed la van toc cua motor: don vi (vong/phut)
	unsigned long stt = 0, pulse_stt = 0;
	for (stt = 0; stt < 51; stt++) {

		control(1000 * stt, 0);
		respeed = 20 * 60 * recount / pulse_encoder;
		pulse_stt = 1000 * stt;

		UART_Write_String("TA1CCR1      van toc tra ve vong/phut:   ");
		UART_Write_Int(pulse_stt);
		UART_Write_String("     ");
		UART_Write_Int(respeed);
		UART_Write_Char(10);
		__delay_cycles(1000000);
//		delay_ms(1000);
	}
}

//void delay_ms(unsigned long t) {
////	TA1CTL |= TASSEL_2 + MC_1 + TAIE;	// config timer
//	t = t * 16;
//	TA1CCR2 = 49000;						// xet gia tri TA1CCR0
//	while (timer_us < t) {// khi chua dem TA1CCR0 chua du 1000 lan thi khong lam gi ca
//		_no_operation();		// 1 lan dem la tu 0 - >> TA1CCR0 : =>> t(ms)
//	}
//	TA1CCR2 = 1000;
//	timer_us = 0;
//}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_A1(void) {
	switch (TA1IV) {
	case 2: {
		break; // CCR1
	}
	case 4: {
//		timer_us++;						//bien dem delay_ms
		break;// CCR2
	}
	case 10: {
		recount = count;					//bien dem COUST_k
		count = 0;							//bien dem count
//		 over flow or CCR0
		break;
	}
	}
}

#pragma vector = PORT2_VECTOR
__interrupt void P2_ISR(void) {
	if ((P2IFG & Encoder) == Encoder) {
		count++;
	}
	P2IFG &= ~ Encoder;
}

