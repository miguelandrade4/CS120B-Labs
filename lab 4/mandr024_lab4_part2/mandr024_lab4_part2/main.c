/*
 * mandr024_lab4_part2.c
 *
 * Created: 8/7/2018 11:46:05 AM
 * Author : Miguel
 */ 

#include <avr/io.h>

enum States{SM2_START, SM2_INIT, SM2_ONE, SM2_TWO, SM2_DEPRESSED} SM2_STATES;
unsigned char tempVal;
unsigned char tempNum;


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
			SM2_STATES = SM2_ONE;
		}
		
		else if(!tempVal)
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
			
			SM2_STATES = SM2_TWO;
		}
		
		else
		{
			tempNum = 0x00;
			SM2_STATES = SM2_DEPRESSED;
		}
		break;
		
		case SM2_ONE:
		if(tempVal == 1)
		{
			SM2_STATES = SM2_ONE;
		}
		
		else if (tempVal == 3)
		{
			tempNum = 0x00;
			SM2_STATES = SM2_DEPRESSED;
			
		}
		
		else
		{
			SM2_STATES = SM2_INIT;
			
		}
		
		break;
		
		case SM2_TWO:
		if(tempVal == 2)
		{
			SM2_STATES = SM2_TWO;
		}
		
		else if (tempVal == 3)
		{
			tempNum = 0x00;
			SM2_STATES = SM2_DEPRESSED;
		}
		
		else
		{
			SM2_STATES = SM2_INIT;
			
		}
		
		break;
		
		case SM2_DEPRESSED:
		if (tempVal == 3 || (tempVal == 1 || tempVal == 2))
		{
			SM2_STATES = SM2_DEPRESSED;
		}
		
		else 
		{
			SM2_STATES = SM2_INIT;
		}
		
		break;
		
		default:
		SM2_STATES = SM2_START;
	}
	
	switch(SM2_STATES) //Actions
	{
		case SM2_START:
		PORTB = tempNum;
		break;
		case SM2_INIT:
		PORTB = tempNum;
		break;
		case SM2_ONE:
		PORTB = tempNum;
		break;
		case SM2_TWO:
		PORTB = tempNum;
		break;
		case SM2_DEPRESSED:
		PORTB = 0x00;
		break;
	}
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	tempNum = 0x07 & 0x0F;
	
	SM2_STATES = SM2_START;
	
	while (1)
	{
		tempVal = ~PINA & 0x03;
		tick();
	}
}
