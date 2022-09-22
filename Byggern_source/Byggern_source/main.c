#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "UART_Control.h"
#include "SRAM_Control.h"
#include "ADC_control.h"

#define OFFSET 0x1000
#define F_CPU 4915200
#define BAUD 9600
#define MYBURR F_CPU/16/BAUD-1


int main(){
	uart_start(MYBURR);
	fdevopen(&uart_transmit, &uart_recieve);
	
	int counter=0;
	adc_init(counter);
	
	MCUCR = (1<<SRE);
	SRAM_test();

}