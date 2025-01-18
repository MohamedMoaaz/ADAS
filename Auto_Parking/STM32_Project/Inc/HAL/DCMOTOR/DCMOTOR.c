/**
* @file DCMOTOR.c
* @author Rana Abdelsalam (ranaabdelsalam65@gmail.com)
* @brief 
* @version 0.1
* @date 2023-09-14
*
*/

/******************************************************************************
* Includes
*******************************************************************************/

#include <LIB/BIT_MATH.h>
#include <LIB/STD_TYPES.h>
#include "LIB/UTILS.h"
#include "RCC/RCC_interface.h"
#include "../MCAL/GPIO/GPIO_interface.h"
#include "PWM/PWM_interface.h"
#include "DCMOTOR.h"


/******************************************************************************
* PWM Configurations
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
static PWM_Config_t _Global_PWM_Timer3_Inst;




/******************************************************************************
* Function Prototypes
*******************************************************************************/




/******************************************************************************
* Function Definitions
*******************************************************************************/
void DCMOTOR_voidInit(DCMotor_Cfg* p2UserConfig)
{
    // Only Supported Timer3 
    if(p2UserConfig->Timerx == Timer3)
    {
        // Init Timer Clocks and Used Ports 
    	RCC_voidInitSysClocks();
    	RCC_voidEnableClock(RCC_AHB, p2UserConfig->CW_Port);
    	RCC_voidEnableClock(RCC_AHB, p2UserConfig->CCW_Port);

    	RCC_voidEnableClock(RCC_APB1, Timer3);

    	// Set CW/CCW Port Pin as output
    	GPIO_voidSetPinDirection( p2UserConfig->CW_Port, p2UserConfig->CW_Pin, GPIO_OUTPUT_LOW_SPD_PUSH_PULL);
        GPIO_voidSetPinDirection( p2UserConfig->CCW_Port, p2UserConfig->CCW_Pin, GPIO_OUTPUT_LOW_SPD_PUSH_PULL);

    	// Set CW to HIGH and CCW to HIGH to Brake Motor @ first
    	GPIO_voidSetPinValue(p2UserConfig->CW_Port, p2UserConfig->CW_Pin , LOW);
    	GPIO_voidSetPinValue(p2UserConfig->CCW_Port, p2UserConfig->CCW_Pin , LOW);


    	// AFIOs Based on Channel Support only Channel 1 and Channel 2
        if(p2UserConfig->CHANNEL_x == CHANNEL_1)
        {
        	RCC_voidEnableClock(RCC_AHB, PORTB);
        	GPIO_voidSetPinDirection(PORTB	, PIN4, GPIO_AF_LOW_SPD);
        	GPIO_voidSetAFIO(PORTB	, PIN4, AFIO_2);	//TIM3CH1
        }
        else if (p2UserConfig->CHANNEL_x == CHANNEL_2)
        {
        	RCC_voidEnableClock(RCC_AHB, PORTC);

        	GPIO_voidSetPinDirection(PORTC	, PIN7, GPIO_AF_LOW_SPD);
        	GPIO_voidSetAFIO(PORTC	, PIN7, AFIO_2);	//TIM3CH2


        	}
        else
        {
            // <!TODO> Not Supported Yet 
        }
        //  PWM Configurations config name _Global_PWM_Timer3_Inst
        _Global_PWM_Timer3_Inst.Timerx = Timer3;
        _Global_PWM_Timer3_Inst.DIR_xCOUNTING = DIR_UPCOUNTING;
        _Global_PWM_Timer3_Inst.TIMx_u32TopValue = 256;
        _Global_PWM_Timer3_Inst.TIMx_PWM_Mode_CHx[p2UserConfig->CHANNEL_x] = PWM_MODE_1;

        // Init PWM 
    	PWM_voidInit(& _Global_PWM_Timer3_Inst);
    }
}

void DCMOTOR_voidSetDirection(DCMotor_Cfg* p2UserConfig,Motor_Dir_t copy_xMotorDir)
{
    // Only Supported Timer3 
	if(p2UserConfig->Timerx == Timer3)
	{
		switch (copy_xMotorDir)
		{
		case MTR_STOP :
			/* code */
			/*IN1 & IN2 = 0 | IN1 & IN2 = 1 */
			GPIO_voidSetPinValue(p2UserConfig->CW_Port, p2UserConfig->CW_Pin , LOW);
			GPIO_voidSetPinValue(p2UserConfig->CCW_Port, p2UserConfig->CCW_Pin , LOW);
			break;

		case MTR_ROTATE_CW :
			/* code */
			/*IN1 = 1 & IN2 = 0*/
			GPIO_voidSetPinValue(p2UserConfig->CW_Port, p2UserConfig->CW_Pin , HIGH);
			GPIO_voidSetPinValue(p2UserConfig->CCW_Port, p2UserConfig->CCW_Pin , LOW);
			break;

		case MTR_ROTATE_CCW :
			/* code */
			/*IN1 = 0 & IN2 = 1*/
			GPIO_voidSetPinValue(p2UserConfig->CW_Port, p2UserConfig->CW_Pin , LOW);
			GPIO_voidSetPinValue(p2UserConfig->CCW_Port, p2UserConfig->CCW_Pin , HIGH);
			break;
        default:
            break;
        }
    }
}

void DCMOTOR_voidSetSpeed(DCMotor_Cfg* p2UserConfig,u16 copy_u16MotorSpeed)
{
    // Only Supported Timer3 
    if(p2UserConfig->Timerx == Timer3)
    {   
    	if(_Global_PWM_Timer3_Inst.TIMx_u32TopValue > copy_u16MotorSpeed)
    	{
            // Only TWO Channels Supported
        	PWM_voidSetDutyCycle(&_Global_PWM_Timer3_Inst , copy_u16MotorSpeed , p2UserConfig->CHANNEL_x);

    	}

    }   
 }

/************************************* End of File ******************************************/
