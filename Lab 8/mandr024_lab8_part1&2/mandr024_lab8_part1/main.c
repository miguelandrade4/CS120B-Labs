/*
 * mandr024_lab8_part1.c
 *
 * Created: 8/15/2018 1:24:04 PM
 * Author : Miguel
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}
volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;


int main(void)
{
	unsigned short my_short = 0xABCD;
	unsigned char x = (char) my_short;
	unsigned char B = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	

	ADC_init();
		
	while(1)
	{	
		my_short = ADC;
		x = (char) my_short;
		B = (char) (my_short>>8);
		PORTB = x; 
		PORTD = B & 0x03;
// 		
		
	}
}