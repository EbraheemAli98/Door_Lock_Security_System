/*-----------------------------------------------------------------------------------------------------
 [FILE NAME]: CONTROL_software_support.c

 [AUTHOR]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: June 19, 2022

 [DESCRIPTION]: This file contains the functions' definitions of the control_ECU application.
 ------------------------------------------------------------------------------------------------------*/


/***********************************************************************************************
							 	 		INCLUDES
 ***********************************************************************************************/
#include "CONTROL_software_support.h"
#include "../HAL/EEPROM/eeprom.h"
#include "../MCAL/GPT/Gpt.h"
#include <util/delay.h>
#include "../HAL/BUZZER/Buzzer.h"
#include "../HAL/DC_MOTOR/Motor.h"

/***********************************************************************************************
							 	 	 Global Variables
 ***********************************************************************************************/
volatile uint8 g_seconds = 0;
uint8 g_currentPassword_array[NUMBER_OF_DIGITS_IN_PASSWORD];
uint8 g_confirmPassword_array[NUMBER_OF_DIGITS_IN_PASSWORD];


/************************************************************************************************
 	 	 	 	 	 	 	 	 	 Functions' Definition
 ************************************************************************************************/

/*==================================== CONTROL_init ===============================================*/
void CTRL_Init(void)
{
	/*********************************************************************************************************
	 * 1. initiate the EEPROM.
	 * 2. initiate the Buzzer.
	 * 3. initiate the motor.
	 * 4. initiate the timer to Timer1, compare-mode, prescaler_1024,and set the initial and compare values.
	 * 5. initiate the UART to baud-rate=9600, 8-bits data, one stop bit and no parity.
	 **********************************************************************************************************/
	EEPROM_Init();
	BUZZER_Init(&BuzzerConfig);
	MOTOR_Init(&MotorConfig);
	GPT_startTimer(T1);
	GPT_T1_setCallBack(CTRL_callBack);
	UART_ConfigType uart_configObj = {9600,EIGHT_BITS,DISABLE_PARITY,ONE_STOP_BIT};
	UART_Init(&uart_configObj);
	GPT_enableNotification(T1, OUTPUT_COMPARE);
}
/*======================================== HMI_receiveACK ==========================================*/
void CTRL_receiveACK(void)
{
	/* Wait until the control ECU check the password*/
	while(UART_receiveByte() != READY);
	UART_sendByte(READY);
}
/*======================================== HMI_sendACK ==========================================*/
void CTRL_sendACK(void)
{
	UART_sendByte(READY);
	while(UART_receiveByte() != READY);
}
/*==================================== receivePassword ===============================================*/
void CTRL_receivePassword(uint8 *a_password)
{
	uint8 i;
	for(i=0; i<NUMBER_OF_DIGITS_IN_PASSWORD;i++)
	{
		a_password[i] = UART_receiveByte();
		_delay_ms(50);
	}
}
/*==================================== sendPassword ===============================================*/
void CTRL_sendPassword(uint8 *a_password)
{
	uint8 i;
	for(i=0; i<NUMBER_OF_DIGITS_IN_PASSWORD; i++)
	{
		UART_sendByte(a_password[i]);
		_delay_ms(50);
	}
}
/*==================================== savePassword ===============================================*/
void CTRL_savePassword(void)
{
	uint8 i;
	for(i=0;i<NUMBER_OF_DIGITS_IN_PASSWORD;i++)
	{
		EEPROM_writeByte((PASSWORD_START_ADDRESS_IN_MEMORY+i), g_currentPassword_array[i]);
		_delay_ms(50);
	}
}
/*==================================== readPassword ===============================================*/
void CTRL_readPassword(void)
{
	uint8 i;
	for(i=0; i< NUMBER_OF_DIGITS_IN_PASSWORD; i++)
	{
		EEPROM_readByte(PASSWORD_START_ADDRESS_IN_MEMORY+i, &g_currentPassword_array[i]);
	}
}
/*==================================== compare_TwoPasswords ========================================*/
uint8 CTRL_compareTwoPasswords(void)
{
	uint8 i,verify = MATCHED;
	for(i=0; i < NUMBER_OF_DIGITS_IN_PASSWORD; i++)
	{
		if(g_currentPassword_array[i] != g_confirmPassword_array[i])
		{
			verify = MISMATCHED;
			break;
		}
	}
	return verify;
}
/*==================================== PasswordInputOperation =======================================*/
void CTRL_passwordInputOperation(void)
{
	uint8 temp = 0;
	/****************************************************************************************
	 * 1. wait HMI to finish its task (getting the password) .
	 * 2. receive password from HMI.
	 * 3. wait HMI to finish its task (getting the confirmed password) and send ready to it.
	 * 4. compare the two passwords and store the result in variable temp.
	 * 5. if two passwords are matched store the password in memory.
	 * 6. send ready to contact to HMI and wait if until finish its task and respond by ready.
	 * 7. send the result of comparsion to HMI.
	 * 8. loop until the two password are matched.
	 ****************************************************************************************/
		do{
			while(UART_receiveByte() != READY);
			UART_sendByte(READY);
			CTRL_receivePassword(g_currentPassword_array);
			while(UART_receiveByte() != READY);
			UART_sendByte(READY);
			CTRL_receivePassword(g_confirmPassword_array);
			temp = CTRL_compareTwoPasswords();
			if(temp == MATCHED)
			{
				CTRL_savePassword();
			}
			UART_sendByte(READY);
			while(UART_receiveByte() != READY);
			UART_sendByte(temp);
		}while(temp == MISMATCHED);
}
/*=================================== display_DoorAction =============================================*/
void CTRL_doorAction(void)
{
	g_seconds = 0;
	MOTOR_rotateCW(&MotorConfig,M0);
	while(g_seconds < TIME_OF_DOOR_OPEN);
	MOTOR_stop(&MotorConfig,M0);
	while(g_seconds < (TIME_OF_DOOR_OPEN+TIME_OF_DOOR_STOP));
	MOTOR_rotateACW(&MotorConfig,M0);
	while(g_seconds < (TIME_OF_DOOR_OPEN+TIME_OF_DOOR_STOP+TIME_OF_DOOR_CLOSE));
	MOTOR_stop(&MotorConfig,M0);

}
/*=================================== Door_callBack =============================================*/
void CTRL_callBack(void)
{
	g_seconds++;
}
/*================================== CONTROL_alarmAction =======================================*/
void CTRL_alarmAction(void)
{
	g_seconds = 0;
	BUZZER_On(&BuzzerConfig,B0);
	while(g_seconds < TIME_OF_ALARM);
	BUZZER_Off(&BuzzerConfig,B0);
}
/*================================= CONTROL_openDoorCheckPassword ================================*/
void CTRL_openDoorWrongPassword(uint8 *a_NumberOfWrongPasswords)
{
	uint8 a_verification_res = 0;
	/*********************************************************************
	 * 1. send ready for contact.
	 * 2. send the option command = MISMATCHED to the HMI.
	 * 3. increment num_of_wrong_passwords by one.
	 * 4. wait until HMI take the password and send it again.
	 * 5. receive password from HMI.
	 * 6. read password stored in EEPROM memory.
	 * 7. compare the two passwords.
	 * 8. send ready for contact and check readiness of HMI
	 * 9. set the resutl in verificaton_res.
	 * 10. If HMI is already ready send it the verification result.
	 * 11.If the verificaton result = MATCHED:
	 * 	11-1. set num_of_wrong_passwords to zero.
	 * 	11-2. apply function CONTROL_doorActoin.
	 * 	11-3. exit from the loop.
	 * 	11-4. return to the option menu again.
	 * 12.If the verification_res = MISMATCHED for three times:
	 * 	12-1. exit the loop.
	 * 	12-2. set num_of_wrong_passwords back to zero.
	 * 	12-3. apply functoin CONTROL_alarmAction.
	 * 	12-4. return back to the option menu.
	 ************************************************************************/
	CTRL_sendACK();
	UART_sendByte(MISMATCHED);
	while((*a_NumberOfWrongPasswords) < MAX_NUMBER_OF_WRONG_PASS_ENTERED)
	{
		(*a_NumberOfWrongPasswords) ++;
		CTRL_receiveACK();
		CTRL_receivePassword(g_confirmPassword_array);
		CTRL_readPassword();
		a_verification_res = CTRL_compareTwoPasswords();
		CTRL_sendACK();
		UART_sendByte(a_verification_res);

		if(a_verification_res == MATCHED)
		{
			(*a_NumberOfWrongPasswords) = 0;
			CTRL_doorAction();
			break;         /* exit from while loop */
		}
	}
	if((*a_NumberOfWrongPasswords) == MAX_NUMBER_OF_WRONG_PASS_ENTERED)
	{
		(*a_NumberOfWrongPasswords) = 0;
		CTRL_alarmAction();
	}
}
/*================================= CONTROL_changePassword ======================================*/
void CTRL_changePassword(uint8 *a_NumberOfWrongPasswords)
{
	uint8 a_verification_res = 0;
	/***********************************************************************************
	 * 1. wait for HMI to finish and send ready to contact.
	 * 2. receive password from HMI.
	 * 3. read the old password from memory.
	 * 4. compare the two passwords and set the result in a_verification_res.
	 * 5. if result = matched:
	 * 	5-1. send CHANGE_PASSEORD message to HMI.
	 * 	5-2. reset the password again [start change the password operation].
	 * 	5-3. return number of wrong passwords back to zero again.
	 * 6. if the verification result is Mismatched :
	 * 	6-1. send ready to the HMI and wait its readiness.
	 * 	6-2. send MISMATCHED message to HMI.
	 * 	6-3. loop until enter the correct password.
	 * 	6-4. if the user enter a wrong password for 3 times ==> implement alarm action.
	 ************************************************************************************/
	CTRL_receiveACK();

	CTRL_receivePassword(g_confirmPassword_array);
	CTRL_readPassword();
	a_verification_res = CTRL_compareTwoPasswords();

	if(a_verification_res == MATCHED)
	{
		CTRL_sendACK();
		UART_sendByte(CHANGE_PASSWORD);
		CTRL_passwordInputOperation();
		(*a_NumberOfWrongPasswords) = 0;
	}
	else if(a_verification_res == MISMATCHED)
	{
		CTRL_sendACK();
		UART_sendByte(MISMATCHED);
		while((*a_NumberOfWrongPasswords) < MAX_NUMBER_OF_WRONG_PASS_ENTERED)
		{
			(*a_NumberOfWrongPasswords)++;

			CTRL_receiveACK();
			CTRL_receivePassword(g_confirmPassword_array);
			CTRL_readPassword();
			a_verification_res = CTRL_compareTwoPasswords();
			CTRL_sendACK();
			UART_sendByte(a_verification_res);
			if(a_verification_res == MATCHED)
			{
				(*a_NumberOfWrongPasswords) = 0;
				CTRL_passwordInputOperation();
				break; /* exit the while loop */
			}
		}
		if((*a_NumberOfWrongPasswords) == MAX_NUMBER_OF_WRONG_PASS_ENTERED)
		{
			(*a_NumberOfWrongPasswords) = 0;
			CTRL_alarmAction();
		}
	}

}
