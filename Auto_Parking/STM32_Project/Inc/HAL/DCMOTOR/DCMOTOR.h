/**
* @file DCMOTOR.h
* @author Rana Abdelsalam (ranaabdelsalam65@gmail.com) 
* @brief 
* @version 0.1
* @date 2023-09-14
*
*/


#ifndef DCMOTOR__H 
#define DCMOTOR__H 





/******************************************************************************
* Includes
*******************************************************************************/




/******************************************************************************
* User Configuration
*******************************************************************************/


/*********************** Pins ****************************/




/******************************************************************************
* Preprocessor Constants
 *******************************************************************************/




/******************************************************************************
* Configuration Constants
*******************************************************************************/




/******************************************************************************
* Macros
*******************************************************************************/




/******************************************************************************
* Typedefs
*******************************************************************************/

typedef enum 
{
    MTR_STOP,
    MTR_ROTATE_CW ,
    MTR_ROTATE_CCW 
}Motor_Dir_t ; 


typedef struct
{
    // Enable Pin
    TIMx_t          Timerx  ;   // DC Motor Will be based on Timerx @ref TIMx_t @file UTILIS.h
    Channel_ID_t    CHANNEL_x ; // DC Motor Will be based CHANNEL_X @ref Channel_ID_t @file UTILIS.h

    // Direction 1 Pin 
    u8                 CW_Port ; 
    Pin_t              CW_Pin ; 
    
    // Direction 2 Pin
    u8                 CCW_Port ; 
    Pin_t              CCW_Pin ; 
}DCMotor_Cfg;




/******************************************************************************
* Variables
*******************************************************************************/




/******************************************************************************
* Function Prototypes
*******************************************************************************/

/**
 * @brief This Function is used to init PWM in Timerx on CHANNEL_x
 * 
 * @param p2UserConfig pointer to @ref Channel_ID_t that user defined in main 
 */
void DCMOTOR_voidInit(DCMotor_Cfg* p2UserConfig);

/**
 * @brief 
 * 
 * @param p2UserConfig 
 * @param copy_xMotorDir 
 */
void DCMOTOR_voidSetDirection(DCMotor_Cfg* p2UserConfig,Motor_Dir_t copy_xMotorDir);


/**
 * @brief 
 * 
 * @param p2UserConfig 
 * @param copy_u16MotorSpeed 
 */
void DCMOTOR_voidSetSpeed(DCMotor_Cfg* p2UserConfig,u16 copy_u16MotorSpeed);


#endif
/************************************* End of File ******************************************/
