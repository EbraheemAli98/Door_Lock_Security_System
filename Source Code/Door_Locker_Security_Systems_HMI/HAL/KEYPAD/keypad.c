/*--------------------------------------------------------------------------
 [FILE NAME]: keypad.c

 [AUTHOR]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: June 9, 2022

 [DESCRIPTION]:
 ---------------------------------------------------------------------------*/
#include "../../MCAL/GPIO/gpio.h"
#include "keypad.h"
#include "../../LIBRARIES/comman_macros.h"

/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/
#if(KEYPAD_NUM_OF_COLS == 4)
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_num);

#elif(KEYPAD_NUM_OF_COLS == 3)
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_num);

#endif

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
uint8 KEYPAD_getPressedKey(void)
{
	uint8 col,row;
	uint8 keypad_port_value = 0;
	GPIO_setupPortDirection(KEYPAD_ROWS_PORT_ID, PORT_INPUT);
	GPIO_setupPortDirection(KEYPAD_COLS_PORT_ID, PORT_INPUT);
	while(1)
	{
		for(col=0; col< KEYPAD_NUM_OF_COLS; col++)
		{
			GPIO_setupPinDirection(KEYPAD_COLS_PORT_ID, KEYPAD_FIRST_COLUMN_PIN_ID+col, PIN_OUTPUT);
#if(KEYPAD_BUTTON_PRESSED == LOGIC_LOW)
			keypad_port_value = ~(1<<(KEYPAD_FIRST_COLUMN_PIN_ID+col));
#else
			keypad_port_value = (1<<(KEYPAD_FIRST_COLUMN_PIN_ID+col));
#endif
			GPIO_writePort(KEYPAD_COLS_PORT_ID,keypad_port_value);
			for(row=0; row<KEYPAD_NUM_OF_ROWS; row++)
			{
				if(GPIO_readPin(KEYPAD_ROWS_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row) == KEYPAD_BUTTON_PRESSED)
				{
#if(KEYPAD_NUM_OF_COLS == 3)
					return KEYPAD_4x3_adjustKeyNumber((row*KEYPAD_NUM_OF_COLS)+col+1);
#elif(KEYPAD_NUM_OF_COLS == 4)
					return KEYPAD_4x4_adjustKeyNumber((row*KEYPAD_NUM_OF_COLS)+col+1);
#endif
				}
			}
		}
	}
}
#if(KEYPAD_NUM_OF_COLS == 3)

	static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number)
	{
		uint8 keypad_button = 0;
		switch(button_number)
		{
		case 10: keypad_button = '*'; // ASCII Code of *
		break;
		case 11: keypad_button = 0;
		break;
		case 12: keypad_button = '#'; // ASCII Code of #
		break;
		default: keypad_button = button_number;
		break;
		}
		return keypad_button;
	}

#elif(KEYPAD_NUM_OF_COLS == 4)

	static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_num)
	{
		uint8 keypad_button = 0;
		switch(button_num)
		{
		default:
			keypad_button = button_num;
			break;
		case 1:
			keypad_button = 7;
			break;
		case 2:
			keypad_button = 8;
			break;
		case 3:
			keypad_button = 9;
			break;
		case 4:
			keypad_button = '/';
			break;
		case 5:
			keypad_button = 4;
			break;
		case 6:
			keypad_button = 5;
			break;
		case 7:
			keypad_button = 6;
			break;
		case 8:
			keypad_button = '*';
			break;
		case 9:
			keypad_button = 1;
			break;
		case 10:
			keypad_button = 2;
			break;
		case 11:
			keypad_button = 3;
			break;
		case 12:
			keypad_button = '-';
			break;
		case 13:
			keypad_button = ENTER; /* ASCII of Enter */
			break;
		case 14:
			keypad_button = 0;
			break;
		case 15:
			keypad_button = '=';
			break;
		case 16:
			keypad_button = '+';
			break;
		}

		return keypad_button;
	}

#endif
