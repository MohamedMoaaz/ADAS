/*
 * nvic_reg.h
 *
 *  Created on: Jul 5, 2023
 *      Author: reBuyTech
 */

#ifndef NVIC_REG_H_
#define NVIC_REG_H_

#define NVIC_ISER_BASE		(0xE000E100)
#define NVIC_ICER_BASE		(0XE000E180)
#define NVIC_ISPR_BASE		(0XE000E200)
#define NVIC_ICPR_BASE		(0XE000E280)
#define NVIC_IABR_BASE		(0xE000E300)
#define NVIC_IPR_BASE		(0xE000E400)
#define NVIC_STIR_BASE		(0xE000EF00)


#define NVIC_ISER0_REG 			(*(volatile u32 *)(NVIC_ISER_BASE + 0x00))
#define NVIC_ISER1_REG 			(*(volatile u32 *)(NVIC_ISER_BASE + 0x04))

#define NVIC_ICER0_REG			(*(volatile u32 *)(NVIC_ICER_BASE + 0x00))
#define NVIC_ICER1_REG			(*(volatile u32 *)(NVIC_ICER_BASE + 0x04))


#define NVIC_ISPR0_REG			(*(volatile u32 *)(NVIC_ISPR_BASE + 0x00))
#define NVIC_ISPR1_REG			(*(volatile u32 *)(NVIC_ISPR_BASE + 0x04))

#define NVIC_ICPR0_REG			(*(volatile u32 *)(NVIC_ICPR_BASE + 0x00))
#define NVIC_ICPR1_REG			(*(volatile u32 *)(NVIC_ICPR_BASE + 0x04))

#define NVIC_IABR0_REG			(*(volatile u32 *)(NVIC_IABR_BASE + 0x00))
#define NVIC_IABR1_REG			(*(volatile u32 *)(NVIC_IABR_BASE + 0x04))

#endif /* NVIC_REG_H_ */
