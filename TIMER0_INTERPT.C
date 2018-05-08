#include <LPC214X.H>
#include <stdio.h>

unsigned int val,i;

void init_timer0(void);
void delay(unsigned int);


__irq void timer0_isr()
{
	T0IR	=	0X01;
	init_timer0();
	i--;


	if(i==0)
	{
		IO0CLR	=	0x000f0000;	
		
		i=2;	
	}

	VICVectAddr=0x00;
}

int main()
{
	VPBDIV	=	0X00;
	PINSEL0	=	0X00000000;
	IO0DIR	=	0x00ff0000;
    init_timer0();

	i=2;

//--- interrupt registers---//
	VICIntSelect	=	0x00000000;
	VICIntEnable	=	0x00000010;
	VICVectCntl0	=	0x00000024;
	VICVectAddr0	=	(unsigned long) timer0_isr;

//--------------------------//

	while(1)
	{
		IO0SET	=	0X000f0000;
		delay(100);

	}

}


void init_timer0()
{
	T0CTCR	=	0x00;
	T0TC	=	0X00000000;
//  T0PC	=	0x00000000;
//  T0PR	=	0x000001f4;
	T0MR0	=	0X00003b2f;
	T0MCR	=	0X0007;
	T0TCR	=	0X01;



}

void delay(unsigned int x)
{
	unsigned int y,z;

	for(y=0;y<=x;y++)
		{
			for(z=0;z<=1200;z++);
		}


}
