/*------------------------------------------------------------------------------
 [FILE NAME]: Gpt.h

 [AUTHOR]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: June 14, 2022

 [DESCRIPTION]: This file contain the definitions , configurations, functions'
  	  	  	  	declaration of TIMER.
 -------------------------------------------------------------------------------*/

#ifndef MCAL_GPT_GPT_H_
#define MCAL_GPT_GPT_H_

#include "../../LIBRARIES/Std_types.h"
#include "Gpt_Cfg.h"
/*******************************************************************************
 * 								  Types Declaration
 *******************************************************************************/
typedef uint16 TimerValueType;
typedef uint16 TimerCompValueType;
typedef uint8 TimerType;
/*-----------------------------------------------------------------------------
 [ENUM NAME]:TIMER_clockSelectType
 [Description]: Describe the values of the three clock select bits select the
 	 	 	 	clock source to be used by the Timer0/Counter0.
 ------------------------------------------------------------------------------*/
typedef enum
{
	TIMER_STOP,
	NO_PRESCALER,
	PRESCALER_8,
	PRESCALER_64,
	PRESCALER_256,
	PRESCALER_1024,
}GPT_PrescalerType;

/*-----------------------------------------------------------------------------
 [ENUM NAME]:TIEMR_modeType
 [Description]: Describe the Wave Generation Mode Bit of TIMER.
 ------------------------------------------------------------------------------*/
typedef enum
{
	NORMAL,
	OUTPUT_COMPARE=2,
}GPT_ModeType;

/*-----------------------------------------------------------------------------
 [ENUM NAME]:TIMER_COMNonPWM_t
 [Description]: Describe the different states of OC(0,1A or 1B) pin in CTC
 	 	 	 	non-PWM mode.
 ------------------------------------------------------------------------------*/
typedef enum
{
	NON_PWM_DISCONNECTED,
	TOGGLE,			/* Toggle Output_Compare_Pin */
	LOW_LEVEL,  /* Clear Output_Compare_Pin (set output to low level) */
	HIGH_LEVEL   /* Set Output_Compare_Pin (set output to high level) */
}GPT_CompareNonPwmType;

/*******************************************************************************
 *								 Structure Declaration
 *******************************************************************************/
/*------------------------------------------------------------------------------
 [Structure NAME]:GPT_ParamConfigStructType
 [Description]: It contains the dynamic configuration parameters of TIMER.
 -------------------------------------------------------------------------------*/
typedef struct
{
	TimerType	Tx_ID;
	GPT_ModeType mode;
	GPT_PrescalerType prescaler;
	GPT_CompareNonPwmType CTC_waveForm; /* Indicate the wave form generation in compare output pin(OCn),non PWM */
	TimerValueType TimerInitValue;	/* store the value of TCNTx */
	TimerCompValueType TimerCompValue;   /* store the value of OCR0,OCR2,OCR1A,OCR1B or ICR1 */

}GPT_ParamConfigStructType;

typedef struct
{
	GPT_ParamConfigStructType GPT_Config[NUM_OF_TIMER_CHANNELS];
}GPT_ConfigType;

extern const GPT_ConfigType	GPT_ConfigStructObj;

/*******************************************************************************
 *								 Functions' Declarations
 *******************************************************************************/
/*------------------------------------------------------------------------------
 [Function Name]:GPT_setMode
 [Arguments]:
 [in]		TimerType  Tx:
 				Indicates the ID of the timer used.
 			GPT_ModeType mode:
 				Indicates the mode of timer.
 [Description]: This function set the mode of timer.
 [Return]: None
 -------------------------------------------------------------------------------*/
void GPT_setMode(TimerType Tx,GPT_ModeType mode);

/*------------------------------------------------------------------------------
 [Function Name]:GPT_setPrescaler
 [Arguments]:
 [in]		TimerType  Tx:
 				Indicates the ID of the timer used.
 			GPT_PrescalerType value:
 				the prescaler value of timer.
 [Description]: This function to change the prescaler in run-time
 [Return]: None
 -------------------------------------------------------------------------------*/
void GPT_setPrescaler(TimerType Tx,GPT_PrescalerType value);

/*------------------------------------------------------------------------------
 [Function Name]:GPT_setInitValue
 [Arguments]:
 [in]		TimerType  Tx:
 				Indicates the ID of the timer used.
 			TimerValueType value:
 				the new initial value of timer.
 [Description]: This function set the initial value of timer.
 [Return]: None
 -------------------------------------------------------------------------------*/
void GPT_setInitValue(TimerType Tx,TimerValueType value);

/*------------------------------------------------------------------------------
 [Function Name]:GPT_setCompValue
 [Arguments]:
 [in]		TimerType  Tx:
 				Indicates the ID of the timer used.
 			TimerCompValueType value:
 				the new Compare value of timer.
 [Description]: This function set the compare value of timer.
 [Return]: None
 -------------------------------------------------------------------------------*/
void GPT_setCompValue(TimerType Tx,TimerCompValueType value);
/*
 *  TODO: create function to change the wave form of Compare-mode in run-time
 *  GPT_setWaveForm(TimerType Tx);
 */

/*------------------------------------------------------------------------------
 [Function Name]:GPT_T0_setCallBack
 [Arguments]:
 [in]	void(*)(void) a_Fun_Ptr:
 	 	 	  Pointer to function returns void to store the call back function.
 [Description]: Function to store pass the address of the call back function to
 	 	  	 the ISR of Timer1.
 [Return]:None
 -------------------------------------------------------------------------------*/
void GPT_T0_setCallBack(void (*a_Fun_Ptr)(void));

/*------------------------------------------------------------------------------
 [Function Name]:GPT_T1_setCallBack
 [Arguments]:
 [in]	void(*)(void) a_Fun_Ptr:
 	 	 	  Pointer to function returns void to store the call back function.
 [Description]: Function to store pass the address of the call back function to
 	 	  	 the ISR of Timer1.
 [Return]:None
 -------------------------------------------------------------------------------*/
void GPT_T1_setCallBack(void (*a_Fun_Ptr)(void));

/*------------------------------------------------------------------------------
 [Function Name]:GPT_T1_setCallBack
 [Arguments]:
 [in]	void(*)(void) a_Fun_Ptr:
 	 	 	  Pointer to function returns void to store the call back function.
 [Description]: Function to store pass the address of the call back function to
 	 	  	 the ISR of Timer1.
 [Return]:None
 -------------------------------------------------------------------------------*/
void GPT_T2_setCallBack(void (*a_Fun_Ptr)(void));

/*------------------------------------------------------------------------------
 [Function Name]:GPT_startTimer
 [Arguments]:
 [in]		TimerType  Tx:
 				Indicates the ID of the timer used.
 [Description]: This function start the timer.
 [Return]: None
 -------------------------------------------------------------------------------*/
void GPT_startTimer(TimerType Tx);

/*------------------------------------------------------------------------------
 [Function Name]:GPT_stopTimer
 [Arguments]:
 [in]		TimerType  Tx:
 				Indicates the ID of the timer used.
 [Description]: This function stop the timer.
 [Return]: None
 -------------------------------------------------------------------------------*/
void GPT_stopTimer(TimerType Tx);

/*------------------------------------------------------------------------------
 [Function Name]:GPT_enableNotification
 [Arguments]:
 [in]		TimerType  Tx:
 				Indicates the ID of the timer used.
 			GPT_ModeType mode:
 				Indicates the mode of the timer.
 [Description]: This function enable the timer interrupt.
 [Return]: None
 -------------------------------------------------------------------------------*/
void GPT_enableNotification(TimerType Tx,GPT_ModeType mode);

/*------------------------------------------------------------------------------
 [Function Name]:GPT_disableNotification
 [Arguments]:
 [in]		TimerType  Tx:
 				Indicates the ID of the timer used.
 			GPT_ModeType mode:
 				Indicates the mode of the timer.
 [Description]: This function disable the timer interrupt.
 [Return]: None
 -------------------------------------------------------------------------------*/
void GPT_disableNotification(TimerType Tx,GPT_ModeType mode);

#endif /* MCAL_GPT_GPT_H_ */
