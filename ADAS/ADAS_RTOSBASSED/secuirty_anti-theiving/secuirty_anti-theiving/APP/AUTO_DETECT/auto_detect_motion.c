/*
 * auto_detect_motion.c
 *
 * Created: 9/20/2023 11:26:06 PM
 *  Author: Shaimaa Mahmoud
 */ 

#include <util/delay.h>
#include "auto_detect_motion.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "../main.h"
u8 TimeDelayDone=0;
u8 fire_alarm;
u8 contactor_state=0;



SYSTEM_ACTION_STATE_t Get_DoorLockState(void)
{
	 return PUSH_BOTTUN_u8GetState(DOOR_LOCK_PORT,DOOR_LOCK_PIN);
}

void set_alarm(void)
{
	if (fire_alarm==1)
	{
		Buzzer_voidSetAlarm();
		
	}
}

// void Get_ContactState(void *pvParameters)
// {
// 	while(1)
// 	{
//      contactor_state= PUSH_BOTTUN_u8GetState(CONTACTOR_PORT,CONTACTOR_PIN);
// 	}
// 
// }

SYSTEM_ACTION_STATE_t Get_VIDContactState(void)
{
	
	return PUSH_BOTTUN_u8GetState(CONTACTOR_PORT,CONTACTOR_PIN);


}


