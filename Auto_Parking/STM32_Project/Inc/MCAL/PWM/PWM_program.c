/**
* @file PWM_program.c
* @author Mohamed Abd El-Naby (mahameda.naby@gmail.com) 
* @brief 
* @version 0.1
* @date 2023-09-12
*
*/
/******************************************************************************
* Includes
*******************************************************************************/
#include <LIB/BIT_MATH.h>
#include <LIB/STD_TYPES.h>
#include "PWM_interface.h"
#include "../ICU/TIM_private.h"
#include "PWM_config.h"










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
void PWM_voidInit(PWM_Config_t * p_userConfig)
{

    if(p_userConfig->Timerx == Timer3)
    {
      // Reset Usage Regs 
      TIM3->CCMR1 = 0x0000 ;
      TIM3->CCMR2 = 0x0000 ;
      TIM3->CR1 = 0x0000 ;
      TIM3->CR2 = 0x0000 ;
      TIM3->SMCR = 0x0000 ;
      TIM3->DIER = 0x0000 ;
      
      // Clock Selection : Internal Clock Source 
      TIM3->SMCR  &= ~(0b111 << SMCR_SMS) ;

      // Counting DIR      
      TIM3->CR1 &= ~(1<<4) ; // DIR BIT : 4
      TIM3->CR1 |= (p_userConfig->DIR_xCOUNTING) ;

      // Configure the prescaler 
      //   clock frequency = fCK_PSC / (PSC[15:0] + 1)
      //	975               = 8*10^6  / X            X ==
      TIM3->PSC  = 0 ;

      // TOP Value 
      TIM3->ARR = (u16) p_userConfig->TIMx_u32TopValue ;
      
      // PWM Mode :  writing 110 (PWM mode 1) or ‘111 (PWM mode 2) in the OCxM bits in the TIMx_CCMRx register
      // enable the corresponding preload register by setting the OCxPE bit in the TIMx_CCMRx register
      // Enable capture/compare For Used Channels
      for (u8 LOC_u8Counter = 0; LOC_u8Counter < 4; LOC_u8Counter++)
      {
        if(p_userConfig->TIMx_PWM_Mode_CHx[LOC_u8Counter] != PWM_NOT_USED)
        {
          if(LOC_u8Counter == 0)
          {
              // CCMR1
              TIM3->CCMR1 |= (p_userConfig->TIMx_PWM_Mode_CHx[LOC_u8Counter] << CCMR1_OC1M);
              // enable the corresponding preload REGISTER
              TIM3->CCMR1 |=  (1 << CCMR1_OC1PE) ;
              // Enable capture/compare channel 1 output
              TIM3->CCER |= (1<<CCER_CC1E);

          }
          else if (LOC_u8Counter == 1)
          {
              TIM3->CCMR1 |= (p_userConfig->TIMx_PWM_Mode_CHx[LOC_u8Counter] << CCMR1_OC2M);
              TIM3->CCMR1 |=  (1 << CCMR1_OC2PE) ;
              TIM3->CCER |= (1<<CCER_CC2E);

          }
          else if (LOC_u8Counter == 2)
          {
              TIM3->CCMR2 |= (p_userConfig->TIMx_PWM_Mode_CHx[LOC_u8Counter] << CCMR2_OC3M);
              TIM3->CCMR2 |=  (1 << CCMR2_OC3PE) ;
              TIM3->CCER |= (1<<CCER_CC3E);
          }
          else if (LOC_u8Counter == 3)
          {
              TIM3->CCMR2 |= (p_userConfig->TIMx_PWM_Mode_CHx[LOC_u8Counter] << CCMR2_OC4M);
              TIM3->CCMR2 |=  (1 << CCMR2_OC4PE) ;
              TIM3->CCER |= (1<<CCER_CC4E);

          }
        }
      }  
      // Auto Preload Value
      TIM3->CR1 |= (1<<CR1_ARPE);
      // Finally Enable TIM3 
      TIM3->CR1 |= (1<<CR1_CEN);
    }

}

void PWM_voidSetDutyCycle(PWM_Config_t * p_userConfig , u16 copy_u16DutyCycle , Channel_ID_t CHANNEL_x)
{
    if(p_userConfig->Timerx == Timer3)
    {
      TIM3->CCRx[CHANNEL_x] = (0xFFFF &copy_u16DutyCycle) ;

    }
}



/************************************* End of File ******************************************/
