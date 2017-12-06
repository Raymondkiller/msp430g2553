////////////////////////////////////////////////////////////////////
// THU VIEN HAM CLOCK
// VIET BOI : PHAM VAN THUAN	DTVT07-K55
// Email:	terran991992@gmail.com
// Blog :	http://thuanbk55.blogspot.com/
// .................................................................		
// AP DUNG CHO MACH UNG DUNG MSP430
//******************************************************************/

#ifndef CLOCK_H_
#define CLOCK_H_

// Tan so Calib toi thieu la 100Khz
// Chu y cac gia tri CALDCO va CALBC1 duoc luu trong Flash
#define DELTA_100KHZ	24			// 24  x 4096   = 98KHZ
#define DELTA_400KHZ  	98        	// 98 x 4096Hz = 401KHz
#define DELTA_1MHZ    	244        	// 244 x 4096Hz = 999.4Hz
#define DELTA_8MHZ    	1953      	// 1953 x 4096Hz = 7.99MHz
#define DELTA_12MHZ   	2930    	// 2930 x 4096Hz = 12.00MHz
#define DELTA_16MHZ   	3906      	// 3906 x 4096Hz = 15.99MHz

//Chu y thach anh ngoai khong mo phong bang protues duoc
typedef enum { 	VLO,					//Xung noi 12Khz
				DCO_10KHZ,				//Tan so noi cuc thap,
				DCO_100KHZ,				//Tan so noi thap
				DCO_400KHZ,				//Tan so noi thap
				DCO_1MHZ,DCO_8MHZ,		//Tan so noi cao
				DCO_12MHZ,DCO_16MHZ,	//Tan so noi cao
				LF,						//Su dung thach anh ngoai tan so thap - 32.768Khz
				HF_1,HF_2,HF_3			//Su dung thach anh ngoai tan so tu 0.4 - 1MHZ
				} CLOCK;		
				
void Select_Clock(CLOCK str);
// Chinh lai tan so DCO,sau khi tinh
// CHU Y :xung clock bi thay doi
// Delta = Tan so/ 4096
//Tan so Calib toi thieu la 100Khz,
//Tan so toi thieu cua CPU khoang 10Khz do chia tan ACLK
void Set_DCO(unsigned int Delta,unsigned int* var_DCO,unsigned int* var_BCS);
void Calib_DCO();
/******************************************************************************\
*					Function (noi dung ham)	                           *
\******************************************************************************/
//////////////////////////////////////////////////////
// Voi xung noi,khi mo phong protues de su dung dien ap nguon cap la 2.7V
// Dien ap khi su dung thuc te la 3.3 V , voi RSEL<=9 thi coi nhu clock=1,5,clock(U=1.8V)
void Select_Clock(CLOCK str)
{
	_delay_cycles(20000);	//Tranh loi tu cac hoat dong chua hoan tat
	//Setup MCLK:Clock dung cho CPU
	switch(str)
	{
		case VLO:
		{
			DCOCTL =0;//DCOx=1 MODx=0
			BCSCTL1 = XT2OFF;
			BCSCTL2 = SELM_3 + SELS +DIVM_3;
			BCSCTL3 = LFXT1S_2;
			break;
		}
		case DCO_10KHZ:
		{
			DCOCTL = 0;//DCOx=1 MODx=0
			BCSCTL1 = XT2OFF ;//RSELx=0
			BCSCTL2 =SELM_0 + DIVM_3 ;//DIVMx=8
			BCSCTL3 = XCAP_3 + LFXT1S_0;
			break;
		}
		case DCO_100KHZ:
		{
			DCOCTL = 42;//DCOx=0 MODx=0
			BCSCTL1 = 128;//RSELx=0
			BCSCTL2 =SELM_0 ;//DIVMx=0 ,dung dien tro trong
			BCSCTL3 = XCAP_3 + LFXT1S_0;
			break;
		}		
		case DCO_400KHZ:
		{
			DCOCTL = 114;
			BCSCTL1 = 132;
			BCSCTL2 =SELM_0 + DIVM_0 ;//DIVMx=8
			BCSCTL3 = XCAP_3 + LFXT1S_0;
			break;
		}
		case DCO_1MHZ:
		{
			DCOCTL = CALDCO_1MHZ;
			BCSCTL1 = CALBC1_1MHZ;
			BCSCTL2 = SELM_0 ;//DIVMx=0
			BCSCTL3 = XCAP_3 + LFXT1S_0;
			break;
		}
		case DCO_8MHZ:
		{
			DCOCTL = CALDCO_8MHZ;
			BCSCTL1 = CALBC1_8MHZ;
			BCSCTL2 = SELM_0;
			BCSCTL3 = XCAP_3 + LFXT1S_2;
			break;
		}
		case DCO_12MHZ:
		{
			DCOCTL = CALDCO_12MHZ;
			BCSCTL1 = CALBC1_12MHZ;
			BCSCTL2 = SELM_0;
			BCSCTL3 = XCAP_3 + LFXT1S_2;
			break;
		}
		case DCO_16MHZ:
		{
			DCOCTL = CALDCO_16MHZ;
			BCSCTL1 = CALBC1_16MHZ;
			BCSCTL2 = SELM_0;
			BCSCTL3 = XCAP_3 + LFXT1S_2;
			break;
		}
		case LF:
		{
			BCSCTL1 = XT2OFF+DIVA_0;
			BCSCTL2 = SELM_3 + SELS + DIVM_0 + DIVS_0;
			BCSCTL3 = XCAP_1;
		}
		case HF_1:
		{
			BCSCTL1 = XT2OFF + XTS;
			BCSCTL2 = SELM_3 + SELS;
			BCSCTL3 = LFXT1S_0;	
			break;		
		}
		case HF_2:
		{
			BCSCTL1 = XT2OFF + XTS;
			BCSCTL2 = SELM_3 + SELS;
			BCSCTL3 = LFXT1S_1;	
			break;		
		}
		case HF_3:
		{
			BCSCTL1 = XT2OFF + XTS;
			BCSCTL2 = SELM_3 + SELS;
			BCSCTL3 = LFXT1S_2;	
			break;		
		}		
	}	
	_delay_cycles(10000);
}

// Set DCO to selected frequency
void Set_DCO(unsigned int Delta,unsigned int* var_DCO,unsigned int* var_BCS)
{
	unsigned int Compare, Oldcapture = 0;

	P1OUT = 0x00;                             // Clear P1 output latches
	P1SEL = 0x10;                             // P1.4 SMCLK output
	P1DIR = 0x11;                             // P1.0,4 output

	BCSCTL1 |= DIVA_3;                        // ACLK = LFXT1CLK/8
	TACCTL0 = CM_1 + CCIS_1 + CAP;            // CAP, ACLK
	TACTL = TASSEL_2 + MC_2 + TACLR;          // SMCLK, cont-mode, clear

	while (1)
	{
		P1OUT^=BIT6;
		while (!(CCIFG & TACCTL0));             // Wait until capture occured
		TACCTL0 &= ~CCIFG;                      // Capture occured, clear flag
		Compare = TACCR0;                       // Get current captured SMCLK
		Compare = Compare - Oldcapture;         // SMCLK difference
		Oldcapture = TACCR0;                    // Save current captured SMCLK

		if (Delta == Compare)
		break;                                // If equal, leave "while(1)"
		else if (Delta < Compare)
		{
			DCOCTL--;                             // DCO is too fast, slow it down
			if (DCOCTL == 0xFF)                   // Did DCO roll under?
			if (BCSCTL1 & 0x0f)
			BCSCTL1--;                        // Select lower RSEL
		}
		else
		{
			DCOCTL++;                             // DCO is too slow, speed it up
			if (DCOCTL == 0x00)                   // Did DCO roll over?
			if ((BCSCTL1 & 0x0f) != 0x0f)
			BCSCTL1++;                        // Sel higher RSEL
		}

	}
	*var_BCS=(unsigned int)BCSCTL1;
	*var_DCO=(unsigned int)DCOCTL;
	TACCTL0 = 0;                              // Stop TACCR0
	TACTL = 0;                                // Stop Timer_A
	BCSCTL1 &= ~DIVA_3;                       // ACLK = LFXT1CLK
}

#endif	/* CLOCK_H_ */
