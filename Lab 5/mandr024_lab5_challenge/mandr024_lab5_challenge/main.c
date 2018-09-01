/*
 * mandr024_lab5_challenge.c
 *
 * Created: 8/8/2018 1:31:14 PM
 * Author : Miguel
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

enum Sys_States {Sys_INIT,Sys_s0,Sys_s1,Sys_s2,Sys_wait} Sys_States;

unsigned char B = 0x00;
unsigned char A1new = 0x00;
unsigned char A1old = 0x00;

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn()
{
	TCCR1B = 0x0B;
	
	OCR1A = 125;
	
	TIMSK1 = 0x02;
	
	TCNT1 = 0;
	
	_avr_timer_cntcurr = _avr_timer_M;
	
	SREG |= 0x80;
}

void TimerOff()
{
	TCCR1B = 0x00;
}

void TimerISR()
{
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect)
{
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0)
	{
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M)
{
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void tick()
{
	A1new = ~PINA & 0x01;
	
	switch(Sys_States)
	{
		case Sys_INIT:
		if ((A1new == 1) & (A1old == 0))
		{
			Sys_States = Sys_wait;
		}
		else if((A1new == 1) & (A1old == 1))
		{
			Sys_States = Sys_INIT;
		}
		else
		{
			Sys_States = Sys_s0;
		}
		break;
		case Sys_s0:
		if ((A1new == 1) & (A1old == 0))
		{
			Sys_States = Sys_wait;
		}
		else
		{
			Sys_States = Sys_s1;
		}
		break;
		case Sys_s1:
		if ((A1new == 1) & (A1old == 0))
		{
			Sys_States = Sys_wait;
		}
		else
		{
			Sys_States = Sys_s2;
		}
		break;
		case Sys_s2:
		if ((A1new == 1) & (A1old == 0))
		{
			Sys_States = Sys_wait;
		}
		else
		{
			Sys_States = Sys_s0;
		}
		break;
		case Sys_wait:
		if ((A1new == 1) & (A1old == 0))
		{
			Sys_States = Sys_INIT;
		}
		else
		{
			Sys_States = Sys_wait;
		}
		break;
		default:
		break;
	}
	
	switch(Sys_States)
	{
		case Sys_INIT:
		B = 0x00;
		A1old = A1new;
		break;
		case Sys_s0:
		B = 0x01;
		A1old = A1new;
		break;
		case Sys_s1:
		B = 0x02;
		A1old = A1new;
		break;
		case Sys_s2:
		B = 0x04;
		A1old = A1new;
		break;
		case Sys_wait:
		A1old = A1new;
		break;
		default:
		break;
	}
	PORTB = B;
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	TimerSet(300);
	TimerOn();

	while(1)
	{
		tick();
		while (!TimerFlag);
		TimerFlag = 0;
	}
}


