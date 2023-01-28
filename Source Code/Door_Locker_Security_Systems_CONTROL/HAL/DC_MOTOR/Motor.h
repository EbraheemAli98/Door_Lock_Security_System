/*----------------------------------------------------------------------------------------------
 [FILE NAME]: motor.h

 [AUTHOR]:Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: June 16, 2022

 [DESCRIPTION]: This file includes the definitions and Functions' Prototype of DC_motor.
 -----------------------------------------------------------------------------------------------*/

#ifndef HAL_DC_MOTOR_MOTOR_H_
#define HAL_DC_MOTOR_MOTOR_H_

#include "../../LIBRARIES/Std_types.h"
#include "Motor_Cfg.h"


typedef uint8 MotorIdType;

typedef struct
{
	MotorIdType Mx_ID;
#if(MOTOR_DIRECTION == MOTOR_BOTH_DIRECTIONS)
	uint8 Motor_CW_port;
	uint8 Motor_CW_pin;
	uint8 Motor_ACW_port;
	uint8 Motor_ACW_pin;
#else
	uint8 Motor_CW_port;
	uint8 Motor_CW_pin;
#endif

}MOTOR_ParamConfigType;

typedef struct
{
	MOTOR_ParamConfigType M_Config[NUM_OF_MOTORS];
}MOTOR_ConfigType;

extern const MOTOR_ConfigType MotorConfig;

/************************************************************************************
 *   							Functions' Prototypes
 ************************************************************************************/
	/*---------------------------------------------------------------------------
	 [Function Name]:MOTOR_Init
	 [Arguments]:None
	 [Description]: This function set the motor's port and pins connected.
	 [Return]:None
	 ----------------------------------------------------------------------------*/
	void MOTOR_Init(const MOTOR_ConfigType *Config_Ptr);

#if(MOTOR_DIRECTION == MOTOR_BOTH_DIRECTIONS)
	/*---------------------------------------------------------------------------
	 [Function Name]: MOTOR_rotateCW
	 [Arguments]:None
	 [Description]: Function to rotate motor Clock-wise.
	 [Return]:None
	 ----------------------------------------------------------------------------*/
	void MOTOR_rotateCW(const MOTOR_ConfigType *Config_Ptr,MotorIdType Mx);
	/*---------------------------------------------------------------------------
	 [Function Name]: MOTOR_rotateACW
	 [Arguments]:None
	 [Description]: Function to rotate motor Anti_Clock-wise.
	 [Return]:None
	 ----------------------------------------------------------------------------*/
	void MOTOR_rotateACW(const MOTOR_ConfigType *Config_Ptr,MotorIdType Mx);

#else
	/*---------------------------------------------------------------------------
	 [Function Name]: MOTOR_rotate
	 [Arguments]:None
	 [Description]: Function to rotate motor.
	 [Return]:None
	 ----------------------------------------------------------------------------*/
	void MOTOR_rotate(const MOTOR_ConfigType *Config_Ptr,MotorIdType Mx);

#endif

/*---------------------------------------------------------------------------
 [Function Name]:MOTOR_stop
 [Arguments]:None
 [Description]: Function to stop motor rotation.
 [Return]:None
 ----------------------------------------------------------------------------*/
void MOTOR_stop(const MOTOR_ConfigType *Config_Ptr,MotorIdType Mx);

#endif /* HAL_DC_MOTOR_MOTOR_H_ */
