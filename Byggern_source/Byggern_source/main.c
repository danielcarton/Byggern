#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include "UART_Control.h"
#include "SRAM_Control.h"
#include "ADC_control.h"
#include "OLED_control.h"
#include "OLED_menu.h"

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
	OLED_reset();
	
	while (1)
	{

	
	printf("Joy Y: %d,\t", joyyPercent);
	printf("Joy X: %d,\t", joyxPercent);
	printf("Left Slider: %d,  \t", sliderLeft);
	printf("Right Slider: %d,\t", sliderRight);
	printf("Left Button: %d, \t", button2State);
	printf("Right button: %d,\t", button1State);
	printf("Joy button: %d\n\r", button3State);
	
	//oled_printf("");
	
	main_menu();
	//razzledazzleess
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