/*
 * RTC.h
 *
 * Created: 9/23/2023 1:01:46 AM
 *  Author: USER
 */ 


#ifndef RTC_H_
#define RTC_H_

#include "../../LIB/std_types.h"
#include "../../MCAL/I2C/I2C.h"

void RTC_Set_Time(u8 hour,u8 mint,u8 second);
void RTC_Set_Date(u8 day,u8 month,u8 year);
void RTC_Get_Time(/*u8 clock_ptr[]*/u8* hour, u8* mint,u8* second);
u8 RTC_Get_Date(u8 day,u8 month,u8 year);


#endif /* RTC_H_ */