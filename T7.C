#include<LPC214X.H>
#include<stdio.h>

void init_t0(void);

int main()
{
 VPBDIV=0X00;
 PINSEL0=0X00000000;
 
 IO0DIR	=	0x00ff0000;
 while(1)
 {
  IO0SET=0X00040000;
  init_t0();
  IO0CLR=0X00040000;
  init_t0();
  }
 }

 void init_t0()
 {
  T0CTCR=0X00;
  T0TC=0X00000000;
  T0MR0=0X00A73198;
  T0MCR=0X0003;
  T0TCR=0X01;
  while(T0MR0!=T0TC);

 }
