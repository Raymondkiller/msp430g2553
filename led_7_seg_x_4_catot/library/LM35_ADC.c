/*
 * LM35_ADC.c
 *
 *  Created on: 28-09-2017
 *      Author: KILLER
 */

#include <msp430.h>
#include "LM35_ADC.h"

void config_ADC10(Vref V_tham_chieu)
{
	// Set ENC=0 thi moi chinh sua duoc cac thanh ghi
	ADC10CTL0 &= ~ENC;
	// Cho cho ADC ranh
	while(ADC10CTL1 & ADC10BUSY);
	//ADC10 Control Register 0

	//Noi cac chan voi cong tuong tu
//	ADC10AE0 = ADC_PORT;
	// Thoi gian lay mau 64xADC10CLK,200ksps,
	ADC10CTL0 = ADC10SHT_3 + ADC10ON;

	//Xoa cai dat cu
	//ADC10CTL0&=~(SREF_7 + REFOUT + REFON + REF2_5V);
	//Chon dien ap tham chieu
	switch(V_tham_chieu)
	{
		case(ON2_5V):
		{
			ADC10CTL0|= SREF_1 + REFON + REF2_5V ;
			break;
		}
		case(ON1_5V):
		{
			ADC10CTL0|= SREF_1 + REFON ;
			break;
		}
		case(VCC):
		{
			ADC10CTL0|= SREF_0;
			break;
		}
		case(VeREF):
		{
			ADC10CTL0|= SREF_2 + REFOUT ;
			break;
		}
	}

	//Bien doi tung kenh
	ADC10CTL1  = CONSEQ_0;
	ADC10DTC0=0;	//Tat DTC
	ADC10DTC1=0;
	// Cho phep chuyen doi
	ADC10CTL0 |= ENC;
	// Bat dau chuyen doi
	ADC10CTL0 |= ADC10SC;
}

unsigned int ADC10_read_temp(unsigned char channel)
{
	//Neu kenh doc khac lan cuoi cung doc
	if(channel != Reading_channel)
	{
		//Disable chuyen doi
		ADC10CTL0&=~( ADC10SC + ENC );
		//Thay doi kenh can chuyen doi-chi dung trong che do don kenh
		ADC10CTL1 &= 0x0FFF;
		ADC10CTL1|=(channel<<12);
		Reading_channel = channel;

		ADC10CTL0 &= ~ADC10IFG;		//Tat co ngat
		ADC10CTL0|= (ADC10SC + ENC);
		//__bis_SR_register(CPUOFF + GIE); // Ngat CPU cho den khi chuyen doi xong
		while(!(ADC10CTL0 & ADC10IFG));		//Cho den khi chuyen doi xong
		return ADC10MEM;		//Lay gia tri ADC
	}
	else	//Neu channel giong channel da doc lan truoc
	{
		ADC10CTL0 &= ~ADC10IFG;		//Tat co ngat
		ADC10CTL0|= (ADC10SC + ENC);	//Cho phep chuyen doi
		//__bis_SR_register(CPUOFF  + GIE); // Ngat CPU cho den khi chuyen doi xong
		while(!(ADC10CTL0 & ADC10IFG));		//Cho den khi chuyen doi xong
		return ADC10MEM;		//Lay gia tri ADC
	}
}

