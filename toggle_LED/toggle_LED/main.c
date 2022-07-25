/*
 * toggle_LED.c
 *
 * Created: 2022-07-25 오후 2:56:26
 * Author : GunwooYun
 */ 

#define F_CPU 14745600L // 14.7456MHz
#include <avr/io.h>
#include <util/delay.h> // Use delay

int main(void)
{
	/* Replace with your application code */
	/* Data Direction Register */
	DDRB = 0xff; // 0 : input, 1 : output
	while (1)
	{
		PORTB = 0xff; // portB 0~7 set
		_delay_ms(1000); // delay 1sec
		PORTB = 0x00; //portB 0~8 clear
		_delay_ms(1000); // delay 1sec
	}
}