/**
* @file ICU_program.c
* @author Mohamed Abd El-Naby (mahameda.naby@gmail.com) 
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
#include "UTILS.h"
#include "ICU_interface.h"
#include "ICU_config.h"
#include "TIM_private.h"










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
void (*GlobalP2F_TIM2[4])(u32 CurrentCounts) ;
void (*GlobalP2F_TIM4[4])(u32 CurrentCounts) ;
void (*GlobalP2F_TIM17[4])(u32 CurrentCounts) ;




/******************************************************************************
* Function Prototypes
*******************************************************************************/




/******************************************************************************
* Function Definitions
*******************************************************************************/

void ICU_voidInit(ICU_Config_t * p_userConfig)
{
    // Checking which Timer Used 
    if(p_userConfig->Timerx == Timer2)
    {
        // Prescaler 
        TIM2->PSC = p_userConfig->ICU_u16Prescaler ; 
        TIM2->ARR = p_userConfig->ICU_Max_Counting ;
        for (u8 LOC_u8Counter = 0; LOC_u8Counter < 4; LOC_u8Counter++)
        {
        if(p_userConfig->ICU_CAPTURE_x_EDGE[LOC_u8Counter] != ICU_NOT_USED || p_userConfig->ICU_CHECK_MECHNSIM_x[LOC_u8Counter] != ICU_NOT_USED)
        {
          if(LOC_u8Counter == 0)
          {
            /**************************************  Channel Mapping to T1  *************************************/
            TIM2->CCMR1 |= (0b01<<0) ;                  //CC1 channel is configured as input, IC1 is mapped on TI1
            /*************************************** Select Mechanism   ******************************************/
            if(p_userConfig->ICU_CHECK_MECHNSIM_x[LOC_u8Counter] == ICU_CHECK_MECHNSIM_POLLING)
            {
                // Polling
                TIM2->DIER &= ~(1<< DIER_CC1IE) ; 
                TIM2->DIER &= ~(1<< DIER_CC1DE) ; 
            }
            else if (p_userConfig->ICU_CHECK_MECHNSIM_x[LOC_u8Counter] == ICU_CHECK_MECHNSIM_IRQs)
            {
                // IRQ
                TIM2->DIER |= (1<< DIER_CC1IE) ; 
                TIM2->DIER &= ~(1<< DIER_CC1DE) ; 
            }
            else 
            {
                // DMA
                TIM2->DIER &= ~(1<< DIER_CC1IE) ; 
                TIM2->DIER |=  (1<< DIER_CC1DE) ; 
            }

            /*************************************** Select Edge   ******************************************/
            if(p_userConfig->ICU_CAPTURE_x_EDGE[LOC_u8Counter] == ICU_CAPTURE_RISING_EDGE)
            {
                // Rising   CC1NP/CC1P 0b00
                TIM2->CCER &= ~(1<<CCER_CC1NP);
                TIM2->CCER &= ~(1<<CCER_CC1P);
            }
            else if (p_userConfig->ICU_CAPTURE_x_EDGE[LOC_u8Counter] == ICU_CAPTURE_FALLING_EDGE)
            {
                // Falling  0b01
                TIM2->CCER &= ~(1<<CCER_CC1NP);
                TIM2->CCER |=  (1<<CCER_CC1P);
            }
            else 
            {
                // Both Edges 0b11
                TIM2->CCER |=  (1<<CCER_CC1NP);
                TIM2->CCER |=  (1<<CCER_CC1P);
            }
            /************************************ Channel Enable    ********************************************/
            TIM2->CCER |= (1<< CCER_CC1E); 
          }
          else if (LOC_u8Counter == 1)
          {
            /**************************************  Channel Mapping to T1  *************************************/
            TIM2->CCMR1 |= (0b01<<8) ;                  //CC2 channel is configured as input, IC1 is mapped on TI1
            
            /*************************************** Select Mechanism   ******************************************/
            if(p_userConfig->ICU_CHECK_MECHNSIM_x[LOC_u8Counter] == ICU_CHECK_MECHNSIM_POLLING)
            {
                // Polling
                TIM2->DIER &= ~(1<< DIER_CC2IE) ; 
                TIM2->DIER &= ~(1<< DIER_CC2DE) ; 
            }
            else if (p_userConfig->ICU_CHECK_MECHNSIM_x[LOC_u8Counter] == ICU_CHECK_MECHNSIM_IRQs)
            {
                // IRQ
                TIM2->DIER |= (1<< DIER_CC2IE) ; 
                TIM2->DIER &= ~(1<< DIER_CC2DE) ; 
            }
            else 
            {
                // DMA
                TIM2->DIER &= ~(1<< DIER_CC2IE) ; 
                TIM2->DIER |=  (1<< DIER_CC2DE) ; 
            }
            /*************************************** Select Edge   ******************************************/
            if(p_userConfig->ICU_CAPTURE_x_EDGE[LOC_u8Counter] == ICU_CAPTURE_RISING_EDGE)
            {
                // Rising   CC1NP/CC1P 0b00
                TIM2->CCER &= ~(1<<CCER_CC2NP);
                TIM2->CCER &= ~(1<<CCER_CC2P);
            }
            else if (p_userConfig->ICU_CAPTURE_x_EDGE[LOC_u8Counter] == ICU_CAPTURE_FALLING_EDGE)
            {
                // Falling  0b01
                TIM2->CCER &= ~(1<<CCER_CC2NP);
                TIM2->CCER |=  (1<<CCER_CC2P);
            }
            else 
            {
                // Both Edges 0b11
                TIM2->CCER |=  (1<<CCER_CC2NP);
                TIM2->CCER |=  (1<<CCER_CC2P);
            }
            /************************************ Channel Enable    ********************************************/
            TIM2->CCER |= (1<< CCER_CC2E);            

          }
          else if (LOC_u8Counter == 2)
          {
            /**************************************  Channel Mapping to T1  *************************************/
            TIM2->CCMR2 |= (0b01<<0) ;                  //CC3 channel is configured as input, IC1 is mapped on TI1

            /*************************************** Select Mechanism   ******************************************/
            if(p_userConfig->ICU_CHECK_MECHNSIM_x[LOC_u8Counter] == ICU_CHECK_MECHNSIM_POLLING)
            {
                // Polling
                TIM2->DIER &= ~(1<< DIER_CC3IE) ; 
                TIM2->DIER &= ~(1<< DIER_CC3DE) ; 
            }
            else if (p_userConfig->ICU_CHECK_MECHNSIM_x[LOC_u8Counter] == ICU_CHECK_MECHNSIM_IRQs)
            {
                // IRQ
                TIM2->DIER |= (1<< DIER_CC3IE) ; 
                TIM2->DIER &= ~(1<< DIER_CC3DE) ; 
            }
            else 
            {
                // DMA
                TIM2->DIER &= ~(1<< DIER_CC3IE) ; 
                TIM2->DIER |=  (1<< DIER_CC3DE) ; 
            }
            /*************************************** Select Edge   ******************************************/
            if(p_userConfig->ICU_CAPTURE_x_EDGE[LOC_u8Counter] == ICU_CAPTURE_RISING_EDGE)
            {
                // Rising   CC1NP/CC1P 0b00
                TIM2->CCER &= ~(1<<CCER_CC3NP);
                TIM2->CCER &= ~(1<<CCER_CC3P);
            }
            else if (p_userConfig->ICU_CAPTURE_x_EDGE[LOC_u8Counter] == ICU_CAPTURE_FALLING_EDGE)
            {
                // Falling  0b01
                TIM2->CCER &= ~(1<<CCER_CC3NP);
                TIM2->CCER |=  (1<<CCER_CC3P);
            }
            else 
            {
                // Both Edges 0b11
                TIM2->CCER |=  (1<<CCER_CC3NP);
                TIM2->CCER |=  (1<<CCER_CC3P);
            }
            /************************************ Channel Enable    ********************************************/
            TIM2->CCER |= (1<< CCER_CC3E); 
          }
          else if (LOC_u8Counter == 3)
          {
            /**************************************  Channel Mapping to T1  *************************************/
            TIM2->CCMR2 |= (0b01<<8) ;                  //CC4 channel is configured as input, IC1 is mapped on TI1

            /*************************************** Select Mechanism   ******************************************/
            if(p_userConfig->ICU_CHECK_MECHNSIM_x[LOC_u8Counter] == ICU_CHECK_MECHNSIM_POLLING)
            {
                // Polling
                TIM2->DIER &= ~(1<< DIER_CC4IE) ; 
                TIM2->DIER &= ~(1<< DIER_CC4DE) ; 
            }
            else if (p_userConfig->ICU_CHECK_MECHNSIM_x[LOC_u8Counter] == ICU_CHECK_MECHNSIM_IRQs)
            {
                // IRQ
                TIM2->DIER |= (1<< DIER_CC4IE) ; 
                TIM2->DIER &= ~(1<< DIER_CC4DE) ; 
            }
            else 
            {
                // DMA
                TIM2->DIER &= ~(1<< DIER_CC4IE) ; 
                TIM2->DIER |=  (1<< DIER_CC4DE) ; 
            }
            /*************************************** Select Edge   ******************************************/
            if(p_userConfig->ICU_CAPTURE_x_EDGE[LOC_u8Counter] == ICU_CAPTURE_RISING_EDGE)
            {
                // Rising   CC1NP/CC1P 0b00
                TIM2->CCER &= ~(1<<CCER_CC4NP);
                TIM2->CCER &= ~(1<<CCER_CC4P);
            }
            else if (p_userConfig->ICU_CAPTURE_x_EDGE[LOC_u8Counter] == ICU_CAPTURE_FALLING_EDGE)
            {
                // Falling  0b01
                TIM2->CCER &= ~(1<<CCER_CC4NP);
                TIM2->CCER |=  (1<<CCER_CC4P);
            }
            else 
            {
                // Both Edges 0b11
                TIM2->CCER |=  (1<<CCER_CC4NP);
                TIM2->CCER |=  (1<<CCER_CC4P);
            }
            /************************************ Channel Enable    ********************************************/
            TIM2->CCER |= (1<< CCER_CC4E); 

          }
        }
      }  
    TIM2->SR |= (1<<0);
    // Enable Timer 
    TIM2->CR1 |= (1<< CR1_CEN);        

    }
    // Checking which Timer Used 
    else if(p_userConfig->Timerx == Timer4)
    {
        // Prescaler 
        TIM4->PSC = p_userConfig->ICU_u16Prescaler ; 
        TIM4->ARR = p_userConfig->ICU_Max_Counting ;
        for (u8 LOC_u8Counter = 0; LOC_u8Counter < 4; LOC_u8Counter++)
        {
        if(p_userConfig->ICU_CAPTURE_x_EDGE[LOC_u8Counter] != ICU_NOT_USED || p_userConfig->ICU_CHECK_MECHNSIM_x[LOC_u8Counter] != ICU_NOT_USED)
        {
          if(LOC_u8Counter == 0)
          {
            /**************************************  Channel Mapping to T1  *************************************/
            TIM4->CCMR1 |= (0b01<<0) ;                  //CC1 channel is configured as input, IC1 is mapped on TI1
            /*************************************** Select Mechanism   ******************************************/
            if(p_userConfig->ICU_CHECK_MECHNSIM_x[LOC_u8Counter] == ICU_CHECK_MECHNSIM_POLLING)
            {
                // Polling
                TIM4->DIER &= ~(1<< DIER_CC1IE) ; 
                TIM4->DIER &= ~(1<< DIER_CC1DE) ; 
            }
            else if (p_userConfig->ICU_CHECK_MECHNSIM_x[LOC_u8Counter] == ICU_CHECK_MECHNSIM_IRQs)
            {
                // IRQ
                TIM4->DIER |= (1<< DIER_CC1IE) ; 
                TIM4->DIER &= ~(1<< DIER_CC1DE) ; 
            }
            else 
            {
                // DMA
                TIM4->DIER &= ~(1<< DIER_CC1IE) ; 
                TIM4->DIER |=  (1<< DIER_CC1DE) ; 
            }

            /*************************************** Select Edge   ******************************************/
            if(p_userConfig->ICU_CAPTURE_x_EDGE[LOC_u8Counter] == ICU_CAPTURE_RISING_EDGE)
            {
                // Rising   CC1NP/CC1P 0b00
                TIM4->CCER &= ~(1<<CCER_CC1NP);
                TIM4->CCER &= ~(1<<CCER_CC1P);
            }
            else if (p_userConfig->ICU_CAPTURE_x_EDGE[LOC_u8Counter] == ICU_CAPTURE_FALLING_EDGE)
            {
                // Falling  0b01
                TIM4->CCER &= ~(1<<CCER_CC1NP);
                TIM4->CCER |=  (1<<CCER_CC1P);
            }
            else 
            {
                // Both Edges 0b11
                TIM4->CCER |=  (1<<CCER_CC1NP);
                TIM4->CCER |=  (1<<CCER_CC1P);
            }
            /************************************ Channel Enable    ********************************************/
            TIM4->CCER |= (1<< CCER_CC1E); 
          }
        }
      }  
    TIM4->SR |= (1<<0);
    // Enable Timer 
    TIM4->CR1 |= (1<< CR1_CEN);        
    }
    // Checking which Timer Used 
    else if(p_userConfig->Timerx == Timer17)
    {
        // Prescaler 
        TIM17->PSC = p_userConfig->ICU_u16Prescaler ; 
        TIM17->ARR = p_userConfig->ICU_Max_Counting ;
        for (u8 LOC_u8Counter = 0; LOC_u8Counter < 4; LOC_u8Counter++)
        {
        if(p_userConfig->ICU_CAPTURE_x_EDGE[LOC_u8Counter] != ICU_NOT_USED || p_userConfig->ICU_CHECK_MECHNSIM_x[LOC_u8Counter] != ICU_NOT_USED)
        {
          if(LOC_u8Counter == 0)
          {
            /**************************************  Channel Mapping to T1  *************************************/
            TIM17->CCMR1 |= (0b01<<0) ;                  //CC1 channel is configured as input, IC1 is mapped on TI1
            /*************************************** Select Mechanism   ******************************************/
            if(p_userConfig->ICU_CHECK_MECHNSIM_x[LOC_u8Counter] == ICU_CHECK_MECHNSIM_POLLING)
            {
                // Polling
                TIM17->DIER &= ~(1<< DIER_CC1IE) ; 
                TIM17->DIER &= ~(1<< DIER_CC1DE) ; 
            }
            else if (p_userConfig->ICU_CHECK_MECHNSIM_x[LOC_u8Counter] == ICU_CHECK_MECHNSIM_IRQs)
            {
                // IRQ
                TIM17->DIER |= (1<< DIER_CC1IE) ; 
                TIM17->DIER &= ~(1<< DIER_CC1DE) ; 
            }
            else 
            {
                // DMA
                TIM17->DIER &= ~(1<< DIER_CC1IE) ; 
                TIM17->DIER |=  (1<< DIER_CC1DE) ; 
            }

            /*************************************** Select Edge   ******************************************/
            if(p_userConfig->ICU_CAPTURE_x_EDGE[LOC_u8Counter] == ICU_CAPTURE_RISING_EDGE)
            {
                // Rising   CC1NP/CC1P 0b00
                TIM17->CCER &= ~(1<<CCER_CC1NP);
                TIM17->CCER &= ~(1<<CCER_CC1P);
            }
            else if (p_userConfig->ICU_CAPTURE_x_EDGE[LOC_u8Counter] == ICU_CAPTURE_FALLING_EDGE)
            {
                // Falling  0b01
                TIM17->CCER &= ~(1<<CCER_CC1NP);
                TIM17->CCER |=  (1<<CCER_CC1P);
            }
            else 
            {
                // Both Edges 0b11
                TIM17->CCER |=  (1<<CCER_CC1NP);
                TIM17->CCER |=  (1<<CCER_CC1P);
            }
            /************************************ Channel Enable    ********************************************/
            TIM17->CCER |= (1<< CCER_CC1E); 
          }
        }
      }  
    TIM17->SR |= (1<<0);
    // Enable Timer 
    TIM17->CR1 |= (1<< CR1_CEN);        
    }  
}

ICU_Error_t ICU_voidGetCapturedValueSynch(ICU_Config_t * p_userConfig , Channel_ID_t CHANNEL_x , u32 *ptr_u32CapturedValue)
{

#define FLAG_DETECTED (( TIM2->SR & ( 1<< ( CHANNEL_x+1 ) ) ) )
#define OVC_DTECTED	(( TIM2->SR & ( 1<< ( CHANNEL_x+9 ) ) ) )
#define PREDEFINED_TIMOUT	480000	// 60 ms
#define CHECK_TIMOUT	(LOC_u32TimeoutCounter > PREDEFINED_TIMOUT)
	ICU_Error_t LOC_eReturnError = ICU_OK ;
	u8 LOC_u8IsOvercapturedDetected = 0 ;
	u32 LOC_u32TimeoutCounter = 0 ;
    // Check Timer
    if(p_userConfig->Timerx == Timer2)
    {
    //		 ( ! ( ( FLAG == 0) || (OVC ==0) ) && !(TIMOUT > PRD)
       while ((! ( FLAG_DETECTED || LOC_u8IsOvercapturedDetected)) && !CHECK_TIMOUT)
        {
            // Wait for the capture flag to be set
        	LOC_u8IsOvercapturedDetected = OVC_DTECTED ;
        	LOC_u32TimeoutCounter++;
        }
        if(LOC_u8IsOvercapturedDetected == 0 && !CHECK_TIMOUT)
        {
            *ptr_u32CapturedValue = TIM2->CCRx[CHANNEL_x]    ;
        }
        else
        {
        	if(LOC_u8IsOvercapturedDetected == 1)
        		LOC_eReturnError = ICU_OVER_CAPTURED ;
        	else if (CHECK_TIMOUT)
        	{
        		LOC_eReturnError = ICU_TIME_OUT ;
        	}
        	else
        	{
        		LOC_eReturnError = ICU_UNKOWN_ERR ;
        	}
        }
    }
    else if(p_userConfig->Timerx == Timer4)
    {
        while (! ( TIM4->SR & ( 1<< ( CHANNEL_x+1 ) ) ) )
        {
            // Wait for the capture flag to be set
        }
        *ptr_u32CapturedValue = TIM4->CCRx[CHANNEL_x]    ;
    }
    else if(p_userConfig->Timerx == Timer17)
    {
        while (! ( TIM17->SR & ( 1<< ( CHANNEL_x+1 ) ) ) )
        {
            // Wait for the capture flag to be set
        }
        *ptr_u32CapturedValue = TIM17->CCRx[CHANNEL_x]    ;
    }
    return LOC_eReturnError ;
}

void ICU_voidGetCapturedValueAsynch(ICU_Config_t * p_userConfig , Channel_ID_t CHANNEL_x , void (*pCallback)(u32 CurrentCounts) )
{
    // Check Timer
    if(p_userConfig->Timerx == Timer2)
    {
    	GlobalP2F_TIM2[CHANNEL_x] = pCallback ;
    }
    else if(p_userConfig->Timerx == Timer4)
    {
    	GlobalP2F_TIM4[CHANNEL_x] = pCallback ;
    }
    else if(p_userConfig->Timerx == Timer17)
    {
    	GlobalP2F_TIM17[CHANNEL_x] = pCallback ;
    }
}

void ICU_voidChangeCaptureEdge(ICU_Config_t * p_userConfig , Channel_ID_t CHANNEL_x ,ICU_CapturingEdges_t ICU_CAPTURE_x_EDGE )
{
    if(p_userConfig->Timerx == Timer2)
    {
    	if(CHANNEL_x == 0)
    	{
            TIM2->DIER &= ~(1<< DIER_CC1IE) ;
            TIM2->DIER &= ~(1<< DIER_CC1DE) ;

            /*************************************** Select Mechanism   ******************************************/
            if(ICU_CAPTURE_x_EDGE == (ICU_CapturingEdges_t)ICU_CHECK_MECHNSIM_POLLING)
            {
                // Polling
                TIM2->DIER &= ~(1<< DIER_CC1IE) ;
                TIM2->DIER &= ~(1<< DIER_CC1DE) ;
            }
            else if (ICU_CAPTURE_x_EDGE == (ICU_CapturingEdges_t)ICU_CHECK_MECHNSIM_IRQs)
            {
                // IRQ
                TIM2->DIER |= (1<< DIER_CC1IE) ;
                TIM2->DIER &= ~(1<< DIER_CC1DE) ;
            }
            else
            {
                // DMA
                TIM2->DIER &= ~(1<< DIER_CC1IE) ;
                TIM2->DIER |=  (1<< DIER_CC1DE) ;
            }
    	}
   		else if (CHANNEL_x == 1)
         {
            /*************************************** Select Edge   ******************************************/
            // Rising   CC1NP/CC1P 0b00
            TIM2->CCER &= ~(1<<CCER_CC2NP);
            TIM2->CCER &= ~(1<<CCER_CC2P);

            if(ICU_CAPTURE_x_EDGE == (ICU_CapturingEdges_t)ICU_CAPTURE_RISING_EDGE)
            {
                // Rising   CC1NP/CC1P 0b00
                TIM2->CCER &= ~(1<<CCER_CC2NP);
                TIM2->CCER &= ~(1<<CCER_CC2P);
            }
            else if (ICU_CAPTURE_x_EDGE == (ICU_CapturingEdges_t)ICU_CAPTURE_FALLING_EDGE)
            {
                // Falling  0b01
                TIM2->CCER &= ~(1<<CCER_CC2NP);
                TIM2->CCER |=  (1<<CCER_CC2P);
            }
            else
            {
                // Both Edges 0b11
                TIM2->CCER |=  (1<<CCER_CC2NP);
                TIM2->CCER |=  (1<<CCER_CC2P);
            }

	  }
	  else if (CHANNEL_x == 2)
	  {
          // Rising   CC1NP/CC1P 0b00
          TIM2->CCER &= ~(1<<CCER_CC3NP);
          TIM2->CCER &= ~(1<<CCER_CC3P);
            /*************************************** Select Edge   ******************************************/
            if(ICU_CAPTURE_x_EDGE == (ICU_CapturingEdges_t)ICU_CAPTURE_RISING_EDGE)
            {
                // Rising   CC1NP/CC1P 0b00
                TIM2->CCER &= ~(1<<CCER_CC3NP);
                TIM2->CCER &= ~(1<<CCER_CC3P);
            }
            else if (ICU_CAPTURE_x_EDGE == (ICU_CapturingEdges_t)ICU_CAPTURE_FALLING_EDGE)
            {
                // Falling  0b01
                TIM2->CCER &= ~(1<<CCER_CC3NP);
                TIM2->CCER |=  (1<<CCER_CC3P);
            }
            else
            {
                // Both Edges 0b11
                TIM2->CCER |=  (1<<CCER_CC3NP);
                TIM2->CCER |=  (1<<CCER_CC3P);
            }
          }
	  else if (CHANNEL_x == 3)
	  {
          TIM2->CCER &= ~(1<<CCER_CC4NP);
          TIM2->CCER &= ~(1<<CCER_CC4P);
            /*************************************** Select Edge   ******************************************/
            if(ICU_CAPTURE_x_EDGE == (ICU_CapturingEdges_t)ICU_CAPTURE_RISING_EDGE)
            {
                // Rising   CC1NP/CC1P 0b00
                TIM2->CCER &= ~(1<<CCER_CC4NP);
                TIM2->CCER &= ~(1<<CCER_CC4P);
            }
            else if (ICU_CAPTURE_x_EDGE == (ICU_CapturingEdges_t)ICU_CAPTURE_FALLING_EDGE)
            {
                // Falling  0b01
                TIM2->CCER &= ~(1<<CCER_CC4NP);
                TIM2->CCER |=  (1<<CCER_CC4P);
            }
            else
            {
                // Both Edges 0b11
                TIM2->CCER |=  (1<<CCER_CC4NP);
                TIM2->CCER |=  (1<<CCER_CC4P);
            }
	  }

    }
}

void ICU_voidDisableChannelIRQ(ICU_Config_t * p_userConfig , Channel_ID_t CHANNEL_x )
{
    if(p_userConfig->Timerx == Timer2)
    {
  	  if (CHANNEL_x == 0)
  	  {
          TIM2->DIER &= ~(1<< DIER_CC1IE) ;
  	  }
	  else if (CHANNEL_x == 1)
	  {
          TIM2->DIER &= ~(1<< DIER_CC2IE) ;

	  }
	  else if (CHANNEL_x == 2)
	  {
          TIM2->DIER &= ~(1<< DIER_CC3IE) ;
	  }
	  else if (CHANNEL_x == 3)
	  {
          TIM2->DIER &= ~(1<< DIER_CC4IE) ;
	  }
	  else
	  {

	  }
    }
    else if(p_userConfig->Timerx == Timer4)
    {
  	  if (CHANNEL_x == 0)
  	  {
          TIM4->DIER &= ~(1<< DIER_CC1IE) ;
  	  }
	  else if (CHANNEL_x == 1)
	  {
          TIM4->DIER &= ~(1<< DIER_CC2IE) ;

	  }
	  else if (CHANNEL_x == 2)
	  {
          TIM4->DIER &= ~(1<< DIER_CC3IE) ;
	  }
	  else if (CHANNEL_x == 3)
	  {
          TIM4->DIER &= ~(1<< DIER_CC4IE) ;
	  }
	  else
	  {

	  }
    }
    else if(p_userConfig->Timerx == Timer17)
    {
  	  if (CHANNEL_x == 0)
  	  {
          TIM17->DIER &= ~(1<< DIER_CC1IE) ;
  	  }
	  else if (CHANNEL_x == 1)
	  {
          TIM17->DIER &= ~(1<< DIER_CC2IE) ;

	  }
	  else if (CHANNEL_x == 2)
	  {
          TIM17->DIER &= ~(1<< DIER_CC3IE) ;
	  }
	  else if (CHANNEL_x == 3)
	  {
          TIM17->DIER &= ~(1<< DIER_CC4IE) ;
	  }
	  else
	  {

	  }
    }
}
void ICU_voidEnableChannelIRQ(ICU_Config_t * p_userConfig , Channel_ID_t CHANNEL_x )
{
    if(p_userConfig->Timerx == Timer2)
    {
  	  if (CHANNEL_x == 0)
  	  {
          TIM2->DIER |= (1<< DIER_CC1IE) ;
  	  }
	  else if (CHANNEL_x == 1)
	  {
          TIM2->DIER |= (1<< DIER_CC2IE) ;

	  }
	  else if (CHANNEL_x == 2)
	  {
          TIM2->DIER |= (1<< DIER_CC3IE) ;
	  }
	  else if (CHANNEL_x == 3)
	  {
          TIM2->DIER |= (1<< DIER_CC4IE) ;
	  }
	  else
	  {

	  }

    }
    else if(p_userConfig->Timerx == Timer4)
    {
  	  if (CHANNEL_x == 0)
  	  {
          TIM4->DIER |= (1<< DIER_CC1IE) ;
  	  }
	  else if (CHANNEL_x == 1)
	  {
          TIM4->DIER |= (1<< DIER_CC2IE) ;
	  }
	  else if (CHANNEL_x == 2)
	  {
          TIM4->DIER |= (1<< DIER_CC3IE) ;
	  }
	  else if (CHANNEL_x == 3)
	  {
          TIM4->DIER |= (1<< DIER_CC4IE) ;
	  }
	  else
	  {

	  }
    }
    else if(p_userConfig->Timerx == Timer17)
    {
  	  if (CHANNEL_x == 0)
  	  {
          TIM17->DIER |= (1<< DIER_CC1IE) ;
  	  }
	  else if (CHANNEL_x == 1)
	  {
          TIM17->DIER |= (1<< DIER_CC2IE) ;

	  }
	  else if (CHANNEL_x == 2)
	  {
          TIM17->DIER |= (1<< DIER_CC3IE) ;
	  }
	  else if (CHANNEL_x == 3)
	  {
          TIM17->DIER |= (1<< DIER_CC4IE) ;
	  }
	  else
	  {

	  }

    }
}
void ICU_voidResetTimer(ICU_Config_t * p_userConfig)
{
    if(p_userConfig->Timerx == Timer2)
    {
        TIM2->CNT  = 0 ;
    }
    else if(p_userConfig->Timerx == Timer4)
    {
        TIM4->CNT  = 0 ;
    }
    else if(p_userConfig->Timerx == Timer17)
    {
        TIM17->CNT  = 0 ;
    }
}
/************************************* IRQs ******************************************/

void TIM2_IRQHandler (void)
{
	u32 ChannelReading = 0 ;
	// Check Channel
    if ( ( TIM2->SR & ( 1<< ( CHANNEL_3+1 ) ) ) )
    {
    	if(GlobalP2F_TIM2[CHANNEL_3] != NULL)
    	{
    		ChannelReading = TIM2->CCRx[CHANNEL_3] ;
    		GlobalP2F_TIM2[CHANNEL_3](ChannelReading) ;
    	}

    }
    if ( ( TIM2->SR & ( 1<< ( CHANNEL_1+1 ) ) ) )
	{
		// CH1
    	if(GlobalP2F_TIM2[CHANNEL_1] != NULL)
    	{
			ChannelReading = TIM2->CCRx[CHANNEL_1] ;
			GlobalP2F_TIM2[CHANNEL_1](ChannelReading) ;
    	}
	}
    if ( ( TIM2->SR & ( 1<< ( CHANNEL_2+1 ) ) ) )
	{
		if(GlobalP2F_TIM2[CHANNEL_2] != NULL)
		{
			ChannelReading = TIM2->CCRx[CHANNEL_2] ;
			GlobalP2F_TIM2[CHANNEL_2](ChannelReading) ;
		}
	}
    if ( ( TIM2->SR & ( 1<< ( CHANNEL_4+1 ) ) ) )
	{
    	if(GlobalP2F_TIM2[CHANNEL_4] != NULL)
    	{
			ChannelReading = TIM2->CCRx[CHANNEL_4] ;
			GlobalP2F_TIM2[CHANNEL_4](ChannelReading) ;
    	}
	}
}

void TIM4_IRQHandler (void)
{
	u32 ChannelReading = 0 ;
	// Check Channel
    if ( ( TIM4->SR & ( 1<< ( CHANNEL_1+1 ) ) ) )
    {
    	if(GlobalP2F_TIM4[CHANNEL_1] != NULL)
    	{
    		ChannelReading = TIM4->CCRx[CHANNEL_1] ;
    		GlobalP2F_TIM4[CHANNEL_1](ChannelReading) ;
    	}

    }

}

void TIM17_IRQHandler (void)
{
	u32 ChannelReading = 0 ;
	// Check Channel
    if ( ( TIM17->SR & ( 1<< ( CHANNEL_1+1 ) ) ) )
    {
    	if(GlobalP2F_TIM17[CHANNEL_1] != NULL)
    	{
    		ChannelReading = TIM17->CCRx[CHANNEL_1] ;
    		GlobalP2F_TIM4[CHANNEL_1](ChannelReading) ;
    	}

    }

}
/************************************* End of File ******************************************/
