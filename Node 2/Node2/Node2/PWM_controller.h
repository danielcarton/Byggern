/*
 * PWM_controller.h
 *
 * Created: 03/11/2022 09:35:09
 *  Author: danie
 */ 


#ifndef PWM_CONTROLLER_H_
#define PWM_CONTROLLER_H_

#define PWM_PERIOD 52500

void PWM_init(void);


/*
Lower PWM bound: 2365	(Plus a little added)
Upper PWM bound: 5510	(Plus a little subtracted)
*/
uint8_t PWM_set(uint16_t dutycycle);

#endif /* PWM_CONTROLLER_H_ */