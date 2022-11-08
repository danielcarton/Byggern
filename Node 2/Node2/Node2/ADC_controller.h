/*
 * ADC_controller.h
 *
 * Created: 03/11/2022 13:41:37
 *  Author: danie
 */ 


#ifndef ADC_CONTROLLER_H_
#define ADC_CONTROLLER_H_


void ADC_init(void);


uint16_t ADC_read(uint8_t port);


#endif /* ADC_CONTROLLER_H_ */