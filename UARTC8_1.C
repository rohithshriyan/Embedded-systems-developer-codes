#include<stdio.h>
#include<reg51.h>
void tx(unsigned char);
void delay(unsigned int);
void uart_clr();
void init_timer1();
void uart_hs();
void inc_d();
void uart_disp();
void init_scon();
void init_timer0();
void isr0_t0();
void scanner();
void init();
int scan_no;
 sbit sl1=P2^0;
 sbit sl2=P2^1;
 sbit sl3=P2^2;
 sbit sl4=P2^3;
unsigned char ds1,ds2,ds3,ds4;
void main()
{
  init();
 EA=1;
 ds1='0';
 ds2='0';
 ds3='0';
 ds4='0';
 
 while(1)
 {uart_clr();
 uart_disp();
 delay(1000);
  inc_d();
   }
  }
  
 void init()
 {
  scan_no=0;
  init_scon();
  init_timer0();
  init_timer1();
  }

  void init_scon()
  {
   SCON=0x52;
  }
  void init_timer1()
  {
   TMOD|=0x20;
   TH1=0xFD;
   TL1=0xFD;
   TR1=1;
   }
  void init_timer0()
  {
   TMOD|=0x01;
   TL0=0x66;
   TH0=0xfc;
   TR0=1;
   ET0=1;
   }

void isr0_t0()	interrupt 1 using 1
{
 init_timer0();
 scanner();
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
       
	   scan_no=1;
	   break;

case 1:
       scan_no=2;
	   break;
case 2:
       scan_no=3;
	   break;
case 3:
       scan_no=4;
	   break;
case 4:
       sl1=1;
	   sl2=0;
	   sl3=1;
	   sl4=1;
	   scan_no=5;
	   break;
case 5:
       scan_no=6;
	   break;
case 6:scan_no=7;
	   break;
case 7:
       
	   scan_no=8;
	   break;
case 8:sl1=1;
	   sl2=1;
	   sl3=0;
	   sl4=1;
	   
	   scan_no=9;
	   break;
case 9:scan_no=10;
       break;
case 10:scan_no=11;
       break;
case 11:scan_no=12;
		break;
case 12:sl1=1;
	   sl2=1;
	   sl3=1;
	   sl4=0;
	   scan_no=13;
	   break;
case 13:scan_no=14;
       break;
case 14:scan_no=15;
       break;
case 15: scan_no=0;
		break;

}
}

void uart_disp()
{
 uart_hs();
 tx(ds4);
 delay(5);
 tx(ds3);
 delay(5);
 tx(ds2);
 delay(5);
 tx(ds1);
 delay(5);
 }

void uart_hs()
  {
   	tx(0x1b);
	delay(2);
	tx('[');
	delay(2);
	tx('H');
	delay(2);
  }

  void uart_clr() 
  {
    tx(0x1b);
	delay(2);
	tx('[');
	delay(2);
	tx('2');
	delay(2);
	tx('J');
	delay(2);
  } 

 void tx(unsigned char tx_data)
{
	while(TI==0);
	SBUF=tx_data;
	TI=0;
}

 void inc_d()
{
 ds1++;
 if(ds1>'9')
 {
  ds1='0';
  ds2++;
  if(ds2>'9')
 {
 
 ds2='0';
 ds3++;
 if(ds3>'9')
{
 ds3='0';
 ds4++;
 if(ds4>'9')
  {
  ds1='0';
  ds2='0';
  ds3='0';
  ds4='0';
  }
  }
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