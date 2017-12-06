/*
 * config.h
 *
 *  Created on: Jul 14, 2016
 *      Author: K.V.D.T
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

//define
#define DATA_1 BIT0 //data: du lieu, sck: xung dong bo,
#define LATCH_1 BIT1 //latch: xung xuat du lieu tu 595 ra led
#define SCK_1 BIT2
#define DATA_2 BIT3
#define LATCH_2 BIT4
#define SCK_2 BIT5
#define Velocity 10
#define but_up BIT2
#define but_down BIT3
#define but_setup BIT4
#define but_onl BIT5

//funcion
void pinwrite_1(unsigned int bit, unsigned char code);
void pulse_1(void);
void pulse_2(void);
void shiftout_1(unsigned char ma1, unsigned char ma2);
void config(void);

#endif /* FUNCTION_H_ */
