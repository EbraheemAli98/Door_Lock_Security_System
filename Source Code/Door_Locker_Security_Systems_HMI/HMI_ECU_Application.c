/*------------------------------------------------------------------------------
 [FILE NAME]: HMI_ECU.c

 [AUTHOR]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: June 9, 2022

 [DESCRIPTION]: This file contain the implementation code of HMI_ECU
 	 	 	 			[HUMAN MACHINE INTERFACE]
 -------------------------------------------------------------------------------*/
#include "HMI_SOFTWARE_SUPPORT_LAYER/HMI_software_support.h"
#include "HAL/LCD/lcd.h"
#include <avr/interrupt.h>
#include <util/delay.h>

#define PASSWORD_NOT_ENTERED	0xFF
#define PASSWORD_ENTERED		1

int main(void)
{
	/***********************************************************************************************************************
	 *  [uint8 flag]: variable to observe if the user is used the program for the first time or not.
	 *  [uint8 a_CTROL_option]: this variable stores the selected option selected by the user.
	 *  [uint8 a_num_of_wrong_passwords]: this variable used to observe how many wrong passwords the user has enterred.
	 *  [uint8 a_CTROL_verification_res]: this variable stores the result of the comparsion betweem the two input passwords.
	 ***********************************************************************************************************************/
	uint8 a_num_of_wrong_passwords = 0,a_passwordState;
	uint8 a_HMI_option = 0,a_HMI_optionOrder = 0;

	/********************************************************************************************
	 * 1. initiate the timer configuration:timer1,compare-mode,prescaler_1024.
	 * 2. set the callback function = HMI_callBack.
	 * 3. initiate LCD.
	 * 4. set the uart configuration: 9600 baud-rate, one stop bit, 8bits-data,and no parity bit.
	 ********************************************************************************************/
	HMI_Init();

	/* ********************************************
	 * wait for control ECU to send ready
	 * receive the flag value from control ECU
	 * ********************************************/
	HMI_receiveACK();
	a_passwordState = UART_receiveByte();

	/* Don't enter here if you already set you password */
	if(a_passwordState == PASSWORD_NOT_ENTERED)
	{
		/*//////////////////////////// set the password for the first time ///////////////////////////////////*/
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
		 * 	8-2. display "MISMATCHED".
		 * 	8-3. displsy "Try Again" on the next line.
		 * 	8-4. wait for 500 msec.
		 * 	8-5. clear the screen.
		 * 9. loop until the user enter a matched passwords.
		 ******************************************************************************************************/
		HMI_passwordInputOperation();
	}

	/* Enable the global interrupt */
	ENABLE_INTERRUPTS();

	for(;;)
	{
		/* Get the chosen option from the user */
		a_HMI_option = HMI_getChosenOption();

		switch(a_HMI_option)
		{
		case OPEN_DOOR_OPTION:
			/*********************************************************************************
			 * 1. increment num_of_wrong_passwords.
			 * 2. clear the screen.
			 * 3. verify the password: get password from user and send it to the control ECU.
			 * 4. send the chosen option to the control ECU.
			 * 5. Wait until the control ECU check the password and ready for communicate.
			 * 6. get option_order from the control ECU.
			 *********************************************************************************/
			a_num_of_wrong_passwords++;
			HMI_CLEAR_SCREEN();
			HMI_sendACK();
			UART_sendByte(OPEN_DOOR_OPTION);
			HMI_enterPassword();
			HMI_receiveACK();
			a_HMI_optionOrder = UART_receiveByte();

			if(a_HMI_optionOrder == DOOR_OPEN)
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
				HMI_displayDoorAction();
				a_num_of_wrong_passwords = 0;
			}
			else if(a_HMI_optionOrder == MISMATCHED)
			{
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
					HMI_openDoorWrongPassword(&a_num_of_wrong_passwords);
			}
			break;		/* return to the option menu */

		case CHANGE_PASSWORD_OPTION:

			a_num_of_wrong_passwords++;
			/*/////////////////////////////////////// Logic of change password option /////////////////////////////////////////////////*/
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
			HMI_changePassword(&a_num_of_wrong_passwords);
			break;
		}
	}
}
