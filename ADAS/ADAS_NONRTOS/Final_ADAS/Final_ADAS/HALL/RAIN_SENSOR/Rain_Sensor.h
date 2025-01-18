/*
 * Rain_Sensor.h
 *
 * Created: 9/15/2023 3:12:11 PM
 *  Author: Shaimaa Mahmoud
 */ 


#ifndef RAIN_SENSOR_H_
#define RAIN_SENSOR_H_
#include "../../MCAL/ADC/ADC_interface.h"
#define RAIN_SENSOR_PORT     DIO_PORTA
#define RAIN_SENSOR_PIN     DIO_PIN7
#define RAIN                  1
#define NO_RAIN                0

void RAIN_SENSOR_vidInit();
u8 RAIN_SENSOR_voidGetState(void);



#endif /* RAIN_SENSOR_H_ */