//#include <msp430.h>
//#include "library_DC.h"
//#include "library_DC.c"
/*
 * library_UART.h
 *
 *  Created on: Jul 22, 2016
 *      Author: K.V.D.T
 */




////////////////////////////////////////////////////////////////////
// THU VIEN DINH NGHIA CAC HAM XU LY UART
//
// nguon :	http://thuanbk55.blogspot.com/
// .................................................................
// MSP430x2xx LIBRARY
//******************************************************************/

#ifndef LIBRARY_UART_H_
#define LIBRARY_UART_H_



//*****************************************************************************
// Bien toan cuc
//*****************************************************************************

/*
 * Cac ky tu dac biet
 * 	0 Ky tu rong
 * 	1 Bat dau header
 * 	2 Bat dau van ban
 * 	3 Ket thuc van ban
 * 	4 Ket thuc truyen
 * 	5 Truy van
 * 	7 Tab ngang
 * 	8 Xoa nguoc
 * 	9 Tab ngang
 * 	10 Xuong dong
 * 	11 Tab doc
 */

//*****************************************************************************
// Transfer  UART
//*****************************************************************************
void UART_Init();						       	//Khoi tao UART
void UART_Write_Char(unsigned char data);	   	//Gui ki tu
void UART_Write_String(char* string);		  	//Gui chuoi ki tu
void UART_Write_Int(unsigned long n);		   	//Goi so kieu int
void UART_Write_Reg(char *name, int n);			//In ra gia tri bit cua thanh ghi
void UART_Write_Float(float x,unsigned char coma);		//coma<=4
//In ra man hinh so thuc x voi so cho hien thi = length, so chu so sau dau phay la coma
//*****************************************************************************
// Receive  UART
//*****************************************************************************
char UART_Read_Char();							//Nhan ki tu
void UART_Read_String(char *s);					//Nhan chuoi ky tu
char UART_Data_Ready();							//Kien tra module san sang

/******************************************************************************\
*					Function (noi dung ham)	                           *
\******************************************************************************/



#endif /* LIBRARY_UART_H_ */
