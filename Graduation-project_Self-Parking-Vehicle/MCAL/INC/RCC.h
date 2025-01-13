/*
 * RCC.h
 *
 *  Created on: Jan 27, 2024
 *      Author: Kareem Abelkader
 */

#ifndef RCC_H_
#define RCC_H_

/******************************************************************************
*                               INCLUDES			                          *
*******************************************************************************/
#include"STM32F103x8.h"

/******************************************************************************
*                                 ENUMs			                              *
*******************************************************************************/
//@ref RCC_Speed
typedef enum{
	RCC_8MHZ  ,
	RCC_32MHZ ,
	RCC_36MHZ
}RCC_speed_t;

//@ref MCU_Buses
typedef enum{
	AHB  ,
	APB1 ,
	APB2
}RCC_Buses_t;

//@ref MCU_Peripherals
//AHB BUS Peripherals
#define RCC_DMA1  		0
#define RCC_DMA2  		1
#define RCC_SRAM  		2
#define RCC_FLITF  		4
#define RCC_CRC  		6
#define RCC_OTGFS		12
#define RCC_ETHMAC		14
#define RCC_ETHMACX		15
#define RCC_ETHMACRX	16
//APB2 BUS Peripherals
#define RCC_AFIO		0
#define RCC_GPIOA		2
#define RCC_GPIOB		3
#define RCC_GPIOC		4
#define RCC_GPIOD		5
#define RCC_GPIOE		6
#define RCC_ADC1		9
#define RCC_ADC2		10
#define RCC_TIM1		11
#define RCC_SPI1		12
#define RCC_USART1		14
//APB1 BUS Peripherals
#define RCC_TIM2		0
#define RCC_TIM3		1
#define RCC_TIM4		2
#define RCC_WWDG		11
#define RCC_SPI2		14
#define RCC_USART2		17
#define RCC_USART3		18
#define RCC_I2C1		21
#define RCC_I2C2		22
#define RCC_CAN1		25
#define RCC_CAN2		26
#define RCC_BKP			27
#define RCC_PWR			28

//@ref RCC_Peripherals_state
#define Enable			1
#define Disable 		0

//@ref RCC_Peripherals_Reset_state
#define RCC_Reset			1
#define RCC_Rereset 		0

//============================================================================

/******************************************************************************
*                                  APIs			                              *
*******************************************************************************/
// function to enable MCU Peripherals
void MCAL_RCC_Peripherals_enable(RCC_Buses_t bus , uint16_t peripheral , uint8_t status);
// function to Reset MCU Peripherals
void MCAL_RCC_Peripherals_Reset(RCC_Buses_t bus , uint16_t peripheral , uint8_t status);
//this function is to set system bus frequency
void MCAL_RCC_GetSYS_CLCKFreq(RCC_speed_t RCC_Speed);
//this function is to set AHB bus frequency
uint32_t MCAL_RCC_GetHCLKFreq(void);
//this function is to set ABP1 bus frequency
uint32_t MCAL_RCC_GetPCLK1Freq(void);
//this function is to set ABP2 bus frequency
uint32_t MCAL_RCC_GetPCLK2Freq(void);
//this function is to set ADC frequency
uint32_t MCAL_RCC_GetPCLK2_ADCFreq(void);


#endif /* RCC_H_ */
