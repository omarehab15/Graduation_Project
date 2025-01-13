/*
 * WDGT.h
 *
 *  Created on: Nov 25, 2023
 *      Author: Kareem Abelkader
 */

#ifndef WDGT_H_
#define WDGT_H_

/******************************************************************************
*                               INCLUDES			                          *
*******************************************************************************/
#include"STM32F103x8.h"
#include"rcc.h"

/******************************************************************************
*                               MACROS			                          *
*******************************************************************************/
#define SET_BIT(PORT, BIT)			PORT |= (1<< BIT)
#define RESET_BIT(PORT, BIT)		PORT &= ~(1<<BIT)
#define TOG_BIT(PORT, BIT)			PORT ^= (1<<BIT)
#define GET_BIT(PORT, BIT)			PORT & (1<<BIT)


/******************************************************************************
*                               APIs			                          *
*******************************************************************************/
//independent watch dog timer enable func.
void IWDG_set(void);
//independent watch dog timer disable func.
void IWDG_RESET(void);

/*
 *pr:
 * 	0: divider /4   : tick_time : 0.1ms  max_time : 409.6ms
	1: divider /8   : tick_time : 0.2ms  max_time : 819.2ms
	2: divider /16  : tick_time : 0.4ms  max_time : 1638.4ms
	3: divider /32  : tick_time : 0.8ms  max_time : 3276.8ms
	4: divider /64  : tick_time : 1.6ms  max_time : 6553.6ms
	5: divider /128 : tick_time : 3.2ms  max_time : 13107.2ms
	6: divider /256 : tick_time : 6.4ms  max_time :26214.4ms
 */
//independent watch dog timer time set func.
void IWDG_time_set(uint32_t pr, uint32_t time);


#endif /* WDGT_H_ */
