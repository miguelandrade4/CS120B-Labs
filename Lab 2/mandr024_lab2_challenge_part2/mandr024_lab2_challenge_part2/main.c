/*
 * mandr024_lab2_challenge_part2.c
 *
 * Created: 8/1/2018 2:08:17 PM
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
		unsigned char porB = 0x00;
		unsigned char key = 0x00;
		unsigned char fastened = 0x00;
		unsigned short tempVal = 0x00;
		PORTC = 0x00;
		
		tempVal = PORTA;
		
		if(tempVal == 255)
		{
			for(unsigned char i = 0; i <8; ++i)
			{
				porC = SetBit()
			}
		}
		
		if(tempVal >= 70)
		{
			porB = SetBit(porB,1,1);
		}
		
		PORTC = porC;
		PORTB = porB;
    }
}

