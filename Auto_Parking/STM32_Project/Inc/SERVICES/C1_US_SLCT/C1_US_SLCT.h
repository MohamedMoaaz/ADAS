/**
* @file C1_US_SLCT.h
* @author Your Name (email) 
* @brief 
* @version 0.1
* @date 2023-09-14
*
*/
#ifndef C1_US_SLCT__H 
#define C1_US_SLCT__H 





/******************************************************************************
* Includes
*******************************************************************************/
#include "US/US.h"


/******************************************************************************
* User Configuration
*******************************************************************************/




/******************************************************************************
* Preprocessor Constants
 *******************************************************************************/




/******************************************************************************
* Configuration Constants
*******************************************************************************/




/******************************************************************************
* Macros
*******************************************************************************/
#define C4_MAX_ERROR_LOGGING 3



/******************************************************************************
* Typedefs
*******************************************************************************/
/******************************** States ********************************/
// Must Started From 0
/**
 * D10 D11 D12 D13
 * 0   1   2   3
 * FR  F   RR  B
 * Front US <--- 1
 * Back US  <--- 3
 * Front Right <--- 0
 * Front Left  <---- 2
 */
typedef enum
{
    FrontRightUS = 0 ,
	FrontUS      = 1 ,
    RearRightUS  = 2 , // BACK
    BackUS       = 3
}US_Selection_t;

/**************************** US Pins ***************************************/ 

#define US1_TRIG_PORT    PORTB
#define US1_TRIG_PIN	 PIN6
#define US2_TRIG_PORT    PORTA
#define US2_TRIG_PIN	 PIN7
#define US3_TRIG_PORT    PORTA
#define US3_TRIG_PIN	 PIN6
#define US4_TRIG_PORT    PORTA
#define US4_TRIG_PIN	 PIN5

/******************************************************************************
* Variables
*******************************************************************************/




/******************************************************************************
* Function Prototypes
*******************************************************************************/
/**
 * @brief This Function is used to init Componant 1 in APP 
 * 
 */
void APPC1_Init(void); 

/**
 * @brief This Function is used to select one of @ref US_Selection_t
 * 
 * @param copy_UltrasonicNumber slect one ultrasonic from @ref US_Selection_t
 * @param pData_DistanceInCM Measured Distance in CM
 *
 * @return one of @ref US_ERROR_t
 */
US_ERROR_t APPC1_SelectUltrasonc(US_Selection_t copy_UltrasonicNumber , u16 *pData_DistanceInCM);

ERROR_t C4_StaticGetFourDistance(u16 *FD , u16 *BD , u16 *FRD , u16 *BRD);

#endif
/************************************* End of File ******************************************/
