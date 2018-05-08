#ifndef lcd_INCLUDED
#define lcd_INCLUDED

unsigned char temp;


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
void delay(unsigned int);

void init_lcd()
{
lcd_delay(6);
cmd_wr(0x03);
lcd_delay(2);

cmd_wr(0x03);
lcd_delay(2);

cmd_wr(0x03);
lcd_delay(2);

cmd_wr(0x20);
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
_nop_();
_nop_();
_nop_();
_nop_();
_nop_();

e=0;
}

void lcd_delay(unsigned int del)
{	unsigned int i,j;
	for(i=0;i<del;i++)
	{
		for(j=0;j<120;j++);
	}
}

void delay(unsigned int x)
{	unsigned int w,z;
	for(w=0;w<x;w++)
	{
		for(z=0;z<120;z++);
	}
}
#endif
