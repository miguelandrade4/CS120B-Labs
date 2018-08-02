/*
 * mandr024_lab3_part1.c
 *
 * Created: 8/1/2018 10:39:46 PM
 * Author : Miguel
 */ 

#include <avr/io.h>

enum States{SM1_START, SM1_INIT, SM1_INIT_PRESS} SM1_STATES;
unsigned char porA;

void tick()
{	
	switch (SM1_STATES)
	{
		case SM1_START:
			SM1_STATES = SM1_INIT;
			break;
		
		case SM1_INIT:
			if(porA)
			{
				SM1_STATES = SM1_INIT_PRESS;
			}
		
			else
			{
				SM1_STATES = SM1_INIT;
			}
		
			break;
		
		case SM1_INIT_PRESS:
			if(porA)
			{
				SM1_STATES = SM1_INIT;
			}
		
			else
			{
				SM1_STATES = SM1_INIT_PRESS;
			}
		
			break;
		
		default:
			SM1_STATES = SM1_START;
			break;
	}
	
	switch (SM1_STATES)
	{
		case SM1_INIT:
			PORTB = 0x01;
			break;
		case SM1_INIT_PRESS:
			PORTB = 0x02;
			break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Replace with your application code */
    while (1) 
    {
		porA = PINA & 0x01;
		tick();
    }
}

