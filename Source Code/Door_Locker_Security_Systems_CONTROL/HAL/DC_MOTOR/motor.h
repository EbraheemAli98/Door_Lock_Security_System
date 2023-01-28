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

/***********************************************************************************
 * 									Definitions
 ***********************************************************************************/
#define ROTATE_A_CW 0
#define ROTATE_CW   1
#define MOTOR_SPEED 75

#define MOTOR_PORT_ID		PORTA_ID
#define MOTOR_A_CW_PIN_ID		PIN1_ID
#define MOTOR_CW_PIN_ID			PIN0_ID

/************************************************************************************
 *   							Functions' Prototypes
 ************************************************************************************/
/*---------------------------------------------------------------------------
 [Function Name]:MOTOR_init
 [Arguments]:None
 [Description]: This function set the motor's port and pins connected.
 [Return]:None
 ----------------------------------------------------------------------------*/
void MOTOR_init();

/*---------------------------------------------------------------------------
 [Function Name]: MOTOR_rotateCW
 [Arguments]:uint8 direction:
 [in]	 	 	 indicate the direction of rotation.
 [Description]: Function to rotate motor Clock-wise.
 [Return]:None
 ----------------------------------------------------------------------------*/
void MOTOR_rotate(uint8 a_direction);

/*---------------------------------------------------------------------------
 [Function Name]:MOTOR_stop
 [Arguments]:None
 [Description]: Function to stop motor rotation.
 [Return]:None
 ----------------------------------------------------------------------------*/
void MOTOR_stop(void);

#endif /* HAL_DC_MOTOR_MOTOR_H_ */
