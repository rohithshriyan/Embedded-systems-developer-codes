#include<pic.h>
#include<stdio.h>

void init_uart();
void transmitter(unsigned char);

unsigned char tx_data, count;

unsigned char a[8]={"NILESH"};  



void main()
{


init_uart();


for(count=0;count<=6;count++)

{
	tx_data=a[count];
	transmitter(tx_data);

}




while(1);


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



