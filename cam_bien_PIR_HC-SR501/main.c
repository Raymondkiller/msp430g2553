#include <msp430.h> 

/*
 * main.c
 */
#define SWITCH			BIT2

#define	PORT_VECTOR_SWITCH		PORT1_VECTOR

#define PSEL_SWITCH		P1SEL
#define PSEL2_SWITCH	P1SEL2
#define PDIR_SWITCH		P1DIR
#define PREN_SWITCH		P1REN
#define POUT_SWITCH		P1OUT
#define PIE_SWITCH		P1IE
#define PIES_SWITCH		P1IES
#define PIFG_SWITCH		P1IFG


int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	PSEL_SWITCH &=~ SWITCH;
	PSEL2_SWITCH &=~ SWITCH;
	PDIR_SWITCH &=~ SWITCH;				//set ngo vao
	PREN_SWITCH |= SWITCH; 				//CHO PHEP TRO TREO
	POUT_SWITCH |= SWITCH; 				//TRO TREO LEN NGUON
	PIE_SWITCH |= SWITCH;					//cho phep ngat
	PIES_SWITCH |= SWITCH;				//ngat canh xuong
	PIFG_SWITCH &=~ SWITCH;        		//xoa co ngat
	P1DIR |= BIT6;
	P1OUT &=~ BIT6;
	__bis_SR_register(GIE);
	while (1)
	{
		//nop
	}
}

#pragma vector = PORT_VECTOR_SWITCH
__interrupt void interrup(void) {

	P1OUT |= BIT6;
	__delay_cycles(500000);
	P1OUT &=~ BIT6;
	PIFG_SWITCH &= ~ SWITCH;
}
