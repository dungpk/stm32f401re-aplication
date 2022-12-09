/*
 * stm32f401_spi_driver.c
 *
 *  Created on: 31 Jul 2021
 *      Author: cuong
 */
#include "stm32f401_spi_driver.h"
/******************************************************************************
 *                     APIS supported by this driver                          *
 *          For more information about the APIs check the function definition *
 ******************************************************************************/
/******************************************************************************
 * @func					SPI_PeriClockControl
 * @brief					This func set enable or disable clock peripheral SPIx
 * @param					SPI_RegDef_t  *pSPIx // base address SPIx
 							unit8_t EnorDi // macros ENABLE or DISABLE
 * @return					none
 * @Note					none
*/
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_EN;
		}else if(pSPIx == SPI2)
		{
			SPI2_PCLK_EN;
		}else if(pSPIx == SPI3)
		{
			SPI3_PCLK_EN;
		}else
		{
			SPI4_PCLK_EN;
		}
	}
	else
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_DI;
		}else if(pSPIx == SPI2)
		{
			SPI2_PCLK_DI;
		}else if(pSPIx == SPI3)
		{
			SPI3_PCLK_DI;
		}else
		{
			SPI4_PCLK_DI;
		}
	}
}

/******************************************************************************
 * @func					SPI_Init
 * @brief					This func init SPIx
 * @param					SPI_Hangle_t *pSPIHandler
 * @return					none
 * @Note					none
*/
void SPI_Init(SPI_Hangle_t *pSPIHandle)
{
	uint16_t tempreg = 0;
	tempreg |= pSPIHandle->SPI_PinConfig.SPI_DeviceMode << SPI_CR1_MSTR;
	if(pSPIHandle->SPI_PinConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		// bidi mode should be cleared
		tempreg &= ~( 1 << SPI_CR1_BIDIMODE);
	}else if(pSPIHandle->SPI_PinConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD){
		// bidi mode should be set
		tempreg |= (1 << SPI_CR1_BIDIMODE);
	}else{ //SPI_BUS_CONFIG_SIMPLEX_RXONLY
		// Bidi mode should be set
		tempreg |= (1 << SPI_CR1_BIDIMODE);
		// RXONLY mod should be set
		tempreg |= (1 << SPI_CR1_RXONLY);
	}
	// configure the spi CPHA
	tempreg |= pSPIHandle->SPI_PinConfig.SPI_CPHA << SPI_CR1_CPHA;
	// configure the spi CPLO
	tempreg |= pSPIHandle->SPI_PinConfig.SPI_CPLO << SPI_CR1_CPLO;
	// configure the spi DFF
	tempreg |= pSPIHandle->SPI_PinConfig.SPI_DDF << SPI_CR1_DFF;
	// configure the spi SSM
	tempreg |= pSPIHandle->SPI_PinConfig.SPI_SSM << SPI_CR1_SSM;
	// configure the spi serial clock speed (baud rate)
	tempreg |= pSPIHandle->SPI_PinConfig.SPI_ScfkSpeed << SPI_CR1_BR;

	pSPIHandle->pSPIx->CR1 = tempreg;
}
/******************************************************************************
 * @func					SPI_DeInit
 * @brief					This func init SPIx
 * @param					SPI_Hangle_t *pSPIHandler
 * @return					none
 * @Note					none
*/
void SPI_DeInit(SPI_RegDef_t *pSPIx);
/******************************************************************************
 * @func					SPIGetFlagStatus
 * @brief					This func get Flag status
 * @param					SPI_RegDef_t *pSPIx
 * 							uint8_t Flag_Name
 * @return					none
 * @Note					none
*/
uint8_t SPIGetFlagStatus(SPI_RegDef_t *pSPIx, uint8_t Flag_Name)
{
	if(pSPIx->SR & Flag_Name)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}
/******************************************************************************
 * @func					SPI_SendData
 * @brief					This func send data
 * @param					SPI_RegDef_t *pSPIx
 * 							uint8_t *pTXbuffer
 * 							uint32_t leng
 * @return					none
 * @Note					none
*/
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTXbuffer, uint32_t leng)
{
	while(leng > 0)
	{
		// wait until  TXE is set
		while(SPIGetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);

		// check the DFF bit in CR1
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
		{
			// 16 bit DFF
			// oad the data in to the DR
			pSPIx->DR = *(uint16_t*)pTXbuffer;
			leng-=2;
			(uint16_t*)pTXbuffer++;
		}else{
			// 8 bit DFF
			pSPIx->DR = *pTXbuffer;
			leng-=1;
			pTXbuffer++;
		}
	}
}
/******************************************************************************
 * @func					SPI_PeripheralControl
 * @brief					This func enable or disable peripheral for SPI
 * @param					SPI_RegDef_t *pSPIx
 * 							uint8-t EnorDi
 * @return					none
 * @Note					none
*/
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx,uint8_t EnorDi)
{
	if(EnorDi ==  ENABLE){
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	}else{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}
}
/******************************************************************************
 * @func					SPI_SSIConfig
 * @brief					This func enable or disable for SPI _SSI
 * @param					SPI_RegDef_t *pSPIx
 * 							uint8-t EnorDi
 * @return					none
 * @Note					none
*/
void SPI_SSIConfig(SPI_RegDef_t *pSPIx,uint8_t EnorDi)
{
	if(EnorDi ==  ENABLE){
		pSPIx->CR1 |= (1 << SPI_CR1_SSI);
	}else{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
	}
}
/******************************************************************************
 * @func					SPI_ReceiveData
 * @brief					This func send data
 * @param					SPI_RegDef_t *pSPIx
 * 							uint8_t *pRXbuffer
 * 							uint32_t leng
 * @return					none
 * @Note					none
*/
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRXbuffer, uint32_t leng)
{
	while(leng > 0)
		{
			// wait until  RXNE is set
			while(SPIGetFlagStatus(pSPIx, SPI_RXNE_FLAG) == FLAG_RESET);

			// check the DFF bit in CR1
			if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
			{
				// 16 bit DFF
				// oad the data in to the DR
				*(uint16_t*)pRXbuffer = pSPIx->DR;
				leng-=2;
				(uint16_t*)pRXbuffer++;
			}else{
				// 8 bit DFF
				pRXbuffer = pSPIx->DR;
				leng-=1;
				pRXbuffer++;
			}
		}
}
/*
 * IRQ Configuration and ISR handling
*/
void SPI_IRQInterruptConfig(uint32_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Hangle_t *pSPIHandle);

