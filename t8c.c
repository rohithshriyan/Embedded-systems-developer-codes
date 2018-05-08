#include<stdio.h>
#include<reg51.h>

void delay(unsigned int);
void init_timer0();
void isr0_timer0();
void disp1();
void disp2();
void disp3();
void disp4();

void inc_d();
void l1_dc();
void l2_dc();
void l3_dc();
void l4_dc();
unsigned int ds1,ds2,ds3,ds4;
int scan_no;
void scanner();
void init();
void test_disp();
unsigned int a[20]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xe6,0x00,0xff,0xee,0x3e,0x9c,0x7a,0x9e,0x8e};
 sbit sl1=P2^0;
 sbit sl2=P2^1;
 sbit sl3=P2^2;
 sbit sl4=P2^3;
 
void main()
{
 init();
 EA=1;
 test_disp();
 ds1='0';
 ds2='0';
 ds3='0';
 ds4='0';

 while(1)
 {
  delay(1000);
  inc_d();
  }

}

void init()
{
 scan_no=0;
 init_timer0();
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
 scanner();
}

void test_disp()
{
 ds1='9'+2;
 ds2='9'+2;
 ds3='9'+2;
 ds4='9'+2;
 delay(1000);
 ds1='9'+1;
 ds2='9'+1;
 ds3='9'+1;
 ds4='9'+1;
 delay(1000);
 }

 void disp1()
 {
   
   P0=a[ds1-'0'];
   delay(1);
   }
 void disp2() 
  {
   
   P0=a[ds2-'0'];
   delay(1);
  }
   void disp3()
   {
  
   P0=a[ds3-'0'];
   delay(1);
   }
   void disp4()
   {
  
   P0=a[ds4-'0'];
   delay(1);
}

void inc_d()
{
 ds1++;
 if(ds1>'9')
  {
   l1_dc();
   }
 }
void l1_dc()
{
  ds1='0';
  ds2++;
  if(ds2>'9')
   {
     l2_dc();
	}
  }

void l2_dc()
{
 ds2='0';
 ds3++;
 if(ds3>'9')
  {
    l3_dc();
   }
  }

void l3_dc()
{
 ds3='0';
 ds4++;
 if(ds4>'9')
  {
    l4_dc();
   }
 }
 
 void l4_dc()
 {
  ds1='0';
  ds2='0';
  ds3='0';
  ds4='0';
  }     
 
void scanner()
{

 switch(scan_no)
 {  
case 0:
      sl1=0;
	  sl2=1;
	  sl3=1;
	  sl4=1;
       disp1();
	   scan_no=1;
	   break;

case 1:
       scan_no=2;
	   break;
case 2:
       scan_no=3;
	   break;
case 3:
       
	   P0=0x00;
	   scan_no=4;
	   break;
case 4:
       sl1=1;
	   sl2=0;
	   sl3=1;
	   sl4=1;
	   disp2();
	   scan_no=5;
	   break;
case 5:
       scan_no=6;
	   break;
case 6:scan_no=7;
	   break;
case 7:
       P0=0x00;
	   scan_no=8;
	   break;
case 8: sl1=1;
	   sl2=1;
	   sl3=0;
	   sl4=1;
	   disp3();
	   scan_no=9;
	   break;
case 9:scan_no=10;
       break;
case 10:scan_no=11;
       break;
case 11:P0=0x00;
        scan_no=12;
		break;
case 12:sl1=1;
	   sl2=1;
	   sl3=1;
	   sl4=0;
	   disp4();
	   scan_no=13;
	   break;
case 13:scan_no=14;
       break;
case 14:scan_no=15;
       break;
case 15:P0=0x00;
        scan_no=0;
		break;

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
	   

