/*------------------------------------------------------------------------------
 [FILE NAME]: Buzzer.h

 [AUTHOR]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: June 9, 2022

 [DESCRIPTION]: This file contain the definitions and functions' declarations of
 	 	 	 	 buzzer.
 -------------------------------------------------------------------------------*/

#ifndef HAL_BUZZER_H_
#define HAL_BUZZER_H_

#include "../../MCAL/GPIO/gpio.h"
#include "Buzzer_Cfg.h"

typedef uint8 BuzzerIdType;
typedef uint8 BuzzerPinType;
typedef uint8 BuzzerPortType;

typedef struct
{
	BuzzerIdType Bx_ID;
	BuzzerPortType port;
	BuzzerPinType pin;
}BUZZER_ParamConfigStruct;

typedef struct
{
	BUZZER_ParamConfigStruct B_Config[NUM_OF_BUZZERS];
}BUZZER_ConfigType;

extern const BUZZER_ConfigType	BuzzerConfig;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*----------------------------------------------------------
 [Function Name]:BUZZER_init
 [Arguments]: None
 [Description]: -This function set the direction of buzzer's pin.
 	 	 	 	-This function set the buzzer's port.
 [Return]: None
 ------------------------------------------------------------*/
void BUZZER_Init(const BUZZER_ConfigType *Config_Ptr);

/*----------------------------------------------------------
 [Function Name]:BUZZER_init
 [Arguments]: None
 [Description]: --This function Turn on the buzzer.
 [Return]: None
 ------------------------------------------------------------*/
void BUZZER_On(const BUZZER_ConfigType *Config_Ptr,BuzzerIdType Bx_ID);

/*----------------------------------------------------------
 [Function Name]:BUZZER_init
 [Arguments]: None
 [Description]: -This function Turn off the buzzer.
 [Return]: None
 ------------------------------------------------------------*/
void BUZZER_Off(const BUZZER_ConfigType *Config_Ptr,BuzzerIdType Bx_ID);


#endif /* HAL_BUZZER_H_ */
