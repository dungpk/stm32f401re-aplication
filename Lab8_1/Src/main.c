#include "stm32f401re.h"
#include "stm32f401re_gpio.h"
#include "stm32f401re_rcc.h"
#include "stm32f401re_adc.h"
#include "stm32f401re_usart.h"
#include "timer.h"

#define ADC_PORT			GPIOC
#define ADC_PIN				GPIO_Pin_5

static uint32_t dwTimeTotal, dwTimeInit, dwTimeCurrent;

void ADC_TemperatureInit(void){
	ADC_InitTypeDef ADC_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;\
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Pin = ADC_PIN;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC, ENABLE);
	ADC_DeInit();
	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStruct);

	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_NbrOfConversion = 1;

	ADC_Init(ADC1, &ADC_InitStruct);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_TempSensor, 1, ADC_SampleTime_144Cycles);
	ADC_TempSensorVrefintCmd(ENABLE);
	ADC_Cmd(ADC1, ENABLE);
}
void USART2_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;//TX

	GPIO_Init(GPIOA, &GPIO_InitStruct);


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
static
void Cover_Temperature(void){
	float TemperatureValue = 0, TemperatureValueLast = 0;
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	TemperatureValue = ADC_GetConversionValue(ADC1);

	TemperatureValue *= 3300;
	TemperatureValue /= 4096;

	TemperatureValue /= (float) 1000.0;

	TemperatureValue -= (float) 0.760;

	TemperatureValue /= (float) 0.0025;

	TemperatureValueLast = TemperatureValue +(float) 25.0;
	USART_SendData(USART2,TemperatureValueLast);
}

static
void MultiSensorScan(void){
	dwTimeCurrent = GetMilSecTick();
	if(dwTimeCurrent >= dwTimeInit){
		dwTimeTotal = dwTimeCurrent - dwTimeInit;
	}else{
		dwTimeTotal = 0xFFFFFFFFU - dwTimeCurrent + dwTimeInit;
	}
	if(dwTimeTotal >= 2000){
		dwTimeTotal = 0;
		Cover_Temperature();
		dwTimeInit = dwTimeCurrent;
	}
}

int main(void){
	SystemCoreClockUpdate();
	TimerInit();
	USART2_Init();
	ADC_TemperatureInit();
	ADC_SoftwareStartConv(ADC1);
	dwTimeInit = GetMilSecTick();
	while(1){
		MultiSensorScan();
	}
	return 0;
}
