/*
 * mandr024_lab9_part2.c
 *
 * Created: 8/19/2018 10:07:04 PM
 * Author : Miguel
 */ 

#include <avr/io.h>
void set_PWM(double frequency) {

	static double current_frequency; // Keeps track of the currently set frequency

	// Will only update the registers when the frequency changes, otherwise allows

	// music to play uninterrupted.

	if (frequency != current_frequency) {

		if (!frequency) { TCCR3B &= 0x08; } //stops timer/counter

		else { TCCR3B |= 0x03; } // resumes/continues timer/counter

		

		// prevents OCR3A from overflowing, using prescaler 64

		// 0.954 is smallest frequency that will not result in overflow

		if (frequency < 0.954) { OCR3A = 0xFFFF; }

		

		// prevents OCR0A from underflowing, using prescaler 64     // 31250 is largest frequency that will not result in underflow

		else if (frequency > 31250) { OCR3A = 0x0000; }

		

		// set OCR3A based on desired frequency

		else { OCR3A = (short)(8000000 / (128 * frequency)) - 1; }

		

		TCNT3 = 0; // resets counter

		current_frequency = frequency; // Updates the current frequency

	}

}

void PWM_on() {

	TCCR3A = (1 << COM3A0);

	// COM3A0: Toggle PB3 on compare match between counter and OCR0A

	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);

	// WGM02: When counter (TCNT0) matches OCR0A, reset counter

	// CS01 & CS30: Set a prescaler of 64

	set_PWM(0);

}

void PWM_off() {

	TCCR3A = 0x00;

	TCCR3B = 0x00;

}

enum STATES{START, INIT, scaleUP, scaleDOWN} soundOn;

double scaleIng[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};
unsigned char tempIn = 0x00;
unsigned char i = 0x00;

void tick()
{
	switch(soundOn)
	{
		case START:
			soundOn = INIT;
		break;
		case INIT:
			if(tempIn == 0x01)
			{
				soundOn = INIT;
			}
			
			else if(tempIn == 0x02)
			{
				if(i < 7)
				{
					i++;	
				}
				soundOn = scaleUP;
			}
			
			else if(tempIn == 0x04)
			{
				if(i > 0)
				{
					i--;
				}
				
				soundOn = scaleDOWN;
			}
			
			else
			{
				soundOn = INIT;
			}
			
		break;
		case scaleUP:
			if (tempIn == 0x01)
			{
				soundOn = INIT;
			}
			
			else if (tempIn == 0x02)
			{
				soundOn = scaleUP;
			}
			
			else if (tempIn == 0x04)
			{
				if(i > 0)
				{
					i--;
				}
				soundOn = scaleDOWN;
			}
			
			else
			{
				soundOn = INIT;
			}
		break;
		case scaleDOWN:
		if (tempIn == 0x01)
		{
			soundOn = INIT;
		}
		
		else if (tempIn == 0x02)
		{
			if(i < 7)
			{
				i++;	
			}
			soundOn = scaleUP;
		}
		
		else if (tempIn == 0x04)
		{
			soundOn = scaleDOWN;
		}
		
		else
		{
			soundOn = INIT;
		}
		break;
		
		default: 
			soundOn = START;
	}
	
	switch(soundOn)
	{
		case START:
		break;
		case INIT:
			set_PWM(scaleIng[i]);
		break;
		case scaleUP:
			set_PWM(scaleIng[i]);		
		break;
		case scaleDOWN:
			set_PWM(scaleIng[i]);
		break;
	}
}


int main(void)
{
	unsigned char out = 0x00;
	
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	PWM_on();
	soundOn = START;
	
    while (1) 
    {
		tempIn = ~PINA & 0x07;
		tick();
    }
}

