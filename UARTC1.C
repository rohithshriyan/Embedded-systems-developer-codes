#include<stdio.h>
#include<reg51.h>
void tx(unsigned char);
void delay(unsigned int);
void uart_clr();
void init_timer1();
void uart_hs();
unsigned char name[]={'N','I','L','E','S','H'};

void main()
{
 init_timer1();

 SCON=0x52;
 uart_clr();
 
 while(1)
 {
  int m;
  uart_hs();
  for(m=0;m<=5;m++)
  {
   tx(name[m]);
   delay(3);
   }
  }
  }
  
  void init_timer1()
  {
   TMOD|=0x20;
   TH1=0xFD;
   TR1=1;
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

void delay(unsigned int del)
{
 unsigned int i,j;
 for(i=0;i<=del;i++)
 {
  for(j=0;j<=120;j++);
  }
  }