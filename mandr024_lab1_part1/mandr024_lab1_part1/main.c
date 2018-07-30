/*
 * mandr024_lab1_part1.c
 *
 * Created: 7/30/2018 2:32:59 PM
 * Author : ucrcse
 */ 

#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs,
	
    /* Replace with your application code */
    while (1) 
    {
		if((PINA & 0x03) == 0x01)
		{
			PORTB = 0x01;
		}
		
		else
			PORTB = 0x00;
	}
}

