/*
* RTC_APP.c
*
* Created: 9/23/2023 1:03:27 AM
*  Author: USER
*/

#include "RTC_APP.h"
extern u8 buffer[20];
// u8 time_clock[3];
//


void RTC_vidsetup(void)
{
	
	RTC_Set_Time(0x10, 0x15, 0x30); 	// Set time 21:40:30	
}

void RTC_vidloop(void)
{
	/*lcd_vidClrDislay();*/
	u8 s=0,m=0,h=0;

			RTC_Get_Time(&h,&m,&s);
			sprintf(buffer, "%02x:%02x:%02x", (h & 0b00011111), (m & 0b01111111), (s & 0b01111111));
			lcd_vidGotoRowColumn(0,0);
			lcd_vidDisplyStr("Time is: ");
			lcd_vidDisplyStr(buffer);
			
			_delay_ms(1000);
	
}

