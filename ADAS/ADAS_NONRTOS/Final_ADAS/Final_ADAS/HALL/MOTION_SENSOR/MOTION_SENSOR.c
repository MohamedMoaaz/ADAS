/*
 * MOTION_SENSOR.c
 *
 * Created: 9/20/2023 10:35:38 PM
 *  Author: Shaimaa Mahmoud
 */ 

#include "MOTION_SENSOR.h"

MOTION_SENSOR_STATE_t MOTIONSENSOR_MOTION_SENSOR_STATE_tGetState(void)
{
	if (dio_dioLevelReadChannel(MOTION_SENSOR_PORT,MOTION_SENSOR_PIN)==1)
	{
		return MOTION;
	} 
	else
	{
		return NO_MOTION;
	}
}