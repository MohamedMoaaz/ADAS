/*
 * shock_sensor.h
 *
 * Created: 9/16/2023 11:34:15 AM
 *  Author: Shaimaa Mahmoud
 */ 


#ifndef SHOCK_SENSOR_H_
#define SHOCK_SENSOR_H_
#include "../../MCAL/ADC/ADC_Interface.h"
#include "../LCD/lcd.h"
#define  SHOCK_SENSOR_CHANNEL  ADC_channel5

typedef enum
{
	NON_SHOCKED,
	SHOCKED
	}SHOCK_STATE_t;    

SHOCK_STATE_t SHOCK_SENSOR_shockstate_tGetstate(void);


#endif /* SHOCK_SENSOR_H_ */