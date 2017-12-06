/*
 * sim800l.c
 *
 *  Created on: 26-11-2017
 *      Author: KILLER
 */
#include "UART_library.h"
#include "sim800l.h"

void Sim800l_Init(char* Baudrate_Sim, char* Echo_Sim)
{
	//test AT
	UART_Write_String("AT");
	UART_Write_Char(0x0A);
	UART_Write_Char(0x0D);
	__delay_cycles(100000);

	//echo 0: khong co, 1: co
	UART_Write_String("ATE");
	UART_Write_String(Echo_Sim);
	UART_Write_Char(0x0A);
	UART_Write_Char(0x0D);
	__delay_cycles(100000);

	//baudrate:  0  (auto), 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200
	UART_Write_String("AT+IPR=");
	UART_Write_String(Baudrate_Sim);
	UART_Write_Char(0x0A);
	UART_Write_Char(0x0D);
	__delay_cycles(100000);

	//save setup
	UART_Write_String("AT&W");
	UART_Write_Char(0x0A);
	UART_Write_Char(0x0D);
	__delay_cycles(100000);
}

/*****Call to 0xxxxxxxx  ****************/
void Sim800l_Call(char* PNumber_Call)
{
	UART_Write_String("ATD");
	UART_Write_String(PNumber_Call);
	UART_Write_String(";");
	UART_Write_Char(0x0A);
	UART_Write_Char(0x0D);
	__delay_cycles(100000);
}

/*****end Call ****************/
void Sim800l_End_Call(char* PNumber_Call)
{
	UART_Write_String("ATH\n\r");
//	UART_Write_Char(0x0A);
//	UART_Write_Char(0x0D);
	__delay_cycles(100000);
}

/*****acept Call ****************/
void Sim800l_acept_Call(char* PNumber_Call)
{
	UART_Write_String("ATA\n\r");
//	UART_Write_Char(0x0A);
//	UART_Write_Char(0x0D);
	__delay_cycles(100000);
}

/*****Sms to 0xxxxxxxx  ****************/
void Sim800l_Sms(char* PNumber_Sms, char* Text_Sms, float value)
{
	UART_Write_String("AT+CMGF=1");
	UART_Write_Char(0x0A);
	UART_Write_Char(0x0D);
	__delay_cycles(100000);
	UART_Write_String("AT+CMGS=\"");
	UART_Write_String(PNumber_Sms);
	UART_Write_String("\"");
	UART_Write_Char(0x0A);
	UART_Write_Char(0x0D);
	__delay_cycles(100000);
	UART_Write_String(Text_Sms);
	UART_Write_Float(value,2);
	UART_Write_Char(0x1a);
	__delay_cycles(5000000);
}



