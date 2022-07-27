/*
 * Uart.c
 *
 * Created: 2022-07-27 오전 11:50:26
 * Author : GunwooYun
 */ 

#define F_CPU 14745600L // 14.7456MHz
#include <avr/io.h>
#include <util/delay.h>

void UART0_transmit(uint8_t data);
uint8_t UART0_receive(void);

int main(void)
{
	DDRE = 0x02; // Set TX output
	UCSR0B |= (1 << RXEN0 | 1 << TXEN0); // RXEN0 : receiver enable, TXEN0 : Transmitter enable
	UCSR0C |= 0x06; // UCSZn1 : 1 UCSZn0 : 1 -> 8-bit
	UBRR0L = 95; // speed : 9600
	
	uint8_t data;
	
    /* Replace with your application code */
    while (1) 
    {
		data = UART0_receive();
		UART0_transmit(data);
		_delay_ms(10);

    }
}

void UART0_transmit(uint8_t data)
{
	
	while(1)
	{
		// empty : 1 & 1 -> 1
		if((UCSR0A & (1 << UDRE0))) break;
	}
	UDR0 = data;
}

uint8_t UART0_receive(void)
{
	while(1)
	{
		if((UCSR0A & (1 << RXC1))) break;
	}
	return UDR0;
}