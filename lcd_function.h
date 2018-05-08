///////// LCD COMMANDS AND FUNCTIONS /////////


#ifndef lcd_function__INCLUDED
#define lcd_function__INCLUDED


////-------LCD DISPLAY CONTROL COMMANDS------////

#define	clear_lcd_display 0x01;

#define	return_lcd_cursor_home 0x02;


#define	shift_lcd_cursor_left 0x04;

#define	shift_lcd_cursor_right 0x06;

#define	shift_lcd_display_right 0x06;

#define	shift_lcd_display_left 0x07;


#define	lcd_display_off_cursor_off 0x08;

#define	lcd_display_off_cursor_on 0x0a;

#define	lcd_display_on_cursor_off 0x0c;

#define	lcd_display_on_cursor_on 0x0e;

#define	lcd_display_on_cursor_blinking 0x0f;


#define	mov_lcd_cursor_left 0x10;

#define	mov_lcd_cursor_right 0x14;

#define	mov_lcd_display_left 0x18;

#define	mov_lcd_display_right 0x1c;


#define	begin_from_lcd_line1 0x80;

#define	begin_from_lcd_line2 0xc0;

////---------LCD SELECTION COMMANDS-------////

#define	data_bit4_line1_small_font 0x20;

#define	data_bit4_line1_big_font 0x24;

#define	data_bit4_line2_small_font 0x28;

#define	data_bit4_line2_big_font 0x2c;


#define	data_bit8_line1_small_font 0x30;

#define	data_bit8_line1_big_font 0x34;

#define	data_bit8_line2_small_font 0x38;

#define	data_bit8_line2_big_font 0x3c;





///--------FUNCTIONS---------///

unsigned char p0_stat,temp,cmd_data;

sbit vled=P0^0;
sbit rs=P0^1;
sbit rw=P0^2;
sbit e=P0^3;

void cmd_wr(unsigned char);
void toggle();
void data_map(unsigned char);
void data_wr(unsigned char);
void delay(unsigned int);

void init_lcd()
{
	cmd_data=0x03;
	cmd_wr(cmd_data);
	delay(1);

	cmd_data=0x03;
	cmd_wr(cmd_data);
	delay(1);

	cmd_data=0x03;
	cmd_wr(cmd_data);
	delay(1);

	cmd_data=0x20;
	cmd_wr(cmd_data);
	delay(1);

	cmd_data=0x28;
	cmd_wr(cmd_data);
	delay(1);

	cmd_data=0x06;
	cmd_wr(cmd_data);
	delay(1);

	cmd_data=0x01;
	cmd_wr(cmd_data);
	delay(1);

	vled=0;
}

void cmd_wr(unsigned char var_cmd)
{
	rs=0;
	rw=0;
	
	data_map(var_cmd);
	toggle();

	var_cmd=var_cmd<<4;

	data_map(var_cmd);
	toggle();
}


void toggle()
{
	e=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	e=0;
}

void data_map(unsigned char var_data)
{
	temp=var_data & 0xf0;
	p0_stat=P0 & 0x0f;
	P0=p0_stat | temp;
}

void data_wr(unsigned char var_disp)
{
	rs=1;
	rw=0;
	
	data_map(var_disp);
	toggle();

	var_disp=var_disp<<4;

	data_map(var_disp);
	toggle();
}

void delay(unsigned int d)
{
	unsigned int dly1,dly2;

	for(dly1=0;dly1<d;dly1++)
	{
		for(dly2=0;dly2<120;dly2++);
	}
}

#endif