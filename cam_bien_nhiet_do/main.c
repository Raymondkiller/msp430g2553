#include <msp430.h> 
#include "ADC.h"
#include "UART.h"
#include "Clock.h"
/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    Select_Clock(DCO_1MHZ);
    SMCLK_F=1000000;
    UART_Init();
    ADC10_Init(VCC);
    float Vol,temp;
    int ng,tp;
    int Data;
    	while(1)
        {
    		Data=ADC10_Read_Channel(0);
    		UART_Write_Char(10);
    		UART_Write_String("volt:  ");
    		Vol = Data*3.3/1024;
    		temp = Vol * 100;
    		ng=Vol;
    		tp=(Vol-ng)*100;
    		UART_Write_Int(ng);
    		UART_Write_String(".");
    		UART_Write_Int(tp);
    		UART_Write_String("             temp:  ");
    		UART_Write_Int(temp);

    		__delay_cycles(1000000);
        }
   }
