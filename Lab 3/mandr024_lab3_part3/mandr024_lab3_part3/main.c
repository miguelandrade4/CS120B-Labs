/*
 * mandr024_lab3_part3.c
 *
 * Created: 8/2/2018 3:40:21 PM
 * Author : Miguel
 */ 

#include <avr/io.h>

enum States{START, INIT, ONE, TWO, THREE, LOCK, UNLOCKED} STATES;

unsigned char key = 0x00;
unsigned char tempNum = 0x00;
unsigned char valueDis = 0x00;

unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}


void tick()
{
	switch(STATES)
	{
		case START:
			STATES = INIT;
		break;
		
		case INIT:
			if(GetBit(tempNum,0) && !GetBit(tempNum,1) && !GetBit(tempNum,2) && !GetBit(tempNum,7))
			{
				STATES = ONE;
			}
			
			else if(!GetBit(tempNum,0) && GetBit(tempNum,1) && !GetBit(tempNum,2) && !GetBit(tempNum,7))
			{
				STATES = TWO;
				if(key)
				{
					valueDis = 0x01;
					STATES = UNLOCKED;
				}
			}
			
			else if(!GetBit(tempNum,0) && !GetBit(tempNum,1) && GetBit(tempNum,2) && !GetBit(tempNum,7))
			{
				STATES = THREE;
				key = 0x01;
			
			}
			
			else if(!GetBit(tempNum,0) && !GetBit(tempNum,1) && !GetBit(tempNum,2) && GetBit(tempNum,7))
			{
				STATES = LOCK;
			}
			
			else
			{
				STATES = INIT;
			}
			
		break;
		
		case ONE:
			if(GetBit(tempNum,0) && !GetBit(tempNum,1) && !GetBit(tempNum,2) && !GetBit(tempNum,7))
			{
				STATES = ONE;
			}
		
			else if(!GetBit(tempNum,0) && GetBit(tempNum,1) && !GetBit(tempNum,2) && !GetBit(tempNum,7))
			{
				STATES = TWO;
			}
		
			else if(!GetBit(tempNum,0) && !GetBit(tempNum,1) && GetBit(tempNum,2) && !GetBit(tempNum,7))
			{
				STATES = THREE;
				key = 0x01;
			}
		
			else if(!GetBit(tempNum,0) && !GetBit(tempNum,1) && !GetBit(tempNum,2) && GetBit(tempNum,7))
			{
				STATES = LOCK;
				valueDis = 0x00;
			}
		
			else
			{
				STATES = INIT;
			}
		
		break;
		
		case TWO:
			if(GetBit(tempNum,0) && !GetBit(tempNum,1) && !GetBit(tempNum,2) && !GetBit(tempNum,7))
			{
				STATES = ONE;
			}
		
			else if(!GetBit(tempNum,0) && GetBit(tempNum,1) && !GetBit(tempNum,2) && !GetBit(tempNum,7))
			{
				STATES = TWO;
			}
		
			else if(!GetBit(tempNum,0) && !GetBit(tempNum,1) && GetBit(tempNum,2) && !GetBit(tempNum,7))
			{
				STATES = THREE;
				key = 0x01;
			}
		
			else if(!GetBit(tempNum,0) && !GetBit(tempNum,1) && !GetBit(tempNum,2) && GetBit(tempNum,7))
			{
				STATES = LOCK;
				valueDis = 0x00;
			}
		
			else
			{
				STATES = INIT;
			}
		
		break;
		
		case THREE:
			if(GetBit(tempNum,0) && !GetBit(tempNum,1) && !GetBit(tempNum,2) && !GetBit(tempNum,7))
			{
				STATES = ONE;
			}
		
			else if(!GetBit(tempNum,0) && GetBit(tempNum,1) && !GetBit(tempNum,2) && !GetBit(tempNum,7))
			{
				STATES = TWO;
			}
		
			else if(!GetBit(tempNum,0) && !GetBit(tempNum,1) && GetBit(tempNum,2) && !GetBit(tempNum,7))
			{
				STATES = THREE;
				key = 0x01;
			}
		
			else if(!GetBit(tempNum,0) && !GetBit(tempNum,1) && !GetBit(tempNum,2) && GetBit(tempNum,7))
			{
				STATES = LOCK;
				valueDis = 0x00;
			}
		
			else
			{
				STATES = INIT;
			}
		
		break;
		
		case LOCK:
			STATES = INIT;
			break;
			
		case UNLOCKED:
			if(GetBit(tempNum, 7))
			{
				STATES = LOCK;
				valueDis = 0x00;
			}
			break;
			
		default:
			STATES = START;
		
	}
	
	switch(STATES)
	{
		case START:
			PORTB = valueDis;
		break;
		
		case INIT:
			PORTB = valueDis;
		break;
		
		case ONE:
			PORTB = valueDis;
		break;
		
		case TWO:
			PORTB = valueDis;
		break;
		
		case THREE:
			PORTB = valueDis;
		break;
		
		case LOCK:
			PORTB = valueDis;
		break;
		
		case UNLOCKED:
			PORTB = valueDis;
		break;
	}
	
}

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
	
	STATES = START;
	
    while (1) 
    {
		tempNum = PINA;
		tick();
    }
}

