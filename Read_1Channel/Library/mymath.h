////////////////////////////////////////////////////////////////////
// THU VIEN DINH NGHIA CAC HAM TINH TOAN
// VIET BOI : PHAM VAN THUAN	DTVT07-K55
// Email:	terran991992@gmail.com
// Blog :	http://thuanbk55.blogspot.com/
// .................................................................		
// AP DUNG CHO VDK noi chung
//******************************************************************/

#ifndef MYMATH_H_
#define MYMATH_H_


void _itoa(int n, char str[], int he)
{
	int i=0,j=0;
	unsigned char dau=0;
	char ch[]="0123456789ABCDEF";
	if(n==0)str[0]=ch[0];
	if(n<0)
	{
		dau=1;
		n*=-1;
	}

	while(n)
	{
		str[i]=ch[n%he];
		n /= he;
		i++;
	}
	if(dau==1){str[i]='-';i++;}
	for(j=0;j<i/2;j++)
	str[j] ^= str[i-j-1] ^= str[j] ^= str[i-j-1];
	str[i]=0;
}

void _itoa_unsigned(unsigned int n, char str[], int he)
{
	unsigned int i=0,j=0;
	char ch[]="0123456789ABCDEF";
	if(n==0)str[0]=ch[0];

	while(n)
	{
		str[i]=ch[n%he];
		n /= he;
		i++;
	}
	for(j=0;j<i/2;j++)
	str[j] ^= str[i-j-1] ^= str[j] ^= str[i-j-1];
	str[i]=0;
}

double myabs(double x)
{
	return ((x>=0)?x:(-x));
}

//	cach tinh can 2 cua a sai so e:  x_(n+1) = (x_n + a / x_n) / 2
float mysqrt(float a)
{
	float xo, xn=1, e= 0.000001;
	do
	{
	   xo=xn;
	   xn=(a/xo+xo)/2.0;
	}
	while (myabs(xn-xo)>e);
	return xn;
}

//Ham sqr
long mysqr(long a,long b)	//a^b
{
	long temp=1,b1=0;
	b1=b;
	for(b1;b1>0;b1--)temp*=a;
	return temp;
}

#endif /* MYMATH_H_ */
