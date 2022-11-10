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
	CAN_message_struct message;
	
	while (1)
	{
	message.message_id[0] = 0xFF;
	message.message_id[1] = 0xFF;
	message.data_length_code = 7;
	message.data[0]=(uint8_t)joyyPercent+100;
	message.data[1]=(uint8_t)joyxPercent+100;
	message.data[2]=sliderLeft;
	message.data[3]=sliderRight;
	message.data[4]=button1State;
	message.data[5]=button3State;
	message.data[6]=button2State;
	CAN_send_message(&message);
	_delay_ms(10);
	
	printf("joyy: %d, joyx: %d, sliderLeft: %d, SliderRight: %d, rightbutton: %d, Leftbutton: %d, Joybutton: %d\n\r", joyyPercent, joyxPercent, sliderLeft, sliderRight, button2State, button1State, button3State);
	printf("data[0]: %d, data[1]: %d, data[2]: %d, data[3]: %d, data[4]: %d, data[5]: %d, data[6]: %d\n\n\r", message.data[0], message.data[1], message.data[2], message.data[3], message.data[4], message.data[5], message.data[6]);
	
	
	//printf("Joy Y: %d,\t", joyyPercent);
	//printf("Joy X: %d,\t", joyxPercent);
	//printf("Left Slider: %d,  \t", sliderLeft);
	//printf("Right Slider: %d,\t", sliderRight);
	//printf("Left Button: %d, \t", button2State);
	//printf("Right button: %d,\t", button1State);
	//printf("Joy button: %d\n\r", button3State);
	//
	//oled_printf("");
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