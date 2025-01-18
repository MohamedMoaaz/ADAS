 /*
 * secuirty_anti-theiving.c
 *
 * Created: 9/17/2023 11:46:30 AM
 * Author : Shaimaa Mahmoud
 */
 #define F_CPU     16000000UL
 
 #include "AUTO_DETECT/auto_detect_motion.h"
 #include "AUTO_LIGHT/AutoLight.h"
 #include "AUTO_WIPE/AutoWiper.h"
 #include "DateAndTime/RTC_APP.h"
 #include "../HALL/SERVO_MOTOR/ServoMotor.h"
 
 
 Timer2Config_t TIMER0DELAY_config={TIM_Normal_Mode,TIMER0_CLK_OVR_8};
 
 extern u8 fire_alarm;
 int main(void)
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
	 Timer_voidInitTimer0(&TIMER0DELAY_config);
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
	 /* Replace with your application code */
	 while (1)
	 {
		 lcd_vidClrDislay();
		 //AUTOLIGHT
		 //detect contactor lock to activate sleep mode
		 while (dio_dioLevelReadChannel(CONTACTOR_PORT,CONTACTOR_PIN)==1)
		 {
			 // display time
			 
			 RTC_vidloop();
			 //AUTOLIGHT
			 AutoLight_Func_StatLoop();
			 //AUTO WIPE
			 AutoWiper_vidloop();
			 //SHOCK_SENSOR_shockstate_tGetstate();
			// while(dio_dioLevelReadChannel(CONTACTOR_PORT,CONTACTOR_PIN)==1);
		 }
		// else
		 {
			 //sleep mode
			 lcd_vidClrDislay();
			 lcd_vidDisplyStr("enter sleep mode -_-");
			 EXTINT_voidEnable(EXT_INT0);
			 SLEEP_MODEvoidEnable(idle);
			 asm("sleep");
			 MCUCR_reg&=~(1<<7);
			 lcd_vidClrDislay();
			 lcd_vidDisplyStr("exit from sleep mode ^_^");
			 //lcd_vidDispalyNumber(fire_alarm);
			 set_alarm();
			 //send message via GSM
			 _delay_ms(10000);
			 Buzzer_voidCLRAlarm();
			 //Timer_voidSetBusyWait_ms(TIMER0,3000);
		 }
	 }
 }
 
