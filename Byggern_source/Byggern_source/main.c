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
#include "CAN_module_controller.h"
#include "CAN_module_registers.h"
#include "CAN_controller.h"

#define OFFSET 0x1000
#define F_CPU 4915200
#define BAUD 9600
#define MYBURR F_CPU/16/BAUD-1


int main(){
	MCUCR = (1<<SRE);
	uart_start(MYBURR);
	fdevopen(&uart_transmit, &uart_recieve);
	
	//Comment
	
	adc_init();
	OLED_init();
	
	CAN_init();
	CAN_message_struct Testmessage;
	
	while (1)
	{
		Testmessage.message_id[0] = 0x01;
		Testmessage.message_id[1] = 0x01;
		Testmessage.data_length_code = 0x07;
		Testmessage.data[0] = joyyPercent;
		Testmessage.data[1] = joyxPercent;
		Testmessage.data[2] = sliderLeft;
		Testmessage.data[3] = sliderRight;
		Testmessage.data[4] = button2State;
		Testmessage.data[5] = button1State;
		Testmessage.data[6] = button3State;
		
		CAN_send_message(&Testmessage);
		printf("joyy: %x, joyx: %x, sliderLeft: %d, SliderRight: %d, rightbutton: %d, Leftbutton: %d, Joybutton: %d\n\n\r", joyyPercent, joyxPercent, sliderLeft, sliderRight, button2State, button1State, button3State);
		_delay_ms(1000);
	}
	
	//while (1)
	//{
	//CAN_module_init(MODE_LOOPBACK);
	//
	//printf("Joy Y: %d,\t", joyyPercent);
	//printf("Joy X: %d,\t", joyxPercent);
	//printf("Left Slider: %d,  \t", sliderLeft);
	//printf("Right Slider: %d,\t", sliderRight);
	//printf("Left Button: %d, \t", button2State);
	//printf("Right button: %d,\t", button1State);
	//printf("Joy button: %d\n\r", button3State);
	//
	////oled_printf("");
	//displaymenu();
	////razzledazzleess
	////for (int row = 0; row < 128; row++)
	////{
		////for (int lin = 0; lin < 8; lin++)
		////{
			////OLED_print_arrow(lin, row);
		////}
		////_delay_ms(joyx);
		////OLED_reset();
	////}
	////
	//}
}