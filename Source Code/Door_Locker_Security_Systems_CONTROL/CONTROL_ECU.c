/*------------------------------------------------------------------------------
 [FILE NAME]: CONTROL_ECU.c

 [AUTHOR]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: June 9, 2022

 [DESCRIPTION]: This file contain the implementation code of CONTROL_ECU
 -------------------------------------------------------------------------------*/

#include "CONTROL_SOFTWARE_SUPPORT_LAYER/CONTROL_software_support.h"
#include "HAL/EEPROM/eeprom.h"
#include <avr/interrupt.h>
#include <util/delay.h>

#define PASSWORD_NOT_ENTERED	0xFF
#define PASSWORD_ENTERED		1

int main(void)
{
	/*****************************************************************************************************************
	 *  [uint8 flag]: variable to observe if the user is used the program for the first time or not.
	 *  [uint8 a_CTROL_option]: this variable stores the selected option coming from HMI ECU.
	 *  [uint8 a_num_of_wrong_passwords]: this variable used to observe how many wrong passwords the user has enterred.
	 *  [uint8 a_CTROL_verification_res]: this variable stores the result of the comparsion betweem the two input passwords.
	 ******************************************************************************************************************/
	uint8 a_num_of_wrong_passwords = 0,a_passwordState;
	uint8 a_CTROL_verification_res = 0,a_CTROL_option=0;

	/*********************************************************************************************************
	 * 1. initiate the EEPROM.
	 * 2. initiate the Buzzer.
	 * 3. initiate the motor.
	 * 4. initiate the timer to Timer1, compare-mode, prescaler_1024,and set the initial and compare values.
	 * 5. initiate the UART to baud-rate=9600, 8-bits data, one stop bit and no parity.
	 **********************************************************************************************************/
	CTRL_Init();
	_delay_ms(10);

	/* read the value of flag from memory */
	EEPROM_readByte(CODE_STATE_ADDRESS, &a_passwordState);
	/* check if HMI is ready to contact. if it is ready send the flag to it. */
	CTRL_sendACK();
	UART_sendByte(a_passwordState);

	/* Don't come here again if you have set your password brefore. */
	if(a_passwordState == PASSWORD_NOT_ENTERED)
	{
		/*///////////////////////////// set your password for the first time //////////////////////////////////*/
		/********************************************************************************************************
		 * 1. wait HMI to finish its task (getting the password) .
		 * 2. receive password from HMI.
		 * 3. wait HMI to finish its task (getting the confirmed password) and send ready to it.
		 * 4. compare the two passwords and store the result in variable temp.
		 * 5. if two passwords are matched store the password in memory.
		 * 6. send ready to contact to HMI and wait if until finish its task and respond by ready.
		 * 7. send the result of comparsion to HMI.
		 * 8. loop until the two password are matched.
		 ********************************************************************************************************/
		CTRL_passwordInputOperation();
	}

	/* set the flag to 1 and store it in memory to prevent the program from starting again from this point */
	a_passwordState = PASSWORD_ENTERED;
	EEPROM_writeByte(CODE_STATE_ADDRESS, a_passwordState);

	/* Enable global interrupt */
	SREG |= (1<<7);
	while(1)
	{
		CTRL_receiveACK();		/* wait until verify password is entered.*/
		a_CTROL_option = UART_receiveByte(); 	/* receive the selected option*/

		switch(a_CTROL_option)
		{
		case OPEN_DOOR_OPTION:
			/*********************************************************************************************
			 * 1. increment the number of wrong passwords by 1.
			 * 2. wait for HMI to send ready.
			 * 3. if HMI is ready receive the input password from it.
			 * 4. return the old password from the memory.
			 * 5. compare the two passwords and put the result in a_CTROL_verification_res.
			 * 6. if a_verification_res = matched ==> implement the door action.
			 * 7. if a_verificatoin_res = mismatched ==> reenter the password again.
			 * 	7-1. if the passwords don't matched for three times ==> implement the alarm action.
			 *********************************************************************************************/
			a_num_of_wrong_passwords++;
			CTRL_receiveACK();
			CTRL_receivePassword(g_confirmPassword_array);
			CTRL_readPassword();
			a_CTROL_verification_res = CTRL_compareTwoPasswords();

			if(a_CTROL_verification_res == MATCHED)
			{
				/*********************************************************************************
				 * 1.set the number of entered wrong password to zero.
				 * 2.send ready to communicate to the HMI ECU.
				 * 3.wait until the HMI finihes its task and ready to respond.
				 * 4.send the command generated depended on verification result to the HMI ECU.
				 * 5.start the door action.
				 * 6.return to option menu again after door actoin ended.(go to break from switch)
				 **********************************************************************************/
				a_num_of_wrong_passwords = 0;
				CTRL_sendACK();
				UART_sendByte(DOOR_OPEN);
				CTRL_doorAction();
			}
			else if(a_CTROL_verification_res == MISMATCHED)
			{

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
				CTRL_openDoorWrongPassword(&a_num_of_wrong_passwords);
			}
			break;		/* return to the option menu , exit from open door option case */

		case CHANGE_PASSWORD_OPTION:
			a_num_of_wrong_passwords ++;
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
			CTRL_changePassword(&a_num_of_wrong_passwords);

			break;/* return to the option menu , exit from change password option case */
		}
	}
}
