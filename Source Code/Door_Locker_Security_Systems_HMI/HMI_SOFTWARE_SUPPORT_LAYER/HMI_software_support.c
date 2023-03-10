/*-----------------------------------------------------------------------------------
 [FILE NAME]: HMI_support.c

 [AUTHER]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: June 18, 2022

 [DESCRIPTION]: This file contains the definitions of all functions used in the main
 	 	 	 	application of HMI_ECU.
 ------------------------------------------------------------------------------------*/

#include "HMI_software_support.h"
#include "../HAL/KEYPAD/keypad.h"
#include "../HAL/LCD/lcd.h"
#include <util/delay.h>
#include "../MCAL/GPT/Gpt.h"
/***********************************************************************************************
							 	 	 Global Variables
 ***********************************************************************************************/

/*------------------------------------------------------------------------------------------
 * [g_seconds]: variable to count the number of seconds at each interrupt come.
 * [T1_ConfigObj]: variable of type object from a structure stores the Timer configuartions.
 -------------------------------------------------------------------------------------------*/

volatile uint8 g_seconds = 0;


/*************************************************************************************************
 * 								Functions' Definitions
 *************************************************************************************************/

/*==================================== HMI_init ===============================================*/
void HMI_Init(void)
{
	/********************************************************************************************
	 * 1. initiate the timer configuration:timer1,compare-mode,prescaler_1024.
	 * 2. set the callback function = HMI_callBack.
	 * 3. initiate LCD.
	 * 4. set the uart configuration: 9600 baud-rate, one stop bit, 8bits-data,and no parity bit.
	 ********************************************************************************************/
//	TIMER_configType T1_ConfigObj;
//	T1_ConfigObj.mode = CTC;
//	T1_ConfigObj.TimerInitValue = 0;
//	T1_ConfigObj.TimerCompValue = 7811;
//	T1_ConfigObj.prescaler = PRESCALER_1024;
//	TIMER1_init(&T1_ConfigObj);
	GPT_startTimer(T1);
	GPT_T1_setCallBack(HMI_callBack);
	LCD_init();
	UART_ConfigType uart_configObj = {9600,EIGHT_BITS,DISABLE_PARITY,ONE_STOP_BIT};
	UART_init(&uart_configObj);
	GPT_enableNotification(T1, OUTPUT_COMPARE);
}

/*==================================== get_password ============================================*/
void HMI_enterPassword(void)
{
	uint8 a_pass_array[NUMBER_OF_DIGITS_IN_PASSWORD],key,i=0;
	LCD_displayString("Enter Your Pass");
	LCD_moveCursor(1, 5);
	while(i<5)
		{
			key = KEYPAD_getPressedKey();
			if(key >= 0 && key <= 9)
			{
				a_pass_array[i] = key;
				LCD_displayCharacter('*');
			}
			else
			{
				--i;
			}

			_delay_ms(500);
			i++;
		}
	while(KEYPAD_getPressedKey() != ENTER);
	UART_sendByte(READY);
	while(UART_receiveByte() != READY);
	HMI_sendPassword(a_pass_array);
}
/*==================================== get_confirmPassword =======================================*/
void HMI_enterConfirmPassword(void)
{
	uint8 key,i=0, a_confim_array[NUMBER_OF_DIGITS_IN_PASSWORD];
	LCD_displayString("Reenter The Pass");
	LCD_moveCursor(1, 5);
	while(i<5)
		{
			key = KEYPAD_getPressedKey();
			if(key >= 0 && key <= 9)
			{
				a_confim_array[i] = key;
				LCD_displayCharacter('*');
			}
			else
			{
				--i;
			}
			_delay_ms(500);
			i++;
		}
	while(KEYPAD_getPressedKey() != ENTER);
	UART_sendByte(READY);
	while(UART_receiveByte() != READY);
	HMI_sendPassword(a_confim_array);
}
/*================================= displayChecknessResult =======================================*/
void HMI_passwordInputOperation(void)
{
	uint8 a_password = 0;
	/******************************************************************************************************
	 * 1. Take the password from user and send it to the control ECU.
	 * 2. clear the screen.
	 * 3. Take the confirm password and send it to the control ECU.
	 * 4. clear the screen.
	 * 5. wait the control ECU to finish its task(comparing the two input passwords) and send ready to it.
	 * 6. receive the compare result in variable temp.
	 * 7. if the compare message = matched:
	 * 	7-1. clear the screen.
	 * 	7-2. display "matched".
	 * 	7-3. display "password saved" on the next line.
	 * 	7-4. wait for 500  msec.
	 * 	7-5. clear screen.
	 * 8. if the compare message = mis-matched:
	 * 	8-1. clear the screen.
	 * 	8-2. display "MISMATCHED" .
	 * 	8-3. displsy "Try Again" on the next line.
	 * 	8-4. wait for 500 msec.
	 * 	8-5. clear the screen.
	 * 9. loop until the user enter a matched passwords.
	 *******************************************************************************************************/
		do
		{
			HMI_enterPassword();
			LCD_clearScreen();
			HMI_enterConfirmPassword();
			LCD_clearScreen();
			HMI_receiveACK();
			a_password = UART_receiveByte();
			switch(a_password)
			{
			case MATCHED:
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 5, "MATCHED");
				LCD_displayStringRowColumn(1, 2, "Password Saved");
				_delay_ms(500);
				LCD_clearScreen();
				break;
			case MISMATCHED:
				LCD_clearScreen();
				LCD_moveCursor(0, 3);
				LCD_displayString("MISMATCHED");
				LCD_displayStringRowColumn(1, 3, "TRY AGAIN");
				_delay_ms(500);
				LCD_clearScreen();
				break;
			default:
				break;
			}
//			if(a_password == MATCHED)
//			{
//				LCD_clearScreen();
//				LCD_displayStringRowColumn(0, 5, "MATCHED");
//				LCD_displayStringRowColumn(1, 2, "Password Saved");
//				_delay_ms(500);
//				LCD_clearScreen();
//			}
//			else
//			{
//				LCD_clearScreen();
//				LCD_moveCursor(0, 3);
//				LCD_displayString("MISMATCHED");
//				LCD_displayStringRowColumn(1, 3, "TRY AGAIN");
//				_delay_ms(500);
//				LCD_clearScreen();
//			}
		}while(a_password == MISMATCHED);
}
/*==================================== HMI_getChosenOption ================================*/
uint8 HMI_getChosenOption(void)
{
	uint8 a_option = 0;
	do
	{
		LCD_displayString("+:Open Door");
		LCD_displayStringRowColumn(1, 0, "-:Change Pass");
		a_option = KEYPAD_getPressedKey();
	}while((a_option != OPEN_DOOR_OPTION && a_option != CHANGE_PASSWORD_OPTION));
	return a_option;
}
/*==================================== sendPassword =======================================*/
void HMI_sendPassword(uint8 *a_password)
{
	uint8 i;
	for(i=0; i<NUMBER_OF_DIGITS_IN_PASSWORD; i++)
	{
		UART_sendByte(a_password[i]);
		_delay_ms(50);
	}
}
/*==================================== readPassword =======================================*/
void HMI_readPassword(uint8 *a_password)
{
	uint8 i;
	for(i=0; i< NUMBER_OF_DIGITS_IN_PASSWORD; i++)
	{
		a_password[i] = UART_receiveByte();
		_delay_ms(50);
	}
}
/*==================================== displayOptionMenu =======================================*/
#if DISABLE
void HMI_displayOptionMenu(void)
{
	LCD_displayString("+:Open Door");
	LCD_displayStringRowColumn(1, 0, "-:Change Pass");
}
#endif
/*======================================== Door_action ==========================================*/
void HMI_displayDoorAction(void)
{
	/***************************************************
	 * 1. reset the value of g_seconds.
	 * 2. clear the screen.
	 * 3. display "Door Is Opening"
	 * 4. wait for 15 seconds.
	 * 5. clear the screen.
	 * 6. display "Door Open..".
	 * 7. wait for 3 seconds.
	 * 8. clear the screen.
	 * 9. display "Door Is Closing".
	 * 10. wait for 15 seconds.
	 * 11. clear screen.
	 * 12. display "Door close" for 100 msec.
	 * 13. clear the screen.
	 **************************************************/
	g_seconds = 0;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Door Is Opening");
	while(g_seconds < TIME_OF_DOOR_OPEN);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Door Open..");
	while(g_seconds < (TIME_OF_DOOR_STOP+TIME_OF_DOOR_OPEN));
	LCD_clearScreen();
	LCD_displayString("Door Is Closing");
	while(g_seconds < (TIME_OF_DOOR_STOP+TIME_OF_DOOR_OPEN+TIME_OF_DOOR_CLOSE));
	LCD_clearScreen();
	LCD_displayString("Door close");
	_delay_ms(100);
	LCD_clearScreen();
}
/*======================================== implementOptionMenu ==========================================*/
void HMI_callBack(void)
{
	g_seconds++;
}

/*======================================== HMI_receiveACK ==========================================*/
void HMI_receiveACK(void)
{
	/* Wait until the control ECU check the password*/
	while(UART_receiveByte() != READY);
	UART_sendByte(READY);
}
/*======================================== HMI_sendACK ==========================================*/
void HMI_sendACK(void)
{
	UART_sendByte(READY);
	while(UART_receiveByte() != READY);
}
/*======================================== HMI_displayAlarmAction =======================================*/
void HMI_displayAlarmAction(void)
{
	g_seconds = 0;
	LCD_clearScreen();
	LCD_displayString("ERROR OPERATION");
	while(g_seconds < TIME_OF_ALARM);
	LCD_clearScreen();
}
/*======================================== HMI_openDoorCheckPassword =====================================*/
void HMI_openDoorWrongPassword(uint8 *a_NumberOfWrongPasswords)
{
	//uint8 a_verification_message = 0;
	/***********************************************************************************************
	 * 1. increment the number of wrong passwords by 1.
	 * 2. clear the screen.
	 * 3. display "Wrong Password" on the screen.
	 * 4. wait for 500 msec.
	 * 5. take the password from user and send it to the control ECU.
	 * 6. check if CONTROL ECU had finished its task and ready for communicate.
	 * 7. receve the verification message from the control ECU.
	 * 8. if the verification message = Matched.
	 * 	8-1. reset the number of wrong passwords to 0.
	 * 	8-2. implement the door action.
	 * 	8-3. exit from the loop.
	 * 9. if the verification message is equal Mismatched:
	 * 	9-1. loop again until enter the correct passwords.
	 * 10. if the number of wrong passwords reaches its maximum value (3):
	 * 	10-1. exit from the loop.
	 * 	10-2. reset the number of wrong passwords to 0.
	 * 	10-3. display the alarm message.
	 *************************************************************************************************/
	while((*a_NumberOfWrongPasswords)< MAX_NUM_OF_WRONG_PASS_ENTERED)
	{
	(*a_NumberOfWrongPasswords)++;
	LCD_clearScreen();
	LCD_displayString("Wrong Password");
	_delay_ms(500);
	LCD_clearScreen();
	/* enter the password again from user */
	HMI_enterPassword();
	/* check if CONTROL ECU had finished its task and ready for communicate */
	HMI_receiveACK();
	/* receive the result of comparsion between the two passwords */
	//a_verification_message = UART_receiveByte();
	if(UART_receiveByte() == MATCHED)
	{
		(*a_NumberOfWrongPasswords) = 0;
		HMI_displayDoorAction();
		break;  /* exit the while loop */
	}
	}
	if((*a_NumberOfWrongPasswords) == MAX_NUM_OF_WRONG_PASS_ENTERED)
	{
		(*a_NumberOfWrongPasswords) = 0;
		HMI_displayAlarmAction();
	}
}
/*================================= HMI_changePassword ======================================*/
void HMI_changePassword(uint8 *a_NumberOfWrongPasswords)
{
	//uint8 a_verificationMessage = 0;
	/***************************************************************************************************************************
	 * 1. clear the screen.
	 * 2. send ready to contact to the CONTROL ECU, and wait until it is ready.
	 * 3. send the selected option (CHANGE_PASSWORD_OPTION) to the control ECU.
	 * 4. take the password from user,and send it to the control ECU.
	 * 5. wait until control ECU finish its task (compare the password sent with the old one) and send the verification message.
	 * 6. receive the verification message from user.
	 * 7. if the verification message is CHANGE_PASSWORD:
	 * 	7-1. clear the screen.
	 * 	7-2. set the new password.
	 * 	7-3. reset the value of number of wrong passwords to 0.
	 * 8. if the verification message in MISMATCHED:
	 * 	8-1. increment the number of wrong passwords by 1.
	 * 	8-2. clear the screen.
	 * 	8-3. display "Wrong Password".
	 * 	8-4. wait for 500msec.
	 * 	8-5. clear the screen.
	 * 	8-6. enter the password again, and send it to control ECU to check its correctance.
	 * 	8-7. wait until control ECU finich.
	 * 	8-8. receive the verification message again.
	 * 	8-9. if the verification message is CHANGE_PASSWORD:
	 * 		8-9-1. clear the screen.
	 * 		8-9-2. reset number of wrong passwords to zero.
	 * 		8-9-3. set the new password.
	 * 		8-9-4. exit from the loop.
	 * 	8-10. loop until the password is matched or the number of wrong passwords reach its maximum value (3).
	 * 	8-11. if the number of wrong passwords == 3:
	 * 		8-11-1. reset the value of number of wrong passwords.
	 * 		8-11-2. display the alarm action.
	 * 9. clear the screen.
	 *********************************************************************************************************************************/
 	LCD_clearScreen();

 	HMI_sendACK();
	UART_sendByte(CHANGE_PASSWORD_OPTION);

	/************** Actualy start ***********************/
	HMI_enterPassword();
	HMI_receiveACK();
	//a_verificationMessage = UART_receiveByte();

	if(UART_receiveByte() == CHANGE_PASSWORD)
	{
	 	LCD_clearScreen();
	 	HMI_passwordInputOperation();
		(*a_NumberOfWrongPasswords) = 0;
	}
	else if(UART_receiveByte() == MISMATCHED)
	{
		while((*a_NumberOfWrongPasswords) < MAX_NUM_OF_WRONG_PASS_ENTERED)
		{
			(*a_NumberOfWrongPasswords)++;
			LCD_clearScreen();
			LCD_displayString("Wrong Password");
			_delay_ms(500);
			LCD_clearScreen();
			HMI_enterPassword();
			HMI_receiveACK();
			//a_verificationMessage = UART_receiveByte();

			if(UART_receiveByte() == CHANGE_PASSWORD)
			{
				LCD_clearScreen();
				(*a_NumberOfWrongPasswords) = 0;
				HMI_passwordInputOperation();
				break;
			}
		}
		if((*a_NumberOfWrongPasswords) == MAX_NUM_OF_WRONG_PASS_ENTERED)
		{
			(*a_NumberOfWrongPasswords) = 0;
			HMI_displayAlarmAction();
		}
	}
	LCD_clearScreen();
}

