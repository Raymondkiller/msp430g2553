#include <msp430.h> 

/*
 * K.V.D.T
 * 13-7-2016
 * I2C with MMA845x
 *
 */

#define MMA8452Q_STATUS        (0x00)
#define MMA8452Q_OUT_X_MSB    (0x01)
#define MMA8452Q_XYZ_DATA_CFG    (0x0E)
#define MMA8452Q_OFF_X    (0x2F)
#define MMA8452Q_OFF_Y    (0x30)
#define MMA8452Q_OFF_Z    (0x31)
#define MMA8452Q_CTRL_REG1    (0x2A)
#define MMA8452Q_CTRL_REG2    (0x2B)
#define MMA8452Q_CTRL_REG3    (0x2C)
#define MMA8452Q_CTRL_REG4    (0x2D)
#define MMA8452Q_CTRL_REG5    (0x2E)
#define MMA8452Q_WHO_AM_I    (0x0D)




unsigned int data[];

void I2C_USCI_Init(unsigned char addr)
{
			P1SEL |= BIT6 + BIT7;
            P1SEL2 |= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
            P3DIR &=~ (BIT6 + BIT7);
            P3OUT |= (BIT6 + BIT7);
            P3REN |= BIT6 + BIT7;
            UCB0CTL1 |= UCSWRST;                      // Enable SW reset
            UCB0CTL0 = UCMST+UCMODE_3+UCSYNC;         // I2C Master, synchronous mode
            UCB0CTL1 = UCSSEL_2+UCSWRST;              // Use SMCLK, keep SW reset
            UCB0BR0 = 40;                             // fSCL = SMCLK/40 = ~400kHz
            UCB0BR1 = 0;
            UCB0I2CSA = addr;                         // Set slave address
            UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
}





unsigned char I2C_USCI_Read_Byte(unsigned char address) {
	while (UCB0CTL1 & UCTXSTP);             	// Cho tin hieu I2C STT duoc gui di
	UCB0CTL1 |= UCTR + UCTXSTT;             	// I2C TX,START

	while (!(IFG2 & UCB0TXIFG));					// Cho gui xong
	UCB0TXBUF = address;                      	// Dia chi luu gia tri Seconds

	while (!(IFG2 & UCB0TXIFG));					// Cho gui xong

	UCB0CTL1 &= ~UCTR;                      // I2C RX
	UCB0CTL1 |= UCTXSTT;                    // I2C RESTART
	IFG2 &= ~UCB0TXIFG;                     // Xoa co ngat USCI_B0 TX

	while (UCB0CTL1 & UCTXSTT);             // Cho den khi I2C STT duoc gui di
	UCB0CTL1 |= UCTXSTP;                    // Gui bit STOP
	return UCB0RXBUF;
}




//unsigned char I2C_USCI_Read_Word(unsigned char Addr_Data, unsigned char *Data,
//		unsigned char Length) {
//	unsigned char i = 0;
//	while (UCB0CTL1 & UCTXSTP);             // Loop until I2C STT is sent
//	UCB0CTL1 |= UCTR + UCTXSTT;             // I2C TX, start condition
//
//	while (!(IFG2 & UCB0TXIFG));
//	IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
//	if (UCB0STAT & UCNACKIFG)
//		return UCB0STAT;	//Neu bao loi
//	UCB0TXBUF = Addr_Data;                      // Dia chi luu gia tri Seconds
//
//	while (!(IFG2 & UCB0TXIFG));
//	if (UCB0STAT & UCNACKIFG)
//		return UCB0STAT;	//Neu bao loi
//
//	UCB0CTL1 &= ~UCTR;                      // I2C RX
//	UCB0CTL1 |= UCTXSTT;                    // I2C start condition
//	IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
//	while (UCB0CTL1 & UCTXSTT);             // Loop until I2C STT is sent
//	for (i = 0; i < (Length - 1); i++) {
//		while (!(IFG2 & UCB0RXIFG));
//		IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
//		Data[i] = UCB0RXBUF;
//	}
//	while (!(IFG2 & UCB0RXIFG));
//	IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
//	UCB0CTL1 |= UCTXSTP;                    // I2C stop condition after 1st TX
//	Data[Length - 1] = UCB0RXBUF;
//	IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
//	return 0;
//}




//unsigned char I2C_USCI_Write_Byte(unsigned char address, unsigned char data)
//{
//	while (UCB0CTL1 & UCTXSTP);             // Cho den khi tin hieu STT duoc gui xong
//	UCB0CTL1 |= UCTR + UCTXSTT;             // I2C TX, Gui bit START
//
//	while (!(IFG2&UCB0TXIFG));				// Cho cho bit START gui xong
//	if(UCB0STAT & UCNACKIFG) return UCB0STAT;	//Neu bao loi thì thoat khoi ham
//	UCB0TXBUF = address;					// Gui dia chi thanh ghi can ghi
//
//
//	while (!(IFG2&UCB0TXIFG));				// Cho gui xong
//	if(UCB0STAT & UCNACKIFG) return UCB0STAT;	//Neu bao loi thì thoat khoi ham
//	UCB0TXBUF = data;						// Gui du lieu
//
//	while (!(IFG2&UCB0TXIFG));				// Cho gui xong
//	if(UCB0STAT & UCNACKIFG) return UCB0STAT;	//Neu bao loi thì thoat khoi ham
//	UCB0CTL1 |= UCTXSTP;                    // Gui bit STOP
//	IFG2 &= ~UCB0TXIFG;                     // Xoa co USCI_B0 TX
//	return 0;
//}



unsigned long SMCLK_F=1000000;                 // frequency of Sub-System Master Clock in Hz
unsigned long BAUDRATE=9600;                   // may be ... 1200, 2400, 4800, 9600, 19200, ...

char UART_Read_Char();							//Nhan ki tu
void UART_Read_String(char *s);					//Nhan chuoi ky tu
char UART_Data_Ready();							//Kien tra module san sang

void UART_Init()
{
	unsigned int tempfactor;
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT
	P1SEL |= BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
	P1SEL2 |= BIT1 + BIT2;
	UCA0CTL0 =0 ;		//Tat Parity ,LSB first,8-bit data,one stop bits
	UCA0CTL1 |= UCSSEL_2; // SMCLK

 	tempfactor = SMCLK_F/BAUDRATE;
    UCA0BR0 = (unsigned char) tempfactor&0x00FF;
    tempfactor >>= 8;
    UCA0BR1 = (unsigned char) (tempfactor&0x00FF);
    UCA0MCTL |=UCBRS_5;	// Modulation UCBRSx = 5
	UCA0CTL1 &=~ UCSWRST; // **Initialize USCI state machine**
	IE2 |= UCA0RXIE; // Enable USCI_A0 RX interrupt
	__bis_SR_register(GIE); // Interrupts enabled
}

void UART_Write_Char(unsigned char data)
{
	while (!(IFG2&UCA0TXIFG)); // Doi gui xong ky tu truoc
	UCA0TXBUF= data; // Moi cho phep gui ky tu tiep theo
}

void UART_Write_Int(unsigned long n)
{
     unsigned char buffer[16];
     unsigned char i,j;

     if(n == 0) {
    	 UART_Write_Char('0');
          return;
     }

     for (i = 15; i > 0 && n > 0; i--) {
          buffer[i] = (n%10)+'0';
          n /= 10;
     }

     for(j = i+1; j <= 15; j++) {
    	 UART_Write_Char(buffer[j]);
     }
}

void UART_Write_String(char* string)
{
	while(*string) // Het chuoi ky tu thi thoat
		{
		while (!(IFG2&UCA0TXIFG)); // Doi gui xong ky tu truoc
		UCA0TXBUF= *string; // Moi cho phep gui ky tu tiep theo
		string ++; // Lay ky tu tiep theo
		}
	UART_Write_Char(0);
}

//In ra man hinh so thuc x voi so cho hien thi = length, so chu so sau dau phay la coma
void UART_Write_Float(float x, unsigned char coma)
{
	unsigned long temp;
	if(coma>4)coma=4;
	// de trong 1 ki tu o dau cho hien thi dau
	if(x<0)
	{
		UART_Write_Char('-');			//In so am
		x*=-1;
	}
	temp = (unsigned long)x;									// Chuyan thanh so nguyen.

	UART_Write_Int(temp);

	x=((float)x-temp);//*mysqr(10,coma);
	if(coma!=0)UART_Write_Char('.');	// In ra dau "."
	while(coma>0)
	{
		x*=10;
		coma--;
	}
	temp=(unsigned long)(x+0.5);	//Lam tron
	UART_Write_Int(temp);
}

char UART_Data_Ready()
{
	if(UCA0RXIFG) return 1;
	else return 0;
}

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	BCSCTL1 = CALBC1_1MHZ;        //2 thanh ghi cài đặt tần số hoạt động
	    DCOCTL = CALDCO_1MHZ;        //Ở đây là 1 Mhz
	I2C_USCI_Init(0x1D);
	UART_Init();

	int x,y,z;
	x = I2C_USCI_Read_Byte(MMA8452Q_OFF_X);
	y = I2C_USCI_Read_Byte(MMA8452Q_OFF_Y);
	z = I2C_USCI_Read_Byte(MMA8452Q_OFF_Z);

	 UART_Write_String("shit10");

}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    while (!(IFG2 & UCA0TXIFG));                // USCI_A0 TX buffer ready?
    _delay_cycles(1000);
	UCA0TXBUF = UCA0RXBUF;                    // TX -> RXed character
	P1OUT|=BIT0;
    _delay_cycles(1000);
    P1OUT^=BIT0;
}
