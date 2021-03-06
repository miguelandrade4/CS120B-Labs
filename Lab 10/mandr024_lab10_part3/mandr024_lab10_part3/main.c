/*
 * mandr024_lab10_part3.c
 *
 * Created: 8/23/2018 12:45:15 AM
 * Author : Miguel
 */ 

#include <avr/io.h>
#include "bit.h"
#include "io.c"

unsigned char pause = 0;
volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

void TimerOn() {
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1=0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}

void TimerOff() {
	TCCR1B = 0x00;
}

void TimerISR() {
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect) {
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

unsigned long int findGCD(unsigned long int a, unsigned long int b)
{
	unsigned long int c;
	while(1){
		c = a%b;
		if(c==0){return b;}
		a = b;
		b = c;
	}
	return 0;
}

typedef struct _task{
	signed char state;
	unsigned long int period;
	unsigned long int elapsedTime;
	int (*TickFct)(int);
} task;

//was having problems with inputs of numpad so made it more secure. using else if statements
void SMTick1() {
	PORTC = 0xEF; // Enable col 4 with 0, disable others with 1�s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { pause = '1'; }
	else if (GetBit(PINC,1)==0) { pause = '4'; }
	else if (GetBit(PINC,2)==0) { pause = '7'; }
	else if (GetBit(PINC,3)==0) { pause = '*'; }
	else{
		// Check keys in col 2
		PORTC = 0xDF; // Enable col 5 with 0, disable others with 1�s
		asm("nop"); // add a delay to allow PORTC to stabilize before checking
		if (GetBit(PINC,0)==0) { pause = '2'; }
		else if (GetBit(PINC,1)==0) { pause = '5'; }
		else if (GetBit(PINC,2)==0) { pause = '8'; }
		else if (GetBit(PINC,3)==0) { pause = '0'; }
		else{
			PORTC = 0xBF;
			asm("nop");
			if (GetBit(PINC,0)==0) { pause = '3'; }
			else if (GetBit(PINC,1)==0) { pause = '6'; }
			else if (GetBit(PINC,2)==0) { pause = '9'; }
			else if (GetBit(PINC,3)==0) { pause = '#'; }
			else{
				PORTC = 0x7F;
				asm("nop");
				if (GetBit(PINC,0)==0) { pause = 'A'; }
				else if (GetBit(PINC,1)==0) { pause = 'B'; }
				else if (GetBit(PINC,2)==0) { pause = 'C'; }
				else if (GetBit(PINC,3)==0) { pause = 'D'; }
				else{ pause = '\0';} // default value
			}
		}
	}
}

int main(void)
{
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0x0F;
	DDRD = 0xFF; PORTD = 0x00;
	
	unsigned long int SMTick1_calc = 1000;	//input period for task
	//unsigned long int SMTick2_calc = 1000;
	unsigned char gateKeeper = 0x00;
	unsigned char tracker = 0x00 + '0';
	
	//unsigned long int GCD = findGCD(SMTick1_calc, SMTick2_calc);	//calculate GCD
	
	unsigned long int SMTick1_period = SMTick1_calc;
// 	unsigned long int SMTick2_period = SMTick2_calc/GCD;
	
	static task task1, task2;
	task *tasks[] = { &task1, &task2};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	
	task1.state = -1;//Task initial state.
	task1.period = SMTick1_period;//Task Period.
	task1.elapsedTime = SMTick1_period;//Task current elapsed time.
	task1.TickFct = &SMTick1;//Function pointer for the tick.

// 	Task 2
// 		task2.state = -1;//Task initial state.
// 		task2.period = SMTick2_period;//Task Period.
// 		task2.elapsedTime = SMTick2_period;//Task current elapsed time.
// 		task2.TickFct = &SMTick2;//Function pointer for the tick.
	
	TimerOn();
	TimerSet(100);//GCD);
	
	LCD_init();
	LCD_ClearScreen();
	
	while(1) {
		
		unsigned short i; // Scheduler for-loop iterator
		while(1) {
			
			//Scheduler code
						for ( i = 0; i < numTasks; i++ ) {
							// Task is ready to tick
							if ( tasks[i]->elapsedTime == tasks[i]->period ) {
								// Setting next state for task
								tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
								// Reset the elapsed time for next tick.
								tasks[i]->elapsedTime = 0;
							}
						}
						tasks[i]->elapsedTime += 1;
// 						
			SMTick1();
			
			gateKeeper = pause;
			
			if(gateKeeper != '\0'){
				
				if(gateKeeper != tracker){
					
					tracker = gateKeeper;
					LCD_ClearScreen();
					LCD_Cursor(1);
					LCD_WriteData(gateKeeper);
				}
				
			}
			
			while(!TimerFlag);
			TimerFlag = 0;
		}
		
	}
}

