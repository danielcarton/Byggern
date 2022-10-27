/*
 * CAN_controller.h
 *
 * Created: 12/10/2022 20:33:55
 *  Author: danie
 */ 


#ifndef CAN_CONTROLLER_H_
#define CAN_CONTROLLER_H_

typedef struct  
{
	uint8_t message_id[2];
	uint8_t data_length_code;
	uint8_t data[8];
}CAN_message_struct;

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

void CAN_init(void);

uint8_t CAN_message_recieved(void);
void CAN_send_message(CAN_message_struct* message);

CAN_message_struct CAN_recieve_message(void);

void CAN_test(uint8_t test);

#endif /* CAN_CONTROLLER_H_ */