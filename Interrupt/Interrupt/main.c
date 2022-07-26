/*
 * Interrupt.c
 *
 * Created: 2022-07-26 오전 10:31:56
 * Author : GunwooYun
 */ 

#define F_CPU 14745600L // 14.7456MHz
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <stdio.h>

uint8_t font[] = {	0x3f, 0x06, 0x5b, 0x4f, // 0, 1, 2, 3
					0x66, 0x6d, 0x7c, 0x07, // 4, 5, 6, 7
					0x7f, 0x6f, 0x77, 0x7c, // 8, 9, A, B
					0x39, 0x5e, 0x79, 0x71, // C, D, E, F
					0x08, 0x80};			// ., _

uint16_t cnt = 0;

void segment(uint8_t n)
{
	
	uint8_t N1000, N100, N10, N1;
	uint16_t buf;
	
	N1000 = n / 1000; // digit 1000
	buf = n % 1000;
	N100 = buf / 100; // digit 100
	buf = n % 100;
	N10 = buf / 10; // digit 10
	N1 = buf % 10; // digit 1
	
	for(int i = 0; i < 125; i++){
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

/* INT0 */
ISR(INT0_vect)
{
	cnt++;
	
	};

ISR(INT4_vect){
	if(cnt > 0)
		cnt--;
}

int main(void)
{
	DDRB |= 0xFF; // LED
	DDRG |= 0x0F; // c
	
	DDRD |= 0x00; // PORTD 0 : input
	DDRE |= 0x00; // PORTE 4 : input
	//EIMSK |= (1 << INT0); // Use INT0 (PORTD0)
	EIMSK |= (1 << INT0 | 1 << INT4); // Use INT0 (PORTD0)
	//EICRA = 0x03; // rising edge
	EICRA |= (1 << ISC01 | 1 << ISC00); // rising edge
	EICRB |= (1 << ISC41 | 1 << ISC40); // rising edge
	//EICRA |= (1 << ISC01); // falling edge
	//SREG = 0x80;

	sei();

    /* Replace with your application code */
    while (1) 
    {
		segment(cnt);
    }
}

