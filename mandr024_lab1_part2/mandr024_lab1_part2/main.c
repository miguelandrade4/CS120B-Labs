/*
 * mandr024_lab1_part2.c
 *
 * Created: 7/30/2018 3:06:41 PM
 * Author : ucrcse
 */ 

#include <avr/io.h>


int main(void)
{
	unsigned char tempA;
    /* Replace with your application code */
    while (1) 
    {
		tempA = (PINA & 0x07);
		
		if((tempA == 0x01) || (tempA == 0x02) || (tempA == 0x04) || (tempA == 0x08))
		{
			PORTC = 0x03;
		}
		
		else if((tempA == 0x03) || (tempA == 0x05) || (tempA == 0x06) || (tempA == 0x09) || (tempA == 0x0A) || (tempA == 0x0C))
		{
			PORTC = 0x02;
		}
		
		else if((tempA == 0x07) || (tempA == 0x0B) || (tempA == 0x0D) || (tempA == 0x0E))
		{
			PORTC = 0x01;
		}
		
		else if((tempA == 0x0F))
		{
			PORTC = 0x00;
		}
		
		else if((tempA == 0x00))
		{
			PORTC = 0x04;
		}
    }
}

