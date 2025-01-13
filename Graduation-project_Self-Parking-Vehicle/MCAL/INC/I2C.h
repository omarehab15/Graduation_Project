/*
 * I2C.h
 *
 *  Created on: Feb 13, 2024
 *      Author: KARIM
 */

#ifndef I2C_H_
#define I2C_H_

/******************************
 * Includes
 *******************************/
#include "STM32F103x8.h"
#include "GPIO.h"
#include "RCC.h"

//==========================================================================

/***********************************
 * User Type Definitions
 ***********************************/
struct S_I2C_Slave_Device_Address
{
	uint16_t 		Enable_Dual_ADD;			// 1:Enable	 0:Disable
	uint16_t		primary_slave_address;
	uint16_t		secondary_slave_address;
	uint32_t		I2C_Addressing_Slave_Mode; 	// @ref I2C_Addressing_Slave_Mode

};

typedef enum
{
	I2C_EV_STOP ,
	I2C_ERROR_AF ,
	I2C_EV_ADDR_Matched ,
	I2C_EV_DATA_REQ , 			//The APP Layer should send the data (I2C_Send_Data) in this state
	I2C_EV_DATA_RCV   			//The APP Layer should Read the data (I2C_Receive_Data) in this state
}Slave_State;


/*To configure I2c, determine the following consideration:
 * 1- I2C mode (I2C/SMBus)
 * 2- Slave address & address length
 * 3- Slave interrupt (Enable/Disable)
 * 4- I2C clock speed (Standard/Fast mode)
 * 5- Acknowledgment return (Enable/Disable)
 * 6- Clock stretch mode (Enable/Disable)
 */
typedef struct
{
	uint32_t I2C_ClockSpeed ; 	// Specifies Clock Frequency, This parameter set based on @ref I2C_SCLK
	uint32_t StrechMode;      	// Enable Or Disable Clock Stretch Mode, This parameter must be set based on @ref I2C_StretchMode
	uint32_t I2C_Mode ;       	// Specifies The I2C Mode, This parameter must be set based on @ref I2C_Mode
	uint32_t I2C_ACK_Control ; 	// Enable or Disable The Acknowledgment, This parameter must be set based on @ref I2C_ACK_
	uint32_t General_Call_Adress_Detection ; //Enable or Disable The General call, This parameter must be set based on @ref I2C_ENGC_
	struct S_I2C_Slave_Device_Address I2C_Slave_Address ;
	void (* P_Slave_Event_CallBack)(Slave_State state); // Set C Function() which will be called once the IRQ Happen .
}I2C_Config_t;


/***********************************
 *  Configuration References
 ***********************************/

/*I2C_SCLK ref*/
//– Standard Speed (up to 100 kHz)
//– Fast Speed (up to 400 kHz)
//• to Confgure Clock before enable the peripheral
//--I2C_CR2.FREQ[5:0]: Peripheral clock frequency
//• Configure the clock control registers
//			Thigh  = Tlow = CCR * TPCLK1
//			SM or FM
//• Configure the rise time register I2C_TRISE
#define I2C_SCLK_SM_50K							(50000UL)
#define I2C_SCLK_SM_100K						(100000UL)
//Fast Mode Not Supported yet
#define I2C_SCLK_FM_200K						(200000UL)
#define I2C_SCLK_FM_400K						(400000UL)


/*I2C_StretchMode ref*/
//I2C_CR1
//Bit 7 NOSTRETCH: Clock stretching disable (Slave mode)
//0: Clock stretching enabled
//1: Clock stretching disabled
#define I2C_StretchMode_Enable					(uint32_t)(0)
#define I2C_StretchMode_Disable					I2C_CR1_NOSTRETCH


/*I2C_Mode ref*/
//I2C_CR1
//Bit 1 SMBUS: SMBus mode
//0: I2C mode
//1: SMBus mode
#define I2C_Mode_I2C							(uint32_t)(0)
#define I2C_Mode_SMBus							I2C_CR1_SMBUS


/*I2C_ACK_ ref*/
//I2C_CR1.ACK
//Bit 10 ACK: Acknowledge enable
//0: No acknowledge returned
//1: Acknowledge returned after a byte is received (matched address or data)
#define I2C_ACK_Enable							I2C_CR1_ACK
#define I2C_ACK_Disable							(uint16_t)(0)


/*I2C_ENGC_ ref*/
//I2C_CR1.ENGC
//Bit 6 ENGC: General call enable
//0: General call disabled. Address 00h is NACKed.
//1: General call enabled. Address 00h is ACKed
#define I2C_ENGC_Enable							I2C_CR1_ENGC
#define I2C_ENGC_Disable						(uint16_t)(0)


/*I2C_Addressing_Slave_Mode ref*/
//I2C_OAR1.ADDMODE
//Bit 15 ADDMODE Addressing mode (slave mode)
//0: 7-bit slave address (10-bit address not acknowledged)
//1: 10-bit slave address (7-bit address not acknowledged)
#define I2C_Addressing_Slave_Mode_7B			(uint16_t)(0)
#define I2C_Addressing_Slave_Mode_10B			(uint16_t)(1<<15)

typedef enum {
	WithStop,			//End the process
	WithoutStop			//When master want receive data from slave, it send repeated start
}Stop_Condition;

typedef enum {
	Start,
	RepeatedStart		//When master want receive data from slave, it send repeated start
}Repeated_Start;

typedef enum {
	DISABLE = 0,
	ENABLE = 1
}Fuctional_State;

typedef enum {
	Reset = 0,
	Set = 1
}FlagSTATUS;

typedef enum
{
	I2C_BUS_BUSY=0,
	EV5	,				//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	EV6 ,				//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	EV7 ,   			//EV5: RxNE = 1 Cleared by Reading DR Register
	EV8 , 				//EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
	EV8_1,				//EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
	EV8_2,  			//EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
	MASTER_BYTE_TRANSMITTING = ((uint32_t)0x00070080) /* TRA,BUSY ,MSL , TXE Flags */
}Status;

typedef enum
{
	I2C_Direction_Transmitter=0, // Write
	I2C_Direction_Receiver		 // Read
}I2C_Direction;

//=====================================================================

/*
* ===============================================
* APIs Supported by "MCAL I2C DRIVER"
* ===============================================
*/

//Initialization of I2Cx according to a specific configuration
void MCAL_I2C_Init(I2C_TypeDef *I2Cx , I2C_Config_t *I2C_Config);
//DeInitialization of I2Cx according to a specific configuration
void MCAL_I2C_DeInit(I2C_TypeDef *I2Cx);
//Set pins with its considerations to work
void MCAL_I2C_Set_Pins(I2C_TypeDef *I2Cx);
//Master
void MCAL_I2C_Master_TX(I2C_TypeDef *I2Cx, uint16_t DevAddr ,uint8_t* dataOut , uint32_t datalen , Stop_Condition Stop , Repeated_Start Start);
void MCAL_I2C_Master_RX(I2C_TypeDef *I2Cx, uint16_t DevAddr ,uint8_t* dataOut , uint32_t datalen , Stop_Condition Stop , Repeated_Start Start);
//Slave
void MCAL_I2C_SlaveSendData(I2C_TypeDef *I2Cx , uint8_t data);
uint8_t MCAL_I2C_SlaveReceiveData(I2C_TypeDef *I2Cx);

/*Generic Functions*/
void I2C_GenerateSTART(I2C_TypeDef *I2Cx, Fuctional_State NewState, Repeated_Start Start);
void I2C_GenerateSTOP(I2C_TypeDef *I2Cx, Fuctional_State NewState);
void I2C_SendAddress(I2C_TypeDef *I2Cx, uint16_t Address, I2C_Direction Direction);
FlagSTATUS I2C_GetFlagSTATUS(I2C_TypeDef *I2Cx, Status Flag);
void I2C_AcknowledgeConfig(I2C_TypeDef *I2Cx, Fuctional_State NewState);
void Slave_States(I2C_TypeDef *I2Cx,Slave_State State);

//=============================================================================================

/*******************  Bit definition for I2C_CR1 register  ********************/
#define I2C_CR1_PE_Pos                      (0U)
#define I2C_CR1_PE_Msk                      (0x1UL << I2C_CR1_PE_Pos)           /*!< 0x00000001 */
#define I2C_CR1_PE                          I2C_CR1_PE_Msk                     /*!< Peripheral Enable */
#define I2C_CR1_SMBUS_Pos                   (1U)
#define I2C_CR1_SMBUS_Msk                   (0x1UL << I2C_CR1_SMBUS_Pos)        /*!< 0x00000002 */
#define I2C_CR1_SMBUS                       I2C_CR1_SMBUS_Msk                  /*!< SMBus Mode */
#define I2C_CR1_SMBTYPE_Pos                 (3U)
#define I2C_CR1_SMBTYPE_Msk                 (0x1UL << I2C_CR1_SMBTYPE_Pos)      /*!< 0x00000008 */
#define I2C_CR1_SMBTYPE                     I2C_CR1_SMBTYPE_Msk                /*!< SMBus Type */
#define I2C_CR1_ENARP_Pos                   (4U)
#define I2C_CR1_ENARP_Msk                   (0x1UL << I2C_CR1_ENARP_Pos)        /*!< 0x00000010 */
#define I2C_CR1_ENARP                       I2C_CR1_ENARP_Msk                  /*!< ARP Enable */
#define I2C_CR1_ENPEC_Pos                   (5U)
#define I2C_CR1_ENPEC_Msk                   (0x1UL << I2C_CR1_ENPEC_Pos)        /*!< 0x00000020 */
#define I2C_CR1_ENPEC                       I2C_CR1_ENPEC_Msk                  /*!< PEC Enable */
#define I2C_CR1_ENGC_Pos                    (6U)
#define I2C_CR1_ENGC_Msk                    (0x1UL << I2C_CR1_ENGC_Pos)         /*!< 0x00000040 */
#define I2C_CR1_ENGC                        I2C_CR1_ENGC_Msk                   /*!< General Call Enable */
#define I2C_CR1_NOSTRETCH_Pos               (7U)
#define I2C_CR1_NOSTRETCH_Msk               (0x1UL << I2C_CR1_NOSTRETCH_Pos)    /*!< 0x00000080 */
#define I2C_CR1_NOSTRETCH                   I2C_CR1_NOSTRETCH_Msk              /*!< Clock Stretching Disable (Slave mode) */
#define I2C_CR1_START_Pos                   (8U)
#define I2C_CR1_START_Msk                   (0x1UL << I2C_CR1_START_Pos)        /*!< 0x00000100 */
#define I2C_CR1_START                       I2C_CR1_START_Msk                  /*!< Start Generation */
#define I2C_CR1_STOP_Pos                    (9U)
#define I2C_CR1_STOP_Msk                    (0x1UL << I2C_CR1_STOP_Pos)         /*!< 0x00000200 */
#define I2C_CR1_STOP                        I2C_CR1_STOP_Msk                   /*!< Stop Generation */
#define I2C_CR1_ACK_Pos                     (10U)
#define I2C_CR1_ACK_Msk                     (0x1UL << I2C_CR1_ACK_Pos)          /*!< 0x00000400 */
#define I2C_CR1_ACK                         I2C_CR1_ACK_Msk                    /*!< Acknowledge Enable */
#define I2C_CR1_POS_Pos                     (11U)
#define I2C_CR1_POS_Msk                     (0x1UL << I2C_CR1_POS_Pos)          /*!< 0x00000800 */
#define I2C_CR1_POS                         I2C_CR1_POS_Msk                    /*!< Acknowledge/PEC Position (for data reception) */
#define I2C_CR1_PEC_Pos                     (12U)
#define I2C_CR1_PEC_Msk                     (0x1UL << I2C_CR1_PEC_Pos)          /*!< 0x00001000 */
#define I2C_CR1_PEC                         I2C_CR1_PEC_Msk                    /*!< Packet Error Checking */
#define I2C_CR1_ALERT_Pos                   (13U)
#define I2C_CR1_ALERT_Msk                   (0x1UL << I2C_CR1_ALERT_Pos)        /*!< 0x00002000 */
#define I2C_CR1_ALERT                       I2C_CR1_ALERT_Msk                  /*!< SMBus Alert */
#define I2C_CR1_SWRST_Pos                   (15U)
#define I2C_CR1_SWRST_Msk                   (0x1UL << I2C_CR1_SWRST_Pos)        /*!< 0x00008000 */
#define I2C_CR1_SWRST                       I2C_CR1_SWRST_Msk                  /*!< Software Reset */
/*******************  Bit definition for I2C_CR2 register  ********************/
#define I2C_CR2_FREQ_Pos                    (0U)
#define I2C_CR2_FREQ_Msk                    (0x3FUL << I2C_CR2_FREQ_Pos)        /*!< 0x0000003F */
#define I2C_CR2_FREQ                        I2C_CR2_FREQ_Msk                   /*!< FREQ[5:0] bits (Peripheral Clock Frequency) */
#define I2C_CR2_ITERREN_Pos                 (8U)
#define I2C_CR2_ITERREN_Msk                 (0x1UL << I2C_CR2_ITERREN_Pos)      /*!< 0x00000100 */
#define I2C_CR2_ITERREN                     I2C_CR2_ITERREN_Msk                /*!< Error Interrupt Enable */
#define I2C_CR2_ITEVTEN_Pos                 (9U)
#define I2C_CR2_ITEVTEN_Msk                 (0x1UL << I2C_CR2_ITEVTEN_Pos)      /*!< 0x00000200 */
#define I2C_CR2_ITEVTEN                     I2C_CR2_ITEVTEN_Msk                /*!< Event Interrupt Enable */
#define I2C_CR2_ITBUFEN_Pos                 (10U)
#define I2C_CR2_ITBUFEN_Msk                 (0x1UL << I2C_CR2_ITBUFEN_Pos)      /*!< 0x00000400 */
#define I2C_CR2_ITBUFEN                     I2C_CR2_ITBUFEN_Msk                /*!< Buffer Interrupt Enable */
#define I2C_CR2_DMAEN_Pos                   (11U)
#define I2C_CR2_DMAEN_Msk                   (0x1UL << I2C_CR2_DMAEN_Pos)        /*!< 0x00000800 */
#define I2C_CR2_DMAEN                       I2C_CR2_DMAEN_Msk                  /*!< DMA Requests Enable */
#define I2C_CR2_LAST_Pos                    (12U)
#define I2C_CR2_LAST_Msk                    (0x1UL << I2C_CR2_LAST_Pos)         /*!< 0x00001000 */
#define I2C_CR2_LAST                        I2C_CR2_LAST_Msk                   /*!< DMA Last Transfer */
/*******************  Bit definition for I2C_OAR2 register  *******************/
#define I2C_OAR2_ENDUAL_Pos                 (0U)
#define I2C_OAR2_ENDUAL_Msk                 (0x1UL << I2C_OAR2_ENDUAL_Pos)      /*!< 0x00000001 */
#define I2C_OAR2_ENDUAL                     I2C_OAR2_ENDUAL_Msk                /*!< Dual addressing mode enable */
#define I2C_OAR2_ADD2_Pos                   (1U)
/*******************  Bit definition for I2C_SR1 register  ********************/
#define I2C_SR1_SB_Pos                      (0U)
#define I2C_SR1_SB_Msk                      (0x1UL << I2C_SR1_SB_Pos)           /*!< 0x00000001 */
#define I2C_SR1_SB                          I2C_SR1_SB_Msk                     /*!< Start Bit (Master mode) */
#define I2C_SR1_ADDR_Pos                    (1U)
#define I2C_SR1_ADDR_Msk                    (0x1UL << I2C_SR1_ADDR_Pos)         /*!< 0x00000002 */
#define I2C_SR1_ADDR                        I2C_SR1_ADDR_Msk                   /*!< Address sent (master mode)/matched (slave mode) */
#define I2C_SR1_BTF_Pos                     (2U)
#define I2C_SR1_BTF_Msk                     (0x1UL << I2C_SR1_BTF_Pos)          /*!< 0x00000004 */
#define I2C_SR1_BTF                         I2C_SR1_BTF_Msk                    /*!< Byte Transfer Finished */
#define I2C_SR1_ADD10_Pos                   (3U)
#define I2C_SR1_ADD10_Msk                   (0x1UL << I2C_SR1_ADD10_Pos)        /*!< 0x00000008 */
#define I2C_SR1_ADD10                       I2C_SR1_ADD10_Msk                  /*!< 10-bit header sent (Master mode) */
#define I2C_SR1_STOPF_Pos                   (4U)
#define I2C_SR1_STOPF_Msk                   (0x1UL << I2C_SR1_STOPF_Pos)        /*!< 0x00000010 */
#define I2C_SR1_STOPF                       I2C_SR1_STOPF_Msk                  /*!< Stop detection (Slave mode) */
#define I2C_SR1_RXNE_Pos                    (6U)
#define I2C_SR1_RXNE_Msk                    (0x1UL << I2C_SR1_RXNE_Pos)         /*!< 0x00000040 */
#define I2C_SR1_RXNE                        I2C_SR1_RXNE_Msk                   /*!< Data Register not Empty (receivers) */
#define I2C_SR1_TXE_Pos                     (7U)
#define I2C_SR1_TXE_Msk                     (0x1UL << I2C_SR1_TXE_Pos)          /*!< 0x00000080 */
#define I2C_SR1_TXE                         I2C_SR1_TXE_Msk                    /*!< Data Register Empty (transmitters) */
#define I2C_SR1_BERR_Pos                    (8U)
#define I2C_SR1_BERR_Msk                    (0x1UL << I2C_SR1_BERR_Pos)         /*!< 0x00000100 */
#define I2C_SR1_BERR                        I2C_SR1_BERR_Msk                   /*!< Bus Error */
#define I2C_SR1_ARLO_Pos                    (9U)
#define I2C_SR1_ARLO_Msk                    (0x1UL << I2C_SR1_ARLO_Pos)         /*!< 0x00000200 */
#define I2C_SR1_ARLO                        I2C_SR1_ARLO_Msk                   /*!< Arbitration Lost (master mode) */
#define I2C_SR1_AF_Pos                      (10U)
#define I2C_SR1_AF_Msk                      (0x1UL << I2C_SR1_AF_Pos)           /*!< 0x00000400 */
#define I2C_SR1_AF                          I2C_SR1_AF_Msk                     /*!< Acknowledge Failure */
#define I2C_SR1_OVR_Pos                     (11U)
#define I2C_SR1_OVR_Msk                     (0x1UL << I2C_SR1_OVR_Pos)          /*!< 0x00000800 */
#define I2C_SR1_OVR                         I2C_SR1_OVR_Msk                    /*!< Overrun/Underrun */
#define I2C_SR1_PECERR_Pos                  (12U)
#define I2C_SR1_PECERR_Msk                  (0x1UL << I2C_SR1_PECERR_Pos)       /*!< 0x00001000 */
#define I2C_SR1_PECERR                      I2C_SR1_PECERR_Msk                 /*!< PEC Error in reception */
#define I2C_SR1_TIMEOUT_Pos                 (14U)
#define I2C_SR1_TIMEOUT_Msk                 (0x1UL << I2C_SR1_TIMEOUT_Pos)      /*!< 0x00004000 */
#define I2C_SR1_TIMEOUT                     I2C_SR1_TIMEOUT_Msk                /*!< Timeout or Tlow Error */
#define I2C_SR1_SMBALERT_Pos                (15U)
#define I2C_SR1_SMBALERT_Msk                (0x1UL << I2C_SR1_SMBALERT_Pos)     /*!< 0x00008000 */
#define I2C_SR1_SMBALERT                    I2C_SR1_SMBALERT_Msk               /*!< SMBus Alert */

/*******************  Bit definition for I2C_SR2 register  ********************/
#define I2C_SR2_MSL_Pos                     (0U)
#define I2C_SR2_MSL_Msk                     (0x1UL << I2C_SR2_MSL_Pos)          /*!< 0x00000001 */
#define I2C_SR2_MSL                         I2C_SR2_MSL_Msk                    /*!< Master/Slave */
#define I2C_SR2_BUSY_Pos                    (1U)
#define I2C_SR2_BUSY_Msk                    (0x1UL << I2C_SR2_BUSY_Pos)         /*!< 0x00000002 */
#define I2C_SR2_BUSY                        I2C_SR2_BUSY_Msk                   /*!< Bus Busy */
#define I2C_SR2_TRA_Pos                     (2U)
#define I2C_SR2_TRA_Msk                     (0x1UL << I2C_SR2_TRA_Pos)          /*!< 0x00000004 */
#define I2C_SR2_TRA                         I2C_SR2_TRA_Msk                    /*!< Transmitter/Receiver */
#define I2C_SR2_GENCALL_Pos                 (4U)
#define I2C_SR2_GENCALL_Msk                 (0x1UL << I2C_SR2_GENCALL_Pos)      /*!< 0x00000010 */
#define I2C_SR2_GENCALL                     I2C_SR2_GENCALL_Msk                /*!< General Call Address (Slave mode) */
#define I2C_SR2_SMBDEFAULT_Pos              (5U)
#define I2C_SR2_SMBDEFAULT_Msk              (0x1UL << I2C_SR2_SMBDEFAULT_Pos)   /*!< 0x00000020 */
#define I2C_SR2_SMBDEFAULT                  I2C_SR2_SMBDEFAULT_Msk             /*!< SMBus Device Default Address (Slave mode) */
#define I2C_SR2_SMBHOST_Pos                 (6U)
#define I2C_SR2_SMBHOST_Msk                 (0x1UL << I2C_SR2_SMBHOST_Pos)      /*!< 0x00000040 */
#define I2C_SR2_SMBHOST                     I2C_SR2_SMBHOST_Msk                /*!< SMBus Host Header (Slave mode) */
#define I2C_SR2_DUALF_Pos                   (7U)
#define I2C_SR2_DUALF_Msk                   (0x1UL << I2C_SR2_DUALF_Pos)        /*!< 0x00000080 */
#define I2C_SR2_DUALF                       I2C_SR2_DUALF_Msk                  /*!< Dual Flag (Slave mode) */
#define I2C_SR2_PEC_Pos                     (8U)
#define I2C_SR2_PEC_Msk                     (0xFFUL << I2C_SR2_PEC_Pos)         /*!< 0x0000FF00 */
#define I2C_SR2_PEC                         I2C_SR2_PEC_Msk                    /*!< Packet Error Checking Register */



#endif /* I2C_H_ */
