/*
 * Alarm_Minitor.c
 *
 *  Created on: Sep 26, 2024
 *      Author: omar
 */
/*************************************************************/
/********************
*     Includes
*********************/
#include "driver.h"

/*************************************************************/
/********************
* APIs
*********************/
void Start_Alarm()
{
	Set_Alarm_actuator(0);
}
void Stop_Alarm()
{
	Set_Alarm_actuator(1);
}
