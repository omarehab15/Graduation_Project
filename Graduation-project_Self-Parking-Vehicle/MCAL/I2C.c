/*
 * I2C.c
 *
 *  Created on: Feb 13, 2024
 *      Author: KARIM
 */


/******************************
 * Includes
 *******************************/
#include "I2C.h"

//==========================================================================

/*
 * =====================================================================================
 * 							Generic Variables
 * =====================================================================================
 */

I2C_Config_t Global_I2C_Config[2] = {NULL,NULL};


/*
 * =====================================================================================
 * 							Generic Macros
 * =====================================================================================
 */

#define   I2C1_INDEX             0
#define   I2C2_INDEX             1


/*
 * =====================================================================================
 * 							Generic Functions
 * =====================================================================================
 */

FlagSTATUS I2C_GetFlagSTATUS(I2C_TypeDef *I2Cx, Status Flag)
{
	uint32_t flag1 = 0 ,flag2 = 0;
	uint32_t lastevent = 0;
	FlagSTATUS bitstatus = Reset;

	switch(Flag)
	{
	case I2C_BUS_BUSY:
	{
		//		Bit 1 BUSY: Bus busy
		//		0: No communication on the bus
		//		1: Communication ongoing on the bus
		//		– Set by hardware on detection of SDA or SCL low
		//		– cleared by hardware on detection of a Stop condition.
		//		It indicates a communication in progress on the bus. This information is still updated when
		//		the interface is disabled (PE=0).
		if((I2Cx->SR2) & (I2C_SR2_BUSY))
			bitstatus = Set;
		else
			bitstatus = Reset;
		break;
	}
	case EV5:
	{
		//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
		//		Bit 0 SB: Start bit (Master mode)
		//		0: No Start condition
		//		1: Start condition generated.
		//		– Set when a Start condition generated.
		//		– Cleared by software by reading the SR1 register followed by writing the DR register, or by
		//		hardware when PE=0
		if((I2Cx->SR1) & (I2C_SR1_SB))
			bitstatus = Set;
		else
			bitstatus = Reset;
		break;
	}
	case EV6:
	{
		//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
		// to perform the complete clearing sequence (READ SR1 then READ SR2) after ADDR is set.
		//		Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
		//		This bit is cleared by software reading SR1 register followed reading SR2, or by hardware
		//		when PE=0.
		//		Address matched (Slave)
		//		0: Address mismatched or not received.
		//		1: Received address matched
		if( (I2Cx->SR1) & (I2C_SR1_ADDR))
			bitstatus = Set;
		else
			bitstatus = Reset;
		break;
	}
	case MASTER_BYTE_TRANSMITTING:
	{
		// Read I2C Status Register
		flag1 = I2Cx->SR1;
		flag2 = I2Cx->SR2;
		flag2 = flag2 << 16;
		// Get the last event value from I2C Status Register
		lastevent = ((flag2 | flag1) & (uint32_t)0x00FFFFFF);
		//Check whether the last event contains the I2C_EVENT
		if( (lastevent & MASTER_BYTE_TRANSMITTING) == MASTER_BYTE_TRANSMITTING)
		{
			/* SUCCESS: last event is equal to I2C_EVENT */
			bitstatus = Set;
		}
		else
		{
			/* ERROR: last event is different from I2C_EVENT */
			bitstatus = Reset;
		}
		break;
	}
	case EV8_1://EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
	case EV8://EV8: TxE=1, shift register not empty, d. ata register empty, cleared by writing DR register
	{
		//		Bit 7 TxE: Data register empty (transmitters)
		//		0: Data register not empty
		//		1: Data register empty
		if(I2Cx->SR1 & (I2C_SR1_TXE))
		{
			bitstatus = Set ;
		}
		else
		{
			bitstatus = Reset;
		}
		break;
	}
	case EV8_2://EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
	{
		//		Bit 7 TxE: Data register empty (transmitters)
		//		0: Data register not empty
		//		1: Data register empty
		//----------------------------------------------
		//		Bit 2 BTF: Byte transfer finished
		//		0: Data byte transfer not done
		//		1: Data byte transfer succeeded
		if( (I2Cx->SR1 & (I2C_SR1_TXE))  &&  (I2Cx->SR1 & (I2C_SR1_BTF)))
		{
			bitstatus = Set ;
		}
		else
		{
			bitstatus = Reset;
		}
		break;
	}
	case EV7://EV5: RxNE = 1 Cleared by Reading DR Register
	{
		//		Bit 6 RxNE: Data register not empty (receivers)
		//		0: Data register empty
		//		1: Data register not empty
		if(I2Cx->SR1 & (I2C_SR1_RXNE))
		{
			bitstatus = Set ;
		}
		else
		{
			bitstatus = Reset;
		}
		break;
	}
	}
	return bitstatus;
}


void I2C_AcknowledgeConfig(I2C_TypeDef *I2Cx, Fuctional_State NewState)
{
	if(NewState == ENABLE)
	{
		/* Enable the Acknowledgment */
		I2Cx->CR1 |= I2C_CR1_ACK;
	}
	else
	{
		/* Disable the Acknowledgment */
		I2Cx->CR1 &= ~(I2C_CR1_ACK);
	}
}


void I2C_GenerateSTART(I2C_TypeDef *I2Cx, Fuctional_State NewState, Repeated_Start Start)
{
	if(Start != RepeatedStart)
	{
		//Check if bus is idle
		while(I2C_GetFlagSTATUS(I2Cx, I2C_BUS_BUSY));
	}
	//	Bit 8 START: Start generation
	//	This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
	//	In Master Mode:
	//	0: No Start generation
	//	1: Repeated start generation
	//	In Slave mode:
	//	0: No Start generation
	//	1: Start generation when the bus is free
	if(NewState == ENABLE)
	{
		/*Generate a START Condition*/
		I2Cx->CR1 |= I2C_CR1_START;
	}
	else
	{
		/*Disable The START Condition Generation*/
		I2Cx->CR1 &= ~(I2C_CR1_START);
	}
}


void I2C_GenerateSTOP(I2C_TypeDef *I2Cx, Fuctional_State NewState)
{
	if(NewState == ENABLE)
	{
		/*Generate a START Condition*/
		I2Cx->CR1 |= I2C_CR1_STOP;
	}
	else
	{
		/*Disable The START Condition Generation*/
		I2Cx->CR1 &= ~(I2C_CR1_STOP);
	}
}


void I2C_SendAddress(I2C_TypeDef *I2Cx, uint16_t Address, I2C_Direction Direction)
{
	Address = (Address << 1);

	if(Direction == I2C_Direction_Transmitter)
	{
		/*Reset the address bit0 for write*/
		Address &= ~(1<<0);
	}
	else  //I2C_Direction_Receiver
	{
		/*Set the address bit0 for Read*/
		Address |= (1<<0);
	}
	/*Send The Address*/
	I2Cx->DR = Address ;
}


void Slave_States(I2C_TypeDef *I2Cx,Slave_State State)
{
	uint8_t index = (I2Cx == I2C1) ? I2C1_INDEX : I2C2_INDEX ;

	switch(State)
	{
	case I2C_ERROR_AF:
		//make sure that the slave is really in transmitter mode
		if(I2Cx->SR2 & (I2C_SR2_TRA))
		{
			//Slave shouldn't send anything else
		}
		break;

	case I2C_EV_STOP:
		//make sure that the slave is really in transmitter mode
		if(I2Cx->SR2 & (I2C_SR2_TRA))
		{
			//Notify APP that the Stop Condition is Sent by the master
			Global_I2C_Config[index].P_Slave_Event_CallBack(I2C_EV_STOP);
		}
		break;

	case I2C_EV_ADDR_Matched:
		//Notify APP that The address is matched with The slave address
		Global_I2C_Config[index].P_Slave_Event_CallBack(I2C_EV_ADDR_Matched);
		break;

	case I2C_EV_DATA_REQ:
		//make sure that the slave is really in transmitter mode
		if(I2Cx->SR2 & (I2C_SR2_TRA))
		{
			//The APP Layer should send the data (MCAL_I2C_SlaveSendData)in this state
			Global_I2C_Config[index].P_Slave_Event_CallBack(I2C_EV_DATA_REQ);
		}

		break;

	case I2C_EV_DATA_RCV:
		//make sure that the slave is really in receiver mode
		if(!(I2Cx->SR2 & (I2C_SR2_TRA)) )
		{
			//The APP Layer should read the data (MCAL_I2C_SlaveReceiveData)in this state
			Global_I2C_Config[index].P_Slave_Event_CallBack(I2C_EV_DATA_RCV);
		}

		break;
	}
}


//===============================================================================================

/**================================================================
 * @Fn			- MCAL_I2C_Init
 * @brief 		- Initialization of I2Cx according to a specific configuration
 * @param [in] 	- I2Cx: x can be (1/2) to select the I2C peripheral
 * @param [in] 	- I2C_Config: points to I2C_Config_t that contain the configuration of the I2c
 * @retval 		- none
 * Note			- none
 */
void MCAL_I2C_Init(I2C_TypeDef *I2Cx , I2C_Config_t *I2C_Config){
	uint16_t tempreg = 0  , freqrange = 0 ;
	uint32_t pclk1 = 8000000 ;
	uint16_t result = 0 ;

	if(I2C_Config->I2C_Mode == I2C_Mode_I2C)
	{
		/*----------------- INIT Timing --------------------*/

		//--I2C_CR2.FREQ[5:0]: Peripheral clock frequency
		//get I2C_CR2 Register value
		tempreg = I2Cx->CR2 ;
		// clear Frequency FREQ[5:0] bits
		tempreg &= ~(I2C_CR2_FREQ_Msk);
		//get pclk1 frequency value
		pclk1 = MCAL_RCC_GetPCLK1Freq();
		//set frequency bits depending on pclk1 value
		freqrange = (uint16_t)(pclk1/1000000);

		tempreg |= freqrange ;
		//Write to I2Cx->CR2
		I2Cx->CR2 = tempreg;

		//• Configure the clock control registers I2Cx->CCR

		// Disable the selected I2C peripheral to configure Time
		I2Cx->CR1 &= ~(I2C_CR1_PE);

		tempreg = 0	;

		if (I2C_Config->I2C_ClockSpeed == I2C_SCLK_SM_50K || I2C_Config->I2C_ClockSpeed == I2C_SCLK_SM_100K)
		{
			//Standard Mode Speed Calculation
			// Thigh = CCR * TPCLK1
			// Thigh = Tclk /2
			// CCR = Tclk / (2 * TPCLK1)
			// CCR = Fpclk1 / (2 * I2C_Clock_Frequency)

			result = (uint16_t)(pclk1 / (I2C_Config->I2C_ClockSpeed <<1 )) ;

			tempreg |= result ;


			// Write To I2Cx CCR

			I2Cx->CCR = tempreg ;

			/*--------------I2C_TRISE Configuration--------------*/
			//For instance: in Sm mode, the maximum allowed SCL rise time is 1000 ns.
			//If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
			//therefore the TRISE[5:0] bits must be programmed with 09h
			//(1000 ns / 125 ns = 8 + 1)
			I2Cx->TRISE = freqrange + 1 ;

		}

		else
		{
			// Fast Mode Not Supported
		}

		//Get I2Cx->CR1 value
		tempreg = I2Cx->CR1 ;

		tempreg |= (uint16_t)(I2C_Config->I2C_ACK_Control | I2C_Config->StrechMode | I2C_Config->General_Call_Adress_Detection | I2C_Config->I2C_Mode);


		//Write to I2Cx->CR1
		I2Cx->CR1 = tempreg ;

		/*--------------I2C_OAR1 & I2C_OAR2 Configuration--------------*/
		tempreg = 0;

		if(I2C_Config->I2C_Slave_Address.Enable_Dual_ADD == 1)
		{
			tempreg = I2C_OAR2_ENDUAL ;
			tempreg |= I2C_Config->I2C_Slave_Address.secondary_slave_address << I2C_OAR2_ADD2_Pos;
			I2Cx->OAR2 = tempreg ;
		}

		tempreg = 0;
		tempreg |= I2C_Config->I2C_Slave_Address.primary_slave_address << 1;
		tempreg |= I2C_Config->I2C_Slave_Address.I2C_Addressing_Slave_Mode ;
		I2Cx->OAR1 = tempreg ;
	}

	else
	{
		// I2C Mode SMBUS is not supported yet
	}
	// Interrupt Mode (Slave Mode) //check callback pointer != NULL
	if( I2C_Config->P_Slave_Event_CallBack != NULL) // that enable IRQ States Mode
	{
		//Enable IRQ
		I2Cx->CR2 |= (I2C_CR2_ITBUFEN);
		I2Cx->CR2 |= (I2C_CR2_ITERREN);
		I2Cx->CR2 |= (I2C_CR2_ITEVTEN);

		if(I2Cx == I2C1)
		{
			NVIC_IRQ31_I2C1_EV_Enable();
			NVIC_IRQ32_I2C1_ER_Enable();
		}
		else if(I2Cx == I2C2)
		{
			NVIC_IRQ33_I2C2_EV_Enable();
			NVIC_IRQ34_I2C2_ER_Enable();
		}
		I2Cx->SR1 = 0;
		I2Cx->SR2 = 0;
	}
	// Enable The selected I2C Peripheral
	I2Cx->CR1 |= I2C_CR1_PE ;

}


/**================================================================
 * @Fn			- MCAL_I2C_DeInit
 * @brief 		- DeInitialization of I2Cx according to a specific configuration
 * @param [in] 	- I2Cx: x can be (1/2) to select the I2C peripheral
 * @retval 		- none
 * Note			- none
 */
void MCAL_I2C_DeInit(I2C_TypeDef *I2Cx){
	if( I2Cx == I2C1 ){
		NVIC_IRQ31_I2C1_EV_Disable();
		NVIC_IRQ32_I2C1_ER_Disable();
		MCAL_RCC_Peripherals_enable(APB1, RCC_I2C1, Enable);
	}
	else{
		NVIC_IRQ33_I2C2_EV_Disable();
		NVIC_IRQ34_I2C2_ER_Disable();
		MCAL_RCC_Peripherals_enable(APB1, RCC_I2C2, Enable);
	}
}


/**================================================================
 * @Fn				-MCAL_I2C_Set_Pins
 * @brief 			-initialize GPIO Pins
 * @param [in] 		-I2Cx: where x can be (1/2)
 * @retval 			-none
 * Note				-Should enable the corresponding ALT & GPIO in RCC clock Also called after MCAL_USART_INIT()
 */
void MCAL_I2C_Set_Pins(I2C_TypeDef *I2Cx){

	if(I2Cx == I2C1){
		/* PB6  SCL
		   PB7  SDA */

		//PB6
		MCAL_GPIO_INIT(GPIOB, PIN_6, Output_AF_OD_Mode_Speed10MHZ);

		//PB7
		MCAL_GPIO_INIT(GPIOB, PIN_7, Output_AF_OD_Mode_Speed10MHZ);
	}
	else{
		/* PB10  SCL
		   PB11  SDA */

		//PB10
		MCAL_GPIO_INIT(GPIOB, PIN_10, Output_AF_OD_Mode_Speed10MHZ);

		//PB11
		MCAL_GPIO_INIT(GPIOB, PIN_11, Output_AF_OD_Mode_Speed10MHZ);
	}
}


/* ================================================================
 * @Fn 				- MCAL_I2C_MASTER_TX
 * @brief 			- Master Send data with I2C
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- DevAddr : slave address
 * @param [in] 		- pTxBuffer : a pointer to the data which will be send
 * @param [in] 		- datalen : number of data bytes to be Transmitted
 * @param [in] 		- Stop : select send stop bit or not
 * @param [in] 		- Start : select send start or repeated start
 * @retval 			- None
 * Note 			- None
 */
void MCAL_I2C_Master_TX(I2C_TypeDef *I2Cx, uint16_t DevAddr ,uint8_t* dataOut , uint32_t datalen , Stop_Condition Stop , Repeated_Start Start)
{
	int i = 0;

	//1. Set The START bit in the I2C_CR1 register to generate a start condition
	I2C_GenerateSTART(I2Cx, ENABLE, Start);

	//2. Wait for EV5
	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while(!I2C_GetFlagSTATUS(I2Cx, EV5));

	//3. Send Address
	I2C_SendAddress(I2Cx, DevAddr, I2C_Direction_Transmitter);

	//4. Wait for EV6
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while(!I2C_GetFlagSTATUS(I2Cx, EV6));

	//5. /* TRA(Transmit/Receive) ,BUSY ,MSL(Master/Receive) , TXE Flags(Transmit is empty) */
	while(!I2C_GetFlagSTATUS(I2Cx, MASTER_BYTE_TRANSMITTING));

	for(i=0;i<datalen;i++)
	{
		/* Write on the Data Register the data to be sent */
		I2Cx->DR = dataOut[i];
		//6. Wait for EV8
		//EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
		while(!I2C_GetFlagSTATUS(I2Cx, EV8));
	}

	//7. Wait for EV8_2
	//EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
	while(!I2C_GetFlagSTATUS(I2Cx, EV8_2));

	if(Stop == WithStop)
	{
		//8. Send Stop Condition
		I2C_GenerateSTOP(I2Cx,ENABLE);
	}

}


/* ================================================================
 * @Fn 				- MCAL_I2C_MASTER_RX
 * @brief 			- Master Receive data with I2C
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- DevAddr : slave address
 * @param [in] 		- pRxBuffer : a pointer to the data which will be send
 * @param [in] 		- datalen : number of data bytes to be Received
 * @param [in] 		- Stop : select send stop bit or not
 * @param [in] 		- Start : select send start or repeated start
 * @retval 			- None
 * Note 			- None
 */
void MCAL_I2C_Master_RX(I2C_TypeDef *I2Cx, uint16_t DevAddr ,uint8_t* dataOut , uint32_t datalen , Stop_Condition Stop , Repeated_Start Start)
{
	int i = 0;

	uint8_t index = (I2Cx == I2C1) ? I2C1_INDEX : I2C2_INDEX ;

	//1. Set The START bit in the I2C_CR1 register to generate a start condition
	I2C_GenerateSTART(I2Cx, ENABLE, Start);

	//2. Wait for EV5
	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while(!I2C_GetFlagSTATUS(I2Cx, EV5));

	//3. Send Address
	I2C_SendAddress(I2Cx, DevAddr, I2C_Direction_Receiver);

	//4. Wait for EV6
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while(!I2C_GetFlagSTATUS(I2Cx, EV6));

	I2C_AcknowledgeConfig(I2Cx , ENABLE);

	if(datalen)
	{
		//Read Until Data Length become Zero
		for(i = datalen ; i > 1 ; i--)
		{
			//5. Wait Until RxNE become 1
			//EV5: RxNE = 1 Cleared by Reading DR Register
			while(!I2C_GetFlagSTATUS(I2Cx, EV7));
			//read the data from data register
			*dataOut = I2Cx->DR ;
			//increment the buffer address
			dataOut++;
		}
		I2C_AcknowledgeConfig(I2Cx , DISABLE);
	}

	if(Stop == WithStop)
	{
		//6. Send Stop Condition
		I2C_GenerateSTOP(I2Cx,ENABLE);
	}

	//7. re-enable The Acknowledging
	if(Global_I2C_Config[index].I2C_ACK_Control == I2C_ACK_Enable)
	{
		I2C_AcknowledgeConfig(I2Cx , ENABLE);
	}
	else
	{
		I2C_AcknowledgeConfig(I2Cx , DISABLE);
	}
}


/* ================================================================
 * @Fn 				- MCAL_I2C_SlaveSendData
 * @brief 			- Slave send data to master using interrupt mechanism
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- data : slave data to be sent to master
 * @retval 			- None
 * Note 			- Support interrupt mechanism only
 */
void MCAL_I2C_SlaveSendData(I2C_TypeDef *I2Cx , uint8_t data)
{
	I2Cx->DR = data;
}

/* ================================================================
 * @Fn 				- MCAL_I2C_SlaveReceiveData
 * @brief 			- Slave Receive data from master using interrupt mechanism
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @retval 			- Received data
 * Note 			- Support interrupt mechanism only
 *
 */
uint8_t MCAL_I2C_SlaveReceiveData(I2C_TypeDef *I2Cx)
{
	return ((uint8_t)I2Cx->DR);
}
