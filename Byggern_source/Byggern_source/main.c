#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "UART_Control.h"
#include "SRAM_Control.h"

#define OFFSET 0x1000
#define F_CPU 4915200
#define BAUD 9600
#define MYBURR F_CPU/16/BAUD-1


int main(){
	uart_start(MYBURR);
	MCUCR = (1<<SRE);
	FILE *Stream;
	Stream = fdevopen(&uart_transmit, &uart_recieve);

	SRAM_test();
}