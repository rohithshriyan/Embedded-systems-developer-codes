#include<pic.h>

#define sl1 RA1
#define sl2 RC0
#define sl3 RC1
#define sl4 RC2

#define krl1 RA2
#define krl2 RA3 
#define krl3 RA4
#define krl4 RA5

#define buzz RC5


void delay(unsigned int);
void init();
void init_keypad();
void init_timer1();
void scanner();

void init_uart();
void transmitter(unsigned char);



void key_release();
void k();
void buzzer();



bit key_ready ;
bit nkp ;
bit start_buzzer;
bit tb ;

unsigned  char ds1='0';
unsigned  char ds2='0';
unsigned  char ds3='0';
unsigned  char ds4='0';



unsigned  char tx_data;
unsigned  char scan_no;
unsigned  char krcount;
unsigned  char key_code;
unsigned  char dcount;
unsigned  char a[]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xe6,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xee,0x3e,0x9c,0x7a,0x9e,0x8e};
unsigned  char ascii_tab[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};


interrupt void isr_timer1()
	{
		init_timer1();
		buzzer();
		scanner();
		
	}


void main()
{
  
 	TRISB=0X00;
	TRISA=0X3C;
	TRISC=0X00;
	ADCON1=0X06;
	
	init();
	GIE=1;
	PEIE=1;
  
  while(1)
  {

	  while(key_ready==0);
	  	ds1= ascii_tab[key_code];
		tx_data=ds1;
		transmitter(tx_data);
	 	 key_release();
	}

}


void init()
	{
		init_uart();
		init_keypad();
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
		nkp=0;
		
		key_ready=0;
		start_buzzer=0;
	
	}


void init_uart()
	{
			TXSTA=0X24;
			SPBRG=25;
			RCSTA=0X90;
	}

void transmitter(unsigned char tx)

{

	while(TXIF==0);
		{
			TXREG=tx;
			TXIF=0;
		}
}


void init_timer1()
	{
		
		T1CON|=0X01;
		TMR1H=0Xfc;
		TMR1L=0X66;
		TMR1IF=0;
		TMR1IE=1;
	
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
			
			  tb=krl1;
			  k();
			  scan_no=1;
			  break;
			
	case 1:
			  
			  tb=krl2;
			  k();
			  scan_no=2;
			  break;
			 
	case 2:
	
			  tb=krl3;
			  k();
			   scan_no=3;
			  break;
			 
	case 3:
			  tb=krl4;
			  k();
			  scan_no=4;
			  break;
	case 4:
		
			 sl1=1;
			  sl2=0;
			  sl3=1;
			  sl4=1;
	
			  tb=krl1;
			  k();
			  scan_no=5;
			  break;
			 
	case 5:
			  tb=krl2;
			  k();
			  scan_no=6;
			  break;
			
	case 6:
			   tb=krl3;
			   k();
			   scan_no=7;
			   
			  break;
			
	case 7:	  
			  tb=krl4;
			  k();
			  scan_no=8;
			  break;
			
			 
	case 8:
			  sl1=1;
			  sl2=1;
			  sl3=0;
			  sl4=1;
			
	
			  tb=krl1;
			  k(); 
			  scan_no=9;
			  break;
			 
	case 9:
			   tb=krl2;
			  k(); 
			  scan_no=10;
			  break;
			
	case 10:
			  tb=krl3;
			  k(); 
			  scan_no=11;
			  break;
			
	case 11:
			  tb=krl4;
			   k(); 
	
			  scan_no=12;
			  break;
			
			
	case 12:
	
			  sl1=1;
			  sl2=1;
			  sl3=1;
			  sl4=0;
			
			  tb=krl1;
			  k();
			  scan_no=13;
			  break;
			 
	case 13:
	
		
			  tb=krl2;
			  k();
			  scan_no=14;
			  break;
			
	case 14:
			  tb=krl3;
			  k();
			  scan_no=15;
			  break;
			
			
	case 15:
			  tb=krl4;
			  k();
			  scan_no=0;

			  break;
			
	default: 
			  scan_no=0;
			  break;
		  }

}
void k()

{
    if (key_ready!=1)
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

 out_k: ;
}

 void delay(unsigned int val)
{
 unsigned int t1,t2;
   for(t1=0;t1<=val;t1++)
    {
  for(t2=0;t2<=120;t2++);
	}

}
void buzzer()

{
	if(start_buzzer==1)
	
	{
	  buzz=~buzz;
	 }
	
	 else
	 {
	 goto out_b;
	 }
	out_b: ;
	}
	
	void key_release()
	{
		while(nkp==0);
		key_ready=0;
		nkp=0;
	}














