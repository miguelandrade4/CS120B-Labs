/*
 * mandr024_lab2_part1.c
 *
 * Created: 7/31/2018 2:29:58 PM
 * Author : Miguel
 */ 

#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as inputs,
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs
	
	unsigned char tempCount = 0x00;
	unsigned char tempA = 0x00;
	unsigned char tempB = 0x00;
	
	
	unsigned char GetBit(unsigned char x, unsigned char k) {
		return ((x & (0x01 << k)) != 0);
	}

	
    while (1) 
    {
		tempCount = 0x00;
		tempA = PINA;
		tempB = PINB;
	
		
		for(unsigned char i = 0; i < 9; i++)
		{
			if((GetBit(tempA, 0) == 1))
			{
				tempCount++;
				tempA = tempA>>1;
			}
			else
			{
				tempA = tempA>>1;
			}
			
		}
		
		for(unsigned char i = 0; i < 9; i++)
		{
			if((GetBit(tempB, 0) == 1))
			{
				tempCount++;
				tempB = tempB>>1;
			}
			else
			{
				tempB = tempB>>1;
			}
			
		}
		
		PORTC = tempCount; 
		
		
		
    }
}

