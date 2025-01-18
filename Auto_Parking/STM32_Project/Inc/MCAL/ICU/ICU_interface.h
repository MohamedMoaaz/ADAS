/**
* @file ICU_interface.h
* @author Mohamed Abd El-Naby (mahameda.naby@gmail.com) 
* @brief 
* @version 0.1
* @date 2023-09-14
*
*/
#ifndef ICU_INTERFACE_H 
#define ICU_INTERFACE_H 





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
* Macros
*******************************************************************************/
#define ICU_NOT_USED 0



/******************************************************************************
* Typedefs
*******************************************************************************/
typedef enum
{
    ICU_CHECK_MECHNSIM_POLLING =1 , 
    ICU_CHECK_MECHNSIM_IRQs    ,
    ICU_CHECK_MECHNSIM_DMA              // Not Supported

}ICU_CheckMechanism_t ; 

typedef enum
{
    ICU_CAPTURE_RISING_EDGE = 1 ,
    ICU_CAPTURE_FALLING_EDGE = 2,
    ICU_CAPTURE_BOTH_EDGE =3
}ICU_CapturingEdges_t; 

typedef struct 
{
    TIMx_t                              Timerx  ;  
    ICU_CheckMechanism_t                ICU_CHECK_MECHNSIM_x[4];
    ICU_CapturingEdges_t                ICU_CAPTURE_x_EDGE[4]  ;
    u16                                 ICU_u16Prescaler    ;
    u32									ICU_Max_Counting	;

}ICU_Config_t;


typedef enum
{
	ICU_OVER_CAPTURED	,
	ICU_TIME_OUT		,
	ICU_UNKOWN_ERR		,
	ICU_OK
}ICU_Error_t;

/******************************************************************************
* Variables
*******************************************************************************/




/******************************************************************************
* Function Prototypes
*******************************************************************************/
/**
 * @brief This Function is used to init the ICU Module 
 * 
 * @param p_userConfig pointer to user config struct @ref ICU_Config_t
 */
void ICU_voidInit(ICU_Config_t * p_userConfig);


/**
 * @brief This Function is used to detect the capture counts 
 * 
 * @param p_userConfig pointer to user config struct @ref ICU_Config_t
 * @param CHANNEL_x     Channel ID
 * @param ptr_u32CapturedValue Pointer to captured value
 *
 * @return one of @ref ICU_Error_t
 */
ICU_Error_t ICU_voidGetCapturedValueSynch(ICU_Config_t * p_userConfig , Channel_ID_t CHANNEL_x , u32 *ptr_u32CapturedValue);


void ICU_voidGetCapturedValueAsynch(ICU_Config_t * p_userConfig , Channel_ID_t CHANNEL_x , void (*pCallback)(u32 CurrentCounts) );


void ICU_voidChangeCaptureEdge(ICU_Config_t * p_userConfig , Channel_ID_t CHANNEL_x ,ICU_CapturingEdges_t ICU_CAPTURE_x_EDGE );

void ICU_voidDisableChannelIRQ(ICU_Config_t * p_userConfig , Channel_ID_t CHANNEL_x );

void ICU_voidEnableChannelIRQ(ICU_Config_t * p_userConfig , Channel_ID_t CHANNEL_x );

void ICU_voidResetTimer(ICU_Config_t * p_userConfig);



#endif
/************************************* End of File ******************************************/
