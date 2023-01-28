/*------------------------------------------------------------------------------
 [FILE NAME]: buzzer.h

 [AUTHOR]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: June 9, 2022

 [DESCRIPTION]: This file contain the definitions and functions' declarations of
 	 	 	 	 buzzer.
 -------------------------------------------------------------------------------*/

#ifndef HAL_BUZZER_H_
#define HAL_BUZZER_H_
#include "../../MCAL/GPIO/gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define BUZZER_PORT_ID	PORTB_ID
#define BUZZER_PIN_ID	PIN0_ID
#define BUZZER_ON	LOGIC_HIGH
#define BUZZER_OFF	LOGIC_LOW


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
void BUZZER_init(void);

/*----------------------------------------------------------
 [Function Name]:BUZZER_init
 [Arguments]: None
 [Description]: --This function Turn on the buzzer.
 [Return]: None
 ------------------------------------------------------------*/
void BUZZER_on(void);

/*----------------------------------------------------------
 [Function Name]:BUZZER_init
 [Arguments]: None
 [Description]: -This function Turn off the buzzer.
 [Return]: None
 ------------------------------------------------------------*/
void BUZZER_off(void);


#endif /* HAL_BUZZER_H_ */
