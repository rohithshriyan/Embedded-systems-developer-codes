//------------  STOPWATCH  --------------//
//----  A=START  B=PAUSE  C=RESET  -----//

#include<pic.h>

//--- Variable Declairation----//
unsigned int dly1,dly2,cnt_1sl;
unsigned char ds1,ds2,ds3,ds4,scan_no,cnt,dcnt,krcount,key_code;

unsigned char luk_up[]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6,
0x00,0xff,0xff,0xff,0xff,0xff,0xff,
0xee,0x3e,0x9c,0x7a,0x9e,0x8e,0xbc,0x6e,0x0c,0x70,0x0e,0x1c,0xaa,0x2a,0x3a,0xce,
0xd6,0x0a,0xb6,0x1e,0x7c,0x38,0xb8,0x62,0x66,0x92,0x00,0xff};

unsigned char ascii_tab[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

bit key_ready,nkp,tb,buzzer,chk,start_sw,s1_over;

#define sl1 RA1
#define sl2 RC0
#define sl3 RC1
#define sl4 RC2

#define krl1 RA2
#define krl2 RA3
#define krl3 RA4
#define krl4 RA5

#define buzz_pin RC5

//---Function Declairation----//
void init();
void init_timer1();
void init_display();
void init_keypad();
void init_delay_1sec();

void scanner();
void k();
void key_release();
void get_key();
void key_process();

void inc_d();

void delay(unsigned int);
void delay_1sec();

void d_buzzer();

void test_display();
void disp_blank();
void adisp1();
void adisp2();
void adisp3();
void adisp4();
void disp_sw();


//------ISR Routine-----------//
interrupt void isr_t1()
{
	init_timer1();
	delay_1sec();
	d_buzzer();
	scanner();

	if(s1_over==1)
	{
		inc_d();
		s1_over=0;
	}
}

//-----MAIN Routine-------//

void main()
{
	TRISA	= 0x3c;
	TRISB 	= 0x00;
	TRISC 	= 0x00;
	ADCON1	= 0x06;

	init();
	GIE	= 1;
	PEIE= 1;

	test_display();

	disp_sw();

	while(1)
	{
		get_key();
		key_process();
	}
}

//---------INITIALISATION Routines------//

void init()
{
	init_timer1();
	init_display();
	init_keypad();
	init_delay_1sec();
}


void init_keypad()
{
	krl1=1;
	krl2=1;
	krl3=1;
	krl4=1;

	scan_no=0;
	dcnt=33;
	krcount=32;

	key_ready=0;
	nkp=0;
	buzzer=0;
}

void init_timer1()
{
	T1CON	|=	0x01;
	TMR1L 	= 0x67;
	TMR1H	= 0xfc;
	TMR1IE 	= 1;
	TMR1IF 	= 0;
}

void init_delay_1sec()
{
	cnt_1sl=1000;
	//cnt_1sh=0x04;
	s1_over=0;
}

void init_display()
{
	ds1='z'+2;
	ds2='z'+2;
	ds3='z'+2;
	ds4='z'+2;
}

//--------SCANNER Routine--------//

void scanner()
{
	switch(scan_no)
	{
		case 0:	sl1=0;
				sl2=1;
				sl3=1;
				sl4=1;

				adisp1();

				chk=krl1;
				k();

				scan_no=1;
				
				break;

		case 1:	chk=krl2;
				k();
		
				scan_no=2;
				break;

		case 2:	chk=krl3;
				k();
		
				scan_no=3;
				break;

		case 3:	disp_blank();
				
				chk=krl4;
				k();
				
				scan_no=4;
				break;

		case 4:	sl1=1;
				sl2=0;
				sl3=1;
				sl4=1;

				adisp2();

				chk=krl1;
				k();

				scan_no=5;
				break;

		case 5:	chk=krl2;
				k();
		
				scan_no=6;
				break;

		case 6:	chk=krl3;
				k();
		
				scan_no=7;
				break;

		case 7:	disp_blank();

				chk=krl4;
				k();
				
				scan_no=8;
				break;

		case 8:	sl1=1;
				sl2=1;
				sl3=0;
				sl4=1;

				adisp3();

				chk=krl1;
				k();

				scan_no=9;
				
				break;

		case 9:	chk=krl2;
				k();
		
				scan_no=10;
				break;

		case 10:chk=krl3;
				k();
		
				scan_no=11;
				break;

		case 11:disp_blank();
				
				chk=krl4;
				k();

				scan_no=12;
				break;

		case 12:sl1=1;
				sl2=1;
				sl3=1;
				sl4=0;

				adisp4();

				chk=krl1;
				k();

				scan_no=13;
				
				break;

		case 13:chk=krl2;
				k();
		
				scan_no=14;
				break;

		case 14:chk=krl3;
				k();
		
				scan_no=15;
				break;

		case 15:disp_blank();

				chk=krl4;
				k();
				
				scan_no=0;
				break;

		default:scan_no=0;
				break;
	}
}

//---------KEY Routine-------//

void k()
{
	if(key_ready==0)
	{
		if(dcnt==33)
		{
			if(chk==0)
			{
				dcnt--;
				key_code=scan_no;
				goto out_k;
			}
			else
			{
			goto out_k;
			}
		}
		else if(dcnt!=33)
		{
			dcnt--;
			if(dcnt==0)
			{
				if(chk==0)
				{
					key_ready=1;
					buzzer=1;
					dcnt=33;
					goto out_k;
				}
				else
				{
					dcnt=33;
					goto out_k;
				}
			}
			
			else
			{
				goto out_k;
			}
		}
	}
	
	else if(key_ready==1)
	{
		if(chk==0)
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
				buzzer=0;		
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
	while(nkp!=1);
	key_ready=0;
	nkp=0;
}

void get_key()
{
	while(key_ready!=1);

	key_code=ascii_tab[key_code];
}

void key_process()
{
	switch(key_code)
	{
		case 'A': start_sw=1;
				  break;

		case 'B': start_sw=0;
				  break;

		case 'C': start_sw=0;

				  ds1='0';
				  ds2='0';
				  ds3='0';
				  ds4='0';

				  break;

		default:  break;
	}

	key_release();
}


void d_buzzer()
{
	if(buzzer==1)
	{
		buzz_pin=~buzz_pin;
	}
}

//---------INCREMENT Routine--------//

void inc_d()
{
	if(start_sw==1)
	{
		ds1++;

		if(ds1==('9'+1))
		{
			ds1='0';
			ds2++;

			if(ds2==('9'+1))
			{
				ds2='0';
				ds3++;
			
				if(ds3==('9'+1))
				{
					ds3='0';
					ds4++;
				
					if(ds4==('9'+1))
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

//---------DELAY Routine-----//

void delay(unsigned int d)
{
	unsigned int dly1,dly2;

	for(dly1=0;dly1<d;dly1++)
	{
		for(dly2=0;dly2<120;dly2++);
	}
}

void delay_1sec()
{
	if(s1_over!=1)
	{
		cnt_1sl--;
		if(cnt_1sl==0)
		{
			s1_over=1;
			cnt_1sl=1000;
		}
	}
}

	

//------------DISPLAY Routines---------//

void disp_blank()
{
	PORTB=0x00;
}

void adisp1()
{
//	chk=0;
	PORTB=luk_up[ds1-'0'];
}

void adisp2()
{
//   	chk=0;
	PORTB=luk_up[ds2-'0'];
}

void adisp3()
{
//	chk=0;
	PORTB=luk_up[ds3-'0'];
}

void adisp4()
{
//	chk=0;
	PORTB=luk_up[ds4-'0'];
}

void test_display()
{
	ds1='Z'+2;
	ds2='Z'+2;
	ds3='Z'+2;
	ds4='Z'+2;

	delay(1000);

	ds1='Z'+1;
	ds2='Z'+1;
	ds3='Z'+1;
	ds4='Z'+1;

	delay(1000);
}

void disp_sw()
{
	ds1='Z'+1;
	ds2='Z'+1;
	ds3='T';
	ds4='S';
}