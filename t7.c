#include<stdio.h>
#include<pic.h>

#define blink RB4
#define Dblink RB2

void delay(unsigned int);
void init_timer1();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    );

unsigned char count=20;


void main()
{
 TRISB=0x00;
 PORTB=0x00;
 
 init_timer1();
 PEIE=1;
 GIE=1;
 while(1);
}

void init_timer1()
{

 T1CON=0x01;
 TMR1IE=1;
 TMR1IF=0;
 TMR1H=0x65;
 TMR1L=0x22;
}
 
interrupt void isr_timer1()
{
 init_timer1();
 count--;
 
if(count==0)
{
  blink=~blink;
  count=20;

if(count==20)
{
 Dblink=~Dblink; 
 count=20;
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

 