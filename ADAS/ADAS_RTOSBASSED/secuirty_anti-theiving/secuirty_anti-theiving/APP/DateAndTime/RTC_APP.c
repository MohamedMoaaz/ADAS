/*
* RTC_APP.c
*
* Created: 9/23/2023 1:03:27 AM
*  Author: USER
*/

#include "RTC_APP.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
extern u8 buffer[20];

// u8 time_clock[3];
//

extern u8 contactor_state;
extern SemaphoreHandle_t  LCDSemaphore;
void RTC_vidsetup()
{
	/*lcd_vidInit();*/
	u8 minute,day;
	u8* clock_ptr;
	RTC_Set_Time(0x02, 0x05, 0x55); 	// Set time 21:40:30
	RTC_Set_Date(0x25, 0x12, 0x11); 	// Set date 25-12-2010
}
void RTC_vidloop(void *pvParameters)
{
	/*lcd_vidClrDislay();*/
	u8 s=0,m=0,h=0;
	while(1)
	{
		if (Get_VIDContactState()==1)
		{
				RTC_Get_Time(&h,&m,&s);	
				sprintf(buffer, "%02x:%02x:%02x", (h & 0b00011111), (m & 0b01111111), (s & 0b01111111));
				lcd_vidGotoRowColumn(0,0);
				lcd_vidDisplyStr("Time is: ");
				lcd_vidDisplyStr(buffer);
		}
   vTaskDelay(60);
	}


}

