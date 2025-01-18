/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  dio.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "dio.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void dio_vidConfigChannel
						(dio_port_t port, dio_pin_t pin, dio_direction_t direction)        
* \Description     : this service for configuring IO channel                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : port 	   -> MC port ID
					 channel   -> MC channel ID
					 direction -> MC channel direction
* \Return value:   : None                            
*******************************************************************************/
void dio_vidConfigChannel(dio_portId_t port, dio_channelId_t channel, dio_direction_t direction)
{
	switch (port)
	{
	case DIO_PORTA:
		if (direction == OUTPUT)
		{
			SET_BIT (DIO_DDRA_REG,channel);
		}
		else
		{
			CLR_BIT (DIO_DDRA_REG,channel);
			CLR_BIT (DIO_PORTA_REG,channel);
		}
		break;

	case DIO_PORTB:
		if (direction == OUTPUT)
		{
			SET_BIT (DIO_DDRB_REG,channel);
			
		}
		else
		{
			CLR_BIT (DIO_DDRB_REG,channel);
			CLR_BIT (DIO_PORTB_REG,channel);
		}
		break;

	case DIO_PORTC:
		if (direction == OUTPUT)
		{
			SET_BIT (DIO_DDRC_REG,channel);
		}
		else
		{
			CLR_BIT (DIO_DDRC_REG,channel);
			CLR_BIT (DIO_PORTC_REG,channel);
		}
		break;

	case DIO_PORTD:
		if (direction == OUTPUT)
		{
			SET_BIT (DIO_DDRD_REG,channel);
			
		}
		else
		{
			CLR_BIT (DIO_DDRD_REG,channel);
			CLR_BIT (DIO_PORTD_REG,channel);
		}
		break;
	}
}

/******************************************************************************
* \Syntax          : void dio_vidWriteChannel
						(dio_portId_t port, dio_channelId_t channel, dio_level_t level)      
* \Description     : this service for writting on IO channel                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : port 	  -> MC port ID
					 channel  -> MC channel ID
					 level    -> MC channel level
* \Return value:   : None                            
*******************************************************************************/
void dio_vidWriteChannel(dio_portId_t port, dio_channelId_t channel, dio_level_t level)
{
	switch (port)
	{
	case DIO_PORTA:
		if (level == STD_LOW)
		{
			CLR_BIT(DIO_PORTA_REG,channel);
		}
		else
		{
			SET_BIT(DIO_PORTA_REG,channel);
		}
		break;

	case DIO_PORTB:
		if (level == STD_LOW)
		{
			CLR_BIT(DIO_PORTB_REG,channel);
		}
		else
		{
			SET_BIT(DIO_PORTB_REG,channel);
		}
		break;

	case DIO_PORTC:
		if (level == STD_LOW)
		{
			CLR_BIT(DIO_PORTC_REG,channel);
		}
		else
		{
			SET_BIT(DIO_PORTC_REG,channel);
		}
		break;

	case DIO_PORTD:
		if (level == STD_LOW)
		{
			CLR_BIT(DIO_PORTD_REG,channel);
		}
		else
		{
			SET_BIT(DIO_PORTD_REG,channel);
		}
		break;
	}
}

/******************************************************************************
* \Syntax          :void dio_vidWriteChannelGroup
						(dio_portId_t port,u8 value,u8 mask)
* \Description     : this service for writting on group of IO channels                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : port  -> MC port ID
					 value -> data value
					 mask  -> data mask
* \Return value:   : None                            
*******************************************************************************/
void dio_vidWriteChannelGroup(dio_portId_t port,u8 value,u8 mask)
{
	/*******************	Example ************************/
	// Value				0b00010100 
	// MASK					0b00011110
	
	// Val&Mask				0b00010100
	// PORTA |= Resut		0bxxx1010x
	/*******************************************************/
	switch (port)
	{
	case DIO_PORTA:
		// Clear Bits 
		DIO_PORTA_REG &= ~(mask);				// PORTA 0bxxx0000x
		// Set Values by Mask 
		DIO_PORTA_REG |= (value & mask); 
		break;

	case DIO_PORTB:
		// Clear Bits 
		DIO_PORTB_REG &= ~(mask);			
		// Set Values by Mask 
		DIO_PORTB_REG |= (value & mask);
		break;

	case DIO_PORTC:
		// Clear Bits 
		DIO_PORTC_REG &= ~(mask);			
		// Set Values by Mask 
		DIO_PORTC_REG |= (value & mask);
		break;

	case DIO_PORTD:
		// Clear Bits 
		DIO_PORTD_REG &= ~(mask);			
		// Set Values by Mask 
		DIO_PORTD_REG |= (value & mask);
		break;
	}
}

/******************************************************************************
* \Syntax          :void dio_vidFlipChannel
						(dio_portId_t port, dio_channelId_t channel)
* \Description     : this service for fliping IO channel                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : port  -> MC port ID
					 channel  -> MC channel ID
* \Return value:   : None                            
*******************************************************************************/
void dio_vidFlipChannel(dio_portId_t port, dio_channelId_t channel)
{
	switch (port)
	{
	case DIO_PORTA:
		TOG_BIT(DIO_PORTA_REG,channel);
		break;

	case DIO_PORTB:
		TOG_BIT(DIO_PORTB_REG,channel);
		break;

	case DIO_PORTC:
		TOG_BIT(DIO_PORTC_REG,channel);
		break;

	case DIO_PORTD:
		TOG_BIT(DIO_PORTD_REG,channel);
		break;
	}
}

/******************************************************************************
* \Syntax          :dio_level_t Dio_dioLevelReadChannel
						(dio_portId_t port, dio_channelId_t channel)
* \Description     : this service for reading IO channel                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : port     -> MC port ID
					 channel  -> MC channel ID
* \Return value:   : loc_pinRead   -> IO channel level                           
*******************************************************************************/
dio_level_t dio_dioLevelReadChannel(dio_portId_t port, dio_channelId_t channel)
{
	/*	show me your code */
	dio_level_t LOC_u8PinValue = STD_HIGH; 
	// Check Input Range
	if(channel >= DIO_PIN0 && channel <= DIO_PIN7)
	{
		switch(port)
		{
			case DIO_PORTA :
				LOC_u8PinValue =   CHECK_BIT(DIO_PINA_REG,channel);
				break ;
			case DIO_PORTB : 
				LOC_u8PinValue =   CHECK_BIT(DIO_PINB_REG,channel);
				break ;
			case DIO_PORTC :
				LOC_u8PinValue =   CHECK_BIT(DIO_PINC_REG,channel);
				break ;
			case DIO_PORTD :
				LOC_u8PinValue =   CHECK_BIT(DIO_PIND_REG,channel);
				break ;
			default : break;
		}
	}
	return LOC_u8PinValue; 
}

/******************************************************************************
* \Syntax          :void dio_vidEnablePullUp
						(dio_portId_t port, dio_channelId_t channel)
* \Description     : this service for enabling pull up resistor for IO channel                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : port  -> MC port ID
					 channel  -> MC channel ID
* \Return value:   : None                            
*******************************************************************************/
void dio_vidEnablePullUp(dio_portId_t port, dio_channelId_t channel)
{
	/*	show me your code */
	// Check Input Range
	if(channel >= DIO_PIN0 && channel <= DIO_PIN7)
	{
		switch(port)
		{
			case DIO_PORTA :
					/* SET PORTxn	*/
					SET_BIT (DIO_PORTA_REG,channel);
				break ;
			case DIO_PORTB : 
				SET_BIT (DIO_PORTB_REG,channel);
				break ;
			case DIO_PORTC :
				SET_BIT (DIO_PORTC_REG,channel);
				break ;
			case DIO_PORTD :
				SET_BIT (DIO_PORTD_REG,channel);
				break ;
			default : break;
		}
	}	
}
/**********************************************************************************************************************
 *  END OF FILE: dio.c
 *********************************************************************************************************************/
