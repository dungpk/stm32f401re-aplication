/*
 * spi_test.c
 *
 *  Created on: 2 Aug 2021
 *      Author: cuong
 */
#include "stm32f401xx.h"
#include <string.h>
/*
 * PB12			SP2_NSS
 * PB13			SP2_SCK
 * PB14			SP2_MISO
 * PB15 		SP2_MOSI
 */
void SPI2_GPIOInits(void){
	GPIO_Hangle_t SPIpins;
	SPIpins.pGPIOx = GPIOB;
	SPIpins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIpins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIpins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIpins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIpins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_MODE_SPEED_FAST;
	SPIpins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12 | GPIO_PIN_NO_13 | GPIO_PIN_NO_14|GPIO_PIN_NO_15;
	GPIO_Init(&SPIpins);
}
void SPI2_Init(void){
	SPI_Hangle_t pSPI2;
	pSPI2.pSPIx = SPI2;
	pSPI2.SPI_PinConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	pSPI2.SPI_PinConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	pSPI2.SPI_PinConfig.SPI_ScfkSpeed = SPI_CLK_SPEED_DEV2;
	pSPI2.SPI_PinConfig.SPI_DDF = SPI_DFF_8BITS;
	pSPI2.SPI_PinConfig.SPI_CPLO = SPI_CPLO_LOW;
	pSPI2.SPI_PinConfig.SPI_CPHA = SPI_CPHA_LOW;
	pSPI2.SPI_PinConfig.SPI_SSM = SPI_SSM_SW_EN;

	SPI_Init(&pSPI2);
}
int main(void)
{
	char user_data[] = "hello world";
	// this function is used to initialize the GPIO pins to behave as SPI2 pins
	SPI2_GPIOInits();

	SPI2_Init();
	// enable the SPI2 peripheral
	SPI_PeriClockControl(SPI2, ENABLE);
	// SSI internal Slave select
	SPI_SSIConfig(SPI2, ENABLE);
	// to send data
	SPI_SendData(SPI2,  (uint8_t*)user_data , strlen(user_data));
	while(1);
	return 0;

}
