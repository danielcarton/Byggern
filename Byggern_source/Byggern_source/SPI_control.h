/*
 * SPI_control.h
 *
 * Created: 06/10/2022 12:59:18
 *  Author: danie
 */ 


#ifndef SPI_CONTROL_H_
#define SPI_CONTROL_H_


void SPI_Init(void);

void SPI_Transmit(char Data);

char SPI_Recieve(void);

void SPI_test(uint8_t Test_data);


#endif /* SPI_CONTROL_H_ */