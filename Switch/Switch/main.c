/*
 * Switch.c
 *
 * Created: 2022-07-26 오전 9:26:35
 * Author : GunwooYun
 */ 

#define F_CPU 14745600L
#include <avr/io.h>
#include <util/delay.h>

/*
	PE0 ~ PE3 : LED
	PD0 ~ PD7 : switch
*/

/*
	PE0~3 : LED
	PE4~7 : switch
*/

int main(void)
{
	//DDRE = 0xff; // LED output 1 : output
	DDRE = 0x0f; // LED output 0~3 : output / 4~7 : input
	DDRD = 0x00; // switch input 0 : input
	
    /* Replace with your application code */
    while (1) 
    {
		PORTE = (PINE & 0xf0) >> 4; // PINE : Input Pins Address
    }
	return 0;
}