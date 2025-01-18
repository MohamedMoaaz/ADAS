/*
 * nvic.h
 *
 *  Created on: Jul 5, 2023
 *      Author: reBuyTech
 */

#ifndef NVIC_H_
#define NVIC_H_

#include "std_types.h"

void nvic_enableInterrupt(u8 intId);
void nvic_disableInterrupt(u8 intId);

void nvic_setPendingFlag(u8 intId);
void nvic_clearPendingFlag(u8 intId);

boolean nvic_readActiveFlag(u8 intId);


#endif /* NVIC_H_ */
