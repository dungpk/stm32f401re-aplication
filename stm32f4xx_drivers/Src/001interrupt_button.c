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
	GPIO_Hangle_t GpioLed, GpioButton;
	// configur LED
	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_MODE_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl =GPIO_NO_PUPD;
	GPIO_PeriClockControl(GpioLed.pGPIOx, ENABLE);
	GPIO_Init(&GpioLed);
	// config BUTTON
	GpioButton.pGPIOx = GPIOC;
	GpioButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GpioButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_MODE_SPEED_FAST;
	GpioButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_PeriClockControl(GpioButton.pGPIOx, ENABLE);
	GPIO_Init(&GpioButton);
	// Config IRQ
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10, NVIC_IRQ_PRI15);
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI15_10, ENABLE);

	while(1);
	return 0;
}
void EXTI15_10_IRQHandler(void)
{
	//delay_ms(100);
	GPIO_IRQHandling(GPIO_PIN_NO_13);
	GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
}


