/*
 * mandr024_lab6_part 1.c
 *
 * Created: 8/13/2018 1:02:46 PM
 * Author : Miguel
 */ 

#include <avr/io.h>
#include "io.c"
#include <avr/interrupt.h>


enum States{SM2_START, SM2_INIT, SM2_ONE, SM2_TWO, SM2_DEPRESSED} SM2_STATES;
unsigned char tempVal = 0x00;
unsigned char tempNum = 0x00;
unsigned char timeChk = 0x00;
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



void tick()
{
	switch(SM2_STATES)  // transitions
	{
		case SM2_START:
			
			SM2_STATES = SM2_INIT;
			
		break;
		
		case SM2_INIT:
			if(tempVal == 1)
			{
				if(tempNum < 9)
				{
					tempNum++;
				}
				
				timeChk = 0;
				SM2_STATES = SM2_ONE;
			}
		
			else if(tempVal == 0)
			{
				SM2_STATES = SM2_INIT;
			}
		
			else if(tempVal == 2)
			{
				if(tempNum > 0)
				{
					tempNum--;
				}
			
				else
				{
					tempNum = 0;
				}
				
				timeChk = 0;
				SM2_STATES = SM2_TWO;
			}
		
			else
			{
				tempNum = 0x00;
				SM2_STATES = SM2_DEPRESSED;
			}
		break;
		
		case SM2_ONE:
			if(tempVal == 1 && timeChk < 1)
			{
				SM2_STATES = SM2_ONE;
			}
			
			else if(tempVal == 1 && timeChk == 1) 
			{
				if(tempNum < 9)
				{
					tempNum++;
				}
				timeChk = 0;
				SM2_STATES = SM2_ONE;
			}
		
			if (tempVal == 3)
			{
				timeChk = 0;
				tempNum = 0x00;
				SM2_STATES = SM2_DEPRESSED;
			
			}
		
			else
			{
				timeChk = 0;
				SM2_STATES = SM2_INIT;
			
			}
		
		break;
		
		case SM2_TWO:
			if(tempVal == 2 && timeChk < 1)
			{
				SM2_STATES = SM2_TWO;
			}

			else if(tempVal == 2 && timeChk == 1)
			{
				if(tempNum > 0)
				{
					tempNum--;
				}
				else
				{
					tempNum = 0;
				}
				
				timeChk = 0;
				SM2_STATES = SM2_TWO;
			}		
			
			else if (tempVal == 3)
			{
				timeChk = 0;
				tempNum = 0x00;
				SM2_STATES = SM2_DEPRESSED;
			}
		
			else
			{
				timeChk = 0;
				SM2_STATES = SM2_INIT;
			}
		
		break;
		
		case SM2_DEPRESSED:
// 			if (tempVal == 3 || (tempVal == 1 || tempVal == 2))
// 			{
// 				SM2_STATES = SM2_DEPRESSED;
// 			}
// 		
// 			else
// 			{
				timeChk = 0;
				SM2_STATES = SM2_INIT;
			//}
		
		break;
		
		default:
		SM2_STATES = SM2_START;
	}
	
	switch(SM2_STATES) //Actions
	{
		case SM2_START:
		LCD_Cursor(1);
		LCD_WriteData(tempNum + '0');
		break;
		case SM2_INIT:
		LCD_Cursor(1);
		LCD_WriteData(tempNum + '0');
		break;
		case SM2_ONE:
		timeChk++;
		LCD_Cursor(1);
		LCD_WriteData(tempNum + '0');
		break;
		case SM2_TWO:
		timeChk++;
		LCD_Cursor(1);
		LCD_WriteData(tempNum + '0');
		break;
		case SM2_DEPRESSED:
			tempNum = 0;
			LCD_ClearScreen();
			LCD_Cursor(1);
			LCD_WriteData(tempNum + '0');
		break;
	}
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00; // LCD data lines
	DDRD = 0xFF; PORTD = 0x00; // LCD control lines
	tempNum = 0x00 & 0x0F;
	
		TimerSet(125);
		TimerOn();
		
		LCD_init();
		LCD_ClearScreen();
	
	SM2_STATES = SM2_START;
	
	while (1)
	{
		tempVal = ~PINA & 0x03;
		tick();
		while (!TimerFlag);
		TimerFlag = 0;
	}
}

