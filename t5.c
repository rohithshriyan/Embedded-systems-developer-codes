#include<pic.h>
#include<stdio.h>

#define sl1 RA1
#define sl2 RC0
#define sl3 RC1
#define sl4 RC2

unsigned char ds1,ds2,ds3,ds4;

//look up table
unsigned int luk_up[]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6};

unsigned char cnt;

void delay(unsigned int);
void inc_ds();
void display();

void main()
{
	TRISA = 0x00;
	TRISB = 0x00;
	TRISC = 0x00;
	
	ds1='0';
	ds2='0';
	ds3='0';
	ds4='0';
 	
	while(1)
	{
		cnt=28;
		while(cnt!=0)
		{
			cnt--;
			display();
		}

		inc_ds();	
	}
}

void inc_ds()
{
	ds1++;

	if(ds1=='9')
	{
		ds1='0';
		ds2++;

		if(ds2=='9')
		{
			ds2='0';
			ds3++;
			
			if(ds3=='9')
			{
				ds3='0';
				ds4++;
				
				if(ds4=='9')
				{
					ds1='0';
					ds2='0';
					ds3='0';
					ds4='0';
				}
			}
		}
	}
}		

void display()
{
	sl1=0;
	sl2=1;
	sl3=1;
	sl4=1;

	
	PORTB=luk_up[ds1-'0'];
	delay(3);


	sl1=1;
	sl2=0;
	sl3=1;
	sl4=1;

	PORTB=luk_up[ds2-'0'];
	delay(3);


	sl1=1;
	sl2=1;
	sl3=0;
	sl4=1;

	PORTB=luk_up[ds3-'0'];
	delay(3);


	sl1=1;
	sl2=1;
	sl3=1;
	sl4=0;

	PORTB=luk_up[ds4-'0'];
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
		