/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  FileName.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "lcd.h"
#include "../../LIB/std_types.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
u8 customChar[NO_CSTOM_CHAR][NO_CSTOM_CHAR_BYTES]=
{
	{0x0A,0x1F,0x1F,0x1F,0x1F,0x0E,0x04,0x00},	/* Heart symbol	 */
	{0x04,0x1F,0x11,0x11,0x11,0x11,0x11,0x1F},	/* Empty battery */
	{0x04,0x1F,0x11,0x11,0x11,0x11,0x1F,0x1F},	/*	20% battery  */
	{0x04,0x1F,0x11,0x11,0x11,0x1F,0x1F,0x1F},  /*	40% battery  */
	{0x04,0x1F,0x11,0x11,0x1F,0x1F,0x1F,0x1F},	/*	60% battery  */
	{0x04,0x1F,0x11,0x1F,0x1F,0x1F,0x1F,0x1F},	/*	80% battery  */
	{0x04,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F},	/*	100% battery */
	{0x00,0x00,0x01,0x01,0x05,0x05,0x15,0x15},	/*	Mobile Signal*/
};
u8 buffer[6];
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
//extern u8 customChar[NO_CSTOM_CHAR][NO_CSTOM_CHAR_BYTES];
static void enablePulse(void);
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : void enablePulse(void)        
* \Description     : send enable pulse to LCD HW                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                                                                        
* \Return value:   : None                                 
*******************************************************************************/

static void enablePulse(void)
{
	dio_vidWriteChannel(LCD_EN_PORT, LCD_EN_CHANNEL, STD_HIGH);
	_delay_us(1);
	dio_vidWriteChannel(LCD_EN_PORT, LCD_EN_CHANNEL, STD_LOW);
	_delay_ms(2);
}
/******************************************************************************
* \Syntax          : void lcd_vidTransferNumToChar(number)
* \Description     : transfer numbers to array of charachers
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : u16
* \Return value:   : None
*******************************************************************************/
static void  lcd_vidTransferNumToChar(u16 number)
{
	for(int index=0;index<6;index++)
	{
		buffer[index]=0;
	}
	u8 temp;
	if (number<0)
	{
		number *=-1;
	}
	else
	{
		if (number<10)
		{
			buffer[0]=number+'0';
		}
		else if (number<100)
		{
			temp=number/10;
			buffer[0]=temp+'0';
			temp=number%10;
			buffer[1]=temp+'0';
		}
		else if (number<1000)
		{
			buffer[2]=(number%10)+'0';
			number/=10;
			buffer[1]=(number%10)+'0';
			number/=10;
			buffer[0]=(number%10)+'0';
		}
		else if (number<10000)
		{
			buffer[3]=(number%10)+'0';
			number/=10;
			buffer[2]=(number%10)+'0';
			number/=10;
			buffer[1]=(number%10)+'0';
			number/=10;
			buffer[0]=(number%10)+'0';
		}
		else if (number<100000)
		{
			buffer[4]=(number%10)+'0';
			number/=10;
			buffer[3]=(number%10)+'0';
			number/=10;
			buffer[2]=(number%10)+'0';
			number/=10;
			buffer[1]=(number%10)+'0';
			number/=10;
			buffer[0]=(number%10)+'0';
		}
	}
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void lcd_init(void)        
* \Description     : initialize LCD HW                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                                                                        
* \Return value:   : None                                 
*******************************************************************************/
void lcd_vidInit(void)
{
	dio_vidConfigChannel(LCD_RS_PORT, LCD_RS_CHANNEL, OUTPUT);
	dio_vidConfigChannel(LCD_EN_PORT, LCD_EN_CHANNEL, OUTPUT);

	dio_vidConfigChannel(LCD_D4_PORT, LCD_D4_CHANNEL, OUTPUT);
	dio_vidConfigChannel(LCD_D5_PORT, LCD_D5_CHANNEL, OUTPUT);
	dio_vidConfigChannel(LCD_D6_PORT, LCD_D6_CHANNEL, OUTPUT);
	dio_vidConfigChannel(LCD_D7_PORT, LCD_D7_CHANNEL, OUTPUT);

	_delay_ms(20);

	lcd_vidSendCmd(0x03);
	_delay_ms(5);
	lcd_vidSendCmd(0x03);
	_delay_us(100);
	lcd_vidSendCmd(0x03);
	lcd_vidSendCmd(0x02);
	lcd_vidSendCmd(_LCD_4BIT_MODE);
	lcd_vidSendCmd(_LCD_CURSOR_OFF);
	//lcd_vidCustomWrite();
	lcd_vidGotoRowColumn(0, 0);
}

/******************************************************************************
* \Syntax          : void lcd_vidSendCmd(lcd_Cmd_Type cmd)        
* \Description     : send command to LCD HW                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : cmd	-> LCD command ID                                                                        
* \Return value:   : None                                 
*******************************************************************************/
void lcd_vidSendCmd(lcd_cmd_t cmd)
{
	/*	RS -> Command Mode	*/
	_delay_ms(1);
	dio_vidWriteChannel(LCD_RS_PORT,LCD_RS_CHANNEL,STD_LOW);

	dio_vidWriteChannel(LCD_D4_PORT,LCD_D4_CHANNEL,CHECK_BIT(cmd,4));
	dio_vidWriteChannel(LCD_D5_PORT,LCD_D5_CHANNEL,CHECK_BIT(cmd,5));
	dio_vidWriteChannel(LCD_D6_PORT,LCD_D6_CHANNEL,CHECK_BIT(cmd,6));
	dio_vidWriteChannel(LCD_D7_PORT,LCD_D7_CHANNEL,CHECK_BIT(cmd,7));
	
	enablePulse();
	
	dio_vidWriteChannel(LCD_D4_PORT,LCD_D4_CHANNEL,CHECK_BIT(cmd,0));
	dio_vidWriteChannel(LCD_D5_PORT,LCD_D5_CHANNEL,CHECK_BIT(cmd,1));
	dio_vidWriteChannel(LCD_D6_PORT,LCD_D6_CHANNEL,CHECK_BIT(cmd,2));
	dio_vidWriteChannel(LCD_D7_PORT,LCD_D7_CHANNEL,CHECK_BIT(cmd,3));
	
	enablePulse();
}

/******************************************************************************
* \Syntax          : void lcd_vidSendData(u8 data)        
* \Description     : send data to LCD HW                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : data	-> LCD data input                                                                       
* \Return value:   : None                                 
*******************************************************************************/
void lcd_vidSendData(u8 data)
{
	/*	RS -> Data Mode	*/
	dio_vidWriteChannel(LCD_RS_PORT,LCD_RS_CHANNEL,STD_HIGH);

	dio_vidWriteChannel(LCD_D4_PORT,LCD_D4_CHANNEL,CHECK_BIT(data,4));
	dio_vidWriteChannel(LCD_D4_PORT,LCD_D5_CHANNEL,CHECK_BIT(data,5));
	dio_vidWriteChannel(LCD_D4_PORT,LCD_D6_CHANNEL,CHECK_BIT(data,6));
	dio_vidWriteChannel(LCD_D4_PORT,LCD_D7_CHANNEL,CHECK_BIT(data,7));
	
	enablePulse();
	
	dio_vidWriteChannel(LCD_D4_PORT,LCD_D4_CHANNEL,CHECK_BIT(data,0));
	dio_vidWriteChannel(LCD_D4_PORT,LCD_D5_CHANNEL,CHECK_BIT(data,1));
	dio_vidWriteChannel(LCD_D4_PORT,LCD_D6_CHANNEL,CHECK_BIT(data,2));
	dio_vidWriteChannel(LCD_D4_PORT,LCD_D7_CHANNEL,CHECK_BIT(data,3));
	
	enablePulse();
	
}

/******************************************************************************
* \Syntax          : void lcd_vidGotoRowColumn(u8 row, u8 column)        
* \Description     : set LCD DDRAM pointer                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : row	-> LCD row ID
					 column -> LCD column ID															
* \Return value:   : None                                 
*******************************************************************************/
void lcd_vidGotoRowColumn(u8 row, u8 column)
{
	switch (row)
	{
	case 0:
		/*	Row 0	*/
		lcd_vidSendCmd(0x80+column);
		break;
	case 1:
		/* Row 1 */
		lcd_vidSendCmd(0xC0+column);
		break;
	case 2:
	/* Row 1 */
	lcd_vidSendCmd(0x94+column);
	break;
	
	case 3:
	/* Row 1 */
	lcd_vidSendCmd(0xD4+column);
	break;	
		
	}	
}

/******************************************************************************
* \Syntax          : void lcd_vidDisplyChar(u8 chr)       
* \Description     : sent character to be displayed                                   
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : chr	-> ASCI value of character															
* \Return value:   : None                                 
*******************************************************************************/
void lcd_vidDisplyChar(u8 chr)
{
	lcd_vidSendData(chr);
}

/******************************************************************************
* \Syntax          : void lcd_vidDisplyStr(u8* str)       
* \Description     : display string on LCD                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : str	-> string to be displayed														
* \Return value:   : None                                 
*******************************************************************************/
void lcd_vidDisplyStr(u8* str)
{
	while (*str != '\0')
	{
		lcd_vidDisplyChar(*str);
		str++;
	}
}

/******************************************************************************
* \Syntax          : void lcd_vidCustomWrite(void)
* \Description     : load LCD CGRAM with configured custom characters
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Return value:   : None
*******************************************************************************/
void lcd_vidCustomWrite(void)
{
	u8 loc_ByteIndex=0;
	u8 loc_CharIndx=0;
	
	for (loc_CharIndx=0;loc_CharIndx<NO_CSTOM_CHAR;loc_CharIndx++)
	{
		lcd_vidSendCmd(_LCD_CGRAM_START_ADDRESS +(loc_CharIndx*8));
		for (loc_ByteIndex =0; loc_ByteIndex<NO_CSTOM_CHAR_BYTES;loc_ByteIndex++)
		{
			lcd_vidDisplyChar(customChar[loc_CharIndx][loc_ByteIndex]);
		}
	}	
}
/******************************************************************************
* \Syntax          : void lcd_vidClrDislay(void);
* \Description     : clear display
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Return value:   : None
*******************************************************************************/
void lcd_vidClrDislay(void)
{
	lcd_vidSendCmd(_LCD_CLEAR);
	_delay_ms(5);
}
/******************************************************************************
* \Syntax          : void lcd_vidDisplayNumber(number);
* \Description     :  display numbers
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : u16
* \Return value:   : None
*******************************************************************************/
void lcd_vidDispalyNumber(u16 number)
{
	if (number<0)
	{
		lcd_vidDisplyChar('-');
	} 
	lcd_vidTransferNumToChar(number);
	lcd_vidDisplyStr(buffer);
}
/**********************************************************************************************************************
 *  END OF FILE: lcd.c
 *********************************************************************************************************************/
