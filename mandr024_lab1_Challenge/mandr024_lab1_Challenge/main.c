/*
 * mandr024_lab1_Challenge.c
 *
 * Created: 7/31/2018 12:25:48 PM
 * Author : Miguel
 */ 

#include <avr/io.h>


int main(void)
{
	signed char tempA;
	signed char tempB;
	signed char tempC;
	unsigned char tempNum;
    /* Replace with your application code */
    while (1) 
    {
		tempA = PINA;
		tempB = PINB;
		tempC = PINC;
		
		tempNum = tempA - tempC;
		
		tempNum = abs(tempNum);
		
		if( (PINA == 140) || (PINB == 140) || (PINC == 140))
		{
			if(tempNum == 80)
			{
				PORTD = 0x02;
			}
			
			else
			{
				PORTD = 0x01;
			}
				
		}
		
    }
}

