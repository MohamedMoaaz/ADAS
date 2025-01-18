/*
 * AutoWiper.c
 *
 * Created: 9/16/2023 12:40:50 PM
 *  Author: youssef rashad
 */ 
#include "../main.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "AutoWiper.h"
u8 AutoWiper_Glob_AutoWiper_Prev_State = 0;
u8 AutoWiper_Glob_AutoWiper_Current_State = 0;
u8 AuttoWiper_Glob_Rain_flag;
Timer2Config_t TIMER2Configdelay={TIM_Normal_Mode,TIMER2_CLK_OVR_8};
ServoMotor_Config  servo1_config={SERVO_ATTTCH_PD5};
extern u8 contactor_state;
extern SemaphoreHandle_t  LCDSemaphore;
void AutoWiper_vidsetup()
{
	 RAIN_SENSOR_vidInit();
	Servo_voidInit(&servo1_config);
	Timer_voidInitTimer2(&TIMER2Configdelay);
	Servo_voidWrite(&servo1_config,0);
	Servo_voidWrite(&servo1_config,0);
}
void AutoWiper_vidloop(void *pvParameters)
{
	while(1)
	{
		if (Get_VIDContactState()==1)
		{
			if (RAIN_SENSOR_voidGetState()==RAIN)
			{
                 xSemaphoreTake(LCDSemaphore,100);
				lcd_vidGotoRowColumn(3,0);
				lcd_vidDisplyStr("Rain");
				xSemaphoreGive(LCDSemaphore);
				Servo_voidWrite(&servo1_config,180);
				Servo_voidWrite(&servo1_config,180);
				vTaskDelay(100);
				//_delay_ms(1000);
				Servo_voidWrite(&servo1_config,0);
				Servo_voidWrite(&servo1_config,0);
				vTaskDelay(100);
				//Timer_voidSetBusyWait_ms(TIMER2,100);
				AutoWiper_Glob_AutoWiper_Current_State = 1;
				AuttoWiper_Glob_Rain_flag = 1;
			}
			else
			{
				xSemaphoreTake(LCDSemaphore,100);
				lcd_vidGotoRowColumn(3,0);
				lcd_vidDisplyStr("No Rain");
				xSemaphoreGive(LCDSemaphore);
				AutoWiper_Glob_AutoWiper_Current_State = 0;
				AuttoWiper_Glob_Rain_flag = 0;
			}
			AutoWiper_Glob_AutoWiper_Prev_State = AutoWiper_Glob_AutoWiper_Current_State;
		}
		vTaskDelay(100);
		/*lcd_vidClrDislay();*/
	}
	
	
}
