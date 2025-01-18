/*
 * nvic.c
 *
 *  Created on: Jul 5, 2023
 *      Author: reBuyTech
 */
#include "nvic_reg.h"
#include "std_types.h"
#include "bit_math.h"

void nvic_enableInterrupt(u8 intId)
{
	if (intId>=0 && intId<32)
	{
		NVIC_ISER0_REG = (1<<intId);
	}
	else if (intId>=32 && intId<64)
	{
		NVIC_ISER1_REG = (1<<(intId-32));
	}
	else
	{

	}
}

void nvic_disableInterrupt(u8 intId)
{
	if (intId>=0 && intId<32)
	{
		NVIC_ICER0_REG = (1<<intId);
	}
	else if (intId>=32 && intId<64)
	{
		NVIC_ICER1_REG = (1<<(intId-32));
	}
	else
	{

	}
}

void nvic_setPendingFlag(u8 intId)
{
	if (intId>=0 && intId<32)
	{
		NVIC_ISPR0_REG = (1<<intId);
	}
	else if (intId>=32 && intId<64)
	{
		NVIC_ISPR1_REG = (1<<(intId-32));
	}
	else
	{

	}
}

void nvic_clearPendingFlag(u8 intId)
{
	if (intId>=0 && intId<32)
	{
		NVIC_ICPR0_REG = (1<<intId);
	}
	else if (intId>=32 && intId<64)
	{
		NVIC_ICPR0_REG = (1<<(intId-32));
	}
	else
	{

	}
}

boolean nvic_readActiveFlag(u8 intId)
{
	boolean loc_result = FALSE;
	if (intId>=0 && intId<32)
	{
		loc_result = CHECK_BIT(NVIC_IABR0_REG,intId);
	}
	else if (intId>=32 && intId<64)
	{
		loc_result = CHECK_BIT(NVIC_IABR1_REG,(intId-32));
	}
	else
	{

	}
	return loc_result;
}
