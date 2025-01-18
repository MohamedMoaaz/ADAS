/*
 * push_botton.c
 *
 * Created: 9/20/2023 7:48:56 PM
 *  Author: Shaimaa Mahmoud
 */ 

#include "push_botton.h"
PUSH_BOTTUN_STATE_t PUSH_BOTTUN_u8GetState(u8 BOTTON_PORT,u8 BOTTON_PIN)
{
	if (dio_dioLevelReadChannel(BOTTON_PORT,BOTTON_PIN)==STD_HIGH)
	{
		return PRESSED;
	} 
	else
	{
		return NOT_PRESSED;
	}
}