/*
 * library_DC.h
 *
 *  Created on: Jul 22, 2016
 *      Author: K.V.D.T
 */

#ifndef LIBRARY_DC_H_
#define LIBRARY_DC_H_

#define Encoder       BIT5   //chanel A
#define Dir_encoder   BIT4   //chanel B
#define PWM_add       BIT2	//PWM
#define Dir_motor     BIT1	//direction 0 or 1

#define pulse_encoder 334   // so xung cua encoder
#define Time_Ecoder   50000  //thoi gian lay mau 50ms = 0,05s
#define Large_pulse   50000	//do rong chu ki xung

/*****************************************************************************\
*                             define name                                     *
 \*****************************************************************************/
void config_motor();						//ham cai dat dong co
void control(unsigned long speed, char direction);//ham dieu kien dong co: input(speed,direction)
void delay_ms(unsigned long t);			//ham delay thoi gian <don vi tinh us>
void CONST_k();						//ham tim he so k cua ham control


#endif /* LIBRARY_DC_H_ */
