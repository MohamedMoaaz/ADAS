/**
 * @file C5_PARKING.c
 * @author Your Name (email)
 * @brief
 * @version 0.1
 * @date 2023-09-15
 *
 */
/******************************************************************************
 * Includes
 *******************************************************************************/
#include "STD_TYPES.h"
#include "UTILS.h"
#include "SW_Delay.h"
#include "BIT_MATH.h"
#include "../SERVICES/C1_US_SLCT/C1_US_SLCT.h"
#include "../SERVICES/C3_VCLE_ALIGN/C3_VCLE_ALIGN.h"
#include "../SERVICES/C2_VCLE_CNTRL/C2_VCLE_CNTRL.h"
#include "C5_PARKING.h"





/******************************************************************************
 * Module Preprocessor Constants
 *******************************************************************************/

/**
 * Suiatable Untill now 180
 */
#define PARKING_SPEED					(u16)170

#define MOVEMENT_DELAY					1000

#define FORCE_STOP_DELAY	100


/******************************************************************************
 * Module Preprocessor Macros
 *******************************************************************************/
#define BACK_RIGHT_THERSHOLD			(u8)4
#define BACK_THERSHOLD					(u8)15


#define ENABLE_FORS_BRK				0




/******************************************************************************
 * Typedefs
 *******************************************************************************/


typedef enum
{
	PARKING_NOK,
	PARKING_OK

}ParkingStat_t;


/******************************************************************************
 * Module Variable Definitions
 *******************************************************************************/




/******************************************************************************
 * Function Prototypes
 *******************************************************************************/



/******************************************************************************
 * Function Definitions
 *******************************************************************************/


void C5VCLEPRK_voidInitParking(void)
{

	/*initialize the US sensor select component*/
	APPC1_Init();
	/*initialize motion control component*/
	//C2VCONTROL_voidInit();

}

ERROR_t C5VCLEPRK_voidStartParking(void)
{
	ERROR_t LOC_xReturnError ;
	u16 LOC_u16FrontDistance ;
	u16 LOC_u16BackDistance ;
	u16 LOC_u16FrontRightDistance ;
	u16 LOC_u16BackRightDistance ;
	u8 LOC_u8AlignmentDiffer ;
	(void)LOC_u8AlignmentDiffer;
	u8 StartParkingPrecedure = 0 ;

	// Stop Vehicle
	C2VCONTROL_voidChangeDirection(VCLE_STOP,0);

	// Evaluate First Impression
	LOC_xReturnError = C4_StaticGetFourDistance(&LOC_u16FrontDistance , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
	if(LOC_xReturnError != E_OK)
		return LOC_xReturnError ;
	LOC_u8AlignmentDiffer = _ABS_((LOC_u16FrontRightDistance-LOC_u16BackRightDistance)) ;
	// Suppose That Front, Back Distance are so big and FR, RR are aligned so start parking scenario
//	if(LOC_u16FrontDistance > 20 && LOC_u16BackDistance > 20 && LOC_u8AlignmentDiffer < 3)
//	{
//		StartParkingPrecedure = 1 ;
//	}
//	else
//	{
//		StartParkingPrecedure = 0 ;
//	}



	StartParkingPrecedure = 1 ;

	if(StartParkingPrecedure == 1)
	{
		// Because of we have poor steering
		C2VCONTROL_voidChangeDirection( VCLE_LEFT_FWD , PARKING_SPEED+30);
		delay_ms(600);

		// First Movement The Vehicle
		C2VCONTROL_voidChangeDirection( VCLE_RIGHT_BWD , PARKING_SPEED);

		while(LOC_u16BackDistance >= (40+3) )
		{
			LOC_xReturnError = C4_StaticGetFourDistance(NULL , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
			if(LOC_xReturnError != E_OK)
				return LOC_xReturnError ;

		}
		C2VCONTROL_voidChangeDirection(VCLE_STOP,0);
		delay_ms((MOVEMENT_DELAY));
		C2VCONTROL_voidChangeDirection( VCLE_RIGHT_BWD , PARKING_SPEED);

#if ENABLE_FORS_BRK	== 1
		C2VCONTROL_voidChangeDirection(VCLE_FWD,255	);
		delay_ms(FORCE_STOP_DELAY);
		C2VCONTROL_voidChangeDirection(VCLE_STOP,0);
#else
		C2VCONTROL_voidChangeDirection(VCLE_STOP,0);
#endif

	//
		delay_ms((MOVEMENT_DELAY));

		// Now Vehicle is stops at angle ~45 with slot
		LOC_xReturnError = C4_StaticGetFourDistance(NULL , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
		if(LOC_xReturnError != E_OK)
			return LOC_xReturnError ;

		C2VCONTROL_voidChangeDirection(VCLE_LEFT_BWD  , PARKING_SPEED+50);
		while(LOC_u16BackDistance > BACK_THERSHOLD-7 && StartParkingPrecedure != 2)
		{
			// Stop With The Same Angle
			LOC_xReturnError = C4_StaticGetFourDistance(NULL , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
			if(LOC_xReturnError != E_OK)
				return LOC_xReturnError ;
			// عشان لو لبست
			while (LOC_u16BackDistance >= 2000 || LOC_u16BackRightDistance >= 2000 || LOC_u16FrontRightDistance >= 2000)
			{
				// The vehicle on wall :)
				C2VCONTROL_voidChangeDirection(VCLE_FWD  , PARKING_SPEED);
				delay_ms((MOVEMENT_DELAY/2));
				C2VCONTROL_voidChangeDirection(VCLE_STOP  , PARKING_SPEED);
				delay_ms((MOVEMENT_DELAY/2));
				C2VCONTROL_voidChangeDirection(VCLE_LEFT_BWD  , PARKING_SPEED);
				LOC_xReturnError = C4_StaticGetFourDistance(NULL , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
				if(LOC_xReturnError != E_OK)
					return LOC_xReturnError ;
			}
			// Check End Point From Loop
			LOC_u8AlignmentDiffer = _ABS_((LOC_u16FrontRightDistance-LOC_u16BackRightDistance)) ;
			if(LOC_u8AlignmentDiffer <= 2 && LOC_u16FrontRightDistance < BACK_RIGHT_THERSHOLD )
			{
				StartParkingPrecedure = 2 ;
			}
		}

		C2VCONTROL_voidChangeDirection(VCLE_STOP,0);
		delay_ms((MOVEMENT_DELAY));

		if(StartParkingPrecedure == 1)
		{
			// Exit Due to Back Distance Isn't Enough
			// Start Alignment Procedure
			LOC_xReturnError = C4_StaticGetFourDistance(NULL , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
			if(LOC_xReturnError != E_OK)
				return LOC_xReturnError ;
			LOC_u8AlignmentDiffer = _ABS_((LOC_u16FrontRightDistance-LOC_u16BackRightDistance)) ;
			while(LOC_u8AlignmentDiffer > 2)
			{
				C2VCONTROL_voidChangeDirection(VCLE_RIGHT_FWD, PARKING_SPEED+25);
				delay_ms(500);
				C2VCONTROL_voidChangeDirection(VCLE_LEFT_BWD  , PARKING_SPEED);
				delay_ms(500);
				LOC_xReturnError = C4_StaticGetFourDistance(NULL , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
				if(LOC_xReturnError != E_OK)
					return LOC_xReturnError ;
				LOC_u8AlignmentDiffer = _ABS_((LOC_u16FrontRightDistance-LOC_u16BackRightDistance)) ;
			}
		}
		else // StartParkingPrecedure == 2
		{
			// Exit Due to Parking Is Complete
			// Then Go Forward Until Back Distance == Front Distance
		}
		C2VCONTROL_voidChangeDirection(VCLE_STOP  , 0);
		delay_ms(100);

	}
	return LOC_xReturnError;
}

/************************************* End of File ******************************************/
