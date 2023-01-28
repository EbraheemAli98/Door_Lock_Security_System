/*
 * Motor_Lcfg.c
 *
 *  Created on: Jan 24, 2023
 *      Author: emena
 */

#include "../../MCAL/GPIO/gpio.h"
#include "Motor.h"

const MOTOR_ConfigType MotorConfig =
{
#if(MOTOR_DIRECTION == MOTOR_BOTH_DIRECTIONS)
		{{M0, MOTOR_CW_PORT_ID, MOTOR_CW_PIN_ID, MOTOR_ACW_PORT_ID, MOTOR_ACW_PIN_ID}}
#else
		{{M0, MOTOR_CW_PORT_ID, MOTOR_CW_PIN_ID}}
#endif
};
