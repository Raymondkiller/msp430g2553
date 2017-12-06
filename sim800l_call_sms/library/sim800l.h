/*
 * sim800l.h
 *
 *  Created on: 26-11-2017
 *      Author: KILLER
 */

#ifndef SIM800L_H_
#define SIM800L_H_


void Sim800l_Init(char* Baudrate_Sim, char* Echo_Sim);
void Sim800l_Call(char* PNumber_Call);
void Sim800l_End_Call(char* PNumber_Call);
void Sim800l_acept_Call(char* PNumber_Call);
void Sim800l_Sms(char* PNumber_Sms, char* Text_Sms, float value);



#endif /* SIM800L_H_ */
