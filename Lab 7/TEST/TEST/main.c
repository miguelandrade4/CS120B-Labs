/*
 * TEST.c
 *
 * Created: 8/14/2018 4:19:39 PM
 * Author : Miguel
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

enum SM4_STATES{SO_START, SO_INIT, SO_OFF} SO_STATES;
unsigned char soundVal = 0x00;
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

void soundON()
{
	switch(SO_STATES)
	{
		case SO_START:
		SO_STATES = SO_INIT;
		break;
		case SO_INIT:
		if (PINA == 0x01)
		{
			soundVal = 0x10;
			SO_STATES = SO_OFF;
		}
		
		else
		{
			soundVal = 0x00;
			SO_STATES = SO_INIT;
		}
		break;
		case SO_OFF:
		if (PINA == 0x01)
		{
			soundVal = 0x10;
			SO_STATES = SO_OFF;
		}
		
		else
		{
			soundVal = 0x00;
			SO_STATES = SO_INIT;
		}
		break;
		
		default:
		SO_STATES = SO_START;
	}
	
	switch(SO_STATES)
	{
		case SO_START:
		PORTB = 0x00;
		break;
		
		case SO_INIT:
		PORTB = soundVal;
		break;
		
		case SO_OFF:
		PORTB = soundVal;
		break;
	}
}

int main(void)
{
    TimerSet(2);
    TimerOn();
	while (1) 
    {
		soundON();
		
		while(!TimerFlag);
		TimerFlag = 0;
    }
}

