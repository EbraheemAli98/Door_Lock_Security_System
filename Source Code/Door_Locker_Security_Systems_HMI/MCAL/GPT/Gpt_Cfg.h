/*-----------------------------------------------------------------------------------
 [FILE NAME]: Gpt_Cfg.h

 [AUTHER]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: Jan 25, 2023

 [DESCRIPTION]: This file contains pre-compile time configurations of GPT module.
 ------------------------------------------------------------------------------------*/

#ifndef MCAL_GPT_GPT_CFG_H_
#define MCAL_GPT_GPT_CFG_H_

/*******************************************************************************
 * 									Definitions
 *******************************************************************************/
#define NUM_OF_TIMER_CHANNELS	3
#define T0	0
#define T1 	1
#define T2	2

#ifndef ENABLE
#define ENABLE	1
#endif

#ifndef DISABLE
#define DISABLE	0
#endif

#define CTC_MODE_NUMBER_4 (4)
#define CTC_MODE_NUMBER_12 (12)
#define TIMER1_CTC_MODE_NUMBER CTC_MODE_NUMBER_4

#define T0_MAX_VALUE 256
#define T1_MAX_VALUE 65536
#define T2_MAX_VALUE 256

#if DISABLE
#define GPT_SET_PRESCALER_API
#endif

#if DISABLE
#define GPT_SET_MODE_API
#endif

#if DISABLE
#define GPT_SET_INIT_VALUE_API
#endif

#if DISABLE
#define GPT_SET_COMP_VALUE_API
#endif

#define GPT_T0_INT_ENABLE	DISABLE
#define GPT_T1_INT_ENABLE	ENABLE
#define GPT_T2_INT_ENABLE	DISABLE

#endif /* MCAL_GPT_GPT_CFG_H_ */
