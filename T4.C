#include<LPC214X.H>
#include<stdio.h>

void delay(int delay);
void display(void);
void inc_d(void);
int ds1,ds2,ds3,ds4;
int i,k;
int disp_luk[17]={0x00fc0000,0x00600000,0x00da0000,0x00f20000,0x00660000,0x00b60000,0x00be0000,
             0x00e00000,0x00fe0000,0x00e60000,0x00ee0000,0x003e0000,0x009c0000,0x007a0000,
			 0x009e0000,0x008e0000};

int main()
{
 ds1=0;
 ds2=0;
 ds3=0;
 ds4=0;
 VPBDIV=0X00;
 PINSEL0=0X00000000;
 PINSEL1=0X00000000;
 IO0DIR=0X00FF0000;

 while(1)
 {
  for(i=0;i<=1000;i++)
  {
   for(k=1;k<=1000;k++)
   {
    display();
   }
   inc_d();
  }
 }
 }

 void display()
 {
  IO1DIR=0X00010000;
  IO0SET=disp_luk[ds1];
  delay(20);
  IO0CLR=disp_luk[ds1];

  IO1DIR=0X00020000;
  IO0SET=disp_luk[ds2];
  delay(20);
  IO0CLR=disp_luk[ds2];

  IO1DIR=0X00040000;
  IO0SET=disp_luk[ds3];
  delay(20);
  IO0CLR=disp_luk[ds3];

  IO1DIR=0X00080000;
  IO0SET=disp_luk[ds4];
  delay(20);
  IO0CLR=disp_luk[ds4];
 }

 void inc_d()
 {
  ds1++;
  if(ds1>15)
  {
   ds1=0;
   ds2++;
   if(ds2>15)
   {
    ds1=0;
	ds2=0;
	ds3++;
	if(ds3>15)
	{
	 ds1=0;
	 ds2=0;
	 ds3=0;
	 ds4++;
	 if(ds4>15)
	 {
	  ds1=0;
	  ds2=0;
	  ds3=0;
	  ds4=0;
	  }
	}
   }
  }
 }


void delay(int del)
{
 unsigned int t1,t2;
 for(t1=0;t1<=del;t1++)
 {
  for(t2=0;t2<=1200;t2++);
  }
}
