/*
 * Timer.c
 *
 * Created: 2022-07-26 오후 2:07:17
 * Author : GunwooYun
 */ 
#define F_CPU 14745600L // 14.7456MHz
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t font[] = {	0x3f, 0x06, 0x5b, 0x4f, // 0, 1, 2, 3
					0x66, 0x6d, 0x7c, 0x07, // 4, 5, 6, 7
					0x7f, 0x6f, 0x77, 0x7c, // 8, 9, A, B
					0x39, 0x5e, 0x79, 0x71, // C, D, E, F
					0x08, 0x80};			// ., _

uint16_t cnt = 0;
uint16_t t_cnt = 0;

/*
ISR(TIMER2_COMP_vect)
{
	//TCNT0 = 0xf2;
	t_cnt++;
	if(t_cnt >= 1000){
		t_cnt = 0;
		cnt++;
	}
	
}
*/


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
		PORTC = 0x0e; // 0b0000 1110
		PORTA = font[N1000];
		_delay_ms(1);
		
		PORTC = 0x0d; // 1101
		PORTA = font[N100];
		_delay_ms(1);
		
		PORTC = 0x0b; // 1011
		PORTA = font[N10];
		_delay_ms(1);
		
		PORTC = 0x07; // 0111
		PORTA = font[N1];
		_delay_ms(1);
	}
}

int main(void)
{
	/*	
		WGM 00 01 : 0, 0 normal mode
		COM 00 01 : 0, 0 normal mode
		prescaler : 1024
		
		f = 14.7456Mhz / 1024 = 14.4khz
		
		T = 1/14.4khz == 0.0694ms
		
		TCNT0 = 0xFF + 1 - counter value
		TCNT0 = 0xFF + 1 -14
		
	*/
	
	DDRA |= 0xff;
	DDRC |= 0x0f;
	DDRB |= 0x80; // PB7 OC2
	
	//PORTA |= 0xff;
	//PORTC |= 0x0f;
	PORTB = 0x00; // PB4 OC0
	
	TCCR2 |= (1 << CS20) | (1 << CS22); // prescaler 1024
	TCCR2 |= (1 << WGM21); // CTC mode
	TCCR2 |= (1 << COM20); // oc2 output toggle
	
	OCR2 = 13;
	TIMSK |= (1 << OCIE0); // oc2 output toggle
	//TCNT0 =  0xf2;
	//OCR0 = 0x7f;
	
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
		segment(cnt);
		
    }
}

