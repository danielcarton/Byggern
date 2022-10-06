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

	
#ifndef ADC_ADDRESS
#define ADC_ADDRESS 0x1400
#endif

volatile char *ADC = (int) 0x1400; // Start address for the ADC

volatile int joyy;
volatile int joyx;
volatile int sliderRight;
volatile int sliderLeft;

volatile int button1State;
volatile int button2State;
volatile int button3State;
uint64_t intermittenty=0;
uint64_t intermittentx=0;
int middleyjoyy;
int middleyjoyx;

volatile char ADC_data;

ISR (TIMER1_OVF_vect){
	ADC[0x00] = 0x00;
	_delay_ms(1);
	joyy=ADC[0x00];
	joyx=ADC[0x00];
	sliderRight = ADC[0x00];
	sliderLeft = ADC[0x00];
	
	button1State = 0 != (PIND & (1<<PD2)); 
	button2State = 0 != (PIND & (1<<PD3));
	button3State = 1 != (0 != (PIND & (1<<PD5))); 
	
	

}


void joy_calibrate(void){
	for (int i = 0; i<1000; i++)
	{
		intermittentx += joyx;
		intermittenty += joyy;
		_delay_ms(1);
	}
	middleyjoyx = intermittentx/1000;
	middleyjoyy = intermittenty/1000;
	printf("\n\n%d %d \n", middleyjoyx, middleyjoyy);
}


void adc_init(int *counter){
    TCCR3A = (1 << WGM30) | (1 << WGM31) | (1 << COM3A0);
    TCCR3B = (1 << CS30) | (1 << WGM33);
    OCR3A = 2; // Define the frequency of the generated PWM signal
    DDRD |= (1 << DDD4); // Configure PD4 as PWM output
	
	
	TCCR1A = 0x00;
	TCCR1B =  (1<<CS11);
	TIMSK = (1 << TOIE1);   
	sei(); 
	
	ADC[0x00] = 0x00;
	//INITIALIZE INTERRUPT ON PIN PD3

	//// button input
	//clear_bit(ddrd, pd3);
	//set_bit(portd, pd3);	//set pull-up resistor
	//// disable global interrupts
	//cli();
	//// interrupt on falling edge pd3
	//set_bit(mcucr, isc11);
	//clear_bit(mcucr, isc10);
	//// enable interrupt on pd3
	//set_bit(gicr,int1);
	//// enable global interrupts
	//sei();


}

ISR(INT1_vect){
	
	ADC_data = ADC[0x00];
}

char get_ADC_data(void){
	return ADC[0x00];
}

void ADC_start_read(void){
	
	char data = 0x00;
	ADC[0x00] = data;
	
}


