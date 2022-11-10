/*
 * Node2.c
 *
 * Created: 20.10.2022 15:22:26
 * Author : tobialie
 */ 
#define F_CPU 84000000L
#define __SAM3X8E__

#include "sam.h"
#include "uart.h"
#include "printf-stdarg.h"
#include "can_controller.h"
#include "can_interrupt.h"
#include "PWM_controller.h"
#include "ADC_controller.h"
#include "QOL_tools.h"


#define ADC_DIGITAL_THRESHOLD 1000

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	
	WDT ->WDT_MR = WDT_MR_WDDIS; 
	configure_uart();
	can_init_def_tx_rx_mb(0x00290165);
	
	
	PWM_init();
	ADC_init();
	DAC_init();
	PWM_set(2500);
	int lightstate = 0, prev_lightstate = 0, i = 0;
    /* Replace with your application code */
    while (1) 
    {
		CAN_MESSAGE message;
		CAN_MESSAGE* msg = &message;
		can_receive(msg, 0);
		for (uint8_t i = 0; i <  8 /*message.data_length*/; i++)
		{
			//printf("Data[%d]: %d ", i, msg->data[i]);
		}
		//printf("\n\r");
		
		uint16_t duty = joy_to_PWM(message.data[0]);
		PWM_set(duty);
		//printf("Joyy: %d, Duty: %d \n\r", message.data[0], duty);
		
		//printf("ADC reads: %d\n\r", ADC_read(0));
		
		uint16_t DACval = message.data[1]*16;
		printf("DAC value is: %d\n\r", DACval);
		DAC_write_channel_1(DACval);
		
		uint16_t ADCVAL= ADC_read(0);
		lightstate = ADCVAL<ADC_DIGITAL_THRESHOLD;
		if ((lightstate != prev_lightstate) && (lightstate == 1))
		{
			i++;
			//printf("light is covered, i = %d! The ADC Read %d\n\r", i, ADCVAL);
			//printf("Score is %d\n\r", i);
		}
		prev_lightstate=lightstate;
		
    }
}
