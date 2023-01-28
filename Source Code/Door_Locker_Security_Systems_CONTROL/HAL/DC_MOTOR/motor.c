/*----------------------------------------------------------------------------------------------
 [FILE NAME]: motor.c

 [AUTHOR]:Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: June 16, 2022

 [DESCRIPTION]: This file includes the Functions' definitions of DC_motor.
 -----------------------------------------------------------------------------------------------*/

#include "../../MCAL/GPIO/gpio.h"
#include "motor.h"

/*********************************************************************
 * 						Static Functions' Prototypes
 *********************************************************************/
void MOTOR_init()
{
	GPIO_setupPinDirection(MOTOR_PORT_ID, MOTOR_CW_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT_ID, MOTOR_A_CW_PIN_ID, PIN_OUTPUT);
	MOTOR_stop();
}

void MOTOR_rotate(uint8 a_direction)
{
	switch(a_direction)
	{
	case ROTATE_A_CW:
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_A_CW_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(MOTOR_PORT_ID,MOTOR_CW_PIN_ID,LOGIC_LOW);
		break;
	case ROTATE_CW:
		GPIO_writePin(MOTOR_PORT_ID,MOTOR_CW_PIN_ID,LOGIC_HIGH);
		GPIO_writePin(MOTOR_PORT_ID,MOTOR_A_CW_PIN_ID,LOGIC_LOW);
		break;
	}
}

void MOTOR_stop(void)
{
	GPIO_writePin(MOTOR_PORT_ID,MOTOR_A_CW_PIN_ID,LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_CW_PIN_ID, LOGIC_LOW);
}

