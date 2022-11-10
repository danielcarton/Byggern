/*
 * Solenoid.c
 *
 * Created: 10.11.2022 13:15:45
 *  Author: tobialie
 */ 
#include "sam.h"

void solenoid_init(void)
{
	PIOD -> PIO_PER |= PIO_PDR_P3; // disable PIO control of pin 28
	PIOD -> PIO_OER |= PIO_OER_P3; // enable output on pin 28
	PIOD -> PIO_PUDR |= PIO_PUDR_P3; // disable pullup on pin 28
}

void solenoid_push(void)
{
	 PIOD -> PIO_SODR |= PIO_SODR_P3; 
}

void solenoid_notpush(void)
{
	PIOD -> PIO_CODR |= PIO_CODR_P3;
}