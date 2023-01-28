/*------------------------------------------------------------------------------
 [FILE NAME]: buzzer.c

 [AUTHOR]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: June 9, 2022

 [DESCRIPTION]: This file contain the functions' definitions of buzzer.
 -------------------------------------------------------------------------------*/

#include "buzzer.h"

#include "../../LIBRARIES/Std_types.h"

void BUZZER_init(void)
{
	/* Set the buzzer at portB , pin0 as output */
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);
	/* Turn off Buzzer */
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, BUZZER_OFF);
}

void BUZZER_on(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, BUZZER_ON);
}

void BUZZER_off(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, BUZZER_OFF);
}
