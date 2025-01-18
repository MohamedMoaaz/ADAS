/**
* @file PWM_private.h
* @author Mohamed Abd El-Naby (mahameda.naby@gmail.com) 
* @brief 
* @version 0.1
* @date 2023-09-12
*
*/
#ifndef PWM_PRIVATE_H 
#define PWM_PRIVATE_H 





/******************************************************************************
* Includes
*******************************************************************************/




/******************************************************************************
* Preprocessor Constants
 *******************************************************************************/




/******************************************************************************
* Configuration Constants
*******************************************************************************/







/******************************************************************************
* Typedefs
*******************************************************************************/
/*          REGISTERS IN EACH MODULE    */
typedef struct 
{
    u32 CR1  ;
    u32 CR2  ;
    u32 SMCR  ;
    u32 DIER  ;
    u32 SR ;
    u32 EGR ;
    u32 CCMR1  ;
    u32 CCMR2 ;
    u32 CCER ;
    u32 CNT ;
    u32 PSC ;
    u32 ARR ;
    u32 RES1 ;
    u32 CCRx[4] ;
    u32 RES2 ;
    u32 DCR ;
    u32 DMAR ;
}volatile *const TIM_Regs_t ;

/******************************************************************************
* Macros
*******************************************************************************/

/*      REGISTER BOUNDARY ADDRESSES FOR TIMx     */      
#define TIM2_BASE_ADDRESS                  0x40000000           //APB1 
#define TIM3_BASE_ADDRESS                  0x40000400           //APB1		For PWM 
#define TIM4_BASE_ADDRESS                  0x40000800            //APB1 
#define TIM17_BASE_ADDRESS                 0x40014800           //APB2



/*          REGISTERS ADDRESSES FOR Port A                  */      

#define TIM2  ((TIM_Regs_t)TIM2_BASE_ADDRESS)
#define TIM3  ((TIM_Regs_t)TIM3_BASE_ADDRESS)
#define TIM4  ((TIM_Regs_t)TIM4_BASE_ADDRESS)
#define TIM17  ((TIM_Regs_t)TIM17_BASE_ADDRESS)




#define SMCR_ECE        14 
#define SMCR_SMS        0 
#define DIER_CC2IE      2
#define DIER_CC2DE      10
#define CCMR2_OC3PE     3

#define CCMR2_OC3M      4
#define CCMR2_OC4M      12

#define CCMR2_OC3PE     3
#define CCMR2_OC4PE     11
#define CCER_CC1E       0
#define CCER_CC1P       1
#define CCER_CC1NP      3
#define CCER_CC2E       4
#define CCER_CC2P       5
#define CCER_CC2NP      7
#define CCER_CC3E       8
#define CCER_CC3P       9
#define CCER_CC3NP      11
#define CCER_CC4E       12
#define CCER_CC4P       13
#define CCER_CC4NP      15
#define CR1_CEN         0
#define CR1_UDIS		1
#define CR1_ARPE		7

/*************************************** DIER Reg Bits  *****************************/
#define DIER_UIE        0
#define DIER_CC1IE      1
#define DIER_CC2IE      2
#define DIER_CC3IE      3
#define DIER_CC4IE      4

#define DIER_TIE        6
#define DIER_UDE        8

#define DIER_CC1DE      9    
#define DIER_CC2DE      10
#define DIER_CC3DE      11
#define DIER_CC4DE      12     


#define DIER_TDE        14

/*************************************** CMR1 Reg Bits  *****************************/
#define CCMR1_OC1PE     3
#define CCMR1_OC1M      4


#define CCMR1_OC2PE     11
#define CCMR1_OC2M      12

/*************************************** SR Reg Bits  *****************************/
#define SR_UIF          0    
#define SR_CC1IF        1
#define SR_CC2IF        2
#define SR_CC3IF        3
#define SR_CC4IF        4
#define SR_TIF          6
#define SR_CC1OF        9
#define SR_CC2OF        10
#define SR_CC3OF        11
#define SR_CC4OF        12










/******************************************************************************
* Variables
*******************************************************************************/




/******************************************************************************
* Module Variable Definitions
*******************************************************************************/




/******************************************************************************
* Private Function Prototypes
*******************************************************************************/




#endif
/************************************* End of File ******************************************/
