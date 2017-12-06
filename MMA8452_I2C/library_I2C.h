/*
 * library.h
 *
 *  Created on: Jul 14, 2016
 *      Author: K.V.D.T
 */


#define MMA8452Q_STATUS        (0x00)
#define MMA8452Q_OUT_X_MSB    (0x01)
#define MMA8452Q_XYZ_DATA_CFG    (0x0E)
#define MMA8452Q_OFF_X    (0x2F)
#define MMA8452Q_OFF_Y    (0x30)
#define MMA8452Q_OFF_Z    (0x31)
#define MMA8452Q_CTRL_REG1    (0x2A)
#define MMA8452Q_CTRL_REG2    (0x2B)
#define MMA8452Q_CTRL_REG3    (0x2C)
#define MMA8452Q_CTRL_REG4    (0x2D)
#define MMA8452Q_CTRL_REG5    (0x2E)
#define MMA8452Q_WHO_AM_I    (0x0D)



#ifndef LIBRARY_I2C_H_
#define LIBRARY_I2C_H_

//I2C

void I2C_USCI_Init(unsigned char addr);
void I2C_USCI_Set_Address(unsigned char addr);
unsigned char I2C_USCI_Read_Byte(unsigned char address);
unsigned char I2C_USCI_Read_Word(unsigned char Addr_Data, unsigned char *Data,unsigned char Length);
unsigned char I2C_USCI_Write_Byte(unsigned char address, unsigned char data);

//uart

void UART_Init();
void UART_Write_Char(unsigned char data);
void UART_Write_String(char* string);
void UART_Write_Int(unsigned long n);
void UART_Write_Float(float x, unsigned char coma);

#endif /* LIBRARY_I2C_H_ */
