/*
 * DC_MOTOR.h
 *
 *  Created on: Feb 13, 2024
 *      Author: KARIM
 */

#ifndef DC_MOTOR_DC_MOTOR_H_
#define DC_MOTOR_DC_MOTOR_H_

/******************************
 * Includes
 *******************************/
#include "STM32F103x8.h"
#include "GPIO.h"
#include "RCC.h"

//==========================================================================


#define driver_pin1				PIN_5
#define driver_pin2				PIN_6

#define FORWARD					0
#define REVERSE					1
#define Stop					2


//=====================================================================

/*
 * ===============================================
 * APIs Supported by "HAL DC Motor DRIVER"
 * ===============================================
 */
void HAL_MOTOR_Init(void);
void HAL_MOTOR_Motion(uint8_t x);

#endif /* DC_MOTOR_DC_MOTOR_H_ */
