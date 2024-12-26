/*
 * Pressure_Sensor_Driver.c
 *
 *  Created on: Sep 26, 2024
 *      Author: omar
 */

/*************************************************************/
/********************
*     Includes
*********************/
#include "Pressure_Sensor_Driver.h"

/*************************************************************/
/********************
*implementation
*********************/

int Get_P_Val(void)
{
	int P_Val ;
	P_Val = getPressureVal();
	return P_Val ;
}

