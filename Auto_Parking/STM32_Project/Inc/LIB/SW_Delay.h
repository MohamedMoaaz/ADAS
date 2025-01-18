/*
 * SW_Delay.h
 *
 *  Created on: Sep 14, 2023
 *      Author: Abnaby
 */

#ifndef SW_DELAY_H_
#define SW_DELAY_H_

#define SW_DELAY 		1
#define STK_DELAY		2

#define DELAY_BASED_ON    STK_DELAY


void delay_init(void);
void delay_us(u32 microseconds);
void delay_ms(u32 milliseconds);

#endif /* SW_DELAY_H_ */
