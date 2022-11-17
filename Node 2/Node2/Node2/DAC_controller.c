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
	
	DACC -> DACC_CR |= DACC_CR_SWRST; // reset DAC (Might also not be entirely neccesary)
	//DACC -> DACC_WPMR |= DACC_WPMR_WPKEY(0x444143)|(DACC_WPMR_WPEN); //Disable write protection on DAC
    DACC -> DACC_MR |= (DACC_MR_WORD_HALF)|(DACC_MR_REFRESH(0x0F))|(DACC_MR_STARTUP_1024)|(DACC_MR_TAG_DIS); // only that needs to be set is the refresh rate, which here is 16k/dacclk (Datasheet said word bit had to be cleared for 16bit use, so setting word to half MIGHT be necessary
    DACC -> DACC_CHER |= (DACC_CHER_CH1); // enable ONLY DAC channel 1
	DACC -> DACC_IER |= DACC_IER_TXRDY;
	DACC ->DACC_MR |= DACC_MR_USER_SEL_CHANNEL1;
	

    //enable pin 32
	PMC -> PMC_PCR |= 14;
	
	PIOD -> PIO_PER |= PIO_PDR_P10|PIO_PDR_P9; // disable PIO control of pin 32
	PIOD -> PIO_OER |= PIO_OER_P10|PIO_OER_P9; // enable output on pin 32
	PIOD -> PIO_PUDR |= PIO_PUDR_P10|PIO_PUDR_P9; // disable pullup on pin 32
	
	PIOD -> PIO_SODR |= PIO_SODR_P9;
}


// write to DAC 1
void DAC_write_channel_1(uint16_t value){
    DACC -> DACC_CDR = value; // write to DAC 1	
}

// set pin 32 high
void Dir_set(uint8_t dir){
    if (dir == 1)
    {
    PIOD -> PIO_SODR |= PIO_SODR_P10; 
    }
    if (dir == 0)
	{
    PIOD -> PIO_CODR |= PIO_CODR_P10;
    }
}

// recipie for a pizza
