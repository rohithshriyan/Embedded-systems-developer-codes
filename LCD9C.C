#include<stdio.h>
#include<reg51.h>

sbit vled=P0^0;
sbit rs=P0^1;
sbit rw=P0^2;
sbit e=P0^3;
sbit buzzer_pin=P1^5;
void cmd_wr(unsigned char);
void data_wr(unsigned char);
void init_lcd();
void init_keypad();
void k();
void key_release();
void lcd_delay(unsigned int);
void data_mapping(unsigned char);
void enable();
void lcd_display();
void isr_t0();

unsigned char scan_no,count,dcount,krcount;
unsigned char key_code;
sbit sl1=P2^0;
sbit sl2=P2^1;
sbit sl3=P2^2;
sbit sl4=P2^3;


sbit krl1=P2^4;
sbit krl2=P2^5;
sbit krl3=P2^6;
sbit krl4=P2^7; 
void inc_d();
void scanner();
void buzzer();
void init_timer0();
void init();
unsigned char ds1;

unsigned char ascii_tab[18]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
bit  nkp,start_buzzer,key_ready,tb,start_sw;

void main()
{
 init();
 EA=1;
 ds1='0';
 while(1)
 {
  
  while(key_ready==0);
  {
   cmd_wr(0x80);
   lcd_delay(2);
   ds1=ascii_tab[key_code];
   data_wr(ds1);
   lcd_delay(2);
   key_release();
   }
   }
   }

void init()
{
 init_lcd();
 
 init_keypad();
 init_timer0();
}

void init_keypad()
{
 krl1=1;
 krl2=2;
 krl3=3;
 krl4=4;
 scan_no=0;
 dcount=33;
 krcount=32;
 key_ready=0;
 nkp=0;
 start_buzzer=0;
 }

void init_timer0()
	{
	 TMOD|=0x01;
	 TL0=0x66;
	 TH0=0xFC;
	 TR0=1;
	 ET0=1;
	}

void isr0_t0() interrupt 1 using 3
{
 init_timer0();
 buzzer();
 scanner();
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

void scanner()
{
	switch(scan_no)
	{
	case 0:	sl1=0;
			sl2=1;
			sl3=1;
			sl4=1;
			tb=krl1;
			k();
			scan_no=1;
			break;
	case 1:	tb=krl2;
	        k();
			scan_no=2;
			break;
	case 2:	tb=krl3;
	        k();
			scan_no=3;
			break;
	case 3: 
	        tb=krl4;
	        k();
			scan_no=4;
			break;
	case 4:	sl1=1;
			sl2=0;
			sl3=1;
			sl4=1;
			tb=krl1;
			k();
			scan_no=5;
			break;
	case 5: tb=krl2;
	        k();
	        scan_no=6;
			break;
	case 6:	tb=krl3;
	        k();
	        scan_no=7;
			break;
	case 7: 
	        tb=krl4;
	        k();
			scan_no=8;
			break;
	case 8:	sl1=1;
			sl2=1;
			sl3=0;
			sl4=1;
			tb=krl1;
			k();
			scan_no=9;
			break;
	case 9: tb=krl2;
	        k();
	        scan_no=10;
			break;
	case 10:tb=krl3;
	        k();
	        scan_no=11;
			break;
	case 11:
	        tb=krl4;
	        k();
			scan_no=12;
			break;
	case 12:sl1=1;
			sl2=1;
			sl3=1;
			sl4=0;
			tb=krl1;
			k();
			scan_no=13;
			break;
	case 13:tb=krl2;
	        k();	
			scan_no=14;
			break;
	case 14:tb=krl3;
	        k();	
			scan_no=15;
			break;
	case 15:
	        tb=krl4;
	        k();
			scan_no=0;
			break;
		}

}


void k()
{
 if(key_ready==0)
  {
   if(dcount==33)
   {
    if(tb==0)
	{
	 dcount--;
	 key_code=scan_no;
	 goto out_k;
	 }
	 else
	 {
	  goto out_k;
	  }
	  }
	  else
	 {
	  dcount--;
	  if(dcount==0)
	  {
	   if(tb==0)
	   {
	    dcount=33;
		 key_ready=1;
		 start_buzzer=1;
		 goto out_k;
	   }
		 else
		 {
		 dcount=33;
		 goto out_k;
		 }
		}
		else
      {
	   goto out_k;
	   }
	 }
 }
	else
	{
	 if(tb==0)
	 {
	  krcount=32;
	  goto out_k;
	  }
	 else
	 {
	 krcount--;
	 if(krcount==0)
	 {
	  nkp=1;
	  start_buzzer=0;
	  krcount=32;
	  goto out_k;
	  }
	  else
	  {
	   goto out_k;
	   }
 }
 
}
out_k:;
}

void key_release()
 {
  while(nkp==0);
  key_ready=0;
  nkp=0;
  }
 
 void buzzer()
 {
  if(start_buzzer==1)
  {
   buzzer_pin=~buzzer_pin;
   }
  else
  {
   goto out_b; 
  }
  out_b:;       
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




