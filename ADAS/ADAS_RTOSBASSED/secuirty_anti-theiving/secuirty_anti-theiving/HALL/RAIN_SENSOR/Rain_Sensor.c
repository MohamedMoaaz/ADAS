/*
 * Rain_Sensor.c
 *
 * Created: 9/15/2023 3:11:57 PM
 *  Author: Shaimaa Mahmoud
 */ 


#include "Rain_Sensor.h"
#include "../LCD/lcd.h"

void RAIN_SENSOR_vidInit()
{
	dio_vidConfigChannel(RAIN_SENSOR_PORT,RAIN_SENSOR_PIN,INPUT);
}
u8 RAIN_SENSOR_voidGetState(void)
{
	u8 temp_state;
	temp_state=dio_dioLevelReadChannel(RAIN_SENSOR_PORT,RAIN_SENSOR_PIN);
// 	lcd_vidClrDislay();
// 	lcd_vidDispalyNumber(temp_state);
	if (temp_state==1)
	{
		return RAIN;
	} 
	else
	{
		return NO_RAIN;
	}
}