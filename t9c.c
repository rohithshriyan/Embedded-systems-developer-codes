#include<stdio.h>
#include<reg51.h>
unsigned char ds1,ds2,ds3,ds4;
unsigned char count,dcount;
unsigned char scan_no,c;
unsigned char a[]={0xfc,0x60,0xda,0xf2,0x66,
0xb6,0xbe,0xe0,0xfe,0x66,
0x00,0xff,0xff,0xff,0xff,0xff,0xff,
0xee,0x3e,0x9c,0x7a,0x9e,0x8e};

unsigned char ascii_tab[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
 sbit sl1=P2^0;
 sbit sl2=P2^1;
 sbit sl3=P2^2;
 sbit sl4=P2^3;
void delay(unsigned int);
void init_timer0();
void init();
void isr0_timer0();

void test_disp();
void init_disp();
void init_keypad();
void scanner();
void buzzer();
void k();

 sbit krl1=P2^4;
 sbit krl2=P2^5;
 sbit krl3=P2^6;
 sbit krl4=P2^7;
 sbit buzzer_pin=P1^5;
 unsigned int krcount;
 unsigned char key_code;
 void key_release();
 
 bit  nkp,start_buzzer,key_ready,tb;
 
 


 void main()
 {
  init();
  EA=1;
  test_disp();
 ds1='9'+2;
 ds2='9'+1;
 ds3='9'+1;
 ds4='9'+1;
 while(1)
 {
  while(key_ready==0);
  ds1=ascii_tab[key_code];
  key_release();
  }
  }
  
 void init()
  {
   init_disp();
   init_keypad();
   init_timer0();
   }
 
 void init_disp()
 {
  ds1='9'+2;
  ds2='9'+2;
  ds3='9'+2;
  ds4='9'+2;
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
  TMOD|=0X01;
  TL0=0x66;
  TH0=0xfc;
  TR0=1;
  ET0=1;
  }

 void isr0_timer0() 	interrupt 1 using 3
{ 
 init_timer0();
 buzzer();
 scanner();
}
void scanner()
{

 switch(scan_no)
 {  
case 0:
      sl1=0;
	  sl2=1;
	  sl3=1;
	  sl4=1;
       P0=a[ds1-'0'];
	   tb=krl1;
	   k();
	   scan_no=1;
	   break;

case 1:tb=krl2;
       	k();
       scan_no=2;
	   break;
case 2:tb=krl3;
       k();
       scan_no=3;
	   break;
case 3:
       
	   P0=0;
	   tb=krl4;
	   k();
	   scan_no=4;
	   break;
case 4:
       sl1=1;
	   sl2=0;
	   sl3=1;
	   sl4=1;
	   P0=a[ds2-'0'];
	   tb=krl1;
	   k();
	   scan_no=5;
	   break;
case 5:tb=krl2;
       k(); 
       scan_no=6;
	   break;

case 6:tb=krl3;
       k();
       scan_no=7;
	   break;
case 7:
       P0=0;
	   tb=krl4;
	   k();
	   scan_no=8;
	   break;
case 8: sl1=1;
	   sl2=1;
	   sl3=0;
	   sl4=1;
	   P0=a[ds3-'0'];
	   tb=krl1;
	   k();
	   scan_no=9;
	   break;
case 9:tb=krl2;
       k();
       scan_no=10;
       break;
case 10:tb=krl3;
        k();
       scan_no=11;
       break;
case 11:P0=0;
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
case 15:P0=0;
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


void test_disp()
{
 ds1='9'+2;
 ds2='9'+2;
 ds3='9'+2;
 ds4='9'+2;
 delay(1000);
 ds1='9'+1;
 ds2='9'+1;
 ds3='9'+1;
 ds4='9'+1;
 delay(1000);
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

  void delay(unsigned int del)
   {
    unsigned int i,j;
	for(i=0;i<=del;i++)
	{
	 for(j=0;j<=120;j++);
	 
	 }
	 }
	   