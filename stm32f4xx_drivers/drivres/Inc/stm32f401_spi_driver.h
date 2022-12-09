/*
 * stm32f401_spi_driver.h
 *
 *  Created on: 31 Jul 2021
 *      Author: cuong
 */

#ifndef INC_STM32F401_SPI_DRIVER_H_
#define INC_STM32F401_SPI_DRIVER_H_

#include "stm32f401xx.h"
/*
 * This is a Configuration structure for a SPI pin
 */
typedef struct
{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_ScfkSpeed;
	uint8_t SPI_DDF;
	uint8_t SPI_CPLO;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;

}SPI_PinConfig_t;

/*
 * This is a Handler structure for SPI pin
 */
typedef struct
{
	//poiter to hold the base address of the GPIO peripheral
	SPI_RegDef_t *pSPIx; // This hold base address pf the SPI(1,2,3,4) to which the pin belongs
	SPI_PinConfig_t SPI_PinConfig;  // This hold SPI pin configuration settings
}SPI_Hangle_t;
/*
 * @SPI_DeviceMode
*/
#define SPI_DEVICE_MODE_SLAVE		0
#define SPI_DEVICE_MODE_MASTER		1
/*
 * @SPI_BusConfig
*/
#define SPI_BUS_CONFIG_FD					1
#define SPI_BUS_CONFIG_HD					2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY		3

/*
 * @ SPI_ScfkSpeed
*/
#define SPI_CLK_SPEED_DEV2						0
#define SPI_CLK_SPEED_DEV4						1
#define SPI_CLK_SPEED_DEV8						2
#define SPI_CLK_SPEED_DEV16						3
#define SPI_CLK_SPEED_DEV32						4
#define SPI_CLK_SPEED_DEV64						5
#define SPI_CLK_SPEED_DEV128					6
#define SPI_CLK_SPEED_DEV256					7
/*
 * @ SPI_DDF
*/
#define SPI_DFF_8BITS						0
#define SPI_DFF_16BITS						1
/*
 * @ SPI_CPLO
*/
#define SPI_CPLO_LOW						0
#define SPI_CPLO_HIGH						1
/*
 * @ SPI_CPHA
*/
#define SPI_CPHA_LOW						0
#define SPI_CPHA_HIGH						1
/*
 * @ SPI_SSM
*/
#define SPI_SSM_SW_DI						0
#define SPI_SSM_SW_EN						1
/*
 * Macros SPI buffer
*/
#define SPI_TXE_FLAG						(1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG						(1 << SPI_SR_RXNE)
#define SPI_BSY_FLAG						(1 << SPI_SR_BSY)
/******************************************************************************
 *                     APIS supported by this driver                          *
 *          For more information about the APIs check the function definition *
 ******************************************************************************/
/*
 * Peripheral Clock Setup
*/
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
/*
 * Init and De Init
*/
void SPI_Init(SPI_Hangle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);
/*
 * Data send and receiver
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTXbuffer, uint32_t leng);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRXbuffer, uint32_t leng);
/*
 * IRQ Configuration and ISR handling
*/
void SPI_IRQInterruptConfig(uint32_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Hangle_t *pSPIHandle);
/*
 * Config ENABLE or DISABLE peripheral for SPI
*/
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx,uint8_t EnorDi);
/*
 * Config ENABLE or DISABLE peripheral for SPI_SSI (Internal Slave Select)
*/
void SPI_SSIConfig(SPI_RegDef_t *pSPIx,uint8_t EnorDi);
#endif /* INC_STM32F401_SPI_DRIVER_H_ */
