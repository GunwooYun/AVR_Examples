/*
 * Timer_CTC.c
 *
 * Created: 2022-07-27 오후 2:10:11
 * Author : GunwooYun
 */ 

#define F_CPU 14745600L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t font[] = {	0x3f, 0x06, 0x5b, 0x4f, // 0, 1, 2, 3
					0x66, 0x6d, 0x7c, 0x07, // 4, 5, 6, 7
					0x7f, 0x6f, 0x77, 0x7c, // 8, 9, A, B
					0x39, 0x5e, 0x79, 0x71, // C, D, E, F
					0x08, 0x80};			// ., _

uint16_t cnt = 0;
uint16_t cntSec = 0;


void segment(uint16_t n)
{
	if(n > 9999) return;
	
	uint8_t n1000, n100, n10, n1;
	uint16_t buf;
	
	n1000 = n / 1000; // digit 1000
	buf = n % 1000;
	n100 = buf / 100; // digit 100
	buf = n % 100;
	n10 = buf / 10; // digit 10
	n1 = buf % 10; // digit 1
	
	for(int i = 0; i < 125; i++){
		PORTC = 0x0e; // 0b0000 1110
		PORTA = font[n1000];
		_delay_ms(1);
		
		PORTC = 0x0d; // 1101
		PORTA = font[n100];
		_delay_ms(1);
		
		PORTC = 0x0b; // 1011
		PORTA = font[n10];
		_delay_ms(1);
		
		PORTC = 0x07; // 0111
		PORTA = font[n1];
		_delay_ms(1);
	}
}

ISR(TIMER2_COMP_vect){
	if(cntSec >= 99){ // 10ms * 100 = 1sec
		cntSec = 0;
		cnt++;
		if(cnt > 9999) cnt = 0;
	}
	cntSec++;
}

int main(void)
{
	/* Timer 설정 */
	DDRB |= 0x80; // OC2[PB7] output mode
	// 프리스케일러 1024 -> F_CPU/1024 = 14,400 -> T = 0.069444ms
	TCCR2 |= (1 << CS22 | 1 << CS20);
	TCCR2 |= (1 << WGM21); // CTC 모드
	TCCR2 |= (1 << COM20); // 매치시 토글
	
	OCR2 = 144; // 10ms 주기로 인터럽트 발생
	
	/* FND 출력 설정 */
	DDRA |= 0xFF;
	DDRC |= 0x0F;
	TIMSK |= (1 << OCIE2); // 타이머2 매치시 인터럽트 발생
	
	sei();
    /* Replace with your application code */
    while (1) 
    {
		segment(cnt);
    }
}

