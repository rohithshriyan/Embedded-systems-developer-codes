#include<pic.h>
#include<stdio.h>

void delay(unsigned int);

void main()
{
 TRISB=0X00;
while(1)
{
PORTB=0x01;

for(int b=0;b<=7;b++)
{
 delay(100);
 PORTB=PORTB<<1; 
}
PORTB=0x80;

for(int b=0;b<=7;b++)
{
 delay(100);
 PORTB=PORTB>>1; 
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


