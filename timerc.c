#include<stdio.h>
#include<reg51.h>

void init_timer0();
void delay(unsigned int);

void main()
{
 P0=0x00;
 init_timer0();
 delay(1000);
 P0=0X0f;
 init_timer0();
 delay(1000);

 }

 void init_timer0()
 {
  TMOD=0x10;
  TH0=0xfc;
  TL0=0x66;
  TR0=1;
  while(TF0==0);
  }
   
  void delay(unsigned int del)
  {
   unsigned int i,j;
   for(i=0;i<=del;i++)
   {
    for(j=0;j<=120;j++);
	}
	}
