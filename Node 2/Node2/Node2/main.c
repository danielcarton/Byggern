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
#include "Solenoid.h"


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
	solenoid_init();
	int lightstate = 0, prev_lightstate = 0, i = 0;
    /* Replace with your application code */
    while (1) 
    {
		CAN_MESSAGE message;
		CAN_MESSAGE* msg = &message;
		can_receive(msg, 0);
		for (uint8_t i = 0; i <  8 /*message.data_length*/; i++)
		{
		//	printf("Data[%d]: %d ", i, msg->data[i]);
		}
		//printf("\n\r");
		
		uint16_t duty = joy_to_PWM(message.data[0]);
		PWM_set(duty);
		
		uint8_t joy_button = message.data[5];
		
		printf("joy_button is %d \r\n", joy_button);
		
		if (joy_button == 1)
		{
			solenoid_push();
		}
		else
		{
			solenoid_notpush();
		}
		//printf("Joyy: %d, Duty: %d \n\r", message.data[0], duty);
		
		//printf("ADC reads: %d\n\r", ADC_read(0));
		
		uint16_t DACval = message.data[1];
		uint8_t dir;
		while (1)
		{
		
		if (DACval == 100)
		{
			DACval=0;
			break;
		}
		if (DACval > 100)
		{
			DACval = (DACval-100)*32;
			//printf("Dir 1\n\r");
			Dir_set(1);
			break;
		}
		else
		{
			DACval = (100-DACval)*32;
			//printf("Dir 0\n\r");
			Dir_set(0);
			break;
		}
		}
		
		//printf("DAC value is: %d\n\r", DACval);
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
