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
int menu;
int menu_button;
int button_flag = 1;

void main_menu () {
	if (button3State == 1 || button_flag == 1)
	{
		menu_button = arrow;
		button_flag = 0;
	}
	
	menu_sel(menu_button);
	//oled_align_centre("Main menu");
	//oled_printf("Main menu");
	
	
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

void menu_sel (int menu_choice) {
	switch (menu_choice) {
		case 1:
			oled_align_centre("Main menu");
			oled_printf("Main menu");
			OLED_goto_pos(1,9);
			oled_printf("Play");
			OLED_goto_pos(2,9);
			oled_printf("High scores");
			OLED_goto_pos(3,9);
			oled_printf("Difficulty");
			break;
		case 2:
			oled_align_centre("Play");
			oled_printf("Play");
			break;
		case 3:
			oled_align_centre("High scores");
			oled_printf("High scores");
			break;
		case 4:
			oled_align_centre("Difficulty");
			oled_printf("Difficulty");
			break;
		case 5:
			menu = 5;
			break;
		case 6:
			menu = 6;
			break;
		case 7:
			menu = 7;
			break;
	}
	
}
