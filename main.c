/*
 * GccApplication1.c
 *
 * Created: 04.09.2022 10:13:05
 * Author : daniesca
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define OFFSET 0x1000
#define F_CPU 4915200
#define BAUD 9600
#define MYBURR F_CPU/16/BAUD-1

void uart_init(unsigned int ubrr){
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

void string_init(unsigned int ubrr){
uart_init(ubrr);
}


int main()
{
	FILE *Stream;
	Stream = fdevopen(&uart_transmit, &uart_recieve);
	string_init(MYBURR);
	unsigned char text[] = "This is working\n";

	for (int i = 0; i<strlen(text); i++)
	{
		printf("%c", text[i]);
		//_delay_ms(10);
	}
    /* Replace with your application code */
	char ch;
	while(1){
		fgets(ch, 1, Stream);
		if (ch != 0)
		{
			printf("%c", ch);
			uart_transmit(ch);
		}
}
  
}

