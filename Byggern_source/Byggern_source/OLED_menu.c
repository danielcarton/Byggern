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
int button_flag = 0;


void main_menu()
{
    // Run right after bootup after a oled_reset() to clear screen
	OLED_home();
    oled_align_centre("Main menu");
    oled_printf("Main menu");
    OLED_goto_pos(1, 9);
    oled_printf("Play");
    OLED_goto_pos(2, 9);
    oled_printf("High scores");
    OLED_goto_pos(3, 9);
    oled_printf("Difficulty");
	
	if (button3State == 0)
	{
		button_flag = 0;
	}

    // Use the joystick to navigate the menus, the joystick needs to be above or below a certain treshold to update the arrow and also to only be activated once on every joystick move
    if (joyy < 200 && (flag_down == 1 || flag_up == 1))
    {
	    if (joyy > 100)
	    {
		    flag_down = 0;
		    flag_up = 0;
	    }
    }

    if (joyy >= 200 && flag_up == 0)
    {
	    arrow_pos--;
	    flag_up = 1;
		OLED_clear_arrow();
	    if (arrow_pos == 0)
	    {
		    arrow_pos = 7;
	    }
    }

    if (joyy <= 100 && flag_down == 0)
    {
	    arrow_pos++;
	    flag_down = 1;
	    OLED_clear_arrow();
	    if (arrow_pos == 8)
	    {
		    arrow_pos = 1;
	    }
    }

    // Based on the arrows position on the menu, submenus can be entered by pressing the joystick button. The submenus run inside while() loops, and when entering a new loop, either break the loop to go back to the main menu or go into a new loop
    // Current design includes another switch-case for the arrowpointer functionality, for deeper submenus, could have to use same system to enter submenus as before, so like nested functions
    switch (arrow_pos)
    {
    case 1:
        arrow = 1;
        if (button3State == 1 && button_flag == 0)
        {
			button_flag = 1;
            OLED_reset();
            // Only run the play_menu, when exiting the play menu break the loop (might have to break the loop with flag instead of break;)
         
            play_menu();
			OLED_clear_arrow();
			arrow_pos = 1;
        }
        break;
    case 2:
        arrow = 2;
        if (button3State == 1)
        {
           OLED_reset();
		   hs_menu();
           // Only run the hs_menu, when exiting the high scores menu break the loop
		   OLED_clear_arrow();
           
		   arrow_pos = 1;
		   
        }
        break;
    case 3:
        arrow = 3;
        if (button3State == 1)
        {
            OLED_reset();
            // Only run the diff_menu, when exiting the difficulty menu break the loop
            diff_menu();
            OLED_clear_arrow();
            arrow_pos = 1;
        }
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

// Each submenu is its own function that loops and functions similary like the main menu
void play_menu(void)
{
	OLED_reset();
	while(1)
	{
		if (button3State == 0)
		{
			button_flag = 0;
		}
		
		OLED_home();
		oled_align_centre("Play");
		oled_printf("Play");
		OLED_goto_pos(1, 0);
		oled_align_centre("LB to quit");
		oled_printf("LB to quit");

		if (button2State == 1)
		{
			arrow = 1;
			OLED_reset();
			
			break;
		}
		
		// Game stuff
		control();
		
	}
}

void hs_menu(void)
{
	arrow_pos = 1;
	if (button3State == 0)
	{
 		button_flag = 0;
	}
	while(1)
	{
		arrow = 1;
		if (button3State == 0)
		{
			button_flag = 0;
		}
		
		OLED_home();
		oled_align_centre("High Scores");
		oled_printf("High Scores");
		OLED_goto_pos(7, 9);
		oled_printf("Back");

		if (joyy < 200 && (flag_down == 1 || flag_up == 1))
		{
			if (joyy > 100)
			{
				flag_down = 0;
				flag_up = 0;
			}
		}

		if (joyy >= 200 && flag_up == 0)
		{
			arrow_pos--;
			flag_up = 1;
			OLED_clear_arrow();
			if (arrow_pos == 0)
			{
				arrow_pos = 7;
			}
		}

		if (joyy <= 100 && flag_down == 0)
		{
			arrow_pos++;
			flag_down = 1;
			OLED_clear_arrow();
			if (arrow_pos == 8)
			{
				arrow_pos = 1;
			}
		}

		switch (arrow_pos)
		{
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

		if (button3State == 1 && arrow == 7)
		{
			arrow = 1;
			OLED_clear_arrow();
			OLED_reset();
			
			break;
		}
	}
	OLED_clear_arrow();
}

void diff_menu(void)
{
	arrow_pos = 1;
	if (button3State == 0)
	{
		button_flag = 0;
	}
	while(1)
	{
		if (button3State == 0)
		{
			button_flag = 0;
		}
		
		OLED_home();
		oled_align_centre("Difficulty");
		oled_printf("Difficulty");
		OLED_goto_pos(7, 9);
		oled_printf("Back");

		if (joyy < 200 && (flag_down == 1 || flag_up == 1))
		{
			if (joyy > 100)
			{
				flag_down = 0;
				flag_up = 0;
			}
		}

		if (joyy >= 200 && flag_up == 0)
		{
			arrow_pos--;
			flag_up = 1;
			OLED_clear_arrow();
			if (arrow_pos == 0)
			{
				arrow_pos = 7;
			}
		}

		if (joyy <= 100 && flag_down == 0)
		{
			arrow_pos++;
			flag_down = 1;
			OLED_clear_arrow();
			if (arrow_pos == 8)
			{
				arrow_pos = 1;
			}
		}

		switch (arrow_pos)
		{
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

		if (button3State == 1 && arrow == 7)
		{
			arrow = 1;
			OLED_reset();
			
			break;
		}
	}
	OLED_clear_arrow();
}

// void hs_menu(void)
// {
// 	arrow_pos = 1;
// 	if (button3State == 0)
// 	{
// 		button_flag = 0;
// 	}
// 	while(1)
// 	{
// 		OLED_home();
// 		oled_align_centre("High scores");
// 		oled_printf("High scores");
// 		OLED_goto_pos(7, 9);
// 		oled_printf("Quit");
// 
// 		if (joyy < 200 && (flag_down == 1 || flag_up == 1))
// 		{
// 			if (joyy > 100)
// 			{
// 				flag_down = 0;
// 				flag_up = 0;
// 			}
// 		}
// 
// 		if (joyy >= 200 && flag_up == 0)
// 		{
// 			arrow_pos--;
// 			flag_up = 1;
// 			OLED_clear_arrow();
// 			if (arrow_pos == 0)
// 			{
// 				arrow_pos = 7;
// 			}
// 		}
// 
// 		if (joyy <= 100 && flag_down == 0)
// 		{
// 			arrow_pos++;
// 			flag_down = 1;
// 			OLED_clear_arrow();
// 			if (arrow_pos == 8)
// 			{
// 				arrow_pos = 1;
// 			}
// 		}
// 
// 		switch (arrow_pos)
// 		{
// 			case 1:
// 			arrow = 1;
// 			break;
// 			case 2:
// 			arrow = 2;
// 			break;
// 			case 3:
// 			arrow = 3;
// 			break;
// 			case 4:
// 			arrow = 4;
// 			break;
// 			case 5:
// 			arrow = 5;
// 			break;
// 			case 6:
// 			arrow = 6;
// 			break;
// 			case 7:
// 			arrow = 7;
// 			break;
// 		}
// 
// 		OLED_print_arrow(arrow, 0);
// 
// 		if (button3State == 1 && arrow == 7)
// 		{
// 			arrow = 1;
// 			OLED_reset();
// 			
// 			break;
// 		}
// 	}
// 	OLED_clear_arrow();
// }
// 
// void diff_menu(void)
// {
// 	arrow_pos = 1;
// 	if (button3State == 0)
// 	{
// 		button_flag = 0;
// 	}
// 	while(1)
// 	{
// 		OLED_home();
// 		oled_align_centre("Difficulty");
// 		oled_printf("Difficulty");
// 		OLED_goto_pos(7, 9);
// 		oled_printf("Back");
// 
// 		if (joyy < 200 && (flag_down == 1 || flag_up == 1))
// 		{
// 			if (joyy > 100)
// 			{
// 				flag_down = 0;
// 				flag_up = 0;
// 			}
// 		}
// 
// 		if (joyy >= 200 && flag_up == 0)
// 		{
// 			arrow_pos--;
// 			flag_up = 1;
// 			OLED_clear_arrow();
// 			if (arrow_pos == 0)
// 			{
// 				arrow_pos = 7;
// 			}
// 		}
// 
// 		if (joyy <= 100 && flag_down == 0)
// 		{
// 			arrow_pos++;
// 			flag_down = 1;
// 			OLED_clear_arrow();
// 			if (arrow_pos == 8)
// 			{
// 				arrow_pos = 1;
// 			}
// 		}
// 
// 		switch (arrow_pos)
// 		{
// 			case 1:
// 			arrow = 1;
// 			break;
// 			case 2:
// 			arrow = 2;
// 			break;
// 			case 3:
// 			arrow = 3;
// 			break;
// 			case 4:
// 			arrow = 4;
// 			break;
// 			case 5:
// 			arrow = 5;
// 			break;
// 			case 6:
// 			arrow = 6;
// 			break;
// 			case 7:
// 			arrow = 7;
// 			break;
// 		}
// 
// 		OLED_print_arrow(arrow, 0);
// 
// 		if (button3State == 1 && arrow == 7)
// 		{
// 			arrow = 1;
// 			OLED_reset();
// 			
// 			break;
// 		}
// 	}
// 	OLED_clear_arrow();
// }
