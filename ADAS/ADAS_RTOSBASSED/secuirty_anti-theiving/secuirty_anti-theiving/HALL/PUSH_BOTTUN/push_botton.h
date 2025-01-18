/*
 * push_botton.h
 *
 * Created: 9/20/2023 7:49:11 PM
 *  Author: Shaimaa Mahmoud
 */ 


#ifndef PUSH_BOTTON_H_
#define PUSH_BOTTON_H_


#include "../../MCAL/DIO/dio.h"



typedef enum
{
	NOT_PRESSED,
	PRESSED
	}PUSH_BOTTUN_STATE_t;

PUSH_BOTTUN_STATE_t PUSH_BOTTUN_u8GetState(u8 BOTTON_PORT,u8 BOTTON_PIN);


#endif /* PUSH_BOTTON_H_ */