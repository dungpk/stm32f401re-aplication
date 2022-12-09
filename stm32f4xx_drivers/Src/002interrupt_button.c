/*
 * 002interrupt_button.c
 *
 *  Created on: 10 Jul 2021
 *      Author: cuong
 */

/*
 * led_button.c
 *
 *  Created on: 8 Jul 2021
 *      Author: cuong
 */
#include "stm32f401xx.h"
#include <string.h>
#define BUTTON_PRESS		0
void delay_ms(uint32_t milisecond)
{
	for(int i  = 0 ; i < milisecond; i++)
	{
		for(int j = 0; j < 5000; j++);
	}
}
int main(void)
{
	GPIO_Hangle_t GpioLed1,GpioLed2 , GpioButton;
	memset((&GpioLed1), 0, sizeof(GpioLed1));
	memset((&GpioLed2), 0, sizeof(GpioLed2));
	memset((&GpioButton), 0, sizeof(GpioButton));
	// configura GpioLed1 Green1
	GpioLed1.pGPIOx = GPIOA;
	GpioLed1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GpioLed1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed1.GPIO_PinConfig.GPIO_PinSpeed = GPIO_MODE_SPEED_FAST;
	GpioLed1.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed1.GPIO_PinConfig.GPIO_PinPuPdControl =GPIO_NO_PUPD;

	GPIO_PeriClockControl(GpioLed1.pGPIOx, ENABLE);

	GPIO_Init(&GpioLed1);
	// configura LED GpioLed2 Green2
	GpioLed2.pGPIOx = GPIOA;
	GpioLed2.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_11;
	GpioLed2.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed2.GPIO_PinConfig.GPIO_PinSpeed = GPIO_MODE_SPEED_FAST;
	GpioLed2.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed2.GPIO_PinConfig.GPIO_PinPuPdControl =GPIO_NO_PUPD;

	GPIO_PeriClockControl(GpioLed2.pGPIOx, ENABLE);

	GPIO_Init(&GpioLed2);
	// config BUTTON
	GpioButton.pGPIOx = GPIOB;
	GpioButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GpioButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_MODE_SPEED_FAST;
	GpioButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GpioButton.pGPIOx, ENABLE);
	GPIO_Init(&GpioButton);
	// Config IRQ
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI9_5, NVIC_IRQ_PRI15);
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI9_5, ENABLE);

	while(1);
	return 0;
}
void EXTI9_5_IRQHandler(void)
{
	delay_ms(100);
	GPIO_IRQHandling(GPIO_PIN_NO_5);
	GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_0);
	GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_11);
}



