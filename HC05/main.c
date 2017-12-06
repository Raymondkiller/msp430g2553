#include <msp430.h> 
#include "uart.h"

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
//    P2DIR|=BIT0;
//    P2OUT|=BIT0;
    UART_Init();
    /*SLAVE*/

    UART_Write_String("AT");
    __delay_cycles(5000000);
    char string[2];
    do{
    UART_Read_String(string);
    }while (string[0] != 'O');

    UART_Write_String("ATE0");
    __delay_cycles(5000000);
    do{
    UART_Read_String(string);
    }while (string[0] != 'O');

    UART_Write_String("AT+CMGF=1");
    __delay_cycles(5000000);
    do{
    UART_Read_String(string);
    }while (string[0] != 'O');

    UART_Write_String("AT+CMGS=\"0965619712\"");
    UART_Write_String("HI tuan");
//    __delay_cycles(5000000);
//    do{
//    UART_Read_String(string);
//    }while (string[0] != 'O');
//    P2OUT &=~ BIT0;

//    UART_Write_String("AT+RESET");
//    __delay_cycles(2000);
//    do{
//    UART_Read_String(string);
//    }while (string[0] != 'O');
//
//    UART_Write_String("AT+ADDR=14:2:110007");
//    __delay_cycles(2000);
//    do{
//    UART_Read_String(string);
//    }while (string[0] != 'O');
//
////
//
//    /*MASTER*/
//
//    UART_Write_String("AT");
//    __delay_cycles(2000);
//    char string[2];
//    do{
//    UART_Read_String(string);
//    }while (string[0] != 'O');
//
//    UART_Write_String("AT+ORGL");
//    __delay_cycles(2000);
//    char string[2];
//    do{
//    UART_Read_String(string);
//    }while (string[0] != 'O');
//
//    UART_Write_String("AT+RMAAD");
//    __delay_cycles(2000);
//    char string[2];
//    do{
//    UART_Read_String(string);
//    }while (string[0] != 'O');
//
//    UART_Write_String("AT+PSWD=1234");
//    __delay_cycles(2000);
//    char string[2];
//    do{
//    UART_Read_String(string);
//    }while (string[0] != 'O');
//
//    UART_Write_String("AT+ROLE=1");
//    __delay_cycles(2000);
//    char string[2];
//    do{
//    UART_Read_String(string);
//    }while (string[0] != 'O');
//
//    UART_Write_String("AT+INIT");
//    __delay_cycles(2000);
//    char string[2];
//    do{
//    UART_Read_String(string);
//    }while (string[0] != 'O');
//
//    UART_Write_String("AT+INQ");
//    __delay_cycles(2000);
//    char string[2];
//    do{
//    UART_Read_String(string);
//    }while (string[0] != 'O');
//
//    UART_Write_String("AT+LINK=14:2:110007");
//    __delay_cycles(2000);
//    char string[2];
//    do{
//    UART_Read_String(string);
//    }while (string[0] != 'O');

    /*READY*/
//
//    __delay_cycles(5000);
//    UART_Write_String("BLUETOOTH READY!");

//    while(1)
//    {
//    	UART_Write_String("s");
//    }
//	return 0;
}
