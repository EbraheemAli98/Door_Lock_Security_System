/*--------------------------------------------------------------------------------
 [FILE NAME]: Std_types

 [AUTHOR]: Ebraheem Ali

 [VERSION]: V1.0

 [DATA CREATION]: May 30, 2022

 [DESCRIPTION]: This file contains all the typedef of the different data types.
 ---------------------------------------------------------------------------------*/

#ifndef HELPERS_STD_TYPES_H_
#define HELPERS_STD_TYPES_H_


#ifndef FALSE
#define FALSE (0u)
#endif

#ifndef TRUE
#define TURE (1u)
#endif

#define LOGIC_HIGH	(1u)
#define LOGIC_LOW	(0u)

#define NULL_PTR	((void*)0)

typedef unsigned char	bool;

typedef unsigned char		uint8;
typedef  signed char		int8;
typedef unsigned short		uint16;
typedef  signed short		int16;
typedef unsigned long		uint32;
typedef  signed long		int32;
typedef float				float32;
typedef double				float64;
typedef unsigned long long 	uint64;
typedef  signed long long	int64;



#endif /* HELPERS_STD_TYPES_H_ */
