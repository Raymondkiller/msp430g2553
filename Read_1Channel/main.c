////////////////////////////////////////////////////////////////////
// CHUONG TRINH TEST TEST ADC 10bit
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


unsigned int  Data;
void main()
{
	WDTCTL = WDTPW | WDTHOLD;	//Stop Watchdog
	Select_Clock(DCO_1MHZ);
	SMCLK_F=1000000;
	UART_Init();
	ADC10_Init(ON2_5V);
	while(1)
	{
		Data=ADC10_Read_Channel(0);
		UART_Write_Char(10);
		UART_Write_String("Channel 0:");
		UART_Write_Int(Data);

		Data=ADC10_Read_Channel(11);
		UART_Write_Char(10);
		UART_Write_String("Channel 11:");
		UART_Write_Int(Data);

		_delay_cycles(1000000);
	}
}



