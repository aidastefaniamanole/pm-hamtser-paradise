#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

char get_data()
{	
	while (!(UCSR0A & (1<<RXC0)));
		return UDR0;
}

void PWM_init_front(unsigned int speed){

	DDRB |= (1 << PB4);
	
	TCCR0A |= (1 << WGM01) | (1 << WGM00);
	TCCR0A |= (1 << COM0B1);
	TCCR0B |= (1 << CS01) | (1 << CS00);
	OCR0B = speed;
	
	if(speed == 0)
		DDRB &= ~(1 << PB4);
	
}

void PWM_init_back(unsigned int speed){

	DDRB |= (1 << PB3);
	
	TCCR0A |= (1 << WGM01) | (1 << WGM00);
	TCCR0A |= (1 << COM0A1);
	TCCR0B |= (1 << CS00);
	OCR0A = speed;
	
	if(speed == 0)
		DDRB &= ~(1 << PB3);
	
}

void motor()
{
/* speed = u, v, x, w, z */	
	DDRD |= (1 << PD7);
	DDRA |= (1 << PA0);
	DDRA |= (1 << PA1);
	DDRA |= (1 << PA2);
	DDRA |= (1 << PA3);
	
	while (1) {
		
		char action = get_data();
		
		if(action == 's') {
			PWM_init_back(0);
			PWM_init_front(0);
			PORTA &= ~(1 << PA2);
			PORTA &= ~(1 << PA3);
		} else if(action == 'l') {
			char state = get_data();
			if(state == 'o'){
				PORTA |= (1 << PA0);
				PORTA |= (1 << PA1);
			} else if(state == 'c') {
				PORTA &= ~(1 << PA0);
				PORTA &= ~(1 << PA1);
			}
		} else if(action == 'g') {
			char direction = get_data();
			char left_right = get_data();
			char speed = get_data();
			
			if(left_right == 'l') {
				PWM_init_front(200);
				PORTB |= (1 << PB1);
				PORTA |= (1 << PA2);
				PORTA &= ~(1 << PA3);
			} else if(left_right == 'r') {
				PWM_init_front(200);
				PORTB &= ~(1 << PB1);
				PORTA |= (1 << PA3);
				PORTA &= ~(1 << PA2);
			} else if(left_right == 'n') {
				PWM_init_front(0);
				PORTA &= ~(1 << PA2);
				PORTA &= ~(1 << PA3);
			}
			
			if(speed == 'u')
				PWM_init_back(80);
			if(speed == 'v')
				PWM_init_back(100);
			if(speed == 'x')
				PWM_init_back(120);
			if(speed == 'w')
				PWM_init_back(130);
			if(speed == 'z')
				PWM_init_back(145);
			
			
			if(direction == 'f') {
				PORTB |= (1 << PB0);
			} else if(direction == 'b') {
				PORTB &= ~(1 << PB0);
			} else if(direction == 'n') {
				PWM_init_back(0);
			}
		} else {
			PWM_init_back(0);
			PWM_init_front(0);
			PORTA &= ~(1 << PA2);
			PORTA &= ~(1 << PA3);
		}
	}
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
	motor();
	
	return 0;
	
}