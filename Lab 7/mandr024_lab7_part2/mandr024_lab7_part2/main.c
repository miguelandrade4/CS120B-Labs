/*
 * mandr024_lab7_part2.c
 *
 * Created: 8/14/2018 2:59:30 PM
 * Author : Miguel
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

enum SM1_STATES{TL_START, TL_INIT, TL_LED_ON} TL_STATES;

enum SM2_STATES{BL_START, BL_INIT, BL_ON, } BL_STATES;

enum SM3_STATES{AL_START, AL_INIT, AL_ON, } AL_STATES;

unsigned char tempVal = 0x00;
unsigned char blinkVal = 0x00;
unsigned char addVal = 0x00;
unsigned char count = 0x00;
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

void ThreeLEDS()
{
	switch(TL_STATES)
	{
		case TL_START:
		tempVal = 1;
		TL_STATES = TL_INIT;
		break;
		
		case TL_INIT:
		if(count < 3)
		{
			tempVal = tempVal<<1;
			TL_STATES = TL_LED_ON;
		}
		
		else
		{
			tempVal = 1;
			TL_STATES = TL_LED_ON;
			count = 0;
		}
		break;
		
		case TL_LED_ON:
		if(count < 3)
		{
			tempVal = tempVal<<1;
			TL_STATES = TL_INIT;
		}
		
		else
		{
			tempVal = 1;
			TL_STATES = TL_INIT;
			count = 0;
		}
		break;
		
		default:
		TL_STATES = TL_START;
	}
	
	switch(TL_STATES)
	{
		case TL_START:
		break;
		case TL_INIT:
		count++;
		break;
		case TL_LED_ON:
		count++;
		break;
	}
	
}

void BlinkingLEDS()
{
	switch(BL_STATES)
	{
		case BL_START:
		blinkVal = 0;
		BL_STATES = BL_INIT;
		break;
		
		case BL_INIT:
		BL_STATES = BL_ON;
		
		break;
		
		case BL_ON:
		blinkVal = 0x08;
		BL_STATES = BL_INIT;
		break;
		
		default:
		BL_STATES = BL_START;
	}
	
	switch(BL_STATES)
	{
		case BL_START:
		blinkVal = 0x00;
		break;
		case BL_INIT:
		break;
		case BL_ON:
		blinkVal = 0x00;
		break;
	}
	
}

void AddLEDS()
{
	switch(AL_STATES)
	{
		case AL_START:
		addVal = 0x00;
		AL_STATES = AL_INIT;
		break;
		
		case AL_INIT:
		addVal = blinkVal + tempVal;
		AL_STATES = AL_ON;
		break;
		
		case AL_ON:
		addVal = blinkVal + tempVal;
		AL_STATES = AL_INIT;
		break;
		
		default:
		AL_STATES = AL_START;
	}
	
	switch(AL_STATES)
	{
		case AL_START:
		PORTB = 0x00;
		break;
		case AL_INIT:
		PORTB = addVal;
		break;
		case AL_ON:
		PORTB = addVal;
		break;
	}
	
}

int main(void)
{
	DDRB = 0xFF; PORTB = 0x00;
	//unsigned char i = 0x00;
	unsigned char TL_elapsedTime = 0x00;
	//const unsigned long timerPeriod = 50;
	
	TimerSet(50);
	TimerOn();
	
	TL_STATES = TL_START;
	BL_STATES = BL_START;
	AL_STATES = AL_START;
	
	while (1)
	{
		
		ThreeLEDS();
		if (TL_elapsedTime >= 150)
		{
			BlinkingLEDS();
			TL_elapsedTime = 0;
		}
		AddLEDS();
		
		
		while(!TimerFlag);
		TimerFlag = 0;
		TL_elapsedTime += 50;
	}
	
}