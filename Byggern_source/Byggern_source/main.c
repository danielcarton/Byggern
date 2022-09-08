#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "UART_Control.h"

#define OFFSET 0x1000
#define F_CPU 4915200
#define BAUD 9600
#define MYBURR F_CPU/16/BAUD-1


int main(){
	uart_start(MYBURR);
	FILE *Stream;

	Stream = fdevopen(&uart_transmit, &uart_recieve);

	printf("This is working\n");
	/* Replace with your application code */
	unsigned char ch, last=0;
	while (1)
	{
		ch=uart_recieve();
		if(last != ch){
			printf("%c", ch);
		}
		last=ch;
	}
}