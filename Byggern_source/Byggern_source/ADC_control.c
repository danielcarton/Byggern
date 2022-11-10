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

volatile uint8_t button1State;
volatile uint8_t button2State;
volatile uint8_t button3State;

int intermittenty=0;
int intermittentx=0;

int middleyjoyy;
int middleyjoyx;

volatile int joyxPercent;
volatile int joyyPercent;


float posXfactor;
float posXadd;
float negXfactor;
float negXadd;
float posYfactor;
float posYadd;
float negYfactor;
float negYadd;

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
	
	if (joyy < middleyjoyy)
	{
		joyyPercent = joyy*negYfactor/100+negYadd;
	}
	if (joyy >= middleyjoyy)
	{
		joyyPercent = joyy*posYfactor/100+posYadd;
	}
	if (joyx < middleyjoyx)
	{
		joyxPercent = joyx*negXfactor/100+negXadd;
	}
	if (joyx >= middleyjoyx)
	{
		joyxPercent = joyx*posXfactor/100+posXadd;
	}	
	if (joyxPercent > -5 && joyxPercent < 5)
	{
		joyxPercent = 0;
	}
	if (joyyPercent > -5 && joyyPercent < 5)
	{
		joyyPercent = 0;
	}

}





void adc_init(){
    TCCR3A = (1 << WGM30) | (1 << WGM31) | (1 << COM3A0);
    TCCR3B = (1 << CS30) | (1 << WGM33);
    OCR3A = 2; // Define the frequency of the generated PWM signal
    DDRD |= (1 << DDD4); // Configure PD4 as PWM output
	
	
	_delay_ms(10);
	int times = 0;
	int ignore;
	for (int i = 0; i<100; i++)
	{
		ADC[0x00] = 0x00;
		_delay_ms(1);
		intermittentx = intermittentx + ADC[0x00];
		intermittenty = intermittenty + ADC[0x00];
		ignore = ADC[0x00];
		ignore = ADC[0x00];
		_delay_ms(1);
		times++;
	}
	middleyjoyx = intermittentx/times;
	middleyjoyy = intermittenty/times;
	printf("\n\n\r %d %d \n", middleyjoyx, middleyjoyy);
	
	posXfactor = (10000)/(255-middleyjoyx);
	posXadd = -1*(100*middleyjoyx)/(255-middleyjoyx);
	negXfactor = (10000/middleyjoyx);
	negXadd = -1*(middleyjoyx*100)/(middleyjoyx);
	posYfactor = (10000)/(255-middleyjoyy);
	posYadd= -1*(100*middleyjoyy)/(255-middleyjoyy);
	negYfactor = (10000/middleyjoyy);
	negYadd = -1*(middleyjoyy*100)/(middleyjoyy);
	printf("Pos x: %d*x + %d\n\r", (int)(posXfactor*1000), (int)posXadd);
	printf("Neg x: %d*x + %d\n\r", (int)(negXfactor*1000), (int)negXadd);
	printf("Pos y: %d*y + %d\n\r", (int)(posYfactor*1000), (int)posYadd);
	printf("Neg y: %d*y + %d\n\r", (int)(negYfactor*1000), (int)negYadd);
	
	cli();
	TCCR1A = 0x00;
	TCCR1B =  (1<<CS11);
	TIMSK = (1 << TOIE1);   
	sei(); 
	
	ADC[0x00] = 0x00;


}

char get_ADC_data(void){
	return ADC[0x00];
}

void ADC_start_read(void){
	
	char data = 0x00;
	ADC[0x00] = data;
	
}


