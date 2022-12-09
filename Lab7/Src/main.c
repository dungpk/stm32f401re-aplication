#include"stm32f401re.h"
#include"stm32f401re_gpio.h"
#include"stm32f401re_tim.h"
#include"stm32f401re_rcc.h"

#define LED_GREEN_PORT		GPIOA
#define LED_GREEN_PIN		GPIO_Pin_5
#define LED_GREEN			5

#define GPIO_PIN_SET		1
#define GPIO_PIN_RESET		0

void Led_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED_GREEN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

	GPIO_Init(LED_GREEN_PORT, &GPIO_InitStructure);
}
static
void Led_Control(GPIO_TypeDef *pGPIOx, uint8_t GPIO_PIN, uint8_t Status){
	if(Status == GPIO_PIN_SET){
		pGPIOx->BSRRL |= 1 << GPIO_PIN;
	}else{
		pGPIOx->BSRRH |= 1 << GPIO_PIN;
	}
}
void Time_Init(void){
	TIM_TimeBaseInitTypeDef Timer_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	Timer_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	Timer_InitStructure.TIM_Prescaler = 83;
	Timer_InitStructure.TIM_Period = 999;
	Timer_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	Timer_InitStructure.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM1, &Timer_InitStructure);
	TIM_Cmd(TIM1, ENABLE);
}

void Delay_ms(uint32_t ms){
	while(ms != 0){
		TIM_SetCounter(TIM1, 0);
		while(TIM_GetCounter(TIM1) != 999);
		ms--;
	}
}
int main(void){
	SystemCoreClockUpdate();
	Led_Init();
	Time_Init();
	while(1){
		Led_Control(LED_GREEN_PORT, LED_GREEN, GPIO_PIN_SET);
		Delay_ms(500);
		Led_Control(LED_GREEN_PORT, LED_GREEN, GPIO_PIN_RESET);
		Delay_ms(500);
	}
	return 0;
}
