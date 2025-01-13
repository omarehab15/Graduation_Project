/*
 * RCC.c
 *
 *  Created on: Jan 27, 2024
 *      Author: Kareem Abelkader
 */

/******************************************************************************
*                               INCLUDES			                          *
*******************************************************************************/
#include "GPIO.h"


/******************************************************************************
*                           APIS IMPLEMENTATION			                      *
*******************************************************************************/
uint8_t getposition(uint16_t pin_num){
	uint8_t rval;
	if(pin_num == PIN_0){
		rval =0;
	}
	if(pin_num == PIN_1){
		rval =4;
	}
	if(pin_num == PIN_2){
		rval =8;
	}
	if(pin_num == PIN_3){
		rval =12;
	}
	if(pin_num == PIN_4){
		rval =16;
	}
	if(pin_num == PIN_5){
		rval =20;
	}
	if(pin_num == PIN_6){
		rval =24;
	}
	if(pin_num == PIN_7){
		rval =28;
	}
	if(pin_num == PIN_8){
		rval =0;
	}
	if(pin_num == PIN_9){
		rval =4;
	}
	if(pin_num == PIN_10){
		rval =8;
	}
	if(pin_num == PIN_11){
		rval =12;
	}
	if(pin_num == PIN_12){
		rval =16;
	}
	if(pin_num == PIN_13){
		rval =20;
	}
	if(pin_num == PIN_14){
		rval =24;
	}
	if(pin_num == PIN_15){
		rval =28;
	}
	return rval;


}


//**================================================================
//* @Fn- pinmode
// * @brief - Initialize a specified GPIO port with specified configurations modes
// * @param [in] - GPIOx: where x can be (A...E Depending on device used) to select the GPIO Peripheral
// * @param [in] - pin: pin name
// * @param [in] - pinmode:mode of the pin
// * @retval -none
// * Note-
void MCAL_GPIO_INIT(GPIO_TypeDef* GPIOx,uint16_t pin,uint32_t pinmode){
	if(GPIOx==GPIOA){
		MCAL_RCC_Peripherals_enable(APB2, RCC_GPIOA, Enable);

	}
	else if(GPIOx==GPIOB){
		MCAL_RCC_Peripherals_enable(APB2, RCC_GPIOB, Enable);

	}
	else{
		MCAL_RCC_Peripherals_enable(APB2, RCC_GPIOC, Enable);
	}

	if(pin<8){
		GPIOx->CRL &=~(0xf<<(getposition(pin)));

		if((pinmode==Input_PD_Mode)||(pinmode==Input_PU_Mode)){
			if(pinmode == Input_PU_Mode){
				GPIOx->CRL |=(0b1000<<(getposition(pin)));
				GPIOx->ODR |= (1<<pin);
			}
			else{
				GPIOx->CRL |=(0b1000<<(getposition(pin)));
				GPIOx->ODR &=~(1<<pin);
			}

		}
		else GPIOx->CRL |=(pinmode<<(getposition(pin)));

	}
	else if(pin>7){
		//GPIOx->GPIOx_CRH
		GPIOx->CRH &=~(0xf<<(getposition(pin)));

		if((pinmode==Input_PD_Mode)||(pinmode==Input_PU_Mode)){
			if(pinmode == Input_PU_Mode){
				GPIOx->CRH |=(0b1000<<(getposition(pin)));
				GPIOx->ODR |= (1<<pin);
			}
			else{
				GPIOx->CRH |=(0b1000<<(getposition(pin)));
				GPIOx->ODR &=~(1<<pin);
			}

		}
		else GPIOx->CRH |=(pinmode<<(getposition(pin)));

	}



}


/**================================================================
 * @Fn			- MCAL_GPIO_DEINIT
 * @brief 		- Reset the GPIOx PINy according to a specific parameter in the Pin Configuration
 * @param [in] 	- GPIOx: x can be (A:G depend on the device used) to select the GPIO peripheral
 * @retval 		- none
 * Note			- Can be reset by reset controller
 */
void MCAL_GPIO_DEINIT(GPIO_TypeDef* GPIOx){
	GPIOx->CRL  = 0x44444444;
	GPIOx->CRH  = 0x44444444;
	GPIOx->ODR  = 0x00000000;
	GPIOx->BSRR = 0x00000000;
	GPIOx->BRR  = 0x00000000;
	GPIOx->LCKR = 0x00000000;
}


/**================================================================
 * @Fn- pinwrite
 * @brief - Write the GPIOx PINy according to specified parameters in Pin_config
 * @param [in] - GPIOx: where x can be (A...E Depending on device used) to select the GPIO Peripheral
 * @param [in] - pin: GPIOx PIN Number
 * @param [in] - status: The desired value to write
 * @retval - None
 * Note-
 */
void MCAL_GPIO_WRITEPIN(GPIO_TypeDef* GPIOx,uint16_t pin,uint8_t status){
	if(status!=0){
		GPIOx->ODR |=(1<<pin);
	}
	else GPIOx->ODR &=~(1<<pin);

}


/**================================================================
 * @Fn- WRITE_PORT
 * @brief - Write the GPIOx according to specified parameters in Pin_config
 * @param [in] - GPIOx: where x can be (A...E Depending on device used) to select the GPIO Peripheral
 * @param [in] - value: The desired value to write
 * @retval -
 * Note-
 */
void WRITE_PORT(GPIO_TypeDef* GPIOx,uint16_t status){
	GPIOx->ODR = (uint16_t)status;

}


/**================================================================
 * @Fn- set_valio_PORT
 * @brief - Write the GPIOx according to specified parameters in Pin_config
 * @param [in] - GPIOx: where x can be (A...E Depending on device used) to select the GPIO Peripheral
 * @param [in] - value: The desired value to write
 * @param [in] - position:position of seting Values
 * @retval -
 * Note-
 */

void set_Value_PORT(GPIO_TypeDef* GPIOx,uint16_t status,uint16_t position){

	GPIOx->ODR |=(status<<position);
}


/**================================================================
 * @Fn- set_valio_PORT
 * @brief - Write the GPIOx according to specified parameters in Pin_config
 * @param [in] - GPIOx: where x can be (A...E Depending on device used) to select the GPIO Peripheral
 * @param [in] - value: The desired value to write
 * @param [in] - position:position of seting Values
 * @retval -
 * Note-
 */

void res_Value_PORT(GPIO_TypeDef* GPIOx,uint16_t status,uint16_t position){

	GPIOx->ODR &=~(status<<position);
}


/**================================================================
 * @Fn              - READ_PIN
 * @brief           - Read the GPIOx PINy according to specified parameters in Pin_config
 * @param [in]      - GPIOx: where x can be (A...E Depending on device used) to select the GPIO Peripheral
 * @param [in]      - Pin: GPIOx PIN Number
 * @retval          - uint8_t
 * Note             - none
 */

uint8_t READ_PIN(GPIO_TypeDef* GPIOx, uint16_t pin){
	return (GPIOx->IDR>>pin)&1;
}


/**================================================================
 * @Fn              - READ_PORT
 * @brief           - Read the GPIOx _PORT according to specified parameters in Pin_config
 * @param [in]      - GPIOx:  GPIO Peripheral

 * @retval          - uint16_t
 * Note             - none
 */
uint16_t READ_PORT(GPIO_TypeDef* GPIOx){

	return GPIOx->IDR;
}


/**================================================================
 * @Fn			- MCAL_GPIO_TOGGLEPIN
 * @brief 		- Toggle a specific pin
 * @param [in] 	- GPIOx: x can be (A:G depend on the device used) to select the GPIO peripheral
 * @param [in] 	- PinNumber: the selected pin according to GPIO_PINS_DEF
 * @retval 		- none
 * Note			- none
 */
void TogglePin(GPIO_TypeDef* GPIOx, uint16_t pin){
	GPIOx->ODR ^=(1<<pin);
}


/**================================================================
 * @Fn			- MCAL_GPIO_TOGGLEPORT
 * @brief 		- Toggle the port
 * @param [in] 	- GPIOx: x can be (A:G depend on the device used) to select the GPIO peripheral
 * @retval 		- none
 * Note			- none
 */
void MCAL_GPIO_TOGGLEPORT(GPIO_TypeDef* GPIOx)
{
	GPIOx->ODR ^= 0xFFFF;
}


/**================================================================
 * @Fn			- MCAL_GPIO_LOCKPIN
 * @brief 		- Lock a specific pin
 * @param [in] 	- GPIOx: x can be (A:G depend on the device used) to select the GPIO peripheral
 * @param [in] 	- PinNumber: the selected pin according to GPIO_PINS_DEF
 * @retval 		- Pin_LOCKED if the pin locked, Pin_UNLOCKED if the pin not locked according to GPIO PIN LOCK DEF
 * Note			- none
 */
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef* GPIOx, uint16_t PinNumber)
{
	volatile uint32_t temp = 1<<16;

	/*
	 * LCKK[16]: Lock key
		   This bit can be read any time. It can only be modified using the Lock Key Writing Sequence.
		   0: Port configuration lock key not active
		   1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset
		   LCKy: Port x Lock bit y (y= 0 .. 15)
		   These bits are read write but can only be written when the LCKK bit is 0.
			0: Port configuration not locked
			1: Port configuration locked
	 */

	GPIOx->LCKR |= PinNumber;

	//Writing Sequence.
	//Write 1
	GPIOx->LCKR = temp;
	//Write 0
	GPIOx->LCKR = (uint32_t)PinNumber;
	//Write 1
	GPIOx->LCKR = temp;
	//Read 0
	temp = GPIOx->LCKR;
	//Read 1
	if( (uint32_t)(GPIOx->LCKR & (1<<16)) ){
		return LOCKED;
	}
	else{
		return UNLOCKED;
	}
}
