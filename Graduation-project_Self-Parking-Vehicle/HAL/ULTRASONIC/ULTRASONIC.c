/*
 * ULTRASONIC.c
 *
 *  Created on: Feb 16, 2024
 *      Author: omar
 */
#include "ULTRASONIC.h"


double time1, time2, time3, time4;

double distance1, distance2, distance3, distance4;

uint8_t flag_ehco1 = 0 ,flag_ehco2 = 0 ,flag_ehco3 = 0 ,flag_ehco4 = 0;

void echo1(){
	if(flag_ehco1==0){
		TIME_CALCULATION(clk, TIMER_START);
		flag_ehco1=1;
	}
	else{
		time1=TIME_CALCULATION(clk, TIMER_STOP);
		distance1 = ((time1*171.5)/10000);
		flag_ehco1=0;
	}

}

void echo2(){
	if(flag_ehco2==0){
		TIME_CALCULATION(clk, TIMER_START);
		flag_ehco2=1;
	}
	else{
		time2=TIME_CALCULATION(clk, TIMER_STOP);
		distance2 = ((time2*171.5)/10000);
		flag_ehco2=0;
	}

}

void echo3(){
	if(flag_ehco3==0){
		TIME_CALCULATION(clk, TIMER_START);
		flag_ehco3=1;
	}
	else{
		time3=TIME_CALCULATION(clk, TIMER_STOP);
		distance3 = ((time3*171.5)/10000);
		flag_ehco3=0;
	}

}

void echo4(){
	if(flag_ehco4==0){
		TIME_CALCULATION(clk, TIMER_START);
		flag_ehco4=1;
	}
	else{
		time4=TIME_CALCULATION(clk, TIMER_STOP);
		distance4 = ((time4*171.5)/10000);
		flag_ehco4=0;
	}

}


void HAL_ULTRASONIC_INIT(ULT_SLEC_T num)
{
	switch(num)
	{
	case ULT1 :
	{
		MCAL_GPIO_INIT(GPIOB, ULT1_TRIG_PIN_B9, Output_PP_Mode_Speed2MHZ);
		EXTI_Init(GPIOA,ULT1_ECHO_PIN_A0,EXTI_Trigger_RisingAndFalling,echo1);
	}
	break;
	case ULT2 :
	{
		MCAL_GPIO_INIT(GPIOB, ULT2_TRIG_PIN_B10, Output_PP_Mode_Speed2MHZ);
		EXTI_Init(GPIOA,ULT2_ECHO_PIN_A2,EXTI_Trigger_RisingAndFalling,echo2);
	}
	break;
	case ULT3 :
	{
		MCAL_GPIO_INIT(GPIOB, ULT3_TRIG_PIN_B11, Output_PP_Mode_Speed2MHZ);
		EXTI_Init(GPIOA,ULT3_ECHO_PIN_A3,EXTI_Trigger_RisingAndFalling,echo3);
	}
	break;
	case ULT4 :
	{
		MCAL_GPIO_INIT(GPIOB, ULT4_TRIG_PIN_B12, Output_PP_Mode_Speed2MHZ);
		EXTI_Init(GPIOA,ULT4_ECHO_PIN_A4,EXTI_Trigger_RisingAndFalling,echo4);


	}
	break;
	}
}



uint32_t HAL_ULTRASONIC_GET_DISTANCE(ULT_SLEC_T num)
{
	uint32_t x ;
	switch(num)
	{
	case ULT1 :
	{
		MCAL_GPIO_WRITEPIN(GPIOB, ULT1_TRIG_PIN_B9,SET);
		delay(10, U_us, clk);
		MCAL_GPIO_WRITEPIN(GPIOB, ULT1_TRIG_PIN_B9,RESET);
		delay(40,U_ms,clk);
		x = distance1 ;
	}
	break;
	case ULT2 :
	{
		MCAL_GPIO_WRITEPIN(GPIOB, ULT2_TRIG_PIN_B10,SET);
		delay(10, U_us, clk);
		MCAL_GPIO_WRITEPIN(GPIOB, ULT2_TRIG_PIN_B10,RESET);
		delay(40,U_ms,clk);
		x = distance2 ;

	}
	break;
	case ULT3 :
	{
		MCAL_GPIO_WRITEPIN(GPIOB, ULT3_TRIG_PIN_B11,SET);
		delay(10, U_us, clk);
		MCAL_GPIO_WRITEPIN(GPIOB, ULT3_TRIG_PIN_B11,RESET);
		delay(40,U_ms,clk);
		x = distance3 ;
	}
	break;
	case ULT4 :
	{
		MCAL_GPIO_WRITEPIN(GPIOB, ULT4_TRIG_PIN_B12,SET);
		delay(10, U_us, clk);
		MCAL_GPIO_WRITEPIN(GPIOB, ULT4_TRIG_PIN_B12,RESET);
		delay(40,U_ms,clk);
		x = distance4 ;
	}
	break;
	}

	return x ;
}


