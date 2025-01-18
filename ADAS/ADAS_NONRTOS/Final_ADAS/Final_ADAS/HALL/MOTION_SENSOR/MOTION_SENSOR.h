/*
 * MOTION_SENSOR.h
 *
 * Created: 9/20/2023 10:35:48 PM
 *  Author: Shaimaa Mahmoud
 */ 


#ifndef MOTION_SENSOR_H_
#define MOTION_SENSOR_H_
#include <util/delay.h>
#include "../../MCAL/DIO/dio.h"
#define MOTION_SENSOR_PIN     DIO_PIN2
#define MOTION_SENSOR_PORT    DIO_PORTD
#define MOTION_SENSOR_MODE    INPUT
typedef enum
{
	NO_MOTION,
	MOTION
	}MOTION_SENSOR_STATE_t;

MOTION_SENSOR_STATE_t MOTIONSENSOR_MOTION_SENSOR_STATE_tGetState(void);

#endif /* MOTION_SENSOR_H_ */