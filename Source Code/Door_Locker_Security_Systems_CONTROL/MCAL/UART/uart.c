/*------------------------------------------------------------------------------
 [FILE NAME]: uart.h

 [AUTHOR]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: June 12, 2022

 [DESCRIPTION]: This file contain the Functions' definitions
 -------------------------------------------------------------------------------*/
#include <avr/io.h>
#include "uart.h"
#include "../../LIBRARIES/comman_macros.h"


void UART_init(UART_ConfigType* uart_config)
{
	uint16 ubrr_value = 0;
	/****************** UCSRA Description ******************************
	 * set U2X=1 for double transmission speed.
	 *******************************************************************/
	UCSRA = (1<<U2X);

	/**************************UCSRB Description ************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART TX Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0 For 8-bit data mode
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ******************************************************************/
	UCSRB = (1<<TXEN)|(1<<RXEN);

	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = 00 Disable parity bit
	 * USBS    = 0 One stop bit
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/
	UCSRC = (uart_config->N_StopBits<<USBS)|(uart_config->frame_type<<1)|(uart_config->parity_type<<4)|(1<<URSEL);

	/* *************************************
	 * Calculate the UBRR register value
	 * *************************************/
	ubrr_value = (uint16)(((F_CPU)/(uart_config->baud_rate*8UL))-1);

	/****************************************************************************
	 * First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH
	 ****************************************************************************/
	UBRRH = (ubrr_value >> 8);
	UBRRL = ubrr_value;
}

void UART_sendByte(uint8 data)
{
	/*
	 *  Poll until the USART data register empty flag is, to make sure the UDR has empty now and ready to transmit
	 *  a new data.
	 * The flag is cleared automatically when the receive buffer is empty.
	 */
	while(BIT_IS_CLEAR(UCSRA,UDRE));
	/*
	 * Put the required data in UDR register
	 * It also clear the UDRE flag as the UDR register is not empty now.
	 */
	UDR = data;
}


uint8 UART_receiveByte(void)
{
	/*
	 *  Poll until the receive complete flag is set, to make sure the UDR has an correctly unread data
	 * The flag is cleared automatically when the receive buffer is empty.
	 */
	while(BIT_IS_CLEAR(UCSRA,RXC));
	/* Read the unread data in the receive buffer register */
	return UDR;
}

void UART_sendString(uint8 *Str)
{
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}
}

void UART_receiveString(uint8* Str)
{
	uint8 i=0;
	Str[i] = UART_receiveByte();
	/*
	 * Receive the whole string until the MASTER is send '$'
	 * '$' here is Used by the programmer/user to refer to the end of the
	 * string received, because we can't send '\0'.
	 */
	while(Str[i] != '$')
	{
		i++;
		Str[i] = UART_receiveByte();
	}
	/* After receiving the whole string plus the '$', replace the '$' with '\0' */
	Str[i] = '\0';

}
