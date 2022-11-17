/*
 * game.c
 *
 * Created: 17.11.2022 11:05:48
 *  Author: tobialie
 */ 

#include "game.h"
#include "CAN_controller.h"
#include "ADC_control.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

CAN_message_struct message;

void control(void)
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
	_delay_ms(1);
}

int score(void)
{
	CAN_message_struct tempmessage = CAN_recieve_message();
	
	int scorevalue = tempmessage.data[0];
	return scorevalue;
}