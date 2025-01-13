/******************************
 * Includes
 *******************************/
#include "Servo.h"

//==========================================================================


void HAL_Servo_Set_Angle(double angle,uint32_t clock)
{

	double duty_cycle = ( (0.01483333) *angle);
	duty_cycle=duty_cycle+0.8;
	if(clock == 36000000)
	{
		MCAL_PWM_Init(PWM_MODE1, CH1, duty_cycle, 50,126);
	}
	else if((clock == 32000000))
	{
		MCAL_PWM_Init(PWM_MODE1, CH1, duty_cycle, 50,112);
	}
	else
	{
		MCAL_PWM_Init(PWM_MODE1, CH1, duty_cycle, 50,28);
	}


}

