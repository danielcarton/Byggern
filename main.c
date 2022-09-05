/*
 * GccApplication1.c
 *
 * Created: 04.09.2022 10:13:05
 * Author : daniesca
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <UART_Control.h>

#define OFFSET 0x1000
#define F_CPU 4915200
#define BAUD 9600
#define MYBURR F_CPU/16/BAUD-1


int main(){
	uart_start(MYBURR);

	fdevopen(&uart_transmit, &uart_recieve);

	unsigned char text[] = "This is working\n";

	for (int i = 0; i<strlen(text); i++)
	{
		printf("%c", text[i]);
		_delay_ms(5);
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

