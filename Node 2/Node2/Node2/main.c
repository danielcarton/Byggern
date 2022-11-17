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
#include "PID_controller.h"


#define ADC_DIGITAL_THRESHOLD 1000

uint16_t motordata_recieve(void);
void motordata_init(void);


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
	pid_init();
	motordata_init();
	
	PWM_set(2500);
	solenoid_init();
	int lightstate = 0, prev_lightstate = 0, i = 0;
	
	
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
		
		uint8_t joy_button = message.data[4];
		
		//printf("joy_button is %d \r\n", joy_button);
		
		if (joy_button == 0)
		{
			solenoid_push();
		}
		else
		{
			solenoid_notpush();
		}
		//printf("Joyy: %d, Duty: %d \n\r", message.data[0], duty);
		
		//printf("ADC reads: %d\n\r", ADC_read(0));
		
		int16_t output = message.data[1];
		//printf("%d\n\r", DACval);
		uint8_t dir;
		
		Dir_set(1);
		if (output< 100)
		{
			Dir_set(0);
		}
		
		if (output == 100)
		{
			output = 0;
			//printf("Set DACval to 0\n\r");
		}
		
		else if (output > 100)
		{
			output = (output - 100)*32;
			//printf("positive direction, set DACval to %d", output);
		}
		
		else if (output < 100)
		{
			output = (100 - output)*32;
			//printf("negative direction, set DACval to %d", output);
		}
		
		
		//printf("DAC value is: %d\n\r", DACval);
		DAC_write_channel_1(output);
		
		uint16_t ADCVAL= ADC_read(0);
		lightstate = ADCVAL<ADC_DIGITAL_THRESHOLD;
		if ((lightstate != prev_lightstate) && (lightstate == 1))
		{
			i++;
			//printf("light is covered, i = %d! The ADC Read %d\n\r", i, ADCVAL);
			//printf("Score is %d\n\r", i);
			CAN_MESSAGE.id = 5;
			CAN_MESSAGE.data_length = 1;
			CAN_MESSAGE.data[0] = i;
			can_send(CAN_MESSAGE, 1);
		}
		prev_lightstate=lightstate;
		
		printf("Motordata reads: %x\n\r", motordata_recieve());
		
    }
}


void motordata_init(void){
	// set pins 1-8 on channel c as input
	PIOC -> PIO_PDR = 0xff;
	PIOC -> PIO_ODR = 0xff;
	// enable pullup on pins 1-8 on channel c
	PIOC -> PIO_PUER = 0xff;

	// set pin 0-2 on channel D as output
	PIOD -> PIO_OER = PIO_PD0|PIO_PD1|PIO_PD2;
	
	// set !OE high, set !reset high, set select low
	PIOD -> PIO_CODR = PIO_PD0|PIO_PD1|PIO_PD2;
	PIOD -> PIO_ODSR = PIO_PD0|PIO_PD1;
	PIOD -> PIO_SODR = PIO_PD0|PIO_PD1|PIO_PD2;

	// set motor to start position
	Dir_set(0);
	DAC_write_channel_1(1000);
	delay(100);
	printf("Delay done");
	DAC_write_channel_1(0);
	
	
	// set !OE high, set !reset low, set select low
	PIOD -> PIO_CODR = PIO_PD1;
	PIOD -> PIO_SODR = PIO_PD1;
	// set !OE high, set !reset high, set select low
	PIOD -> PIO_CODR = PIO_PD1;
	PIOD -> PIO_ODSR = PIO_PD1;
	PIOD -> PIO_SODR = PIO_PD1;

}

// !OE pin D0, !RST pin D1, SEL pin D2

uint16_t motordata_recieve(void){
	uint16_t data = 0;

	// set output enable low, Set reset high set select low
	PIOD -> PIO_CODR = PIO_PD0;
	PIOD -> PIO_SODR = PIO_PD0;

	// read from 8 bits
	for (int i = 0; i < 8; i++){
		data |= (PIOD -> PIO_PDSR & 0xff) << i;
	}

	// set select high
	PIOD -> PIO_CODR = PIO_PD1;
	PIOD -> PIO_ODSR = PIO_PD1;
	PIOD -> PIO_SODR = PIO_PD1;

uint16_t temp;
	// read from 8 bits
	for (int i = 0; i < 8; i++){
		temp |= (PIOD -> PIO_PDSR & 0xff) << i;
	}

	// set output enable high & select low
	PIOD -> PIO_CODR = PIO_PD0|PIO_PD2;
	PIOD -> PIO_ODSR = PIO_PD0;
	PIOD -> PIO_SODR = PIO_PD0|PIO_PD2;

	// return 16 bit value
	data = data << 8;

	return(data+temp);
}