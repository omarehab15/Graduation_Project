/*
 * STM32_TIMERS_DRIVER.h
 *
 *  Created on: Nov 3, 2022
 *      Author: Kareem Abelkader
 */

#ifndef INC_STM32_TIMERS_DRIVER_H_
#define INC_STM32_TIMERS_DRIVER_H_

/******************************
 * Includes
 *******************************/
#include "stdio.h"
#include "stdint.h"
#include "GPIO.h"
#include "STM32F103x8.h"
#include "ISR.h"
#include "RCC.h"

//==========================================================================


typedef enum{
	PWM_MODE1 ,
	PWM_MODE2
}PWM_Modes_t;

typedef enum
{
	CH1,
	CH2,
	CH3,
	CH4
}TIMER_channels_t;

//@delay
#define U_ms     0 //milli seconds
#define U_us     1 //micro seconds

#define TIMER_START    1
#define TIMER_STOP     0


//===========================================================================================

/******************************************************************************
*                                  APIs			                              *
*******************************************************************************/

//timer3 ch_1 --> A6  <> timer3 ch_2 --> A7 <> timer3 ch_3 --> B0 <> timer3 ch_4 --> B1
void MCAL_PWM_Init(PWM_Modes_t mode ,TIMER_channels_t channel , double duty_cycle , uint32_t freq,uint32_t TIM_PSC);

//Enter in while loop and after timer interrupt it break the loop
void delay(uint16_t time,uint8_t U,uint32_t clk);

uint32_t TIME_CALCULATION(uint32_t clk,uint8_t TIMER_ST);

uint32_t MCAL_COUNTER(uint32_t clk,uint8_t TIMER_ST);

#endif /* INC_STM32_TIMERS_DRIVER_H_ */
