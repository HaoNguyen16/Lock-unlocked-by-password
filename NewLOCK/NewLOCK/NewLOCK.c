
#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "lcd_lib.h"
#include <avr/interrupt.h>
#include "stdutils.h"
#include "uart.h"


static unsigned int key;
static unsigned int op;
static unsigned int operand;
static char char_op;
unsigned char vib = 0;
char buf_lcd1[16];
char buf_lcd2[16];
char buf_lcd3[16];
ISR(INT0_vect)
{   
	unsigned char temp;
	//read the 74C922 outputs
	temp=PINC&0x0F;
	//Determine what key
	if(temp==7)
	{
		key = 0;
		sprintf(buf_lcd1, "%1d",key);
		strcat(buf_lcd2,buf_lcd1);
		LCD4_gotoxy(2,1);
		_delay_ms(10);
		LCD4_write_string(buf_lcd2);
	}
	else if(temp==2)
	{
		key = 1;
		sprintf(buf_lcd1, "%1d",key);
		strcat(buf_lcd2,buf_lcd1);
		LCD4_gotoxy(2,1);
		LCD4_write_string(buf_lcd2);
	}	
	else if(temp==6)
	{
		key = 2;
		sprintf(buf_lcd1, "%1d",key);
		strcat(buf_lcd2,buf_lcd1);
		LCD4_gotoxy(2,1);
		LCD4_write_string(buf_lcd2);
	}		
	else if(temp==10)
	{
		key = 3;
		sprintf(buf_lcd1, "%1d",key);
		strcat(buf_lcd2,buf_lcd1);
		LCD4_gotoxy(2,1);
		LCD4_write_string(buf_lcd2);
	}	
	else if(temp==1)
	{
		key = 4;
		sprintf(buf_lcd1, "%1d",key);
		strcat(buf_lcd2,buf_lcd1);
		LCD4_gotoxy(2,1);
		LCD4_write_string(buf_lcd2);
	}	
	else if(temp==5)
	{
		key = 5;
		sprintf(buf_lcd1, "%1d",key);
		strcat(buf_lcd2,buf_lcd1);
		LCD4_gotoxy(2,1);
		LCD4_write_string(buf_lcd2);
	}
	else if(temp==9)
	{
		key = 6;
		sprintf(buf_lcd1, "%1d",key);
		strcat(buf_lcd2,buf_lcd1);
		LCD4_gotoxy(2,1);
		LCD4_write_string(buf_lcd2);
	}
	else if(temp==0)
	{
		key = 7;
		sprintf(buf_lcd1, "%1d",key);
		strcat(buf_lcd2,buf_lcd1);
		LCD4_gotoxy(2,1);
		LCD4_write_string(buf_lcd2);
	}
	else if(temp==4)
	{
		key = 8;
		sprintf(buf_lcd1, "%1d",key);
		strcat(buf_lcd2,buf_lcd1);
		LCD4_gotoxy(2,1);
		LCD4_write_string(buf_lcd2);
	}
	else if(temp==8)
	{
		key = 9;
		sprintf(buf_lcd1, "%1d",key);
		strcat(buf_lcd2,buf_lcd1);
		LCD4_gotoxy(2,1);
		LCD4_write_string(buf_lcd2);
	}
	else if(temp==15)
	{
	//plus
	}
		
	else if(temp==14)
	{	
	//subtraction
	}		
		
	else if(temp==13)
	{
	//mult	
	}		

	else if(temp==12)
	{		
	//div	
	}		
		
	else if(temp==11)
	{	
	strcpy(buf_lcd3,buf_lcd2);	
	}		
	
	else if(temp==3)
	{
	LCD4_clear();
	LCD4_gotoxy(1,1);
	LCD4_write_string("ENTER PASSWORD");
	buf_lcd1[0] = '\0';
	buf_lcd2[0] = '\0';
	buf_lcd3[0] = '\0';
	}		

}
ISR(INT1_vect)
{	unsigned char i =0;
	vib++;
	if(vib == 3){
	UART_TxString("====!!!SUSPECTED BREAK-IN!!!====\r");
	UART_TxString("PRESS 1 TO CALL THE SECURITY\r");
	char a = UART_RxChar();
		if (a == '1')
		{
		UART_TxString("CALLING THE SECURITY\r");
			while(i<10)
			{
			LCD4_clear();
			LCD4_gotoxy(1,1);
			LCD4_write_string("Calling Security");
			PORTA ^= (1<<PA2);
			_delay_ms(100);
			PORTA ^= (1<<PA3);
			_delay_ms(100);
			i++;
			vib=0;
			}
		}
	}	
}
int main(void)
{	
	UART_Init(9600);
	DDRC=0x0F;
	DDRA=0xFF;
	PORTC=0xF0;
	DDRD |= (1<<PD5)|(1<<PD6)|(1<<PD7);
	DDRD &= ~(1<<PD2)&~(1<<PD3);
	PORTD = 0xFF;
	GICR|=0xC0;
    MCUCR=0x0F;
    //MCUCSR=0x00;
    GIFR=0xC0;
	sei();
	MENU:
	LCD4_init();
	LCD4_clear();
	LCD4_gotoxy(1,1);
	LCD4_write_string("ENTER PASSWORD");
	while(1)
	{	
		PORTA |=(1<<PA4);
		int x = atoi(buf_lcd3);
		if (x==123)
		{	
				LCD4_clear();
				LCD4_gotoxy(1,1);
				LCD4_write_string("WELCOME HOME!!!");
				PORTA = 0x02;
				_delay_ms(2000);
				PORTA = 0x00;
				buf_lcd3[0] = '\0';
				buf_lcd2[0] = '\0';
				LCD4_clear();
				LCD4_gotoxy(1,1);
				LCD4_write_string("LOCK? PRESS 1");
		}
		x = atoi(buf_lcd3);
				if (x==1)
				{
				PORTA = 0x01;
				_delay_ms(2000);
				PORTA = 0x00;
				buf_lcd3[0] = '\0';
				buf_lcd2[0] = '\0';
				LCD4_clear();
				LCD4_gotoxy(1,1);
				LCD4_write_string("DOOR CLOSED");
				_delay_ms(1000);
				goto MENU;
		
				}
			
	}	
}
