/*
 * shock_sensor.c
 *
 * Created: 9/16/2023 11:34:26 AM
 *  Author: Shaimaa Mahmoud
 */ 
#include "shock_sensor.h"
SHOCK_STATE_t SHOCK_SENSOR_shockstate_tGetstate(void)
{
	u16 DATA;
	DATA=ADC_u16Read(SHOCK_SENSOR_CHANNEL);
	lcd_vidGotoRowColumn(1,0);
	lcd_vidDispalyNumber(DATA);
}