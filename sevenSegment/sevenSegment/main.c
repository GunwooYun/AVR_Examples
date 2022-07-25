/*
 * sevenSegment.c
 *
 * Created: 2022-07-25 오후 3:37:35
 * Author : GunwooYun
 */ 

#define F_CPU 14745600L // 14.7456MHz
#include <avr/io.h>
#include <util/delay.h>

/* 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F, ., _*/
unsigned char font[] = {0x3f, 0x06, 0x5b, 0x4f,
						0x66, 0x6d, 0x7c, 0x07,
						0x7f, 0x6f, 0x77, 0x7c,
						0x39, 0x5e, 0x79, 0x71,
						0x08, 0x80};

void segment(int n)
{
	
	unsigned char N1000, N100, N10, N1;
	int buf;
	
	N1000 = n / 1000; // digit 1000
	buf = n % 1000;
	N100 = buf / 100; // digit 100
	buf = n % 100;
	N10 = buf / 10; // digit 10
	N1 = buf % 10; // digit 1
	
	for(int i = 0; i < 250; i++){
		PORTG = 0x0e; // 0b0000 1110
		PORTB = font[N1000];
		_delay_ms(1);
		
		PORTG = 0x0d; // 1101
		PORTB = font[N100];
		_delay_ms(1);
		
		PORTG = 0x0b; // 1011
		PORTB = font[N10];
		_delay_ms(1);
		
		PORTG = 0x07; // 0111
		PORTB = font[N1];
		_delay_ms(1);
	}
}

int main(void)
{
    /* Replace with your application code */
	DDRB = 0xff; // LED all output
	DDRG = 0x0f; // FND 0~3 output
	PORTG = 0x00; // 0 : active
	
	//int num = 0;
	int count = 0;
    while (1) 
    {
		segment(count);
		count++;
		if(count == 9999) count = 0;
				
		/*
		PORTG = 0x0e; // 0b0000 1110
		PORTB = font[1];
		_delay_ms(1);
		
		PORTG = 0x0d; // 1101
		PORTB = font[2];
		_delay_ms(1);
		
		PORTG = 0x0b; // 1011
		PORTB = font[3];
		_delay_ms(1);
		
		PORTG = 0x07; // 0111
		PORTB = font[4];
		_delay_ms(1);
		*/
		
		/*
		PORTB = font[num];
		num++;
		_delay_ms(1000);
		if(PORTB == 0x80)
		{
			
			//PORTB = 0x01;
			num = 0;
		}
		*/
		
    }
}

