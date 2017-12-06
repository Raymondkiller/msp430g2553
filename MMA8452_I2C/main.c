#include <msp430.h> 
#include "library_I2C.h"


/*
 *  MMA8452 with I2C
 *
 *  Created on: Jul 14, 2016
 *      Author: K.V.D.T
 *
 */
////MMA define
//#define STATUS_REG            0x00
//#define slave_add 0x1C     // SA0=0
//#define CTRL_REG1 0x2A
//#define CTRL_REG2 0x2B
//#define CTRL_REG3  0x2C
//#define CTRL_REG4 0x2D
//#define CTRL_REG5 0x2E
//#define ACTIVE_MASK 0x01
//#define XYZ_DATA_CFG_REG 0x0E
//#define SCALE 0x00// FS1=1,FS0=0       2g
//#define FS_MASK 0x03 // FS0=1,FS1=1
//#define DR_MASK 0x38
//#define DR_0 0x10      //200 Hz
//#define OUT_X_LSB 0x02
//#define OUT_X_MSB 0x01
//#define OUT_Y_LSB 0x04
//#define OUT_Y_MSB 0x03
//#define OUT_Z_LSB 0x06
//#define OUT_Z_MSB  0x05
//#define ID_devide 0x0D
//#define MODs_MASK 0x01
//#define HP_FILTER_CUTOFF 0x06
//#define SENSITIVITY_2G   1024
//#define OFF_X_REG             0x2F            // XYZ Offset
//#define OFF_Y_REG             0x30
//#define OFF_Z_REG             0x31
////*******************************************************************************
////       Bien toan cuc
////&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//int x_h,x_l,y_h,y_l,z_h,z_l;
//long Xout_12_bit, Yout_12_bit, Zout_12_bit;
//float Xout_g, Yout_g, Zout_g,a,b,c;
//char Xoffset, Yoffset, Zoffset;
//
void MMA845x_Standby (void)
{
   byte n;
   n = read_mma(CTRL_REG1);
   write_mma(CTRL_REG1, n & ~ACTIVE_MASK);
}
void MMA845x_Active ()
{
   write_mma(CTRL_REG1, (read_mma(CTRL_REG1) | ACTIVE_MASK));
}
void MMA845x_fullscale()
{

   MMA845x_Standby();
   write_mma(XYZ_DATA_CFG_REG, (read_mma(XYZ_DATA_CFG_REG) & ~FS_MASK));
   write_mma(XYZ_DATA_CFG_REG, (read_mma(XYZ_DATA_CFG_REG) | SCALE));// scale 2g
   MMA845x_Active();
   }
void MMA845x_datarate()
{
   MMA845x_Standby();
   write_mma(CTRL_REG1, (read_mma(CTRL_REG1) & ~DR_MASK));
   write_mma(CTRL_REG1, (read_mma(CTRL_REG1) | DR_0));//Data rate 200Hz
   MMA845x_Active();

   }
//void MMA845x_oversampling() {
//MMA845x_Standby();
//   Write_mma(CTRL_REG2, (read_mma(CTRL_REG2) & ~MODS_MASK));
//MMA845x_Active();}


int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    BCSCTL1 = CALBC1_1MHZ;        //2 thanh ghi cài đặt tần số hoạt động
    DCOCTL = CALDCO_1MHZ;        //Ở đây là 1 Mhz

    I2C_USCI_Init(0x1D);
    UART_Init();

    while(1) {
    	UART_Write_String("      K.V.D.T     ");
    	    	__delay_cycles(200000);

    	float x,y,z;
    	x = I2C_USCI_Read_Byte(MMA8452Q_OFF_X);
    	UART_Write_Int(x);
    	y = I2C_USCI_Read_Byte(MMA8452Q_OFF_Y);
    	UART_Write_Int(y);
    	z = I2C_USCI_Read_Byte(MMA8452Q_OFF_Z);
    	UART_Write_Int(z);


    	__bis_SR_register(LPM0);
}
}
