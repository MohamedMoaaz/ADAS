/*
 * buzzar.h
 *
 * Created: 9/20/2023 11:27:13 PM
 *  Author: Shaimaa Mahmoud
 */ 


#ifndef BUZZAR_H_
#define BUZZAR_H_

#define BUZZER_PORT       DIO_PORTC
#define  BUZZER_PIN       DIO_PIN6

void Buzzer_voidSetAlarm(void);
void Buzzer_voidCLRAlarm(void);




#endif /* BUZZAR_H_ */