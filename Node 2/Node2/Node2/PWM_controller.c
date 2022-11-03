/*
 * PWM_controller.c
 *
 * Created: 03/11/2022 09:31:07
 *  Author: danie
 */ 


#include "sam.h"

#define PWM_PERIOD 52500

void PWM_init(void){

    PMC->PMC_WPMR = 0x504d4300; //disable write protection
	
    PMC->PMC_SCER = 0x00000700; //enable all programmable clocks
    PMC->PMC_PCER1 |= PMC_PCER1_PID36; // enable clock on PWM
    PMC->PMC_PCER0 |= PMC_PCER0_PID13; //enable peripheral clock on port C

    
    PIOC->PIO_WPMR = 0x50494f00; //disable write protection

    PIOC->PIO_OER |= PIO_PC18; // enable output on pin 8 port A
    PIOC->PIO_PER &= ~PIO_PC18; //disable PIO control on PA8 aka enable peripheral control
    PIOC->PIO_PDR |= PIO_PC18; //set pin 19 port C as output
    PIOC->PIO_ABSR |= PIO_ABSR_P18; //enable peripheral B (pwm high) on pin 

    PWM->PWM_WPCR = 0x50574dfc;
    REG_PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(42);		// Set the PWM clock A rate to 2MHz (84MHz/42)
    REG_PWM_CMR6 = PWM_CMR_CPRE_CLKA;						// Left-align the PWM signal
    REG_PWM_CMR6 = (PWM_CMR_CPRE_MCK_DIV_32 | PWM_CMR_CPOL);
    REG_PWM_CPRD6 = PWM_PERIOD;
    REG_PWM_CDTY6 = 5510;
    REG_PWM_ENA = PWM_ENA_CHID6; 
}


/*
Lower PWM bound: 2365	(Plus a little added)
Upper PWM bound: 5510	(Plus a little subtracted)
*/
uint8_t PWM_set(uint16_t dutycycle){
	if (dutycycle >= 2365 && dutycycle <= 5510)
	{
		REG_PWM_CDTY6 = dutycycle;
		return(1);
	}
	return(0);
}

uint16_t joy_to_PWM(uint8_t joyval){
	float duty = 15.725*(float)joyval+2365;
	return((uint16_t)duty);
}