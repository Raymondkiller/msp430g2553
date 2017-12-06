/*
 * clock.c
 *
 *  Created on: 27-09-2017
 *      Author: KILLER
 */

#include <msp430.h>
#include "clock.h"

void config_clock_MHz(unsigned char CLOCK_CHOSE)
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    switch (CLOCK_CHOSE)
    {
    case 1:
	{
    	if (CALBC1_1MHZ == 0xFF)
    	    {
    	    	while(1);
    	    }
    	    DCOCTL = 0;
    	    BCSCTL1 = CALBC1_1MHZ;
    	    DCOCTL = CALDCO_1MHZ;
    	    break;
	}
    case 8:
	{
    	if (CALBC1_8MHZ == 0xFF)
    	    {
    	    	while(1);
    	    }
    	    DCOCTL = 0;
    	    BCSCTL1 = CALBC1_8MHZ;
    	    DCOCTL = CALDCO_8MHZ;
    	    break;
	}
    case 12:
	{
    	if (CALBC1_12MHZ == 0xFF)
    	    {
    	    	while(1);
    	    }
    	    DCOCTL = 0;
    	    BCSCTL1 = CALBC1_12MHZ;
    	    DCOCTL = CALDCO_12MHZ;
    	    break;
	}
    case 16:
	{
    	if (CALBC1_16MHZ == 0xFF)
    	    {
    	    	while(1);
    	    }
    	    DCOCTL = 0;
    	    BCSCTL1 = CALBC1_16MHZ;
    	    DCOCTL = CALDCO_16MHZ;
    	    break;
	}
    }
//    BCSCTL2 |= SELM_0;		//CHON NGUON CLK LA DCO
}

void config_timerA0(void)
{
	TA0CTL |= TASSEL_2 + MC_1 + TAIE;		//MC_1: CHON CHE DO DEM LAP LAI 0->CCR0
											//TAIE: CHO PHEP NGAT
    TA0CCR0 = 49746;
}

void config_timerA1(void)
{
	TA1CTL |= TASSEL_2 + MC_1 + TAIE;		//MC_1: CHON CHE DO DEM LAP LAI 0->CCR0
											//TAIE: CHO PHEP NGAT
    TA1CCR0 = 49746;   						// Ä�áº·t giĂ¡ trá»‹ cho bá»™ Ä‘áº¿m Timer , cĂ³ thá»ƒ thay Ä‘á»•i
    										// Do lĂ  thanh ghi 16bits , nĂªn giĂ¡ trá»‹ Ä‘áº·t  <= 65535
}
