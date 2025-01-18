/*
 * RTC.c
 *
 * Created: 9/23/2023 1:01:33 AM
 *  Author: USER
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "RTC2.h"

//unsigned char day, month, year;
u8 buffer[20];

void RTC_Set_Time(u8 hour,u8 mint,u8 second)        
{
	I2C_Start(); 		// transmit START condition
	I2C_Write(0xD0); 	// address DS1307 for write
	I2C_Write(0); 		// set register pointer to 0
	/*I2C_Write(second);*/  // set seconds
	I2C_Write(mint); 	// set minutes
	I2C_Write(hour);  	// set Hours
I2C_Stop();            
}
void RTC_Set_Date(u8 day,u8 month,u8 year)        
{
	I2C_Start(); 		// transmit START condition
	I2C_Write(0xD0);       // address DS1307 for write
	I2C_Write(0x04); 	// set register pointer to 4
	I2C_Write(day);  	// set day
	I2C_Write(month); 	// set month
	I2C_Write(year);  	// set year
I2C_Stop();            
}

void RTC_Get_Time(/*u8 clock_ptr[]*/u8* hour, u8* mint, u8* second)
{	
	I2C_Start();
	I2C_Write(0xD0);
	I2C_Write(0);
	I2C_Start();
	I2C_Write(0xD1);
	*second = I2C_Read(1);
	*mint= I2C_Read(1);
	*hour = I2C_Read(0);	
	I2C_Stop();
}	
 
u8 RTC_Get_Date(u8 day,u8 month,u8 year) 
{
	I2C_Start () ;         //transmit START condition
	I2C_Write(0xD0);       //address DS1307 for write
	I2C_Write(4);          //set register pointer to 4
	I2C_Start () ; 		//transmit START condition
	I2C_Write(0xD1); 	//address DS1307 for read
	day = I2C_Read(4);	//read second, return ACK
	month = I2C_Read(5);	//read minute, return ACK
	year = I2C_Read(6);	//read hour, return NACK
I2C_Stop();       
return day;
}	//transmit STOP condition

