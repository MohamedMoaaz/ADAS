/*
 * ADC.c
 *
 * Created: 9/13/2023 8:53:17 PM
 *  Author: youssef rashad
 */ 
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ADC_Interface.h"
/******************************************************************************
* \Syntax          : void ADC_vidInit()
* \Description     : Initialize ADC
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : NONE 
* \Return value:   : Func_State_t  Func_StatOk
*                                    Func_StatNotOk
*******************************************************************************/
Func_Stat_t ADC_vidInit()
{
	Func_Stat_t retstat = 1;
	ADMUX |= (1<<REFS1) | (1<<REFS0); //Internal Voltage Reference
	ADCSRA |= (1<<ADEN);//Enable ADC 
	switch(ADC_GlobPrescalerval)
	{
		case ADC_Prescaler_2:
		ADCSRA |= (1<<ADPS0);
		break;
		case ADC_Prescaler_4:
		ADCSRA |= (1<<ADPS1);
		break;
		case ADC_Prescaler_8:
		ADCSRA |= (1<<ADPS0) | (1<<ADPS1);
		break;
		case ADC_Prescaler_16:
		ADCSRA |= (1<<ADPS2);
		break;
		case ADC_Prescaler_32:
		ADCSRA |= (1<<ADPS0) | (1<<ADPS2);
		break;
		case ADC_Prescaler_64:
		ADCSRA |= (1<<ADPS1) | (1<<ADPS2);
		break;
		case ADC_Prescaler_128:
		ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);
		break;
	}
	retstat = 0;

return retstat;
}
u16 ADC_u16Read(ADC_channelnum_t channelId)
{
	u16 loc_ADCconvres = 0;
	ADMUX = (ADMUX & 0b11100000)|(channelId & 0b00011111); //first part to maintain ADMUX value in init and clear the 5 LSB OF ADMUX to be ready to be set by channel ID then the second part take channel id and make & with 000 to ensure that these bits won't be changed by channel ID and the rest is set by channelID
	SET_BIT(ADCSRA,ADSC); //start conversion
	while( CHECK_BIT(ADCSRA,ADIF) == 0);//wait until conversion is complete
	loc_ADCconvres = ADCL; // store in ADCL "Data reg"
	loc_ADCconvres |= (ADCH<<8);//store in ADCH
	return loc_ADCconvres;
	
}