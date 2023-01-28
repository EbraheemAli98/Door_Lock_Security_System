/*--------------------------------------------------------------------------------
 [FILE NAME]: eeprom.h

 [AUTHOR]:Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: June 18, 2022

 [DESCRIPTION]: This file contains the definitions and functions' prototypes of
 	 	 	 	external EEPROM memory
 ----------------------------------------------------------------------------------*/

#ifndef HAL_EEPROM_EEPROM_H_
#define HAL_EEPROM_EEPROM_H_

#include "../../LIBRARIES/Std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void EEPROM_Init(void);
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);

#endif /* HAL_EEPROM_EEPROM_H_ */
