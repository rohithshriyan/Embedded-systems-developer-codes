#include<stdio.h>
#include<reg51.h>
sbit led=P0^0;
void delay(unsigned int);
void init_timer0();
void isr0_timer0();
 int count;
void main()
{
 count=120;
 P0=0x00;
 init_timer0();
 EA=1;
 while(1);
}


void init_timer0() 
 {
  TMOD|=0X01;
  TL0=0x66;
  TH0=0xfc;
  TR0=1;
  ET0=1;
  }


void isr0_timer0() 	interrupt 1 using 3
{ 

 init_timer0();
 count--;
 if(count==0)
 {
  
   
  P0=~P0;
  count=120;
 
 }
}

 