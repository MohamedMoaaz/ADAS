/*
 * auto_detect_motion.h
 *
 * Created: 9/20/2023 11:26:31 PM
 *  Author: Shaimaa Mahmoud
 */ 


#ifndef AUTO_DETECT_MOTION_H_
#define AUTO_DETECT_MOTION_H_

#include "../../LIB/bit_math.h"
#include "../../LIB/std_types.h"
#include "../../LIB/MAPPING.h"
#include "../../MCAL/DIO/dio.h"
#include "../../MCAL/timer/TIMERS_Interface.h"
#include "../../MCAL/EXT_INT/EXT_INT_interface.h"
#include "../../MCAL/EXT_INT/EXT_INT_interface.h"
#include "../../MCAL/SLEEP_MODE/SLEEP_MODE.h"
#include "../../MCAL/timer/TIMERS_Interface.h"
#include "../../HALL/PUSH_BOTTUN/push_botton.h"
#include "../../HALL/MOTION_SENSOR/MOTION_SENSOR.h"
#include "../../HALL/Buzzer/buzzar.h"



#define CONTACTOR_PIN     DIO_PIN3
#define CONTACTOR_PORT    DIO_PORTD

#define DOOR_LOCK_PIN     DIO_PIN4
#define DOOR_LOCK_PORT    DIO_PORTD

typedef enum
{
	NO_ACTION,
	ACTION
	}SYSTEM_ACTION_STATE_t;
	
void EXTINT0_CALLBACK(void);
SYSTEM_ACTION_STATE_t Get_DoorLockState(void);
void Get_ContactState(void *pvParameters);
void ENABLE_Sleep_Mode(void *pvParameters);
void DISABLE_Sleep_Mode(void *pvParameters);
void set_alarm(void);
SYSTEM_ACTION_STATE_t Get_VIDContactState(void);
#endif /* AUTO_DETECT_MOTION_H_ */