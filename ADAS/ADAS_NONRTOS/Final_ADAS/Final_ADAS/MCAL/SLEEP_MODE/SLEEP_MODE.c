/*
 * SLEEP_MODE.c
 *
 * Created: 9/23/2023 2:00:50 PM
 *  Author: Shaimaa Mahmoud
 */ 
#include "SLEEP_MODE.h"


void SLEEP_MODEvoidEnable(u8 mode)
{
		MCUCR_reg|=(mode<<4);
		MCUCR_reg|=(1<<7);

}