/*
 * PWM_controller.h
 *
 * Created: 10/11/2022 09:26:36
 *  Author: danie
 */ 


#ifndef PWM_CONTROLLER_H_
#define PWM_CONTROLLER_H_



/*
 * PWM_controller.c
 *
 * Created: 03/11/2022 09:31:07
 *  Author: danie
 */ 


#include "sam.h"

#define PWM_PERIOD 52500

void PWM_init(void);


uint8_t PWM_set(uint16_t dutycycle);

uint16_t joy_to_PWM(uint8_t joyval);


#endif /* PWM_CONTROLLER_H_ */