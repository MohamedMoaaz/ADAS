/*
 * buzzar.c
 *
 * Created: 9/20/2023 11:27:23 PM
 *  Author: Shaimaa Mahmoud
 */ 

#include "buzzar.h"
#include "../../MCAL/DIO/dio.h"
void Buzzer_voidSetAlarm(void)
{
	dio_vidWriteChannel(BUZZER_PORT,BUZZER_PIN,STD_HIGH);
}
void Buzzer_voidCLRAlarm(void)
{
	dio_vidWriteChannel(BUZZER_PORT,BUZZER_PIN,STD_LOW);
}