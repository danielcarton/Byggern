/*
 * OLED_menu.c
 *
 * Created: 29.09.2022 13:15:08
 *  Author: tobialie
 */ 

#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include "OLED_control.h"

int arrow_pos;

void main_menu () {
	oled_align_centre("Main menu");
	oled_printf("Main menu");
	OLED_print_arrow(1,0);
	OLED_goto_pos(1,9);
	oled_printf("Sub menu 1");
	OLED_goto_pos(2,9);
	oled_printf("Sub menu 2");
	
	switch (arrow_pos){
		case arrow_pos = 1:
			
			break;
		case arrow_pos = 2:
		
			break;
		case arrow_pos = 3:
		
			break;	
		case arrow_pos = 4:
				
			break;
		case arrow_pos = 5:
				
			break;
		case arrow_pos = 6:
				
			break;
		case arrow_pos = 7:
		
			break;
	}
	
	
}