   ///////// I2C ROUTINES ////////////

#ifndef i2c__INCLUDED
#define i2c__INCLUDED

#include<intrins.h>
#include<lcd_function.h>

sbit	SCL = P1^6;
sbit	SDA = P1^7;


unsigned char rx_val,rx_cont,tx_cont;

void start_i2c();
unsigned char i2c_shin();
void shout_i2c(unsigned char);
void stop_i2c();

void ack_i2c();
void nack_i2c();


void start_i2c()
{
	SDA=1;
	SCL=1;

	if(SDA==0)
	{
		cmd_wr(0x8f);
		delay(5);
		
		data_wr('#');
		delay(5);
	}

	if(SCL==0)
	{
		cmd_wr(0xcf);
		delay(5);
		
		data_wr('#');
		delay(5);
	}

	_nop_();
	_nop_();
	_nop_();
	_nop_();

	SDA=0;

	_nop_();
	_nop_();
	_nop_();
	_nop_();

	SCL=0;
}

void shout_i2c(unsigned char tx_val)
{
	unsigned char val_tx,cnt;

	tx_cont=0x80;

	SCL=0;
	for(cnt=0;cnt<=7;cnt++)
	{
		val_tx=tx_val & tx_cont;
		
		if(val_tx==0x80)
		{
			SDA=1;
		}

		else
		{
			SDA=0;
		}

		tx_val=tx_val<<1;

		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();

		SCL=1;

		_nop_();
		_nop_();
		_nop_();
		_nop_();
		
		SCL=0;

	}
}

unsigned char shin_i2c()
{
	unsigned char cnt;	

	rx_val=0x00;
	rx_cont=0x80;

	SCL=0;

	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();

	SDA=1;

	for(cnt=0;cnt<=7;cnt++)
	{
		SCL=1;

		_nop_();
		_nop_();
		_nop_();
		_nop_();

		if(SDA==1)
		{
			rx_val=rx_val | rx_cont;
		}

		SCL=0;

		_nop_();
		_nop_();
		_nop_();
		_nop_();

		rx_cont=rx_cont>>1;
	}
	
	return(rx_val);
}



void ack_i2c()
{
	SDA=0;
	SCL=0;

	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();

	SCL=1;

	_nop_();
	_nop_();
	_nop_();
	_nop_();

	SCL=0;
}

void nack_i2c()
{
	SDA=1;
	SCL=1;

	_nop_();
	_nop_();
	_nop_();
	_nop_();

	SCL=0;
}

void stop_i2c()
{
	SDA=0;
	SCL=1;

	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();

	SDA=1;

	_nop_();
	_nop_();
	_nop_();
	_nop_();
	
	SCL=0;
}


#endif