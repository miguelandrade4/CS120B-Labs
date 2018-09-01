/*
 * mandr024_customlab.c
 *
 * Created: 8/26/2018 2:46:14 PM
 * Author : Miguel
 */ 

#include <avr/io.h>
#include "io.c"
#include "string.h"
#include "math.h"
#include <avr/interrupt.h>
#include "bit.h"
#include "timer.h"


void EEPROM_write(unsigned int uiAddress, unsigned char ucData)
{
	
	EECR = EECR & 0x0F;
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE))
	;
	/* Set up address and Data Registers */
	EEAR = uiAddress;
	EEDR = ucData;
	/* Write logical one to EEMPE */
	EECR |= (1<<EEMPE);
	/* Start eeprom write by setting EEPE */
	EECR |= (1<<EEPE);
}

unsigned char EEPROM_read(unsigned int uiAddress)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE))
	;
	/* Set up address register */
	EEAR = uiAddress;
	
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from Data Register */
	return EEDR;
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
//--------End find GCD function ----------------------------------------------

//--------Task scheduler data structure---------------------------------------
// Struct for Tasks represent a running process in our simple real-time operating system.
typedef struct _task {
    /*Tasks should have members that include: state, period,
        a measurement of elapsed time, and a function pointer.*/
    signed char state; //Task's current state
    unsigned long int period; //Task period
    unsigned long int elapsedTime; //Time elapsed since last task tick
    int (*TickFct)(int); //Task tick function
} task;

unsigned char customCharOne[] = 
{
	0x00,
	0x04,
	0x03,
	0x13,
	0x0E,
	0x0E,
	0x0A,
	0x00
};

unsigned char customCharTwo[] =
{
	0x0E,
	0x0E,
	0x04,
	0x0E,
	0x15,
	0x0A,
	0x0A,
	0x00
};

unsigned char customCharThree[] =
{
	0x04,
	0x0E,
	0x15,
	0x1F,
	0x1F,
	0x1F,
	0x15,
	0x00
};

unsigned char customCharFour[] =
{
	0x04,
	0x0A,
	0x1F,
	0x1F,
	0x1F,
	0x0A,
	0x0A,
	0x00
};

void tostring(char str[], int num)
{
	int i, rem, len = 0, n;
	n = num;
	
	while (n != 0)
	{
		len++;
		n /= 10;
	}

	for (i = 0; i < len; i++)
	{
		rem = num % 10;
		num = num / 10;
		str[len - (i + 1)] = rem + '0';
	}

	str[len] = '\0';
}

int main(void)
{
	DDRD = 0xFF; PORTD = 0x00; // LCD data lines
	DDRA = 0xFF; PORTA = 0x00; // LCD control lines
    /* Replace with your application code */
	char stringTemp[3];
	unsigned char position = 0x00;
	
	unsigned long int tmpGCD = 1;
	
	static task task1, task2, task3, task4;
	task *tasks[] = { &task1, &task2, &task3, &task4};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	
// 	task1.state = -1;//Task initial state.
// 	task1.period = SMTick1_period;//Task Period.
// 	task1.elapsedTime = SMTick1_period;//Task current elapsed time.
// 	task1.TickFct = &SMTick1;//Function pointer for the tick.

	unsigned short i;
	LCD_init();
	
	EEPROM_write(0x00, 0x47);
	LCD_WriteData(EEPROM_read(0x0000));
	
	LCD_WriteData(EEPROM_read(0x0001));
	LCD_WriteData(EEPROM_read(0x0002));
	
	int tempVal = (int)EEPROM_read(0x03);
	
	tostring(stringTemp,tempVal);
	
	LCD_WriteData(stringTemp[0]);
	LCD_WriteData(stringTemp[1]);
	LCD_WriteData(stringTemp[2]);
		
	LCD_WriteData(EEPROM_read(0x00FF));
    while (1) 
    {
		
		
		while(!TimerFlag);
		TimerFlag = 0;
    }
}

