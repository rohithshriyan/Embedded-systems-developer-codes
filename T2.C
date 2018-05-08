 #include<LPC214X.h>
 #include<stdio.h>

 void display(void);
 void delay(unsigned int);
int main()
{
 VPBDIV|=0X00;
 PINSEL0|=0X00000000;  //FOR SELECT PORT0
 IO0DIR=0X00FF0000;  //DEFINE PINS 16 TO 23
 while(1)
 {
  
  display();
  }
 }

 void display()
 {
  IO1DIR=0X00010000;
  IO0SET=0X0060000;
  delay(500);
  IO0CLR=0X0060000;

  IO1DIR=0X00020000;
  IO0SET=0X0020000;
  delay(500);
  IO0CLR=0X0020000;

  IO1DIR=0X00040000;
  IO0SET=0X00DA0000;
  delay(500);
  IO0CLR=0X00DA0000;

  IO1DIR=0X00080000;
  IO0SET=0X00F20000;
  delay(500);
  IO0CLR=0X00F20000;

 
  }

 void delay(unsigned int d)
  {
  unsigned int i,j;
  
   for(i=0;i<=d;i++)
   {
    for(j=0;j<=120;j++);
	}
	}
