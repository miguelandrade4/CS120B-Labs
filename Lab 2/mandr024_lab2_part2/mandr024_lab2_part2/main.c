/*
 * mandr024_lab2_part2.c
 *
 * Created: 7/31/2018 3:42:02 PM
 * Author : Miguel
 */ 

#include <avr/io.h>

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as inputs,
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs
	
	unsigned char tempNum = 0x00;
	unsigned char tempVal = 0x00;
	
    while (1) //FIX ALGORITHM
    {
		tempNum = PINA;
		
		if(tempNum <= 4)
		{
			SetBit(tempVal, 6, 1);
		}
		
		if(tempNum == 0x01 || tempNum == 0x02)
		{
			SetBit(tempVal, 6, 1);
		}
		
		if(tempNum == 0x03 || tempNum == 0x04)
		{
			SetBit(tempVal, 6, 1);
		}
		
		if(tempNum == 0x05 || tempNum == 0x06)
		{
			SetBit(tempVal, 6, 1);
		}
		
		if(tempNum == 0x07 || tempNum == 0x08)
		{
			SetBit(tempVal, 6, 1);
		}
		
		if(tempNum == 0x01 || tempNum == 0x02)
		{
			SetBit(tempVal, 6, 1);
		}
		
		if(tempNum == 0x01 || tempNum == 0x02)
		{
			SetBit(tempVal, 6, 1);
		}
		
		PORTC = tempVal;
    }
}

