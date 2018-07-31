/*
 * mandr024_lab1_Challenge.c
 *
 * Created: 7/31/2018 12:25:48 PM
 * Author : Miguel
 */ 

#include <avr/io.h>
#define range 84

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0x00; PORTC = 0xFF; // Configure port C's 8 pins as inputs
	DDRD = 0xFF; PORTD = 0x00;
	
	unsigned char tempA;
	unsigned char tempB;
	unsigned char tempC;
	unsigned short tempNum;
	unsigned short tempNumTwo;
    /* Replace with your application code */
    while (1) 
    {
		tempA = PINA;
		tempB = PINB;
		tempC = PINC;
		
		tempNumTwo = tempA + tempB + tempC;
		
		tempNum = tempA - tempC;
		
		tempNum = abs(tempNum);
		
		if( tempNumTwo >= 140)
		{
			if(tempNum >= 80)
			{
				PORTD = 0x02;
			}
			
			else
			{
				PORTD = 0x01;
			}
				
		}
		
		if( tempNumTwo > 255 && tempNumTwo < 339) //range of 84 for 1 bit each estimate quick and easy
		{
			PORTD = 0x04;
		}
		else if( tempNumTwo > 339 && tempNumTwo < 423)
		{
			PORTD = 0x08;
		}
		else if( tempNumTwo > 423 && tempNumTwo < 507)
		{
			PORTD = 0x10;
		}
		else if( tempNumTwo > 507 && tempNumTwo < 591)
		{
			PORTD = 0x20;
		}
		else if( tempNumTwo > 591 && tempNumTwo < 675)
		{
			PORTD = 0x40;
		}
		else if( tempNumTwo > 675 && tempNumTwo < 765) // not 84 range but to accommodate
		{
			PORTD = 0x80;
		}
    }
}

