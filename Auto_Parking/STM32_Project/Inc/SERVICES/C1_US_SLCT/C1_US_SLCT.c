/**
* @file C1_US_SLCT.c
* @author Your Name (email) 
* @brief 
* @version 0.1
* @date 2023-09-14
*
*/

/******************************************************************************
* Includes
*******************************************************************************/
#include "STD_TYPES.h"
#include "RCC/RCC_interface.h"
#include "../MCAL/GPIO/GPIO_interface.h"
#include "../HAL/US/US.h"
#include "C1_US_SLCT.h"
#include "C4_SLOT_FIND/C4_SLOT_FIND.h"


/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/


/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/




/******************************************************************************
* Typedefs
*******************************************************************************/




/****************************** Don't Forget to Edit PORT/PIN OF IC in @ref IC4051.h    **************************************/ 


/****************************** Ultrasonic Configuration *******************************************************************/ 
static Ultrasonic_Cfg Global_UltraSonics ;



/******************************************************************************
* Module Variable Definitions
*******************************************************************************/




/******************************************************************************
* Function Prototypes
*******************************************************************************/




/******************************************************************************
* Function Definitions
*******************************************************************************/


void APPC1_Init(void)
{
	/**********************************	US	 *************************************/
	Global_UltraSonics.Timerx       = Timer2 ;
	Global_UltraSonics.CHANNEL_x    = CHANNEL_3 ;
	Global_UltraSonics.Trig_Port[0] = US1_TRIG_PORT ;
	Global_UltraSonics.Trig_Pin[0]  = US1_TRIG_PIN	;
	Global_UltraSonics.Trig_Port[1] = US2_TRIG_PORT    ;
	Global_UltraSonics.Trig_Pin[1]  = US2_TRIG_PIN	;
	Global_UltraSonics.Trig_Port[2] = US3_TRIG_PORT    ;
	Global_UltraSonics.Trig_Pin[2]  = US3_TRIG_PIN	;
    Global_UltraSonics.Trig_Port[3] = US4_TRIG_PORT    ;
	Global_UltraSonics.Trig_Pin[3]  = US4_TRIG_PIN	;
	Global_UltraSonics.US_x         = US_POLLING;
	US_voidInit(&Global_UltraSonics);

}

US_ERROR_t APPC1_SelectUltrasonc(US_Selection_t copy_UltrasonicNumber , u16 *pData_DistanceInCM)
{
	US_ERROR_t LOC_eReturnState = US_INVALID_READING ;
    switch (copy_UltrasonicNumber)
    {
		case FrontUS :
			LOC_eReturnState = US_voidGetDistanceSynch(&Global_UltraSonics , pData_DistanceInCM , FrontUS);
			break;
		
		case BackUS :
			LOC_eReturnState = US_voidGetDistanceSynch(&Global_UltraSonics , pData_DistanceInCM , BackUS);
			break;
		case FrontRightUS :
			LOC_eReturnState = US_voidGetDistanceSynch(&Global_UltraSonics , pData_DistanceInCM , FrontRightUS);
			break;
		case RearRightUS :
			LOC_eReturnState =US_voidGetDistanceSynch(&Global_UltraSonics , pData_DistanceInCM , RearRightUS);
			break;
		default :
			/*Do Nothing*/
			break;
    }
    return LOC_eReturnState ;
}

US_ERROR_t APPC1_xGetAllUSData(u8 pArr[])
{
	u16 data = 0 ;

	US_ERROR_t LOC_eReturnState = US_INVALID_READING ;

	// Front
	LOC_eReturnState = APPC1_SelectUltrasonc(FrontUS, &data);
	if(LOC_eReturnState != US_VALID_READING)
	{
		return LOC_eReturnState;
	}
	pArr[FrontUS] = data ;
	data = 0 ;

	// Back
	LOC_eReturnState = APPC1_SelectUltrasonc(BackUS, &data);
	if(LOC_eReturnState != US_VALID_READING)
	{
		return LOC_eReturnState;
	}
	pArr[BackUS] = data ;
	data = 0 ;

	// Front Right
	LOC_eReturnState= APPC1_SelectUltrasonc(FrontRightUS, &data);
	if(LOC_eReturnState != US_VALID_READING)
	{
		return LOC_eReturnState;
	}
	pArr[FrontRightUS] = data ;
	data = 0 ;

	// Back Right
	LOC_eReturnState = APPC1_SelectUltrasonc(RearRightUS, &data);
	if(LOC_eReturnState != US_VALID_READING)
	{
		return LOC_eReturnState;
	}
	pArr[RearRightUS] = data ;
	data = 0 ;

	return LOC_eReturnState;
}

ERROR_t C4_StaticGetFourDistance(u16 *FD , u16 *BD , u16 *FRD , u16 *BRD)
{
    US_ERROR_t LOC_xErrorTracing = 0 ;
    ERROR_t LOC_xReturnError = E_OK ;
    u8 LOC_u8ErrorCounter = 0 ;
    if(FD != NULL )
    {
        // Front Distance
        LOC_xErrorTracing = APPC1_SelectUltrasonc(FrontUS,FD);
        while (LOC_xErrorTracing != US_VALID_READING)
        {
            LOC_u8ErrorCounter++ ;
            LOC_xErrorTracing = APPC1_SelectUltrasonc(FrontUS,FD);
            if(LOC_u8ErrorCounter > C4_MAX_ERROR_LOGGING)
            {
                LOC_xReturnError = ERR_FRONT_US_FAILED ;
                return LOC_xReturnError ;
            }
        }
        LOC_u8ErrorCounter = 0 ;
    }

    if(BD != NULL)
    {
        // Back
        LOC_xErrorTracing = APPC1_SelectUltrasonc(BackUS,BD);
        while (LOC_xErrorTracing != US_VALID_READING)
        {
            LOC_u8ErrorCounter++ ;
            LOC_xErrorTracing = APPC1_SelectUltrasonc(BackUS,BD);
            if(LOC_u8ErrorCounter > C4_MAX_ERROR_LOGGING)
            {
                LOC_xReturnError = ERR_BACK_US_FAILED ;
                return LOC_xReturnError ;
            }
        }
        LOC_u8ErrorCounter = 0 ;
    }

    if(FRD != NULL)
    {
        // Front Right
        LOC_xErrorTracing = APPC1_SelectUltrasonc(FrontRightUS,FRD);
        while (LOC_xErrorTracing != US_VALID_READING)
        {
            LOC_u8ErrorCounter++ ;
            LOC_xErrorTracing = APPC1_SelectUltrasonc(FrontRightUS,FRD);
            if(LOC_u8ErrorCounter > C4_MAX_ERROR_LOGGING)
            {
                LOC_xReturnError = ERR_FRONT_RIGHT_US_FAILED ;
                return LOC_xReturnError ;
            }
        }
        LOC_u8ErrorCounter = 0 ;
    }

    if(BRD != NULL)
    {
        // Rear Right
    	LOC_xErrorTracing = APPC1_SelectUltrasonc(RearRightUS,BRD);
        while (LOC_xErrorTracing != US_VALID_READING)
        {
            LOC_u8ErrorCounter++ ;
            LOC_xErrorTracing = APPC1_SelectUltrasonc(RearRightUS,BRD);
            if(LOC_u8ErrorCounter > C4_MAX_ERROR_LOGGING)
            {
                LOC_xReturnError = ERR_REAR_RIGHT_US_FAILED ;
                return LOC_xReturnError ;
            }
        }
        LOC_u8ErrorCounter = 0 ;
    }
    return LOC_xReturnError;
}



/************************************* End of File ******************************************/
