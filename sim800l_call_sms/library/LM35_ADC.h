/*
 * LM35_ADC.h
 *
 *  Created on: 28-09-2017
 *      Author: KILLER
 */

#ifndef LM35_ADC_H_
#define LM35_ADC_H_

#define ADC_PORT	BIT0

typedef enum { 	ON2_5V,		//Dien ap tham chieu noi 2.5V
				ON1_5V,		//Dien ap tham chieu noi 2.5V
				VCC,//Dien ap nguon,luu y phai loc nhieu tot cho nguon neu dung che do nay
				VeREF
				} Vref;

static unsigned char Reading_channel=0;

void config_ADC10(Vref V_tham_chieu);
unsigned int ADC10_read_temp(unsigned char channel);

#endif /* LM35_ADC_H_ */
