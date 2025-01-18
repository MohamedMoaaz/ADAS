/*
 * AutoLight.h
 *
 * Created: 9/15/2023 8:21:53 PM
 *  Author: youssef rashad
 */ 
/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <AutoLight.h>
 *       Module:  Car Automatic Lightning subsystem
 *
 *  Description:  LEDS should automatically be turned on based on level of darkness from LDR sensor  
 *  
 *********************************************************************************************************************/

#ifndef AUTOLIGHT_H_
#define AUTOLIGHT_H_
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "../../HALL/LDR/LDR.h"
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
typedef enum 
{
	Led_ON = 0,
	Led_OFF
	}AutoLight_Stat_t;
void AutoLight_Func_StatSetup();
void AutoLight_Func_StatLoop(void *pvParameters);
#define AutoLight_LED_Port DIO_PORTA
#define AutoLight_LED_Pin  DIO_PIN6
#define AutoLight_LDR_threshold 800



#endif /* AUTOLIGHT_H_ */