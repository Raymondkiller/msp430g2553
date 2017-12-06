////////////////////////////////////////////////////////////////////
// CHUONG TRINH TEST ADC 10bit
// VIET BOI : PHAM VAN THUAN	DTVT07-K55
// Email:	terran991992@gmail.com
// Blog :	http://thuanbk55.blogspot.com/
// .................................................................
// AP DUNG CHO MACH UNG DUNG MSP430
//******************************************************************/
#include "msp430g2553.h"
#include "stdio.h"
#include "Library/Clock.h"
#include "Library/UART.h"
#include "Library/ADC.h"




unsigned int  Data[8];
void main()
{
	WDTCTL = WDTPW | WDTHOLD;	//Stop Watchdog
	Select_Clock(DCO_1MHZ);
	SMCLK_F=1000000;
	UART_Init();	//UART

	ADC10_DTC(7,&Data[0],1);
	//Doc cac ADC tu 0->7 tru A1 va A2 cho UART
	while(1)
	{
		UART_Write_Char(10);
		UART_Write_Int(Data[7]);
		UART_Write_Char(' ');		//Tab ngang
		UART_Write_Int(Data[4]);
		UART_Write_Char(' ');		//Tab ngang
		UART_Write_Int(Data[3]);
		UART_Write_Char(' ');		//Tab ngang
		UART_Write_Int(Data[2]);
		UART_Write_Char(' ');		//Tab ngang
		UART_Write_Int(Data[1]);
		UART_Write_Char(' ');		//Tab ngang
		UART_Write_Int(Data[0]);
		UART_Write_Char(10);
		_delay_cycles(1000000);
	}
}



