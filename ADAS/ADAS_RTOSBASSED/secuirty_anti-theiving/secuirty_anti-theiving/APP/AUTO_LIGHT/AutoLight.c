/*
 * AutoLight.c
 *
 * Created: 9/15/2023 8:22:11 PM
 *  Author: youssef rashad
 */ 
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "AutoLight.h"
/**********************************************************************************************************************
*  GLOBAL FUNCTIONS
*********************************************************************************************************************/

/******************************************************************************
* \Syntax          : Func_Stat_t AutoLight_Func_StatSetup()
* \Description     : Setups components initialization in Automatic lightning system
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : None
* \Return value:   : Func_Stat_t  Func_StatOk
*                                    Func_StatNotOk
*******************************************************************************/
#include "../main.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
extern SemaphoreHandle_t  LCDSemaphore;
void AutoLight_Func_StatSetup()
{

	dio_vidConfigChannel(AutoLight_LED_Port,AutoLight_LED_Pin,OUTPUT);

	//return retstat;
}

/******************************************************************************
* \Syntax          : Func_Stat_t AutoLight_Func_StatSetup()
* \Description     : Reads LDR value and Sets LED if LDR value above threshold in Automatic lightning system
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non-Reentrant
* \Parameters (in) : None
* \Return value:   : Func_Stat_t  Func_StatOk
*                                    Func_StatNotOk
*******************************************************************************/
u8 AutoLight_Glob_AutoLight_Prev_State = 0;
u8 AutoLight_Glob_AutoLight_Current_State = 0;
u8 AutoLight_Glob_Light_flag;
AutoLight_Stat_t AutoLight_Glob_Retstat = Led_OFF;
extern u8 contactor_state;
void AutoLight_Func_StatLoop(void *pvParameters)
{
	u16 Loc_AutoLight_Read;
	while(1)
	{
		if (Get_VIDContactState()==1)
		{
			Loc_AutoLight_Read = LDR_u16Read();
			if (Loc_AutoLight_Read > AutoLight_LDR_threshold)
			{
				dio_vidWriteChannel(AutoLight_LED_Port,AutoLight_LED_Pin,STD_HIGH);
				xSemaphoreTake(LCDSemaphore,100);
				lcd_vidGotoRowColumn(2,0);
				lcd_vidDisplyStr("Light Activated");
				xSemaphoreGive(LCDSemaphore);
				AutoLight_Glob_Retstat = Led_ON;

			}
			else
			{
				xSemaphoreTake(LCDSemaphore,100);
				dio_vidWriteChannel(AutoLight_LED_Port,AutoLight_LED_Pin,STD_LOW);	
				lcd_vidGotoRowColumn(2,0);
				xSemaphoreGive(LCDSemaphore);
				lcd_vidDisplyStr("Light De-Activated");
				AutoLight_Glob_Retstat = Led_OFF;
			}
		}
	}
	
	
	/*lcd_vidClrDislay();*/
	
}