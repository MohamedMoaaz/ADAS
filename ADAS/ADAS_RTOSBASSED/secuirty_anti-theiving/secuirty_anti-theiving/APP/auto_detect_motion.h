/*
 * auto_detect_motion.h
 *
 * Created: 9/20/2023 11:26:31 PM
 *  Author: Shaimaa Mahmoud
 */ 


#ifndef AUTO_DETECT_MOTION_H_
#define AUTO_DETECT_MOTION_H_

#include "../HALL/MOTION_SENSOR/MOTION_SENSOR.h"
#include "../HALL/PUSH_BOTTUN/push_botton.h"

#define CONTACTOR_PIN     DIO_PIN3
#define CONTACTOR_PORT    DIO_PORTD

#define DOOR_LOCK_PIN     DIO_PIN2
#define DOOR_LOCK_PORT    DIO_PORTD

typedef enum
{
	NO_ACTION,
	ACTION
	};
	

#endif /* AUTO_DETECT_MOTION_H_ */