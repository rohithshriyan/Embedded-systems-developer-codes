#include<pic.h>
#include<stdio.h>

void delay(unsigned int);

void main()
{
TRISB=0x00;
 while(1)
{
 int a;
 for(a=0;a<10;a++)
{
 PORTB=0xF0;
 delay(100);
PORTB=PORTB>>1;
delay(100);
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

