#include<stdio.h>
#include<reg51.h>
void tx(unsigned char);
void delay(unsigned int);
void uart_clr();
void init_timer1();
void uart_hs();


void init_scon();
void init_timer0();
void isr0_t0();
void scanner();
void init();
void buzzer();
void init_keypad();
void k();
void key_release();

int scan_no,krcount,dcount,key_code;

 sbit sl1=P2^0;
 sbit sl2=P2^1;
 sbit sl3=P2^2;
 sbit sl4=P2^3;

 sbit krl1=P2^4;
 sbit krl2=P2^5;
 sbit krl3=P2^6;
 sbit krl4=P2^7;
 sbit buzzer_pin=P1^5;
 bit key_ready,nkp,tb,start_buzzer,start_sw,sl1_over,nkp;
unsigned char ds1,ds2,ds3,ds4;
unsigned char a[]={0xfc,0x60,0xda,0xf2,0x66,
0xb6,0xbe,0xe0,0xfe,0x66,
0x00,0xff,0xff,0xff,0xff,0xff,0xff,
0xee,0x3e,0x9c,0x7a,0x9e,0x8e};
unsigned char ascii_tab[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
void main()
{
  init();
 EA=1;
 ds1='0'; 
 uart_clr();
 while(1)	            
 {
 while(key_ready==0);
 {
 
 uart_hs();
 ds1=ascii_tab[key_code];
 tx(ds1);
 delay(10);
 key_release(); 
   }
  }
  }

 

 void init()
 {
  scan_no=0;
  init_scon();
  init_keypad();
  init_timer0();
  init_timer1();
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

 void init_scon()
  {
   SCON=0x52;
  }
  void init_timer1()
  {
   TMOD|=0x20;
   TH1=0xFD;
   TL1=0xFD;
   TR1=1;
   }
  void init_timer0()
  {
   TMOD|=0x01;
   TL0=0x66;
   TH0=0xfc;
   TR0=1;
   ET0=1;
   }

void isr0_t0()	interrupt 1 using 1
{
 init_timer0();
 buzzer();
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
			P0=a[ds1-'0'];
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
			P0=a[ds2-'0'];
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
			P0=a[ds3-'0'];
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
			P0=a[ds4-'0'];
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

