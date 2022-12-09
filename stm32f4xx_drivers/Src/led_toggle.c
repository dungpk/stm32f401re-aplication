/*
 * led_toggle.c
 *
 *  Created on: 8 Jul 2021
 *      Author: cuong
 */
#include "stm32f401xx.h"
void delay_ms(uint32_t milisecond)
{
	for(int i  = 0 ; i < milisecond; i++)
	{
		for(int j = 0; j < 5000; j++);
	}
}
int main(void)
{
	GPIO_Hangle_t GpioLed;
	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_MODE_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl =GPIO_NO_PUPD;

	GPIO_PeriClockControl(GpioLed.pGPIOx, ENABLE);

	GPIO_Init(&GpioLed);

	while(1)
	{
		GPIO_ToggleOutputPin(GpioLed.pGPIOx, GPIO_PIN_NO_5);
		delay_ms(500);
	}
}
