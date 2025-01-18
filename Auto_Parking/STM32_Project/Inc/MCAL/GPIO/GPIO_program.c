/**
* @file GPIO_program.c
* @author Mohamed Abd El-Naby (mahameda.naby@gmail.com) 
* @brief 
* @version 0.1
* @date 2022-10-25
*
*/
/******************************************************************************
* Includes
*******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "UTILS.h"
#include "GPIO_interface.h"
#include "GPIO_config.h"
#include "GPIO_private.h"










/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/




/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/




/******************************************************************************
* Typedefs
*******************************************************************************/




/******************************************************************************
* Module Variable Definitions
*******************************************************************************/




/******************************************************************************
* Function Prototypes
*******************************************************************************/

void GPIO_voidSetPinDirection	(u8 Copy_u8Port, Pin_t Copy_Pin , u8 Copy_u8Mode)
{

	u8 copy_u8Moder = 0, copy_OTYPER= 0 , copy_OSPEEDR = 0 , copy_PUPDR = 0  ;

	copy_u8Moder |= (CHECK_BIT(Copy_u8Mode,6)<<1) | CHECK_BIT(Copy_u8Mode,5) ;
	copy_OTYPER  |= CHECK_BIT(Copy_u8Mode,4);
	copy_OSPEEDR |= (CHECK_BIT(Copy_u8Mode,3)<<1) | CHECK_BIT(Copy_u8Mode,2) ;
	copy_PUPDR   |=(CHECK_BIT(Copy_u8Mode,1)<<1) | CHECK_BIT(Copy_u8Mode,0) ;
	switch(Copy_u8Port)
	{
		case PORTA :

			if (Copy_Pin <= PIN15 )
			{
				GPIOA->MODER &= ~(0b11 << (2*Copy_Pin)) ;
				GPIOA->OTYPER &= ~(1 << Copy_Pin );
				GPIOA->OSPEEDR &= ~ (0b11 << ( 2*Copy_Pin )) ;
				GPIOA->PUPDR  &= ~ (0b11<< (2*Copy_Pin));


				GPIOA->MODER |= (copy_u8Moder <<  (2*Copy_Pin));
				GPIOA->OTYPER |= (copy_OTYPER << Copy_Pin) ;
				GPIOA->OSPEEDR |= (copy_OSPEEDR << (2*Copy_Pin ) ) ;
				GPIOA->PUPDR  |= (copy_PUPDR<<   (2*Copy_Pin) );
			}
			else 
			{
				/* error */ 
			}
			break;
		case PORTB :
			if (Copy_Pin <= PIN15 )
			{

				GPIOB->MODER &= ~(0b11 << (2*Copy_Pin)) ;
				GPIOB->OTYPER &= ~(1 << Copy_Pin );
				GPIOB->OSPEEDR &= ~ (0b11 << ( 2*Copy_Pin )) ;
				GPIOB->PUPDR  &= ~ (0b11<< (2*Copy_Pin));

				GPIOB->MODER |= (copy_u8Moder << (2*Copy_Pin)) ;
				GPIOB->OTYPER |= (copy_OTYPER << Copy_Pin );
				GPIOB->OSPEEDR |= (copy_OSPEEDR << ( 2*Copy_Pin )) ;
				GPIOB->PUPDR  |= (copy_PUPDR<< (2*Copy_Pin));
			}
			else 
			{
				/* error */ 
			}
			break;
		case PORTC :
			if (Copy_Pin <= PIN15 )
			{
				GPIOC->MODER &= ~(0b11 << (2*Copy_Pin)) ;
				GPIOC->OTYPER &= ~(1 << Copy_Pin );
				GPIOC->OSPEEDR &= ~ (0b11 << ( 2*Copy_Pin )) ;
				GPIOC->PUPDR  &= ~ (0b11<< (2*Copy_Pin));

				GPIOC->MODER |= (copy_u8Moder <<  (2*Copy_Pin)) ;
				GPIOC->OTYPER |= (copy_OTYPER << Copy_Pin) ;
				GPIOC->OSPEEDR |= (copy_OSPEEDR << (2*Copy_Pin ) ) ;
				GPIOC->PUPDR  |= (copy_PUPDR<<   (2*Copy_Pin) );
			}
			else
			{
				/* error */
			}
			break ;
		case PORTD :
			if (Copy_Pin <= PIN15 )
			{

				GPIOD->MODER &= ~(0b11 << (2*Copy_Pin)) ;
				GPIOD->OTYPER &= ~(1 << Copy_Pin );
				GPIOD->OSPEEDR &= ~ (0b11 << ( 2*Copy_Pin )) ;
				GPIOD->PUPDR  &= ~ (0b11<< (2*Copy_Pin));

				GPIOD->MODER |= (copy_u8Moder <<  (2*Copy_Pin)) ;
				GPIOD->OTYPER |= (copy_OTYPER << Copy_Pin) ;
				GPIOD->OSPEEDR |= (copy_OSPEEDR << (2*Copy_Pin ) ) ;
				GPIOD->PUPDR  |= (copy_PUPDR<<   (2*Copy_Pin) );
			}
			else 
			{
				/* error */ 
			}
			break;
		default : break ;	
	}

}

void GPIO_voidSetPortDirection	(u8 Copy_u8Port, 				 u8 Copy_u8Mode)
{
	u8 copy_u8Moder = 0, copy_OTYPER= 0 , copy_OSPEEDR = 0 , copy_PUPDR = 0  ;
	copy_u8Moder |= (CHECK_BIT(Copy_u8Mode,6)<<1) | CHECK_BIT(Copy_u8Mode,5) ;
	copy_OTYPER  |= CHECK_BIT(Copy_u8Mode,4);
	copy_OSPEEDR |= (CHECK_BIT(Copy_u8Mode,3)<<1) | CHECK_BIT(Copy_u8Mode,2) ;
	copy_PUPDR   |=(CHECK_BIT(Copy_u8Mode,1)<<1) | CHECK_BIT(Copy_u8Mode,0) ;
	switch(Copy_u8Port)
	{

		case PORTA :
			GPIOA->MODER = 0 ;
			GPIOA->OTYPER = 0 ;
			GPIOA->OSPEEDR = 0 ;
			GPIOA->PUPDR = 0 ;
			for (u8 Copy_Pin = 0 ; Copy_Pin <= PIN15 ; Copy_Pin++)
			{
				if (Copy_Pin <= PIN15 )
				{
					/* 			RESET		*/
					GPIOA->MODER  &= (copy_u8Moder << 2*Copy_Pin) ;
					GPIOA->OTYPER  &=(copy_OTYPER << Copy_Pin) ;
					GPIOA->OSPEEDR  &= (copy_OSPEEDR << 2*Copy_Pin) ;
					GPIOA->PUPDR   &= (copy_PUPDR<< 2*Copy_Pin);

					GPIOA->MODER |= (copy_u8Moder <<  (2*Copy_Pin));
					GPIOA->OTYPER |= (copy_OTYPER << Copy_Pin) ;
					GPIOA->OSPEEDR |= (copy_OSPEEDR << (2*Copy_Pin ) ) ;
					GPIOA->PUPDR  |= (copy_PUPDR<<   (2*Copy_Pin) );
				}
				else
				{
					/* error */
				}
			}

			break;
		case PORTB:
			GPIOB->MODER = 0 ;
			GPIOB->OTYPER = 0 ;
			GPIOB->OSPEEDR = 0 ;
			GPIOB->PUPDR = 0 ;
			for (u8 Copy_Pin = 0 ; Copy_Pin <= PIN15 ; Copy_Pin++)
			{
				if (Copy_Pin <= PIN15 )
				{
					/* 			RESET		*/
					GPIOB->MODER  &= (copy_u8Moder << 2*Copy_Pin) ;
					GPIOB->OTYPER  &=(copy_OTYPER << Copy_Pin) ;
					GPIOB->OSPEEDR  &= (copy_OSPEEDR << 2*Copy_Pin) ;
					GPIOB->PUPDR   &= (copy_PUPDR<< 2*Copy_Pin);

					GPIOB->MODER |= (copy_u8Moder <<  (2*Copy_Pin));
					GPIOB->OTYPER |= (copy_OTYPER << Copy_Pin) ;
					GPIOB->OSPEEDR |= (copy_OSPEEDR << (2*Copy_Pin ) ) ;
					GPIOB->PUPDR  |= (copy_PUPDR<<   (2*Copy_Pin) );
				}
				else
				{
					/* error */
				}
			}

			break;
		case PORTC :
			GPIOC->MODER = 0 ;
			GPIOC->OTYPER = 0 ;
			GPIOC->OSPEEDR = 0 ;
			GPIOC->PUPDR = 0 ;
			for (u8 Copy_Pin = 0 ; Copy_Pin <= PIN15 ; Copy_Pin++)
			{
				if (Copy_Pin <= PIN15 )
				{
					/* 			RESET		*/
					GPIOC->MODER  &= (copy_u8Moder << 2*Copy_Pin) ;
					GPIOC->OTYPER  &=(copy_OTYPER << Copy_Pin) ;
					GPIOC->OSPEEDR  &= (copy_OSPEEDR << 2*Copy_Pin) ;
					GPIOC->PUPDR   &= (copy_PUPDR<< 2*Copy_Pin);

					GPIOC->MODER |= (copy_u8Moder <<  (2*Copy_Pin));
					GPIOC->OTYPER |= (copy_OTYPER << Copy_Pin) ;
					GPIOC->OSPEEDR |= (copy_OSPEEDR << (2*Copy_Pin ) ) ;
					GPIOC->PUPDR  |= (copy_PUPDR<<   (2*Copy_Pin) );
				}
				else
				{
					/* error */
				}
			}

			break;
		case PORTD :
			GPIOD->MODER = 0 ;
			GPIOD->OTYPER = 0 ;
			GPIOD->OSPEEDR = 0 ;
			GPIOD->PUPDR = 0 ;
			for (u8 Copy_Pin = 0 ; Copy_Pin <= PIN15 ; Copy_Pin++)
			{
				if (Copy_Pin <= PIN15 )
				{
					GPIOD->MODER |= (copy_u8Moder <<  (2*Copy_Pin));
					GPIOD->OTYPER |= (copy_OTYPER << Copy_Pin) ;
					GPIOD->OSPEEDR |= (copy_OSPEEDR << (2*Copy_Pin ) ) ;
					GPIOD->PUPDR  |= (copy_PUPDR<<   (2*Copy_Pin) );
				}
				else
				{
					/* error */
				}
			}

			break;
		default :  break ;
	}

}
void GPIO_voidSetPinValue(u8 Copy_u8Port, Pin_t Copy_Pin , u8 Copy_u8Value)
{
	//GPIOA->BSRR = 0x0000ffff;
	switch(Copy_u8Port)
	{
		case PORTA :		
			switch (Copy_u8Value)
			{
				case HIGH :
					GPIOA->BSRR = (1 << Copy_Pin);
					break ;
				case LOW  :	
					GPIOA->BRR = (1 << Copy_Pin);
					break ;
				default :
					/*error */ 
					break ; 
			}	
			break ; 
		case PORTB :
			switch (Copy_u8Value)
			{
				case HIGH :
					GPIOB->BSRR = (1 << Copy_Pin);
					break ;
				case LOW  :	
					GPIOB->BRR = (1 << Copy_Pin);
					break ;
				default :
					/*error */ 
					break ; 
			}			
			break ;
		case PORTC	:
			switch (Copy_u8Value)
			{
				case HIGH :
					GPIOC->BSRR = (1 << Copy_Pin);
					break ;
				case LOW  :	
					GPIOC->BRR = (1 << Copy_Pin);
					break ;
				default :
					/*error */ 
					break ; 
			}	
			break ;
			case PORTD	:
				switch (Copy_u8Value)
				{
					case HIGH :
						GPIOD->BSRR = (1 << Copy_Pin);
						break ;
					case LOW  :
						GPIOD->BRR = (1 << Copy_Pin);
						break ;
					default :
						/*error */
						break ;
				}
				break ;
		default :
		//error
			break ;
	}

}
void GPIO_voidSetPortValue		(u8 Copy_u8Port, u8 Copy_u8Value)
{
	switch(Copy_u8Port)
	{
		case PORTA :
			switch(Copy_u8Value)
			{
			case HIGH :
				GPIOA->ODR = 0b1111111111111111 ;
				break ;
			case LOW :
				GPIOA->ODR = 0b0000000000000000 ;
				break ;
			}
			break ;
		case PORTB :
			switch(Copy_u8Value)
			{
			case HIGH :
				GPIOB->ODR = 0b1111111111111111 ;
				break ;
			case LOW :
				GPIOB->ODR = 0b0000000000000000 ;
				break ;
			}
			break ;
		case PORTC :
			switch(Copy_u8Value)
			{
			case HIGH :
				GPIOC->ODR = 0b1111111111111111 ;
				break ;
			case LOW :
				GPIOC->ODR = 0b0000000000000000 ;
				break ;
			}
			break ;
			case PORTD :
				switch(Copy_u8Value)
				{
				case HIGH :
					GPIOD->ODR = 0b1111111111111111 ;
					break ;
				case LOW :
					GPIOD->ODR = 0b0000000000000000 ;
					break ;
				}
				break ;
		default :
			/** 		error 		**/
		break ;
	}

}
void GPIO_voidTogglePinValue	(u8 Copy_u8Port, Pin_t Copy_Pin)
{
	switch(Copy_u8Port){
		case PORTA :
			FLIP_BIT(GPIOA->ODR , Copy_Pin ) ;

			break ;
		case PORTB :
			FLIP_BIT(GPIOB->ODR , Copy_Pin ) ;

			break ;
		case PORTC :
			FLIP_BIT(GPIOC->ODR , Copy_Pin ) ;
			break ;
		case PORTD :
			FLIP_BIT(GPIOD->ODR , Copy_Pin ) ;
			break ;
		default :
			/* error */
			break ;

	}


}

u8 GPIO_u8GetPinValue (u8 Copy_u8Port, Pin_t Copy_Pin)
{
	u8 LOC_u8Result = 0;
	if(Copy_Pin > 15)
	{
		/* error */
	}
	switch(Copy_u8Port)
	{
		case PORTA :
			LOC_u8Result  = CHECK_BIT(GPIOA->IDR , Copy_Pin ) ;
			break ;
		case PORTB :
			LOC_u8Result  = CHECK_BIT(GPIOB->IDR , Copy_Pin ) ;
			break ;
		case PORTC :
			LOC_u8Result  = CHECK_BIT(GPIOC->IDR , Copy_Pin ) ;
			break ;
		case PORTD :
			LOC_u8Result  = CHECK_BIT(GPIOD->IDR , Copy_Pin ) ;
			break ;
		default :
			/* error */
			break ;
	}
	return LOC_u8Result ;
}

void GPIO_voidSetAFIO(u8 Copy_u8Port, Pin_t Copy_Pin ,AFR_t AFRy)
{
	switch(Copy_u8Port)
	{
		case PORTA :
			if(Copy_Pin <= PIN7)
			{
				/* 			RESET		*/
				GPIOA->AFRL |= (AFRy << Copy_Pin*4) ;
			}
			else if (Copy_Pin <= PIN15 )
			{
				GPIOA->AFRH |= (AFRy << (Copy_Pin-8)*4) ;
			}
			else
			{
				/* error */
			}
			break ;
		case PORTB :
			if(Copy_Pin <= PIN7)
			{
				/* 			RESET		*/
				GPIOB->AFRL |= (AFRy << Copy_Pin*4) ;
			}
			else if (Copy_Pin <= PIN15 )
			{
				GPIOB->AFRH |= (AFRy << (Copy_Pin-8)*4) ;
			}
			else
			{
				/* error */
			}
			break ;
		case PORTC :
			if(Copy_Pin <= PIN7)
			{
				/* 			RESET		*/
				GPIOC->AFRL |= (AFRy << Copy_Pin*4) ;
			}
			else if (Copy_Pin <= PIN15 )
			{
				GPIOC->AFRH |= (AFRy << (Copy_Pin-8)*4) ;
			}
			else
			{
				/* error */
			}
			break ;
		case PORTD :
			if(Copy_Pin <= PIN7)
			{
				/* 			RESET		*/
				GPIOD->AFRL |= (AFRy << Copy_Pin*4) ;
			}
			else if (Copy_Pin <= PIN15 )
			{
				GPIOD->AFRH |= (AFRy << (Copy_Pin-8)*4) ;
			}
			else
			{
				/* error */
			}
			break ;
		default :
			/* error */
			break ;
	}}
/******************************************************************************
* Function Definitions
*******************************************************************************/




/************************************* End of File ******************************************/
