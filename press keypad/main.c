#include <msp430.h> 

/*
 * main.c
 */
volatile char n;
int config(void)
{
	P2SEL=0;
	P2SEL2=0;
	P2DIR |=0XF0;
	P2REN |= 0X0F;
	P2IE |= 0X0F;
	P2IES |= 0X0F;
	P2IFG |= 0 ;
	P2OUT = 0X0F;

	P1SEL=P1SEL2=0;
	P1DIR |= BIT0+BIT3+BIT4+BIT5;
	P1OUT  |= BIT0+BIT3+BIT4+BIT5;
return(0);
}
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	config();
	_BIS_SR(GIE);
while(1)
{
	switch (n)
	{
	case 1:
	{
		P1OUT &=~ BIT0;
		break;
	}
	case 10:
	{
		P1OUT &=~ BIT3;
		break;
	}
	}
}
}

#pragma vector = PORT1_VECTOR
__interrupt void P1_int(void)
{
	unsigned char A[4]={
	char i;
	switch (P2OUT & BIT4)
 {
	case
	switch (P2IFG & 0X0F)
	{
	case BIT0:
	{
		unsigned char A[4]={}
	}

	}
	P2IFG = 0;
}
void efect(void )
{
	switch (P2IFG&0X01)
	{
	case 1
	}
