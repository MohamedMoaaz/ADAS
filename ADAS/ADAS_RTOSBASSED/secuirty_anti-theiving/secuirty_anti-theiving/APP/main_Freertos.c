/*
 * main_Freertos.c
 *
 * Created: 10/1/2023 10:49:22 PM
 *  Author: Shaimaa Mahmoud
 */ 
#define F_CPU     16000000UL

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "semphr.h"
#include "AUTO_DETECT/auto_detect_motion.h"
#include "AUTO_LIGHT/AutoLight.h"
#include "AUTO_WIPE/AutoWiper.h"
#include "DateAndTime/RTC_APP.h"
#include "../HALL/SERVO_MOTOR/ServoMotor.h"


extern u8 fire_alarm;
TaskHandle_t Task_LCDClr;
TaskHandle_t Task_GetTime;
TaskHandle_t Task_AutoLight;
TaskHandle_t Task_AutoWiper;
TaskHandle_t Task_GetContactState;
TaskHandle_t Task_DetectionRunning;
TaskHandle_t  Task_EnableSleepMode;
TaskHandle_t  Task_DisableSleepMode;
//
SemaphoreHandle_t  ButtonSemaphore = NULL;
SemaphoreHandle_t  LCDSemaphore = NULL;
u8 running_state=0;
extern u8 contactor_state;
extern u8 TimeDelayDone;
void EXTINT0_CALLBACK()
{
	static u8 flag=0;
	if (flag==0)
	{
		flag=1;
		EXTINT_voidDisable(EXT_INT0);
		vTaskDelay(500);
		TimeDelayDone=1;
		EXTINT_voidEnable(EXT_INT0);
	}
	xSemaphoreGive(ButtonSemaphore);
	fire_alarm=Get_DoorLockState();
	flag=0;
	
}
void DISABLE_Sleep_Mode(void *pvParameters)
{
	while(1)
	{
		if (pdTRUE==xSemaphoreTake(ButtonSemaphore,100))
		{
				MCUCR_reg&=~(1<<7);
				xSemaphoreTake(LCDSemaphore,100);
				lcd_vidClrDislay();
				lcd_vidDisplyStr("exit from sleep mode ^_^");
				xSemaphoreGive(LCDSemaphore);
					set_alarm();
				
		}
	}

}
void ENABLE_Sleep_Mode(void *pvParameters)
{
	while(1)
	{
		if ( Get_VIDContactState()==NO_ACTION)
		{
			xSemaphoreTake(LCDSemaphore,100);
				lcd_vidClrDislay();
				lcd_vidDisplyStr("enter sleep mode -_-");
				xSemaphoreGive(LCDSemaphore);
				EXTINT_voidEnable(EXT_INT0);
				SLEEP_MODEvoidEnable(idle);
				asm("sleep");
		}
	}

	
}
void main()
{
	
		//initializations
		lcd_vidInit();
		//INIT BUZZAR
		dio_vidConfigChannel(BUZZER_PORT,BUZZER_PIN,OUTPUT);
		//INIT BUTTUN FOR CONTACTOR
		dio_vidConfigChannel(CONTACTOR_PORT,CONTACTOR_PIN,INPUT);
		//INIT BUTTON FOR LOCK DOOR
		dio_vidConfigChannel(DOOR_LOCK_PORT,DOOR_LOCK_PIN,INPUT);
		//INIT TIMER0 FOR DELAY FUNCTIONS
		//init extint
		EXTINT_voidGlobalIntEnable();
		EXTINT_voidMode(EXT_INT0,EXT_INT0_RISING_EDGE,EXTINT0_CALLBACK);
		//INIT I2C
		I2C_Init();
		//INIT RTC FOR TIME AND CLOCK
		RTC_vidsetup();
		//init autolight system
		//init ADC
		ADC_vidInit();
		AutoLight_Func_StatSetup();
		//INIT AUTO WIPE SYSTEM
		//INIT
		AutoWiper_vidsetup();
		//dio_vidWriteChannel(CONTACTOR_PORT,CONTACTOR_PIN,STD_HIGH);
		// when motion detected exit from sleep mode
		//check for door lock sensor
		//if door unlock fire the buzzer and send message via GSM
	//task for check contact access global variable
	//xTaskCreate(Get_ContactState,(const signed char*)"Contact state check",85,NULL,GetContactState_pr,&Task_GetContactState);
	//task for auto light
	xTaskCreate(AutoLight_Func_StatLoop,(const signed char*)"auto lighting",85,NULL,AutoLight_pr,&Task_AutoLight);
	//task for auto wiper
	xTaskCreate(AutoWiper_vidloop,(const signed char*)"auto wiper",85,NULL,AutoWiper_pr,&Task_AutoWiper);
	//task for detection
	//xTaskCreate(lcd_vidClrDislay,(const signed char*)"LCD CLEAR DISPLAY",85,NULL,lcd_ClrDislay_pr,&Task_LCDClr);
	//task for time 
	xTaskCreate(RTC_vidloop,(const signed char*)"RTC GET TIME",85,NULL,GetTime_pr,&Task_GetTime);
	//task for sleep mode
	//enable sleep mode
	xTaskCreate(ENABLE_Sleep_Mode,(const signed char*)"enter sleep mode",85,NULL,EnableSleepMode_pr,&Task_EnableSleepMode);
	//disable sleep mode
	//xTaskCreate(DISABLE_Sleep_Mode,(const signed char*)"exit sleep mode",85,NULL,DisableSleepMode_pr,&Task_DisableSleepMode);
	 ButtonSemaphore=xSemaphoreCreateBinary();
	 LCDSemaphore=xSemaphoreCreateBinary();
	 xSemaphoreGive(LCDSemaphore);
	//xSemaphoreTake(ButtonSemaphore,100);
		lcd_vidClrDislay();
	lcd_vidDisplyStr("hello to ADAS ^-^");

	vTaskStartScheduler();
}

