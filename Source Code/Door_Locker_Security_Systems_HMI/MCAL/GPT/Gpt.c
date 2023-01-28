/*------------------------------------------------------------------------------
 [FILE NAME]: timer.c

 [AUTHOR]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: June 14, 2022

 [DESCRIPTION]: This file contain the functions'definitons of TIMER.
 -------------------------------------------------------------------------------*/

#include "Gpt.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include "../../LIBRARIES/comman_macros.h"

/*******************************************************************************
 * 						GPT Static Functions' Prototypes
 *******************************************************************************/
/*------------------------------------------------------------------------------
 [Function Name]: GPT_InitTimer0
 [Arguments]:
 [in]		GPT_ConfigType*  Config_Ptr:
 	 	 	 	 Pointer to timer configuration structure.
 [Description]:
 	 	 	 	1. initiate TCNTx.
 	 	 	 	2. initiate OCRnx if Output Compare Mode.
 	 	 	 	3. set the timer mode.
 	 	 	 	4. set the timer clock.
 	 	 	 	5. Enable interrupt if needed.
 [Return]: None
 -------------------------------------------------------------------------------*/
#if(GPT_T0_INT_ENABLE == ENABLE)
static void GPT_InitTimer0(const GPT_ConfigType* Config_Ptr);
#endif
/*------------------------------------------------------------------------------
 [Function Name]: GPT_InitTimer1
 [Arguments]:
 [in]		GPT_ConfigType*  Config_Ptr:
 	 	 	 	 Pointer to timer configuration structure.
 [Description]:
 	 	 	 	1. initiate TCNTx.
 	 	 	 	2. initiate OCRnx if Output Compare Mode.
 	 	 	 	3. set the timer mode.
 	 	 	 	4. set the timer clock.
 	 	 	 	5. Enable interrupt if needed.
 [Return]: None
 -------------------------------------------------------------------------------*/
#if(GPT_T1_INT_ENABLE == ENABLE)
static void GPT_InitTimer1(const GPT_ConfigType* Config_Ptr);
#endif
/*------------------------------------------------------------------------------
 [Function Name]: GPT_InitTimer2
 [Arguments]:
 [in]		GPT_ConfigType*  Config_Ptr:
 	 	 	 	 Pointer to timer configuration structure.
 [Description]:
 	 	 	 	1. initiate TCNTx.
 	 	 	 	2. initiate OCRnx if Output Compare Mode.
 	 	 	 	3. set the timer mode.
 	 	 	 	4. set the timer clock.
 	 	 	 	5. Enable interrupt if needed.
 [Return]: None
 -------------------------------------------------------------------------------*/
#if(GPT_T2_INT_ENABLE == ENABLE)
static void GPT_InitTimer2(const GPT_ConfigType* Config_Ptr);
#endif
/*******************************************************************************
 * 						 GPT Global Variables
 *******************************************************************************/
/*
 * Private Pointer to function initialized by (void*)0.
 * This pointer will points to the function we want to call it back.
 */
#if(GPT_T0_INT_ENABLE == ENABLE)
static void (*g_Timer0_callBack_Ptr)(void) = NULL_PTR;
#endif
#if(GPT_T1_INT_ENABLE == ENABLE)
static void (*g_Timer1_callBack_Ptr)(void) = NULL_PTR;
#endif
#if(GPT_T2_INT_ENABLE == ENABLE)
static void (*g_Timer2_callBack_Ptr)(void) = NULL_PTR;
#endif


/*******************************************************************************
 * 						GPT Functions' Definition
 *******************************************************************************/

void GPT_startTimer(TimerType Tx)
{
	if(Tx>=0 && Tx<=2)
	{
		switch(Tx)
		{
#if(GPT_T0_INT_ENABLE == ENABLE)
		case T0:
			GPT_InitTimer0(&GPT_ConfigStructObj);
			break;
#endif
#if(GPT_T1_INT_ENABLE == ENABLE)
		case T1:
			GPT_InitTimer1(&GPT_ConfigStructObj);
			break;
#endif
#if(GPT_T2_INT_ENABLE == ENABLE)
		case T2:
			GPT_InitTimer2(&GPT_ConfigStructObj);
			break;
#endif
		default:
			/* Do Nothing... */
			break;
		}
	}
	else
	{
		/* Do Nothing... */
	}
}
#ifdef GPT_SET_PRESCALER_API
/*--------------------------------------- GPT_setPrescaler ----------------------------------------------------------*/
void GPT_setPrescaler(TimerType Tx,GPT_PrescalerType value)
{
	if(Tx >= T0 && Tx <= T2)
	{
		switch(Tx)
		{
		case T0:
			TCCR0 = (TCCR0 & 0xF8)|(value);
			break;
		case T1:
			TCCR1B = (TCCR1B & 0xF8) | (value);
			break;
		case T2:
			TCCR2 = (TCCR2 & 0xF8)|(value);
			break;
		default:
			/* Do Nothing...*/
			break;
		}
	}
	else
	{
		/* Do Nothing...*/
	}
}
#endif
/*--------------------------------------- GPT_setInitValue ----------------------------------------------------------*/
#ifdef GPT_SET_INIT_VALUE_API
void GPT_setInitValue(TimerType Tx,TimerValueType value)
{
	if(Tx>=T0 && Tx<=T2)
	{
		switch(Tx)
		{
		case T0:
			TCNT0 = value;
			break;
		case T1:
			TCNT1 = value;
			break;
		case T2:
			TCNT2 = value;
			break;
		default:
			/* Do Nothing...*/
			break;
		}
	}
	else
	{
		/* Do Nothing...*/
	}
}
#endif
/*--------------------------------------- GPT_setCompValue ----------------------------------------------------------*/
#ifdef GPT_SET_COMP_VALUE_API
void GPT_setCompValue(TimerType Tx,TimerValueType value)
{
	if(Tx>=T0 && Tx<=T2)
	{
		switch(Tx)
		{
		case T0:
			OCR0 = value;
			break;
		case T1:
			OCR1A = value;
			break;
		case T2:
			OCR2 = value;
			break;
		default:
			/* Do Nothing...*/
			break;
		}
	}
	else
	{
		/* Do Nothing...*/
	}
}
#endif
/*--------------------------------------- GPT_setMode ----------------------------------------------------------*/
#ifdef GPT_SET_MODE_API
void GPT_setMode(TimerType Tx,GPT_ModeType mode)
{
	if((Tx >= T0 && Tx <= T2) && (mode == NORMAL || mode == OUTPUT_COMPARE))
	{
		switch(Tx)
		{
		case T0:
			(mode == NORMAL)? (TCCR0 &=~ (1<<WGM01)):(TCCR0 |= (1<<WGM01));
			break;
		case T1:
#if(TIMER1_CTC_MODE_NUMBER == CTC_MODE_NUMBER_12)
			(mode == NORMAL)? (TCCR1B &= ~(1<<WGM12) & ~(1<<WGM13)):(TCCR1B |= (1<<WGM12)| (1<<WGM13));

#else
			(mode == NORMAL)? (TCCR1B &=~ (1<<WGM12)):(TCCR1B |= (1<<WGM12));

#endif
			break;
		case T2:
			(mode == NORMAL)? (TCCR0 &=~ (1<<WGM21)):(TCCR0 |= (1<<WGM21));
			break;
		default:
			/* Do Nothing...*/
			break;
		}
	}
	else
	{
		/* Do Nothing...*/
	}
}
#endif
/*--------------------------------------- GPT_stopTimer ----------------------------------------------------------*/
void GPT_stopTimer(TimerType Tx)
{
	switch(Tx)
	{
	case T0:
		TCCR0 = 0;
		break;
	case T1:
		TCCR1B = 0;
		break;
	case T2:
		TCCR2 = 0;
		break;
	default:
		/* Do Nothing...*/
		break;
	}
}

/*------------------------------------------ GPT_InitTimer0 ------------------------------------------------------*/
#if(GPT_T0_INT_ENABLE == ENABLE)
static void GPT_InitTimer0(const GPT_ConfigType* Config_Ptr)
{
	if(Config_Ptr != NULL_PTR)
	{
		/* Set an Initial Value for Timer0 */
		TCNT0 = Config_Ptr->GPT_Config[T0].TimerInitValue;
		switch(Config_Ptr->GPT_Config[T0].mode)
		{
		/*================================================= Normal Mode ===============================================*/
		case NORMAL:
			/*
			 * Select Normal mode in TIMER0 by setting WGM01:00 = 0.
			 * Select the pre-scaler CS02:00 = prescaler_value
			 * Disable PWM.
			 * -----------------------------------------------------------
			 * |  B7 |  B6   |  B5 	 |   B4  |   B3  |  B2  |  B1  |  B0 |
			 * -----------------------------------------------------------
			 * |FOC0 | WGM00 | COM01 | COM00 | WGM01 | CS02 | CS01 | CS00|
			 * -----------------------------------------------------------
			 * |  1  |   0   |   - 	 |   -   |   0   |  prescaler_value  |
			 * -----------------------------------------------------------
			 */
			TCCR0 = (1<<FOC0)|((TCCR0 & 0xF8)|(Config_Ptr->GPT_Config[T0].prescaler));
			break;
		/*=========================================== CTC Mode ========================================================*/
		case OUTPUT_COMPARE:
			/* Initialize OCR0 = TOP ,for CTC Mode */
			OCR0 = Config_Ptr->GPT_Config[T0].TimerCompValue;
			/*
			 * Select Output-compare mode in TIMER0 by setting WGM01:00 = 2.
			 * Select the pre-scaler CS02:00 = prescaler_value
			 * Disable PWM.
			 * -----------------------------------------------------------
			 * |  B7 |  B6   |  B5 	 |   B4  |   B3  |  B2  |  B1  |  B0 |
			 * -----------------------------------------------------------
			 * |FOC0 | WGM00 | COM01 | COM00 | WGM01 | CS02 | CS01 | CS00|
			 * -----------------------------------------------------------
			 * |  1  |   0   |   - 	 |   -   |   1   |  prescaler_value  |
			 * -----------------------------------------------------------
			 */
			TCCR0 = (1<<FOC0)|(1<<WGM01)|((TCCR0 & 0xF8)|(Config_Ptr->GPT_Config[T0].prescaler))| (0x30 & (Config_Ptr->GPT_Config[T0].CTC_waveForm<<4));
			break;
		default:
			/* Do Nothing..*/
			break;
		}
	}
	else
	{
		/* Do Nothing...*/
	}
}
#endif
/*------------------------------------------ GPT_InitTimer1 ------------------------------------------------------*/
#if(GPT_T1_INT_ENABLE == ENABLE)
static void GPT_InitTimer1(const GPT_ConfigType* Config_Ptr)
{
	if(Config_Ptr != NULL_PTR)
	{
		/* Set an Initial Value for Timer1 */
		TCNT1 = Config_Ptr->GPT_Config[T1].TimerInitValue;
		switch(Config_Ptr->GPT_Config[T1].mode)
		{
		/*================================================= Normal Mode ===============================================*/
		case NORMAL:
			/* DISABLE PWM for Normal mode */
			TCCR1A = (1<<FOC1A)|(1<<FOC1B);
			/* Select the prescaler for Normal mode */
			TCCR1B = (TCCR1B & 0xF8)|(Config_Ptr->GPT_Config[T1].prescaler);

			break;
		/*=========================================== CTC Mode ========================================================*/
		case OUTPUT_COMPARE:
#if(TIMER1_CTC_MODE_NUMBER == CTC_MODE_NUMBER_12)
			/*
			 * Initialize ICR1 register if you want to use Mode 12 in Timer1 (ICR1 = TOP)
			 * This will disable the ICU feature.
			 */
			ICR1 = Config_Ptr->GPT_Config[T1].TimerCompValue;
			/*
			 * Disable PWM for channel A,also set the COM1A1:0 bit functionality when the WGM13:0 bits are set to a normal or a CTC mode (non-PWM).
			 */
			TCCR1A = (1<<FOC1A)|(1<<FOC1B)|(0xF0 & (Config_Ptr->GPT_Config[T1].CTC_waveForm<<4));
			/*
			 * Select CTC mode 12 in TIMER1 by setting WGM13:10 = 12, WGM13=1 ,WGM12=1 ,WGM11=0 ,WGM10=0.
			 * select the pre-scaler CS12:10 = value
			 * ----------------------------------------------------------
			 * |  B7  |  B6   |  B5 |   B4  |   B3  |  B2  |  B1  |  B0 |
			 * ----------------------------------------------------------
			 * |ICNC1 | ICES1 |  -  | WGM13 | WGM12 | CS12 | CS11 | CS10|
			 * ----------------------------------------------------------
			 * |  0   |   0   |  -  |   1   |   1   |  prescaler_value  |
			 * ----------------------------------------------------------
			 */
			TCCR1B = (1<<WGM12)| (1<<WGM13)| ((TCCR1B & 0xF8) | (Config_Ptr->GPT_Config[T1].prescaler));

#elif(TIMER1_CTC_MODE_NUMBER == CTC_MODE_NUMBER_4)
			/* Initialize OCR1A = TOP ,for CTC Mode number (4)*/
			OCR1A = Config_Ptr->GPT_Config[T1].TimerCompValue;

			/*
			 * Disable PWM for channel A,also set the COM1A1:0 bit functionality when the
			 * WGM13:0 bits are set to a normal or a CTC mode (non-PWM).
			 * -----------------------------------------------------
			 * |  B7  |  B6  |  B5  |  B4  |  B3 |  B2 |  B1 |  B0 |
			 * -----------------------------------------------------
			 * |COM1A1|COM1A0|COM1B1|COM1B0|FOC1A|FOC1B|WGM11|WGM10|
			 * -----------------------------------------------------
			 * |CTC_waveForm |  0   |  0   |  1  |  1  |  0  |  0  |
			 * -----------------------------------------------------
			 */
			TCCR1A = (1<<FOC1A)|(1<<FOC1B)|(Config_Ptr->GPT_Config[T1].CTC_waveForm<<6);
			/*
			 * Select CTC mode 12 in TIMER1 by setting WGM13:10 = 12
			 * select the prescaler CS12:10 = value
			 * ----------------------------------------------------------
			 * |  B7  |  B6   |  B5 |   B4  |   B3  |  B2  |  B1  |  B0 |
			 * ----------------------------------------------------------
			 * |ICNC1 | ICES1 |  -  | WGM13 | WGM12 | CS12 | CS11 | CS10|
			 * ----------------------------------------------------------
			 * |  0   |   0   |  -  |   0   |   1   |  prescaler_value  |
			 * ----------------------------------------------------------
			 */
			TCCR1B = (1<<WGM12) | ((TCCR1B & 0xF8) | (Config_Ptr->GPT_Config[T1].prescaler));
#endif
			break;
		default:
			/* Do nothing... */
			break;
		}
	}
	else
	{
		/* Do Nothing...*/
	}
}
#endif
/*------------------------------------------ GPT_InitTimer2 ------------------------------------------------------*/
#if(GPT_T2_INT_ENABLE == ENABLE)
static void GPT_InitTimer2(const GPT_ConfigType* Config_Ptr)
{
	if(Config_Ptr != NULL_PTR)
	{
		/* Set an Initial Value for Timer0 */
		TCNT2 = Config_Ptr->GPT_Config[T2].TimerInitValue;
		switch(Config_Ptr->GPT_Config[T2].mode)
		{
		/*================================================= Normal Mode ===============================================*/
		case NORMAL:

			/*
			 * Select Normal mode in TIMER0 by setting WGM21:20 = 0.
			 * Select the pre-scaler CS22:20 = prescaler_value
			 * Disable PWM.
			 * -----------------------------------------------------------
			 * |  B7 |  B6   |  B5 	 |   B4  |   B3  |  B2  |  B1  |  B0 |
			 * -----------------------------------------------------------
			 * |FOC2 | WGM20 | COM21 | COM20 | WGM21 | CS22 | CS21 | CS20|
			 * -----------------------------------------------------------
			 * |  1  |   0   |   - 	 |   -   |   0   |  prescaler_value  |
			 * -----------------------------------------------------------
			 */
			TCCR2 = (1<<FOC2)|((TCCR2 & 0xF8)|(Config_Ptr->GPT_Config[T2].prescaler));
			break;
		/*=========================================== CTC Mode ========================================================*/
		case OUTPUT_COMPARE:

			/* Initialize OCR0 = TOP ,for CTC Mode */
			OCR2 = Config_Ptr->GPT_Config[T2].TimerCompValue;
			/*
			 * Select Output-compare mode in TIMER0 by setting WGM21:20 = 2.
			 * Select the pre-scaler CS22:20 = prescaler_value
			 * Disable PWM.
			 * -----------------------------------------------------------
			 * |  B7 |  B6   |  B5 	 |   B4  |   B3  |  B2  |  B1  |  B0 |
			 * -----------------------------------------------------------
			 * |FOC2 | WGM20 | COM21 | COM20 | WGM21 | CS22 | CS21 | CS20|
			 * -----------------------------------------------------------
			 * |  1  |   0   |   - 	 |   -   |   1   |  prescaler_value  |
			 * -----------------------------------------------------------
			 */
			TCCR2 = (1<<FOC2)|(1<<WGM21)|((TCCR2 & 0xF8)|(Config_Ptr->GPT_Config[T2].prescaler))| (0x30 & (Config_Ptr->GPT_Config[T2].CTC_waveForm <<4));
			break;
		default:
			/* Do Nothing..*/
			break;
		}
	}
	else
	{
		/* Do Nothing..*/
	}
}
#endif
/*******************************************************************************
 * 						GPT Enable/Disable Notification Functions
 *******************************************************************************/
void GPT_enableNotification(TimerType Tx,GPT_ModeType mode)
{
	if((Tx >= T0 && Tx <= T2) && (mode == NORMAL || mode == OUTPUT_COMPARE))
	{
		switch(Tx)
		{
		case T0:
			(mode == NORMAL)? SET_BIT(TIMSK,TOIE0):SET_BIT(TIMSK,OCIE0);
			break;
		case T1:
#if(TIMER1_CTC_MODE_NUMBER == CTC_MODE_NUMBER_12)
			(mode == NORMAL)? SET_BIT(TIMSK,TOIE1):SET_BIT(TIMSK,TICIE1);

#else
			(mode == NORMAL)? SET_BIT(TIMSK,TOIE1):SET_BIT(TIMSK,OCIE1A);

#endif
			break;
		case T2:
			(mode == NORMAL)? SET_BIT(TIMSK,TOIE2):SET_BIT(TIMSK,OCIE2);
			break;
		default:
			/* Do Nothing...*/
			break;
		}
	}
	else
	{
		/* Do Nothing...*/
	}
}
/*------------------------------------------ GPT_disableNotification -------------------------------------------*/
void GPT_disableNotification(TimerType Tx,GPT_ModeType mode)
{
	if((Tx >= T0 && Tx <= T2) && (mode == NORMAL || mode == OUTPUT_COMPARE))
	{
		switch(Tx)
		{
		case T0:
			(mode == NORMAL)? CLEAR_BIT(TIMSK,TOIE0):CLEAR_BIT(TIMSK,OCIE0);
			break;
		case T1:
#if(TIMER1_CTC_MODE_NUMBER == CTC_MODE_NUMBER_12)
			(mode == NORMAL)? CLEAR_BIT(TIMSK,TOIE1):CLEAR_BIT(TIMSK,TICIE1);
			break;
#else
			(mode == NORMAL)? CLEAR_BIT(TIMSK,TOIE1):CLEAR_BIT(TIMSK,OCIE1A);
			break;
#endif
		case T2:
			(mode == NORMAL)? CLEAR_BIT(TIMSK,TOIE2):CLEAR_BIT(TIMSK,OCIE2);
			break;
		default:
			/* Do Nothing...*/
			break;
		}
	}
	else
	{
		/* Do Nothing...*/
	}
}
/*******************************************************************************
 * 						Timer Call Back Functions
 *******************************************************************************/
#if(GPT_T0_INT_ENABLE == ENABLE)
void GPT_T0_setCallBack(void (*a_Fun_Ptr)(void))
{
	g_Timer0_callBack_Ptr = a_Fun_Ptr;
}
#endif
/*--------------------------------------------------------------------*/
#if(GPT_T1_INT_ENABLE == ENABLE)
void GPT_T1_setCallBack(void (*a_Fun_Ptr)(void))
{
	g_Timer1_callBack_Ptr = a_Fun_Ptr;
}
#endif
/*-------------------------------------------------------------------*/
#if(GPT_T2_INT_ENABLE == ENABLE)
void GPT_T2_setCallBack(void (*a_Fun_Ptr)(void))
{
	g_Timer2_callBack_Ptr = a_Fun_Ptr;
}
#endif
/*******************************************************************************
 * 						TIMERS'	Interrupt Service Routine
 *******************************************************************************/
/*-------------------------- TIMER0 ISR -------------------------*/
#if(GPT_T0_INT_ENABLE == ENABLE)
ISR(TIMER0_OVF_vect)
{
	if(g_Timer0_callBack_Ptr != NULL_PTR)
		(*g_Timer0_callBack_Ptr)();
}

ISR(TIMER0_COMP_vect)
{
	if(g_Timer0_callBack_Ptr != NULL_PTR)
		(*g_Timer0_callBack_Ptr)();
}
#endif
/*-------------------------- TIMER1 ISR -------------------------*/
#if(GPT_T1_INT_ENABLE == ENABLE)
ISR(TIMER1_OVF_vect)
{
	if(g_Timer1_callBack_Ptr != NULL_PTR)
		(*g_Timer1_callBack_Ptr)();
}

ISR(TIMER1_COMPA_vect)
{
	if(g_Timer1_callBack_Ptr != NULL_PTR)
		(*g_Timer1_callBack_Ptr)();
}

ISR(TIMER1_COMPB_vect)
{
	if(g_Timer1_callBack_Ptr != NULL_PTR)
		(*g_Timer1_callBack_Ptr)();
}
#endif
/*-------------------------- TIMER2 ISR -------------------------*/
#if(GPT_T2_INT_ENABLE == ENABLE)
ISR(TIMER2_OVF_vect)
{
	if(g_Timer2_callBack_Ptr != NULL_PTR)
		(*g_Timer2_callBack_Ptr)();
}

ISR(TIMER2_COMP_vect)
{
	if(g_Timer2_callBack_Ptr != NULL_PTR)
		(*g_Timer2_callBack_Ptr)();
}
#endif
