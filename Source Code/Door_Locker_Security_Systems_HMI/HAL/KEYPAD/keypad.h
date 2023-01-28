/*--------------------------------------------------------------------------
 [FILE NAME]: keypad.h

 [AUTHOR]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: June 9, 2022

 [DESCRIPTION]: This file contain the definitions and functions prototype of
  	  	  	  	keypad.
 ---------------------------------------------------------------------------*/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../../HELPERS/Std_types.h"

/************************************************************************
 * 							Definitions
 ************************************************************************/

#define KEYPAD_NUM_OF_COLS	4

#if((KEYPAD_NUM_OF_COLS != 4) && (KEYPAD_NUM_OF_COLS != 3))

#error "Wrong number of columns, Keypad driver supported only either 3 or 4 number of columns."

#endif

#define KEYPAD_COLS_PORT_ID	PORTC_ID
#define KEYPAD_ROWS_PORT_ID	PORTC_ID

#define KEYPAD_FIRST_COLUMN_PIN_ID	PIN4_ID
#define KEYPAD_FIRST_ROW_PIN_ID	PIN0_ID
#define KEYPAD_NUM_OF_ROWS	4

#define KEYPAD_BUTTON_PRESSED	LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED	LOGIC_HIGH

#ifndef ENTER
#define ENTER (13)
#endif
/************************************************************************
 * 						Functions' Prototypes
 ************************************************************************/

/*-------------------------------------------------------------------
 [Function Name]: KEYPAD_getPressedKey
 [Arguments]: None
 [Description]:
 [Return]: this function returns the key pressed.
 --------------------------------------------------------------------*/
uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
