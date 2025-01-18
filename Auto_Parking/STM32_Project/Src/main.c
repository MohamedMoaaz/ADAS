/**
 ******************************************************************************
 * @file           : main.c
 * @author         : NTI-Team 3
 *					 Team Members
 *					 - Eslam El-Sayed Refeat
 *					 - Mohamed Abd El-Naby Mohamed
 *					 - Rana Abd El-Salam Mohamed
 *					 - Salma Mohamed Hashim
 *					 - Shaimaa Mahmoud Samir
 *					 - Sherif Atef Sedek
 *					 - Youssef Ahmed Mohamed
 * @brief          : This Program for Auto parking/Find Slot/Vehicle to Traffic Light applications
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) NTI-Team 3.
 * All rights reserved.</center></h2>
 *
 ******************************************************************************
 */



/************************************ Includes ****************************************/
#include "RCC_interface.h"
#include "C1_US_SLCT.h"
#include "C2_VCLE_CNTRL.h"
#include "C3_VCLE_ALIGN.h"
#include "C4_SLOT_FIND.h"
#include "C5_PARKING/C5_PARKING.h"
#include "SYS_DIG_MNG.h"
#include "main.h"
#include "SW_Delay.h"
#include "APP/APP1_UsrControlled/APP1_UsrControlled.h"
#include "C6_TrafficLightV2I/C6_TrafficLight_V2I.h"

/**
 * This Macros is used to
 * 							MAIN_CODE : Enable Main App
 * 							TESTING_PHASE : Starting With Parking
 */
#define TESTING_PHASE	0
#define MAIN_CODE		1

/**
 * For Componant Test
 */
#define PWM_TEST		0
#define STEERING_TST	0

#define NUM_OF_US_TEST_BEG	3
FORCE_INLINE boolean APP_boolCheckUltrasonics(void)
{

	ERROR_t LOC_eReturnState = E_OK ;
	u8 LOC_u8NumberOfTests =  NUM_OF_US_TEST_BEG;
	u16 dataf = 0 , datab = 0 ,dataFR = 0 , dataBR = 0  ;
	while (LOC_u8NumberOfTests)
	{
		LOC_eReturnState = C4_StaticGetFourDistance(&dataf, &datab, &dataFR, &dataBR);
		if(LOC_eReturnState != E_OK)
		{
			LOG_ERROR(LOC_eReturnState);
			return FALSE ;
		}
		else
		{
			LOC_u8NumberOfTests-- ;
		}
	}
	return TRUE ;
}

int main(void)
{

	/*
	 * Local Variables
	 */
	ERROR_t    LOC_eReturnForSystemLog = 0 ;
#if TESTING_PHASE == 1 && MAIN_CODE == 0
	VehicleStates_t LOC_xSystemState = PARKING_MODE ;
#else
	VehicleStates_t LOC_xSystemState = USR_CONTROLLED ;
#endif




    /* Clock Initialization
     * System Clock : SYSCLK	 = 8 MHz
     * AHB    Clock : HCLK	     = 8 MHz
     * APB1   Clock : APB1CLK    = 8 MHz
     * APB2   Clock : APB2CLK    = 8 MHz
     */
	RCC_voidInitSysClocks();

	/*
	 * Services Component Initialization
	 *	C1_US_SLCT          : Used to Select One of Vehicle Ultrasonic
	 *  C2_VCLE_CNTRL		: Used to Control Vehicle Directions
	 *  C3_VCLE_ALIGN		: Used to Check Vehicle Alignment
	 *  C4_SLOT_FIND		: Used to Find Slot
	 *
	 *  SYS_DIG_Mng			: Used to log Errors
	 *
	 */
	C2VCONTROL_voidInit();
	C4SLTFIND_voidInit();
	DIGMngr_voidInit();
	C5VCLEPRK_voidInitParking();
	C6TL_voidTrafficV2I_init();
	delay_init();


	/*
	 * APP Component Initialization
	 *	APP1_UsrControllerd           : For Free Running Mode
	 */
	APP1_voidSetup();

	// Check Ultrasonics
	u8 LOC_u8SystemCheck = APP_boolCheckUltrasonics();
	while (LOC_u8SystemCheck != TRUE)
	{
		LOC_u8SystemCheck = APP_boolCheckUltrasonics();
	}

	for(;;)
	{
#if MAIN_CODE == 1 && PWM_TEST == 0 && STEERING_TST == 0
		switch (LOC_xSystemState) {
			case USR_CONTROLLED:
				APP1_voidControlVehcileThroughBTL(&LOC_xSystemState);
				break;
			case PARKING_MODE :
				LOC_eReturnForSystemLog = C4SLTFIND_voidSearchingforSlot();
				if (LOC_eReturnForSystemLog != E_OK )
				{
					LOG_ERROR(LOC_eReturnForSystemLog);
				}
				else if (LOC_eReturnForSystemLog == E_OK)
				{
					delay_ms(700);
					LOC_eReturnForSystemLog = C5VCLEPRK_voidStartParking();
				}
				LOC_xSystemState = USR_CONTROLLED ;
				break ;
			case TF_START_V2I :
				/*	That Handled Automatically in state of USR_CONTROLLED but can be enable automatically by driver */ 
				C6TL_voidStartV2I(&LOC_xSystemState);
				break ;
			default:
				break;
		}
#endif

#if MAIN_CODE == 1 && PWM_TEST == 1 && STEERING_TST == 0
		int i = 5 ;
		// Work Motors
    	C2VCONTROL_voidChangeDirection(VCLE_FWD, 255);

    	// Get Ultrasonic Work While Motor is Running
    	while(i)
    	{
        	APP_boolCheckUltrasonics();
        	i-- ;
    	}
    	i = 5 ;
#endif
#if MAIN_CODE == 0 && PWM_TEST == 0 && STEERING_TST == 1
    	// Goes Right First
    	C2VCONTROL_voidChangeDirection(VCLE_LEFT_FWD, 255);
//    	C2VCONTROL_voidChangeDirection(VCLE_FWD, 255);

    	// Stop
    	C2VCONTROL_voidChangeDirection(VCLE_STOP, 0);

    	// FWD Right Direct
    	C2VCONTROL_voidChangeDirection(VCLE_FWD, 255);
#endif
	}
}
