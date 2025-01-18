/*
 * SLEEP_MODE.h
 *
 * Created: 9/23/2023 2:01:02 PM
 *  Author: Shaimaa Mahmoud
 */ 


#ifndef SLEEP_MODE_H_
#define SLEEP_MODE_H_
#include "../../LIB/std_types.h"
#define MCUCR_reg     (*(volatile u8 *)(0x55))
typedef enum
{
	idle,
	 ADC_Noise_Reduction,
	 power_down,
	 power_saver,
	 standby=6,
	 external_standby
	}sleep_mode_t;
void SLEEP_MODEvoidEnable(u8 mode);



#endif /* SLEEP_MODE_H_ */