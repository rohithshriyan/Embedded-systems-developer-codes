#include<stdio.h>
#include<reg51.h>

sbit vled=P0^0;
sbit rs=P0^1;
sbit rw=P0^2;
sbit e=P0^3;

void cmd_wr(unsigned char);
void data_wr(unsigned char);
void init_lcd();
void lcd_delay(unsigned int);
void enable();
void data_mapping(unsigned char);
unsigned char name[]={'N','I','L','E','S','H'};

void main()
{ int i;
 init_lcd();
lcd_delay(3);
while(1)
{
cmd_wr(0xC0);//second line first
lcd_delay(2);
 	for(i=0;i<=5;i++)
 	{
 	data_wr(name[i]);
	lcd_delay(3);
	}
}
}

void init_lcd()
{
lcd_delay(6);
cmd_wr(0x03);
lcd_delay(2);

cmd_wr(0x03);
lcd_delay(2);

cmd_wr(0x03);
lcd_delay(2);

cmd_wr(0x020);
lcd_delay(2);

cmd_wr(0x28);
lcd_delay(2);

cmd_wr(0x06); 
lcd_delay(2);

cmd_wr(0x01);
lcd_delay(2);
vled=0;
}

void cmd_wr(unsigned char var_data)
{
rs=0;
rw=0;
data_mapping(var_data);
enable();
var_data=var_data<<4;
data_mapping(var_data);
enable();
}

void data_wr(unsigned char var_data)
{
rs=1;
rw=0;
data_mapping(var_data);
enable();
var_data=var_data<<4;
data_mapping(var_data);
enable();
}

void data_mapping(unsigned char var_data1)
{
P0=( (var_data1&0xF0) | (P0&0x0F) );
}


void enable()
{
e=1;
;
;
;
;
;
e=0;
}

void lcd_delay(unsigned int x)
{	unsigned int i,j;
	for(i=0;i<x;i++)
	{
		for(j=0;j<120;j++);
	}
}

