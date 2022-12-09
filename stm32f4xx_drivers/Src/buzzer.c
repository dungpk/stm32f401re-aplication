/*
 * buzzer.c
 *
 *  Created on: 8 Jul 2021
 *      Author: cuong
 */
#include "stm32f401xx.h"
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
	GPIO_Hangle_t GpioBuzzer, GpioButton;
	GpioBuzzer.pGPIOx = GPIOC;
	GpioBuzzer.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
	GpioBuzzer.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioBuzzer.GPIO_PinConfig.GPIO_PinSpeed = GPIO_MODE_SPEED_FAST;
	GpioBuzzer.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioBuzzer.GPIO_PinConfig.GPIO_PinPuPdControl =GPIO_NO_PUPD;

	GPIO_PeriClockControl(GpioBuzzer.pGPIOx, ENABLE);

	GPIO_Init(&GpioBuzzer);

	// config BUTTON
	GpioButton.pGPIOx = GPIOB;
	GpioButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GpioButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_MODE_SPEED_FAST;
	GpioButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GpioButton.pGPIOx, ENABLE);

	GPIO_Init(&GpioButton);

	while(1)
	{
		if(GPIO_ReadFromInputPin(GpioButton.pGPIOx, GPIO_PIN_NO_5) == BUTTON_PRESS)
		{
			delay_ms(100);
			GPIO_ToggleOutputPin(GpioBuzzer.pGPIOx, GPIO_PIN_NO_9);
		}
	}
}

