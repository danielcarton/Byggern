/*
 * OLED_control.c
 *
 * Created: 22/09/2022 13:00:50
 *  Author: danie
 */ 

#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>


#ifndef OLED_COMMAND_ADDRESS
#define OLED_COMMAND_ADDRESS  0x1000
#endif

#ifndef OLED_DATA_ADDRESS
#define OLED_DATA_ADDRESS 0x1200
#endif

volatile char* oled_command = OLED_COMMAND_ADDRESS;
volatile char* oled_data = OLED_DATA_ADDRESS;

void oledWriteCommand(int command){
	oled_command[0] = command;
}

void OLED_init(){
	oledWriteCommand(0xae);
	oledWriteCommand(0xa1);
	oledWriteCommand(0xda);
	oledWriteCommand(0x12);
	oledWriteCommand(0xc8);
	oledWriteCommand(0xa8);
	oledWriteCommand(0x3f);
	oledWriteCommand(0xd5);
	oledWriteCommand(0x80);
	oledWriteCommand(0x81);
	oledWriteCommand(0x50);
	oledWriteCommand(0xd9);
	oledWriteCommand(0x21);
	oledWriteCommand(0x20);
	oledWriteCommand(0x02);
	oledWriteCommand(0xdb);
	oledWriteCommand(0x30);
	oledWriteCommand(0xad);
	oledWriteCommand(0x00);
	oledWriteCommand(0xa4);
	oledWriteCommand(0xa6);
	oledWriteCommand(0xa5);
	oled_data[0]=0x53;
}