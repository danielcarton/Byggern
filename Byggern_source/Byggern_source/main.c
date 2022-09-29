#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include "UART_Control.h"
#include "SRAM_Control.h"
#include "ADC_control.h"
#include "OLED_control.h"

#define OFFSET 0x1000
#define F_CPU 4915200
#define BAUD 9600
#define MYBURR F_CPU/16/BAUD-1


int main(){
	MCUCR = (1<<SRE);
	uart_start(MYBURR);
	fdevopen(&uart_transmit, &uart_recieve);
	
	int counter=0;
	adc_init(counter);
	OLED_init();
	
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
	
	int button3State;
	if (PIND & (1<<PD5))
	{
		button3State = 0;
	}
	else
	{
		button3State = 1;
	}
	int joyx=10;
	
	printf("Joy Y: %d,\t", (int)get_ADC_data());
	printf("Joy X: %d,\t", (int)get_ADC_data());
	printf("Right Slider: %d,\t", (int)get_ADC_data());
	printf("Left Slider: %d,  \t", (int)get_ADC_data());
	printf("Right button: %d,\t", button1State);
	printf("Left Button: %d, \t", button2State);
	printf("Joy button: %d\n\r", button3State);
	_delay_ms(1);
	OLED_reset();
	
	OLED_home();
	oled_printf("I DONT WANT TO MAKE THE FUCKING MENU");
	
	//for (int row = 0; row < 128; row++)
	//{
		//for (int lin = 0; lin < 8; lin++)
		//{
			//OLED_print_arrow(lin, row);
		//}
		//_delay_ms(joyx);
		//OLED_reset();
	//}
	//
	}
}