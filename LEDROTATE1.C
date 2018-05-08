#include<LPC214X.h>
#include<stdio.h>
 unsigned val,val1,cnt;
 void delay(unsigned int);
int main()
{
 VPBDIV|=0X00;
 PINSEL0|=0X00000000;  //FOR SELECT PORT0
 IO0DIR=0X00FF0000;  //DEFINE PINS 16 TO 23

 val=0x00010000;

 while(1)
 {
  val1=val;
  for(cnt=1;cnt<=8;cnt++)
  {
   IO0SET=val1;
   delay(500);
   IO0CLR=val1;
   delay(500);
   val1=val1<<1;
   }
 for(cnt=1;cnt<8;cnt++)
 {
  IO0SET=val1;
  delay(500);
  IO0CLR=val1;
  delay(500);
  val1=val1>>1;
  }
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
