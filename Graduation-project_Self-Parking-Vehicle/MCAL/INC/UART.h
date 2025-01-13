/*
 * UART.h
 *
 *  Created on: Feb 13, 2024
 *      Author: KARIM
 */

#ifndef UART_H_
#define UART_H_

/******************************
 * Includes
 *******************************/
#include "STM32F103x8.h"
#include "GPIO.h"
#include "RCC.h"

//==========================================================================

/*
 * To configure a pin, determine the following consideration:
 * 1- USART Mode (Transmit/Receive)
 * 2- USART Buadrate
 * 3- Data length (8/9 bits)
 * 4- Parity (even/odd)
 * 5- No. of stop bits (1/2 bits)
 * 6- HW Flow control (CTS/RTS)
 * 7- USART mechanism (Polling/EXTI/DMA)
 */
/***********************************
 * User Type Definitions
 ***********************************/
typedef struct{
	uint8_t Mode; 			//Select the TX/RX mode, This parameter is value of @ref Mode_Def
	uint32_t Buadrate;		//Select communication buadrate, This parameter is value of @ref Buadrate_Def
	uint8_t Data_Len;		//Specific the data length that will transmit/receive, This parameter is value of @ref Data_Len_Def
	uint8_t Parity;			//Specific the parity mode, This parameter is value of @ref Parity_Def
	uint8_t StopBit;		//Specific the number of stop bits, This parameter is value of @ref Stop_Bit_Def
	uint8_t Flow_Ctl;		//Specific the HW flow control is enable/disable, This parameter is value of @ref Flow_Ctl_Def
	uint8_t IRQ_EN;			//Specific the UART IRQ is enable/disable, This parameter is value of @ref IRQ_EN_Def

	void (* P_IRQ_CALLBACK)(void);		//Called when IRQ is happen
}USART_Config;


/***********************************
 *  Configuration References
 ***********************************/

// Mode_Def ref
// Control register 1 (USART_CR1): Bit3 TE: Transmitter enable - Bit2 RE: Receiver enable
#define MODE_TX				(uint32_t)(1<<3)
#define MODE_RX				(uint32_t)(1<<2)
#define MODE_TX_RX			(uint32_t)(1<<2 | 1<<3)

// Buadrate_Def ref
#define BaudRate_2400					2400
#define BaudRate_9600					9600
#define BaudRate_19200					19200
#define BaudRate_57600					57600
#define BaudRate_115200					115200
#define BaudRate_230400					230400
#define BaudRate_460800					460800
#define BaudRate_921600					921600
#define BaudRate_2250000				2250000
#define BaudRate_4500000				4500000

//BaudRate Calculation
//USARTDIV = fclk / (16 * Baudrate)
//USARTDIV_MUL100 =
//uint32((100 *fclk ) / (16 * Baudrate) == (25 *fclk ) / (4* Baudrate) )
//DIV_Mantissa_MUL100 = Integer Part (USARTDIV  )  * 100
//DIV_Mantissa = Integer Part (USARTDIV  )
//DIV_Fraction = (( USARTDIV_MUL100  - DIV_Mantissa_MUL100  ) * 16 ) / 100
#define USARTDIV(_PCLK_, _BAUD_)							(uint32_t) (_PCLK_/(16 * _BAUD_ ))
#define USARTDIV_MUL100(_PCLK_, _BAUD_)						(uint32_t) ( (25 * _PCLK_ ) / (4  * _BAUD_ ))
#define Mantissa_MUL100(_PCLK_, _BAUD_)						(uint32_t) (USARTDIV(_PCLK_, _BAUD_) * 100)
#define Mantissa(_PCLK_, _BAUD_)							(uint32_t) (USARTDIV(_PCLK_, _BAUD_) )
#define DIV_Fraction(_PCLK_, _BAUD_)						(uint32_t) (((USARTDIV_MUL100(_PCLK_, _BAUD_) -  Mantissa_MUL100(_PCLK_, _BAUD_) ) * 16 ) / 100 )
#define UART_BRR_Register(_PCLK_, _BAUD_)					(( Mantissa (_PCLK_, _BAUD_) ) <<4 )|( (DIV_Fraction(_PCLK_, _BAUD_)) & 0xF )


// Data_Len_Def ref
// Control register 1 (USART_CR1): Bit12 M: Word length
#define Data_Len_8				(uint32_t)(0)
#define Data_Len_9				(uint32_t)(1<<12)

// Parity_Def ref
// Control register 1 (USART_CR1): Bit10 PCE: Parity control enable - Bit9 PS: Parity selection
#define Parity_DISABLE			(uint32_t)(0)
#define Parity_EVEN_EN			(uint32_t)(1<<10)
#define Parity_ODD_EN			(uint32_t)(1<<10 | 1<<9)

// Stop_Bit_Def ref
// Control register 2 (USART_CR2): Bits13:12 STOP: STOP bits
#define StopBits_1				(uint32_t)(0)
#define StopBits_2				(uint32_t)(2<<12)

// Flow_Ctl_Def
// Control register 3 (USART_CR3): Bit10 CTSIE: CTS interrupt enable - Bit9 CTSE: CTS enable
// Control register 3 (USART_CR3): Bit8 RTSE: RTS enable
#define FLOW_CTL_DISABLE			(uint32_t)(0)
#define FLOW_CTL_ENABLE				(uint32_t)(1<<8 | 1<<9)
#define FLOW_CTL_CTS_EN				(uint32_t)(1<<9)
#define FLOW_CTL_RTS_EN				(uint32_t)(1<<8)

// IRQ_EN_Def ref
#define IRQ_DISABLE					(uint32_t)(0)
#define IRQ_TXE_EN					(uint32_t)(1<<7)  //TXE interrupt enable
#define IRQ_TC_EN					(uint32_t)(1<<6)  //Transmission complete interrupt enable
#define IRQ_RXNE_EN					(uint32_t)(1<<5)  //Received data ready to read & over run error interrupt enable
#define IRQ_PE_EN					(uint32_t)(1<<8)  //Parity error interrupt enable

enum USART_IRQ_EVENT{
	USART_IRQ_TXE,			//Transmit data register empty
	USART_IRQ_TC,			//Transmission complete
	USART_IRQ_RXNE,			//Received data ready to read
	USART_IRQ_ORE,			//Overrun error
	USART_IRQ_PE			//Parity error
};

enum Polling_Mechanism{
	enable ,
	disable
};


//=====================================================================

/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/

//Initialization of USARTx according to a specific configuration
void MCAL_USART_INIT(USART_TypeDef* USARTx, USART_Config* USART_ConFig);
//DeInitialization of USARTx according to a specific configuration
void MCAL_USART_DEINIT(USART_TypeDef* USARTx);
//Send data
void MCAL_USART_SEND_DATA(USART_TypeDef* USARTx, uint16_t* Buffer, enum Polling_Mechanism PollingEN);
//Read data
void MCAL_USART_READ_DATA(USART_TypeDef* USARTx, uint16_t* Buffer, enum Polling_Mechanism PollingEN);
//Wait
void MCAL_UART_WAIT_TC(USART_TypeDef* USARTx);
//Set pins with its considerations to work
void MCAL_USART_SETPIN(USART_TypeDef* USARTx);




#endif /* UART_H_ */
