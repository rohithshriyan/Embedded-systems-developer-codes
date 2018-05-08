#include<LPC214X.h>
#include<stdio.h>

 void delay(unsigned int);
int main()
{
 VPBDIV|=0X00;
 PINSEL0|=0X00000000;  //FOR SELECT PORT0
 IO0DIR=0X00FF0000;  //DEFINE PINS 16 TO 23
 while(1)
 {
  IO0SET=0X00030000;
  delay(500);
  IO0CLR=0XFFFFFFFF;
  delay(500);
  }
 }

 void delay(unsigned int d)
  {
  unsigned int i,j;
  
   for(i=0;i<=d;i++)
   {
    for(j=0;j<=120;j++);
	}
	}
