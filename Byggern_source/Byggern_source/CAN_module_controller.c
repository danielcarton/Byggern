/*
 * CAN_control.c
 *
 * Created: 06/10/2022 13:15:48
 *  Author: danie
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "SPI_control.h"
#include "CAN_module_registers.h"


void CAN_module_activate_cs(void){
	PORTB = (0<<PB4);
}

void CAN_module_deactivate_cs(void){
	PORTB = (1<<PB4);
}



uint8_t CAN_module_read(uint8_t addr){
	uint8_t data;
	
	CAN_module_activate_cs();
	SPI_Transmit(MCP_READ);
	SPI_Transmit(addr);
	data=SPI_Recieve();
	CAN_module_deactivate_cs();
	return(data);
}
//comment
void CAN_module_write(uint8_t addr, uint8_t data){
	CAN_module_activate_cs();
	SPI_Transmit(MCP_WRITE);
	SPI_Transmit(addr);
	SPI_Transmit(data);
	CAN_module_deactivate_cs();
}

void CAN_module_request_send(uint8_t temp){
	CAN_module_activate_cs();
	SPI_Transmit(temp);
	CAN_module_deactivate_cs();
}

uint8_t CAN_module_read_status(void){
	uint8_t status;
	
	CAN_module_activate_cs();
	SPI_Transmit(MCP_READ_STATUS);
	status=SPI_Recieve();
	
	CAN_module_deactivate_cs();
	return(status);
}

void CAN_module_bit_modify(uint8_t addr, uint8_t bit, uint8_t data){
	CAN_module_activate_cs();
	SPI_Transmit(MCP_BITMOD);
	SPI_Transmit(addr);
	SPI_Transmit(bit);
	SPI_Transmit(data);	
	CAN_module_deactivate_cs();
}

void CAN_module_reset(void){
	CAN_module_activate_cs();
	SPI_Transmit(MCP_RESET);
	CAN_module_deactivate_cs();
	_delay_ms(10); //change if timing is off
}

void CAN_module_test(void){
	
}

void CAN_module_init(uint8_t mode){
	uint8_t val;
	SPI_Init();
	
	CAN_module_reset();
	
	val = CAN_module_read(MCP_CANSTAT);
	uint8_t mode_bits = (val & MODE_MASK);
	if(mode_bits != MODE_CONFIG){
	printf("MCP2515 is NOT in Configuration mode after reset! Its config bits are %x\n\r", mode_bits);
	//return(1);
	}
	
	CAN_module_write(MCP_CANCTRL, mode);
	
	val = CAN_module_read(MCP_CANSTAT);
	printf("%x\n\r", val);
	mode_bits = (val & MODE_MASK);
	if(mode_bits != mode){
	
	printf("MCP2515 is NOT in correct mode after reset! Its config bits are %x\n\r", mode_bits);
	printf("\n!\n");
	//return(1);
	}
	
	
	//return(0);
}