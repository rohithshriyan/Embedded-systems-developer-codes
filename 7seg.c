#include <pic.h>
#include <stdio.h>


#define sl1 RA1
#define sl2 RC0
#define sl3 RC1
#define sl4 RC2


unsigned char ds1,ds2,ds3,ds4,cnt;

unsigned char ascii[]={0xfc,0x60,0xda,0xf2,0x66,
					   0xb6,0xbe,0xe0,0xfe,0xf6};


void delay(unsigned int);
void display();


void main()
{
	TRISA = 0x00;
	TRISB = 0x00;
	TRISC = 0x00;

	while(1)
	{
		cnt=28;
		ds1=0;
		ds2=1;
		ds3=2;
		ds4=3;
		
		while(cnt>0)
		{
		display();
		cnt--;
		}

	}
}

void display()
{
	sl1=0;
	sl2=1;
	sl3=1;
	sl4=1;

	PORTB = ascii[ds1];
	delay(3);

	sl1=1;
	sl2=0;
	sl3=1;
	sl4=1;

	PORTB = ascii[ds2];
	delay(3);

	sl1=1;
	sl2=1;
	sl3=0;
	sl4=1;

	PORTB = ascii[ds3];
	delay(3);

	sl1=1;
	sl2=1;
	sl3=1;
	sl4=0;

	PORTB = ascii[ds4];
	delay(3);
}

void delay(unsigned int d)
{
	unsigned int dly1,dly2;

	for(dly1=0;dly1<d;dly1++)
	{
		for(dly2=0;dly2<120;dly2++);
	}
}

