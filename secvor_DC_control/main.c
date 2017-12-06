#include <msp430.h> 
#include <stdio.h>
#include <math.h>
/*
 * main.c
 * Mr.Minh
 */

// uart

void UART_Init()
{
	unsigned int tempfactor;
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT
	P1SEL |= BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
	P1SEL2 |= BIT1 + BIT2;
	UCA0CTL0 =0 ;		//Tat Parity ,LSB first,8-bit data,one stop bits
	UCA0CTL1 |= UCSSEL_2; // SMCLK

 	tempfactor = 1000000/9600;
    UCA0BR0 = (unsigned char) tempfactor&0x00FF;
    tempfactor >>= 8;
    UCA0BR1 = (unsigned char) (tempfactor&0x00FF);
    UCA0MCTL |=UCBRS_5;	// Modulation UCBRSx = 5
	UCA0CTL1 &=~ UCSWRST; // **Initialize USCI state machine**
	IE2 |= UCA0RXIE; // Enable USCI_A0 RX interrupt
	__bis_SR_register(GIE); // Interrupts enabled
}

void UART_Write_Char(unsigned char data)
{
	while (!(IFG2&UCA0TXIFG)); // Doi gui xong ky tu truoc
	UCA0TXBUF= data; // Moi cho phep gui ky tu tiep theo
}

void UART_Write_String(char* string)
{
	while(*string) // Het chuoi ky tu thi thoat
		{
		while (!(IFG2&UCA0TXIFG)); // Doi gui xong ky tu truoc
		UCA0TXBUF= *string; // Moi cho phep gui ky tu tiep theo
		string ++; // Lay ky tu tiep theo
		}
	UART_Write_Char(0);
}

void UART_Write_Int(unsigned long n)
{
     unsigned char buffer[16];
     unsigned char i,j;

     if(n == 0) {
    	 UART_Write_Char('0');
          return;
     }

     for (i = 15; i > 0 && n > 0; i--) {
          buffer[i] = (n%10)+'0';
          n /= 10;
     }

     for(j = i+1; j <= 15; j++) {
    	 UART_Write_Char(buffer[j]);
     }
}


void UART_Write_Float(float x, unsigned char coma)
{
	unsigned long temp;
	if(coma>4)coma=4;
	// de trong 1 ki tu o dau cho hien thi dau
	if(x<0)
	{
		UART_Write_Char('-');			//In so am
		x*=-1;
	}
	temp = (unsigned long)x;									// Chuyan thanh so nguyen.

	UART_Write_Int(temp);

	x=((float)x-temp);//*mysqr(10,coma);
	if(coma!=0)UART_Write_Char('.');	// In ra dau "."
	while(coma>0)
	{
		x*=10;
		coma--;
	}
	temp=(unsigned long)(x+0.5);	//Lam tron
	UART_Write_Int(temp);
}


//motor

volatile unsigned int count,direction,recount,redirection;
volatile float speed,respeed;


void config_motor() {
	 //config_I/O
	    P1SEL = 0;
	    P1SEL2 = 0;
	    P1DIR &=~ (BIT5 + BIT4);// BIT2 chanel A, BIT4 chanel B
	    P1SEL |= BIT6;// BIT6 address PWM, BIT7 direction
	    P1DIR |= BIT6 + BIT7;
	//config_Timer
		TA0CTL |= TASSEL_2 + MC_1 + TAIE;
		TA0CCR0 = 50000;
	//config_PWM
		TA0CTL |= TASSEL_2 + MC_1;
		TA0CCTL1 = OUTMOD_7;
		TA0CCR0 = 50000;
	//Config_Interrupt
	    P1REN |= BIT5 + BIT4;
	 	P1OUT |= BIT5 + BIT4;
	 	P1IE |= BIT5;
		P1IES |= BIT5;
		P1IFG &= ~BIT5;
		_BIS_SR(GIE);
       }
void control() {
//		scanf("%d",&direction);
//		scanf("%f",&speed);
	direction = 1;
		switch (direction){
		case 1: {
			P1OUT |= BIT7; // right direction
			break;
		}
		case 0: {
			P1OUT &=~ BIT7; // opposite direction
			break;
		}
		}
		TA0CCR1 = 50;
//	 	TA0CCR1 = 10*speed; // PWM
}
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    BCSCTL1 = CALBC1_1MHZ;        //2 thanh ghi cài d?t t?n s? ho?t d?ng
    DCOCTL = CALDCO_1MHZ;        //? dây là 1 Mhz
	config_motor();
	count = 0;
	UART_Init();


	while(1) {
		control();
		__delay_cycles(65000);

		if(count==0) {
		UART_Write_Char(10);
		__delay_cycles(1000000);
		UART_Write_String(" van toc tra ve la: ");
		respeed = 10*recount/167;
		UART_Write_Int(respeed);
		}

	}
}
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A1 (void) {
	switch(TA0IV) {
	case 2: {
	break; // CCR1
		}
	case 4: {
		break; // CCR2
		}
	case 10:{
		recount = count;
		count = 0;
		// over flow or CCR0
		break;
		}
	}
}
#pragma vector = PORT1_VECTOR
__interrupt
void P1_ISR(void) {
	count ++;
if (P1IN & BIT4 == 0) {
	redirection = 1; // right direction
}
else { redirection = 0;} // opposite direction
P1IFG &= ~BIT5;
}
