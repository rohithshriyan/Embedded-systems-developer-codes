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
void data_mapping(unsigned char);
void enable();
void lcd_display();
void isr_t0();

int scan_no,count;

sbit sl1=P2^0;
sbit sl2=P2^1;
sbit sl3=P2^2;
sbit sl4=P2^3;

 
void inc_d();
void scanner();
void init_timer0();
void init();
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
		{
		lcd_display();
		lcd_delay(1000);
		inc_d();
		}
	}

void init()
{
init_lcd();

scan_no=0;
init_timer0();
}

void init_timer0()
	{
	 TMOD=0x01;
	 TL0=0x66;
	 TH0=0xFC;
	 TR0=1;
	 ET0=1;
	}

void isr_t0()	interrupt 1 using 3
{
 init_timer0();
 scanner();
 }

void scanner()
{
	switch(scan_no)
	{
	case 0:	sl1=0;
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
	case 4:	sl1=1;
			sl2=0;
			sl3=1;
			sl4=1;
			scan_no=5;
			break;
	case 5: scan_no=6;
			break;
	case 6:	scan_no=7;
			break;
	case 7: 
			scan_no=8;
			break;
	case 8:	sl1=1;
			sl2=1;
			sl3=0;
			sl4=1;
			scan_no=9;
			break;
	case 9: scan_no=10;
			break;
	case 10:scan_no=11;
			break;
	case 11:
			scan_no=12;
			break;
	case 12:sl1=1;
			sl2=1;
			sl3=1;
			sl4=0;
			scan_no=13;
			break;
	case 13:	
			scan_no=14;
			break;
	case 14:	
			scan_no=15;
			break;
	case 15:
			scan_no=0;
			break;
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

void lcd_display()
{
cmd_wr(0x80);
lcd_delay(2);
data_wr(ds4);
lcd_delay(2);
data_wr(ds3);
lcd_delay(2);
data_wr(ds2);
lcd_delay(2);
data_wr(ds1);
lcd_delay(2);
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

void lcd_delay(unsigned int del)
{	unsigned int i,j;
	for(i=0;i<del;i++)
	{
		for(j=0;j<120;j++);
	}
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
  
    

