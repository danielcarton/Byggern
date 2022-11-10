/*
 * ADC_controller.c
 *
 * Created: 03/11/2022 13:41:24
 *  Author: danie
 */ 

#include "sam.h"
#include "ADC_controller.h"

void ADC_init(void){
	PMC -> PMC_PCR = (PMC_PCR_EN)|(PMC_PCR_CMD)|37;
	ADC -> ADC_CR |= ADC_CR_START; // Start ADC
	
	// set ADC clock to 1MHz, 96 clock cycle startup time, tracktime is 8 adc clock cycles, transfer time is 9 adc clock cycles, Set freerun mode on, hardware triggers disabled, 12 bit resolution
	ADC -> ADC_MR |= (ADC_MR_PRESCAL(41))|(ADC_MR_STARTUP_SUT96)|(ADC_MR_TRACKTIM(7))|(ADC_MR_TRANSFER(3))|(ADC_MR_FREERUN_ON)|(ADC_MR_SETTLING_AST9);
	ADC -> ADC_CHER |= 0xFFFF; // enable all ports :^)
}


uint16_t ADC_read(uint8_t port){
	//while((ADC->ADC_ISR_DRDY)); // wait for data ready
	return(ADC->ADC_CDR[port]); // return adc value
}

// Delay function that inputs milliseconds
void delay_ms(uint32_t ms){
	uint32_t i;
	for(i=0;i<ms;i++){
		delay_us(1000);
	}
}