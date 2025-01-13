/*
 * stm32f103c6_ISR_DRIVER.c
 *
 *  Created on: Sep 27, 2022
 *      Author: Kareem Abelkader
 */

#include "ISR.h"

/*
 * ------------------------------------------------
 * 				  Generic Variables
 *-------------------------------------------------
 */

void(* GP_IRQ_Callback[15])(void);
/*
 * ------------------------------------------------
 * 				  Generic Functions
 *-------------------------------------------------
 */

void Enable_NVIC(uint16_t IRQ){
	switch(IRQ){
	case 0:
		NVIC_IRQ6_EXTI0_Enable;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Enable;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Enable;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Enable;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Enable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Enable;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Enable;
		break;
	}


}
void Disable_NVIC(uint16_t IRQ){
	switch(IRQ){
	case 0:
		NVIC_IRQ6_EXTI0_Disable;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Disable;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Disable;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Disable;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Disable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Disable;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Disable;
		break;
	}


}

//================================================================
//##############################  API  ##########################
//================================================================

/**================================================================
 * @Fn              - EXTI
 * @brief           - Initialize EXTI from specific GPIO Pin and specify the mask\trigger condition and IRQ callback
 * @param [in]      - PORTx: GPIOx
 * @param [in]      - pin: pin
 * @param [in]      - triggercase: trigger case falling or rising
 * @param [in]      -function_addres : app ISR function
 * @retval          - none
 * Note             -
 *================================================================ */

void EXTI_Init(GPIO_TypeDef* PORTx ,uint16_t pin,uint16_t triggercase,void (*function_addres) (void))
{

	MCAL_GPIO_INIT(PORTx,pin,Input_ALF_Mode);//set pin to _INTPUT_AF

	//AFIO_EXTICR1
		//	0000: PA[x] pin
		//	0001: PB[x] pin
		//	0010: PC[x] pin
		//	0011: PD[x] pin

		switch(pin){
		case PIN_0:
			AFIO->EXTICR1 &=~(0b1111<<0);
			if(PORTx==GPIOA)     {AFIO->EXTICR1 &=~(0b1111<<0);}
			else if(PORTx==GPIOB){AFIO->EXTICR1 |= (0b0001<<0);}
			else if(PORTx==GPIOC){AFIO->EXTICR1 |= (0b0010<<0);}
			else if(PORTx==GPIOD){AFIO->EXTICR1 |= (0b0011<<0);}

			break;
		case PIN_1:
			AFIO->EXTICR1 &=~(0b1111<<4);
			if(PORTx==GPIOA)     {AFIO->EXTICR1 &=~(0b1111<<4);}
			else if(PORTx==GPIOB){AFIO->EXTICR1 |= (0b0001<<4);}
			else if(PORTx==GPIOC){AFIO->EXTICR1 |= (0b0010<<4);}
			else if(PORTx==GPIOD){AFIO->EXTICR1 |= (0b0011<<4);}

			break;
		case PIN_2:
			AFIO->EXTICR1 &=~(0b1111<<8);
			if(PORTx==GPIOA)     {AFIO->EXTICR1 &=~(0b1111<<8);}
			else if(PORTx==GPIOB){AFIO->EXTICR1 |= (0b0001<<8);}
			else if(PORTx==GPIOC){AFIO->EXTICR1 |= (0b0010<<8);}
			else if(PORTx==GPIOD){AFIO->EXTICR1 |= (0b0011<<8);}

			break;
		case PIN_3:
			AFIO->EXTICR1 &=~(0b1111<<12);
			if(PORTx==GPIOA)     {AFIO->EXTICR1 &=~(0b1111<<12);}
			else if(PORTx==GPIOB){AFIO->EXTICR1 |= (0b0001<<12);}
			else if(PORTx==GPIOC){AFIO->EXTICR1 |= (0b0010<<12);}
			else if(PORTx==GPIOD){AFIO->EXTICR1 |= (0b0011<<12);}

			break;
			//			AFIO_EXTICR2
			//			0000: PA[x] pin
			//			0001: PB[x] pin
			//			0010: PC[x] pin
			//			0011: PD[x] pin
		case PIN_4:
			AFIO->EXTICR2 &=~(0b1111<<0);
			if(PORTx==GPIOA)     {AFIO->EXTICR2 &=~(0b1111<<0);}
			else if(PORTx==GPIOB){AFIO->EXTICR2 |= (0b0001<<0);}
			else if(PORTx==GPIOC){AFIO->EXTICR2 |= (0b0010<<0);}
			else if(PORTx==GPIOD){AFIO->EXTICR2 |= (0b0011<<0);}

			break;
		case PIN_5:
			AFIO->EXTICR2 &=~(0b1111<<4);
			if(PORTx==GPIOA)     {AFIO->EXTICR2 &=~(0b1111<<4);}
			else if(PORTx==GPIOB){AFIO->EXTICR2 |= (0b0001<<4);}
			else if(PORTx==GPIOC){AFIO->EXTICR2 |= (0b0010<<4);}
			else if(PORTx==GPIOD){AFIO->EXTICR2 |= (0b0011<<4);}

			break;
		case PIN_6:
			AFIO->EXTICR2 &=~(0b1111<<8);
			if(PORTx==GPIOA)     {AFIO->EXTICR2 &=~(0b1111<<8);}
			else if(PORTx==GPIOB){AFIO->EXTICR2 |= (0b0001<<8);}
			else if(PORTx==GPIOC){AFIO->EXTICR2 |= (0b0010<<8);}
			else if(PORTx==GPIOD){AFIO->EXTICR2 |= (0b0011<<8);}

			break;
		case PIN_7:
			AFIO->EXTICR2 &=~(0b1111<<12);
			if(PORTx==GPIOA)     {AFIO->EXTICR2 &=~(0b1111<<12);}
			else if(PORTx==GPIOB){AFIO->EXTICR2 |= (0b0001<<12);}
			else if(PORTx==GPIOC){AFIO->EXTICR2 |= (0b0010<<12);}
			else if(PORTx==GPIOD){AFIO->EXTICR2 |= (0b0011<<12);}

			break;
			//			AFIO_EXTICR3
			//			0000: PA[x] PIN_
			//			0001: PB[x] pin
			//			0010: PC[x] pin
			//			0011: PD[x] pin
		case PIN_8:
			AFIO->EXTICR3 &=~(0b1111<<0);
			if(PORTx==GPIOA)     {AFIO->EXTICR3 &=~(0b1111<<0);}
			else if(PORTx==GPIOB){AFIO->EXTICR3 |= (0b0001<<0);}
			else if(PORTx==GPIOC){AFIO->EXTICR3 |= (0b0010<<0);}
			else if(PORTx==GPIOD){AFIO->EXTICR3 |= (0b0011<<0);}

			break;
		case PIN_9:
			AFIO->EXTICR3 &=~(0b1111<<4);
			if(PORTx==GPIOA)     {AFIO->EXTICR3 &=~(0b1111<<4);}
			else if(PORTx==GPIOB){AFIO->EXTICR3 |= (0b0001<<4);}
			else if(PORTx==GPIOC){AFIO->EXTICR3 |= (0b0010<<4);}
			else if(PORTx==GPIOD){AFIO->EXTICR3 |= (0b0011<<4);}

			break;
		case PIN_10:
			AFIO->EXTICR3 &=~(0b1111<<8);
			if(PORTx==GPIOA)     {AFIO->EXTICR3 &=~(0b1111<<8);}
			else if(PORTx==GPIOB){AFIO->EXTICR3 |= (0b0001<<8);}
			else if(PORTx==GPIOC){AFIO->EXTICR3 |= (0b0010<<8);}
			else if(PORTx==GPIOD){AFIO->EXTICR3 |= (0b0011<<8);}

			break;
		case PIN_11:
			AFIO->EXTICR3 &=~(0b1111<<12);
			if(PORTx==GPIOA)     {AFIO->EXTICR3 &=~(0b1111<<12);}
			else if(PORTx==GPIOB){AFIO->EXTICR3 |= (0b0001<<12);}
			else if(PORTx==GPIOC){AFIO->EXTICR3 |= (0b0010<<12);}
			else if(PORTx==GPIOD){AFIO->EXTICR3 |= (0b0011<<12);}

			break;
			//			AFIO_EXTICR4
			//			0000: PA[x] pin
			//			0001: PB[x] pin
			//			0010: PC[x] pin
			//			0011: PD[x] pin
		case PIN_12:
			AFIO->EXTICR4 &=~(0b1111<<0);
			if(PORTx==GPIOA)     {AFIO->EXTICR4 &=~(0b1111<<0);}
			else if(PORTx==GPIOB){AFIO->EXTICR4 |= (0b0001<<0);}
			else if(PORTx==GPIOC){AFIO->EXTICR4 |= (0b0010<<0);}
			else if(PORTx==GPIOD){AFIO->EXTICR4 |= (0b0011<<0);}

			break;
		case PIN_13:
			AFIO->EXTICR4 &=~(0b1111<<4);
			if(PORTx==GPIOA)     {AFIO->EXTICR4 &=~(0b1111<<4);}
			else if(PORTx==GPIOB){AFIO->EXTICR4 |= (0b0001<<4);}
			else if(PORTx==GPIOC){AFIO->EXTICR4 |= (0b0010<<4);}
			else if(PORTx==GPIOD){AFIO->EXTICR4 |= (0b0011<<4);}

			break;
		case PIN_14:
			AFIO->EXTICR4 &=~(0b1111<<8);
			if(PORTx==GPIOA)     {AFIO->EXTICR4 &=~(0b1111<<8);}
			else if(PORTx==GPIOB){AFIO->EXTICR4 |= (0b0001<<8);}
			else if(PORTx==GPIOC){AFIO->EXTICR4 |= (0b0010<<8);}
			else if(PORTx==GPIOD){AFIO->EXTICR4 |= (0b0011<<8);}

			break;
		case PIN_15:
			AFIO->EXTICR4 &=~(0b1111<<12);
			if(PORTx==GPIOA)     {AFIO->EXTICR4 &=~(0b1111<<12);}
			else if(PORTx==GPIOB){AFIO->EXTICR4 |= (0b0001<<12);}
			else if(PORTx==GPIOC){AFIO->EXTICR4 |= (0b0010<<12);}
			else if(PORTx==GPIOD){AFIO->EXTICR4 |= (0b0011<<12);}

			break;
		}
	//================================================
	//3- Update Rising or Falling Register
	EXTI->RTSR &=~(1<<pin);
	EXTI->FTSR &=~(1<<pin);
	if(triggercase == EXTI_Trigger_Rising){
		EXTI->RTSR |= (1<<pin);
	}
	else if(triggercase == EXTI_Trigger_Falling){
		EXTI->FTSR |= (1<<pin);
	}
	else{
		EXTI->RTSR |= (1<<pin);
		EXTI->FTSR |= (1<<pin);
	}
	//4- Update IRQ Handling callback
	GP_IRQ_Callback[pin] =function_addres;


	EXTI->IMR |=(1<<pin);

	Enable_NVIC(pin);
}



void EXTI0_IRQHandler(void){
	// clear bit in pending register (EXTI_PR)
	EXTI->PR |= (1<<0);
	GP_IRQ_Callback[0]();
}

void EXTI1_IRQHandler(void){
	EXTI->PR |= (1<<1);
	GP_IRQ_Callback[1]();

}

void EXTI2_IRQHandler(void){
	EXTI->PR |= (1<<2);
	GP_IRQ_Callback[2]();
}

void EXTI3_IRQHandler(void){
	EXTI->PR |= (1<<3);
	GP_IRQ_Callback[3]();
}

void EXTI4_IRQHandler(void){
	EXTI->PR |= (1<<4);
	GP_IRQ_Callback[4]();
}

void EXTI9_5_IRQHandler(void){
	if(EXTI->PR & (1<<5)) {EXTI->PR |= (1<<5); GP_IRQ_Callback[5]();  }
	if(EXTI->PR & (1<<6)) {EXTI->PR |= (1<<6); GP_IRQ_Callback[6]();  }
	if(EXTI->PR & (1<<7)) {EXTI->PR |= (1<<7); GP_IRQ_Callback[7]();  }
	if(EXTI->PR & (1<<8)) {EXTI->PR |= (1<<8); GP_IRQ_Callback[8]();  }
	if(EXTI->PR & (1<<9)) {EXTI->PR |= (1<<9); GP_IRQ_Callback[9]();  }
}

void EXTI15_10_IRQHandler(void){
	if(EXTI->PR & (1<<10)) {EXTI->PR |= (1<<10); GP_IRQ_Callback[10]();  }
	if(EXTI->PR & (1<<11)) {EXTI->PR |= (1<<11); GP_IRQ_Callback[11]();  }
	if(EXTI->PR & (1<<12)) {EXTI->PR |= (1<<12); GP_IRQ_Callback[12]();  }
	if(EXTI->PR & (1<<13)) {EXTI->PR |= (1<<13); GP_IRQ_Callback[13]();  }
	if(EXTI->PR & (1<<14)) {EXTI->PR |= (1<<14); GP_IRQ_Callback[14]();  }
	if(EXTI->PR & (1<<15)) {EXTI->PR |= (1<<15); GP_IRQ_Callback[15]();  }

}

/**================================================================
 * @Fn              - MCAL_EXTI_GPIO_DEINIT
 * @brief           - Reset External interrupt registers and NVIC coresponding IRQ mask
 * @retval          - none
 *================================================================ */

/**================================================================
 * @Fn              - MCAL_EXTI_GPIO_DEINIT
 * @brief           - Reset External interrupt registers and NVIC coresponding IRQ mask
 * @retval          - none
 *================================================================ */
void MCAL_EXTI_GPIO_DEINIT(void){
	EXTI->IMR = 0x00000000;
	EXTI->EMR = 0x00000000;
	EXTI->FTSR = 0x00000000;
	EXTI->RTSR = 0x00000000;
	EXTI->SWIER = 0x00000000;
	EXTI->PR = 0xFFFFFFFF;



	NVIC_IRQ6_EXTI0_Disable;
	NVIC_IRQ7_EXTI1_Disable;
	NVIC_IRQ8_EXTI2_Disable;
	NVIC_IRQ9_EXTI3_Disable;
	NVIC_IRQ10_EXTI4_Disable;
	NVIC_IRQ23_EXTI5_9_Disable;
	NVIC_IRQ40_EXTI10_15_Disable;


}


