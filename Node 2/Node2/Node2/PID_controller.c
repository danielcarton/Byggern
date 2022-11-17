/*
 * PID_controller.c
 *
 * Created: 15/11/2022 13:59:09
 *  Author: danie
 */
#include "PID_controller.h"
#include "sam.h"

#define PID_frequency 100

uint16_t motorpos, target, output;



// necessary variables
uint16_t error, prev_error = 0;
uint16_t integral, prev_integral = 0;
uint16_t derivative;

// PID constants
uint8_t KP = 1;
uint8_t KI = 1;
uint8_t KD = 0;



void TC0_Handler(){
	// PID calculations
	error = target - motorpos;
	integral = prev_integral + error / PID_frequency;
	derivative = (error - prev_error) * PID_frequency;
	output = KP * error + KI * integral + KD * derivative;

	// for next iteration
	prev_error = error;
	prev_integral = integral;
	
	// clear status register
	uint8_t status = TC0 ->TC_CHANNEL[0].TC_SR;
}

void pid_init(void)
{
	motorpos=0;
	output=0;
	PMC -> PMC_PCR = (PMC_PCR_EN)|(PMC_PCR_CMD)|27;
	__disable_irq();
	TC0 ->TC_WPMR = TC_WPMR_WPKEY_PASSWD | 0x0<<0x0;
    TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_SET; // set mode
    TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS; // enable interrupt
    TC0->TC_CHANNEL[0].TC_RC = 84000000/PID_frequency;
    TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG; // enable clock and trigger
    NVIC_EnableIRQ(TC0_IRQn); // enable interrupt
    __enable_irq();
}



