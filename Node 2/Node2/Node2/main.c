/*
 * Node2.c
 *
 * Created: 20.10.2022 15:22:26
 * Author : tobialie
 */ 


#include "sam.h"
#include "uart.h"
#include "printf-stdarg.h"
#include "can_controller.h"
#include "can_interrupt.h"
#include "PWM_controller.h"

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	
	WDT ->WDT_MR = WDT_MR_WDDIS; 
	configure_uart();
	can_init_def_tx_rx_mb(0x00290165);
	
	//printf("Daniel");
	
	PWM_init();
	PWM_set(2500);
	
    /* Replace with your application code */
    while (1) 
    {
		CAN_MESSAGE message;
		CAN_MESSAGE* msg = &message;
		can_receive(msg, 0);
		for (uint8_t i = 0; i <  8 /*message.data_length*/; i++)
		{
			//printf("Data[%d]: %d\t", i, msg->data[i]);
		}
		//printf("\n\r");
		uint8_t duty = joy_to_PWM(message.data[0]);
		PWM_set(duty);
		printf("Joyy: %d, Duty: %d \n\r", message.data[0], duty);
		
		
    }
}
