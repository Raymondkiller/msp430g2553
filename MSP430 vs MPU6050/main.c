////////////////////////////////////////////////////////////////////
// CHUONG TRINH TEST MPU6050
// VIET BOI : PHAM VAN THUAN	DTVT07-K55
// Email:	terran991992@gmail.com
// Blog :	http://thuanbk55.blogspot.com/
// .................................................................
// AP DUNG CHO MACH UNG DUNG MSP430
//******************************************************************/

//Khai bao cac thanh phan su dung
#define USE_CLOCK
#define USE_I2C_USCI
#define USE_MPU6050
#define USE_UART

////////////////////////////////////////////////////////////////////////////////


#include <wchar.h>
#include "stdio.h"
//#include "string.h"
#include "Library/mymath.h"
#include <math.h>
#include "msp430g2553.h"
#include "Library/Global.h"
#include "Library/UART.h"
#include "Library/Clock.h"
#include "Library/I2C_USCI.h"
#include "Library/MPU6050.h"


int temp=0,i=0;
int abc=0;
char buff[50];

//Chu y Gyro bi sai so tinh khong dong nhat khi goc quay thay doi
// Khong tinh duoc vi phan cua gyro

void main()
{
	WDTCTL = WDTPW | WDTHOLD;
    Select_Clock(DCO_16MHZ);
	_delay_cycles(100000);

	// Khoi tao Ngat timer
	// Tao timer 0,5 s
	//TACCR0 = 10000;
	//TACCTL0 = CCIE;
	//TACTL = TASSEL_2 + MC_1 + ID_0;             // SMCLK/8, Up mode

	P1DIR|=BIT0;
	UART_Init();
	//UART_Write_Char(10);		//Ky tu xuong dong
	//UART_Write_String("Ket noi thanh cong");
	//UART_Write_Char(10);		//Ky tu xuong dong
	_delay_cycles(100000);
	Init_I2C_USCI(MPU6050_ADDRESS);
	Setup_MPU6050();
	//MPU6050_Test_I2C();
	//MPU6050_Check_Registers();
	//Calibrate_Gyros();
	_delay_cycles(320000);
	Get_Accel_Values();
	Get_Gyro_Values();
	ACCEL_XOUT = 0;
	ACCEL_YOUT = 0;
	ACCEL_ZOUT = 0;
	ACCEL_XOUT_PAST=0;			//
	ACCEL_YOUT_PAST=0;
	ACCEL_ZOUT_PAST=0;
	ACCEL_XA    =0;
	ACCEL_YA    =0;
	ACCEL_ZA    =0;
	ACCEL_XV    = 0;
	ACCEL_YV    = 0;
	ACCEL_ZV    = 0;
	ACCEL_XDECAC=0;
	ACCEL_YDECAC=0;
	ACCEL_ZDECAC=0;
	_delay_cycles(1000000);
	//__bis_SR_register(GIE);			//Cho phep ngat hoat dong
	while(1)
	{
		//Get_Gyro_Values();
		P1OUT^=BIT0;
		//sprintf(buff,"GX:%d GY:%d GZ:%d AX:%d AY:%d AZ:%d",GYRO_XOUT,GYRO_YOUT,GYRO_ZOUT,ACCEL_XOUT,ACCEL_YOUT,ACCEL_ZOUT);
		//sprintf(buff,"1%d 2%d 3%d 4%d 5%d 6%d ",GYRO_XOUT,GYRO_YOUT,GYRO_ZOUT,ACCEL_XOUT,ACCEL_YOUT,ACCEL_ZOUT);
		UART_Write_Char('1');
		sprintf(buff,"%d",ACCEL_XOUT);
		UART_Write_String(buff);
		UART_Write_Char(' ');
		//_delay_cycles(10000);
		UART_Write_Char('2');
		sprintf(buff,"%d",ACCEL_YOUT);
		UART_Write_String(buff);
		UART_Write_Char(' ');
		//_delay_cycles(10000);
		UART_Write_Char('3');
		sprintf(buff,"%d",ACCEL_ZOUT);
		UART_Write_String(buff);
		UART_Write_Char(' ');
		_delay_cycles(10000);
		Get_Accel_Values();
	}
}


// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0 (void)
{

}
