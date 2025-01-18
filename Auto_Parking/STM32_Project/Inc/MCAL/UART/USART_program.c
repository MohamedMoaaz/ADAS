/**
* @file USART_program.c
* @author Mohamed Abd El-Naby (mahameda.naby@gmail.com) 
* @brief 
* @version 0.3
* @date 2022-11-16
*
*/
/******************************************************************************
* Includes
*******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "UTILS.h"
#include "../MCAL/GPIO/GPIO_interface.h"
#include "../MCAL/RCC/RCC_interface.h"
#include "USART_interface.h"
#include "USART_config.h"
#include "USART_private.h"










/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/




/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/
/*Transmit data register empty*/

#define WAIT_TO_TXE(USRTx)	while(!(CHECK_BIT(USRTx->ISR ,TXE )))
#define WAIT_TO_TXC(USRTx)	while(!(CHECK_BIT(USRTx->ISR ,TXC )))
#define WAIT_TO_RXNE(USRTx)	while(!((CHECK_BIT(USRTx->ISR ,RXNE))))


/******************************************************************************
* Typedefs
*******************************************************************************/




/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
static USART_Config *Global_USART_Config[3] = {NULL ,NULL,NULL};



/******************************************************************************
* Function Prototypes
*******************************************************************************/




/******************************************************************************
* Function Definitions
*******************************************************************************/
void USART_voidInit(USART_Number_t  USART_Number , USART_Config * usrConfig)
{
	u16 LOC_u16CR1 = 0 ;
	u16 LOC_u16CR2 = 0 ;
	u16 LOC_u16CR3 = 0 ;

/********************************************************* CR1 REG	****************************************************************/
	LOC_u16CR1 = (1<<0)									/*	Enable	*/
				|(usrConfig->USART_DataLength)			/*	Data Length	*/
				|(usrConfig->USART_Parity)				/*	 Parity control	*/
				|(usrConfig->USART_OperationMode)		/*	Tx,Rx or Tx and Rx*/
				|(usrConfig->USART_IRQ_t) ;
/*
	u8 LOC_u8Counter = 0 ;
	for(LOC_u8Counter = 0 ; LOC_u8Counter < 4 ;LOC_u8Counter++)
	{
		if(usrConfig->USART_IRQ_t[LOC_u8Counter] != (u8)NULL)
		{
			LOC_u16CR1 |= (usrConfig->USART_IRQ_t[LOC_u8Counter]) ;
		}
	}
*/
/******************************************************* CR2 REG ********************************************************************/
	LOC_u16CR2 = (usrConfig->USART_StopBit) 			/*	Number of Stop Bits	*/
				|(usrConfig->USART_IdleLevel)			/*	Clock polarity		*/
				|(usrConfig->USART_DataSampling);		/*	Clock phase			*/
/******************************************************* CR3 REG ********************************************************************/
	LOC_u16CR3 = (usrConfig->USART_DMA);			/*	DMA		*/

/******************************************************* BuadRate ********************************************************************/
	Global_USART_Config[USART_Number] = usrConfig ;
	u32 BRR_Reg = 0 ;
	USART_voidBuadRateCalc(usrConfig->USART_BuadRate , 8000000 , &BRR_Reg);


/******************************************************* Regs ********************************************************************/


	switch(USART_Number)
	{
	case USART_1 : USART1->BRR =  BRR_Reg  ; USART1->CR1 = LOC_u16CR1 ;  USART1->CR2 = LOC_u16CR2 , USART1->CR3 = LOC_u16CR3 ; 	break ;
	case USART_3 : USART3->BRR =  BRR_Reg  ; USART3->CR1 = LOC_u16CR1 ;  USART3->CR2 = LOC_u16CR2 , USART3->CR3 = LOC_u16CR3 ; 	break ;

	default : break ;

	}
}

void USART_voidSendDataSynch(USART_Number_t USART_Number , u16 *P_u16Data)
{
	switch(USART_Number)
	{
	case USART_1 :
		WAIT_TO_TXE(USART1)	;
		USART1->TDR = *P_u16Data ;
		WAIT_TO_TXC(USART1);
		break ;
	case USART_3 :
		WAIT_TO_TXE(USART3)	;
		USART3->TDR = *P_u16Data ;
		WAIT_TO_TXC(USART3);
		break ;
	default:
		break ;
	}
}

void USART_voidSendDataAsynch(USART_Number_t USART_Number , u16 *P_u16Data )
{
	*P_u16Data = *P_u16Data & 0x01FF ;
	switch(USART_Number)
	{
	case USART_1 :
		USART1->TDR = *P_u16Data ;
		break ;
	case USART_3 :
		USART3->TDR = *P_u16Data ;
		break ;
	default:
		break ;
	}
}

void USART_voidReceiveDataSynch(USART_Number_t USART_Number , u16 *P_u16Data)
{
	// 8-bit is parity
	switch(USART_Number)
	{
	case USART_1 :
		WAIT_TO_RXNE(USART1)	;
		*P_u16Data = (USART1->RDR)& ((u8)0xff) ;
		USART1->ICR = 0xffffffff;

		break ;
	case USART_3 :
		WAIT_TO_RXNE(USART3)	;
		*P_u16Data = (USART3->RDR)& ((u8)0xff) ;
		USART3->ICR = 0xffffffff;
		break ;
	default:
		break ;
	}
}

void USART_voidReceiveDataAsynch(USART_Number_t USART_Number)
{

}


void USART_voidBuadRateCalc(u32 BuadRate , u32 PClock , u32 *BRR_Reg)
{

	

	u32 USARTDEV = ((PClock)/(16*BuadRate)) ;
	u32 USARTDEV_Mull_100 = ((25.0 * PClock)/(4.0*BuadRate)) ;
	u32 Mantiessa_Mull_100 = USARTDEV * 100  ;
	u32 Mantiessa = USARTDEV ;
	u32 Fraction = ((USARTDEV_Mull_100 - Mantiessa_Mull_100)*16) /100 ;

	/*u32 Mantiessa = ((PClock)/(16*BuadRate)) ;
	u32 Fraction  = ((((1.0*PClock)/(16.0*BuadRate)) * 100) - (Mantiessa * 100)) * 16 ;
	*/
	if(Fraction > 16)
	{
		Mantiessa = Mantiessa+1 ;
	}
	*BRR_Reg = (u16) ((Mantiessa<<4) | (Fraction & 0x0F)) ;

}

void USART_voidSetPins(USART_Number_t USART_Number)
{
	if(USART_Number == USART_1)
	{
		RCC_voidEnableClock(RCC_AHB,PORTC);
		/*
		 * PC4 <-- TX
		 * PC5 <-- RX
		 */
		if(Global_USART_Config[USART_Number]->USART_OperationMode == USART_TRANSMIT)
		{
			/*		AF Function		*/
			GPIO_voidSetPinDirection(PORTC, PIN4, GPIO_AF_HIGH_SPD);
			GPIO_voidSetAFIO(PORTC, PIN4, AFIO_7) ;
		}
		else if (Global_USART_Config[USART_Number]->USART_OperationMode == USART_RECEIVE)
		{
			/*		AF Function		*/
			GPIO_voidSetPinDirection(PORTC, PIN6, GPIO_AF_HIGH_SPD);
			GPIO_voidSetAFIO(PORTC, PIN5,  AFIO_7) ;
		}
		else
		{
			// Tranciever
			/*		AF Function		*/
			GPIO_voidSetPinDirection(PORTC, PIN4, GPIO_AF_HIGH_SPD);
			GPIO_voidSetPinDirection(PORTC, PIN5, GPIO_AF_HIGH_SPD);
			GPIO_voidSetAFIO(PORTC, PIN4, AFIO_7) ;
			GPIO_voidSetAFIO(PORTC, PIN5,  AFIO_7) ;
		}
	}
	else if(USART_Number == USART_3)
	{
		RCC_voidEnableClock(RCC_AHB,PORTB);
		/*
		 * PB11 <-- USART3_RX
		 */
		GPIO_voidSetPinDirection(PORTB, PIN11, GPIO_AF_HIGH_SPD);
		GPIO_voidSetAFIO(PORTB, PIN11,  AFIO_7) ;
	}

}

void USART_voidGetDMA_PeripheralAddress(USART_Number_t USART_Number , u32* ptr_u32PeripheralAddress)
{
	u32 LOC_u32Result  ;

	switch(USART_Number)
	{
	case USART_1 : LOC_u32Result = (u32)(&(USART1->RDR)) ; break ;
	default : break ;
	}

	*ptr_u32PeripheralAddress =LOC_u32Result ;
}

void USART_voidSendStringWithFixedSizeSynch(USART_Number_t USART_Number , u8 *P_u8Data , u16 copy_u16BufferSize )
{
	u16 LOC_u16Counter = 0 ;
	for(LOC_u16Counter = 0 ; LOC_u16Counter < copy_u16BufferSize ; LOC_u16Counter++)
	{
		USART_voidSendDataSynch(USART_Number, (u16*)&P_u8Data[LOC_u16Counter]);
	}
}
void USART_voidSendStringWithDelimiterSynch(USART_Number_t USART_Number , u8 *P_u8Data , u8 copy_u16Delimiter )
{
	u32 LOC_u16Counter = 0 ;
	while (P_u8Data[LOC_u16Counter] != copy_u16Delimiter)
	{
		USART_voidSendDataSynch(USART_Number, (u16*)&P_u8Data[LOC_u16Counter]);
		LOC_u16Counter++ ;
	}
}

/************************************* ISR		*********************************************/
void USART1_EXTI25_IRQHandler(void)
{
	/*
	USART_IRQ_SRC irq_src;

	irq_src.USART_TXE  = ((USART1->SR & (1<<7)) >> 7);
	irq_src.USART_TXC  = ((USART1->SR & (1<<6)) >> 6);
	irq_src.USART_RXNE  = ((USART1->SR & (1<<5)) >> 5);
	irq_src.USART_PE	 = ((USART1->SR & (1<<0)) >> 0);
	if(Global_USART_Config[0]->P_IRQ_CallBack != NULL)
	{
		if(irq_src.USART_RXNE != 1)
		{
			Global_USART_Config[0]->P_IRQ_CallBack(NULL , irq_src);
		}
		else
		{
			Global_USART_Config[0]->P_IRQ_CallBack(USART1->DR , irq_src);

		}
	}
	*/
	Global_USART_Config[0]->P_IRQ_CallBack(USART1->RDR);
	//	Clear Fflags
	 USART1->ISR &=~ (1<<6) ; // TXC
	 USART1->ISR &=~  (1<<5) ; // RXNE

}
/************************************* End of File ******************************************/
