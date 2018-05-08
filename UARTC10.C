//stopwatch using timers

#include<stdio.h>
#include<reg51.h>


void delay(unsigned int);
void tx(unsigned char);
void init_timer1();
void uart_hs();
void uart_clr();
void uart_display();


sbit buzzer_pin=P1^5;
sbit sl1=P2^0;
sbit sl2=P2^1;
sbit sl3=P2^2;
sbit sl4=P2^3;
sbit krl1=P2^4;
sbit krl2=P2^5;
sbit krl3=P2^6;
sbit krl4=P2^7;
unsigned int counts;
bit key_ready,nkp,tb,start_buzzer,start_sw,sl1_over;
unsigned char dcount,krcount,scan_no,key_code,ds1,ds2,ds3,ds4;
unsigned char ascii_tab[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void inc_d();
void k();
void init();
void init_display();
void init_keypad();
void init_timer0();
void scanner();
void buzzer();
void key_release();
void init_delay_1sec();
void delay_1sec();
void get_key();
void keyprocess();
void disp_sw();

void isr_t0() interrupt 1 using 1
{
init_timer0();
delay_1sec();
buzzer();
scanner();
	if(sl1_over==1)
	{
	inc_d();
	sl1_over=0;
	}
}

//A-start,B-pause,C-reset
void main()
{
	init();
	EA=1;
	uart_clr();
	disp_sw();
		while(1)
		{
		get_key();
		keyprocess();
		}
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
	        tb=krl4                                                                                                                        ;
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


void init()
{
init_timer1();
SCON=0x52;
init_timer0();
init_display();
init_keypad();
init_delay_1sec();
}

void disp_sw()
{
ds1='E';
ds2='M';
ds3='I';
ds4='T';
}

void init_display()
{
ds1='0';
ds2='0';
ds3='0';
ds4='0';
}

void init_keypad()
{
krl1=1;
krl2=1;
krl3=1;
krl4=1;
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
TH0=0xfc;
TR0=1;
ET0=1;
}

void init_delay_1sec()
{
counts=1000;//to increase the stopwatch speed, decrease the cnts count
sl1_over=1;
}

void delay_1sec()
{
	if(sl1_over==0)
	{
	counts--;
		if(counts==0)
		{
		 counts=1000;
		 sl1_over=1;
		}
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
}


void inc_d()
{
if(start_sw==1)
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
}

void get_key()
{
	while(key_ready==0)
	{
	uart_display();
	}
	key_code=ascii_tab[key_code];
}

void keyprocess()
{
switch(key_code)
	{
	case 'A':start_sw=1;
			 break;
	case 'B':start_sw=0;
			 break;
	case 'C':start_sw=0;
	         ds1='0';
			 ds2='0';
			 ds3='0';
			 ds4='0';
			 break;
	}
	key_release();
}

//LCD FUNCTIONS

void uart_display()
{
uart_hs();

tx(ds4);
delay(2);
tx(ds3);
delay(2);
tx(ds2);
delay(2);
tx(ds1);
delay(2);
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
{	unsigned int i,j;
	for(i=0;i<del;i++)
	{
		for(j=0;j<120;j++);
	}
}




