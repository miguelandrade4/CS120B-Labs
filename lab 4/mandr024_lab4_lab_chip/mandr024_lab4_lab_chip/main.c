/*
 * mandr024_lab4_lab_chip.c
 *
 * Created: 8/6/2018 1:28:10 PM
 * Author : Miguel
 */ 
#include <avr/io.h>

int main(void)
{
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs
	while(1)
	{
		PORTB = 0x0F; // Writes port B's 8 pins with 00001111
	}
}

