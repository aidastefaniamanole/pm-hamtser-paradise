#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>


char get_data()
{
	while (!(UCSR0A & (1<<RXC0)));
		return UDR0;
}


void init_usart()
{
	UCSR0A = 0;
	UCSR0B = _BV(RXEN0) | _BV(TXEN0); //enable RX si TX
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); //8 data bit

	int baud = 103;
	UBRR0= baud;
}

int main(void) {

	init_usart();

	return 0;
}