/*
 * UART.c
 *
 *  Created on: Feb 13, 2024
 *      Author: KARIM
 */

/******************************
 * Includes
 *******************************/
#include"UART.h"

//==========================================================================

/*
 * ------------------------------------------------
 * 				  Generic Variables
 *-------------------------------------------------
 */



//===========================================================================

/**================================================================
 * @Fn				-MCAL_USART_Init
 * @brief 			-Initializes USART (Supported feature ASYNCH. Only)
 * @param [in] 		-USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		-USART_Config: All UART Configuration EXTI_PinConfig_t
 * @retval 			-none
 * Note				-Support for Now Asynch mode & Clock 8 MHZ S
 */
void MCAL_USART_INIT(USART_TypeDef* USARTx, USART_Config* USART_ConFig){

	//enable the Clock for given USART peripheral
	if ( USARTx == USART1 )
	{
		MCAL_RCC_Peripherals_enable(APB2, RCC_USART1, Enable);
	}
	else if ( USARTx == USART2 )
	{
		MCAL_RCC_Peripherals_enable(APB1, RCC_USART2, Enable);
	}
	else if ( USARTx == USART3 )
	{
		MCAL_RCC_Peripherals_enable(APB1, RCC_USART3, Enable);
	}

	//(USART_CR1): Bit13 UE: USART enable
	USARTx->CR1 |= 1<<13;

	//Enable USART Tx and Rx engines according to the Mode_Def configuration item
	//(USART_CR1): Bit3 TE: Transmitter enable - Bit2 RE: Receiver enable
	USARTx->CR1 |= USART_ConFig->Mode;

	//(USART_CR1): Bit12 M: Word length
	USARTx->CR1 |= USART_ConFig->Data_Len;

	//(USART_CR1): Bit10 PCE: Parity control enable - Bit9 PS: Parity selection
	USARTx->CR1 |= USART_ConFig->Parity;

	//(USART_CR2): Bits13:12 STOP: STOP bits
	USARTx->CR2 |= USART_ConFig->StopBit;

	//(USART_CR3): Bit10 CTSIE: CTS interrupt enable - Bit9 CTSE: CTS enable
	//(USART_CR3): Bit8 RTSE: RTS enable
	USARTx->CR3 |= USART_ConFig->Flow_Ctl;

	uint32_t pclk, BRR;
	//PCLK1 for USART2, 3
	//PCLK2 for USART1
	if ( USARTx == USART1 )
	{
		pclk = MCAL_RCC_GetPCLK2Freq();
	}
	else
	{
		pclk = MCAL_RCC_GetPCLK1Freq();
	}

	BRR = UART_BRR_Register(pclk, USART_ConFig->Buadrate) ;
	USARTx->BRR = BRR;

	if (USART_ConFig->IRQ_EN  != IRQ_DISABLE)
	{
		USARTx->CR1 |= (USART_ConFig->IRQ_EN) ;
		//Enable NVIC For USARTx IRQ
		if ( USARTx == USART1 )
			NVIC_USART1_interrupt_Enable;

		else if ( USARTx == USART2 )
			NVIC_USART2_interrupt_Enable;

		else if ( USARTx == USART3 )
			NVIC_USART3_interrupt_Enable;
	}
}


/**================================================================
 * @Fn				-MCAL_USART_DEInit
 * @brief 			-DEInitializes UART (Supported feature ASYNCH. Only)
 * @param [in] 		-USARTx: where x can be (1..3 depending on device used)
 * @retval 			-none
 * Note				-Reset the Model By RCC
 */
void MCAL_USART_DEINIT(USART_TypeDef* USARTx){
	if ( USARTx == USART1 )
	{
		MCAL_RCC_Peripherals_Reset(APB2, RCC_USART1, Enable);
		NVIC_USART1_interrupt_Disable ;

	}

	else if ( USARTx == USART2 )
	{
		MCAL_RCC_Peripherals_Reset(APB1, RCC_USART2, Enable);
		NVIC_USART2_interrupt_Disable ;


	}

	else if ( USARTx == USART3 )
	{
		MCAL_RCC_Peripherals_Reset(APB1, RCC_USART3, Enable);
		NVIC_USART3_interrupt_Disable ;

	}
}


/*********************************************************************
 * @fn      		  -MCAL_USART_SendData
 * @brief             -Send Buffer on UART
 * @param [in] 		  -USARTx: where x can be (1..3 depending on device used)
 * @param[in]         -Buffer: Buffer
 * @param[in]         -PollingEn: Enable pooling or disable it
 * @return            -none
 * @Note              -Should initialize UART First
 */
void MCAL_USART_SEND_DATA(USART_TypeDef* USARTx, uint16_t* Buffer, enum Polling_Mechanism PollingEN){
	USART_Config* USART_config;

	//Status register (USART_SR): Bit7 TXE: Transmit data register empty
	//Wait until TXE flag is set in the SR register
	if(PollingEN == enable){
		while(! (USARTx->SR & 1<<7) );
	}

	//Check if the data 9bit or 8bit
	if(USART_config->Data_Len == Data_Len_9){
		//Data register (USART_DR)
		//access all register bits (0:8)
		USARTx->DR = (*Buffer & (uint16_t)0x01FF);
	}
	else{
		//Data register (USART_DR)
		//access register bits (0:7)
		USARTx->DR = (*Buffer & (uint16_t)0xFF);
	}

}


/*********************************************************************
 * @fn      		  -MCAL_USART_READ_DATA
 * @brief             -Read Buffer from USART
 * @param [in] 		  -USARTx: where x can be (1..3 depending on device used)
 * @param[in]         -Buffer: Buffer
 * @param[in]         -PollingEn: Enable pooling or disable it
 * @return            -none
 * @Note              -Should initialize UART First
 */
void MCAL_USART_READ_DATA(USART_TypeDef* USARTx, uint16_t* Buffer, enum Polling_Mechanism PollingEN){
	USART_Config UART_CFG;

	//Status register (USART_SR): Bit 5 RXNE: Read data register not empty
	//Wait until RXNE flag is set in the SR register
	if(PollingEN == enable){
		while(! (USARTx->SR & 1<<5) );
	}

	//Check if the data 9bit or 8bit
	if(UART_CFG.Data_Len == Data_Len_9){
		if(UART_CFG.Parity == Parity_DISABLE){
			//All 9bits are considered data
			(* Buffer) = USARTx->DR;
		}
		else{
			//Parity is used, data will be 8bits
			(* Buffer) = (USARTx->DR & (uint8_t)0xff);
		}
	}
	else{
		if(UART_CFG.Parity == Parity_DISABLE){
			//All 8bits are considered data
			(* Buffer) = (USARTx->DR & (uint8_t)0xff);
		}
		else{
			//Parity is used, data will be 7bits
			(* Buffer) = (USARTx->DR & (uint8_t)0x7f);
		}
	}

}


/**================================================================
 * @Fn				-MCAL_UART_WAIT_TC
 * @brief 			-Wait till TC flag is set in the SR
 * @param [in] 		-USARTx: where x can be (1..3 depending on device used)
 * @retval 			-none
 * Note				-none
 */
void MCAL_UART_WAIT_TC(USART_TypeDef* USARTx){
	while( ! (USARTx->SR & 1<<6 ));
}


/**================================================================
 * @Fn				-MCAL_USART_SETPIN
 * @brief 			-initialize GPIO Pins
 * @param [in] 		-USARTx: where x can be (1..3 depending on device used)
 * @retval 			-none
 * Note				-Should enable the corresponding ALT & GPIO in RCC clock Also called after MCAL_USART_INIT()
 */
void MCAL_USART_SETPIN(USART_TypeDef* USARTx){

	USART_Config* USART_config;

	if(USARTx == USART1){
		/*PA9		TX
		 *PA10		RX
		 *PA11		CTS
		 *PA12		RTS
		 */

		//PA9 TX
		MCAL_GPIO_INIT(GPIOA, PIN_9, Output_AF_PP_Mode_Speed10MHZ);

		//PA10
		MCAL_GPIO_INIT(GPIOA, PIN_10, Input_ALF_Mode);

		//PA11 CTS
		if(USART_config->Flow_Ctl == FLOW_CTL_CTS_EN || USART_config->Flow_Ctl == FLOW_CTL_ENABLE){
			MCAL_GPIO_INIT(GPIOA, PIN_11, Input_ALF_Mode);
		}

		//PA12 RTS
		if(USART_config->Flow_Ctl == FLOW_CTL_RTS_EN || USART_config->Flow_Ctl == FLOW_CTL_ENABLE){
			MCAL_GPIO_INIT(GPIOA, PIN_12, Output_AF_PP_Mode_Speed10MHZ);
		}

	}

	if(USARTx == USART2){
		/*PA2		TX
		 *PA3		RX
		 *PA0		CTS
		 *PA1		RTS
		 */

		//PA2		TX
		MCAL_GPIO_INIT(GPIOA, PIN_2, Output_AF_PP_Mode_Speed10MHZ);

		//PA3		RX
		MCAL_GPIO_INIT(GPIOA, PIN_3, Input_ALF_Mode);

		//PA0		CTS
		if(USART_config->Flow_Ctl == FLOW_CTL_CTS_EN || USART_config->Flow_Ctl == FLOW_CTL_ENABLE){
			MCAL_GPIO_INIT(GPIOA, PIN_0, Input_ALF_Mode);
		}

		//PA1		RTS
		if(USART_config->Flow_Ctl == FLOW_CTL_RTS_EN || USART_config->Flow_Ctl == FLOW_CTL_ENABLE){
			MCAL_GPIO_INIT(GPIOA, PIN_1, Output_AF_PP_Mode_Speed10MHZ);
		}
	}

	if(USARTx == USART3){
		/*PB10		TX
		 *PB11		RX
		 *PB13		CTS
		 *PB14		RTS
		 */

		//PB10		TX
		MCAL_GPIO_INIT(GPIOB, PIN_10, Output_AF_PP_Mode_Speed10MHZ);

		//PB11		RX
		MCAL_GPIO_INIT(GPIOB, PIN_11, Input_ALF_Mode);

		//PB13		CTS
		if(USART_config->Flow_Ctl == FLOW_CTL_CTS_EN || USART_config->Flow_Ctl == FLOW_CTL_ENABLE){
			MCAL_GPIO_INIT(GPIOB, PIN_13, Input_ALF_Mode);
		}

		//PB14		RTS
		if(USART_config->Flow_Ctl == FLOW_CTL_RTS_EN || USART_config->Flow_Ctl == FLOW_CTL_ENABLE){
			MCAL_GPIO_INIT(GPIOB, PIN_14, Output_AF_PP_Mode_Speed10MHZ);
		}
	}

}


//ISR
void USART1_IRQHandler (void)
{
	USART_Config* config1;
	config1->P_IRQ_CALLBACK () ;

}

void USART2_IRQHandler (void)
{
	USART_Config* config;
	config->P_IRQ_CALLBACK () ;

}
void USART3_IRQHandler (void)
{
	USART_Config* config;
	config->P_IRQ_CALLBACK () ;
}
