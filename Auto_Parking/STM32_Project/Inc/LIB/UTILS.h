/**************************************************************************/
/* Author	: Mohamed                                                 */
/* Date		: 28 OCT 2022                                             */
/* Version	: V02							  */
/**************************************************************************/
#ifndef COMMON_H
#define COMMON_H

/************************	PORTS	**********************************/

#define PORTA	17
#define PORTB	18
#define PORTC	19
#define PORTD	20
typedef enum
{
	Timer2 =	0	,
    Timer3 =	1	,
	Timer4 =    2    ,
	Timer17=	18
}TIMx_t;

/************************	PINS	**********************************/
typedef enum
{
	PIN0 = 0 , 
	PIN1  , 
	PIN2  , 
	PIN3  , 
	PIN4  , 
	PIN5  , 
	PIN6  , 
	PIN7  , 
	PIN8  , 
	PIN9  , 
	PIN10 , 
	PIN11 , 
	PIN12 , 
	PIN13 , 
	PIN14 , 
	PIN15  
}Pin_t;

/************************* LOGIC ****************************************/
#define	HIGH								1
#define LOW									0

/*************************	TIMERS	*****************************************/
typedef enum
{
    CHANNEL_1 = 0 ,
    CHANNEL_2,
    CHANNEL_3,
    CHANNEL_4
}Channel_ID_t ;

/************************ Auto Parking System Errors	***************************/
typedef enum
{
	ERR_FRONT_US_FAILED,
	ERR_BACK_US_FAILED	,
	ERR_FRONT_RIGHT_US_FAILED,
	ERR_REAR_RIGHT_US_FAILED,
	NO_SLOT,
	PARKING_FAILED,
	E_OK
}ERROR_t;


#endif
