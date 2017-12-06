#include <msp430.h> 
#include "UART_library.h"

/*
 * 		K.V.D.T
 * 	 03-Aug-2016
 *   read_encoder
 *
 *   Input: motor
 *   Output: CCR1 and speed
 *
 */
#define Encoder       BIT5   //chanel A
#define Dir_encoder   BIT4   //chanel B
#define PWM_add       BIT6	//PWM
#define Dir_motor     BIT0	//direction 0 or 1

#define pulse_encoder 346   // so xung cua encoder
#define Time_Ecoder   50000  //thoi gian lay mau 50ms = 0,05s
#define Large_pulse   50000	//do rong chu ki xung
unsigned long count, recount;
unsigned long respeed;

void config_motor() {
	if (CALBC1_16MHZ == 0xFF) {
		while (1);
	}
	DCOCTL = 0;
	BCSCTL1 = CALBC1_16MHZ;        //2 thanh ghi cài đặt tần số hoạt động
	DCOCTL = CALDCO_16MHZ;        //Ở đây là 16 Mhz

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
	TA1CTL |= TASSEL_2 + MC_1 + TAIE;	//mode1 dem 0 -> Ta0CCR0
	TA1CCR0 = Time_Ecoder;		//chon thoi gian lay mau

//config_PWM
//	P2SEL = 0;
//	P2SEL2 = 0;
	P2SEL |= PWM_add;		//address PWM, direction
	P2DIR |= PWM_add + Dir_motor;
	P2OUT &= ~ Dir_motor;
	TA1CCTL1 = OUTMOD_7;
	TA1CCR0 = Large_pulse;		//do rong xung

}

void control(unsigned long speed, char direction) { // tim he so k roi bo vao day
	switch (direction) {
	case 1: {
		unsigned int Large_pulse_1 = 0;
		Large_pulse_1 = (Large_pulse - speed);
		TA1CCR1 = Large_pulse_1; // PWM
		P2OUT |= Dir_motor; // right direction
		break;
	}
	case 0: {
		TA1CCR1 = speed; // PWM
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

		control( 1000*stt, 0);
		respeed = 320 * 60 * recount / pulse_encoder;
		pulse_stt = 1000 * stt;

		UART_Write_String("TA1CCR1      van toc tra ve vong/phut:   ");
		UART_Write_Int(pulse_stt);
		UART_Write_String("     ");
		UART_Write_Int(respeed);
		UART_Write_Char(10);
		__delay_cycles(500000);
	}
}


int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    config_motor();

    while(1) {
    CONST_k();
    }
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_A1(void) {
	switch (TA1IV) {
	case 2: {
		break; // CCR1
	}
	case 4: {
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



