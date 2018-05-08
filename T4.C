#include<stdio.h>
#include<pic.h>

void display();
void delay(unsigned int);
void inc_d();
void l1_dc();
void l2_dc();
void l3_dc();
void l4_dc();
unsigned char ds1,ds2,ds3,ds4;
unsigned char a[16]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xe6,0xee,0x3e,0x9c,0x7a,0x9e,0x8e};
#define sl1 RA1
#define sl2 RC0
#define sl3 RC1
#define sl4 RC2
                        
void main()
{
 TRISB=0x00;
 TRISA=0x00;
 TRISC=0X00;
 
 int i;
 
 ds1=0;
 ds2=0;
 ds3=0;
 ds4=0;
while(1)
{
 for(i=0;i<=100;i++)
{
 display();
}
inc_d();
}
}

void display()
{
 sl1=0;
 sl2=1;
 sl3=1;
 sl4=1;
 PORTB=a[ds1];
 delay(1);
 
 sl1=1;
 sl2=0;
 sl3=1;
 sl4=1;
 PORTB=a[ds2];
 delay(1);
 
 sl1=1;
 sl2=1;
 sl3=0;
 sl4=1;
 PORTB=a[ds3];
 delay(1);

 sl1=1;
 sl2=1;
 sl3=1;
 sl4=0;
 PORTB=a[ds4];
 delay(1);
}

void inc_d()
{
 ds1++;
 if(ds1==16)
{
 l1_dc();
}
}

void l1_dc()
{
 ds1=0;
 ds2++;
 if(ds2==16)
{
 l2_dc();
}
}

void l2_dc()
{
 ds2=0;
 ds3++;
 if(ds3==16)
 {
  l3_dc();
 }
}
 
void l3_dc()
{
 ds3=0;
 ds4++;
 if(ds4==16);
 {
  l4_dc();
 }
}
void l4_dc()
{
 ds1=0;
 ds2=0;
 ds3=0;
 ds4=0;
}
  

void delay(unsigned int d)
{
	unsigned int dly1,dly2;

	for(dly1=0;dly1<=d;dly1++)
	{
		for(dly2=0;dly2<120;dly2++);
	}
}			