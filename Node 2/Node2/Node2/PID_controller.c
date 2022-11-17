/*
 * PID_controller.c
 *
 * Created: 15/11/2022 13:59:09
 *  Author: danie
 */
#include "PID_controller.h"
#include "sam.h"

#define PID_frequency 10

//uint16_t motorpos, target, output;
//
//
//
//// necessary variables
//uint16_t error, prev_error = 0;
//uint16_t integral, prev_integral = 0;
//uint16_t derivative;
//
//// PID constants
//uint8_t KP = 1;
//uint8_t KI = 1;
//uint8_t KD = 0;
//
//
//
//void TC0_Handler(){
	//// PID calculations
	//error = target - 200*motorpos/9000;
	//printf("Error: %d, target: %d, motorpos: %d\n\r", error, target, motorpos);
	//integral = prev_integral + error / PID_frequency;
	//derivative = (error - prev_error) * PID_frequency;
	//output = KP * error + KI * integral + KD * derivative;
//
	//// for next iteration
	//prev_error = error;
	//prev_integral = integral;
	//
	//// clear status register
	//uint8_t status = TC0 ->TC_CHANNEL[0].TC_SR;
//}

void pid_init(void)
{
	PMC -> PMC_PCER0 |= 1<<ID_TC3;
	
	NVIC_DisableIRQ(ID_CAN0);
	
	TC1 ->TC_WPMR = TC_WPMR_WPKEY_PASSWD | 0x0<<0x0;
	
    TC1->TC_CHANNEL[0].TC_CMR |= TC_CMR_TCCLKS_TIMER_CLOCK3 | TC_CMR_ENETRG | TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_SET; // set mode
    TC1->TC_CHANNEL[0].TC_IER |= TC_IER_CPCS; // enable interrupt
    TC1->TC_CHANNEL[0].TC_RC |= 84000000/(PID_frequency*32);
    NVIC_EnableIRQ(TC3_IRQn); // enable interrupt
    TC1->TC_CHANNEL[0].TC_CCR |= TC_CCR_CLKEN | TC_CCR_SWTRG; // enable clock and trigger
}
