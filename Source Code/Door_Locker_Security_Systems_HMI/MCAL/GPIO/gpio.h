/*--------------------------------------------------------------------------------
 [FILE NAME]: GPIO

 [AUTHOR]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATED]: May 30, 2022

 [DESCRIPTION]: This file contains all the declarations of the GPIO module.
 ---------------------------------------------------------------------------------*/

#ifndef MCAL_GPIO_GPIO_H_
#define MCAL_GPIO_GPIO_H_

#include "../../LIBRARIES/Std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define NUM_OF_PORTS           4
#define NUM_OF_PINS_PER_PORT   8

#define PORTA_ID               0
#define PORTB_ID               1
#define PORTC_ID               2
#define PORTD_ID               3

#define PIN0_ID                0
#define PIN1_ID                1
#define PIN2_ID                2
#define PIN3_ID                3
#define PIN4_ID                4
#define PIN5_ID                5
#define PIN6_ID                6
#define PIN7_ID                7

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/*-------------------------------------------------------------------------------
 [ENUM NAME]: GPIO_PinDirectionType
 [DESCRIPTION]: Indicates the type of the pin used.
 -------------------------------------------------------------------------------*/
typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

/*-------------------------------------------------------------------------------
 [ENUM NAME]: GPIO_PortDirectionType
 [DESCRIPTION]: Indicates the type of the port used.
 -------------------------------------------------------------------------------*/
typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*---------------------------------------------------------------------------------------------------
 [Function Name]: GPIO_setupPinDriection
 [Args]:
 [in]	uint8 port_num:
 	 	 	 	 - This parameter indicates the port ID.
 [in]   uint8 pin_num:
  	 	 	 	 - This parameter indicates the pin ID.
 [in] 	GPIO_PinDirectionType direction:
 	 	 	 	 - This parameter indicates the direction of the pin used.
 [Description]:
  	  1- Setup the direction of the required pin input/output.
  	  2- If the input port number or pin number are not correct, The function will not handle the request.
 ---------------------------------------------------------------------------------------------------*/
void GPIO_setupPinDirection(uint8 port_num,uint8 pin_num, GPIO_PinDirectionType direction);

/*------------------------------------------------------------------------------------------------------
 [Function Name]: GPIO_writePin
 [Args]:
 [in]	uint8 port_num:
 	 	 	 	 - This parameter indicates the port ID.
 [in]   uint8 pin_num:
  	 	 	 	 - This parameter indicates the pin ID.
 [in]	uint8 value:
 				- This parameter indicates the state of the pin (HIGH/LOW).
 [Description]:
  	  1- Write the value Logic High or Logic Low on the required pin.
 	  2- If the input port number or pin number are not correct, The function will not handle the request.
 	  3- If the pin is input, this function will enable/disable the internal pull-up resistor.
 -----------------------------------------------------------------------------------------------------------*/
void GPIO_writePin(uint8 port_num,uint8 pin_num, uint8 value);

/*----------------------------------------------------------------------------------------------------------
 [Function Name]: GPIO_readPin
 [Args]:
 [in]	uint8 port_num:
 	 	 	 	 - This parameter indicates the port ID.
 [in]   uint8 pin_num:
  	 	 	 	 - This parameter indicates the pin ID.
 [out]  uint8 a_pin_value:
 	 	 	 	  -  This variable store the value of the pin.
 [Description]:
 	 	1- Read and return the value for the required pin, it should be Logic High or Logic Low.
 	 	2- If the input port number or pin number are not correct, The function will return Logic Low.
 ----------------------------------------------------------------------------------------------------------*/
uint8 GPIO_readPin(uint8 port_num,uint8 pin_num);

/*--------------------------------------------------------------------------------------------------------
 [Function Name]:setupPortDirection
 [Args]:
 [in]	uint8 port_num:
 	 	 	 	 - This parameter indicates the port ID.
 [in]	uint8 direction:
 	 	 	 	 - This parameter indicates the direction of the port used.
 [Description]:
 	 1- Setup the direction of the required port all pins input/output.
 	 2- If the direction value is PORT_INPUT all pins in this port should be input pins.
 	 3- If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 	 4- If the input port number is not correct, The function will not handle the request.
 --------------------------------------------------------------------------------------------------------*/
void GPIO_setupPortDirection(uint8 port_num, uint8 direction);

/*---------------------------------------------------------------------------------------------------------
 [Function Name]:
 [Args]:
 [in]	uint8 port_num:
 	 	 	 	 - This parameter indicates the port ID.
 [in]	uint8 value:
 	 	 	 	 - This parameter indicates the state of the port (HIGH/LOW).
 [Description]:
 	 1- Write the value on the required port.
 	 2- If any pin in the port is output pin the value will be written.
 	 3- If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 	 4- If the input port number is not correct, The function will not handle the request.
 -----------------------------------------------------------------------------------------------------------*/
void GPIO_writePort(uint8 port_num, uint8 value);

/*----------------------------------------------------------------------------------------------------------
 [Function Name]: GPIO_readPort
 [Args]:
 [in]	uint8 port_num:
 	 	 	 	 - This parameter indicates the port ID.
 [out]	uint8 a_value:
  	 	  - This local variable store the value of the port.
 [Description]:
 	 1- Read and return the value of the required port.
 	 2- If the input port number is not correct, The function will return ZERO value.
 -----------------------------------------------------------------------------------------------------------*/
uint8 GPIO_readPort(uint8 port_num);


#endif /* MCAL_GPIO_GPIO_H_ */
