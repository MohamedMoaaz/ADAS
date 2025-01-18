/**
* @file C2_VCLE_CNTRL.h
* @author Your Name (email) 
* @brief 
* @version 0.1
* @date 2023-09-15
*
*/
#ifndef C2_VCLE_CNTRL__H 
#define C2_VCLE_CNTRL__H 





/******************************************************************************
* Includes
*******************************************************************************/




/******************************************************************************
* User Configuration
*******************************************************************************/
// Back_Motor
#define C2_MOT1_CW_PORT        PORTB		//
#define C2_MOT1_CW_PIN         PIN13
#define C2_MOT1_CCW_PORT       PORTB
#define C2_MOT1_CCW_PIN        PIN14

// Steering
#define C2_MOT2_CCW_PORT        PORTB
#define C2_MOT2_CCW_PIN         PIN15
#define C2_MOT2_CW_PORT       PORTB
#define C2_MOT2_CW_PIN        PIN1



// LEDs
#define BACK_RIGHT_LED_PORT		PORTB
#define BACK_RIGHT_LED_PIN		PIN9

#define BACK_LEFT_LED_PORT		PORTB
#define BACK_LEFT_LED_PIN		PIN8



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
	VCLE_STOP,
    VCLE_FWD,
    VCLE_BWD,
    VCLE_RIGHT_FWD,
	VCLE_RIGHT_BWD,
    VCLE_LEFT_BWD,
	VCLE_LEFT_FWD
}VCLE_Dir_t ; 



/******************************************************************************
* Variables
*******************************************************************************/




/******************************************************************************
* Function Prototypes
*******************************************************************************/

/**
 * @brief Init the required Modules 
 * 
 */
void C2VCONTROL_voidInit(void); 

/**
 * @brief Change Vechile Dirction with specific speed 
 * 
 * @param VCLE_x        ديسكريبشن هنااا
 * @param copy_u16Speed 
 * 
 */
void C2VCONTROL_voidChangeDirection(VCLE_Dir_t VCLE_x , u16 copy_u16VcleSpeed);






#endif
/************************************* End of File ******************************************/
