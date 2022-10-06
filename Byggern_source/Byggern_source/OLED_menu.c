/*
 * OLED_menu.c
 *
 * Created: 29.09.2022 13:15:08
 *  Author: tobialie
 */ 
//
#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include "OLED_control.h"
#include "ADC_control.h"


int arrow_pos;
int arrow = 1;
int flag_up = 0;
int flag_down = 0;

void main_menu () {
	oled_align_centre("Main menu");
	oled_printf("Main menu");
	OLED_goto_pos(1,9);
	oled_printf("Sub menu 1");
	OLED_goto_pos(2,9);
	oled_printf("Sub menu 2");
	
	if (joyy < 200 && (flag_down == 1 || flag_up == 1))
	{
		if (joyy > 100)
		flag_down = 0; 
		flag_up = 0;
	}
	
	if (joyy >= 200 && flag_up == 0)
	{
		arrow_pos--;
		flag_up = 1;
		if (arrow_pos == 0)
		{
			arrow_pos = 7;
		}
		
	}
	
	if (joyy <= 100 && flag_down == 0)
	{
		arrow_pos++;
		flag_down = 1;
		if (arrow_pos == 8)
		{
			arrow_pos = 1;
		}
	}
	
	switch (arrow_pos){
		case 1:
			arrow = 1;
			break;
		case 2:
			arrow = 2;
			break;
		case 3:
			arrow = 3;
			break;	
		case 4:
			arrow = 4;
			break;
		case 5:
			arrow = 5;	
			break;
		case 6:
			arrow = 6;	
			break;
		case 7:
			arrow = 7;
			break;
	}
	OLED_print_arrow(arrow, 0);
	
}