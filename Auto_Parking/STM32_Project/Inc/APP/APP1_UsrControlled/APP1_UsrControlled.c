/*
 * C6_BTLCTRL.c
 *
 *  Created on: Sep 29, 2023
 *      Author: Abnaby
 */

#include "STD_TYPES.h"
#include "UTILS.h"
#include "BIT_MATH.h"
#include "RCC/RCC_interface.h"
#include "UART/USART_interface.h"

#include "C2_VCLE_CNTRL/C2_VCLE_CNTRL.h"
#include "APP1_UsrControlled.h"

static USART_Config _APP1_UART1_ ;


void APP1_voidSetup(void)
{
	// Clock of UART1
	RCC_voidEnableClock(RCC_APB2,14 );		/*	USART1	*/
	/******************* GPIO AFIOs	**********************************/
	USART_voidSetPins(USART_1);
	/******************* USART INIT	******************************/
	_APP1_UART1_.USART_OperationMode = USART_TRANCIVER ;
	_APP1_UART1_.USART_BuadRate = 9600 ;
	_APP1_UART1_.USART_DataLength = USART_8BIT ;
	_APP1_UART1_.USART_Parity =USART_DISABLE_PARITY ;
	_APP1_UART1_.USART_StopBit = USART_1_STOPBIT ;
	_APP1_UART1_.USART_HWFlowControl = USART_HW_FLOW_CONTROLLED_DISALBED ;
	_APP1_UART1_.USART_IdleLevel     = USART_ASYNC ;
	_APP1_UART1_.USART_DataSampling  = USART_ASYNC ;
	_APP1_UART1_.USART_DMA = DMA_DISABLE ;
	_APP1_UART1_.P_IRQ_CallBack = NULL ;
	_APP1_UART1_.USART_IRQ_t = USART_DISABLE_IRQs ;
	USART_voidInit(USART_1, &_APP1_UART1_);


	/*************** Init Used Services ***************************/
	C2VCONTROL_voidInit();


}
void APP1_voidControlVehcileThroughBTL(VehicleStates_t *copy_xSystemState)
{
	u16 rxData = 0 ;
	static u8 LOC_u8defaultSpeed;

	while(*copy_xSystemState == USR_CONTROLLED)
	{
		// Get Data
		USART_voidReceiveDataSynch(USART_1,  &rxData);

		// Check Data
	    if((u8)(u8)rxData == 'F')
	    {
	      // Forward
	    	C2VCONTROL_voidChangeDirection(VCLE_FWD, LOC_u8defaultSpeed);;
	    }
	    else if((u8)(u8)rxData == 'B')
	    {
	      // Backward
	    	C2VCONTROL_voidChangeDirection(VCLE_BWD, LOC_u8defaultSpeed);;
	    }
	    else if((u8)(u8)rxData == 'R')
	    {
	    	C2VCONTROL_voidChangeDirection(VCLE_LEFT_FWD, 0);
	    }
	    else if((u8)(u8)rxData == 'L')
	    {
	      // Left
	    	C2VCONTROL_voidChangeDirection(VCLE_RIGHT_FWD, 0);
	    }
	    else if((u8)rxData == 'I')
	    {
	      // FWD Right
	    	C2VCONTROL_voidChangeDirection(VCLE_LEFT_FWD, LOC_u8defaultSpeed);

	    }
	    else if ((u8)rxData == 'G')
	    {
	      // FWD Left
	    	C2VCONTROL_voidChangeDirection(VCLE_RIGHT_FWD, LOC_u8defaultSpeed);

	    }
	    else if ((u8)rxData == 'H')
	    {
	      // Back Left
	    	C2VCONTROL_voidChangeDirection(VCLE_LEFT_BWD, LOC_u8defaultSpeed);

	    }
	    else if ((u8)rxData == 'J')
	    {
	      // Back RIGHT
	    	C2VCONTROL_voidChangeDirection(VCLE_RIGHT_BWD, LOC_u8defaultSpeed);

	    }
	    else if ((u8)rxData == 'X')
	    {
	      // Parking State On
	    	*copy_xSystemState = PARKING_MODE ;
	    	break ;
	    }
	    else if ((u8)rxData == 'V')
	    {
	      // Parking State On
	    	*copy_xSystemState =  TF_START_V2I;
	    	break ;
	    }
	    else if ((u8)rxData == '1')
	    {
	      LOC_u8defaultSpeed = 50 ;
	    }
	    else if ((u8)rxData == '2')
	    {
	      LOC_u8defaultSpeed = 100 ;
	    }
	    else if ((u8)rxData == '3')
	    {
	      LOC_u8defaultSpeed = 150 ;
	    }
	    else if ((u8)rxData == '4')
	    {
	      LOC_u8defaultSpeed = 200 ;
	    }
	    else if ((u8)rxData == '5')
	    {
	      LOC_u8defaultSpeed = 210 ;
	    }
	    else if ((u8)rxData == '6')
	    {
	      LOC_u8defaultSpeed = 220 ;
	    }
	    else if ((u8)rxData == '7')
	    {
	      LOC_u8defaultSpeed = 230 ;
	    }
	    else if ((u8)rxData == '8')
	    {
	      LOC_u8defaultSpeed = 240 ;
	    }
	    else if ((u8)rxData == '9')
	    {
	      LOC_u8defaultSpeed = 250 ;
	    }
	        else if ((u8)rxData == 'q')
	    {
	      LOC_u8defaultSpeed = 255 ;
	    }
	    else
	    {
	      // S or anything else
	    	C2VCONTROL_voidChangeDirection(VCLE_STOP, LOC_u8defaultSpeed);

	    }
	}

	// To Exit From Unparking Mode
    if ((u8)rxData == 'x')
    {
      // Parking State Off
    	*copy_xSystemState = USR_CONTROLLED ;
    }
}



