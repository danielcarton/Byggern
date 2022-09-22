/*
 * ADC_control.h
 *
 * Created: 15/09/2022 10:14:09
 *  Author: danie
 */ 


#ifndef ADC_CONTROL_H_
#define ADC_CONTROL_H_

typedef enum {CHANNEL1, CHANNEL2, CHANNEL3, CHANNEL4} channel_t;

void adc_init(int *counter);
char get_ADC_data(void);
void ADC_start_read(channel_t channel);


#endif /* ADC_CONTROL_H_ */