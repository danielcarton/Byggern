/*
 * SPI_control.c
 *
 * Created: 06/10/2022 12:59:02
 *  Author: danie
 */ 
#include <avr/io.h>


#define set_bit( reg, bit ) (reg |= (1 << bit))


void SPI_Init(void)
{
	/* Set MOSI and SCK output, all others input */
	DDRB = (1<<PB4)|(1<<PB5)|(1<<PB7);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	
	set_bit(PORTB, PB4);
}

void SPI_Transmit(char Data)
{
	/* Start transmission */
	SPDR = Data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)))
	;
}