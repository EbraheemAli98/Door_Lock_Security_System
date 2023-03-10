/*-----------------------------------------------------------------------------------
 [FILE NAME]: HMI_support.h

 [AUTHER]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: June 18, 2022

 [DESCRIPTION]: This file contains definitions and the declarations of all functions
 	 	 	 	 used in the main application of HMI_ECU.
 ------------------------------------------------------------------------------------*/

#ifndef HMI_SUPPORT_LAYER_HMI_SUPPORT_H_
#define HMI_SUPPORT_LAYER_HMI_SUPPORT_H_

#define __OPTIMIZE__
#undef F_CPU
#define F_CPU 8000000UL
/***********************************************************************************
 * 								INCLUDES
 ***********************************************************************************/
#include "../LIBRARIES/Std_types.h"
#include "../MCAL/UART/uart.h"

/***********************************************************************************
 * 								Definitions
 ***********************************************************************************/
#define NUMBER_OF_DIGITS_IN_PASSWORD (5)
#define MISMATCHED (0)
#define MATCHED (1)

#define ENTER	(13)
#define READY	(0x01)

#define TIME_OF_ALARM	(60) /* 1 min */
#define TIME_OF_DOOR_STOP	(3)   /* 3 sec */
#define TIME_OF_DOOR_OPEN	(15)  /* 15 sec */
#define TIME_OF_DOOR_CLOSE  (15)  /* 15 sec */

#define CHANGE_PASSWORD (44)
#define DOOR_OPEN	(88)

#define OPEN_DOOR_OPTION ('+')
#define CHANGE_PASSWORD_OPTION ('-')

#define MAX_NUM_OF_WRONG_PASS_ENTERED	(3)

/***********************************************************************************
 * 							Extern Global Variables
 ***********************************************************************************/
extern volatile uint8 g_seconds;

#define ENABLE_INTERRUPTS()		SREG|=(1<<7)
#define DISABLE_INTERRUPTS()	sreg&=~(1<<7)
#define HMI_CLEAR_SCREEN()		LCD_clearScreen()
/***********************************************************************************
 * 							 Functions' Prototype
 ***********************************************************************************/
/*----------------------------------------------------------------------------
 [Function Name]:HMI_init
 [Arguments]:None
 [Description]: Function to initiate all the drivers used by HMI ECU.
 	 	 	 	 - initiate LCD (8bits-mode,2 lines).
 	 	 	 	 - initiate uart: 9600 baud-rate,one stop bit, no parity and 8bits data.
 	 	 	 	 - initiate timer1: compare-mode, prescaler_1024.
 [Return]:None
 -----------------------------------------------------------------------------*/
void HMI_Init(void);
/*----------------------------------------------------------------------------
 [Function Name]:HMI_enterPassword
 [Arguments]:None
 [Description]: Function to get the password from the user.
 [Return]:None
 -----------------------------------------------------------------------------*/
void HMI_enterPassword(void);
/*----------------------------------------------------------------------------
 [Function Name]:HMI_enterConfirmPassword
 [Arguments]:None
 [Description]: Function to get the confirmed password for user.
 [Return]:None
 -----------------------------------------------------------------------------*/
void HMI_enterConfirmPassword(void);
/*----------------------------------------------------------------------------
 [Function Name]:HMI_getChosenOption
 [Arguments]: None
 [Description]:Function to get the desired option from the user.
 [Return]: returns the selected option
 -----------------------------------------------------------------------------*/
uint8 HMI_getChosenOption(void);
/*----------------------------------------------------------------------------
 [Function Name]:HMI_sendPassword
 [Arguments]:
 [in]	uint8 a_password:
 	 	 - variable to store the password array that will sent to CONTROL ECU.
 [Description]: Function to send the password to CONTROL ECU.
 [Return]: None
 -----------------------------------------------------------------------------*/
void HMI_sendPassword(uint8 *a_password);
/*----------------------------------------------------------------------------
 [Function Name]:HMI_receivePassword
 [Arguments]:
 [in]	uint8 a_password:
 	 	 - variable to store the password array that is already stored in memory.
 [Description]: Function to return the stored password from memory and store it
 	 	 	 	 in an array.
 [Return]: None
 -----------------------------------------------------------------------------*/
void HMI_readPassword(uint8 *a_password);
/*----------------------------------------------------------------------------
 [Function Name]:HMI_displayOptionMenu
 [Arguments]:None
 [Description]: Funtion to display the option menu.
 [Return]:None
 -----------------------------------------------------------------------------*/
#if 0
void HMI_displayOptionMenu(void);
#endif
/*----------------------------------------------------------------------------
 [Function Name]:HMI_displayDoorAction
 [Arguments]:None
 [Description]:Function to implement the door action.
 [Return]:None
 -----------------------------------------------------------------------------*/
void HMI_displayDoorAction(void);
/*----------------------------------------------------------------------------
 [Function Name]:HMI_passwordInputOperation
 [Arguments]:None
 [Description]:Function to handle the password input operation.
 	 	 	 	- takes the first password from user and send it to Control ECU
 	 	 	 	- takes the second password and send it to the control ECU
 	 	 	 	- display the matchness result on the screen.
 [Return]:None
 -----------------------------------------------------------------------------*/
void HMI_passwordInputOperation(void);

/*----------------------------------------------------------------------------
 [Function Name]:HMI_callBack
 [Arguments]:None
 [Description]:The call back function implemented in ISR each interrupt.
 [Return]:None
 -----------------------------------------------------------------------------*/
void HMI_callBack(void);

/*----------------------------------------------------------------------------
 [Function Name]:HMI_displayAlarmAction
 [Arguments]:None
 [Description]:Function to display the alarm message on the screen.
 [Return]:None
 -----------------------------------------------------------------------------*/
void HMI_displayAlarmAction(void);

/*----------------------------------------------------------------------------
 [Function Name]:HMI_receiveACK
 [Arguments]:None
 [Description]:Function to check the readiness of control ECU.
 [Return]:None
 -----------------------------------------------------------------------------*/
void HMI_receiveACK(void);

/*----------------------------------------------------------------------------
 [Function Name]:HMI_sendACK
 [Arguments]:None
 [Description]:Function to notify control ECU that HMI is ready for contact.
 [Return]:None
 -----------------------------------------------------------------------------*/
void HMI_sendACK(void);
/*----------------------------------------------------------------------------
 [Function Name]:HMI_changePassword
 [Arguments]:
 [in]	uint8 a_NumberOfWrongPasswords:
 	 	 - variable to count the number of wrong password enterred by user.
 [Description]: Function handles the change password option.
 [Return]:None
 -----------------------------------------------------------------------------*/
void HMI_changePassword(uint8 *a_NumberOfWrongPasswords);

/*----------------------------------------------------------------------------
 [Function Name]:HMI_openDoorWrongPassword
 [Arguments]:
[in]	uint8 a_NumberOfWrongPasswords:
 	 	 - variable to count the number of wrong password enterred by user.
 [Description]: Funtion to handle the case of entering a wrong password during
 	 	 	 	 the implementation of open door option.
 [Return]:None
 -----------------------------------------------------------------------------*/
void HMI_openDoorWrongPassword(uint8 *NumberOfWrongPasswrods);

#endif /* HMI_SUPPORT_LAYER_HMI_SUPPORT_H_ */
