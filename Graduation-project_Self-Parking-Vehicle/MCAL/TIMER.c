
/*
 * STM32_TIMERS_DRIVER.c
 *
 *  Created on: Nov 3, 2022
 *      Author: Kareem Abelkader
 */
#include "TIMER.h"
//==============================================================================================
uint8_t delay_flag =1;
uint16_t overflowtims=0;
uint16_t overflowtims1=0;
uint16_t timer_ticks=0;
uint16_t timer_ticks1=0;
TIMx_TypeDef* delay_TIMER=TIM2;

//uint32_t TIM_PSC ;
uint32_t TIM_Arr ;
float TIM_Crr ;

//===============================================================================================

void MCAL_PWM_Init(PWM_Modes_t mode ,TIMER_channels_t channel , double duty_cycle , uint32_t freq,uint32_t TIM_PSC)
{

	//counter disabled
	TIM3->CR1 &=~ (1 << 0);
	TIM_Arr = (1000000 / freq );
	TIM_Crr = ((duty_cycle /100) * (float)TIM_Arr );

	//Timer clock enable
	MCAL_RCC_Peripherals_enable(APB1, RCC_TIM3, Enable);
	MCAL_RCC_Peripherals_enable(APB2, RCC_GPIOA, Enable);
	MCAL_RCC_Peripherals_enable(APB2, RCC_GPIOB, Enable);
	MCAL_RCC_Peripherals_enable(APB2, RCC_AFIO, Enable);

	switch (channel)
	{
	case CH1 :
	{
		//GPIO config
		MCAL_GPIO_INIT(GPIOA, PIN_6,Output_AF_PP_Mode_Speed50MHZ);

		//timer 3 CH1 setup
		TIM3->CCMR1 &=~ (0b11 << 0);
		TIM3->CCMR1 |= (1 << 3);
		TIM3->CCER |= (1 << 0);
		switch (mode)
		{
		case PWM_MODE1 :
		{
			TIM3->CCMR1 |= (0b110<<4);
			break;
		}
		case PWM_MODE2 :
		{
			TIM3->CCMR1 |= (0b111<<4);
			break;
		}
		}
		TIM3->CCR1 =  TIM_Crr ;
		TIM3->DIER |= (0b11 << 0);
		TIM3->EGR |= (1 << 1);
		TIM3->CCER &=~ (1 << 1);
		break;


	}
	case CH2 :
	{
		//GPIO config
		MCAL_GPIO_INIT(GPIOA, PIN_7,Output_AF_PP_Mode_Speed50MHZ);

		//timer 3 CH2 setup
		TIM3->CCMR1 &=~ (0b11 << 8);
		TIM3->CCMR1 |= (1 << 11);
		TIM3->CCER |= (1 << 4);
		switch (mode)
		{
		case PWM_MODE1 :
		{
			TIM3->CCMR1 |= (0b110<<12);
			break;
		}
		case PWM_MODE2 :
		{
			TIM3->CCMR1 |= (0b111<<12);
			break;
		}
		}

		TIM3->CCR2 = TIM_Crr ;
		TIM3->DIER |= (0b101 << 0);
		TIM3->EGR |= (1 << 2);
		TIM3->CCER &=~ (1 << 5);
		break;

	}
	case CH3 :
	{

		//GPIO config
		MCAL_GPIO_INIT(GPIOB, PIN_0,Output_AF_PP_Mode_Speed50MHZ);

		//timer 3 CH3 setup
		TIM3->CCMR2 &=~ (0b11 << 0);
		TIM3->CCMR2 |= (1 << 3);
		TIM3->CCER |= (1 << 8);
		switch (mode)
		{
		case PWM_MODE1 :
		{
			TIM3->CCMR2 |= (0b110<<4);
			break;
		}
		case PWM_MODE2 :
		{
			TIM3->CCMR2 |= (0b111<<4);
			break;
		}
		}
		TIM3->CCR3 = TIM_Crr ;
		TIM3->DIER |= (0b1001 << 0);
		TIM3->EGR |= (1 << 3);
		TIM3->CCER &=~ (1 << 9);
		break;

	}
	case CH4 :
	{
		//GPIO config
		MCAL_GPIO_INIT(GPIOB, PIN_1,Output_AF_PP_Mode_Speed50MHZ);

		//timer 4 CH2 setup
		TIM3->CCMR2 &=~ (0b11 << 8);
		TIM3->CCMR2 |= (1 << 11);
		TIM3->CCER |= (1 << 12);
		switch (mode)
		{
		case PWM_MODE1 :
		{
			TIM3->CCMR2 |= (0b110<<12);
			break;
		}
		case PWM_MODE2 :
		{
			TIM3->CCMR2 |= (0b111<<12);
			break;
		}
		}

		TIM3->CCR4 = TIM_Crr ;
		TIM3->DIER |= (0b10001 << 0);
		TIM3->EGR |= (1 << 4);
		TIM3->CCER &=~ (1 << 13);
		break;

	}
	}

	TIM3->CR1 |= (1 << 7);
	TIM3->ARR = TIM_Arr ;
	TIM3->PSC = TIM_PSC ;
	TIM3->EGR |= (1 << 0);
	TIM3->CR1 |=(1<<0);//enable the timer
}
//=======================================================================================
void delay(uint16_t time,uint8_t U,uint32_t clk){

	MCAL_RCC_Peripherals_enable(APB1, RCC_TIM2, Enable);

	delay_TIMER->CR1 &=~(1<<0);//timer off
	///TIMERS_typeDef* TIMERx=TIM2;
	char user_flage=1;
	uint32_t user_top=0;
	uint32_t user_pre=1;
	uint32_t unit =1000;
	uint8_t  increase=2;

	if (U == 0){
		unit = 1000;
		if (time > 3000)increase = 100;
		else increase = 10;
	}
	else {
		unit = 1000000;
		if (time > 3000)increase = 10;
		else increase = 5;
	}

	while(user_flage==1){
		user_top = (clk/unit*time)/( user_pre );
		if(user_top>=32000){

			if(user_pre>65530){
				user_pre=65530;
				user_flage=0;
			}
			else user_pre+=increase;

		}
		else{
			user_flage=0;
		}
	}


	delay_TIMER->CR1 &=~(1<<0);//timer off

	delay_TIMER->CR1  |=(1<<2);//Only counter overflow/underflow generates an update

	delay_TIMER->DIER |=(1<<0);//Update interrupt enabled



	delay_TIMER->ARR=user_top;//frec peak value

	delay_TIMER->PSC=(user_pre-1);//prescaller

	delay_TIMER->EGR |=(1<<0);//1: Re-initialize the counter and generates an update of the registers. Note that the prescaler

	delay_TIMER->CR1 |=(1<<0);//enable the timer



	delay_flag=1;
	NVIC_TIM2_global_interrupt_Enable;
	while(delay_flag){

	}
}

//======================================================================================================

uint32_t TIME_CALCULATION(uint32_t clk,uint8_t TIMER_ST){
	if(TIMER_ST==TIMER_START){
		MCAL_RCC_Peripherals_enable(APB1, RCC_TIM4, Enable);
		TIM4->CR1 &=~(1<<0);//stop

		TIM4->CR1  |=(1<<2);

		TIM4->DIER |=(1<<0);//Update interrupt enable

		TIM4->ARR=64000;//peak value 8ms of freq=8000000hz

		TIM4->PSC=0;//prescaller

		TIM4->EGR |=(1<<0);//Bit 0 UG: Update generation

		TIM4->CR1 |=(1<<0);//enable the timer
		NVIC_TIM4_global_interrupt_Enable;
		return 1;
	}
	else {
		TIM4->CR1 &=~(1<<0);//stop
		timer_ticks=TIM4->CNT;
		uint32_t X=((timer_ticks+(overflowtims*64000))/(clk/1000000));
		overflowtims=0;
		timer_ticks=0;
		return X;
	}
}


uint32_t MCAL_COUNTER(uint32_t clk,uint8_t TIMER_ST)
{
	if(TIMER_ST==TIMER_START){
		MCAL_RCC_Peripherals_enable(APB1, RCC_TIM3, Enable);
		TIM3->CR1 &=~(1<<0);//stop

		TIM3->CR1  |=(1<<2);

		TIM3->DIER |=(1<<0);//Update interrupt enable

		TIM3->ARR=64000;//peak value 8ms of freq=8000000hz

		TIM3->PSC=0;//prescaller

		TIM3->EGR |=(1<<0);//Bit 0 UG: Update generation

		TIM3->CR1 |=(1<<0);//enable the timer
		NVIC_TIM3_global_interrupt_Enable;
		return 1;
	}
	else {
		TIM3->CR1 &=~(1<<0);//stop
		timer_ticks1=TIM3->CNT;
		uint32_t X1=((timer_ticks1+(overflowtims1*64000))/(clk/1000000));
		overflowtims1=0;
		timer_ticks1=0;
		return X1;
	}
}


//========<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  ISR  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void TIM2_IRQHandler(){
	delay_TIMER->SR &=~(1<<0);//Bit 0 UIF: Update interrupt flag
	delay_flag=0;
	//NVIC_TIM2_global_interrupt_Disable;
	delay_TIMER->CR1 &=~(1<<0);//timer off

}

void TIM3_IRQHandler(){
	TIM3->SR &=~(1<<0);
	overflowtims1++;
}

void TIM4_IRQHandler(){
	TIM4->SR &=~(1<<0);
	overflowtims++;
}

