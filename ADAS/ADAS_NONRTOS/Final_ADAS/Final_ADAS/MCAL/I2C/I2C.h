/*
 * I2C.h
 *
 * Created: 9/21/2023 2:36:19 PM
 *  Author: USER
 */ 


#ifndef I2C_H_
#define I2C_H_

#include "../../LIB/std_types.h"
#include "I2C_reg.h"



void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(unsigned char data);
u8 I2C_Read(unsigned char ack);

#endif /* I2C_H_ */