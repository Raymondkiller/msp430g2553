/*
 * led_7_seg.h
 *
 *  Created on: 26-09-2017
 *      Author: KILLER
 */

#ifndef LED_7_SEG_H_
#define LED_7_SEG_H_

static unsigned int led_number[10] = {0x3F, 0x30, 0x5B, 0x79, 0x74, 0x6D, 0x6F, 0x38, 0x7F, 0x7D};
//static unsigned char led_clk[4] = {BIT6, BIT5, BIT4, BIT3};

//DEFINE NAME PORT
#define DATA_LED 		BIT0
#define CLK_LED 		BIT1
#define LATCH_LED		BIT2
#define LED_MINU		BIT3 + BIT4
#define LED_HOUR		BIT6 + BIT5

#define PSEL_LED 		P2SEL
#define PSEL2_LED		P2SEL2
#define PORT_LED		P2OUT
#define PORT_LED_DIR	P2DIR

#define SWITCH			BIT7

#define	PORT_VECTOR_SWITCH		PORT2_VECTOR

#define PSEL_SWITCH		P2SEL
#define PSEL2_SWITCH	P2SEL2
#define PDIR_SWITCH		P2DIR
#define PREN_SWITCH		P2REN
#define POUT_SWITCH		P2OUT
#define PIE_SWITCH		P2IE
#define PIES_SWITCH		P2IES
#define PIFG_SWITCH		P2IFG


//DEFINE FUNTION
void pinwrite(unsigned int bit, unsigned char code);
void pulse(void);
void shiftout(unsigned char ma1);
void out_led7seg (unsigned char hour, unsigned char minute);
void config_LED7SEG(void);



#endif /* LED_7_SEG_H_ */
