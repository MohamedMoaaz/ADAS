/*
* ADC_Interface.h
*
* Created: 9/15/2023 6:32:32 PM
*  Author: youssef rashad
*/

/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <ADC.h>
 *       Module:  ADC
 *
 *  Description:  <Selection of ADC prescaler value>     
 *  Note: ADC requires input clock frequency between 50KHz to 200KHz for maximum resolution
 *********************************************************************************************************************/
#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_
#define ADC_Prescaler_2 2
#define ADC_Prescaler_4 4
#define ADC_Prescaler_8 8
#define ADC_Prescaler_16 16
#define ADC_Prescaler_32 32
#define ADC_Prescaler_64 64
#define ADC_Prescaler_128 128



/**************************SELECT ADC PRESCALER VALUE HERE******************/
#define ADC_SELECTED_PRESCALER ADC_Prescaler_128





// Automatically set the ADC prescaler value
#if (ADC_SELECTED_PRESCALER == ADC_Prescaler_2)
#define ADC_GlobPrescalerval 2
#elif (ADC_SELECTED_PRESCALER == ADC_Prescaler_4)
#define ADC_GlobPrescalerval 4
#elif (ADC_SELECTED_PRESCALER == ADC_Prescaler_8)
#define ADC_GlobPrescalerval 8
#elif (ADC_SELECTED_PRESCALER == ADC_Prescaler_16)
#define ADC_GlobPrescalerval 16
#elif (ADC_SELECTED_PRESCALER == ADC_Prescaler_32)
#define ADC_GlobPrescalerval 32
#elif (ADC_SELECTED_PRESCALER == ADC_Prescaler_64)
#define ADC_GlobPrescalerval 64
#elif (ADC_SELECTED_PRESCALER == ADC_Prescaler_128)
#define ADC_GlobPrescalerval 128
#else
#error "Invalid ADC prescaler selected"
#endif






#endif /* ADC_INTERFACE_H_ */