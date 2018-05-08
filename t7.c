#include<pic.h>
#include<stdio.h>

//#define led RB0;
unsigned char cnt;

void init_timer1();

interrupt void isr_t1()
{
	init_timer1();
//	TMR1IF = 0;
	cnt--;
	if (cnt==0)
	{
		RB0 =~ RB0;
		cnt =  20;
	}
}

void main()
{
	TRISB 	= 0x00;
	PORTB 	= 0x00;
	cnt	= 20;
	init_timer1();
	PEIE 	= 1;11:22 AM 8/7/200711:22 AM 8/7/2007
	GIE	= 1;
	while(1);
}

void init_timer1()
{
	T1CON 	= 0x01;
	TMR1L 	= 0x00;
	TMR1H	= 0x00;
	TMR1IE 	= 1;
	TMR1IF 	= 0;	
}	