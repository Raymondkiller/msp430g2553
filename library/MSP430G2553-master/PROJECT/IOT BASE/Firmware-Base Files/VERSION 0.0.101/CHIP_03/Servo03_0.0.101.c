/*
 *	File			:	Servo03_0.0.101.c
 *	Date created	:	27/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:	Source file for Servo of Third Chip
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "HEADER03_0.0.101.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
servo03Open (void)
{
	gpioLow(PORT2, PIN_SERVO_DIR);
	pwmSetup(TIMER_A_1, MODE_UP, BIT1, PWM_RST_SET, 1000, 990);
	__delay_cycles(DL_2S * FREQUENCY);
	pwmSetup(TIMER_A_1, MODE_UP, BIT1, PWM_RST_SET, 1000, 0);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
servo03Close (void)
{
	gpioLow(PORT2, PIN_SERVO_DIR);
	pwmSetup(TIMER_A_1, MODE_UP, BIT1, PWM_RST_SET, 1000, 990);
	__delay_cycles(DL_2S * FREQUENCY);
	pwmSetup(TIMER_A_1, MODE_UP, BIT1, PWM_RST_SET, 1000, 0);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF Servo03_0.0.101.c
 *************************************************************************************************/