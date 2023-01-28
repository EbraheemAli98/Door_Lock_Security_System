/*------------------------------------------------------------------------------
 [FILE NAME]: uart.h

 [AUTHOR]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: June 10, 2022

 [DESCRIPTION]: This file contain the definitions ,configuration and Functions'
  	  	  	  	prototypes.
 -------------------------------------------------------------------------------*/

#ifndef MCAL_UART_UART_H_
#define MCAL_UART_UART_H_

#include "../../LIBRARIES/Std_types.h"

/*******************************************************************************
 *                                Definitions	                               *
 *******************************************************************************/
#define PARITY_CHECKER	DISABLE_PARITY

#define DISABLE_PARITY 0
#define EVEN_PARITY	1
#define ODD_PARITY 2

#define FIVE_BITS	0
#define SIX_BITS	1
#define SEVEN_BITS	2
#define EIGHT_BITS	3
#define NINE_BITS	7

/*******************************************************************************
 *                                ENUMS	                                       *
 *******************************************************************************/

/*-----------------------------------------------------------------
 [ENUM Name]: UART_stopBitNumType
 [Description]: Indicates the number of stop bits in the frame.
 ------------------------------------------------------------------*/
typedef enum
{
	ONE_STOP_BIT,
	TWO_STOP_BITS
}UART_stopBitNumType;

/*******************************************************************************
 *                                STRUCTURE	                                       *
 *******************************************************************************/

/*-------------------------------------------------------------------
 [Structure Name]:UART_ConfigType
 [Description]: Indicates dynamic configuration of UART[variables can
 	 	 	 	be changed in rum-time].
 --------------------------------------------------------------------*/
typedef struct
{
	uint32 baud_rate;
	uint8 frame_type;
	uint8 parity_type;
	UART_stopBitNumType N_StopBits;
}UART_ConfigType;
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*-------------------------------------------------------------------------
 [Function Name]:UART_init
 [Arguments]:
 [in]		 UART_ConfigType* uart_config:
 	 	 	 	 	 It's a pointer to structure pointer to access the dynamic
 	 	 	 	 	 configurations members of UART.
 [Description]:
 	 	 	 	1. set the baud rate.
 	 	 	 	2. set the frame size (number of data bits)
 	 	 	 	3. set how many numbers of stop bit do you want.
 	 	 	 	4. set the type of parity bit (if u decided to use it).
 [Return]: None
 --------------------------------------------------------------------------*/
void UART_init(UART_ConfigType* uart_config);

/*-------------------------------------------------------------------------
 [Function Name]:UART_sendByte
 [Arguments]:
 [in]		uint8 data: contains the transmit data.
 [Description]: transmit the data in the UDR transmit register.
 [Return]: None
 --------------------------------------------------------------------------*/
void UART_sendByte(uint8 data);

/*-------------------------------------------------------------------------
 [Function Name]: UART_receiveByte
 [Arguments]:None
 [Description]: wait the data to completely received then read it from UDR.
 [Return]: the data received and stored in UDR receive.
 --------------------------------------------------------------------------*/
uint8 UART_receiveByte(void);

#if 0
/*-------------------------------------------------------------------------
 [Function Name]:UART_sendString
 [Arguments]:
 [in] 		uint8 *Str: the string wanted to transmitted.
 [Description]:This function is used to send a string to the receiver.
 [Return]:None
 --------------------------------------------------------------------------*/
void UART_sendString(uint8 *Str);

/*-------------------------------------------------------------------------
 [Function Name]: UART_receiveString
 [Arguments]: None
 [Description]: This function receive a string sent by the transmitter.
 [Return]: return the received string.
 --------------------------------------------------------------------------*/
void UART_receiveString(uint8* Str);
#endif

#if 0
void UART_sendPassword(uint8 *password);
void UART_receivePassword(uint8 *password);
#endif

#endif /* MCAL_UART_UART_H_ */

