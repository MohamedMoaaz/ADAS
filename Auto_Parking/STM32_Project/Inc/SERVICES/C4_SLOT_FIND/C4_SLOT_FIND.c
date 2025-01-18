/**
* @file C4_SLOT_FIND.c
* @author Mohamed Abd El-Naby (mahameda.naby@gmail.com) 
* @brief 
* @version 0.1
* @date 2023-09-15
*
*/


/******************************************************************************
* Includes
*******************************************************************************/

#include "UTILS.h"
#include "std_types.h"
#include "SW_Delay.h"

#include "HAL/US/US.h"
#include "../C1_US_SLCT/C1_US_SLCT.h"
#include "C2_VCLE_CNTRL/C2_VCLE_CNTRL.h"
#include "../C3_VCLE_ALIGN/C3_VCLE_ALIGN.h"
#include "../C4_SLOT_FIND/C4_SLOT_FIND.h"




/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

#define ENABLE_FIND_LANE_PART         1

#define ENABLE_FIND_SLOT_PART         1

#define ENABLE_AFTER_SLOT_PART        1



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
#define BRAKE_DELAY_PARK	120
/**
 * 1 Sec  -- > 8000000
 * 4 Sec  -- > 32000000
 */
#define TIME_OUT_FOR_SLOT_SEARCH	32000000


#define FORCE_BREAK_FRM_FWD()  					C2VCONTROL_voidChangeDirection(VCLE_BWD,255	); \
												delay_ms(BRAKE_DELAY_PARK);\
												C2VCONTROL_voidChangeDirection(VCLE_STOP,0)
/******************************************************************************
* Function Definitions
*******************************************************************************/

void C4SLTFIND_voidInit(void)
{

}

// Uncovered Scenario :
// 					Exist vehicle in front of our vehicle in general lane
//					Behavior: Our Algorithm will suppose that current position is suitable for parking
ERROR_t C4SLTFIND_voidSearchingforSlotFull(void)
{
    u16 LOC_u8FrontDistance ,  LOC_u8BackDistance , LOC_u8FRDistance, LOC_u8BRDistance ;
    u8 LOC_u8ReadyToFindSlot = 0 ;  // OPS : 0 Searching for lane, 1 Searching For Slot, 2 Find Slot, 3 Move Forward to be ready for parking
    VCLE_State_t LOC_xVechileAlignState ; 
    ERROR_t LOC_xReturnError = E_OK ; 

    /******************************************** Find Parking Lane ***************************************************/
    #if ENABLE_FIND_LANE_PART == 1 
    while(LOC_u8ReadyToFindSlot != 1)
    {
        // Find Lane 
        // Measure Distance 
        LOC_xReturnError = C4_StaticGetFourDistance(&LOC_u8FrontDistance,&LOC_u8BackDistance,&LOC_u8FRDistance,&LOC_u8BRDistance);
        if(LOC_xReturnError != E_OK)
            return LOC_xReturnError ; 
        // Check Front and Front Right Sensors 
        if((LOC_u8FrontDistance <= MIN_DISTANCE_TO_BE_IN_PARKING_LANE || LOC_u8FRDistance <= MIN_DISTANCE_TO_BE_IN_PARKING_LANE))
        {
            /****************************************** Possiable Parking Lane *****************************************/
            // Stop Vechile 
            C2VCONTROL_voidChangeDirection(VCLE_STOP,0); 
            // Check Alignment 
            LOC_xVechileAlignState = C3_voidIsVehicleAlignment(LOC_u8FRDistance , LOC_u8BRDistance); 
            if(LOC_xVechileAlignState != VCLE_ALINED)
            {
                if(LOC_xVechileAlignState == VCLE_NOT_ALINED_TURN_LEFT)
                {
                    // VCLE_NOT_ALINED_TURN_LEFT 
                    C2VCONTROL_voidChangeDirection(VCLE_LEFT_FWD,FIND_SLOT_SPEED);
                    delay_ms(50);
                    C2VCONTROL_voidChangeDirection(VCLE_FWD,0); 
                }
                else 
                {
                    // VCLE_NOT_ALINED_TURN_Right
                    C2VCONTROL_voidChangeDirection(VCLE_RIGHT_FWD,FIND_SLOT_SPEED); 
                    delay_ms(50);
                    C2VCONTROL_voidChangeDirection(VCLE_FWD,0); 
                }
            }
            else
            {
             LOC_u8ReadyToFindSlot = 1 ;
            }
        }

        else 
        {
            /***************************************** The Distance is so big ****************************/ 
            // Moving Forward Right 
            C2VCONTROL_voidChangeDirection(VCLE_RIGHT_FWD,FIND_SLOT_SPEED); 
            delay_ms(100); 
        }
    }
    #endif 
    
    C2VCONTROL_voidChangeDirection(VCLE_FWD,0); // اعدل العجل 

    #if ENABLE_FIND_SLOT_PART == 1 
    // If Goes Here so LOC_u8ReadyToFindSlot == 1 
    while (LOC_u8ReadyToFindSlot != 2 )
    {        
        // Measure Distance 
        LOC_xReturnError = C4_StaticGetFourDistance(&LOC_u8FrontDistance,&LOC_u8BackDistance,&LOC_u8FRDistance,&LOC_u8BRDistance);
        if(LOC_xReturnError != E_OK)
            return LOC_xReturnError ; 
        // Check Slot 
        if(LOC_u8FRDistance >= MIN_DEPTH_TO_DETECT_SLOT && LOC_u8BRDistance >=MIN_DEPTH_TO_DETECT_SLOT)    
        {
            // Stop Vechile and make sterring nutural 
            C2VCONTROL_voidChangeDirection(VCLE_FWD,0); // اعدل العجل 
            // Align Vechile 
            LOC_xVechileAlignState = C3_voidIsVehicleAlignment(LOC_u8FRDistance , LOC_u8BRDistance); 
            if(LOC_xVechileAlignState != VCLE_ALINED)
            {
                if(LOC_xVechileAlignState == VCLE_NOT_ALINED_TURN_LEFT)
                {
                    // VCLE_NOT_ALINED_TURN_LEFT 
                    C2VCONTROL_voidChangeDirection(VCLE_LEFT_FWD,FIND_SLOT_SPEED); 
                    delay_ms(50);
                    C2VCONTROL_voidChangeDirection(VCLE_FWD,0); 
                }
                else 
                {
                    // VCLE_NOT_ALINED_TURN_Right
                    C2VCONTROL_voidChangeDirection(VCLE_RIGHT_FWD,FIND_SLOT_SPEED); 
                    delay_ms(50);
                    C2VCONTROL_voidChangeDirection(VCLE_FWD,0); 
                }
            }
            else
            {
                // Aligned 
                // Exist Slot 
                LOC_u8ReadyToFindSlot = 2 ;
            }

        }
        else if (LOC_u8FrontDistance  <= MIN_FRONT_DISTANCE_IN_PARKING )
        {
            // No Avialable Slot 
            return NO_SLOT; 
        }
        else
        {
            // Still Searching  For Slot 
            C2VCONTROL_voidChangeDirection(VCLE_FWD,FIND_SLOT_SPEED);
        }
    }
    #endif 

    C2VCONTROL_voidChangeDirection(VCLE_FWD,0); // اعدل العجل 
    #if ENABLE_AFTER_SLOT_PART == 1
    // Here Start Moving Forward for time of until find reference 
    while (LOC_u8ReadyToFindSlot != 3)
    {
        C2VCONTROL_voidChangeDirection(VCLE_FWD,FIND_SLOT_SPEED); 
        // Measure Distance 
        LOC_xReturnError = C4_StaticGetFourDistance(&LOC_u8FrontDistance,&LOC_u8BackDistance,&LOC_u8FRDistance,&LOC_u8BRDistance);
        if ((LOC_u8FRDistance <= MIN_DEPTH_TO_DETECT_SLOT && LOC_u8BRDistance <= MIN_DEPTH_TO_DETECT_SLOT) /* && Timout*/)
        {
            LOC_u8ReadyToFindSlot = 3 ; 
        }     
    }
    #endif 
    
    return LOC_xReturnError ;
}


ERROR_t C4SLTFIND_voidSearchingforSlot(void)
{
	u16 loc_u16Front,loc_u16Back,loc_u16FrontRight,loc_u16BackRight;
	u32 LOC_u32SlotTimeOut = 0 ;
	ERROR_t loc_udErrorStat = NO_SLOT;
	loc_udErrorStat = C4_StaticGetFourDistance(&loc_u16Front,&loc_u16Back,&loc_u16FrontRight,&loc_u16BackRight);
	if(E_OK != loc_udErrorStat)
	{
		C2VCONTROL_voidChangeDirection(VCLE_STOP,0);
		return loc_udErrorStat;
	}
	else
	{
		/*1st motion until the slot is detected*/
		C2VCONTROL_voidChangeDirection(VCLE_FWD,FIND_SLOT_SPEED);

		while(( (MIN_DEPTH_TO_DETECT_SLOT > loc_u16BackRight) || (MIN_DEPTH_TO_DETECT_SLOT >loc_u16FrontRight) ))
		{
			loc_udErrorStat = C4_StaticGetFourDistance(&loc_u16Front,&loc_u16Back,&loc_u16FrontRight,&loc_u16BackRight);
			if(E_OK != loc_udErrorStat)
			{
				C2VCONTROL_voidChangeDirection(VCLE_FWD,0);
				return loc_udErrorStat;
			}
			if(loc_u16Front < 16)
			{
				// End of Lane, No Parking Slot
				return NO_SLOT ;
			}
		}
		// brake By Backward movement
		FORCE_BREAK_FRM_FWD();

		// Update Vehicle Position
		C2VCONTROL_voidChangeDirection(VCLE_RIGHT_FWD, FIND_SLOT_SPEED+50);
		delay_ms(900);

		/******************************************************************/
		/* now the slot is detected by the two us's so continue to move */
		/* until the right back us read the minimum value or smaller */
		/* Make An Timeout Event for Forward movement 			*/

		loc_udErrorStat = C4_StaticGetFourDistance(NULL,NULL,&loc_u16FrontRight,&loc_u16BackRight);
		if(E_OK != loc_udErrorStat)
		{
			C2VCONTROL_voidChangeDirection(VCLE_STOP,0);
			return loc_udErrorStat;
		}
		else
		{
			C2VCONTROL_voidChangeDirection(VCLE_FWD,FIND_SLOT_SPEED);
			while(MIN_DEPTH_TO_DETECT_SLOT < loc_u16BackRight)
			{
				loc_udErrorStat = C4_StaticGetFourDistance(NULL,NULL,&loc_u16FrontRight,&loc_u16BackRight);
				if(E_OK != loc_udErrorStat)
				{
					C2VCONTROL_voidChangeDirection(VCLE_STOP,0);
					return loc_udErrorStat;
				}
				// For Time out
				if(LOC_u32SlotTimeOut > TIME_OUT_FOR_SLOT_SEARCH)
				{
					break ;
				}
				LOC_u32SlotTimeOut++;
			}

		}
		FORCE_BREAK_FRM_FWD();
	}

	return loc_udErrorStat;
}
/************************************* End of File ******************************************/
