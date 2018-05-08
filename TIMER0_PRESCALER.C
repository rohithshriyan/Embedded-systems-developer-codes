#include <LPC214X.H>
#include <stdio.h>

unsigned int val;

void init_timer0(void);


int main()
{
	VPBDIV	=	0X00;
	PINSEL0	=	0X00000000;
	IO0DIR	=	0x00ff0000;

	val		=	0x00010000;	

	while(1)
	{
		IO0SET	=	val;
		init_timer0();
		IO0CLR	=	val;

		val = val<<1;

		if(val == 0x01000000)
		{
			val	=	0x00010000;
		}
	}
}


void init_timer0()
{
	T0CTCR	=	0x00;
	T0TC	=	0X00000000;
	T0PC	=	0x00000000;
	T0MR0	=	0X00003b2f;
	T0PR	=	0x000001f4;
	T0MCR	=	0X0004;
	T0TCR	=	0X01;

	while(T0TC != T0MR0);
}


