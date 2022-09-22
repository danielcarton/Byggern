#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>


#define set_bit( reg, bit ) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))
#define test_bit( reg, bit ) (reg & (1 << bit))
#define loop_until_bit_is_set( reg, bit ) while( !test_bit( reg, bit ) )
#define loop_until_bit_is_clear( reg, bit ) while( test_bit( reg, bit ) )
#define toggle_bit(reg, bit) (reg ^= (1 << bit))


typedef enum {CHANNEL1, CHANNEL2, CHANNEL3, CHANNEL4} channel_t;
	
#ifndef ADC_ADDRESS
#define ADC_ADDRESS 0x1400
#endif

volatile char *ADC = (int) 0x1400; // Start address for the ADC
volatile char ADC_data;

void adc_init(int *counter){
    TCCR3A = (1 << WGM30) | (1 << WGM31) | (1 << COM3A0);
    TCCR3B = (1 << CS30) | (1 << WGM33);
    OCR3A = 2; // Define the frequency of the generated PWM signal
    DDRD |= (1 << DDD4); // Configure PD4 as PWM output
	
	//INITIALIZE INTERRUPT ON PIN PD3

	// Button input
	clear_bit(DDRD, PD3);
	set_bit(PORTD, PD3);	//Set pull-up resistor
	// Disable global interrupts
	cli();
	// Interrupt on falling edge PD3
	set_bit(MCUCR, ISC11);
	clear_bit(MCUCR, ISC10);
	// Enable interrupt on PD3
	set_bit(GICR,INT1);
	// Enable global interrupts
	sei();


}

ISR(INT1_vect){
	
	ADC_data = ADC[0x00];
}

char get_ADC_data(void){
	return ADC_data;
}

void ADC_start_read(channel_t channel){
	
	char data = 0x00;
	
	switch (channel) {
		case CHANNEL1 :
		data = 0x04;
		break;
		case CHANNEL2 :
		data = 0x05;
		break;
		case CHANNEL3 :
		data = 0x06;
		break;
		case CHANNEL4 :
		data = 0x07;
		break;
		default:
		printf("Not valid channel");
		return EXIT_FAILURE;
	}
	
	ADC[0x00] = data;
	
}


