/*
 * GccApplication1.c
 *
 * Created: 04.09.2022 10:13:05
 * Author : daniesca
 */ 

#include <avr/io.h>


void uart_start(unsigned int ubrr){
	UCSR0A &=~(1<<U2X0);
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	UCSR0C = (1 << URSEL0) | (1 << USBS0) | (3 << UCSZ00);
}

void uart_transmit(unsigned char data){
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

void uart_recieve(void){
	while (!(UCSR0A & (1<<UDRE0)));
	return(UDR0);
}


