/*
 * I2C_reg.h
 *
 * Created: 9/24/2023 1:39:35 AM
 *  Author: USER
 */ 


#ifndef I2C_REG_H_
#define I2C_REG_H_

#define I2C_TWDR_REG      		(*(volatile u8*)0x23)
#define I2C_TWAR_REG			(*(volatile u8*)0x22)
#define TWGCE	0
#define I2C_TWCR_REG			(*(volatile u8*)0x56)
#define TWIE	0
#define TWEN	2
#define TWWC	3
#define TWSTO	4
#define TWSTA	5
#define TWEA	6
#define TWINT	7
#define I2C_TWSR_REG			(*(volatile u8*)0x21)
#define I2C_TWBR_REG			(*(volatile u8*)0x20)



#endif /* I2C_REG_H_ */