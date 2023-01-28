/*
 * Buzzer_Lcfg.c
 *
 *  Created on: Jan 25, 2023
 *      Author: emena
 */

#include "../../MCAL/GPIO/gpio.h"
#include "Buzzer.h"

const BUZZER_ConfigType BuzzerConfig =
{
		{{B0, BUZZER_PORT_ID, BUZZER_PIN_ID}}
};
