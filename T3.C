#include <LPC214X.H>
#include <stdio.h>


// port1 16-19:select lines

unsigned int luk_up[10]={0x00fc0000,0x00600000,0x00dDA0000,0x00F20000,0x00660000,0x00B60000,0x00BE0000,
0x00E00000,0x00FE0000,0x00F60000};


void delay(unsigned int);
void display(void);

int main()
{
	PINSEL0=0X00000000;
	PINSEL1=0X00000000;

	IO0DIR |= 0x00FF0000;
	//IO1DIR |= 0x000f0000;

	//IO1SET = 0x000f0000;

	while(1)
	{
		
		
			display();
		
	}
		
}



void display()
{
	IO1DIR = 0x00010000;
	//IO1CLR = 0x00010000;
	
	IO0SET = luk_up[0];
	delay(1000);
	IO0CLR=luk_up[0];
	//IO1SET = 0x00010000;

	IO1DIR = 0x00020000;
	//IO1CLR = 0x00020000;
	IO0SET =luk_up[1]; 
	delay(1000);
	IO0CLR=luk_up[1];
	//IO1SET = 0x00020000;

	IO1DIR = 0x00040000;
	//IO1CLR = 0x00040000;
	IO0SET= luk_up[2];
	delay(1000);
	IO0CLR=luk_up[2];

	//IO1SET = 0x00040000;

	IO1DIR = 0x00080000;
	//IO1CLR = 0x00080000;
	IO0SET = luk_up[3];
	delay(1000);
	IO0CLR=luk_up[3];
	//IO1SET = 0x00080000;

}



void delay(unsigned int d)
{
	unsigned int dly1,dly2;

	for(dly1=0;dly1<d;dly1++)
	{
		for(dly2=0;dly2<1200;dly2++);
	}

}









	