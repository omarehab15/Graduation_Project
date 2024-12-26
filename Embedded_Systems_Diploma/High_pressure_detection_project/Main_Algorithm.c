/*
 * Main_Algorithm.c
 *
 *  Created on: Sep 26, 2024
 *      Author: omar
 */

/********************
*     Includes
*********************/
#include "Main_Algorithm.h"

/*************************************************************/
/********************
* Global variables
*********************/
int threshold = 20 , Alaram_Period = 200000;

/*************************************************************/
/********************
* IMPLEMENTATION
*********************/
void App_init(void)
{
	GPIO_INITIALIZATION();
}
void High_Pressure_detection_system_APP(void)
{
	int P_Val ;

	P_Val = Get_P_Val();
	if(P_Val > threshold)
	{
		Start_Alarm();
		Delay(Alaram_Period);
		Stop_Alarm();

	}
	else{
		Stop_Alarm();
	}
}
