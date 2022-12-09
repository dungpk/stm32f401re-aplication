/*
 * stm32f401_gpio_driver.c
 *
 *  Created on: 6 Jul 2021
 *      Author: cuong
 */
#include "stm32f401_gpio_driver.h"

/******************************************************************************
 *                     APIS supported by this driver                          *
 *          For more information about the APIs check the function definition *
 ******************************************************************************/

/******************************************************************************
 * @func					GPIO_PeriClockControl
 * @brief					This func set enable or disable clock peripheral GPIOx
 * @param					GPIO_RegDef_t *pGPIOx // base address GPIOx
 							unit8_t EnorDi // macros ENABLE or DISABLE
 * @return					none
 * @Note					none
*/
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN;
		}else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN;
		}else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN;
		}else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN;
		}else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN;
		}else
		{
			GPIOH_PCLK_EN;
		}
	}
	else
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI;
		}else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI;
		}else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI;
		}else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI;
		}else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI;
		}else
		{
			GPIOH_PCLK_DI;
		}
	}
}
/******************************************************************************
 * @func					GPIO_Init  and GPIO DeInit
 * @brief					This func set Init or DiInitt peripheral GPIOx
 * @param					GPIO_RegDef_t *pGPIOx // base address GPIOx
 							GPIO_Handle_t *pGPIOHandle
 * @return					none
 * @Note					none
*/
void GPIO_Init(GPIO_Hangle_t *pGPIOHandle)
{
	uint32_t temp; // temp.resgister
	// enable the peripheral clock
	GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);
	// Configure the mode of gpio pin
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		// non interrupt
		temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << 2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clearing
		pGPIOHandle->pGPIOx->MODER |= temp;// setting
	}else
	{
		// interrupt mode
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			// config the FTSR
			EXTI->FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			// clearing RTSR
			EXTI->RTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_IT_RT)
		{
			// config the RTSR
			EXTI->RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			// clearing FTSR
			EXTI->FTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}else
		{
			// config the both FTSR and RTSR
			// config the FTSR
			EXTI->FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			// config the RTSR
			EXTI->RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		// configure the GPIO port selection in SYSCFG_EXTICR
		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber/4;
		uint8_t temp2 =  pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber%4;
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG_PCLK_EN;
		SYSCFG->EXTICR[temp1] = portcode << (temp2 * 4);
		// enable the exti interrupt delivery using IMR
		EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}
	temp = 0;
	// configure the speed
	temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << 2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clearing
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;
	temp = 0;
	// configure pupd settings
	temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << 2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clearing
	pGPIOHandle->pGPIOx->PUPDR |= temp;
	temp = 0;
	// configure the optype
	temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clearing
	pGPIOHandle->pGPIOx->OTYPER |= temp;
	temp = 0;
	//configure the alt functionality
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		uint32_t temp1, temp2;
		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode % 8;
		pGPIOHandle->pGPIOx->AFR[temp1] |= pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2);
	}
}
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA)
	{
		GPIOA_REG_RESET();
	}else if(pGPIOx == GPIOB)
	{
		GPIOB_REG_RESET();
	}else if(pGPIOx == GPIOC)
	{
		GPIOC_REG_RESET();
	}else if(pGPIOx == GPIOD)
	{
		GPIOD_REG_RESET();
	}else if(pGPIOx == GPIOE)
	{
		GPIOE_REG_RESET();
	}else
	{
		GPIOH_REG_RESET();
	}
}
/******************************************************************************
 * @func					GPIO_ReadFromInputPin
 * @brief					This func read data to input pin (IDR)
 * @param					GPIO_RegDef_t *pGPIOx // base address GPIOx
 							uint8_t PinNumber // value pin number
 * @return					uint8_t
 * @Note					none
*/
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);
	return value;
}
/******************************************************************************
 * @func					GPIO_ReadFromInputPort
 * @brief					This func read data to input port (IDR)
 * @param					GPIO_RegDef_t *pGPIOx // base address GPIOx
 * @return					uint16_t
 * @Note					none
*/
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = (uint8_t)(pGPIOx->IDR);
	return value;
}
/******************************************************************************
 * @func					GPIO_WriteOutputPin
 * @brief					This func read data output pin (ODR)
 * @param					GPIO_RegDef_t *pGPIOx // base address GPIOx
 * 							uint8_t PinNumber // value pin number
 * 							uint8_t Value ( Value =  0 or  1)
 * @return					none
 * @Note					none
*/
void GPIO_WriteOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if(Value == GPIO_PIN_SET)
	{
		// write 1 to the output data redister at the bit field corresponding to the pin number
		pGPIOx->ODR |= (0x1 << PinNumber);
	}else
	{
		pGPIOx->ODR &= ~(0x1 << PinNumber);
	}
}
/******************************************************************************
 * @func					GPIO_WriteOutputPort
 * @brief					This func read data output port (ODR)
 * @param					GPIO_RegDef_t *pGPIOx // base address GPIOx
 * 							uint16_t Value ( Value =  0 or  1)
 * @return					none
 * @Note					none
*/
void GPIO_WriteOutputPort(GPIO_RegDef_t *pGPIOx,  uint16_t Value)
{
	pGPIOx->ODR =  Value;
}
/******************************************************************************
 * @func					GPIO_ToggleOutputPin
 * @brief					This func Toggle output pin
 * @param					GPIO_RegDef_t *pGPIOx // base address GPIOx
 * 							uint8_t PinNumber // value pin number
 * @return					none
 * @Note					none
*/
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1 << PinNumber);
}
/******************************************************************************
 * @func					GPIO_IRQInterruptConfig
 * @brief					This func config IRQ interrupt
 * @param					uint8_t IRQNumber, // Number of IQR in NVIC
 * 							uint8_t EnorDi// macros Enable and Disable
 * @return					none
 * @Note					none
*/
void GPIO_IRQInterruptConfig(uint32_t IRQNumber, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			// program ISER0 register
			*NVIC_ISER0 |= (1 << IRQNumber);
		}else if(IRQNumber >= 32 && IRQNumber <= 63)
		{
			// program ISER1 register
			*NVIC_ISER1 |= (1 << (IRQNumber % 32));
		}else if(IRQNumber >= 64 && IRQNumber <= 95)
		{
			// program ISER2 register
			*NVIC_ISER2 |= (1 << (IRQNumber % 64));
		}
	}else
	{
		if(IRQNumber <= 31)
		{
			// program ICER0 register
			*NVIC_ICER0 &= ~(1 << IRQNumber);
		}else if(IRQNumber >= 32 && IRQNumber <= 63)
		{
			// program ICER1 register
			*NVIC_ICER1 &= ~(1 << (IRQNumber % 32));
		}else if(IRQNumber >= 64 && IRQNumber <= 95)
		{
			// program ICER2 register
			*NVIC_ICER2 &= ~(1 << (IRQNumber % 64));
		}
	}
}
/******************************************************************************
 * @func					GPIO_IRQPriorityConfig
 * @brief					This func config Priority IRQ interrupt
 * @param					uint8_t IRQPriority // Priority of IRQ
 * @return					none
 * @Note					none
*/
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
	//1, Fisrt lets find out the IRQ register
	uint8_t iprx = IRQNumber /4;
	uint8_t iprx_section = IRQNumber % 4;
	uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_PR_BASE_ADDR + iprx) |= IRQPriority << shift_amount;
}
/******************************************************************************
 * @func					GPIO_IRQHandling
 * @brief					This func handling interrupt
 * @param					uint8_t PinNumber, // Number of Pin
 * @return					none
 * @Note					none
*/
void GPIO_IRQHandling(uint8_t PinNumber)
{
	// clear the exti pr register cressponding to the pin number
	if(EXTI->PR & (1 << PinNumber))
	{
		// clear
		EXTI->PR |= ( 1 << PinNumber);
	}
}

