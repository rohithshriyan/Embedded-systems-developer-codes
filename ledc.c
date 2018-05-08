#include<stdio.h>
#include<reg51.h>
void delay(unsigned int);
void main()
{
 while(1)
 {
   int a;
   P0=0x80;
   for(a=0;a<=8;a++)
   {
     delay(1000);
    P0=P0>>1;
	  delay(1000);
   }
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
