#include <msp430.h>
#include <math.h>
#include"USCI_SPI_1_0_1.h"


/*
 * 		K.V.D.T
 * 	 03-Aug-2016
 *   PID_Control
 *
 *   Input: goc cua truc z
 *   		kI, kP, kD
 *   Output: TA1CCR1 ->> xung PWM
 *
 */
#define hight_balancing_robot   1600 // chieu cao tu carm bien den truc banh xe: mm/10

#define PWM_add_1       BIT1	//PWM
#define Dir_motor_1     BIT2	//direction 0 or 1
#define PWM_add_2       BIT6	//PWM
#define Dir_motor_2     BIT7	//direction 0 or 1

#define toi  			1
#define lui				0

#define Large_pulse   50000	//do rong chu ki xung

#define sampling_time   25   // thoi gian lay mau: ms
#define inv_sampling_time   40   // nghich dao cua thoi gian lay mau: 1/s

#define kP  			0
#define kI  			0
#define kD  			0

unsigned int e, re_e = 0;
unsigned long P_part, I_part, D_part, output = 0;
float re_goc;

unsigned char varAngleOld = 90, varAngleNew = 90;	// Used to calculate PID derivative

/* Get from sensor chip */
unsigned char varRx;								// Received data
unsigned char varDirection ;						// 0: backward, 1: forward
unsigned char varAngle;								// Range of value: 0~90 degrees

void dataDecode(unsigned char varRx , unsigned char *pAngle, unsigned char *pDirection)
{
	*pAngle 	= varRx & 0x7F;			// 7 lowest bits of varRx
	*pDirection = (varRx >> 7) & 0xFF;	// Highest bit of varRx
}

void config(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	if (CALBC1_16MHZ == 0xFF) {
		while (1)
			;
	}
	DCOCTL = 0;
	BCSCTL1 = CALBC1_16MHZ;        //2 thanh ghi cài đặt tần số hoạt động
	DCOCTL = CALDCO_16MHZ;        //Ở đây là 16 Mhz
	_BIS_SR(GIE);

	//config_Timer
	TA1CTL |= TASSEL_2 + MC_1 + TAIE;	//mode1 dem 0 -> Ta0CCR0
	TA1CCTL2 |= CCIE;

	TA0CTL |= TASSEL_2 + MC_1 + TAIE;	//mode1 dem 0 -> Ta0CCR0
	TA0CCTL2 |= CCIE;

	//config_PWM
	//motor_1
	P2SEL = 0;
	P2SEL2 = 0;
	P2SEL |= PWM_add_1;		// address PWM,  direction
	P2DIR |= PWM_add_1 + Dir_motor_1;
	P2OUT &= ~Dir_motor_1;
	TA1CCTL1 = OUTMOD_7;
	TA1CCR0 = Large_pulse;		//do rong xung
	//motor_2
	P1SEL = 0;
	P1SEL2 = 0;
	P1SEL |= PWM_add_2;		// address PWM, direction
	P1DIR |= PWM_add_2 + Dir_motor_2;
	P1OUT &= ~Dir_motor_2;
	TA0CCTL1 = OUTMOD_7;
	TA0CCR0 = Large_pulse;		//do rong xung
}

void control_motor_1(unsigned long ta1ccr1_1, char direction_1) {
	switch (direction_1) {
	case toi: {
		unsigned int Large_pulse_1 = 0;
		Large_pulse_1 = (Large_pulse - ta1ccr1_1);
		TA1CCR1 = Large_pulse_1; // PWM
		P2OUT |= Dir_motor_1; // right direction
		break;
	}
	case lui: {
		TA1CCR1 = ta1ccr1_1; // PWM
		P2OUT &= ~Dir_motor_1; // opposite direction
		break;
	}
	}
}

void control_motor_2(unsigned long ta1ccr1_2, char direction_2) {
	switch (direction_2) {
	case toi: {
		unsigned int Large_pulse_2 = 0;
		Large_pulse_2 = (Large_pulse - ta1ccr1_2);
		TA0CCR1 = Large_pulse_2; // PWM
		P1OUT |= Dir_motor_2; // right direction
		break;
	}
	case lui: {
		TA0CCR1 = ta1ccr1_2; // PWM
		P1OUT &= ~Dir_motor_2; // opposite direction
		break;
	}
	}
}

void balance_control(float goc, char direction) {
	re_goc = goc / 57.3;
	e = hight_balancing_robot * cos(re_goc);
	P_part = kP * e;
	D_part = kD * (e - re_e) * inv_sampling_time;
	I_part += kI * sampling_time * e / 1000;
	output = P_part + D_part + I_part;
	if (output >= Large_pulse)
		output = Large_pulse - 1;
	if (output <= 0)
		output = 1;
	control_motor_1(output, direction);
	control_motor_2(output, direction);
	re_e = e;
}
int main(void) {
	config();
	spiA0Setup(SPI_SLAVE, 4, INT_SPIA0_RX_ON, INT_SPIA0_TX_OFF);
	while(1) {

		balance_control(varAngle,varDirection);
	}

}

/**************************************************************************************************
 *	INTERRUPT SERVICE ROUTINEs
 *************************************************************************************************/
/* SPI RX */
/* (Used to get data from sensor chip) */
#pragma vector = USCIAB0RX_VECTOR
__interrupt void rxIsr (void)
{
	while (UCA0STAT & UCBUSY);		// Wait for bus
	varRx = UCA0RXBUF;				// Get received data
	dataDecode(varRx, &varAngle, &varDirection);// Decode varRx to obtain varAngle and varDirection
	varAngleOld = varAngleNew;
	varAngleNew = varAngle;
}


/**************************************************************************************************
 *	END OF main.c
 *************************************************************************************************/

