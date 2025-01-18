/*
 * AutoWiper.h
 *
 * Created: 9/16/2023 12:40:36 PM
 *  Author: youssef rashad
 */ 


#ifndef AUTOWIPER_H_
#define AUTOWIPER_H_

#include "util/delay.h"
#include "../../LIB/std_types.h"
#include "../../MCAL/timer/TIMERS_Interface.h"
#include "../../HALL/SERVO_MOTOR/ServoMotor.h"
#include "../../HALL/RAIN_SENSOR/Rain_Sensor.h"




void AutoWiper_vidsetup();
void AutoWiper_vidloop();



#endif /* AUTOWIPER_H_ */