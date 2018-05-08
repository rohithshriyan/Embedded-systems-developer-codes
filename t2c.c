#include<stdio.h>
#include<reg51.h>
void delay(unsigned int);
unsigned char ds1,ds2,ds3, ds4;
 sbit sl1=P2^0;
 sbit sl2=P2^1;
 sbit sl3=P2^2;
 sbit sl4=P2^3;
void main()
{
  
 while(1)
 {
   sl1=0;
   sl2=1;
   sl3=1;
   sl4=1;
   ds1=0x01;
   P0=ds1;
   delay(1);

    sl1=1;
   sl2=0;
   sl3=1;
   sl4=1;
   ds1=0xda;
   P0=ds1;
   delay(1);

   sl1=1;
   sl2=1;
   sl3=0;
   sl4=1;
   ds1=0x01;
   P0=ds1;
   delay(1);

    sl1=1;
   sl2=1;
   sl3=1;
   sl4=0;
   ds1=0xda;
   P0=ds1;
   delay(1);
  }
   }
  
   void delay(unsigned int del)
   {
    unsigned int i,j;
	for(i=0;i<=del;i++)
	{
	 for(j=0;j<=120;j++);
	 
	 }
	 }
