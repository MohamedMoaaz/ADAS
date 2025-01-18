/**
* @file US.h
* @author Your Name (email) 
* @brief 
* @version 0.1
* @date 2023-09-14
*
*/
#ifndef US__H 
#define US__H 





/******************************************************************************
* Includes
*******************************************************************************/



/******************************************************************************
* User Configuration
*******************************************************************************/




/******************************************************************************
* Preprocessor Constants
 *******************************************************************************/
#define NUXED_US_ENABLE         1
#if NUXED_US_ENABLE == 1 
#define US_NUMBER       4
#endif 



/******************************************************************************
* Configuration Constants
*******************************************************************************/




/******************************************************************************
* Macros
*******************************************************************************/
#define FIXED_US_ERROR_IN_CM		1

/**
 * @brief for 8 MHz Clock Min Counts are 3000 count
 */
#define DELAYS_BETWEEN_READINGS_IN_TERMS_OF_COUNTS		4000
/******************************************************************************
* Typedefs
*******************************************************************************/

typedef enum 
{
    US_POLLING = 0 , 
    US_IRQs    = 1 
}US_Mechanis_t;

typedef struct
{
    // Echo Pin Noted That TIM2CH3 Only Supported 
    TIMx_t          Timerx  ;   // DC Motor Will be based on Timerx @ref TIMx_t @file UTILIS.h
    Channel_ID_t    CHANNEL_x ; // DC Motor Will be based CHANNEL_X @ref Channel_ID_t @file UTILIS.h
    // Trig Pin
    #if NUXED_US_ENABLE == 1 
    u8              Trig_Port[US_NUMBER] ; 
    Pin_t           Trig_Pin[US_NUMBER] ;
    #else 
    u8              Trig_Port ; 
    Pin_t           Trig_Pin ;
    #endif 

    US_Mechanis_t   US_x    ;
    void (*p2Function)(u8 copy_u8Distance); // Used if US_x == US_IRQs
    
}Ultrasonic_Cfg;


typedef enum
{
	US_INVALID_READING,
	US_VALID_READING
}US_ERROR_t;

/******************************************************************************
* Variables
*******************************************************************************/




/******************************************************************************
* Function Prototypes
*******************************************************************************/

/**
 * @brief This Function is used to init ultrasonic module based on @ref Ultrasonic_Cfg
 * 
 * @param p2UserConfig Pinter to user configuration
 */
void US_voidInit(Ultrasonic_Cfg *p2UserConfig);


/**
 * @brief This Function is used to Get Distance Through Callback Function
 * 
 * @param p2UserConfig Pointer to user configuration  @ref Ultrasonic_Cfg
 * @param copy_u8UltrasonicIndex index of trig if @ref NUXED_US_ENABLE == 1 
 */
void US_voidGetDistanceAsynch(Ultrasonic_Cfg *p2UserConfig , u8 copy_u8UltrasonicIndex);

/**
 * @brief This Function is used to get Ultrasonic Reading in CM 
 * 
 * @param p2UserConfig  Pointer to user configuration  @ref Ultrasonic_Cfg
 * @param pData_DistanceInCM Calculated Distance in CM
 * @param copy_u8UltrasonicIndex    index of trig if @ref NUXED_US_ENABLE == 1
 *
 * @return one of @ref US_ERROR_t
 */
US_ERROR_t US_voidGetDistanceSynch(Ultrasonic_Cfg *p2UserConfig , u16* pData_DistanceInCM,u8 copy_u8UltrasonicIndex) ;



#endif
/************************************* End of File ******************************************/
