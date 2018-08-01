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
	DDRB = 0xFF; PORTB = 0x00; // Configure port C's 8 pins as outputs
	
    while (1) //FIX ALGORITHM
    {
		
		signed char tempNum = 0x00;
		signed char i = 0;
		unsigned char driver = 0x00;
		unsigned char key = 0x00;
		unsigned char fastened = 0x00;
		unsigned char tempVal = 0x00;
		PORTB = 0x00;
		
		tempNum = PINA;
		
		if(PINA <= 4)
		{
			tempVal = SetBit(tempVal, 6, 1);
		}
			
		for(i = 5; i >= 0 ; i--)
		{
			if(tempNum > 0)
			{
				unsigned char x = i;
				tempVal = SetBit(tempVal, x, 1);
				tempNum = tempNum - 2;
				
				if (PINA == 9 && i == 1)
				{
					tempVal = SetBit(tempVal, 1, 0);
					break;
				}
				
			}
			
		}
		
		PORTB = tempVal;
    }
}

