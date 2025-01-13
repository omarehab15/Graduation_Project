/*
 * STM32F103x8.h
 *
 * Master Embedded System Diploma
 * Eng. Kareem Abelkader
 */

#ifndef STM32F103X8_H_
#define STM32F103X8_H_

/******************************
 * Includes
 *******************************/
#include "stdlib.h"
#include <stdint.h>

//==========================================================================

/***********************************
 * Base Addresses for Memories
 ***********************************/
#define FLASH_MEM_BASE						0x08000000UL
#define SESTYM_MEM_BASE						0x1FFFF000UL
#define SRAM_MEM							0x20000000UL
#define Peripherals_BASE					0x40000000UL
#define Cortex_Internal_Per					0xE0000000UL

/*************************************
 * Base Addresses for Bus Peripheral
 ************************************/
//RCC
#define RCC_BASE              				0x40021000UL

//GPIO
#define GPIOA_BASE							0x40010800UL
#define GPIOB_BASE							0x40010C00UL
#define GPIOC_BASE							0x40011000UL
#define GPIOD_BASE							0x40011400UL
#define GPIOE_BASE							0x40011800UL

//AFIO
#define AFIO_BASE							0x40010000UL

//Timer
#define TIM1_BASE             				0x40012C00UL
#define IWDG_BASE             				0x40003000UL
#define TIM2_BASE             				0x40000000UL
#define TIM3_BASE             				0x40000400UL
#define TIM4_BASE             				0x40000800UL

//USART
#define USART1_BASE							0x40013800UL
#define USART2_BASE							0x40004400UL
#define USART3_BASE							0x40004800UL

//EXTI
#define EXTI_BASE							0x40010400UL
#define NVIC_BASE							0xE000E100UL

//I2C
#define I2C1_BASE							0x40005400UL
#define I2C2_BASE							0x40005800UL
//================================================================================

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
typedef struct {
	volatile uint32_t CRL;		//Port configuration register low (P0:p7)
	volatile uint32_t CRH;		//Port configuration register high (P8:P15)
	volatile uint32_t IDR;		//Port input data register
	volatile uint32_t ODR;		//Port output data register
	volatile uint32_t BSRR;		//Port bit set/reset register
	volatile uint32_t BRR;		//Port bit reset register
	volatile uint32_t LCKR;		//Port configuration lock register
}GPIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
typedef struct {
	volatile uint32_t EVCR;			//Event control register
	volatile uint32_t MAPR;			//AF remap and debug I/O configuration register
	volatile uint32_t EXTICR1;		//External interrupt configuration register 1
	volatile uint32_t EXTICR2;		//External interrupt configuration register 1
	volatile uint32_t EXTICR3;		//External interrupt configuration register 1
	volatile uint32_t EXTICR4;		//External interrupt configuration register 1
	volatile uint32_t RESERVED0;
	volatile uint32_t MAPR2;		//AF remap and debug I/O configuration register2
}AFIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
} RCC_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register: TIM1
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t RCR;//not included in TIM2 , TIM3 and TIM4
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t BDTR;//not included in TIM2 , TIM3 and TIM4
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
} TIMx_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: IWDG
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
typedef struct
{
	volatile uint32_t KR;
	volatile uint32_t PR;
	volatile uint32_t RLR;
	volatile uint32_t SR;
} IWDG_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: USART
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
typedef struct{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}USART_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
typedef struct{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: I2C
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
typedef struct{
	volatile uint32_t CR1   ;
	volatile uint32_t CR2   ;
	volatile uint32_t OAR1  ;
	volatile uint32_t OAR2  ;
	volatile uint32_t DR    ;
	volatile uint32_t SR1   ;
	volatile uint32_t SR2   ;
	volatile uint32_t CCR   ;
	volatile uint32_t TRISE ;
}I2C_TypeDef;


//================================================================================

/*************************************
 * Peripheral instant
 ************************************/

//RCC
#define RCC                 ((RCC_TypeDef *)RCC_BASE)

//GPIO
//GPIO A/B are fully included
#define GPIOA				((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB				((GPIO_TypeDef *)GPIOB_BASE)
//GPIO C/D are partial included
#define GPIOC				((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD				((GPIO_TypeDef *)GPIOD_BASE)

//AFIO
#define AFIO 				 ((AFIO_TypeDef *) AFIO_BASE)

//TIMER
#define TIM1                 ((TIMx_TypeDef *)TIM1_BASE)
#define TIM2                 ((TIMx_TypeDef *)TIM2_BASE)
#define TIM3                 ((TIMx_TypeDef *)TIM3_BASE)
#define TIM4                 ((TIMx_TypeDef *)TIM4_BASE)
#define IWDG                 ((IWDG_TypeDef *)IWDG_BASE)

//USART
#define USART1				 ((USART_TypeDef *)USART1_BASE)
#define USART2				 ((USART_TypeDef *)USART2_BASE)
#define USART3				 ((USART_TypeDef *)USART3_BASE)

//I2C
#define I2C1                 ((I2C_TypeDef *)I2C1_BASE)
#define I2C2                 ((I2C_TypeDef *)I2C2_BASE)
//INTERRUPT
#define EXTI                 ((EXTI_TypeDef *)EXTI_BASE)

#define NVIC_ISER0			 *(volatile uint32_t *)(NVIC_BASE + 0x00)
#define NVIC_ISER1			 *(volatile uint32_t *)(NVIC_BASE + 0x04)
#define NVIC_ISER2			 *(volatile uint32_t *)(NVIC_BASE + 0x08)
#define NVIC_ICER0			 *(volatile uint32_t *)(NVIC_BASE + 0x80)
#define NVIC_ICER1			 *(volatile uint32_t *)(NVIC_BASE + 0x84)
#define NVIC_ICER2			 *(volatile uint32_t *)(NVIC_BASE + 0x88)

//================================================================================

/**********************************
 * NVIC IRQ enable/disable Macros
 **********************************/

#define NVIC_TIM1_BRK_Enable 				 		    (NVIC_ISER0	|= 1<<24 )
#define NVIC_TIM1_UP_Enable 			    		   	(NVIC_ISER0	|= 1<<25 )
#define NVIC_TIM1_TRG_COM_Enable 						(NVIC_ISER0	|= 1<<26 )
#define NVIC_TIM1_CC_Enable 							(NVIC_ISER0	|= 1<<27 )
#define NVIC_TIM2_global_interrupt_Enable 	        	(NVIC_ISER0	|= 1<<28 )
#define NVIC_TIM3_global_interrupt_Enable 	      	    (NVIC_ISER0	|= 1<<29 )
#define NVIC_TIM4_global_interrupt_Enable 	      	    (NVIC_ISER0	|= 1<<30 )

#define NVIC_USART1_interrupt_Enable 	                (NVIC_ISER1	|= 1<<(37-32) )
#define NVIC_USART2_interrupt_Enable 	                (NVIC_ISER1	|= 1<<(38-32) )
#define NVIC_USART3_interrupt_Enable 	                (NVIC_ISER1	|= 1<<(39-32) )

#define NVIC_SPI1_interrupt_Enable 	                    (NVIC_ISER1	|= 1<<(35-32) )
#define NVIC_SPI2_interrupt_Enable 	                    (NVIC_ISER1	|= 1<<(36-32) )

#define NVIC_IRQ31_I2C1_EV_Enable()						(NVIC_ISER0 |=1<<31)
#define NVIC_IRQ32_I2C1_ER_Enable()						(NVIC_ISER1 |=1<< (32- 32) )
#define NVIC_IRQ33_I2C2_EV_Enable()						(NVIC_ISER1 |=1<< (33- 32) )
#define NVIC_IRQ34_I2C2_ER_Enable()						(NVIC_ISER1 |=1<< (34- 32) )
//==============================================================

#define NVIC_TIM1_BRK_Disable 							(NVIC_ICER0 |= 1<<24)
#define NVIC_TIM1_UP_Disable 							(NVIC_ICER0 |= 1<<25)
#define NVIC_TIM1_TRG_COM_Disable 		    		    (NVIC_ICER0 |= 1<<26)
#define NVIC_TIM1_CC_Disable 							(NVIC_ICER0	|= 1<<27)
#define NVIC_TIM2_global_interrupt_Disable 	     	    (NVIC_ICER0 |= 1<<28)
#define NVIC_TIM3_global_interrupt_Disable 	      		(NVIC_ICER0 |= 1<<29)
#define NVIC_TIM4_global_interrupt_Disable 	      		(NVIC_ICER0 |= 1<<30)

#define NVIC_USART1_interrupt_Disable 	                (NVIC_ICER1	|= 1<<(37-32))
#define NVIC_USART2_interrupt_Disable 	                (NVIC_ICER1	|= 1<<(38-32))
#define NVIC_USART3_interrupt_Disable 	                (NVIC_ICER1	|= 1<<(39-32))

#define NVIC_SPI1_interrupt_Disable 	                (NVIC_ICER1 |= 1<<(35-32))
#define NVIC_SPI2_interrupt_Disable 	                (NVIC_ICER1 |= 1<<(36-32))

#define NVIC_IRQ31_I2C1_EV_Disable()					(NVIC_ICER0 |=1<< ( 31 ))
#define NVIC_IRQ32_I2C1_ER_Disable()					(NVIC_ICER1 |=1<< ( 32 - 32))
#define NVIC_IRQ33_I2C2_EV_Disable()					(NVIC_ICER1 |=1<< ( 33 - 32))
#define NVIC_IRQ34_I2C2_ER_Disable()					(NVIC_ICER1 |=1<< ( 34 - 32))
//=================================================================



#endif /* STM32F103X8_H_ */
