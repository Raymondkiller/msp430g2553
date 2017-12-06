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
//	ADC10_Init(ON2_5V);
//	float Vol;
//	int ng,tp;
//	while(1)
//	{
//		Data=ADC10_Read_Channel(0);
//		UART_Write_Char(10);
//		UART_Write_String("Channel 0:");
//		Vol = Data*3.3/1024;
//		ng=Vol;
//		tp=(Vol-ng)*100;
//		UART_Write_Int(ng);
//		UART_Write_String(".");
//		UART_Write_Int(tp);
//
//
//		Data=ADC10_Read_Channel(11);
//		UART_Write_Char(10);
//		UART_Write_String("Channel 11:");
//		Vol = Data*3.3/1024;
//		UART_Write_Int(Vol);

		UART_Write_String("A");
//		UART_Write_Char(10);
//		UART_Write_Char(13);
		_delay_cycles(5000);

		UART_Write_String("T");
		UART_Write_Char(10);
		UART_Write_Char(13);
//		_delay_cycles(5000000);
//
//		UART_Write_String("ATD0965619712;");
//		UART_Write_Char(10);
//		UART_Write_Char(13);
//		_delay_cycles(10000000);

		while(1)
			{
	}
}



