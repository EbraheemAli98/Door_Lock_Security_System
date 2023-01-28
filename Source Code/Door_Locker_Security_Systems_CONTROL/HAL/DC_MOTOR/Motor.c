/*----------------------------------------------------------------------------------------------
 [FILE NAME]: motor.c

 [AUTHOR]:Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: June 16, 2022

 [DESCRIPTION]: This file includes the Functions' definitions of DC_motor.
 -----------------------------------------------------------------------------------------------*/

#include "Motor.h"

#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/GPT/Gpt.h"


/*********************************************************************
 * 						 Functions' Prototypes
 *********************************************************************/
void MOTOR_Init(const MOTOR_ConfigType *Config_Ptr)
{
	uint8 motorId;
	for(motorId=0; motorId < NUM_OF_MOTORS; motorId++)
	{
#if(MOTOR_DIRECTION == MOTOR_BOTH_DIRECTIONS)
		GPIO_setupPinDirection(Config_Ptr->M_Config[motorId].Motor_CW_port,
				Config_Ptr->M_Config[motorId].Motor_CW_pin,
				PIN_OUTPUT);
		GPIO_setupPinDirection(Config_Ptr->M_Config[motorId].Motor_ACW_port,
				Config_Ptr->M_Config[motorId].Motor_ACW_pin,
				PIN_OUTPUT);
#else
		GPIO_setupPinDirection(Config_Ptr->ConfigMotorInstances[motorId].Motor_CW_port,
				Config_Ptr->M_Config[motorId].Motor_CW_pin,
				PIN_OUTPUT);
#endif
	}
}


#if(MOTOR_DIRECTION == MOTOR_BOTH_DIRECTIONS)
	void MOTOR_rotateCW(const MOTOR_ConfigType *Config_Ptr,MotorIdType Mx)
	{
		GPIO_writePin(Config_Ptr->M_Config[Mx].Motor_CW_port,
					  Config_Ptr->M_Config[Mx].Motor_CW_pin,
					  LOGIC_HIGH);
		GPIO_writePin(Config_Ptr->M_Config[Mx].Motor_ACW_port,
				  	  Config_Ptr->M_Config[Mx].Motor_ACW_pin,
				  	  LOGIC_LOW);
	}

	void MOTOR_rotateACW(const MOTOR_ConfigType *Config_Ptr,MotorIdType Mx)
	{
		GPIO_writePin(Config_Ptr->M_Config[Mx].Motor_ACW_port,
				  	  Config_Ptr->M_Config[Mx].Motor_ACW_pin,
					  LOGIC_HIGH);
		GPIO_writePin(Config_Ptr->M_Config[Mx].Motor_CW_port,
					  Config_Ptr->M_Config[Mx].Motor_CW_pin,
					  LOGIC_LOW);
	}
#else
	void MOTOR_rotate(MOTOR_ConfigType *Config_Ptr,MotorIdType Mx)
	{
		GPIO_writePin(Config_Ptr->M_Config[Mx].Motor_CW_port,
					  Config_Ptr->M_Config[Mx].Motor_CW_pin,
					  LOGIC_HIGH);
	}
#endif


void MOTOR_stop(const MOTOR_ConfigType *Config_Ptr,MotorIdType Mx)
{
#if(MOTOR_ONE_DIR == MOTOR_DIRECTION)
	GPIO_writePin(Config_Ptr->M_Config[Mx].Motor_CW_port,
				  Config_Ptr->M_Config[Mx].Motor_CW_pin,
				  LOGIC_LOW);
#else
	GPIO_writePin(Config_Ptr->M_Config[Mx].Motor_CW_port,
				  Config_Ptr->M_Config[Mx].Motor_CW_pin,
				  LOGIC_LOW);
	GPIO_writePin(Config_Ptr->M_Config[Mx].Motor_ACW_port,
			  	  Config_Ptr->M_Config[Mx].Motor_ACW_pin,
				  LOGIC_LOW);
#endif
}

