/*----------------------------------------------------------
 [FILE NAME]: twi.h

 [AUTHOR]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: June 17, 2022

 [DESCRIPTION]: This file contains the definitions and functions'
 	 	 	 	 prototypes of I2C.
 -----------------------------------------------------------*/

#ifndef MCAL_I2C_TWI_H_
#define MCAL_I2C_TWI_H_

#include "../../LIBRARIES/Std_types.h"

/*******************************************************************************************
 * 										Definitions
 ********************************************************************************************/
/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/* TWBR value of I2C data transfer rates working on zero-prescaler (TWPS = 00) and F_CPU = 8Mhz */
#define _100KB_BIT_RATE	(32)
#define _400KB_BIT_RATE (2)

/*************************************************************************************************
 * 										Sturctures and Unions
 *************************************************************************************************/
typedef struct
{
	uint8 bitRate;
	uint8 deviceAddress;
}TWI_configType;

/**************************************************************************************************
 * 										Funcitons' Prototype
 **************************************************************************************************/
/*------------------------------------------------------------------------
 [Function Name]:TWI_init
 [Arguments]:
 [in]	TWI_configTye *a_Ptr:
 	 	 	 	 It is a pointer to structure responsible for TWI configuraions
 [Description]: This function :
 	 	 	 	 1. set the TWI bit rate.
 	 	 	 	 2. set the prescaler.
 	 	 	 	 3. set the device address.
 	 	 	 	 4. enable TWI.
 [Return]:none
 -------------------------------------------------------------------------*/
void TWI_init(TWI_configType *a_Ptr);
/*------------------------------------------------------------------------
 [Function Name]:TWI_start
 [Arguments]:none
 [Description]: sends the start condition.
 [Return]:none
 -------------------------------------------------------------------------*/
void TWI_start(void);
/*------------------------------------------------------------------------
 [Function Name]:TWI_stop
 [Arguments]:none
 [Description]: sends the stop condition
 [Return]:none
 -------------------------------------------------------------------------*/
void TWI_stop(void);
/*------------------------------------------------------------------------
 [Function Name]:TWI_writeByte
 [Arguments]:none
 [Description]: sends the data to the slave device.
 [Return]:none
 -------------------------------------------------------------------------*/
void TWI_writeByte(uint8 data);

/*------------------------------------------------------------------------
 [Function Name]:TWI_readByteWithACK
 [Arguments]:none
 [Description]:
 [Return]:the data coming from the transmitter.
 -------------------------------------------------------------------------*/
uint8 TWI_readByteWithACK(void);
/*------------------------------------------------------------------------
 [Function Name]:TWI_readByteWithNACK
 [Arguments]: none
 [Description]: read the data from the slave and end the current transaction.
 [Return]: the last data coming from the receiver.
 -------------------------------------------------------------------------*/
uint8 TWI_readByteWithNACK(void);
/*------------------------------------------------------------------------
 [Function Name]:TWI_getStatus
 [Arguments]:none
 [Description]:read the status register  value of TWI.
 [Return]: the status register value.
 -------------------------------------------------------------------------*/
uint8 TWI_getStatus(void);


#endif /* MCAL_I2C_TWI_H_ */
