#include<pic.h>

void delay(unsigned int);
void init();
void init_timer0();
void scanner();
void display();

void inc_d();

void init_uart();
void txmit(unsigned char);
void uart_display();

void uart_home();

#define sl1 RA1
#define sl2 RC0
#define sl3 RC1
#define sl4 RC2


unsigned  int ds1=0;
unsigned  int ds2=0;
unsigned  int ds3=0;
unsigned  int ds4=0;

unsigned  int count;
unsigned char tx_data;
unsigned  int scan_no;




interrupt void isr_timer0()
	{
		init_timer0();

		scanner();
		
	}


void main()
	{

	TRISB=0X00;
	TRISA=0X3C;
	TRISC=0X00;
	ADCON1=0X06;
	GIE=1;
	PEIE=1;
   
	init();
	ds1='0';
	ds2='0';
	ds3='0';
	ds4='0';
	
	
	
	
	while(1)
		{
	uart_display();
		delay(100);
		inc_d();
	
		}
}

void uart_display()
{
	uart_home();
	txmit(ds4);
	delay(2);
	txmit(ds3);
	delay(2);
	txmit(ds2);
	delay(2);
	txmit(ds1);
	delay(2);
	
}



void uart_home()
{
	unsigned char vtcmd_hmpos[]={0x1b,'[','H'};

	unsigned int i;

	for(i=0;i<3;i++)
	{
		txmit(vtcmd_hmpos[i]);
	}
}

void init()
{
	init_uart();
	scan_no=0;
	init_timer0();
}

void init_timer0()
	{
		
		T1CON|=0X01;
		TMR1IE=1;
		TMR1IF=0;
		TMR1H=0Xfc;
		TMR1L=0X66;
	
	}


void init_uart()
	{
			TXSTA=0X24;
			SPBRG=25;
			RCSTA=0X90;
	}

void txmit(unsigned char tx)

{

	while(TXIF==0);
		{
			TXREG=tx;
			TXIF=0;
		}
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




 case 4:
 
  sl1=1;
  sl2=0;
  sl3=1;
  sl4=1;

  scan_no=5;
  break;
 
case 5:
  
  scan_no=6;
  break;

case 6:

   scan_no=7;
  break;

case 7:
  
  scan_no=8;
  break;

 
case 8:

  sl1=1;
  sl2=1;
  sl3=0;
  sl4=1;

  scan_no=9;
  break;
 
case 9:
   
  scan_no=10;
  break;

case 10:
   
  scan_no=11;
  break;

case 11:

 
  scan_no=12;
  break;


case 12:


  sl1=1;
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

  default: 
  scan_no=0;
  break;
  }

  
}





void inc_d()
{
	ds1++;

	if(ds1=='9'+1)
	{
		ds1='0';
		ds2++;

		if(ds2=='9'+1)
		{
			ds2='0';
			ds3++;
			
			if(ds3=='9'+1)
			{
				ds3='0';
				ds4++;
				
				if(ds4=='9'+1)
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

 void delay(unsigned int val)
{
 unsigned int t1,t2;
   for(t1=0;t1<=val;t1++)
    {
  for(t2=0;t2<=120;t2++);
	}

}
