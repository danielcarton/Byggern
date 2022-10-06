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
int arrow = 0;
int flag_up = 0;
int flag_down = 0;
int menu_main = 1;
int menu_button;
int button_flag = 1;
int oled_update = 1;




void main_menu () {
	if (button3State == 1 || button_flag == 1)
	{
		menu_button = arrow;
		button_flag = 0;
		oled_update = 1;
	}
	
	
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
			OLED_reset();
			oled_update = 1 ;
			if (arrow_pos == 0)
			{
				arrow_pos = 7;
			}
		
		}
	
		if (joyy <= 100 && flag_down == 0)
		{
			arrow_pos++;
			flag_down = 1;
			OLED_reset();
			oled_update = 1 ;
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
		if(oled_update == 1)
		{
			menu_sel(menu_button);
			oled_update = 0;
		}
		
		OLED_print_arrow(arrow, 0);
		
	
	
}

void menu_sel (int menu_choice) {
	int menu_play = 0;
	int menu_hs = 0;
	int menu_diff = 0;
	
	if(menu_main == 1 || (menu_play == 0 && menu_hs == 0 && menu_diff == 0))
	{
		switch (menu_choice) {
			case 0:
				OLED_reset();
				oled_align_centre("Main menu");
				oled_printf("Main menu");
				OLED_goto_pos(1,9);
				oled_printf("Play");
				OLED_goto_pos(2,9);
				oled_printf("High scores");
				OLED_goto_pos(3,9);
				oled_printf("Difficulty");		

				break;
			case 1:
				OLED_reset();
				oled_align_centre("Play");
				oled_printf("Play");
				OLED_goto_pos(7,9);
				oled_printf("Quit");
				menu_play = 1;
				menu_main = 0;
			

				break;
			case 2:
				
				menu_hs = 1;
				menu_main = 0;

				break;
			case 3:
				
				menu_diff = 1;
				menu_main = 0;

				break;
			case 4:
				//menu = 5;
				break;
			case 5:
				//menu = 6;
				break;
			case 6:
				//menu = 7;
				break;
		}
	}
	if(menu_play == 1 && menu_main == 0)
	{
		OLED_reset();
		oled_align_centre("Play");
		oled_printf("Play");
		OLED_goto_pos(7,9);
		oled_printf("Quit");
		
		if(menu_choice == 7)
		{
				printf("blahblahblahblah");
				menu_main = 1;
				menu_play = 0;
				menu_choice = 0;
		}
	}
	if(menu_hs == 1 && menu_main == 0)
	{
		OLED_reset();
		oled_align_centre("High scores");
		oled_printf("High scores");
		OLED_goto_pos(7,9);
		oled_printf("Back");
		switch(menu_choice)
		{
			case 7:
				menu_main = 1;
				menu_hs = 0;
		}
	}
	if(menu_diff == 1 && menu_main == 0)
	{
		OLED_reset();
		oled_align_centre("Difficulty");
		oled_printf("Difficulty");
		OLED_goto_pos(7,9);
		oled_printf("Back");
		switch(menu_choice)
		{
			case 7:
				menu_main = 1;
				menu_diff = 0;
		}
	}
	
}

void displaymenu(void){
	struct {
		int display;
		int lv1;
		int lv2;
		int lv3;
	}menulocation;
	menulocation.display = 1;
	menulocation.lv1 = 0;
	menulocation.lv2 = 0;
	menulocation.lv3 = 0;
	int debounce=0;
	
	while (menulocation.display == 1)
	{
		
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
			OLED_reset();
			oled_update = 1 ;
			if (arrow_pos == 0)
			{
				arrow_pos = 7;
			}
			
		}
		
		if (joyy <= 100 && flag_down == 0)
		{
			arrow_pos++;
			flag_down = 1;
			OLED_reset();
			oled_update = 1 ;
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
		OLED_reset();
		oled_align_centre("Main menu");
		oled_printf("Main menu");
		OLED_goto_pos(1,9);
		oled_printf("Play");
		OLED_goto_pos(2,9);
		oled_printf("High scores");
		OLED_goto_pos(3,9);
		oled_printf("Difficulty");
		menulocation.lv1 = arrow_pos;
		
		
		if (button3State != debounce)
		{
			if (button3State==1)
			{
				OLED_reset();
				while (menulocation.lv1==1)
				{
					oled_align_centre("Play");
					oled_printf("Play");
					OLED_goto_pos(7,9);
					oled_printf("Quit");
					menulocation.lv2 = arrow_pos;
					if (button3State != debounce)
					{
						if (button3State==1)
						{
							if (menulocation.lv2=7)
							{
								menulocation.lv1=0;
							}
						}
					}
					debounce = button3State;
				}
			}
		}
		debounce = button3State;
	}
}

