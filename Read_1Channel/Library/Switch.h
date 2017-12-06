////////////////////////////////////////////////////////////////////
// THU VIEN DINH NGHIA CAC HAM XU LY PHIM BAM
// VIET BOI : PHAM VAN THUAN	DTVT07-K55
// Email:	terran991992@gmail.com
// Blog :	http://thuanbk55.blogspot.com/
// .................................................................
// AP DUNG CHO MACH UNG DUNG MSP430
//******************************************************************/

#ifndef SWITCH_H_
#define SWITCH_H_

//Dinh nghia phim mac dinh
#define DDRSWITCH		P2DIR	//Thanh ghi dinh huong ra vao I/O
#define PORTSWITCH		P2OUT	//Thanh ghi du lieu xuat
#define PINSWITCH		P2IN	//Thanh ghi du lieu nhap
#define PRENSWITCH		P2REN	//Thanh ghi tang giam diem tro
#define PSELSWITCH		P2SEL	//Thanh ghi lua chon chuc nang 1
#define PSEL2SWITCH		P2SEL2	//Thanh ghi lua chon chuc nang 2
#define DIRECT_SWITCH	0x0F

#define sbi(REG,BIT) REG |= (1<<BIT) // set BIT trong thanh ghi REG
#define cbi(REG,BIT) REG &= ~(1<<BIT)// clear BIT trong thanh ghi REG

unsigned char press=0;//trang thai phim bam
unsigned char press_quakhu=0;


/******************************************************************************\
*					Prototype (nguyen mau ham)    						       *
\******************************************************************************/
void SWITCH_Init();
/*  Ham quet phim, tra ve 1 so 8 bit sw the hien trang thai cua 8 nut bam, moi nut
	bam tuong ung voi 1 bit cua sw, 1 la dang duoc bam, 0 la khong duoc bam */
void SWITCH_CheckKey();
/*  Ham quet phim, tra ve 1 so 8 bit sw the hien trang thai cua 8 nut bam, 
	ham co tac dung doi cho den khi co mot nut duoc bam 
	0 la chua bam, 1 la dang bam */
void SWITCH_SelectKey();
//Ham quet phim chi nhan tung lan 1 nhung cpu ko chay trong vong while
void SWITCH_Key();
/******************************************************************************\
*					Function (noi dung ham)	                           *
\******************************************************************************/
void SWITCH_Init()
{
	PSELSWITCH &=~DIRECT_SWITCH;	//Chon chuc nang I/O		
	PSEL2SWITCH &=~DIRECT_SWITCH;
	DDRSWITCH&=~DIRECT_SWITCH;		//Chon nhap du lieu
	PRENSWITCH |= DIRECT_SWITCH;	//Cho phep tro keo len
	PORTSWITCH |=DIRECT_SWITCH;		//Tro keo len nguon
}
void SWITCH_CheckKey()
{
	press=0;
	if((PINSWITCH & DIRECT_SWITCH) != DIRECT_SWITCH)	// neu co bat ky nut nao o PORT duoc bam
	{	
		_delay_ms(1);			
		if(PINSWITCH & 0x01)cbi(press,0); else sbi(press,0);
		if(PINSWITCH & 0x02)cbi(press,1); else sbi(press,1);
		if(PINSWITCH & 0x04)cbi(press,2); else sbi(press,2);
		if(PINSWITCH & 0x08)cbi(press,3); else sbi(press,3);
	}
}

void SWITCH_SelectKey()
{
	while(((PINSWITCH & DIRECT_SWITCH) != DIRECT_SWITCH)); 	// Cho cho phim dang giu o PORT duoc nhan
	while((PINSWITCH & DIRECT_SWITCH) == DIRECT_SWITCH);	// Vong lap khi khong co nut nao dc bam
	SWITCH_CheckKey();
}

//Ham quet phim chi nhan tung lan 1 nhung cpu ko chay trong vong while
void SWITCH_Key()
{
	press=0;
	if(PINSWITCH^press_quakhu)//cho cho tat ca nut bam deu nha
	{
		SWITCH_CheckKey();
		if(press==0x00)press_quakhu=0;
		else press_quakhu=PINSWITCH;
	}
}

#endif /* SWITCH_H_ */
