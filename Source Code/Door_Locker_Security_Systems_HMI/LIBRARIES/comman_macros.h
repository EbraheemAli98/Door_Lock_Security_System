/*--------------------------------------------------------------------------------
 [FILE NAME]: comman_macro

 [AUTHOR]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATION]: May 30, 2022

 [DESCRIPTION]: This file contains the dynamic definitions.
 ---------------------------------------------------------------------------------*/

#ifndef LIBRARIES_COMMAN_MACROS_H_
#define LIBRARIES_COMMAN_MACROS_H_

#define SET_BIT(REG,BIT)		(REG |= (1<<BIT))
#define CLEAR_BIT(REG,BIT)		(REG &=~(1<<BIT))
/* SHIFT_NUM: number of bits needed to rotate */
#define ROR(REG,SHIFT_NUM)		(REG = (REG>>SHIFT_NUM)|(REG<<(8-SHIFT_NUM)))
#define ROL(REG,SHIFT_NUM)		(REG = (REG<<SHIFT_NUM)|(REG>>(8-SHIFT_NUM)))
#define BIT_IS_SET(REG,BIT)		(REG & (1<<BIT))
#define BIT_IS_CLEAR(REG,BIT)	(!(REG & (1<<BIT)))

#endif /* LIBRARIES_COMMAN_MACROS_H_ */
