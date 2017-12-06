/*
 * library.c
 *
 *  Created on: Jul 14, 2016
 *      Author: K.V.D.T
 */

#include <msp430.h>
#include "library_I2C.h"


//I2C

unsigned int data[];

void I2C_USCI_Init(unsigned char addr)					// config I2C
{
			P1SEL |= BIT6 + BIT7;
            P1SEL2 |= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
            P3DIR  &=~ (BIT6 + BIT7);
            P3OUT |= (BIT6 + BIT7);
            P3REN |= BIT6 + BIT7;
            UCB0CTL1 |= UCSWRST;                      // Enable SW reset
            UCB0CTL0 = UCMST+UCMODE_3+UCSYNC;         // I2C Master, synchronous mode
            UCB0CTL1 = UCSSEL_2+UCSWRST;              // Use SMCLK, keep SW reset
            UCB0BR0 = 40;                             // fSCL = SMCLK/40 = ~400kHz
            UCB0BR1 = 0;
            UCB0I2CSA = addr;                         // Set slave address
            UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
}


void I2C_USCI_Set_Address(unsigned char addr)
{
  	UCB0CTL1 |= UCSWRST;
  	UCB0I2CSA = addr;                     		// Set slave address
  	UCB0CTL1 &= ~UCSWRST;                 		// Clear SW reset, resume operation
}


unsigned char I2C_USCI_Read_Byte(unsigned char address) //read byte
{
	while (UCB0CTL1 & UCTXSTP);             	// Cho tin hieu I2C STT duoc gui di
	UCB0CTL1 |= UCTR + UCTXSTT;             	// I2C TX,START

	while (!(IFG2 & UCB0TXIFG));					// Cho gui xong
	UCB0TXBUF = address;                      	// Dia chi luu gia tri Seconds

	while (!(IFG2 & UCB0TXIFG));					// Cho gui xong

	UCB0CTL1 &= ~UCTR;                      // I2C RX
	UCB0CTL1 |= UCTXSTT;                    // I2C RESTART
	IFG2 &= ~UCB0TXIFG;                     // Xoa co ngat USCI_B0 TX

	while (UCB0CTL1 & UCTXSTT);             // Cho den khi I2C STT duoc gui di
	UCB0CTL1 |= UCTXSTP;                    // Gui bit STOP
	return UCB0RXBUF;
}




unsigned char I2C_USCI_Read_Word(unsigned char Addr_Data, unsigned char *Data,unsigned char Length) //read word
{
	unsigned char i = 0;
	while (UCB0CTL1 & UCTXSTP);             // Loop until I2C STT is sent
	UCB0CTL1 |= UCTR + UCTXSTT;             // I2C TX, start condition

	while (!(IFG2 & UCB0TXIFG));
	IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
	if (UCB0STAT & UCNACKIFG)
		return UCB0STAT;	//Neu bao loi
	UCB0TXBUF = Addr_Data;                      // Dia chi luu gia tri Seconds

	while (!(IFG2 & UCB0TXIFG));
	if (UCB0STAT & UCNACKIFG)
		return UCB0STAT;	//Neu bao loi

	UCB0CTL1 &= ~UCTR;                      // I2C RX
	UCB0CTL1 |= UCTXSTT;                    // I2C start condition
	IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
	while (UCB0CTL1 & UCTXSTT);             // Loop until I2C STT is sent
	for (i = 0; i < (Length - 1); i++) {
		while (!(IFG2 & UCB0RXIFG));
		IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
		Data[i] = UCB0RXBUF;
	}
	while (!(IFG2 & UCB0RXIFG));
	IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
	UCB0CTL1 |= UCTXSTP;                    // I2C stop condition after 1st TX
	Data[Length - 1] = UCB0RXBUF;
	IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
	return 0;
}

unsigned char I2C_USCI_Write_Byte(unsigned char address, unsigned char data)	//write byte
{
	while (UCB0CTL1 & UCTXSTP);             // Cho den khi tin hieu STT duoc gui xong
	UCB0CTL1 |= UCTR + UCTXSTT;             // I2C TX, Gui bit START

	while (!(IFG2&UCB0TXIFG));				// Cho cho bit START gui xong
	if(UCB0STAT & UCNACKIFG) return UCB0STAT;	//Neu bao loi thì thoat khoi ham
	UCB0TXBUF = address;					// Gui dia chi thanh ghi can ghi


	while (!(IFG2&UCB0TXIFG));				// Cho gui xong
	if(UCB0STAT & UCNACKIFG) return UCB0STAT;	//Neu bao loi thì thoat khoi ham
	UCB0TXBUF = data;						// Gui du lieu

	while (!(IFG2&UCB0TXIFG));				// Cho gui xong
	if(UCB0STAT & UCNACKIFG) return UCB0STAT;	//Neu bao loi thì thoat khoi ham
	UCB0CTL1 |= UCTXSTP;                    // Gui bit STOP
	IFG2 &= ~UCB0TXIFG;                     // Xoa co USCI_B0 TX
	return 0;
}

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




