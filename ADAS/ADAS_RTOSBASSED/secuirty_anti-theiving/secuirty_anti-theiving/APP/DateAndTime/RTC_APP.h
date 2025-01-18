/*
 * RTC_APP.h
 *
 * Created: 9/24/2023 10:28:48 AM
 *  Author: youssef rashad
 */ 


#ifndef RTC_APP_H_
#define RTC_APP_H_
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
//#include "I2C.h"
#include "../../HALL/RTC/RTC2.h"

#include "../../HALL/LCD/lcd.h"
#include "../../LIB/std_types.h"
void RTC_vidsetup();
void RTC_vidloop(void *pvParameters);




#endif /* RTC_APP_H_ */