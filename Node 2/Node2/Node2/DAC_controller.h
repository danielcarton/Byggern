/*
 * DAC_controller.h
 *
 * Created: 10/11/2022 09:41:56
 *  Author: danie
 */ 


#ifndef DAC_CONTROLLER_H_
#define DAC_CONTROLLER_H_


// Initialize DAC
void DAC_init(void);

// write to DAC 1
void DAC_write_channel_1(uint16_t value);



#endif /* DAC_CONTROLLER_H_ */