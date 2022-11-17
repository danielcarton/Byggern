/*
 * CAN_controller.c
 *
 * Created: 12/10/2022 20:33:43
 *  Author: danie
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "CAN_module_controller.h"
#include "SPI_control.h"
#include "CAN_module_registers.h"
#include "CAN_controller.h"

volatile uint8_t message_interrupt_flag=0;
extern CAN_message_struct message;

ISR(INT0_vect){
	message_interrupt_flag=1;
	printf("Flag");
}

void CAN_init(void){
	CAN_module_init();
	cli();
	MCUCR |= 3;
	GICR = (1<< INT0);
	sei();
	
	CAN_module_write(MCP_CANCTRL, MODE_CONFIG); //set to config mode
	CAN_module_write(MCP_CANINTE, 0x01); //Enable interrupts on recieve
	CAN_module_write(MCP_CNF1, 0x03); //set T	Q to 500ns, 8 times the FOSC
	CAN_module_write(MCP_CNF2, 0xB1); // Set PS1 to 6, determine PS2 with CNF3 bits, with sampling at 1x prescaler
	CAN_module_write(MCP_CNF3, 0x05); // set PS2 to 7 with no wakeup filter
	CAN_module_write(MCP_CANCTRL, MODE_NORMAL); 
}
uint8_t CAN_message_recieved(void){
	uint8_t temp = message_interrupt_flag;
	message_interrupt_flag=0;
	return(temp);
}




void CAN_send_message(CAN_message_struct* message){
	//load tx0 buffer with data
	//printf("ID: %x%x, DLC: %x, Data[8]: %x\n\r", message->message_id[0], message->message_id[1], message->data_length_code, message->data[6]);
	CAN_module_write(MCP_TXB0CTRL + 0x01, message->message_id[0]);
	CAN_module_write(MCP_TXB0CTRL + 0x02, message->message_id[1]<<5);
	CAN_module_write(MCP_TXB0CTRL + 0x05, message->data_length_code);
	for (uint8_t i = 0; i < 8; i++)
	{
		CAN_module_write(MCP_TXB0CTRL+0x06+i, message->data[i]);
	}
	//request to send
	_delay_ms(10);
	CAN_module_activate_cs();
	SPI_Transmit(MCP_RTS_TX0);
	CAN_module_deactivate_cs();
}

CAN_message_struct CAN_recieve_message(void){
	CAN_message_struct TempMessage;
	
	if (message_interrupt_flag==1)
	{
		TempMessage.message_id[0] = CAN_module_read(MCP_RXB0CTRL + 0x01);
		//printf("%x\n",CAN_module_read(MCP_RXB0CTRL + 0x01));
		TempMessage.message_id[1] = CAN_module_read(MCP_RXB0CTRL + 0x02)>>5;
		//printf("%x\n",CAN_module_read(MCP_RXB0CTRL + 0x02));
		TempMessage.data_length_code = CAN_module_read(MCP_RXB0CTRL + 0x05);
		//printf("%x\n",CAN_module_read(MCP_RXB0CTRL + 0x05));
		for (uint8_t i = 0; i < 8; i++)
		{
			TempMessage.data[i]= CAN_module_read(MCP_RXB0CTRL + 0x06 + i);
			//printf("%x\n",CAN_module_read(MCP_RXB0CTRL + 0x06+i));
		}
		message_interrupt_flag = 0;
		CAN_module_write(MCP_CANINTF, 0x00);
	}
	return(TempMessage);
}

void CAN_test(uint8_t test){
	CAN_message_struct temp;
	temp.message_id[0]=0xff;
	temp.message_id[1]=0x01;
	temp.data_length_code=0x0f;
	temp.data[0]=test;
	for (int i = 0; i<8; i++)
	{
		temp.data[i] = test;
	}
	CAN_send_message(&temp);
	_delay_ms(10);
	CAN_message_struct Recieved = CAN_recieve_message();
	printf("ID: %x%x, DLC: %x, Data[8]: %x", Recieved.message_id[0], Recieved.message_id[1]>>5, Recieved.data_length_code, Recieved.data[7]);
}