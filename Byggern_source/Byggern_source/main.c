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
	OLED_init();
	
	MCUCR = (1<<SRE);
	while (1)
	{
	ADC_start_read(CHANNEL3);
	_delay_ms(1);


	int button1State;
	if (PIND & (1<<PD2))    // see comment #2
	{
		button1State = 1;
	}
	else
	{
		button1State = 0;
	}
	
	int button2State;
	if (PIND & (1<<PD3))   
	{
		button2State = 1;
	}
	else
	{
		button2State = 0;
	}
	
	printf("Joy Y: %d,\t", (int)get_ADC_data());
	printf("Joy X: %d,\t", (int)get_ADC_data());
	printf("Right Slider: %d,\t", (int)get_ADC_data());
	printf("Left Slider: %d,  \t", (int)get_ADC_data());
	printf("Right button: %d,\t", button1State);
	printf("Left Button: %d\n\r", button2State);
	_delay_ms(1);
	}
}