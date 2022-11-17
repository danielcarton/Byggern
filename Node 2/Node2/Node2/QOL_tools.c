/*
 * QOL_tools.c
 *
 * Created: 08/11/2022 13:19:12
 *  Author: danie
 */ 
#include "sam.h"
#include "QOL_tools.h"
#define F_CPU 84000000L

void delay(uint16_t mills) {
	for (int t=0; t<mills*(F_CPU/1000); t++){
		asm("nop");
	}
	}