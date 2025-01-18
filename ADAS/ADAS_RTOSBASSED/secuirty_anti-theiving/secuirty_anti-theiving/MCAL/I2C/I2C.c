/*
 * I2C.c
 *
 * Created: 9/21/2023 2:36:04 PM
 *  Author: USER
 */ 

#include "I2C.h"

void I2C_Init(void)
{
	I2C_TWSR_REG=0x00;  // set prescaler bits  to zero
	I2C_TWBR_REG=32;    // SCL freq. is 100k for XTAL=8M
	I2C_TWCR_REG=0x04;
} // enable TWI module

void I2C_Start(void){
	I2C_TWCR_REG = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);
	while (!(I2C_TWCR_REG & (1<<TWINT))); 
}

void I2C_Stop(void){
I2C_TWCR_REG = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

void I2C_Write(unsigned char data){
	I2C_TWDR_REG = data;
	I2C_TWCR_REG = (1<<TWINT) | (1<<TWEN) ;
	while (!(I2C_TWCR_REG & (1<<TWINT) ) ) ;
}

u8 I2C_Read(unsigned char ack)
{
	I2C_TWCR_REG = (1<<TWINT) | (1<<TWEN)|(ack<<TWEA) ;
	while (!(I2C_TWCR_REG & (1<<TWINT) ) ) ; 
	return I2C_TWDR_REG; 
}
 