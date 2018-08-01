/*
 * mandr024_lab2_part3.c
 *
 * Created: 8/1/2018 10:37:01 AM
 * Author : Miguel
 */ 

#include <avr/io.h>

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}

unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}


int main(void)
{
    DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
    DDRB = 0xFF; PORTB = 0x00; // Configure port C's 8 pins as outputs
	
    while (1) 
    {
		
		signed char tempNum = 0x00;
		signed char tempNum_two = 0x00;
		signed char i = 0;
		unsigned char key = 0x01;
		unsigned char tempVal = 0x00;
		PORTB = 0x00;
		
		tempNum = PINA;
		
				
		if(GetBit(tempNum, 4) && GetBit(tempNum, 6) == 0 && GetBit(tempNum, 5))
		{
			tempVal = SetBit(tempVal, 7, 1);
		}
		
		tempNum_two = (PINA & 0x0F);
		key = (PINA & 0x0F);
		
		if(key <= 4)
		{
			tempVal = SetBit(tempVal, 6, 1);
		}
		
		for(i = 5; i >= 0 ; i--)
		{
			if(tempNum_two > 0)
			{
				unsigned char x = i;
				tempVal = SetBit(tempVal, x, 1);
				tempNum_two = tempNum_two - 2;
				
				if (key == 9 && i == 1)
				{
					tempVal = SetBit(tempVal, 1, 0);
					break;
				}
				
			}
			
		}
		
		PORTB = tempVal;
		
    }
}

