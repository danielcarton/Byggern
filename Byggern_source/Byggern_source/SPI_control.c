/*
 * SPI_control.c
 *
 * Created: 06/10/2022 12:59:02
 *  Author: danie
 */ 
#include <avr/io.h>



void SPI_Init(void)
{
	DDRB = (1<<PB4)|(1<<PB5)|(1<<PB7);
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	PORTB = (1<<PB4);
}

void SPI_Transmit(char Data)
{
	SPDR = Data;
	while(!(SPSR & (1<<SPIF)));
}


char SPI_Recieve(void)
{
	SPDR = 0x00;
	while(!(SPSR & (1<<SPIF)));
	return(SPDR);
}

void SPI_test(uint8_t Test_data){
	printf("Testing SPI...\n\r");
	printf("5\n\r");
	_delay_ms(1000);
	printf("4\n\r");
	_delay_ms(1000);
	printf("3\n\r");
	_delay_ms(1000);
	printf("2\n\r");
	_delay_ms(1000);
	printf("1\n\r");
	_delay_ms(1000);
	PORTB = (0<<PB4);
	SPI_Transmit(Test_data);
	printf("Test Data Transmitted!\n\r");
	printf("%c\n\r", SPDR);
	PORTB = (1<<PB4);
}