/*
 * DAC_controller.c
 *
 * Created: 10/11/2022 09:41:42
 *  Author: danie
 */ 

#include "sam.h"

// Initialize DAC
void DAC_init(void){
    PMC -> PMC_PCR = (PMC_PCR_EN)|(PMC_PCR_CMD)|38; // enable peripheral clock for DAC (this will already be done by other processes, but doesnt hurt enabling it again
	
	DACC -> DACC_WPMR |= DACC_WPMR_WPKEY(0x444143)|(DACC_WPMR_WPEN); //Disable write protection on DAC
    //DACC -> DACC_CR |= DACC_CR_SWRST; // reset DAC (Might also not be entirely neccesary)	
    DACC -> DACC_MR |= (DACC_MR_WORD_HALF)|(DACC_MR_REFRESH(0x0F)); // only that needs to be set is the refresh rate, which here is 16k/dacclk (Datasheet said word bit had to be cleared for 16bit use, so setting word to half MIGHT be necessary
    DACC -> DACC_CHER |= (DACC_CHER_CH1); // enable ONLY DAC channel 1
}

// write to DAC 1
void DAC_write_channel_1(uint16_t value){
    DACC -> DACC_CDR |= value; // write to DAC 1	
}