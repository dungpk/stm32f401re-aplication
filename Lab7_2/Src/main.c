#include"stm32f401re.h"
#include"stm32f401re_gpio.h"
#include"stm32f401re_tim.h"
#include"stm32f401re_rcc.h"

#define TIM_PERIOD			8399

void TimPwm_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_TIM1);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;

	GPIO_Init(GPIOA, &GPIO_InitStructure);


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_Period = 8399;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	//TIM_Cmd(TIM2, ENABLE);

	TIM_OCInitStructure.TIM_OCMode  = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

	TIM_OC4Init(TIM1, &TIM_OCInitStructure);

	TIM_Cmd(TIM1, ENABLE);

	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

static
void LedControl_PWM(uint16_t  Duty_cycle){
	static uint16_t pulse_length = 0;
	pulse_length = ((TIM_PERIOD * Duty_cycle)/100);
	TIM_SetCompare4(TIM1, pulse_length);
}
int main(void){
	SystemCoreClockUpdate();
	TimPwm_Init();
	while(1){
		LedControl_PWM(100);
	}
}
