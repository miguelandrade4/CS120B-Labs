/*
 * mandr024_lab4_part1.c
 *
 * Created: 8/6/2018 3:03:00 PM
 * Author : Miguel
 */ 

#include <avr/io.h>

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port C's 8 pins as outputs
	
    while (1) //FIX ALGORITHM
    {
		
		signed char tempVal = 0x00 & 0x7F;
		signed char tempNum = 0x00 & 0x0F;
		PORTB = 0x00;
		
		tempNum = ~PINA & 0x0F;
		
			
		if( tempNum == 0)
		{
			tempVal = 0x40;
		}
		
		else if (tempNum == 1 || tempNum == 2)
		{
			tempVal = 0x60;
		}
		
		else if (tempNum == 3 || tempNum == 4)
		{
			tempVal = 0x70;
		}
		
		else if (tempNum == 5 || tempNum ==6)
		{
			tempVal = 0x38;
		}
		
		else if (tempNum >= 7 && tempNum <= 9)
		{
			tempVal = 0x3C;
		}
		
		else if (tempNum >= 10 && tempNum <= 12)
		{
			tempVal = 0x3E;
		}
		
		else if (tempNum >= 13 && tempNum <= 15)
		{
			tempVal = 0x3F;
		}
		
		PORTB = tempVal;
    }
}

