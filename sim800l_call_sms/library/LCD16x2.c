/*
 * LCD_16x2.c
 *
 *  Created on: 28-09-2017
 *      Author: KILLER
 */

#include <msp430.h>
#include "LCD16x2.h"


unsigned char dao_data(unsigned char data_in)
{
	unsigned char data_out=0;
	switch (data_in)
	{
	case 0x00:
	{
		data_out = 0x00;
		break;
	}
	case 0x10:
	{
		data_out = 0x80;
		break;
	}
	case 0x20:
	{
		data_out = 0x40;
		break;
	}
	case 0x30:
	{
		data_out = 0xC0;
		break;
	}
	case 0x40:
	{
		data_out = 0x20;
		break;
	}
	case 0x50:
	{
		data_out = 0xA0;
		break;
	}
	case 0x60:
	{
		data_out = 0x60;
		break;
	}
	case 0x70:
	{
		data_out = 0xE0;
		break;
	}
	case 0x80:
	{
		data_out = 0x10;
		break;
	}
	case 0x90:
	{
		data_out = 0x90;
		break;
	}
	case 0xA0:
	{
		data_out = 0x50;
		break;
	}
	case 0xB0:
	{
		data_out = 0xD0;
		break;
	}
	case 0xC0:
	{
		data_out = 0x30;
		break;
	}
	case 0xD0:
	{
		data_out = 0xB0;
		break;
	}
	case 0xE0:
	{
		data_out = 0x70;
		break;
	}
	case 0xF0:
	{
		data_out = 0xF0;
		break;
	}

	}
	return (data_out);
}

//Khoi tao lcd
void config_LCD()					//Cac lenh Init co delay dai hon binh thuong de dam bao chac chan
{
	//Khoi tao chuc nang I/O
	PSELLCD &=~(0xF0>>SHIFT_DATA);		//Chon chuc nang I/O
	//PSEL2LCD &=~(0xF0>>SHIFT_DATA);
	DDRLCD|=0xF0>>SHIFT_DATA;			//Chon xuat du lieu cho 4 chan data
	PRENLCD &=~(0xF0>>SHIFT_DATA);		//Khong co dien tro noi keo len
	PORTLCD &=~(0xF0>>SHIFT_DATA);		//Dau ra muc thap
	DDR_E |=E;
	DDR_RS |=RS;
	PORT_RS &=~RS;
	PORT_E &=~E;
	_delay_cycles(lcd_delay*40);				  //delay 1.64mS
	LCD_Init_write(0x20);					//4 bit mode					   //delay 40uS
	LCD_Command(0x28);
	_delay_cycles(lcd_delay);
	LCD_Command(0x0C);					  // Bat hien thi,tat con tro					  //delay 40uS
	///////////////////////////////////////////
	_delay_cycles(lcd_delay);
	LCD_Command(6);						//hien thi tang vao khong shift					   	//delay 40uS
	///////////////////////////////////////////
	_delay_cycles(lcd_delay);
	LCD_Command(1);						//Xoa man hinh hien thi
	///////////////////////////////////////////
	_delay_cycles(lcd_delay*40);				   //delay 1.64mS
	LCD_Command(2);						  //Tro ve dau dong
	_delay_cycles(lcd_delay*40);				  //delay 1.64mS
}

//Ghi du lieu 8 bit len lcd ban dau
void LCD_Init_write(unsigned char b)		//Cac lenh Init co delay dai hon binh thuong de dam bao chac chan
{
	PORTLCD&=~(0xF0>>SHIFT_DATA);
	PORT_RS &=~RS;
	_delay_cycles(lcd_delay*40);
	b&=0xF0;
	b = dao_data(b);
	PORTLCD|=b>>SHIFT_DATA;
	PORT_E |=E;
	_delay_cycles(lcd_delay);
	PORT_E &=~E;
	_delay_cycles(lcd_delay*40);
}



//Ham goi lenh vao LCD
void LCD_Command(unsigned char chr)
{
	unsigned char HNib,LNib,temp_data;
	temp_data=(PORTLCD&~(0xF0>>SHIFT_DATA));
	HNib=chr&0xF0;
	HNib = dao_data(HNib);
	LNib=(chr<<4)&0xF0;
	LNib = dao_data(LNib);

	PORTLCD=((HNib>>SHIFT_DATA)|temp_data);
	PORTLCD=((HNib>>SHIFT_DATA)|temp_data);
	PORT_E |=E;
	PORT_E &=~E ;
	_delay_cycles(lcd_delay);

	PORTLCD=((LNib>>SHIFT_DATA)|temp_data);
	PORTLCD=((LNib>>SHIFT_DATA)|temp_data);
	PORT_E |=E;
	PORT_E &=~E;
	_delay_cycles(lcd_delay);
}


//Xoa LCD
void LCD_Clear()
{
	PORT_RS &=~RS;
	LCD_Command(0x01);
	_delay_cycles(lcd_delay*40);
}

//Dua con tro ve home
void LCD_Home()
{
	PORT_RS &=~RS;
	LCD_Command(0x02);
	_delay_cycles(lcd_delay*40);
}


//Hien thi ki tu
void LCD_Display(unsigned char chr)
{
	PORT_RS |=RS;
	LCD_Command(chr);
}


/* Di chuyen con tro toi vi tri hang row, cot column */
void LCD_Goto(unsigned char row, unsigned char column)
{
	PORT_RS &=~RS;
	if(row == 2)
		LCD_Command(0xC0 + column);
	else
		LCD_Command(0x80 + column);
}



/* Dich chuyen con tro sang trai(direct=0) hoac sang phai(direct=1) "step" vi tri */
void LCD_CursorShift(unsigned char direct, unsigned char step)
{
	unsigned char i;
	PORT_RS &=~RS;
	if (direct == 0)
		for(i=0;i<step;i++)
			LCD_Command(0x10);
	else
		for(i=0;i<step;i++)
			LCD_Command(0x14);
}


/* In ra man hinh xau ki tu str[] */
void LCD_PrintString(char *str)
{
	while(*str)
	{
		LCD_Display(*str);
		str++;
	}
}


/* In ra man hinh so nguyen n voi so cho hien thi bang length(chua ke vi tri cua dau) */
void LCD_PrintDecimal(long n, unsigned char length)
{
	unsigned char du,luu=length;
	// de trong 1 ki tu o dau cho hien thi dau
	if(n>=0)LCD_Display(' ');		//In so duong
	else
	{
		LCD_Display('-');			//In so am
		n*=-1;
	}

	length--;
	LCD_CursorShift(1,length-1);	// dich con tro sang phai length-1 vi tri
	PORT_RS &=~RS;
	_delay_cycles(lcd_delay);

	LCD_DEC_CUR_SHIFT_OFF();		// chuyen sang che do in lui
	// Bat dau in lan luot cac chu so tu hang don vi
	while(length)
	{
		du = n % 10;
		n = n / 10;
		LCD_Display(0x30 + du);
		length--;
	}
	LCD_CursorShift(1,luu);		// dua con tro sang phai length+1 vi tri de in tiep
	PORT_RS &=~RS;
	_delay_cycles(lcd_delay);

	LCD_INC_CUR_SHIFT_OFF();		// chuyen lai ve che do in xuoi

}

void LCD_PrintUnDecimal(long n, unsigned char length)
{
	unsigned char du,luu=length;
	LCD_CursorShift(1,length-1);	// dich con tro sang phai length-1 vi tri
	PORT_RS &=~RS;
	_delay_cycles(lcd_delay);
	LCD_DEC_CUR_SHIFT_OFF();		// chuyen sang che do in lui
	// Bat dau in lan luot cac chu so tu hang don vi
	while(length)
	{
		du = n % 10;
		n = n / 10;
		LCD_Display(0x30 + du);
		length--;
	}
	LCD_CursorShift(1,luu+1);		// dua con tro sang phai length+1 vi tri de in tiep
	PORT_RS &=~RS;
	_delay_cycles(lcd_delay);
	LCD_INC_CUR_SHIFT_OFF();		// chuyen lai ve che do in xuoi


}

/* In ra man hinh so thuc x voi so cho hien thi = length, so chu so sau dau phay la coma */
void LCD_PrintFloat(float x, unsigned char length, unsigned char coma)
{
	// de trong 1 ki tu o dau cho hien thi dau
	if(x>=0)LCD_Display(' ');
	else
	{
		LCD_Display('-');			//In so am
		x*=-1;
	}
	unsigned long n;
	unsigned char store,temp;
	store = length;						// Luu lai do dai so thuc.
	length--;								// Giam di 1 cho dau "."
	for(temp=0;temp<coma;temp++)
		x = x*10;

	n = x;									// Chuyan thanh so nguyen.
	if((x-n)>=0.5)n++;

	LCD_CursorShift(1,length);				// Dich chuyen con tro sang phai
	PORT_RS &=~RS;
	_delay_cycles(lcd_delay);
	LCD_DEC_CUR_SHIFT_OFF();				// Chuyen sang che do in nguoc.

	while(coma)								// In ra phan truoc dau phay
	{
		temp = n % 10;
		n = n / 10;
		LCD_Display(0x30 + temp);
		coma--;
		length--;
	}

	LCD_Display('.');							// In ra dau "."

		while(length)							// In ra phan thap phan
		{
			temp = n % 10;
			n = n / 10;
			//if(temp!=n)
			LCD_Display(0x30 + temp);
			length--;
		}
	PORT_RS &=~RS;
	_delay_cycles(lcd_delay);
	LCD_INC_CUR_SHIFT_OFF();				// Chuyen lai che do in thuan.
	LCD_CursorShift(1,store+1);					// Nhay den vi tri tiep theo.
}

void config_switch_interup(void)
{
	////CONFIG SWITCH INTERUP
	PSEL_SWITCH &=~ SWITCH;
	PSEL2_SWITCH &=~ SWITCH;
	PDIR_SWITCH &=~ SWITCH;				//set ngo vao
	PREN_SWITCH |= SWITCH; 				//CHO PHEP TRO TREO
	POUT_SWITCH |= SWITCH; 				//TRO TREO LEN NGUON
	PIE_SWITCH |= SWITCH;					//cho phep ngat
	PIES_SWITCH |= SWITCH;				//ngat canh xuong
	PIFG_SWITCH &=~ SWITCH;        		//xoa co ngat'
}

void config_LED(void)
{
	LED_DIR |= LED;
	LED_OUT |= LED;
	__delay_cycles(500000);
	LED_OUT &=~ LED;
	__delay_cycles(500000);
	LED_OUT &=~ LED;
}
