/*
 *	File			:	Speaker_0_0_101.c
 *	Date created	:	16/9/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:	Source for Speaker
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "HEADER_0_0_101.h"


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
void speakerTurnOn (void)
{
	gpioHigh(PORT1, PIN_SPEAKER);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void speakerTurnOff (void)
{
	gpioLow(PORT1, PIN_SPEAKER);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void speakerPlay (unsigned int SPEAKER_)
{
	int varTmpCount;
	switch (SPEAKER_)
	{
		case SPEAKER_ALARM:
			speakerTurnOn();
			break;
		//=========================================================================================
		case SPEAKER_FOCUS:
			if(sStatusRegister.bSpkAlarm == 0)
			{
				for(varTmpCount = 0; varTmpCount < 3; varTmpCount++)
				{
					speakerTurnOn();
					__delay_cycles(DL_1S);
					speakerTurnOff();
					__delay_cycles(DL_1S);
				}
			}
			break;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF Speaker_0_0_101.c
 *************************************************************************************************/
