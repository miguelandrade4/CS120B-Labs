/*
 * mandr024_customlab_EEPROMtest.c
 *
 * Created: 8/27/2018 12:36:43 PM
 * Author : Miguel
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "io.c"
#include "timer.h"
#include "string.h"
#include "math.h"
#include "bit.h"

unsigned char start = 0x00;
unsigned char timePassed = 0x00;
unsigned char restartFlag = 0;
unsigned short y = 0x00;
unsigned char restart = 0x00;
unsigned char stopScrollingOne = 0x00;
unsigned char stopScrollingTwo = 0x00;
unsigned char stopScrollingThree = 0x00;
unsigned char stopScrollingFour = 0x00;
unsigned char buttonPress = 0x00;
unsigned char startArray[] = {"-*-GRAVE MIND-*-*-PRESS  START-*"};
unsigned char charArray[] = {" CHOOSE  AVATAR  "};
unsigned char gameArray[] = {"________________________________"};
unsigned char enemyChosen = 0x00;
unsigned char location = 0x00;
unsigned char death = 0x00;	
unsigned char charPosition = 0x17;
unsigned char avatarPosition = 0x17;
unsigned char enemyOnePosition = 0x00;
unsigned char enemyTwoPosition = 0x00;
unsigned char enemyThreePosition = 0x00;
unsigned char enemyFourPosition = 0x00;
unsigned char chosenAvatar = 0x00;
unsigned char startGame = 0x00;
unsigned char stallFlag = 0x00;
unsigned char stallFlagTwo = 0x00;
int playerPoints = 0x00;
unsigned char winFlag = 0x00;
	

void EEPROM_write(unsigned int uiAddress, unsigned char ucData)
{
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

enum START_SM{START_START,START_INIT, START_DISPLAY, START_PRESS} START_STATE;
	
void START_TEST()
{
	switch(START_STATE)
	{
		case START_START:
			START_STATE = START_INIT;
		break;
		
		case START_INIT:
			if (start)
			{
				START_STATE = START_INIT;	
			}
			else if(!start)
			{
				START_STATE = START_DISPLAY;
			}
		break;
		
		case START_DISPLAY:
			buttonPress = ~PINB & 0x01;
			
			if(buttonPress == 0x01)
			{
				START_STATE = START_PRESS;
			}
			
			else
			{
				START_STATE = START_DISPLAY;
			}
		break;
		
		case START_PRESS:
			START_STATE = START_INIT;
		break;
		
		default:
		START_STATE = START_START;
	}
	
	switch(START_STATE)
	{
		case START_START:
		break;
		
		case START_INIT:
		break;
		
		case START_DISPLAY:
			LCD_DisplayString(1, startArray);
		break;
		
		case START_PRESS:
			start = 0x01;
			LCD_ClearScreen();
		break;
	}
}	

enum CHARACTER_SM{CHAR_START, CHAR_INIT, CHAR_DISPLAY, CHAR_CURSOR, CHAR_RIGHT, CHAR_LEFT, CHAR_PAUSE, CHAR_RELEASE} CHAR_STATE;

void CHARACTER_TEST()
{
	switch (CHAR_STATE)
	{
		case CHAR_START:
			CHAR_STATE = CHAR_INIT;
		break;
		
		case CHAR_INIT:
			if(start && !startGame && !death)
			{
				CHAR_STATE = CHAR_DISPLAY;
			}
			
			else if(restartFlag)
			{
				death = 0x00;
				restartFlag = 0x00;
				CHAR_STATE = CHAR_DISPLAY;
			}
			
			else
			{
				CHAR_STATE = CHAR_INIT;
			}
		break;
		
		case CHAR_DISPLAY:
			CHAR_STATE = CHAR_CURSOR;
		break;
		
		case CHAR_CURSOR:
			buttonPress = ~PINB & 0x07;
			
			if(buttonPress == 0x02)
			{
				CHAR_STATE = CHAR_RIGHT;
			}
			
			else if(buttonPress == 0x04)
			{
				CHAR_STATE = CHAR_LEFT;
			}
			
			
			else
			{
				CHAR_STATE = CHAR_CURSOR;
			}
		break;
		
		case CHAR_RIGHT:
			CHAR_STATE = CHAR_PAUSE;
		break;
		
		case CHAR_LEFT:
			CHAR_STATE = CHAR_PAUSE;
		break;
		
		case CHAR_PAUSE:
			buttonPress = ~PINB & 0x07;		
			if( buttonPress == 0x00)
			{
				CHAR_STATE = CHAR_RELEASE;
			}
			
			else
			{
				CHAR_STATE = CHAR_PAUSE;
			}
			
		break;
		
		case CHAR_RELEASE:
			buttonPress = ~PINB & 0x07;
			if(buttonPress == 0x02)
			{
				CHAR_STATE = CHAR_RIGHT;
			}
			
			else if(buttonPress == 0x04)
			{
				CHAR_STATE = CHAR_LEFT;
			}
		
			else if(buttonPress == 0x01 && charPosition == 20)
			{
				chosenAvatar = 1;
				startGame = 0x01;
				CHAR_STATE = CHAR_INIT;
				LCD_ClearScreen();
			}
			
			else if(buttonPress == 0x01 && charPosition == 23)
			{
				chosenAvatar = 2;
				startGame = 0x01;
				CHAR_STATE = CHAR_INIT;
				LCD_ClearScreen();
			}
			
			else if(buttonPress == 0x01 && charPosition == 26)
			{
				chosenAvatar = 3;
				startGame = 0x01;
				CHAR_STATE = CHAR_INIT;
				LCD_ClearScreen();
			}
			else if(buttonPress == 0x01 && charPosition == 29)
			{
				chosenAvatar = 4;
				startGame = 0x01;
				CHAR_STATE = CHAR_INIT;
				LCD_ClearScreen();
			}
			else
			{
				CHAR_STATE = CHAR_RELEASE;
			}
		break;
		
		default: 
		CHAR_STATE = CHAR_START;
	}
	
	switch(CHAR_STATE)
	{
		case CHAR_START:
		break;
		
		case CHAR_INIT:
		break;
		
		case CHAR_DISPLAY:
			LCD_ClearScreen();
			LCD_WriteCommand(0x0E);
			LCD_DisplayString(1, charArray);
			LCD_Cursor(20);
			LCD_WriteData(1);
			LCD_Cursor(23);
			LCD_WriteData(2);
			LCD_Cursor(26);
			LCD_WriteData(3);
			LCD_Cursor(29);
			LCD_WriteData(4);
			LCD_Cursor(17);
		break;
		
		case CHAR_CURSOR:
		break;
		
		case CHAR_RIGHT:
			if(charPosition < 33)
			{
				charPosition++;
			}
			
			LCD_Cursor(charPosition);
			
		break;
		
		case CHAR_LEFT:
			if(charPosition > 17)
			{
				charPosition--;
			}
			
			LCD_Cursor(charPosition);
		break;
		
		case CHAR_PAUSE:
		break;
		
		case CHAR_RELEASE:
		break;
	}
}

enum GAME_SM{GAME_START, GAME_INIT, GAME_DISPLAY, GAME_PAUSE} GAME_STATE;

void GAME_TEST()
{
	switch(GAME_STATE)
	{
		case GAME_START:
			GAME_STATE = GAME_INIT;
		break;
		
		case GAME_INIT:
			if(start && startGame && !death)
			{
				GAME_STATE = GAME_DISPLAY;
			}
			
			else
			{
				GAME_STATE = GAME_INIT;
			}	
		break;
		
		case GAME_DISPLAY:
			GAME_STATE = GAME_PAUSE;	
		break;
		
		case GAME_PAUSE:
			GAME_STATE = GAME_PAUSE;
		break;
		
		default:
			GAME_STATE = GAME_START;	
	}
	
	switch(GAME_STATE)
	{
		case GAME_START:
		break;
		
		case GAME_INIT:
		break;
		
		case GAME_DISPLAY:
			LCD_DisplayString(1, gameArray);
			LCD_Cursor(17);
			LCD_WriteData(chosenAvatar);
			LCD_WriteCommand(0x0C);
		break;
		
		case GAME_PAUSE:
		break;
	}
}

enum MOVE_SM{MOVE_START, MOVE_INIT, MOVE_UP, MOVE_DOWN, MOVE_PAUSE, MOVE_RELEASE} MOVE_STATE;	

void MOVE_TEST()
{
	switch(MOVE_STATE)
	{
		case MOVE_START:
			MOVE_STATE = MOVE_INIT;
		break;
		
		case MOVE_INIT:
			buttonPress = ~PINB & 0x07;
			if(startGame && !death && buttonPress == 0x02)
			{
				MOVE_STATE = MOVE_UP;
			}
			
			else if(startGame && !death && buttonPress == 0x04)
			{
				MOVE_STATE = MOVE_DOWN;
			}
			
			else
			{
				MOVE_STATE = MOVE_INIT;
			}
			
		break;
		
		case MOVE_UP:
			MOVE_STATE = MOVE_PAUSE;
		break;
		
		case MOVE_DOWN:
			MOVE_STATE = MOVE_PAUSE;
		break;
		
		case MOVE_PAUSE:
			buttonPress = ~PINB & 0x07;
			if(buttonPress == 0x00)
			{
				MOVE_STATE = MOVE_RELEASE;
			}
			
			else
			{
				MOVE_STATE = MOVE_PAUSE;
			}
		break;
		
		case MOVE_RELEASE:
			buttonPress = ~PINB & 0x07;
			if(startGame && !death && buttonPress == 0x02)
			{
				MOVE_STATE = MOVE_UP;
			}
		
			else if(startGame && !death && buttonPress == 0x04)
			{
				MOVE_STATE = MOVE_DOWN;
			}
		
			else
			{
				MOVE_STATE = MOVE_RELEASE;
			}		
		break;
		
		default:
			MOVE_STATE = MOVE_START; 
	}
	
	switch(MOVE_STATE)
	{
		
		case MOVE_START:
		break;
		
		case MOVE_INIT:
		break;
		
		case MOVE_UP:
			if(avatarPosition != 1)
			{
				LCD_Cursor(17);
				LCD_WriteData('_');
				avatarPosition = 1;
			}
			
			else if(avatarPosition == 1)
			{
				avatarPosition = 1;
			}
			
			LCD_Cursor(avatarPosition);
			LCD_WriteData(chosenAvatar);
			
			
		break;
		
		case MOVE_DOWN:
			if(avatarPosition != 17)
			{
				avatarPosition = 17;
				LCD_Cursor(1);
				LCD_WriteData('_');
			}
			
			else if(avatarPosition == 17)
			{
				avatarPosition = 17;
			}
			
			LCD_Cursor(avatarPosition);
			LCD_WriteData(chosenAvatar);
			
		break;
		
		case MOVE_PAUSE:
		break;
		
		case MOVE_RELEASE:
		break;
	}
}

enum SEL_SM{SEL_START, SEL_INIT, SEL_RNG} SEL_STATE;
	
void SEL_TEST()
{
	switch(SEL_STATE)
	{
		case SEL_START:
			SEL_STATE = SEL_INIT;
		break;
		
		case SEL_INIT:
			if(!death && startGame)
			{
				SEL_STATE = SEL_RNG;
			}
			
			else
			{
				SEL_STATE = SEL_INIT;
			}
		break;
		
		case SEL_RNG:
			if(!death && startGame)
			{
				SEL_STATE = SEL_RNG;
			}
			
			else
			{
				SEL_STATE = SEL_INIT;
			}
		break;
		
		default:
			SEL_STATE = SEL_START;
	}
	
	switch(SEL_STATE)
	{
		case SEL_START:
		break;
		
		case SEL_INIT:
		break;
		
		case SEL_RNG:
			enemyChosen =  rand() % 5;
			location =  rand() % 3;			
			
		break;
	}
}

enum ENEMY_SM{ENEMY_START, ENEMY_INIT} ENEMY_STATE;		
	
void ENEMY_TEST()
{
	switch(ENEMY_STATE)
	{
		case ENEMY_START:
			ENEMY_STATE = ENEMY_INIT;
		break; 
		
		case ENEMY_INIT:
			if(startGame && !death)
			{
				if(enemyChosen == 1 && location == 1)
				{
					enemyOnePosition = 16;
				}
				
				if(enemyChosen == 2 && location == 1)
				{
					
					enemyTwoPosition = 16;
				}
				if(enemyChosen == 3 && location == 1)
				{
					
					enemyThreePosition = 16;
				}
				if(enemyChosen == 4 && location == 1)
				{
					
					enemyFourPosition = 16;
				}
				if(enemyChosen == 1 && location == 2)
				{
					
					enemyOnePosition = 32;
				}
				
				if(enemyChosen == 2 && location == 2)
				{
					enemyTwoPosition = 32;
				}
				
				if(enemyChosen == 3 && location == 2)
				{
					
					enemyThreePosition = 32;
				}
				
				if(enemyChosen == 4 && location == 2)
				{
					enemyFourPosition = 32;
				}
								
				ENEMY_STATE = ENEMY_INIT;
			}
			
			else
			{
				ENEMY_STATE = ENEMY_INIT;
			}
		break;
	
		default:
			ENEMY_STATE = ENEMY_START;
	}
	
	switch(ENEMY_STATE)
	{
		
		case ENEMY_START:
		break;
		
		case ENEMY_INIT:
		break;		
		break;
	}
}

enum E1_SM{E1_START, E1_INIT, E1_SCROLL} E1_STATE;

void E1_TEST()
{
	switch(E1_STATE)
	{
		case E1_START:
			E1_STATE = E1_INIT;
		break;
		
		case E1_INIT:
			if(enemyChosen == 1  && !death)
			{
				stopScrollingOne = 0;
				E1_STATE = E1_SCROLL;
			}
		
			else
			{
				E1_STATE = E1_INIT;
			}
		break;
		
		case E1_SCROLL:
			if(stopScrollingOne && death)
			{
				E1_STATE= E1_INIT;
			}
			
			else
			{
				E1_STATE = E1_SCROLL;
				
			}
		break;
		
		default:
		E1_STATE = E1_START;
	}
	
	switch(E1_STATE)
	{
		case E1_START:
		break;
		
		case E1_INIT:
		break;
		
		case E1_SCROLL:
			if(enemyOnePosition > 17)
			{
				enemyOnePosition--;
				LCD_Cursor(enemyOnePosition);
				LCD_WriteData('*');
				LCD_Cursor(enemyOnePosition+1);
				LCD_WriteData('_');
				
				if((enemyOnePosition == avatarPosition))
				{
					death = 0x01;
					startGame = 0x00;
					stopScrollingOne = 1;
					enemyOnePosition = 0;
				}
				
				else if(enemyOnePosition == 17)
				{
					LCD_Cursor(17);
					LCD_WriteData('_');
					enemyOnePosition = 0;
					stopScrollingOne = 1;
				}
			}
		
			else if(enemyOnePosition > 1 && enemyOnePosition < 17)
			{
				enemyOnePosition--;
				LCD_Cursor(enemyOnePosition);
				LCD_WriteData('*');
				LCD_Cursor(enemyOnePosition+1);
				LCD_WriteData('_');
			
				if((enemyOnePosition == avatarPosition))
				{
					death = 0x01;
					startGame = 0x00;
					stopScrollingOne = 1;
					enemyOnePosition = 0;
				}
				
				else if(enemyOnePosition == 1)
				{
					LCD_Cursor(1);
					LCD_WriteData('_');
					enemyOnePosition = 0;
					stopScrollingOne = 1;
				}
			}
		
		break;
	}
}

enum E2_SM{E2_START, E2_INIT, E2_SCROLL} E2_STATE;

void E2_TEST()
{
	switch(E2_STATE)
	{
		case E2_START:
			E2_STATE = E2_INIT;
		break;
		
		case E2_INIT:
		if(enemyChosen == 2 && !death)
		{
			stopScrollingTwo = 0;
			E2_STATE = E2_SCROLL;
		}
		
		else
		{
			E2_STATE = E2_INIT;
		}
		break;
		
		case E2_SCROLL:
		if(stopScrollingTwo && death)
		{
			E2_STATE = E2_INIT;
		}
		
		else
		{
			E2_STATE = E2_SCROLL;
			
		}
		break;
		
		default:
		E2_STATE = E2_START;
	}
	
	switch(E2_STATE)
	{
		case E2_START:
		break;
		
		case E2_INIT:
		break;
		
		case E2_SCROLL:
			if(enemyTwoPosition > 17)
			{
				enemyTwoPosition--;
				LCD_Cursor(enemyTwoPosition);
				LCD_WriteData('*');
				LCD_Cursor(enemyTwoPosition+1);
				LCD_WriteData('_');
			
				if((enemyTwoPosition == avatarPosition))
				{
					death = 0x01;
					startGame = 0x00;
					stopScrollingTwo = 1;
				}
				
				else if(enemyTwoPosition == 17)
				{
					LCD_Cursor(17);
					LCD_WriteData('_');
					enemyTwoPosition = 0;
					stopScrollingTwo = 1;
				}
			}
		
			else if(enemyTwoPosition > 1 && enemyTwoPosition < 17)
			{
				enemyTwoPosition--;
				LCD_Cursor(enemyTwoPosition);
				LCD_WriteData('*');
				LCD_Cursor(enemyTwoPosition+1);
				LCD_WriteData('_');
				
				if((enemyTwoPosition == avatarPosition))
				{
					death = 0x01;
					startGame = 0x00;
					stopScrollingTwo = 1;
				}
				
				else if(enemyTwoPosition == 1)
				{
					LCD_Cursor(1);
					LCD_WriteData('_');
					enemyTwoPosition = 0;
					stopScrollingTwo = 1;
				}
			}
		break;
	}
}

enum E3_SM{E3_START, E3_INIT, E3_SCROLL} E3_STATE;

void E3_TEST()
{
	switch(E3_STATE)
	{
		case E3_START:
			E3_STATE = E3_INIT;
		break;
		
		case E3_INIT:
		if(enemyChosen == 3 && !death)
		{
			stopScrollingThree = 0;
			E3_STATE = E3_SCROLL;
		}
		
		else
		{
			E3_STATE = E3_INIT;
		}
		break;
		
		case E3_SCROLL:
		if(stopScrollingThree && death)
		{
			E3_STATE= E3_INIT;
		}
		
		else
		{
			E3_STATE = E3_SCROLL;
			
		}
		break;
		
		default:
		E3_STATE = E3_START;
	}
	
	switch(E3_STATE)
	{
		case E3_START:
		break;
		
		case E3_INIT:
		break;
		
		case E3_SCROLL:
		if(enemyThreePosition > 17)
		{
			enemyThreePosition--;
			LCD_Cursor(enemyThreePosition);
			LCD_WriteData('*');
			LCD_Cursor(enemyThreePosition+1);
			LCD_WriteData('_');
			
			if((enemyThreePosition == avatarPosition))
			{
				death = 0x01;
				startGame = 0x00;
				stopScrollingThree = 1;
			}
			
			else if(enemyThreePosition == 17)
			{
				LCD_Cursor(17);
				LCD_WriteData('_');
				enemyThreePosition = 0;
				stopScrollingThree = 1;
			}
		}
		
		else if(enemyThreePosition > 1 && enemyThreePosition < 17)
		{
			enemyThreePosition--;
			LCD_Cursor(enemyThreePosition);
			LCD_WriteData('*');
			LCD_Cursor(enemyThreePosition+1);
			LCD_WriteData('_');
			
			if((enemyThreePosition == avatarPosition))
			{
				death = 0x01;
				startGame = 0x00;
				stopScrollingThree = 1;
			}
			
			else if(enemyThreePosition == 1)
			{
				LCD_Cursor(1);
				LCD_WriteData('_');
				enemyThreePosition = 0;
				stopScrollingThree = 1;
			}
		}
		break;
	}
}

enum E4_SM{E4_START, E4_INIT, E4_SCROLL} E4_STATE;

void E4_TEST()
{
	switch(E4_STATE)
	{
		case E4_START:
			E4_STATE = E4_INIT;
		break;
		
		case E4_INIT:
		if(enemyChosen == 4 && !death)
		{
			stopScrollingFour = 0;
			E4_STATE = E4_SCROLL;
		}
		
		else
		{
			E4_STATE = E4_INIT;
		}
		break;
		
		case E4_SCROLL:
		if(stopScrollingFour && death)
		{
			E4_STATE= E4_INIT;
		}
		
		else
		{
			E4_STATE = E4_SCROLL;
			
		}
		break;
		
		default:
		E4_STATE = E4_START;
	}
	
	switch(E4_STATE)
	{
		case E4_START:
		break;
		
		case E4_INIT:
		break;
		
		case E4_SCROLL:
		if(enemyFourPosition > 17)
		{
			enemyFourPosition--;
			LCD_Cursor(enemyFourPosition);
			LCD_WriteData('*');
			LCD_Cursor(enemyFourPosition+1);
			LCD_WriteData('_');
			
			if((enemyFourPosition == avatarPosition))
			{
				death = 0x01;
				startGame = 0x00;
				stopScrollingFour = 1;
			}
			
			else if(enemyFourPosition == 17)
			{
				LCD_Cursor(17);
				LCD_WriteData('_');
				enemyFourPosition = 0;
				stopScrollingFour = 1;
			}
		}
		
		else if(enemyFourPosition > 1 && enemyFourPosition < 17)
		{
			enemyFourPosition--;
			LCD_Cursor(enemyFourPosition);
			LCD_WriteData('*');
			LCD_Cursor(enemyFourPosition+1);
			LCD_WriteData('_');
			
			if((enemyFourPosition == avatarPosition))
			{
				death = 0x01;
				startGame = 0x00;
				stopScrollingFour = 1;
			}
			
			else if(enemyFourPosition == 1)
			{
				LCD_Cursor(1);
				LCD_WriteData('_');
				enemyFourPosition = 0;
				stopScrollingFour = 1;
			}
		}
		
		break;
	}
}

enum POINTS_SM{POINTS_START, POINTS_INIT, POINTS_INCREMENT, POINTS_NOTHING} POINTS_STATE;

void POINTS_TEST()
{
	switch(POINTS_STATE)
	{
		case POINTS_START:
		POINTS_STATE = POINTS_INIT;
		break;
		
		case POINTS_INIT:
			if(!death && startGame)
			{
				POINTS_STATE = POINTS_INCREMENT;
			}
			else
			{
				POINTS_STATE = POINTS_NOTHING;
			}
		break;
		
		
		
		case POINTS_INCREMENT:
		if(death)
		{
			
			POINTS_STATE = POINTS_NOTHING;
		}
		
		else
		{
			POINTS_STATE = POINTS_INCREMENT;
		}
		break;
		
		case POINTS_NOTHING:
			POINTS_STATE = POINTS_INIT;
		break;
		
		
		default:
		POINTS_STATE = POINTS_INCREMENT;
	}
	
	switch(POINTS_STATE)
	{
		case POINTS_START:
		break;
		
		case POINTS_INIT:
		break;
		
		case POINTS_INCREMENT:
		if(playerPoints == 100)
		{
			winFlag = 0x01;
		}
		
		else
		{
			playerPoints++;
		}
		
		
		break;
		
		case POINTS_NOTHING:
		break;
	}
}

enum DEATH_SM{DEATH_START, DEATH_INIT, DEATH_DISPLAY, DEATH_PAUSE, DEATH_SAVE} DEATH_STATE;
	
void DEATH_TEST()
{
	
	unsigned char pointPosition = 0x00;
	unsigned char sizeArray = 0x00;
	unsigned char newSlot = 0x00;
	char str[3];
	
	switch(DEATH_STATE)
	{
		case DEATH_START:
			DEATH_STATE = DEATH_INIT;
		break;
		
		case DEATH_INIT:
			if(death && timePassed == 0)
			{
				DEATH_STATE = DEATH_DISPLAY;
			}
		
			else
			{
				DEATH_STATE = DEATH_INIT;
			}
			
		break;
		
		case DEATH_DISPLAY:
			DEATH_STATE = DEATH_SAVE;
		break;
		
		case DEATH_PAUSE:
		if(timePassed == 20)
		{
			stallFlag = 0x01;
			DEATH_STATE = DEATH_INIT;
		}
		else
		{
			timePassed++;
			DEATH_STATE = DEATH_PAUSE;
		}
		break;
		
		case DEATH_SAVE:
			DEATH_STATE = DEATH_PAUSE;
		break;
		
		default:
			DEATH_STATE = DEATH_START;
	}
	
	switch(DEATH_STATE)
	{
		case DEATH_START:
		break;
		
		case DEATH_INIT:
		break;
		
		case DEATH_DISPLAY:
			pointPosition = 30;
			if (playerPoints > 0 && playerPoints < 10)
			{
				sizeArray = 1;
			}
			
			else if (playerPoints > 9 && playerPoints < 100)
			{
				sizeArray = 2;
			}
			
			else if (playerPoints >= 100)
			{
				sizeArray = 3;
			}
			
			LCD_DisplayString(1,"   GAME  OVER    YOUR SCORE = ");		
			tostring(str, playerPoints);	
			for(unsigned char i = 0; i < sizeArray; ++i)
			{	
				LCD_Cursor(pointPosition);
				LCD_WriteData(str[i]);
				pointPosition++;
			}
			
		break;
		
		case DEATH_PAUSE:
			
		break;
		
		case DEATH_SAVE:
			for (unsigned char j = 0x00; EEPROM_read(j) != 0xFF; j++ )
			{
				newSlot++;
			}
			unsigned int newPos = (unsigned int) newSlot;
			unsigned char tempVal = (unsigned char) playerPoints;
			EEPROM_write(newPos, tempVal);
		break;
		
		
	}
}

enum RESTART_SM{RESTART_START, RESTART_INIT, RESTART_DISPLAY, RESTART_PAUSE, RESTART_ONEMORE, RESTART_PAUSE_TWO} RESTART_STATE;

void RESTART_TEST()
{
	int highScore =0x00;
	char str[3];
	
	switch(RESTART_STATE)
	{
		case RESTART_START:
			RESTART_STATE = RESTART_INIT;
		break;
		
		case RESTART_INIT:
			if(death && stallFlag)
			{
				RESTART_STATE = RESTART_DISPLAY;
			}
			
			else
			{
				RESTART_STATE = RESTART_INIT;
			}
		break;
		
		case RESTART_DISPLAY:
			RESTART_STATE = RESTART_PAUSE;
		break;
		
		case RESTART_PAUSE:
			if(stallFlagTwo == 20)
			{
				 RESTART_STATE = RESTART_ONEMORE;
			}
			
			else
			{
				stallFlagTwo++;
				RESTART_STATE = RESTART_PAUSE;
			}
		break;
		
		case RESTART_ONEMORE:
				RESTART_STATE = RESTART_PAUSE_TWO;
		break;
		
		case RESTART_PAUSE_TWO:
			buttonPress =  ~PINB & 0x01;
			if(buttonPress)
			{
				restartFlag = 1;
				RESTART_STATE = RESTART_INIT;
			}
		
			else
			{
				RESTART_STATE = RESTART_PAUSE_TWO;
			}
		break;
		
		default:
			RESTART_STATE = RESTART_START;	
	}
	
	switch(RESTART_STATE)
	{
		case RESTART_START:
		break;
		
		case RESTART_INIT:
		break;
		
		case RESTART_DISPLAY:	
			
// 			for(unsigned char k = 4; EEPROM_read(k) != 0xFF; k++)
// 			{
// 				unsigned char tempVal = 0x00;
// 				tempVal = EEPROM_read(k);
// 				
// 				if(tempVal > largestVal)
// 				{
// 					largestVal = tempVal;
// 				}
// 				
// 			}
			
// 			unsigned int highScore = (unsigned int) largestVal; 
// 			
			highScore = (int) EEPROM_read(0x03);
			LCD_DisplayString(1,"   GAME  OVER    HIGH SCORE =100");
			tostring(str, highScore);
			
			
		break;
		
		case RESTART_PAUSE:
			
		break;
		
		case RESTART_ONEMORE:
				LCD_DisplayString(1," PRESS START TO     RESTART     ");
		break;
		
		case RESTART_PAUSE_TWO:
		break;
	}
}


int main(void)
{
    DDRD = 0xFF; PORTD = 0x00; // LCD data lines
    DDRA = 0xFF; PORTA = 0x00; // LCD control lines
	DDRC = 0xFF; PORTC = 0x00;
	DDRB = 0x00; PORTB = 0xFF;
	 
	unsigned short timerKeptOne  = 0x00;
	unsigned short timerKeptTwo  = 0x00;
	unsigned short timerKeptThree  = 0x00;
	unsigned short timerKeptFour  = 0x00;	
	unsigned short timerKeptFive  = 0x00;
	unsigned short timerKeptSix  = 0x00;
	unsigned short timerKeptSev  = 0x00;
	unsigned short timerKeptEigh  = 0x00;
	unsigned short timerKeptNine  = 0x00;
	unsigned short timerKeptTen  = 0x00;
	unsigned short timerKeptEle  = 0x00;
	unsigned short timerKeptTwe  = 0x00;
	unsigned short timerKeptThi  = 0x00;
	unsigned short timerKeptFou  = 0x00;
	
	LCD_CustomChar(1, customCharOne);
	LCD_CustomChar(2, customCharTwo);
	LCD_CustomChar(3, customCharThree);
	LCD_CustomChar(4, customCharFour);
	LCD_WriteCommand(0x80);
	
	
	TimerSet(25);
	TimerOn();
	
	LCD_init();
	LCD_ClearScreen();
	
	START_STATE = START_START;
	CHAR_STATE = CHAR_START; 
	GAME_STATE = GAME_START;
	MOVE_STATE = MOVE_START;
	SEL_STATE = SEL_START;
	ENEMY_STATE = ENEMY_START;
	E1_STATE = E1_START;
	E2_STATE = E2_START;
	E3_STATE = E3_START;
	E4_STATE = E4_START;
	DEATH_STATE = DEATH_START;
	POINTS_STATE = POINTS_START;
	RESTART_STATE = RESTART_START;
	
	
    while(1) 
    {
		
		
		if(timerKeptOne >= 1000)
		{
			START_TEST();
			timerKeptOne = 0;
		}
		
		if(timerKeptTwo >= 100)
		{
			CHARACTER_TEST();
			timerKeptTwo = 0;
		}
		
		if(timerKeptThree >= 100)
		{
			GAME_TEST();
			timerKeptThree = 0;
		}
		
		if(timerKeptFour >= 50)
		{
			MOVE_TEST();
			timerKeptFour = 0;
		}
		
		if (timerKeptFive >= 400)
		{
			SEL_TEST();
			timerKeptFive = 0;
		}
		
		if(timerKeptSix >= 100)
		{
			ENEMY_TEST();
			timerKeptSix = 0;
		}
		
		if(timerKeptSev >= 100)
		{
			E1_TEST();
			timerKeptSev = 0;
		}
		
		if(timerKeptEigh >= 100)
		{
			E2_TEST();
			timerKeptEigh = 0;
		}
		
		if(timerKeptNine >= 100)
		{
			E3_TEST();
			timerKeptNine = 0;
		}
		
		if(timerKeptTen >= 100)
		{
			E4_TEST();
			timerKeptTen = 0;
		}
		
		if(timerKeptEle >= 100)
		{
			DEATH_TEST();
			timerKeptEle = 0;
		}
		
		if(timerKeptThi >= 1000)
		{
			POINTS_TEST();
			timerKeptThi = 0;
		}
		
		if(timerKeptFou >= 50)
		{
			RESTART_TEST();
			timerKeptFou = 0;
		}
		
		while(!TimerFlag);
		TimerFlag = 0;
		
		timerKeptOne += 25;
		timerKeptTwo += 25;
		timerKeptThree += 25;
		timerKeptFour += 25;
		timerKeptFive += 25;
		timerKeptSix += 25;
		timerKeptSev += 25;
		timerKeptEigh += 25;
		timerKeptNine += 25;
		timerKeptTen += 25;
		timerKeptEle += 25;
		timerKeptTwe += 25;
		timerKeptThi += 25;
		timerKeptFou += 25;
    }
}

