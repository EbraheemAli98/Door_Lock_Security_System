/*------------------------------------------------------------------------------
 [FILE NAME]: timer.c

 [AUTHOR]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: June 14, 2022

 [DESCRIPTION]: This file contain the functions'definitons of TIMER.
 -------------------------------------------------------------------------------*/

#include "../../HELPERS/comman_macros.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "timer.h"

/*******************************************************************************
 * 						 Timer Global Variables
 *******************************************************************************/
static volatile void (*g_Timer1_callBack_Ptr)(void) = NULL_PTR;

/*******************************************************************************
 * 						Timer Functions' Definition
 *******************************************************************************/

/*---------------------------------------------------------------------------------------------------*/
void TIMER_stop()
{
		/* Group of instructions to stop timer1, not included in a function to save the time of context switch */
		TCCR1A = 0;
		TCCR1B = 0;
		TCNT1 = 0;
		ICR1 = 0;
#if(TIMER_INTERRUPT == ENABLE)
		TIMSK &= (~(1<<TICIE1)) & (~(1<<OCIE1A)) & (~(1<<OCIE1B)) & (~(1<<TOIE1));
#endif
}

/*******************************************************************************
 * 						 Timer Static Functions' Definition
 *******************************************************************************/
/*------------------------------------------ TIMER1_init ------------------------------------------------------*/

void TIMER1_init(TIMER_configType* a_TimerConfig2_Ptr)
{
	/* Initial Value for Timer1 */
	TCNT1 = a_TimerConfig2_Ptr->TimerInitValue;
	switch(a_TimerConfig2_Ptr->mode)
	{
/*================================================= Normal Mode ===================================================*/
	case NORMAL:
		/* Disable/Enable the TIMER0 OVF interrpt */
#if(TIMER_INTERRUPT == ENABLE)
		SET_BIT(TIMSK,TOIE1);
#endif
		/* DISABLE PWM for Normal mode */
		TCCR1A = (1<<FOC1A)|(1<<FOC1B);
		/* Select the prescaler for Normal mode */
		TCCR1B = (TCCR1B & 0xF8)|(a_TimerConfig2_Ptr->prescaler);

		break;
/*=========================================== CTC Mode ========================================================*/
	case CTC:
#if(TIMER1_CTC_MODE_NUMBER == CTC_MODE_NUMBER_12)
		/*
		 * Initialize ICR1 register if you want to use Mode 12 in Timer1 (ICR1 = TOP)
		 * This will disable the ICU feature.
		 */
		ICR1 = a_TimerConfig2_Ptr->TimerCompValue;
#if(TIMER_INTERRUPT == ENABLE)
		/* Enable interrupt for Timer1 Input Capure , this interrupt will triggered if ICR1 register reaches the TOP value */
		SET_BIT(TIMSK,TICIE1);
#endif
		/*
		 * Disable PWM for channel A,also set the COM1A1:0 bit functionality when the
		 * WGM13:0 bits are set to a normal or a CTC mode (non-PWM).
		 */
		TCCR1A = (1<<FOC1A)|(1<<FOC1B)|(0xF0 & (a_TimerConfig2_Ptr->CTC_waveForm<<4));
		/*
		 * Select CTC mode 12 in TIMER1 by setting WGM13:10 = 12
		 * select the prescaler CS12:10 = value
		 */
		TCCR1B = (1<<WGM12)| (1<<WGM13)| ((TCCR1B & 0xF8) | (a_TimerConfig2_Ptr->prescaler));

#elif(TIMER1_CTC_MODE_NUMBER == CTC_MODE_NUMBER_4)
		/* Initialize OCR1A = TOP ,for CTC Mode number (4)*/
		OCR1A = a_TimerConfig2_Ptr->TimerCompValue;
#if(TIMER_INTERRUPT == ENABLE)
		/* Enable output compare interrupt */
		SET_BIT(TIMSK,OCIE1A);
#endif
		/*
		 * Disable PWM for channel A,also set the COM1A1:0 bit functionality when the
		 * WGM13:0 bits are set to a normal or a CTC mode (non-PWM).
		 */
		TCCR1A = (1<<FOC1A)|(1<<FOC1B)|(a_TimerConfig2_Ptr->CTC_waveForm<<6);
		/*
		 * Select CTC mode 12 in TIMER1 by setting WGM13:10 = 12
		 * select the prescaler CS12:10 = value
		 */
		TCCR1B = (1<<WGM12) | ((TCCR1B & 0xF8) | (a_TimerConfig2_Ptr->prescaler));
#endif
		break;
/*=============================================== Fast_PWM Mode =================================================*/
	case FAST_PWM:

#if (TIMER1_FAST_PWM_MODE_NUMBER == FAST_PWM_MODE_NUMBER_15)
		/* set the TOP value in OCR1A for Fast_PWM mode number (15) */
		OCR1A = a_TimerConfig2_Ptr->TimerCompValue;
#if(TIMER_INTERRUPT == ENABLE)
		/* Enable Output Compare interrupt for channel A and ICU interrupt*/
		SET_BIT(TIMSK,OCIE1A);
#endif
		/*
		 * set the PWM_wave form in COM1A10:11 , COM1B10:11 in TCCR1A.
		 * set WGM10=1, WGM11=1 in TCCR1A for mode number (15).
		 * FOC1A = 0 ,FOC1B = 0
		 */
		TCCR1A = (1<<WGM10)|(1<<WGM11)|((TCCR1A & 0x0F)|(a_TimerConfig2_Ptr->PWM_waveForm<<4));
		/*
		 * set the prescaler value in CS10:12 in TCCR1B.
		 * set WGM12=1 , WGM13=1 in TCCR1B for Fast_PWM mode number (15).
		 * set ICES1=0,ICNC1=0
		 */
		TCCR1B = (a_TimerConfig2_Ptr->prescaler)|(1<<WGM00)|(1<<WGM01);

#elif(TIMER1_FAST_PWM_MODE_NUMBER == FAST_PWM_MODE_NUMBER_14)
		/*
		 * set the TOP value in ICR1 register for fast_PWM mode number (14)
		 * this will disable the ICU feature.
		 * */
		ICR1 = a_TimerConfig2_Ptr->TimerCompValue;
#if(TIMER_INTERRUPT == ENABLE)
		/*
		 * The Input Capture Interrupt is executed when the ICF1 Flag, located in TIFR, is set.
		 * This flag is set when a capture event occurs on the ICP1 pin. When the Input Capture Register (ICR1) is set by the WGM13:0
		 * to be used as the TOP value, the ICF1 Flag is set when the counter reaches the TOP value.
		 */
		SET_BIT(TIMSK,TICIE1);
#endif
		/*
		 * set the PWM_wave form in COM1A10:11 , COM1B10:11 in TCCR1A.
		 * set WGM10=0, WGM11=1 in TCCR1A for Fast_PWM mode number 14.
		 * FOC1A = 0 ,FOC1B = 0
		 */
		TCCR1A = (1<<WGM11)|((TCCR1A & 0x0F)|(a_TimerConfig2_Ptr->PWM_waveForm<<4));
		/*
		 * set the prescaler value in CS10:12 in TCCR1B.
		 * set WGM12=1 , WGM13=1 in TCCR1B for Fast_PWM mode number (14).
		 * ICNC1=0
		 */
		TCCR1B = (a_TimerConfig2_Ptr->prescaler)|(1<<WGM12)|(1<<WGM13);
#endif
		break;
	}
}
/*******************************************************************************
 * 						Timer Call Back Functions
 *******************************************************************************/
/*--------------------------------------------------------------------*/
void TIMER1_setCallBack(void (*a_Fun_Ptr)(void))
{
		g_Timer1_callBack_Ptr = a_Fun_Ptr;
}


/*******************************************************************************
 * 						TIMERS'	Interrupt Service Routine
 *******************************************************************************/
/*-------------------------- TIMER1 ISR -------------------------*/
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

ISR(TIMER1_CAPT_vect)
{
	if(g_Timer1_callBack_Ptr != NULL_PTR)
		(*g_Timer1_callBack_Ptr)();
}

