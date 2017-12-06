//WRITTEN BY NGUYEN TAN PHU

#define delay 500
#define  E   BIT7
#define  RS  BIT0
#define  PORT  (BIT4 + BIT5 + BIT0 + BIT7)
//-------------------------------------------------------
#define SWITCH          BIT3

#define PSEL_SWITCH     P1SEL
#define PSEL2_SWITCH    P1SEL2
#define PDIR_SWITCH     P1DIR
#define PREN_SWITCH     P1REN
#define POUT_SWITCH     P1OUT
#define PIE_SWITCH      P1IE
#define PIES_SWITCH     P1IES
#define PIFG_SWITCH     P1IFG
//-------------------------------------------------------------
void config_switch(void);

void LCD_Display(unsigned char chr);
void LCD_PrintString(char *str);
void gui2nib(unsigned char a);
void LCD_Clear();
void LCD_Home();
void LCD_Goto(unsigned char row, unsigned char column);
void LCD_Init();

//------------------------------------------------------------------
void config_switch(void)
{   PSEL_SWITCH &=~ SWITCH;
    PSEL2_SWITCH &=~ SWITCH;
    PDIR_SWITCH &=~ SWITCH;             //set ngo vao
    PREN_SWITCH |= SWITCH;              //CHO PHEP TRO TREO
    POUT_SWITCH |= SWITCH;              //TRO TREO LEN NGUON
    PIE_SWITCH |= SWITCH;               //cho phep ngat
    PIES_SWITCH |= SWITCH;              //ngat canh xuong
    PIFG_SWITCH &=~ SWITCH;             //xoa co ngat
}
void LCD_Init()
{   P1SEL &= ~(PORT);
   // P1SEL2 &= ~(PORT);
    P1DIR |= (PORT);
    P1OUT &=~ (PORT);
    P1REN &=~ PORT;
  //  P1OUT |=E;
    P1DIR |= E;
    P1DIR |= RS;
    P1OUT &= ~RS;
    P1OUT &= ~E;
    _delay_cycles(delay);

     gui2nib(0x01);                             //xoa man hinh
     _delay_cycles(delay*40);
     gui2nib(0x02);                             // dua con tro ve dau dong
     _delay_cycles(delay*40);
     gui2nib(0x06);                             //dich con tro sang phai, khong dich noi dung
     _delay_cycles(delay*40);
     gui2nib(0x28);                             //giao tiep 4bit, hien thi 2 hang, ki tu kieu 5x8
     _delay_cycles(delay*40);
     gui2nib(0x0C);                             // khong hien thi con tro, khong nhap nhay ki tu
     _delay_cycles(delay*40);
}
//--------------------------------------------------------
void gui2nib(unsigned char a)
{   //P1OUT &=~ RS;
    P1OUT &= ~PORT;                             //xoa data
    unsigned char b;
    unsigned char c;
    b=a &(0xB0);
    c=(a &(0x40))>>6;
    P1OUT|= (b|c);
    P1OUT |=E;
    P1OUT &=~E;
    _delay_cycles(delay);

    P1OUT &= ~PORT;                            //xoa data
    b=(a<<4)& 0xB0;
    c=((a<<4)&(0x40))>>6;
    P1OUT|=(b|c);
    P1OUT |=E;
    P1OUT &=~E;
     _delay_cycles(delay);
}
//-------------------------------------------------------------
 //Xoa LCD
 void LCD_Clear()
 {
     P1OUT &=~RS;
     gui2nib(0x01);
     _delay_cycles(delay*40);
 }
 //Dua con tro ve home
 void LCD_Home()
 {
     P1OUT &=~RS;
     gui2nib(0x02);
     _delay_cycles(delay*40);
 }
//-------------------------------------------------------------
void LCD_Goto(unsigned char row, unsigned char column)
{
    P1OUT &=~RS;
    if(row == 2)
       gui2nib(0xC0 + column);           //dau hang 1+ column
    else
       gui2nib(0x80 + column);           //dau hang 2+ column
}
//-----------------------------------------------------------
void LCD_PrintString(char *str)
{
    while(*str)
    {
        LCD_Display(*str);
        str++;
    }
}
//------------------------------------------------
void LCD_Display(unsigned char chr)
{
    P1OUT |=RS;                         //RS=1: che do nhap data
    gui2nib(chr);
}
//---------------------------------------------------
