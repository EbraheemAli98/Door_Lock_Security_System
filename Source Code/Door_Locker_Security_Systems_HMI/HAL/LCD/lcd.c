/*---------------------------------------------------------------------------------------
 [FILE NAME]: lcd.c

 [AUTHOR]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: May 31, 2022

 [DESCRIPTION]: This file contains the lcd functions definition.
 --------------------------------------------------------------------------------------*/

#include "../../HELPERS/comman_macros.h"
#include "../../MCAL/GPIO/gpio.h"
#include <util/delay.h>
#include <stdlib.h>
#include "lcd.h"


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void LCD_sendCommand(uint8 command)
{
	/***********************************************
	 * set RS = 0 , send command.
	 * set RW = 0 , Write on LCD.
	 * wait time = tas (50ns)
	 * Active E pin HIGH.
	 * wait time = tpw - tdsw (290ns - 100ns)
	 * send command
	 * wait
	 * Active E pin LOW
	 * wait
	 ************************************************/
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);
	GPIO_writePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LOGIC_LOW);
	_delay_us(50);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_us(200);
#if(LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID, command);
	_delay_us(100);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_us(15);
#elif(LCD_DATA_BITS_MODE == 4)
	/******************************************************************************
	 * Read the value in the LCD_DATA_PORT and store it in lcd_port_value
	 * if the Most 4bits in LCD_DATA_PORT are connected, Put the Most 4bits
	 * 	of the command on it then send the Least 4bits in command to LCD_DATA_PORT
	 * if the least 4bits in LCD_DATA_PORT are connected, Put the Most 4bits of
	 *  the command on it, then send the Least 4bits in command to LCD_DATA_PORT.
	 ******************************************************************************/
	uint8 lcd_port_value = 0;
	lcd_port_value = GPIO_readPort(LCD_DATA_PORT_ID);
#ifdef LCD_LAST_PORT_PINS
	lcd_port_value = (lcd_port_value & 0x0F) | (command & 0xF0);
#else
	lcd_port_value = (lcd_port_value & 0xF0) | ((command & 0xF0)>>4)
#endif
	GPIO_writePort(LCD_DATA_PORT_ID,lcd_port_value);
	_delay_us(100);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_us(15);

	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	_delay_us(200);

	lcd_port_value = GPIO_readPort(LCD_DATA_PORT_ID);
#ifdef LCD_LAST_PORT_PINS
	lcd_port_value = (lcd_port_value & 0x0F) | ((command & 0x0F)<<4);
#else
	lcd_port_value = (lcd_port_value & 0xF0) | (command & 0x0F);
#endif
	GPIO_writePort(LCD_DATA_PORT_ID,lcd_port_value);
	_delay_us(100);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_us(15);
#endif
}

void LCD_init(void)
{
	/***********************************************
	 * initialize LCD_DATA_PORT.
	 * initialize LCD_RS_PIN
	 * initialize LCD_RW_PIN
	 * initialize LCD_E_PIN
	 * set LCD configuration. 2lines,8bit mode
	 * clear screen
	 * turn on display
	 ************************************************/
	GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_RW_PORT_ID,LCD_RW_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,PIN_OUTPUT);

#if(LCD_DATA_BITS_MODE == 4)
	/* Configure 4 pins in the data port as output pins with unrolling loop */
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_FIRST_DATA_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_FIRST_DATA_PIN_ID+1,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_FIRST_DATA_PIN_ID+2,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_FIRST_DATA_PIN_ID+3,PIN_OUTPUT);
	LCD_sendCommand(LCD_GO_TO_HOME_POSITION);
	LCD_sendCommand(LCD_2LINES_4BIT_MODE);
#elif(LCD_DATA_BITS_MODE == 8)
	GPIO_setupPortDirection(LCD_DATA_PORT_ID, PORT_OUTPUT);
	LCD_sendCommand(LCD_GO_TO_HOME_POSITION);
	LCD_sendCommand(LCD_2LINES_8BIT_MODE);
#endif

	LCD_sendCommand(LCD_CLEAR_COMMAND);
	LCD_sendCommand(DISPLAY_ON_CURSOR_OFF);
}

void LCD_displayCharacter(uint8 character)
{
	/************************************************
	 * set RS = 1 , send data.
	 * set RW = 0 , Write on LCD.
	 * wait time = tas (50ns)
	 * Active E pin HIGH
	 * wait time = tpw - tdsw (290ns - 100ns)
	 * send data
	 * wait
	 * Active E pin LOW
	 * wait
	 *************************************************/
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);
	GPIO_writePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LOGIC_LOW);
	_delay_us(50);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_us(200);
#if(LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID, character);
	_delay_us(100);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_us(15);
#elif(LCD_DATA_BITS_MODE == 4)
	/******************************************************************************
	 * Read the value in the LCD_DATA_PORT and store it in lcd_port_value
	 * if the Most 4bits in LCD_DATA_PORT are connected, Put the Most 4bits
	 * 	of the command on it then send the Least 4bits in command to LCD_DATA_PORT
	 * if the least 4bits in LCD_DATA_PORT are connected, Put the Most 4bits of
	 *  the command on it, then send the Least 4bits in command to LCD_DATA_PORT.
	 ******************************************************************************/
	uint8 lcd_port_value = 0;
	lcd_port_value = GPIO_readPort(LCD_DATA_PORT_ID);
#ifdef LCD_LAST_PORT_PINS
	lcd_port_value = (lcd_port_value & 0x0F) | (character & 0xF0);
#else
	lcd_port_value = (lcd_port_value & 0xF0) | ((character & 0xF0)>>4)
#endif
	GPIO_writePort(LCD_DATA_PORT_ID,lcd_port_value);
	_delay_us(100);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_us(15);

	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	_delay_us(200);

	lcd_port_value = GPIO_readPort(LCD_DATA_PORT_ID);
#ifdef LCD_LAST_PORT_PINS
	lcd_port_value = (lcd_port_value & 0x0F) | ((character & 0x0F)<<4);
#else
	lcd_port_value = (lcd_port_value & 0xF0) | (character & 0x0F);
#endif
	GPIO_writePort(LCD_DATA_PORT_ID,lcd_port_value);
	_delay_us(100);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_us(15);
#endif
}

void LCD_displayString(const char *Str)
{
	/**************************************************
	 * loop on Str until reach '\0'
	 * display each character of the string
	 * increment the pointer.
	 **************************************************/
	while(*Str != '\0')
	{
		LCD_displayCharacter(*Str);
		++Str;
	}
}

void LCD_integerToString(int num)
{
	/**************************************************************************
	 * use itoa built in fuction to convert from integer to string.
	 * itoa(integer to ASCII).
	 * itoa takes three arguments :
	 * int num: the integer needed to be converted.
	 * char *str: the string contains the ASCII of the integer.
	 * base : the base of the number (Decimal(10),Binary(2),Octal(8),Hex(16)).
	 ***************************************************************************/
	char String[16];
	itoa(num,String,10);
	LCD_displayString(String);
}

void LCD_moveCursor(uint8 row_index,uint8 col_index)
{
	/*************************************************************
	 * set the address of the column depend on two parameters..
	 * 1. column index.
	 * 2. address of the first column in the row.
	 * add the final address to the address of the origin(0,0) to..
	 * calculate the address referred to the origin.
	 *************************************************************/
	uint8 a_lcd_col_address = LCD_FIRST_LINE_FIRST_COL_ADDRESS;
	switch(row_index)
	{
	case 0:
		a_lcd_col_address += col_index;
		break;
	case 1:
		a_lcd_col_address += (col_index+LCD_SECOND_LINE_FIRST_COL_ADDRESS);
		break;
	case 2:
		a_lcd_col_address += (col_index+LCD_THIRD_LINE_FIRST_COL_ADDRESS);
		break;
	case 3:
		a_lcd_col_address += (col_index+LCD_FOURTH_LINE_FIRST_COL_ADDRESS);
		break;
	}
	LCD_sendCommand(a_lcd_col_address|LCD_SET_CURSOR_POSITION);
}

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	/**********************************************
	 * move to the desired position.
	 * display the string.
	 **********************************************/
	LCD_moveCursor(row, col);
	LCD_displayString(Str);
}

void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}
