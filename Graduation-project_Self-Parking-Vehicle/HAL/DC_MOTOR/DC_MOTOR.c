/*
 * DC_MOTOR.c
 *
 *  Created on: Feb 13, 2024
 *      Author: KARIM
 */

/******************************
 * Includes
 *******************************/
#include "DC_MOTOR.h"

//==========================================================================


void HAL_MOTOR_Init(void)
{
	MCAL_GPIO_INIT(GPIOB,driver_pin1 ,Output_PP_Mode_Speed10MHZ);
	MCAL_GPIO_INIT(GPIOB,driver_pin2 ,Output_PP_Mode_Speed10MHZ);
}


void HAL_MOTOR_Motion(uint8_t x)
{
	switch(x)
	{
	case FORWARD :
	{
		MCAL_GPIO_WRITEPIN(GPIOB, driver_pin1, SET);
		MCAL_GPIO_WRITEPIN(GPIOB, driver_pin2, RESET);
	}
	break;
	case REVERSE :
	{
		MCAL_GPIO_WRITEPIN(GPIOB, driver_pin1, RESET);
		MCAL_GPIO_WRITEPIN(GPIOB, driver_pin2, SET);
	}
	break ;
	case Stop :
	{
		MCAL_GPIO_WRITEPIN(GPIOB, driver_pin2, RESET);
		MCAL_GPIO_WRITEPIN(GPIOB, driver_pin1, RESET);
	}
	break;
	}

}
