/*-----------------------------------------------------------------------------------
 [FILE NAME]: Gpt_Lcfg.c

 [AUTHER]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: Jan 25, 2023

 [DESCRIPTION]: This file contains the configuration of General Purpose Timer.
 ------------------------------------------------------------------------------------*/
#include "Gpt.h"

const GPT_ConfigType GPT_ConfigStructObj =
{
		{
		 {T0, OUTPUT_COMPARE, TIMER_STOP, NON_PWM_DISCONNECTED, 0, 0},
		 {T1, OUTPUT_COMPARE, PRESCALER_1024, NON_PWM_DISCONNECTED, 0, 7811}, /*for 1000 msec*/
		 {T2, OUTPUT_COMPARE, TIMER_STOP, NON_PWM_DISCONNECTED, 0, 0}
		}
};
