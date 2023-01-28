/*
 * Motor_Cfg.h
 *
 *  Created on: Jan 24, 2023
 *      Author: emena
 */

#ifndef HAL_DC_MOTOR_MOTOR_CFG_H_
#define HAL_DC_MOTOR_MOTOR_CFG_H_

/***********************************************************************************
 * 									Definitions
 ***********************************************************************************/
#define NUM_OF_MOTORS		(1)
#define M0	0						/* Motor0 ID */
#define MOTOR_ROTATE_A_CW 	(0)
#define MOTOR_ROTATE_CW   	(1)


#define MOTOR_CW_PORT_ID		PORTA_ID
#define MOTOR_ACW_PORT_ID		PORTA_ID
#define MOTOR_ACW_PIN_ID		PIN1_ID
#define MOTOR_CW_PIN_ID			PIN0_ID


#define MOTOR_ONE_DIR			0
#define MOTOR_BOTH_DIRECTIONS	1
#define MOTOR_DIRECTION		(MOTOR_BOTH_DIRECTIONS)

#endif /* HAL_DC_MOTOR_MOTOR_CFG_H_ */
