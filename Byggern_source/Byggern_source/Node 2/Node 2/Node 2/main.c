/*
 * Byggern Node 2.c
 *
 * Created: 20.10.2022 09:58:04
 * Author : tobialie
 */ 

//#include <util/delay.h>
#include "sam.h"
#include "uart.h"
#include "printf-stdarg.h"
#include "can_controller.h"
#include "can_interrupt.h"

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	configure_uart();
	//can_init();
	// Disable watchdog
	WDT ->WDT_MR = WDT_MR_WDDIS; 
	 
	
	
	printf("Daniel\n");

    /* Replace with your application code */
    while (1); 
    // {
		
    //}
}
