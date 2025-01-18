/**
* @file US.c
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
#include "BIT_MATH.h"
#include "RCC/RCC_interface.h"
#include "NVIC/nvic.h"
#include "GPIO/GPIO_interface.h"
#include "ICU/ICU_interface.h"
#include "US.h"
#include "SW_Delay.h"




/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
static ICU_Config_t Global_ICU_TIMx ; 
static Ultrasonic_Cfg *Global_US_Config[4][4] ;
static u8 Is_Timer_Busy[4] ; 


/******************************************************************************
* Module Preprocessor Variable 
*******************************************************************************/




/******************************************************************************
* Typedefs
*******************************************************************************/




/******************************************************************************
* Module Private Functions 
*******************************************************************************/
static void ICU_TIM2_EdgeCallback(u32 Counts)
{
    /************** LOCAL Variables **********************/ 
    static u32 IC_Val1 = 0;
    static u32 IC_Val2 = 0;
    static u32 Difference = 0;
    static u8 Is_First_Captured = 0;
    u8 Distance  = 0;
    if (Is_First_Captured==0) // if the first value is not captured
    {
        IC_Val1 = Counts; // read the first value
        IC_Val2= 0 ;
        Is_First_Captured = 1;  // set the first captured as true
        Is_Timer_Busy[2] = 1 ;
    }
    else if (Is_First_Captured==1)   // if the first is already captured
    {
        IC_Val2 = Counts;  // read second value
        /*  Reset The Counter   */
        if (IC_Val2 > IC_Val1)
        {
            Difference = IC_Val2-IC_Val1;
        }

        else if (IC_Val1 > IC_Val2)
        {
            Difference = (Global_ICU_TIMx.ICU_Max_Counting - IC_Val1) + IC_Val2;
        }
       // Distance = (Difference * (0.034/2.0));
        Distance = ((Difference * 0.017) / (8)) + FIXED_US_ERROR_IN_CM;

        Is_First_Captured = 0; // set it back to false
        IC_Val1 = 0 ;
        IC_Val2 = 0 ;
        //	Timer Channel 2 3
        Global_US_Config[2][2]->p2Function(Distance);
        ICU_voidResetTimer(&Global_ICU_TIMx);
        // Interrupt will be disabled
        ICU_voidDisableChannelIRQ(&Global_ICU_TIMx, CHANNEL_3);
        Is_Timer_Busy[2] = 0 ; 
    }

}



/******************************************************************************
* Function Prototypes
*******************************************************************************/
FORCE_INLINE void TrigUltrasonic(u8 copy_u8TrigPort , Pin_t copy_u8Pin)
{
    GPIO_voidSetPinValue(copy_u8TrigPort, copy_u8Pin , HIGH);
    delay_us(10);
    GPIO_voidSetPinValue(copy_u8TrigPort, copy_u8Pin , LOW);
}

/******************************************************************************
* Function Definitions
*******************************************************************************/

void US_voidInit(Ultrasonic_Cfg *p2UserConfig)
{
    // Only Timer 2 Supported 
    if(p2UserConfig->Timerx == Timer2)
    {
        /*          RCC Init        */
        #if NUXED_US_ENABLE == 1 
        for (u8 LOC_u8Counter = 0; LOC_u8Counter < US_NUMBER; LOC_u8Counter++)
        {
            RCC_voidEnableClock(RCC_AHB, p2UserConfig->Trig_Port[LOC_u8Counter]);
            GPIO_voidSetPinDirection(p2UserConfig->Trig_Port[LOC_u8Counter],p2UserConfig->Trig_Pin[LOC_u8Counter], GPIO_OUTPUT_HIGH_SPD_PUSH_PULL);
            GPIO_voidSetPinValue(p2UserConfig->Trig_Port[LOC_u8Counter],p2UserConfig->Trig_Pin[LOC_u8Counter], LOW);

        }
        #else 
        // Trig Pin
        RCC_voidEnableClock(RCC_AHB, p2UserConfig->Trig_Port);
        /*          Trig Port as Output     */ 
        GPIO_voidSetPinDirection(p2UserConfig->Trig_Port,p2UserConfig->Trig_Pin, GPIO_OUTPUT_HIGH_SPD_PUSH_PULL);
        #endif 
        // PWM Init
        Global_ICU_TIMx.Timerx = Timer2 ;
        Global_ICU_TIMx.ICU_u16Prescaler = 0 ;
        Global_ICU_TIMx.ICU_Max_Counting = 0xFFFFFFFF ;
        // Channel Related 
        if(p2UserConfig->CHANNEL_x == CHANNEL_3)
        {
            // Echo Pin
            RCC_voidEnableClock(RCC_APB1, Timer2);	/*	TIMER2	*/
            /*          AFIOs                   */
            // Configure PB10 alternate function
            GPIO_voidSetPinDirection(PORTB	, PIN10, GPIO_AF_HIGH_SPD);
            GPIO_voidSetAFIO(PORTB	, PIN10, AFIO_1);	//TIM2CH3

            /*      Inits       */
            Global_ICU_TIMx.ICU_CAPTURE_x_EDGE[CHANNEL_3] = ICU_CAPTURE_BOTH_EDGE ;
            if(p2UserConfig->US_x == US_IRQs && p2UserConfig->p2Function != NULL)
            {
                Global_ICU_TIMx.ICU_CHECK_MECHNSIM_x[CHANNEL_3] = ICU_CHECK_MECHNSIM_IRQs ;
                ICU_voidGetCapturedValueAsynch(&Global_ICU_TIMx, CHANNEL_3, ICU_TIM2_EdgeCallback);
                /******************************** ICU NVIC	**********************************************/
                nvic_enableInterrupt(28);
            }
            else 
                Global_ICU_TIMx.ICU_CHECK_MECHNSIM_x[CHANNEL_3] = ICU_CHECK_MECHNSIM_POLLING ;

        }
    	ICU_voidInit(&Global_ICU_TIMx);
    	// For Channel 3 Only
        ICU_voidDisableChannelIRQ(&Global_ICU_TIMx, CHANNEL_3);

    	Global_US_Config[2][p2UserConfig->CHANNEL_x] = p2UserConfig ;

    }
}

US_ERROR_t US_voidGetDistanceSynch(Ultrasonic_Cfg *p2UserConfig , u16* pData_DistanceInCM,u8 copy_u8UltrasonicIndex)
{
     u32 IC_Val1 = 0;
     u32 IC_Val2 = 0;
     u32 Difference = 0;
     u16 Distance ;
     ICU_Error_t LOC_eICU_Signal1_State = ICU_OK ;
     ICU_Error_t LOC_eICU_Signal2_State = ICU_OK ;
     US_ERROR_t LOC_eReturnState = US_INVALID_READING ;

     volatile u32 LOC_u32Counter = 0 ;
    if(p2UserConfig->Timerx == Timer2)
    {
        if(Is_Timer_Busy[2] == 0)
        {
            // Trig Pin
            TrigUltrasonic( p2UserConfig->Trig_Port[copy_u8UltrasonicIndex],p2UserConfig->Trig_Pin[copy_u8UltrasonicIndex]) ;

            LOC_eICU_Signal1_State = ICU_voidGetCapturedValueSynch(&Global_ICU_TIMx, CHANNEL_3, &IC_Val1);
            LOC_eICU_Signal2_State = ICU_voidGetCapturedValueSynch(&Global_ICU_TIMx, CHANNEL_3, &IC_Val2);
            if(LOC_eICU_Signal1_State == ICU_OK && LOC_eICU_Signal2_State == ICU_OK)
            {
            	/*	Set it as valid Reading	*/
            	LOC_eReturnState = US_VALID_READING;
                /*  Reset The Counter   */
                if (IC_Val2 > IC_Val1)
                {
                    Difference = IC_Val2-IC_Val1;
                }

                else if (IC_Val1 > IC_Val2)
                {
                    Difference = (Global_ICU_TIMx.ICU_Max_Counting - IC_Val1) + IC_Val2;
                }
                // Tick Time = 0.25 ;
                // 	DISTANCE(M) = (DIFF * 0.017)/(TIM_CLK_MHz/(PS+1));
                Distance = (Difference * 0.017) / (8);
               // Distance = (Difference * (0.017));
                *pData_DistanceInCM = (Distance+FIXED_US_ERROR_IN_CM) ;
                ICU_voidResetTimer(&Global_ICU_TIMx);
            	for(LOC_u32Counter=0 ; LOC_u32Counter < DELAYS_BETWEEN_READINGS_IN_TERMS_OF_COUNTS ;LOC_u32Counter++)
            	{
            		__asm("NOP");

            	}

            }
            else
            {
            	LOC_eReturnState = US_INVALID_READING ;
            }
        }
    }
    return LOC_eReturnState ;
}
void US_voidGetDistanceAsynch(Ultrasonic_Cfg *p2UserConfig , u8 copy_u8UltrasonicIndex)
{
   // Enable Timer  
    // Only Timer 2 Supported 
    if(p2UserConfig->Timerx == Timer2)
    {
        if(Is_Timer_Busy[2] == 0)
        {
            // Trig Pin
            TrigUltrasonic( p2UserConfig->Trig_Port[copy_u8UltrasonicIndex],p2UserConfig->Trig_Pin[copy_u8UltrasonicIndex]) ; 
            // Enable IRQ 
            ICU_voidEnableChannelIRQ(&Global_ICU_TIMx, CHANNEL_3);
            Is_Timer_Busy[2] = 1 ; 
        }
    }
}
/************************************* End of File ******************************************/
