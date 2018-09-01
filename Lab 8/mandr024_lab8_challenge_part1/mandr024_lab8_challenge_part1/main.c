/*
 * mandr024_lab8_challenge_part1.c
 *
 * Created: 8/16/2018 12:06:32 PM
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

void TimerOn() {
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}
void TimerOff() {
	TCCR1B = 0x00;
}
void TimerISR() {
	TimerFlag = 1;
}
ISR(TIMER1_COMPA_vect) {
	
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0) {
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

int main(void)
{
	unsigned char x = 0x00;
	unsigned char i = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	TimerSet(2000);
	TimerOn();

	ADC_init();
	
	while(1)
	{
		x = ADC ;
// 		
// 		x = x>>2;
// 		
// 		if (x = 0x08)
// 		{
// 			PORTB = x = x>>3;
;
// 		}
// 		
// 		else if (x == )
// 		{
// 			PORTB = 0x7F;
// 		}
// 		
// 		else if (x == )
// 		{
// 			PORTB = 0x3F;
// 		}
// 		
// 		else if (x == )
// 		{
// 			PORTB = 0x1F;
// 		}
// 		
// 		else if (x ==)
// 		{
// 			PORTB = 0x07;
// 		}
// 		
// 		else if (x == )
// 		{
// 			PORTB = 0x03;
// 		}
// 		
// 		else if (x <=   )
// 		{
// 			PORTB = 0x01;
// 		}
// 		
// 		else if (x >= 0xFF)
// 		{
// 			PORTB = 0x00;
// 		}

		PORTB = x & 0xFF;

// 		PORTD = x & 0x03;
	}
}