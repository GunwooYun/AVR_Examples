/*
 * Timer_PWM.c
 *
 * Created: 2022-07-27 오전 9:48:34
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

uint8_t l_tcnt, l_mcnt;
uint8_t r_tcnt, r_mcnt;

void l_segment(uint8_t n)
{
	
	uint8_t N1000, N100, N10, N1;
	uint16_t buf;
	
	N10 = n / 10; // digit 10
	N1 = n % 10; // digit 1
	
	for(int i = 0; i < 5; i++){
		
		PORTC = 0x0e; // 1011
		PORTA = font[N10];
		_delay_ms(1);
		
		PORTC = 0x0d; // 0111
		PORTA = font[N1];
		_delay_ms(1);
	}
}

void r_segment(uint8_t n)
{
	
	uint8_t N1000, N100, N10, N1;
	uint16_t buf;
	
	N10 = n / 10; // digit 10
	N1 = n % 10; // digit 1
	
	for(int i = 0; i < 5; i++){
		
		PORTC = 0x0b; // 1011
		PORTA = font[N10];
		_delay_ms(1);
		
		PORTC = 0x07; // 0111
		PORTA = font[N1];
		_delay_ms(1);
	}
}

ISR(TIMER0_COMP_vect){
	l_tcnt++;
	/* 0.069444ms * 102 * 28 = 198.332064ms == 0.2s */
	if(l_tcnt >= 28){
		l_tcnt = 0;
		l_mcnt++;
		if(l_mcnt > 99) l_mcnt = 0;
	}
}

ISR(TIMER0_OVF_vect){
	r_tcnt++;
	/* 0.069444ms * 153 * 28 = 594.996192ms == 0.6 s*/
	if(r_tcnt >= 56){
		r_tcnt = 0;
		r_mcnt++;
		if(r_mcnt > 99) r_mcnt = 0;
	}
}

int main(void)
{
	/*	
		WGM 00 01 : 1, 1 PWM mode
		COM 00 01 : 1, 1 Clear OC0 on match point
		prescaler : 1024
		
		f = 14.7456Mhz / 1024 = 14.4khz == 14400 hz
		
		T = 1/14.4khz = 6.9444 * e-5(s) = 0.0694(ms)
	*/
	
	DDRB |= 0x10; // PB4 OC0 set output

	TCCR0 |= (1 << WGM00) | 1<< WGM01; // fast PWM mode
	TCCR0 |= (1 << COM01) | (1 << COM00); // Clear OC0 on match point <-- ARM PWM mode 0
	TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00); // prescaler 1024

	TIMSK |= (1 << OCIE0) | (1 << TOIE0); // oc2 output toggle

	DDRA = 0xff;
	DDRC = 0x0f;
	PORTA = 0xff;
	PORTC = 0x0f;

	OCR0 = 102; // PWM duty 40%

	sei();
	
	//uint8_t level = 0;
		
    /* Replace with your application code */
    while (1) 
    {
		r_segment(r_mcnt);
		l_segment(l_mcnt);
    }
}