/*
 * RCC.c
 *
 *  Created on: Jan 27, 2024
 *      Author: Kareem Abelkader
 */

/******************************************************************************
*                               INCLUDES			                          *
*******************************************************************************/
#include"RCC.h"


/******************************************************************************
*                           APIS IMPLEMENTATION			                      *
*******************************************************************************/

/**================================================================
 * @Fn			-MCAL_RCC_Peripherals_enable
 * @brief 		-RCC enable the MCU Peripherals
 * @param[in] 	-bus:to select the bus
 * @param[in] 	-peripheral:to select which peripheral to enable
 * @param[in] 	-status:to choose between enable or disable
 * @param[out] 	-none
 * @retval		-none
 * Note			-none
 */
void MCAL_RCC_Peripherals_enable(RCC_Buses_t bus , uint16_t peripheral , uint8_t status)
{
	switch(bus)
	{
	case AHB :
	{

		RCC->AHBENR &=~ (status << peripheral);
		RCC->AHBENR |=  (status << peripheral);
	}
	break ;
	case APB1 :
	{
		RCC->APB1ENR &=~ (status << peripheral);
		RCC->APB1ENR |=  (status << peripheral);
	}
	break ;
	case APB2 :
	{
		RCC->APB2ENR &=~ (status << peripheral);
		RCC->APB2ENR |=  (status << peripheral);
	}
	break ;
	}

}


/**================================================================
 * @Fn			-MCAL_RCC_Peripherals_enable
 * @brief 		-RCC Reset the MCU Peripherals
 * @param[in] 	-bus:to select the bus
 * @param[in] 	-peripheral:to select which peripheral to Reset
 * @param[in] 	-status:to choose between Reset or Rereset
 * @param[out] 	-none
 * @retval		-none
 * Note			-AHB bus can't be used with this function
 */
void MCAL_RCC_Peripherals_Reset(RCC_Buses_t bus , uint16_t peripheral , uint8_t status)
{
	switch(bus)
	{
	case AHB :
	{
		break;
	}
	break ;
	case APB1 :
	{
		RCC->APB1RSTR &=~ (status << peripheral);
		RCC->APB1RSTR |=  (status << peripheral);
	}
	break ;
	case APB2 :
	{
		RCC->APB2RSTR &=~ (status << peripheral);
		RCC->APB2RSTR |=  (status << peripheral);
	}
	break ;
	}

}


/**================================================================
 * @Fn			-MCAL_RCC_GetSYS_CLCKFreq
 * @brief 		-to set System bus frequency
 * @param[in] 	-RCC_Speed: to choose the frequency
 * @param[out] 	-none
 * @retval		-none
 * Note			-none
 */
void MCAL_RCC_GetSYS_CLCKFreq(RCC_speed_t RCC_Speed)
{
	switch(RCC_Speed)
	{
	case RCC_8MHZ:
	{
		//---------------------------------
		//HSI ON
		//---------------------------------
		RCC->CR |= (1 << 0);
		//---------------------------------
		//System clock Switch
		//---------------------------------
		RCC->CFGR &=~ (0b11 << 0);
	}
	break;
	case RCC_36MHZ:
	{
		//---------------------------------
		//HSI ON
		//---------------------------------
		RCC->CR |= (1 << 0);
		//---------------------------------
		//PLL entry clock source
		//---------------------------------
		RCC->CFGR &=~ (1 << 16);
		//---------------------------------
		//PLL multiplication factor :0111: PLL input clock x 9 sysclock = 36MHZ
		//---------------------------------
		RCC->CFGR &=~ (0b1111 << 18);
		RCC->CFGR |= (0b0111 << 18);
		//---------------------------------
		//PLL enable
		//---------------------------------
		RCC->CR |= (1 << 24);
		//---------------------------------
		//System clock Switch
		//---------------------------------
		RCC->CFGR &=~ (0b11 << 0);
		RCC->CFGR |=  (0b10 << 0);
	}
	break;
	case RCC_32MHZ:
	{
		//---------------------------------
		//HSE ON
		//---------------------------------
		RCC->CR |= (1 << 16);
		//---------------------------------
		//HSE divider for PLL entry
		//---------------------------------
		RCC->CFGR &=~ (1 << 17);
		//---------------------------------
		//PLL entry clock source
		//---------------------------------
		RCC->CFGR &=~ (1 << 16);
		RCC->CFGR |=  (1 << 16);
		//---------------------------------
		//PLL multiplication factor :0010: PLL input clock x 4 = 32MHZ
		//---------------------------------
		RCC->CFGR &=~ (0b1111 << 18);
		RCC->CFGR |= (0010 << 18);
		//---------------------------------
		//PLL enable
		//---------------------------------
		RCC->CR |= (1 << 24);
		//---------------------------------
		//System clock Switch
		//---------------------------------
		RCC->CFGR &=~ (0b11 << 0);
		RCC->CFGR |=  (0b10 << 0);


	}
	break;
	}

}


/**================================================================
 * @Fn			-MCAL_RCC_GetHCLKFreq
 * @brief 		-to set AHB bus frequency
 * @param[in] 	-none
 * @param[out] 	-none
 * @retval		-none
 * Note			-none
 */
uint32_t MCAL_RCC_GetHCLKFreq(void)
{
	/*
	 * 0xxx: SYSCLK not divided
	 *1000: SYSCLK divided by 2
	 *1001: SYSCLK divided by 4
	 *1010: SYSCLK divided by 8
	 *1011: SYSCLK divided by 16
	 *1100: SYSCLK divided by 64
	 *1101: SYSCLK divided by 128
	 *1110: SYSCLK divided by 256
	 *1111: SYSCLK divided by 512
	 */
	return RCC->CFGR &=~  (0b1111 << 4)   ;
}


/**================================================================
 * @Fn			-MCAL_RCC_GetPCLK1Freq
 * @brief 		-to set APB1 bus frequency
 * @param[in] 	-none
 * @param[out] 	-none
 * @retval		-none
 * Note			-none
 */
uint32_t MCAL_RCC_GetPCLK1Freq(void)
{
	/*
	 *0xx: HCLK not divided
	 *100: HCLK divided by 2
	 *101: HCLK divided by 4
	 *110: HCLK divided by 8
	 *111: HCLK divided by 16
	 */

	return RCC->CFGR  &=~ (0b111 << 8)   ;
}


/**================================================================
 * @Fn			-MCAL_RCC_GetPCLK2Freq
 * @brief 		-to set APB2 bus frequency
 * @param[in] 	-none
 * @param[out] 	-none
 * @retval		-none
 * Note			-none
 */
uint32_t MCAL_RCC_GetPCLK2Freq(void)
{
	/*
	 *0xx: HCLK not divided
	 *100: HCLK divided by 2
	 *101: HCLK divided by 4
	 *110: HCLK divided by 8
	 *111: HCLK divided by 16
	 */
	return RCC->CFGR &=~  (0b111 << 11)   ;
}


/**================================================================
 * @Fn			-MCAL_RCC_GetPCLK2_ADCFreq
 * @brief 		-to set ADC frequency
 * @param[in] 	-none
 * @param[out] 	-none
 * @retval		-none
 * Note			-none
 */
uint32_t MCAL_RCC_GetPCLK2_ADCFreq(void)
{
	return RCC->CFGR |= (0b01 << 14)   ;
}
