/**
* @file GPIO_interface.h
* @author Mohamed Abd El-Naby (mahameda.naby@gmail.com) 
* @brief 
* @version 0.1
* @date 2022-10-25
*
*/
#ifndef GPIO_INTERFACE_H 
#define GPIO_INTERFACE_H 




/******************************************************************************
* Includes
*******************************************************************************/
#include "UTILS.h"



/******************************************************************************
* Preprocessor Constants
 *******************************************************************************/




/******************************************************************************
* Configuration Constants
*******************************************************************************/




/******************************************************************************
* Macros
*******************************************************************************/


		/*			PORT OUTPUT BIT CONFIGURATION  					*/


/*											MODR(2)	OTYPER(1)	OSPEEDR(2)		PUDR(2)		*/
// Push Pulll With Speeds
#define GPIO_OUTPUT_LOW_SPD_PUSH_PULL			0b00100000
#define GPIO_OUTPUT_LOW_SPD_PUSH_PULL_PU		0b00100001
#define GPIO_OUTPUT_LOW_SPD_PUSH_PULL_PD		0b00100010

#define GPIO_OUTPUT_MED_SPD_PUSH_PULL			0b00100100
#define GPIO_OUTPUT_MED_SPD_PUSH_PULL_PU		0b00100101
#define GPIO_OUTPUT_MED_SPD_PUSH_PULL_PD		0b00100110

#define GPIO_OUTPUT_HIGH_SPD_PUSH_PULL			0b00101100
#define GPIO_OUTPUT_HIGH_SPD_PUSH_PULL_PU		0b00101101
#define GPIO_OUTPUT_HIGH_SPD_PUSH_PULL_PD		0b00101110


// Opendrain with speeds

#define GPIO_OUTPUT_LOW_SPD_OPEN_DRAIN			0b00110000
#define GPIO_OUTPUT_LOW_SPD_OPEN_DRAIN_PU		0b00110001
#define GPIO_OUTPUT_LOW_SPD_OPEN_DRAIN_PD		0b00110010

#define GPIO_OUTPUT_MED_SPD_OPEN_DRAIN			0b00110100
#define GPIO_OUTPUT_MED_SPD_OPEN_DRAIN_PU		0b00110101
#define GPIO_OUTPUT_MED_SPD_OPEN_DRAIN_PD		0b00110110

#define GPIO_OUTPUT_HIGH_SPD_OPEN_DRAIN			0b00111100
#define GPIO_OUTPUT_HIGH_SPD_OPEN_DRAIN_PU		0b00111101
#define GPIO_OUTPUT_HIGH_SPD_OPEN_DRAIN_PD		0b00111110


// AF
#define GPIO_AF_LOW_SPD					0b01000000
#define GPIO_AF_LOW_SPD_PU				0b01010001
#define GPIO_AF_LOW_SPD_PD				0b01010010

#define GPIO_AF_MED_SPD					0b01000100
#define GPIO_AF_MED_SPD_PU				0b01010101
#define GPIO_AF_MED_SPD_PD				0b01010110

#define GPIO_AF_HIGH_SPD				0b01001100
#define GPIO_AF_HIGH_SPD_PU				0b01011101
#define GPIO_AF_HIGH_SPD_PD				0b01011110


// Inputs
#define GPIO_DIGITAL_INPUT_FLOAT				0b00000000
#define GPIO_DIGITAL_INPUT_PU					0b00000001
#define GPIO_DIGITAL_INPUT_PD					0b00000010
#define GPIO_ANALOG_INPUT						0b00000010




/******************************************************************************
* Typedefs
*******************************************************************************/


// For NUCLEO - F303RE
typedef enum
{
	AFIO_0	,
	AFIO_1	,
	AFIO_2	,
	AFIO_3	,
	AFIO_4	,
	AFIO_5	,
	AFIO_6	,
	AFIO_7	,
	AFIO_8	,
	AFIO_9	,
	AFIO_10	,
	AFIO_11	,
	AFIO_12	,
	AFIO_13	,
	AFIO_14	,
	AFIO_15
}AFR_t;


/******************************************************************************
* Variables
*******************************************************************************/




/******************************************************************************
* Function Prototypes
*******************************************************************************/

void GPIO_voidInit	(void);
/**
 * @brief Set Direction of Pin
 * 
 * @param Copy_u8Port   PORTA,PORTB,PORTC
 * @param Copy_u8Pin    PIN0 : PIN7
 * @param Copy_u8Mode   Select Mode Of Operation
 */
void GPIO_voidSetPinDirection	(u8 Copy_u8Port, Pin_t Copy_u8Pin , u8 Copy_u8Mode);

/**
 * @brief Set Direction of Port
 * 
 * @param Copy_u8Port   PORTA,PORTB,PORTC
 * @param Copy_u8Mode   Select Mode Of Operation
 */
void GPIO_voidSetPortDirection	(u8 Copy_u8Port, 				 u8 Copy_u8Mode);

/**
 * @brief Set Pin Value
 *  
 * @param Copy_u8Port PORTA,PORTB,PORTC
 * @param Copy_u8Pin  PIN0 : PIN7
 * @param Copy_u8Value HIGH/LOW
 */
void GPIO_voidSetPinValue(u8 Copy_u8Port, Pin_t Copy_u8Pin , u8 Copy_u8Value);
/**
 * @brief Set PORT Value
 *  
 * @param Copy_u8Port PORTA,PORTB,PORTC
 * @param Copy_u8Value HIGH/LOW
 */
void GPIO_voidSetPortValue		(u8 Copy_u8Port, u8 Copy_u8Value);
/**
 * @brief toggle pin Value
 *
 * @param Copy_u8Port PORTA,PORTB,PORTC
 * @param Copy_u8Pin  PIN0 : PIN7
 */
void GPIO_voidTogglePinValue	(u8 Copy_u8Port, Pin_t Copy_Pin);

/**
 * @brief GET PIN VALUE
 *
 * @param Copy_u8Port PORTA,PORTB,PORTC
 * @param Copy_u8Pin  PIN0 : PIN7
 */
u8 GPIO_u8GetPinValue (u8 Copy_u8Port, Pin_t Copy_Pin);


void GPIO_voidSetAFIO(u8 Copy_u8Port, Pin_t Copy_Pin ,AFR_t AFRy);

#endif
/************************************* End of File ******************************************/
