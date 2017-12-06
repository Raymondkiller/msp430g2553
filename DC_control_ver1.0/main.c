#include <msp430.h> 
#include "library_DC.h"
#include "library_UART.h"
/**************
 *  22-7-2016
 * ***********
 *   K.V.D.T
 *   *******
 *   test_control_motor_secvor_DC
 */

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
//	BCSCTL1 = CALBC1_1MHZ;        //2 thanh ghi cài đặt tần số hoạt động
//	DCOCTL = CALDCO_1MHZ;        //Ở đây là 1 Mhz
	config_motor();	//setup motor
	UART_Init();	//setup UART

	while (1) {

		CONST_k();
//		control(25000, 1);
//		__delay_cycles(2000000);
//////			delay_ms(40000);
//		control(0, 1);
//		__delay_cycles(2000000);
//////			delay_ms(2000);
//		control(50000, 0);
//		__delay_cycles(2000000);
////			delay_ms(2000);
//		control(0, 0);
//		__delay_cycles(2000000);
////			delay_ms(2000);
//		UART_Write_String("k.v.d.t");
	}
}
