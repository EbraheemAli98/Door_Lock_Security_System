/*------------------------------------------------------------------------------
 [FILE NAME]: timer.h

 [AUTHOR]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: June 14, 2022

 [DESCRIPTION]: This file contain the definitions , configurations, functions'
  	  	  	  	declaration of TIMER.
 -------------------------------------------------------------------------------*/

#ifndef MCAL_TIMER_TIMER_H_
#define MCAL_TIMER_TIMER_H_

#include "../../HELPERS/Std_types.h"

/*******************************************************************************
 * 									Definitions
 *******************************************************************************/

#define TIMER_INTERRUPT	ENABLE
#define ENABLE  1
#define DISABLE 0

#define TIMER1_CTC_MODE_NUMBER CTC_MODE_NUMBER_4
#define CTC_MODE_NUMBER_4 (4)
#define CTC_MODE_NUMBER_12 (12)

#define TIMER1_FAST_PWM_MODE_NUMBER FAST_PWM_MODE_NUMBER_15
#define FAST_PWM_MODE_NUMBER_14 (14)
#define FAST_PWM_MODE_NUMBER_15 (15)

#define TIMER1_MAX_VALUE 65536

/*******************************************************************************
 * 								  ENUM Declaration
 *******************************************************************************/
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
}TIMER_clockSelectType;

/*-----------------------------------------------------------------------------
 [ENUM NAME]:TIEMR_modeType
 [Description]: Describe the Wave Generation Mode Bit of TIMER.
 ------------------------------------------------------------------------------*/
typedef enum
{
	NORMAL,
	CTC=2,
	FAST_PWM
}TIMER_modeType;

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
}TIMER_COMNonPWM_t;

/*-----------------------------------------------------------------------------
 [ENUM NAME]:TIEMR_COMFastPWM_t
 [Description]: Describe the different states of OC(0,1A or 1B) pin in
 	 	 	 	fast-PWM mode.
 ------------------------------------------------------------------------------*/
typedef enum
{
	PWM_DISCONNECTED,
	PWM_TOGGLE,
	PWM_NON_INVERTING,
	PWM_INVERTING
}TIMER_COMPWM_t;
/*******************************************************************************
 *								 Structure Declaration
 *******************************************************************************/
/*------------------------------------------------------------------------------
 [Structure NAME]:TIMER_configType
 [Description]: It contains the dynamic configuration parameters of TIMER.
 -------------------------------------------------------------------------------*/
typedef struct
{
	TIMER_modeType mode;
	TIMER_COMNonPWM_t CTC_waveForm; /* Indicate the wave form generation in compare output pin(OCn),non PWM */
	TIMER_COMPWM_t PWM_waveForm;	/* Indicate the wave form generation in compare output pin (OCn),PWM mode */
	uint16 TimerCompValue;   /* store the value of OCR0,OCR2,OCR1A,OCR1B or ICR1 */
	TIMER_clockSelectType prescaler;
	uint16 TimerInitValue;	/* store the value of TCNTx */

}TIMER_configType;

/*******************************************************************************
 *								 Functions' Declarations
 *******************************************************************************/

/*------------------------------------------------------------------------------
 [Function Name]:TIMER1_setCallBack
 [Arguments]:
 [in]	void(*)(void) a_Fun_Ptr:
 	 	 	  Pointer to function returns void to store the call back function.
 [Description]: Function to store pass the address of the call back function to
 	 	  	 the ISR of Timer1.
 [Return]:None
 -------------------------------------------------------------------------------*/
void TIMER1_setCallBack(void (*a_Fun_Ptr)(void));


/*------------------------------------------------------------------------------
 [Function Name]: TIMER_init
 [Arguments]:
 [in]		TIMER_configType*  a_TimerConfig_Ptr:
 	 	 	 	 Pointer to timer configuration structure.
 [Description]:
 	 	 	 	1. initiate TCNTx.
 	 	 	 	2. initiate OCRnx if Output Compare Mode.
 	 	 	 	3. set the timer mode.
 	 	 	 	4. set the timer clock.
 	 	 	 	5. Enable interrupt if needed.
 [Return]: None
 -------------------------------------------------------------------------------*/
void TIMER1_init(TIMER_configType* a_TimerConfig1_Ptr);

/*------------------------------------------------------------------------------
 [Function Name]:TIMER_stop
 [Arguments]:
 [in]		TIMER_IdType  timer_ID:
 				Indicates the ID of the timer used.
 [Description]: This function stop the timer.
 [Return]: None
 -------------------------------------------------------------------------------*/
void TIMER_stop();

#endif /* MCAL_TIMER_TIMER_H_ */
