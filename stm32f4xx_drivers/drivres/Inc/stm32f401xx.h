/*
 * stm32401xx.h
 *
 *  Created on: Jul 3, 2021
 *      Author: cuong
 */

#ifndef INC_STM32F401XX_H_
#define INC_STM32F401XX_H_
#define __vo					volatile

#include <stdint.h>
/*************************** START: Processor Specific Details*******************
 * ARM Cortex Mx Processor NVIC ISERx register Addresses
*/
#define NVIC_ISER0				((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1				((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2				((__vo uint32_t*)0xE000E108)
#define NVIC_ISER3				((__vo uint32_t*)0xE000E10C)

/*
 * ARM Cortex Mx Processor NVIC ICERx register Addresses
*/
#define NVIC_ICER0				((__vo uint32_t*)0xE000E180)
#define NVIC_ICER1				((__vo uint32_t*)0xE000E184)
#define NVIC_ICER2				((__vo uint32_t*)0xE000E188)
#define NVIC_ICER3				((__vo uint32_t*)0xE000E18C)
/*
 * ARM Cortex Mx Processor NVIC Priority register Addresses
*/
#define NVIC_PR_BASE_ADDR		((__vo uint32_t*)0xE000E400)

#define NO_PR_BITS_IMPLEMENTED		4
/*
 * base addresses of FLASH and SRAM memories
 */
#define FLASH_BASEADDR			0x08000000U
#define	SRAM1_BASEADDR			0x20000000U
#define ROM_BASEADDR			0x1FFF0000U
#define SRAM_BASEADDR			SRAM1_BASEADDR
/*
 * AHBx and APBx Bus Peripheral base addresses
 */
#define PERIPH_BASEADDR 		0x40000000U
#define APB1PERIPH_BASEADDR		PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR		0x40010000U
#define AHB1PERIPH_BASEADDR		0x40020000U
#define AHB2PERIPH_BASEADDR		0x50000000U
/*
 * base addresses peripheral hanging out on APB1
 */
#define I2C1_BASEADDR			(APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR			(APB1PERIPH_BASEADDR + 0x5800)
#define I2C3_BASEADDR			(APB1PERIPH_BASEADDR + 0x5C00)
#define SPI2_BASEADDR			(APB1PERIPH_BASEADDR + 0x3800)
#define SPI3_BASEADDR			(APB1PERIPH_BASEADDR + 0x3C00)
#define USART2_BASEADDR			(APB1PERIPH_BASEADDR + 0x4400)
/*
 * base addresses peripheral hanging out on APB2
 */
#define USART1_BASEADDR			(APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR			(APB2PERIPH_BASEADDR + 0x1400)
#define SPI1_BASEADDR			(APB2PERIPH_BASEADDR + 0x3000)
#define SPI4_BASEADDR			(APB2PERIPH_BASEADDR + 0x3400)
#define EXTI_BASEADDR			(APB2PERIPH_BASEADDR + 0x3C00)
#define SYSCFG_BASEADDR			(APB2PERIPH_BASEADDR + 0x3800)
/*
 * base addresses peripheral hanging out on AHB1
 */
#define	GPIOA_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0000)
#define	GPIOB_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0400)
#define	GPIOC_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0800)
#define	GPIOD_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0C00)
#define	GPIOE_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1000)
#define	GPIOH_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1C00)
#define RCC_BASEADDR			(AHB1PERIPH_BASEADDR + 0x3800)
/*
 * Peripheral register definition structure for GPIO
 */
typedef struct
{
	__vo uint32_t MODER;		/*Address offset: 0x00*/
	__vo uint32_t OTYPER;		/*Address offset: 0x04*/
	__vo uint32_t OSPEEDR;		/*Address offset: 0x08*/
	__vo uint32_t PUPDR;		/*Address offset: 0x0C*/
	__vo uint32_t IDR;			/*Address offset: 0x10*/
	__vo uint32_t ODR;			/*Address offset: 0x14*/
	__vo uint32_t BSRR;			/*Address offset: 0x18*/
	__vo uint32_t LCKR;			/*Address offset: 0x1C*/
	__vo uint32_t AFR[2];		/*Address offset: 0x20-0x24*/

}GPIO_RegDef_t;
/*
 * Peripheral register definition structure for GPIO
 */
typedef struct
{
	__vo u32_t CR1;				/*Address offset: 0x00*/
	__vo u32_t CR2;				/*Address offset: 0x04*/
	__vo u32_t OAR1;				/*Address offset: 0x08*/
	__vo u32_t OAR2;			````/*Address offset: 0x10*/
	__vo u32_t DR;			/*Address offset: 0x0C*/
	__vo uint16_t TXCRCR;			/*Address offset: 0x14*/
	__vo uint32_t SPI_I2SCFGR;		/*Address offset: 0x18*/
	__vo uint32_t SPI_I2SPR;		/*Address offset: 0x1C*/
}SPI_RegDef_t;
/*
 * Peripheral register definition structure for EXTI
 */
typedef struct
{
	__vo uint32_t IMR;		/*Address offset: 0x00*/
	__vo uint32_t EMR;		/*Address offset: 0x04*/
	__vo uint32_t RTSR;		/*Address offset: 0x08*/
	__vo uint32_t FTSR;		/*Address offset: 0x0C*/
	__vo uint32_t SWIER;	/*Address offset: 0x10*/
	__vo uint32_t PR;		/*Address offset: 0x14*/

}EXTI_RegDef_t;
/*
 * Peripheral register definition structure for SYSCFG
 */
typedef struct
{
	__vo uint32_t MEMRMP;		/*Address offset: 0x00*/
	__vo uint32_t PMC;			/*Address offset: 0x04*/
	__vo uint32_t EXTICR[4];	/*EXTICR[0] <==> EXTICR1  offset 0x08 - 0x14*/
	//uint32_t REVERVED1[2];
	__vo uint32_t CMPCR;		/*Address offset: 0x20*/

}SYSCFG_RegDef_t;
/*
 * Peripheral register definition structure for RCC
 */
typedef struct
{
	__vo uint32_t CR;			/*Address offset: 0x00*/
	__vo uint32_t PLLCFGR;		/*Address offset: 0x04*/
	__vo uint32_t CFGR;			/*Address offset: 0x08*/
	__vo uint32_t CIR;			/*Address offset: 0x0C*/
	__vo uint32_t AHB1RSTR;		/*Address offset: 0x10*/
	__vo uint32_t AHB2RSTR;		/*Address offset: 0x14*/
	uint32_t RESERVED0[2];				/*Reserved: 0x18-0x1C*/
	__vo uint32_t APB1RSTR;		/*Address offset: 0x20*/
	__vo uint32_t APB2RSTR;		/*Address offset: 0x24*/
	uint32_t RESERVED1[2];				/*Reserved: 0x28-0x2C*/
	__vo uint32_t AHB1ENR;		/*Address offset: 0x30*/
	__vo uint32_t AHB2ENR;		/*Address offset: 0x34*/
	uint32_t RESERVED2[2];				/*Reserved: 0x38-0x3C*/
	__vo uint32_t APB1ENR;		/*Address offset: 0x40*/
	__vo uint32_t APB2ENR;		/*Address offset: 0x44*/
	uint32_t RESERVED3[2];				/*Reserved: 0x48-0x4C*/
	__vo uint32_t AHB1LPENR;	/*Address offset: 0x50*/
	__vo uint32_t AHB2LPENR;	/*Address offset: 0x54*/
	uint32_t RESERVED4[2];				/*Reserved: 0x58-0x5C*/
	__vo uint32_t APB1LPENR;	/*Address offset: 0x60*/
	__vo uint32_t APB2LPENR;	/*Address offset: 0x64*/
	uint32_t RESERVED5[2];				/*Reserved: 0x68-0x6C*/
	__vo uint32_t BDCR;			/*Address offset: 0x70*/
	__vo uint32_t CSR;			/*Address offset: 0x74*/
	uint32_t RESERVED6[2];				/*Reserved: 0x78-0x7C*/
	__vo uint32_t SSCGR;		/*Address offset: 0x80*/
	__vo uint32_t PLLI2SCFGR;	/*Address offset: 0x84*/
	uint32_t RESERVED7;				/*Reserved: 0x88*/
	__vo uint32_t DCKCFGR;		/*Address offset: 0x8C*/
}RCC_RegDef_t;

/*
 * peripheral definition (Peripheral bas addresses typecasted to GPIO_ref_def_t
 */
#define GPIOA					((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB					((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC					((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD					((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE					((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOH					((GPIO_RegDef_t*)GPIOH_BASEADDR)
/*
 * peripheral definition (Peripheral bas addresses typecasted to SPI_ref_def_t
 */
#define SPI1					((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2					((SPI_RegDef_t*)SPI2_BASEADDR)
#define SPI3					((SPI_RegDef_t*)SPI3_BASEADDR)
#define SPI4					((SPI_RegDef_t*)SPI4_BASEADDR)
/*
 * peripheral definition (Peripheral bas addresses typecasted to RCC_ref_def_t
 */
#define RCC						((RCC_RegDef_t*)RCC_BASEADDR)
/*
 * EXTI Macros
*/
#define EXTI					((EXTI_RegDef_t*)EXTI_BASEADDR)
/*
 * SYSCFG Macros
*/
#define SYSCFG					((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)
//////////////////////////////Enable Clock//////////////////////////////////
/*
 *	Clock Enable Macros for GPIOx peripheral
 */
#define GPIOA_PCLK_EN			RCC->AHB1ENR |=(1 << 0)
#define GPIOB_PCLK_EN			RCC->AHB1ENR |=(1 << 1)
#define GPIOC_PCLK_EN			RCC->AHB1ENR |=(1 << 2)
#define GPIOD_PCLK_EN			RCC->AHB1ENR |=(1 << 3)
#define GPIOE_PCLK_EN			RCC->AHB1ENR |=(1 << 4)
#define GPIOH_PCLK_EN			RCC->AHB1ENR |=(1 << 7)
/*
 * Clock Enanble Macros for SPIx peripheral
 */
#define SPI1_PCLK_EN			RCC->APB2ENR |=(1 << 12)
#define SPI2_PCLK_EN			RCC->APB1ENR |=(1 << 14)
#define SPI3_PCLK_EN			RCC->APB1ENR |=(1 << 15)
#define SPI4_PCLK_EN			RCC->APB2ENR |=(1 << 13)
/*
 * Clock Enanble Macros for I2Cx peripheral
 */
#define I2C1_PCLK_EN			RCC->APB1ENR |=(1 << 21)
#define I2C2_PCLK_EN			RCC->APB1ENR |=(1 << 22)
#define I2C3_PCLK_EN			RCC->APB1ENR |=(1 << 23)
/*
 * Clock Enanble Macros for USARTx peripheral
 */
#define USART2_PCLK_EN			RCC->APB1ENR |=(1 << 17)
#define USART1_PCLK_EN			RCC->APB2ENR |=(1 << 4)
#define USART6_PCLK_EN			RCC->APB2ENR |=(1 << 5)
/*
 * Clock Enanble Macros for SYSCFG peripheral
 */
#define SYSCFG_PCLK_EN			RCC->APB2ENR |=(1 << 14)
//////////////////////////////Disable Clock//////////////////////////
/*
 *	Clock Disable Macros for GPIOx peripheral
 */
#define GPIOA_PCLK_DI			RCC->AHB1ENR &= ~(1 << 0)
#define GPIOB_PCLK_DI			RCC->AHB1ENR &= ~(1 << 1)
#define GPIOC_PCLK_DI			RCC->AHB1ENR &= ~(1 << 2)
#define GPIOD_PCLK_DI			RCC->AHB1ENR &= ~(1 << 3)
#define GPIOE_PCLK_DI			RCC->AHB1ENR &= ~(1 << 4)
#define GPIOH_PCLK_DI			RCC->AHB1ENR &= ~(1 << 7)
/*
 * Clock Disable Macros for SPIx peripheral
 */
#define SPI1_PCLK_DI			RCC->APB2ENR &= ~(1 << 12)
#define SPI2_PCLK_DI			RCC->APB1ENR &= ~(1 << 14)
#define SPI3_PCLK_DI			RCC->APB1ENR &= ~(1 << 15)
#define SPI4_PCLK_DI			RCC->APB2ENR &= ~(1 << 13)
/*
 * Clock Disable Macros for I2Cx peripheral
 */
#define I2C1_PCLK_DI			RCC->APB1ENR &= ~(1 << 21)
#define I2C2_PCLK_DI			RCC->APB1ENR &= ~(1 << 22)
#define I2C3_PCLK_DI			RCC->APB1ENR &= ~(1 << 23)
/*
 * Clock Disable Macros for USARTx peripheral
 */
#define USART2_PCLK_DI			RCC->APB1ENR &= ~(1 << 17)
#define USART1_PCLK_DI			RCC->APB2ENR &= ~(1 << 4)
#define USART6_PCLK_DI			RCC->APB2ENR &= ~(1 << 5)
/*
 * Clock Disable Macros for SYSCFG peripheral
 */
#define SYSCFG_PCLK_DI			RCC->APB2ENR &= ~(1 << 14)
/*
 * Macros to reset GPIOx peripheral
*/
#define GPIOA_REG_RESET()		do{ RCC->AHB1RSTR |= (1 << 0); RCC->AHB1RSTR &= ~(1 << 0);}while(0)
#define GPIOB_REG_RESET()		do{ RCC->AHB1RSTR |= (1 << 1); RCC->AHB1RSTR &= ~(1 << 1);}while(0)
#define GPIOC_REG_RESET()		do{ RCC->AHB1RSTR |= (1 << 2); RCC->AHB1RSTR &= ~(1 << 2);}while(0)
#define GPIOD_REG_RESET()		do{ RCC->AHB1RSTR |= (1 << 3); RCC->AHB1RSTR &= ~(1 << 3);}while(0)
#define GPIOE_REG_RESET()		do{ RCC->AHB1RSTR |= (1 << 4); RCC->AHB1RSTR &= ~(1 << 4);}while(0)
#define GPIOH_REG_RESET()		do{ RCC->AHB1RSTR |= (1 << 7); RCC->AHB1RSTR &= ~(1 << 7);}while(0)
/*
 * returns port code for given GPIOx base address
*/
#define GPIO_BASEADDR_TO_CODE(x)   ((x == GPIOA) ? 0:\
									(x == GPIOB) ? 1:\
									(x == GPIOC) ? 2:\
									(x == GPIOD) ? 3:\
									(x == GPIOE) ? 4:7)
/*
 *IQR(Interrupt Request) Number of STM32F401z MCU
 *NOTE: update these acros with valid values according to your MCU
 *TODO: You may complete this list for other peripheral
*/
#define IRQ_NO_EXTI0			6
#define IRQ_NO_EXTI1			7
#define IRQ_NO_EXTI2			8
#define IRQ_NO_EXTI3			9
#define IRQ_NO_EXTI4			10
#define IRQ_NO_EXTI9_5			23
#define IRQ_NO_EXTI15_10		40
/*
 * Macros Priority Levels
*/
#define NVIC_IRQ_PRI0			0
#define NVIC_IRQ_PRI1			1
#define NVIC_IRQ_PRI2			2
#define NVIC_IRQ_PRI3			3
#define NVIC_IRQ_PRI4			4
#define NVIC_IRQ_PRI5			5
#define NVIC_IRQ_PRI6			6
#define NVIC_IRQ_PRO7			7
#define NVIC_IRQ_PRI8			8
#define NVIC_IRQ_PRI9			9
#define NVIC_IRQ_PRI10			10
#define NVIC_IRQ_PRI11			11
#define NVIC_IRQ_PRI12			12
#define NVIC_IRQ_PRI13			13
#define NVIC_IRQ_PRI14			14
#define NVIC_IRQ_PRI15			15
/*
 * Macros for SPI_CR1 register
*/
#define SPI_CR1_CPHA			0
#define SPI_CR1_CPLO			1
#define SPI_CR1_MSTR			2
#define SPI_CR1_BR				3
#define SPI_CR1_SPE				6
#define SPI_CR1_LSBFIRST		7
#define SPI_CR1_SSI				8
#define SPI_CR1_SSM				9
#define SPI_CR1_RXONLY			10
#define SPI_CR1_DFF				11
#define SPI_CR1_CRCNEXT			12
#define SPI_CR1_CRCEN			13
#define SPI_CR1_BIDIOE			14
#define SPI_CR1_BIDIMODE		15
/*
 * Macros for SPI_CR2 register
*/
#define SPI_CR2_RXDMAEN			0
#define SPI_CR2_TXDMAEN			1
#define SPI_CR2_SSOE			2
#define SPI_CR2_FRF				4
#define SPI_CR2_ERRIE			5
#define SPI_CR2_RXNEIE			6
#define SPI_CR2_TXEIE			7
/*
 * Macros for SPI_SR register
*/
#define SPI_SR_RXNE				0
#define SPI_SR_TXE				1
#define SPI_SR_CHSIDE			2
#define SPI_SR_UDR				3
#define SPI_SR_CRCRERR			4
#define SPI_SR_MODF				5
#define SPI_SR_OVR				6
#define SPI_SR_BSY				7
#define SPI_SR_FRE				8

/*
 * Some general macros
*/
#define ENABLE					1
#define DISABLE					0
#define SET						ENABLE
#define RESET					DISABLE
#define GPIO_PIN_SET			SET
#define GPIO_PIN_RESET			RESET
#define FLAG_RESET				RESET
#define FLAG_SET				SET

#include "stm32f401_gpio_driver.h"
#include "stm32f401_spi_driver.h"
#endif /* INC_STM32F401XX_H_ */
