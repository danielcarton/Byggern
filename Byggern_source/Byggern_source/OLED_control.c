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
#include "fonts.h"


#ifndef OLED_COMMAND_ADDRESS
#define OLED_COMMAND_ADDRESS  0x1000
#endif

#ifndef OLED_DATA_ADDRESS
#define OLED_DATA_ADDRESS 0x1200
#endif

volatile char* oled_command = OLED_COMMAND_ADDRESS;
volatile char* oled_data = OLED_DATA_ADDRESS;



typedef enum {horizontal, vertical, page}addressingMode;

//typedef enum{FONT4, FONT5, FONT8}fontName;
volatile int fontSize = 8;

struct position{
	uint8_t line;
	uint8_t column;
	}pos;

void OLED_Write_Command(uint8_t command){
	oled_command[0] = command;
}

void OLED_Write_Data(uint8_t data){
	oled_data[0] = data;
}

void OLED_init(){
	OLED_Write_Command(0xae);
	OLED_Write_Command(0xa1);
	OLED_Write_Command(0xda);
	OLED_Write_Command(0x12);
	OLED_Write_Command(0xc8);
	OLED_Write_Command(0xa8);
	OLED_Write_Command(0x3f);
	OLED_Write_Command(0xd5);
	OLED_Write_Command(0x80);
	OLED_Write_Command(0x81);
	OLED_Write_Command(0x50);
	OLED_Write_Command(0xd9);
	OLED_Write_Command(0x21);
	OLED_Write_Command(0x20);
	OLED_Write_Command(0x02);
	OLED_Write_Command(0xdb);
	OLED_Write_Command(0x30);
	OLED_Write_Command(0xad);
	OLED_Write_Command(0x00);
	OLED_Write_Command(0xa4);
	OLED_Write_Command(0xa6);
	OLED_Write_Command(0xaf);
}

void OLED_reset(void){
	for (uint8_t line=0; line < 8; line++)
	{
		OLED_clear_line(line);
	}
	OLED_home();
}

void OLED_home(void){
	OLED_goto_pos(0,0);
}

int OLED_goto_line(uint8_t line){
	if(line < 8 && line >= 0){
		pos.line = line;
		set_addressingMode(page);
		OLED_Write_Command(0xB0+line);
		set_addressingMode(horizontal);
	}
	else{
		printf("Line out of bounds\n");
		return(0);
	}
}

int OLED_goto_column(uint8_t column){
	if (column<128 && column >= 0)
	{
		pos.column=column;
		set_addressingMode(page);
		
		uint8_t numLow = column % 16;
		uint8_t numHigh = column / 16;
		
		OLED_Write_Command(numLow);
		OLED_Write_Command(16 + numHigh);
		
		set_addressingMode(horizontal);
	}
	else{
		printf("Column out of bounds\n");
		return(0);
	}
}

void OLED_clear_line(uint8_t line){
	OLED_goto_pos(line, 0);
	
	for(uint8_t i = 0; i < 128; i++){
		OLED_Write_Data(0x00);
	}
	OLED_goto_line(line);
}


void OLED_fill_line(uint8_t line){
	OLED_goto_pos(line, 0);
	
	for(uint8_t i = 0; i < 128; i++){
		OLED_Write_Data(~0x00);
}
OLED_goto_line(line);
}

void OLED_goto_pos(uint8_t line, uint8_t column ){
	OLED_goto_line(line);
	OLED_goto_column(column);
}

void OLED_print_at_Pos(char ch){
	
}

void OLED_print_string(char* string){
	
}

void OLED_set_brightness(int lvl){
	
}

void OLED_print_arrow ( uint8_t row , uint8_t col )
{
	OLED_goto_pos(row , col);
	OLED_Write_Data(0b00011000);
	OLED_Write_Data(0b00011000);
	OLED_Write_Data(0b01111110);
	OLED_Write_Data(0b00111100);
	OLED_Write_Data(0b00011000);
}
int oled_put_char(unsigned char c){
	uint8_t printChar = (int)c-32;
	
	for (int i=0; i < fontSize; i++) {
		OLED_Write_Data(pgm_read_word(&font8[printChar][i]));
		pos.column += fontSize;
		oled_is_out_of_bounds();
	}
	
	return 0;
}

static FILE mystdout = FDEV_SETUP_STREAM(oled_put_char, NULL, _FDEV_SETUP_WRITE);

void oled_is_out_of_bounds() {
	if (pos.column > 127) {
		pos.column -= 128;
		pos.line += 1;
		if (pos.line > 7) {
			pos.line = 0;
		}
	}
}


void set_addressingMode(addressingMode mode){
	OLED_Write_Command(0x20);
	OLED_Write_Command(mode);
}

void oled_printf(char* data, ...){
	va_list args;
	va_start(args, data);
	vfprintf(&mystdout, data, args);
	va_end(args);
	
}
