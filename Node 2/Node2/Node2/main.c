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
#include "DAC_controller.h"


#define PID_frequency 10
#define ADC_DIGITAL_THRESHOLD 1000

uint16_t motordata_recieve(void);
void motordata_init(void);


uint16_t motorpos, target, output;

// necessary variables
uint16_t error, prev_error = 0;
uint16_t integral, prev_integral = 0;
uint16_t derivative;

// PID constants
uint8_t KP = 10;
uint8_t KI = 10;
uint8_t KD = 0;



CAN_MESSAGE message;
int joytarget;


void TC3_Handler(){
	// PID calculations
	target = message.data[1];
	if (joytarget > motorpos)
	{
		error = joytarget - motorpos;
		Dir_set(0);
	}
	else{
		error = motorpos - joytarget;
		Dir_set(1);
	}
	
	printf("Error: %d, target: %d, motorpos: %d\n\r", error, joytarget, motorpos);
	integral = prev_integral + error / PID_frequency;
	derivative = (error - prev_error) * PID_frequency;
	output = KP * error + KI * integral + KD * derivative;

	// for next iteration
	prev_error = error;
	prev_integral = integral;
	printf("PID output: %d\n\r", output);
	
	// clear status register
	uint32_t status = TC1 ->TC_CHANNEL[0].TC_SR;
	//TC1 -> TC_CHANNEL[0].TC_CCR |= TC_CCR_SWTRG;
	//NVIC_ClearPendingIRQ(TC0_IRQn);
}





int main(void)
{
CAN_MESSAGE* msg = &message;

    /* Initialize the SAM system */
    SystemInit();
	
	WDT ->WDT_MR = WDT_MR_WDDIS; 
	configure_uart();
	can_init_def_tx_rx_mb(0x00290165);
	pid_init();

	
	PWM_init();
	ADC_init();
	DAC_init();
	
	PWM_set(2500);
	solenoid_init();
	motordata_init();
	int lightstate = 0, prev_lightstate = 0, i = 0;
	
	
    while (1) 
    {
		can_receive(msg, 0);
		//for (uint8_t i = 0; i <  8 /*message.data_length*/; i++)
		//{
			//printf("Data[%d]: %d ", i, msg->data[i]);
		//}
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
		
		joytarget = message.data[1];
		motorpos = motordata_recieve();
		//output = message.data[1];
		//printf("%d\n\r", DACval);
		
		//Dir_set(0);
		//if (output< 100)
		//{
			//Dir_set(1);
		//}
		//
		//if (output == 100)
		//{
			//output = 0;
			////printf("Set DACval to 0\n\r");
		//}
		//
		//else if (output > 100)
		//{
			//output = (output - 100)*32;
			////printf("positive direction, set DACval to %d", output);
		//}
		//
		//else if (output < 100)
		//{
			//output = (100 - output)*32;
			////printf("negative direction, set DACval to %d", output);
		//}
		
		
		//printf("DAC value is: %d\n\r", DACval);
		DAC_write_channel_1(output);
		
		uint16_t ADCVAL= ADC_read(0);
		lightstate = ADCVAL<ADC_DIGITAL_THRESHOLD;
		CAN_MESSAGE Recieve_message;
		if ((lightstate != prev_lightstate) && (lightstate == 1))
		{
			i++;
			//printf("light is covered, i = %d! The ADC Read %d\n\r", i, ADCVAL);
			//printf("Score is %d\n\r", i);
			Recieve_message.id = 5;
			Recieve_message.data_length = 1;
			Recieve_message.data[0] = i;
			can_send(&Recieve_message, 0);
		}
		prev_lightstate=lightstate;
		
		//printf("Motordata reads: %d\n\r", motordata_recieve());
		
    }
}

void motordata_init(void){
	// set pins 1-8 on channel c as input
	PIOC -> PIO_PER = 0xff<<1;
	PIOC -> PIO_ODR = 0xff<<1;

	// set pin 0-2 on channel D as output
	PIOD -> PIO_OER = PIO_PD0|PIO_PD1|PIO_PD2;
	
	// HHL
	PIOD -> PIO_CODR = PIO_PD2;
	//PIOD -> PIO_ODSR = PIO_PD0|PIO_PD1;
	PIOD -> PIO_SODR = PIO_PD0|PIO_PD1;

	// set motor to start position
	Dir_set(1);
	DAC_write_channel_1(3000);
	
	// HLL
	PIOD -> PIO_CODR = PIO_PD1;
	//delay(500);
	printf("Delay done");
	
	
	//delay(10);
	
	
	
	// HHL
	//PIOD -> PIO_CODR = PIO_PD1;
	//delay(1);
	PIOD -> PIO_SODR = PIO_PD1;
	DAC_write_channel_1(0);
	
}

 //!OE pin D0, !RST pin D1, SEL pin D2

uint16_t motordata_recieve(void){
	
	uint16_t motormax = 90000, range = 400;
	
	uint16_t data = 0;

	// LHL
	PIOD -> PIO_CODR = PIO_PD0|PIO_PD2;
	delay(1);
	//PIOD -> PIO_SODR = PIO_PD0;

	// read from 8 bits
	//for (int i = 0; i < 8; i++){
		//
	//}
	data |= (PIOC -> PIO_PDSR & 0xff)>>1;

	// LHH
	//PIOD -> PIO_CODR = PIO_PD2;
	//PIOD -> PIO_ODSR = PIO_PD2;
	PIOD -> PIO_SODR = PIO_PD2;
	//delay(1);

	uint16_t temp;
	// read from 8 bits
	//for (int i = 0; i < 8; i++){
		//
	//}
	temp |= (PIOC -> PIO_PDSR & 0xff)>>1;
	
	
	// HHL
	PIOD -> PIO_CODR = PIO_PD2;
	//PIOD -> PIO_ODSR = PIO_PD0;
	PIOD -> PIO_SODR = PIO_PD0;

	// return 16 bit value
	data = data << 8;

	if (data > motormax)
	{
		data = 0;
	}
	return(data*range/motormax);
}

