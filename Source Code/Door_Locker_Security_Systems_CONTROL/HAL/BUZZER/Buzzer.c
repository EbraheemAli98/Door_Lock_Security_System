/*------------------------------------------------------------------------------
 [FILE NAME]: buzzer.c

 [AUTHOR]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: June 9, 2022

 [DESCRIPTION]: This file contain the functions' definitions of buzzer.
 -------------------------------------------------------------------------------*/

#include "Buzzer.h"

#include "../../LIBRARIES/Std_types.h"


/************************************************************************************************
 	 	 	 	 	 	 	 	 	 Functions' Definition
 ************************************************************************************************/
void BUZZER_Init(const BUZZER_ConfigType *Config_Ptr)
{
	uint8 Bx_ID;
	for(Bx_ID = 0; Bx_ID < NUM_OF_BUZZERS; Bx_ID++ )
	{
		/* Set the buzzer at portB , pin0 as output */
		GPIO_setupPinDirection(Config_Ptr->B_Config[Bx_ID].port,
							   Config_Ptr->B_Config[Bx_ID].pin,
							   PIN_OUTPUT);
		/* Turn off Buzzer */
		GPIO_writePin(Config_Ptr->B_Config[Bx_ID].port,
				   	   Config_Ptr->B_Config[Bx_ID].pin,
					   BUZZER_OFF);
	}
}

void BUZZER_On(const BUZZER_ConfigType *Config_Ptr,BuzzerIdType Bx_ID)
{
	GPIO_writePin(Config_Ptr->B_Config[Bx_ID].port,
			   	   Config_Ptr->B_Config[Bx_ID].pin,
				   BUZZER_ON);
}

void BUZZER_Off(const BUZZER_ConfigType *Config_Ptr,BuzzerIdType Bx_ID)
{
	GPIO_writePin(Config_Ptr->B_Config[Bx_ID].port,
			   	   Config_Ptr->B_Config[Bx_ID].pin,
				   BUZZER_OFF);
}
