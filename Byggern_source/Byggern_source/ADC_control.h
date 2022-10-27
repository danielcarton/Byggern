/*
 * ADC_control.h
 *
 * Created: 15/09/2022 10:14:09
 *  Author: danie
 */ 


#ifndef ADC_CONTROL_H_
#define ADC_CONTROL_H_


extern volatile int joyy;
extern volatile int joyx;
extern volatile int sliderRight;
extern volatile int sliderLeft;

extern volatile uint8_t button1State;
extern volatile uint8_t button2State;
extern volatile uint8_t button3State;

extern volatile int joyxPercent;
extern volatile int joyyPercent;

void adc_init();
char get_ADC_data(void);
void ADC_start_read(void);

#endif /* ADC_CONTROL_H_ */