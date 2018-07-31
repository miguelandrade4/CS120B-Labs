/*
 * mandr024_lab1_part3.c
 *
 * Created: 7/31/2018 12:11:39 PM
 * Author : Miguel
 */ 

#include <avr/io.h>


int main(void)
{
		unsigned char tempA;
    /* Replace with your application code */
    while (1) 
    {
		tempA = (PINA & 0x0F);
		
		if ((tempA == 0x01) || (tempA == 0x02) || (tempA == 0x04) || (tempA == 0x08))
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
			PORTC = 0x80;
		}
		else
		{
			PORTC = 0x04;
		}
    }
}

