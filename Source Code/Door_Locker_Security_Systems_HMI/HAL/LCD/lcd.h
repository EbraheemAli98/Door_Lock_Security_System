/*---------------------------------------------------------------------------------------
 [FILE NAME]: lcd.h

 [AUTHOR]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]:  May 31, 2022

 [DESCRIPTION]: This file contains all functions declaration and types definitions of LCD
 --------------------------------------------------------------------------------------*/

#ifndef HAL_LCD_LCD_H_
#define HAL_LCD_LCD_H_

#include "../../HELPERS/Std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define LCD_DATA_BITS_MODE	8

#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))
#error "Number of Data bits should be equal to 4 or 8"
#endif

#if(LCD_DATA_BITS_MODE == 4)

#define LCD_LAST_PORT_PINS

#ifdef LCD_LAST_PORT_PINS
#define LCD_FIRST_DATA_PIN_ID	PIN4_ID
#else
#define LCD_FIRST_DATA_PIN_ID	PIN0_ID
#endif

#endif

#define LCD_DATA_PORT_ID	PORTA_ID

#define LCD_RS_PORT_ID		PORTB_ID
#define LCD_RS_PIN_ID		PIN0_ID

#define LCD_RW_PORT_ID		PORTB_ID
#define LCD_RW_PIN_ID		PIN1_ID

#define LCD_E_PORT_ID		PORTB_ID
#define LCD_E_PIN_ID		PIN2_ID

#define LCD_SET_CURSOR_POSITION 0x80
#define LCD_2LINES_8BIT_MODE	0x38
#define LCD_2LINES_4BIT_MODE	0x28
#define DISPLAY_ON_CURSOR_OFF	0x0C
#define DISPLAY_ON_CURSOR_ON	0x0E
#define LCD_GO_TO_HOME_POSITION	0x02
#define LCD_CLEAR_COMMAND		0x01

#define LCD_FIRST_LINE_FIRST_COL_ADDRESS	0x00
#define LCD_SECOND_LINE_FIRST_COL_ADDRESS   0x40
#define LCD_THIRD_LINE_FIRST_COL_ADDRESS    0x10
#define LCD_FOURTH_LINE_FIRST_COL_ADDRESS	0x50

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*-------------------------------------------------------------------------------
 [Function Name]: LCD_sendCommand
 [Args]:
 [in]	uint8 command:
 	 	 	 - This parameter store the value of the command needed to performed.
 [Description]:
  	   	  -	Send the required command to the screen
[Return]: This function returns nothing.
 -------------------------------------------------------------------------------*/
void LCD_sendCommand(uint8 command);

/*-------------------------------------------------------------------------------
 [Function Name]: LCD_init
 [Args]:
 [Description]:
  	  1. Setup the LCD pins directions by use the GPIO driver.
  	  2. Setup the LCD Data Mode 4-bits or 8-bits.
[Return]: This function returns nothing.
 -------------------------------------------------------------------------------*/
void LCD_init(void);

/*-------------------------------------------------------------------------------
 [Function Name]: LCD_displayCharacter
 [Args]:
 [in]	uint8 character:
 	 	 	 - This parameter store the character need to be displayed.
 [Description]:
  	  	  - Display the required character on the screen
[Return]: This function returns nothing.
 -------------------------------------------------------------------------------*/
void LCD_displayCharacter(uint8 character);

/*-------------------------------------------------------------------------------
 [Function Name]: LCD_sendCommand
 [Args]:
 [in]	const char Str:
 	 	 	 - This parameter is a pointer to const data stores the string address.
 [Description]:
  	  	  - Display the required string on the screen.
[Return]: This function returns nothing.
 -------------------------------------------------------------------------------*/
void LCD_displayString(const char *Str);

/*-------------------------------------------------------------------------------
 [Function Name]: LCD_integerToString
 [Args]:
 [in]	int num:
 	 	 	 - This parameter store the number needed to be displayed.
 [Description]:
  	  	  - Display the required decimal value on the screen.
[Return]: This function returns nothing.
 -------------------------------------------------------------------------------*/
void LCD_integerToString(int num);

/*-------------------------------------------------------------------------------
 [Function Name]: LCD_moveCursor
 [Args]:
 [in]	uint8 row:
 	 	 	 - This parameter store the index of the row on a screen.
 [in]	uint8 col:
  	 	 	 - This parameter store the index of the column on a screen.
 [Description]:
  	  	  - Move the cursor to a specified row and column index on the screen.
[Return]: This function returns nothing.
 -------------------------------------------------------------------------------*/
void LCD_moveCursor(uint8 row,uint8 col);

/*-------------------------------------------------------------------------------
 [Function Name]: LCD_displayStringRowColumn
 [Args]:
 [in]	uint8 row:
 	 	 	 -  This parameter store the index of the row on a screen.
 [in]   uint8 col:
  	 	 	 - This parameter store the index of the column on a screen.
 [in]   const char str:
   	 	 	 - Pointer to const char store an array of characters.
 [Description]:
  	  	  - Display the required string in a specified row and column index on the screen.
[Return]: This function returns nothing.
 -------------------------------------------------------------------------------*/
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *str);

/*-------------------------------------------------------------------------------
 [Function Name]: LCD_sendCommand
 [Args]:
 [Description]:
  	  	  - Display the required string on the screen.
[Return]: This function returns nothing.
 -------------------------------------------------------------------------------*/
void LCD_clearScreen(void);

#endif /* HAL_LCD_LCD_H_ */
