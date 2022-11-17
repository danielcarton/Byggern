/*
 * PID_controller.h
 *
 * Created: 15/11/2022 13:59:20
 *  Author: danie
 */ 


#ifndef PID_CONTROLLER_H_
#define PID_CONTROLLER_H_


/*
 * PID_controller.c
 *
 * Created: 15/11/2022 13:59:09
 *  Author: danie
 */
#include "PID_controller.h"
#include "sam.h"



extern uint16_t motorpos, target, output;

void TC0_Handler();

void pid_init(void);

uint16_t PID_calc(uint16_t input, uint16_t target);


#endif /* PID_CONTROLLER_H_ */