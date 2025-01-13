/*
 * GPIO_DRIVER.h
 *
 *  Created on: Sep 21, 2022
 *      Author: Kareem Abelkader
 */

#ifndef INC_GPIO_DRIVER_H_
#define INC_GPIO_DRIVER_H_


/******************************
 * Includes
 *******************************/
#include "STM32F103x8.h"
#include "RCC.h"

//==========================================================================


/***********************************
 * User Type Definitions
 ***********************************/
/*To configure a pin, determine the following consideration:
 * 1- Pin number
 * 2- Pin mode (input / output / AF)
 * 3- Pin speed if it output pin
 */
/***********************************
 *  Configuration References
 ***********************************/

/*PINS_DEF ref*/
#define PIN_0  0
#define PIN_1  1
#define PIN_2  2
#define PIN_3  3
#define PIN_4  4
#define PIN_5  5
#define PIN_6  6
#define PIN_7  7
#define PIN_8  8
#define PIN_9  9
#define PIN_10 10
#define PIN_11 11
#define PIN_12 12
#define PIN_13 13
#define PIN_14 14
#define PIN_15 15

/*MODE_DEF ref */
/*
		0: Analog mode
		1: Floating input (reset state)
		2: Input with pull-up
		3:  Input with  pull-down
		4: General purpose output push-pull
		5: General purpose output Open-drain
		6: Alternate function output Push-pull
		7: Alternate function output Open-drain
		8: Alternate function INPUT
 */
//Input Modes
#define Input_Analog_Mode			   				0b0000     // 00: Analog mode 00: Input mode (reset state)
#define Input_FLO_Mode			   					0b0100    //01: Floating input (reset state) 00: Input mode (reset state)
#define Input_PU_Mode								0b11000  // 10: Input with pull-up  00: Input mode (reset state)
#define Input_PD_Mode								0b01000 //10: Input with  pull-down  00: Input mode (reset state)
#define Input_ALF_Mode		       			 		0b0100 // 00: Input mode (reset state)
//Output push-Pull
#define Output_PP_Mode_Speed10MHZ					0b0001  //00: General purpose output push-pull
#define Output_PP_Mode_Speed2MHZ					0b0010 //00: General purpose output push-pull
#define Output_PP_Mode_Speed50MHZ					0b0011//00: General purpose output push-pull
//Output Open-Drain
#define Output_OD_Mode_Speed10MHZ					0b0101  //01: General purpose output Open-drain
#define Output_OD_Mode_Speed2MHZ					0b0110 //01: General purpose output Open-drain
#define Output_OD_Mode_Speed50MHZ					0b0111//01: General purpose output Open-drain
//Output Alternative function Push-Pull
#define Output_AF_PP_Mode_Speed10MHZ				0b1001  //10: Alternate function output Push-pull
#define Output_AF_PP_Mode_Speed2MHZ					0b1010 //10: Alternate function output Push-pull
#define Output_AF_PP_Mode_Speed50MHZ				0b1011//10: Alternate function output Push-pull
//Output Alternative function Open-Drain
#define Output_AF_OD_Mode_Speed10MHZ				0b1101  //11: Alternate function output Open-drain
#define Output_AF_OD_Mode_Speed2MHZ					0b1110 //11: Alternate function output Open-drain
#define Output_AF_OD_Mode_Speed50MHZ				0b1111//11: Alternate function output Open-drain


//=====================================================
#define SET 	1
#define RESET	0
#define LOCKED				0
#define UNLOCKED			1

//============================================================================================

/******************************************************************************
*                                  APIs			                              *
*******************************************************************************/

//Initialization of GPIOx PINy according to a specific configuration
void MCAL_GPIO_INIT(GPIO_TypeDef* GPIOx,uint16_t pin,uint32_t pinmode);//port , pin , mode
//De-initialization of GPIOx PINy
void MCAL_GPIO_DEINIT(GPIO_TypeDef* GPIOx);
//Write on pin
void MCAL_GPIO_WRITEPIN(GPIO_TypeDef* GPIOx,uint16_t pin,uint8_t status);
//Write on port
void MCAL_GPIO_WRITEPORT(GPIO_TypeDef* GPIOx,uint16_t status);
//Values of a port
void set_Value_PORT(GPIO_TypeDef* GPIOx,uint16_t status,uint16_t position);
void res_Value_PORT(GPIO_TypeDef* GPIOx,uint16_t status,uint16_t position);
//Read from pin
uint8_t MCAL_GPIO_READPIN(GPIO_TypeDef* GPIOx, uint16_t pin);
//Read from port
uint16_t MCAL_GPIO_READPORT(GPIO_TypeDef* GPIOx);
//Toggle pin
void MCAL_GPIO_TOGGLEPIN(GPIO_TypeDef* GPIOx, uint16_t pin);
//Toggle port
void MCAL_GPIO_TOGGLEPORT(GPIO_TypeDef* GPIOx);
//Lock pin
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef* GPIOx, uint16_t pin_number);


#endif /* INC_GPIO_DRIVER_H_ */
