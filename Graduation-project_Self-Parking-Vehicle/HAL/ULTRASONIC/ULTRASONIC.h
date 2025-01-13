/*
 * ULTRASONIC.h
 *
 *  Created on: Feb 16, 2024
 *      Author: omar
 */

#ifndef ULTRASONIC_ULTRASONIC_H_
#define ULTRASONIC_ULTRASONIC_H_

/******************************
 * Includes
 *******************************/
#include "STM32F103x8.h"
#include "GPIO.h"
#include "RCC.h"
#include "TIMER.h"
#include "ISR.h"


//==========================================================================

/******************************
 * Generic Variables
 *******************************/

#define clk		36000000

//Ultrasonic Sensor Pins
#define ULT1_TRIG_PIN_B9		PIN_9
#define ULT2_TRIG_PIN_B10		PIN_10
#define ULT3_TRIG_PIN_B11		PIN_11
#define ULT4_TRIG_PIN_B12		PIN_12
#define ULT1_ECHO_PIN_A0		PIN_0
#define ULT2_ECHO_PIN_A2		PIN_2
#define ULT3_ECHO_PIN_A3		PIN_3
#define ULT4_ECHO_PIN_A4		PIN_4


typedef enum{
	ULT1,
	ULT2,
	ULT3,
	ULT4
}ULT_SLEC_T;


//============================================================================================

/******************************************************************************
*                                  APIs			                              *
*******************************************************************************/

void HAL_ULTRASONIC_INIT(ULT_SLEC_T num);
uint32_t HAL_ULTRASONIC_GET_DISTANCE(ULT_SLEC_T num);



#endif /* ULTRASONIC_ULTRASONIC_H_ */
