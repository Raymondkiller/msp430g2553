/*
 * 	File			:	USCI_UART_1_1_1.c
 * 	Author			:	Nguyen Chinh Thuy
 *	Date created	:	28/05/2016
 *	Tool			: 	CCS6.1.2.00015
 *	Current version	:	1.1.1
 *	Description		:	Construct USCI UART library
 */
/****************************************************************************************
 *	IMPORT
 ***************************************************************************************/
#include "USCI_UART_1_1_1.h"


/****************************************************************************************
 *	DEFINITIONs
 ***************************************************************************************/
const uart_Setup sUartSetup[] =
{
		{// Mode 0
				CLKS_SMCLK_1MHZ,
				BAUD_9600,
				INT_RXD_OFF
		},
		{// Mode 1
				CLKS_SMCLK_1MHZ,
				BAUD_9600,
				INT_RXD_ON
		},
		{// Mode 2
				CLKS_SMCLK_8MHZ,
				BAUD_9600,
				INT_RXD_OFF
		},
		{// Mode 3
				CLKS_SMCLK_8MHZ,
				BAUD_9600,
				INT_RXD_ON
		},
		{// Mode 4
				CLKS_SMCLK_12MHZ,
				BAUD_9600,
				INT_RXD_OFF
		},
		{// Mode 5
				CLKS_SMCLK_12MHZ,
				BAUD_9600,
				INT_RXD_ON
		},
		{// Mode 6
				CLKS_SMCLK_16MHZ,
				BAUD_9600,
				INT_RXD_OFF
		},
		{// Mode 7
				CLKS_SMCLK_16MHZ,
				BAUD_9600,
				INT_RXD_ON
		}
};

/****************************************************************************************
 *	FUNCTIONs
 ***************************************************************************************/
/*
 * 	Function:	uartSetup
 * 	Purpose	:	Setup USCI_UART default
 * 	Input	:	CLKS_: Clock source
 * 				BAUD_: Baudrate
 * 				INT_RXD_: Turn on/off RXD interrupt
 * 	Output	:	None
 */
void uartSetup (const uart_Setup sUartSetup_)
{
	P1SEL    |= TXD + RXD;
	P1SEL2   |= TXD + RXD;
	UCA0CTL0  = 0;		// no parity, LSB, 8-bit, 1 stop, UART mode, asynchronous
	switch (sUartSetup_.CLKS_)
	{
		case CLKS_SMCLK_1MHZ:
		{
			UCA0CTL1 = UCSSEL_2;
			switch (sUartSetup_.BAUD_)
			{
				case BAUD_9600:
				{
					UCA0BR0   = 104;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_1 + UCBRF_0;
					break;
				}
				case BAUD_19200:
				{
					UCA0BR0   = 52;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_0 + UCBRF_0;
					break;
				}
				case BAUD_38400:
				{
					UCA0BR0   = 26;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_0 + UCBRF_0;
					break;
				}
				case BAUD_56000:
				{
					UCA0BR0   = 17;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_7 + UCBRF_0;
					break;
				}
				case BAUD_115200:
				{
					UCA0BR0   = 8;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_6 + UCBRF_0;
					break;
				}
				case BAUD_128000:
				{
					UCA0BR0   = 7;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_7 + UCBRF_0;
					break;
				}
				case BAUD_256000:
				{
					UCA0BR0   = 3;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_7 + UCBRF_0;
					break;
				}
				default:
				{
					break;
				}
			}
			break;
		}
		case CLKS_SMCLK_8MHZ:
		{
			UCA0CTL1 = UCSSEL_2;
			switch (sUartSetup_.BAUD_)
			{
				case BAUD_9600:
				{
					UCA0BR0   = 833;
					UCA0BR1   = 833>>8;
					UCA0MCTL  = UCBRS_2 + UCBRF_0;
					break;
				}
				case BAUD_19200:
				{
					UCA0BR0   = 416;
					UCA0BR1   = 416>>8;
					UCA0MCTL  = UCBRS_6 + UCBRF_0;
					break;
				}
				case BAUD_38400:
				{
					UCA0BR0   = 208;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_3 + UCBRF_0;
					break;
				}
				case BAUD_56000:
				{
					UCA0BR0   = 142;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_7 + UCBRF_0;
					break;
				}
				case BAUD_115200:
				{
					UCA0BR0   = 69;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_4 + UCBRF_0;
					break;
				}
				case BAUD_128000:
				{
					UCA0BR0   = 62;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_4 + UCBRF_0;
					break;
				}
				case BAUD_256000:
				{
					UCA0BR0   = 31;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_2 + UCBRF_0;
					break;
				}
				default:
				{
					break;
				}
			}
			break;
		}
		case CLKS_SMCLK_12MHZ:
		{
			UCA0CTL1 = UCSSEL_2;
			switch (sUartSetup_.BAUD_)
			{
				case BAUD_9600:
				{
					UCA0BR0   = 1250;
					UCA0BR1   = 1250>>8;
					UCA0MCTL  = UCBRS_0 + UCBRF_0;
					break;
				}
				case BAUD_19200:
				{
					UCA0BR0   = 625;
					UCA0BR1   = 625>>8;
					UCA0MCTL  = UCBRS_0 + UCBRF_0;
					break;
				}
				case BAUD_38400:
				{
					UCA0BR0   = 312;
					UCA0BR1   = 312>>8;
					UCA0MCTL  = UCBRS_4 + UCBRF_0;
					break;
				}
				case BAUD_56000:
				{
					UCA0BR0   = 214;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_2 + UCBRF_0;
					break;
				}
				case BAUD_115200:
				{
					UCA0BR0   = 104;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_1 + UCBRF_0;
					break;
				}
				case BAUD_128000:
				{
					UCA0BR0   = 93;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_6 + UCBRF_0;
					break;
				}
				case BAUD_256000:
				{
					UCA0BR0   = 46;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_7 + UCBRF_0;
					break;
				}
				default:
				{
					break;
				}
			}
			break;
		}
		case CLKS_SMCLK_16MHZ:
		{
			UCA0CTL1 = UCSSEL_2;
			switch (sUartSetup_.BAUD_)
			{
				case BAUD_9600:
				{
					UCA0BR0   = 1666;
					UCA0BR1   = 1666>>8;
					UCA0MCTL  = UCBRS_6 + UCBRF_0;
					break;
				}
				case BAUD_19200:
				{
					UCA0BR0   = 833;
					UCA0BR1   = 833>>8;
					UCA0MCTL  = UCBRS_2 + UCBRF_0;
					break;
				}
				case BAUD_38400:
				{
					UCA0BR0   = 416;
					UCA0BR1   = 416>>8;
					UCA0MCTL  = UCBRS_6 + UCBRF_0;
					break;
				}
				case BAUD_56000:
				{
					UCA0BR0   = 285;
					UCA0BR1   = 285>>8;
					UCA0MCTL  = UCBRS_6 + UCBRF_0;
					break;
				}
				case BAUD_115200:
				{
					UCA0BR0   = 138;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_7 + UCBRF_0;
					break;
				}
				case BAUD_128000:
				{
					UCA0BR0   = 125;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_0 + UCBRF_0;
					break;
				}
				case BAUD_256000:
				{
					UCA0BR0   = 62;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_4 + UCBRF_0;
					break;
				}
				default:
				{
					break;
				}
			}
			break;
		}
		default:
		{
			break;
		}
	}
	IE2 = sUartSetup_.INT_RXD_;		// Receive interrupt enable
	if (sUartSetup_.INT_RXD_ == INT_RXD_ON)
	{
		_BIS_SR(GIE);
	}
	UCA0CTL1 &= ~UCSWRST;		// Initialize USCI state machine
}
//-----------------------------------------------------------------------------
/*
 * 	Function:	txdChar
 * 	Purpose	:	Transmit a byte of data
 * 	Input	:	varChar: data byte
 * 	Output	:	None
 */
void txdChar (unsigned char varChar)
{
	while(!(IFG2 & UCA0TXIFG));
	UCA0TXBUF = varChar;
}
//-----------------------------------------------------------------------------
/*
 * 	Function:	txdStr
 * 	Purpose	:	Transmit a string of data
 * 	Input	:	strString: String of data
 * 	Output	:	None
 */
void txdStr (unsigned char *strString)
{
	int varCount = 0;
	do
	{
		txdChar(*(strString + varCount));
		varCount++;
	} while(*(strString + varCount - 1) != '\0');
}
//-----------------------------------------------------------------------------
/*
 * 	Function:	txdToStr
 * 	Purpose	:	Transmit to string from ASCII number of char
 * 	Input	:	varChar: data needed to convert and transmit
 * 	Output	:	None
 */
void txdToStr (unsigned char varChar)
{
	unsigned char varA, varB, varC;
	varC = (varChar % 10);
	varB = ((varChar - varC) % 100) / 10;
	varA = (varChar - 10*varB - varC) / 100;
	varC += 48; varB += 48; varA += 48;
	txdChar(varA);
	txdChar(varB);
	txdChar(varC);
}
//-----------------------------------------------------------------------------
/*
 * 	Function:	rxdChar
 * 	Purpose	:	Receive a byte of data
 * 	Input	:	None
 * 	Output	:	Byte of data
 */
unsigned char rxdChar (void)
{
	while(!(IFG2 & UCA0RXIFG));
	return UCA0RXBUF;
}
//-----------------------------------------------------------------------------
/*
 * 	Function:	rxdStr
 * 	Purpose	:	Receive a string of data
 * 	Input	:	strRxd: Destination of storing
 * 	Output	:	None
 */
void rxdStr (unsigned char strRxd[])
{
	do
	{
		*strRxd = rxdChar();
		strRxd++;
	} while((*(strRxd - 1) != '\n') && (*(strRxd - 1) != '\0'));
	*(strRxd - 1) = '\0';
}


/****************************************************************************************
 *	END OF USCI_UART_1_1_1.c
 ***************************************************************************************/