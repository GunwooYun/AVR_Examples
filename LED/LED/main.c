/*
 * LED.c
 *
 * Created: 2022-07-27 오후 5:14:50
 * Author : KCCI18
 */ 
#define F_CPU 14745600L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 0xff;
    
	PORTA = 0x05;
	PORTA = 0x0a;
	
    while (1) 
    {
		PORTA = 0x05;
		_delay_ms(100);
		PORTA = 0x0a;
		_delay_ms(100);
	}
}

