#include"stm32f401re.h"
#include"stm32f401re_gpio.h"
#include"stm32f401re_tim.h"
#include"stm32f401re_rcc.h"
#include"stm32f401re_usart.h"
#include"misc.h"

#define USART2_TX				GPIO_Pin_2
#define Tim_Update				(TIM2->CNT)
#define TimLimit_SendData		1000

uint8_t status = 1, check_rising = 0;
uint16_t Tim_Rising  = 0;
uint16_t Number_Press = 0;
uint32_t Tim_SendData = 0;
void delay_ms(uint32_t milliseconds){
	for(int i =0; i < milliseconds; i++){
		for(int j = 0; j < 5000; j++);
	}
}
void Timer_Config(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICIbitStrcuture;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;

	GPIO_Init(GPIOB, &GPIO_InitStructure);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Prescaler = 41999;
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	//TIM_Cmd(TIM2, ENABLE);

	TIM_ICIbitStrcuture.TIM_Channel  = TIM_Channel_2;
	TIM_ICIbitStrcuture.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
	TIM_ICIbitStrcuture.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICIbitStrcuture.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICIbitStrcuture.TIM_ICFilter = 0x0;

	TIM_ICInit(TIM2, &TIM_ICIbitStrcuture);

	TIM_Cmd(TIM2, ENABLE);

	TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);
}
void USART2_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);	//TX

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx;

	USART_Init(USART2, &USART_InitStruct);
	USART_Cmd(USART2, ENABLE);
}

void Check_Tim_Press(void){
	if(status == 0){
		Number_Press++;

	}else if(status == 1){
		check_rising = 1;
		Tim_Rising = TIM_GetCapture2(TIM2);
	}
}
void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2, TIM_IT_CC2)){
		status = 1 - status;
		Check_Tim_Press();
	}
	TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);
}
static
void Send_NumberPress(void){
	if(status == 1 && check_rising == 1){
		if(Tim_Update < Tim_Rising ){
			Tim_SendData = (0xffff + Tim_Update) - Tim_Rising;
		}else{
			Tim_SendData = Tim_Update - Tim_Rising;
		}
		if(Tim_SendData > TimLimit_SendData){
			USART_SendData(USART2, Number_Press);
			Number_Press = 0;
			Tim_SendData = 0;
			check_rising =  0;
		}
	}
}
int main(void){
	SystemCoreClockUpdate();
	USART2_Init();
	Timer_Config();
	while(1){
		Send_NumberPress();
	}
	return 0;
}
