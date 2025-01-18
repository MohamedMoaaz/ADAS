/*
 * C6_TrafficLight_V2I.c
 *
 *  Created on: Oct 4, 2023
 *      Author: Abnaby
 */

// libs
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "LIB/UTILS.h"
#include "LIB/SW_Delay.h"
#include "main.h"

#include "MCAL/RCC/RCC_interface.h"
#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/UART/USART_interface.h"
#include "C2_VCLE_CNTRL/C2_VCLE_CNTRL.h"
#include "C6_TrafficLight_V2I.h"

#define TL_ON_STATE 		50
#define TL_OFF_STATE 		25

#define TL_AUTO_SPD			150


USART_Config _V2I_UART_PORT_ ;


void C6TL_voidTrafficV2I_init(void)
{
	RCC_voidEnableClock(RCC_APB1,18);		/*	USART3	*/
	USART_voidSetPins(USART_3);
	_V2I_UART_PORT_.USART_OperationMode = USART_RECEIVE;
	_V2I_UART_PORT_.USART_BuadRate = 9600 ;
	_V2I_UART_PORT_.USART_DataLength = USART_8BIT ;
	_V2I_UART_PORT_.USART_Parity =USART_DISABLE_PARITY ;
	_V2I_UART_PORT_.USART_StopBit = USART_1_STOPBIT ;
	_V2I_UART_PORT_.USART_HWFlowControl = USART_HW_FLOW_CONTROLLED_DISALBED ;
	_V2I_UART_PORT_.USART_IdleLevel     = USART_ASYNC ;
	_V2I_UART_PORT_.USART_DataSampling  = USART_ASYNC ;
	_V2I_UART_PORT_.USART_DMA = DMA_DISABLE ;
	_V2I_UART_PORT_.P_IRQ_CallBack = NULL ;
	_V2I_UART_PORT_.USART_IRQ_t = USART_DISABLE_IRQs ;
	USART_voidInit(USART_3, &_V2I_UART_PORT_);
}

void C6TL_voidStartV2I(VehicleStates_t *ptr2VehivleState)
{
	while(*ptr2VehivleState == TF_START_V2I)
	{
		u16 LOC_u16CommingData = 0;
		// Vehcile Start Moving FWD

		// Get Data
		USART_voidReceiveDataSynch(USART_1,  &LOC_u16CommingData);
		// Check Communication
		switch(LOC_u16CommingData)
		{
		case TL_ON_STATE :
			C2VCONTROL_voidChangeDirection(VCLE_FWD, TL_AUTO_SPD);
			break ;
		case TL_OFF_STATE:
			C2VCONTROL_voidChangeDirection(VCLE_FWD, 0);
			break ;
		default:
			// Hacking
			C2VCONTROL_voidChangeDirection(VCLE_STOP, 0);
			*ptr2VehivleState = USR_CONTROLLED;
			break ;
		}


	}
}
