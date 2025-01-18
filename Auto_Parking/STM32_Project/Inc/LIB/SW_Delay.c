/*
 * SW_Delay.c
 *
 *  Created on: Sep 14, 2023
 *      Author: Abnaby
 */
#include <LIB/STD_TYPES.h>
#include "RCC/RCC_interface.h"

#if DELAY_BASED_ON == STK_DELAY
#include "STK/STK_interface.h"
#endif
#include "SW_Delay.h"

void delay_init(void)
{
#if DELAY_BASED_ON == STK_DELAY
    STK_voidInit();
#endif

}
void delay_us(u32 microseconds)
{
#if DELAY_BASED_ON == SW_DELAY
    // Calculate the number of loops required for the delay
	u32 loops = (8 * microseconds) / 3; // 8 MHz sysclk

    for (u32 i = 0; i < loops; ++i)
    {
        __asm("NOP");
    }
#elif DELAY_BASED_ON == STK_DELAY
    STK_voidSetBusyWait_US((u16)microseconds);
#endif
}

void delay_ms(u32 milliseconds) {
#if DELAY_BASED_ON == SW_DELAY
    // Calculate the number of loops required for the desired delay
    u32 loops = milliseconds * (8000 / 5);

    __asm volatile (
        "1: \n"
        "subs %[loops], %[loops], #1 \n"
        "bne 1b \n"
        : [loops] "+r" (loops)
        :
        :
    );
#elif DELAY_BASED_ON == STK_DELAY
    STK_voidSetBusyWait_MS((u16)milliseconds);
#endif

}



