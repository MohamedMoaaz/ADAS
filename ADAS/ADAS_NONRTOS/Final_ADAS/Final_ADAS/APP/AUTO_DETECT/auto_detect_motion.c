/*
 * auto_detect_motion.c
 *
 * Created: 9/20/2023 11:26:06 PM
 *  Author: Shaimaa Mahmoud
 */ 

#include <util/delay.h>
#include "auto_detect_motion.h"
u8 TimeDelayDone=0;
u8 fire_alarm;
void EXTINT0_CALLBACK()
{
	static u8 flag=0;
	if (flag==0)
	{
		flag=1;
		EXTINT_voidDisable(EXT_INT0);

		Timer_voidSetBusyWait_ms(TIMER0,500);
		TimeDelayDone=1;
		EXTINT_voidEnable(EXT_INT0);
	}
		fire_alarm=Get_DoorLockState();
		flag=0;
	
}

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

SYSTEM_ACTION_STATE_t Get_ContactState(void)
{
	return PUSH_BOTTUN_u8GetState(CONTACTOR_PORT,CONTACTOR_PIN);
}

void ENABLE_Sleep_Mode(void *pvparam)
{
	while(1)
	{
			if (Get_ContactState()==NO_ACTION)
			{
				lcd_vidDisplyStr("enter sleep mode -_-");
				EXTINT_voidEnable(EXT_INT0);
				SLEEP_MODEvoidEnable(idle);
				asm("sleep");
			}
	}

	
}

void DISABLE_Sleep_Mode(void *pvparam)
{
	while(1)
	{
				MCUCR_reg&=~(1<<7);
				lcd_vidClrDislay();
				lcd_vidDisplyStr("exit from sleep mode ^_^");
	}

}