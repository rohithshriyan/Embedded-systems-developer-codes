#include<stdio.h>
#include<reg51.h>
void disp();
void inc_d();
void l1_dc();
void l2_dc();
void l3_dc();
void l4_dc();
void delay(unsigned int);
unsigned char ds1,ds2,ds3,ds4;

unsigned int a[16]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xe6,0xee,0x3e,0x9c,0x7a,0x9e,0x8e};
 sbit sl1=P2^0;
 sbit sl2=P2^1;
 sbit sl3=P2^2;
 sbit sl4=P2^3;

void main()
{
  int i;
  int count=100;
  ds1=ds2=ds3=ds4=0;
  while(1)
  {
   	for(i=0;i<=count;i++)
 	 {
	    disp();
	 }
  	inc_d();
   }
 }
  
 void disp()
 {
   sl1=0;
   sl2=1;
   sl3=1;
   sl4=1;
   P0=a[ds1];
   delay(1);

   sl1=1;
   sl2=0;
   sl3=1;
   sl4=1;
   P0=a[ds2];
   delay(1);

   sl1=1;
   sl2=1;
   sl3=0;
   sl4=1;
   P0=a[ds3];
   delay(1);

   sl1=1;
   sl2=1;
   sl3=1;
   sl4=0;
   P0=a[ds4];
   delay(1);
}

void inc_d()
{
 ds1++;
 if(ds1==0x10)
  {
   l1_dc();
   }
 }
void l1_dc()
{
  ds1=0x00;
  ds2++;
  if(ds2==0x10)
   {
     l2_dc();
	}
  }

void l2_dc()
{
 ds2=0x00;
 ds3++;
 if(ds3==0x10)
  {
    l3_dc();
   }
  }

void l3_dc()
{
 ds3=0x00;
 ds4++;
 if(ds4==0x10)
  {
    l4_dc();
   }
 }
 
 void l4_dc()
 {
  ds1=0x00;
  ds2=0x00;
  ds3=0x00;
  ds4=0x00;
  }     
  
  
  void delay(unsigned int del)
   {
    unsigned int i,j;
	for(i=0;i<=del;i++)
	{
	 for(j=0;j<=120;j++);
	 
	 }
	 }
