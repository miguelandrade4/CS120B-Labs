/*
 * mandr024_lab2_challenge_part1.c
 *
 * Created: 8/1/2018 1:05:22 PM
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
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs
	
	while (1) 
    {
		
		signed char tempNum = 0x00;
		signed char i = 0;
		unsigned char driver = 0x00;
		unsigned char key = 0x00;
		unsigned char fastened = 0x00;
		unsigned char tempVal = 0x00;
		PORTC = 0x00;
		
// 		tempNum = PINA;
// 		
// 		if(driver == 1)
// 		{
// 			tempVal = SetBit(tempVal, 5, 1);
// 		}
// 		
// 		if(fastened == 1)
// 		{
// 			tempVal = SetBit(tempVal, 5, 1);
// 		}
// 		
// 		if(key == 1)
// 		{
// 			tempVal = SetBit(tempVal, 4, 1);
// 			
// 			if(fastened == 0 && driver == 1)
// 			{
// 				tempVal = SetBit(tempVal, 7, 1);
// 			}
// 			
// 			else
// 			{
// 				tempVal = SetBit(tempVal, 7, 0);
// 			}
// 		}
// 		
// 		if(PINA <= 4)
// 		{
// 			tempVal = SetBit(tempVal, 6, 1);
// 		}
// 		
// 		for(i = 5; i >= 0 ; i--)
// 		{
// 			if(tempNum > 0)
// 			{
// 				unsigned char x = i;
// 				tempVal = SetBit(tempVal, x, 1);
// 				tempNum = tempNum - 2;
// 				
// 				if (PINA == 9 && i == 1)
// 				{
// 					tempVal = SetBit(tempVal, 1, 0);
// 					break;
// 				}
// 				
// 			}
// 			
// 		}
// 		
// 		
// 		PORTC = tempVal;
// 		
		
		unsigned char porB = 0x00;
		unsigned char porC = 0x00;
		tempVal = PINA;
		
		porC = tempVal<<4; 
		porB = tempVal>>4;
		
		PORTC = porC;
		PORTB = porB;
    }
}

