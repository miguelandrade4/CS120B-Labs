/*
 * mandr024_lab4_challenge.c
 *
 * Created: 8/7/2018 12:48:13 PM
 * Author : Miguel
 */ 

#include <avr/io.h>

enum STATES{START, INIT, WAIT, ONE, TWO, THREE, FOUR, RESET} lightShow;
	
	unsigned char tempNum = 0x00;
	unsigned char tempVal = 0x00;
	unsigned char countChk = 0x00; 
	unsigned char checkState = 0x00;
	unsigned char halo = 0x00;
	
	
void tick()
{
	switch(lightShow)
	{
		case START:
			tempNum = 0xFF;
			lightShow = INIT;
		break;
		
		case INIT:
			if (tempVal && countChk == 0)
			{
				++countChk;
				tempNum = 0x55;
				lightShow = ONE;
			}
			
			else if (tempVal && countChk == 1)
			{
				++countChk;
				tempNum = 0xAA;
				lightShow = TWO;
			}
			
			else if (tempVal && countChk == 2)
			{
				++countChk;
				tempNum = 1;
				checkState = 0;
				lightShow = THREE;
			}
			
			else if (tempVal && countChk == 3)
			{
				++countChk;
				checkState = 0;
				tempNum = 0x80;
				lightShow = FOUR;
			}
			
			else if (countChk == 4)
			{
				
				lightShow = RESET;
			}
		break;
			
		case WAIT:
				if(tempVal && halo)
				{
					tempNum = tempNum<<2;
					++tempNum;
					++checkState;
					lightShow = THREE;
				}
				
				else if (tempVal && !halo)
				{
					tempNum = tempNum>>2;
					tempNum += 0x80;
					++checkState;
					lightShow = FOUR;
				}
		break; 	
			
		case ONE:
			if (tempVal)
			{
				lightShow = ONE;
			}
			
			else
			{
				lightShow = INIT;
			}
			
		break;	
		
		case TWO:
			if (tempVal)
			{
				
				lightShow = TWO;
			}
		
			else
			{
				lightShow = INIT;
			}
		
		break;
			
		case THREE:
			if(tempVal && checkState != 4)
			{
				lightShow = THREE;
			}
			
			else if (!tempVal && checkState != 4)
			{
				halo = 1;
				lightShow = WAIT;
			}
			
			else if(tempVal  && checkState == 4)
			{
				halo = 0;
				checkState = 0;
				lightShow = INIT;
			}
		break;
			
		case FOUR:
			if(tempVal && checkState != 4)
			{
				lightShow = FOUR;
			}
		
			else if (!tempVal && checkState != 4)
			{
				halo = 0;
				lightShow = WAIT;
			}
		
			else if(tempVal  && checkState == 4)
			{
				halo = 0;
				checkState = 0;
				lightShow = INIT;
			}
		break;
		
		case RESET:
			if (tempVal)
			{
				tempNum = 0xFF;
				lightShow = RESET;
			}
			
			else
			{
				lightShow = INIT;
			}
		break;
		
		default:
			lightShow = START;
		break;
	}
	
	switch(lightShow) //Actions
	{
		case START:
		PORTB = tempNum;
		break;
		case INIT:
		PORTB = tempNum;
		break;
		case WAIT:
		PORTB = tempNum;
		break;
		case ONE:
		PORTB = tempNum;
		break;
		case TWO:
		PORTB = tempNum;
		break;
		case THREE:
		PORTB = tempNum;
		break;
		case FOUR:
		PORTB = tempNum;
		break;
		case RESET:
		countChk = 0;
		PORTB = tempNum;
		break;
	}
}

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	lightShow = START;
	
	PORTB = 0xFF;
	
    while (1) 
    {
		tempVal = ~PINA & 0x01;
		tick();
    }
}

