#include<reg51.h>
#include<math.h>
#include<stdio.h>

unsigned char rx();
void tx(unsigned char);
unsigned char temp;
void init_uart();
void uart_hs();
void uart_clr();
void init_timer0();


void delay(unsigned int);

void main()
{
 
 unsigned char r_data;
 init_uart();
 uart_clr();
 uart_hs();

 printf("welcome to uart");
 while(1)
 {
  
   
 
  r_data=rx();
  tx(r_data);
  uart_clr();
  }
  }

  unsigned char rx()
  {
   while(rx==0);
   temp=SBUF;
   RI=0;
   return(temp);
   }

void tx(unsigned char tx_data)
{
 while(TI==0);
 SBUF=tx_data;
 TI=0;
 }

void init_uart()
{
 init_timer0();
 
 SCON=0x52;

 
 }

 void init_timer0()
 {
  TMOD|=0x20;
  TH1=0xF0;
  TR1=1;
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

 void uart_hs()
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

 void delay(unsigned int del)
 {
  unsigned int i,j;
  for(i=0;i<=del;i++)
  {
   for(j=0;j<=120;j++);
   }
   }

 
 
