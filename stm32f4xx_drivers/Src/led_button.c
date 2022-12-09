
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
	GPIO_Hangle_t GpioLed, GpioButton;
	// Enable Clock
	GPIO_PeriClockControl(GpioLed.pGPIOx, ENABLE);
	// configur LED
	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_MODE_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&GpioLed);
	// config BUTTON
	GpioButton.pGPIOx = GPIOB;
	GpioButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
	GpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GpioButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_MODE_SPEED_FAST;
	GpioButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GpioButton.pGPIOx, ENABLE);

	GPIO_Init(&GpioButton);

	while(1)
	{
		if(GPIO_ReadFromInputPin(GpioButton.pGPIOx, GPIO_PIN_NO_4) == BUTTON_PRESS)
		{
			delay_ms(50);
			GPIO_ToggleOutputPin(GpioLed.pGPIOx, GPIO_PIN_NO_0);
		}
	}
	return 0;
}


