#include <pic.h>
#include <stdio.h>


void delay(unsigned int);


void main()
{
	TRISB = 0x00;
	
	while(1)
	{
		PORTB = 0x55;
		delay(100);
		PORTB = 0xaa;
		delay(100);
	}
}

void delay(unsigned int d)
{
	unsigned int dly1,dly2;

	for(dly1=0;dly1<d;dly1++)
	{
		for(dly2=0;dly2<120;dly2++);
	}
}