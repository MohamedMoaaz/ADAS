/**
* @file C3_VCLE_ALIGN.c
* @author Your Name (email) 
* @brief 
* @version 0.1
* @date 2023-09-15
*
*/


/******************************************************************************
* Includes
*******************************************************************************/
#include <LIB/STD_TYPES.h>
#include "BIT_MATH.h"
#include "LIB/UTILS.h"
#include "C3_VCLE_ALIGN.h"




/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/



/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/




/******************************************************************************
* Typedefs
*******************************************************************************/




/******************************************************************************
* Module Variable Definitions
*******************************************************************************/




/******************************************************************************
* Function Prototypes
*******************************************************************************/




/******************************************************************************
* Function Definitions
*******************************************************************************/


VCLE_State_t C3_voidIsVehicleAlignment(u8 copy_u8FrontRightDistance , u8 copy_u8RearRightDistance)
{
	VCLE_State_t LOC_ReturnBack = VCLE_NOT_ALINED_TURN_RIGHT ;
	u8 LOC_u8Diff = _ABS_((copy_u8FrontRightDistance - copy_u8RearRightDistance))  ;
	if(LOC_u8Diff > C3_ALIGNMENT_ERROR_MARGIN)
	{
		// Difference > Allowed hence: Not Aligned 
		if (copy_u8FrontRightDistance > copy_u8RearRightDistance)
		{
			LOC_ReturnBack = VCLE_NOT_ALINED_TURN_LEFT ; 
		}
		else
		{
			LOC_ReturnBack = VCLE_NOT_ALINED_TURN_RIGHT ; 						
		}
	}
	else
	{
		// Difference <= Allowed hence: Not Aligned 
		LOC_ReturnBack = VCLE_ALINED ; 
	}
	return LOC_ReturnBack;  
}

/************************************* End of File ******************************************/
