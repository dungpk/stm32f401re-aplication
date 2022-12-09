#include "stm32f401re.h"
#include "stm32f401re_gpio.h"
#include "stm32f401re_rcc.h"
#include "stm32f401re_adc.h"
#include "stm32f401re_usart.h"
#include "timer.h"
#include "stm32f401re_dma.h"

#define USART2_TX			GPIO_Pin_2
#define USART2_Baud			9600

#define ADC_PORT			GPIOC
#define ADC_PIN				GPIO_Pin_5

#define ADCx_SENSOR			ADC1
#define ADCx_CLK			RCC_APB2Periph_ADC1
#define DMA_CHANNELx		DMA_Channel_0
#define DMA_STREAMx			DMA2_Stream0
#define ADCx_DR_ADDRESS		((uint32_t) 0x4001204C)

static uint32_t uhADCConvertedValue = 0;
static uint32_t dwTimeTotal, dwTimeInit,Light,dwTimeCurrent;

void LightSensor_Init(void){
	ADC_InitTypeDef ADC_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	DMA_InitTypeDef DMA_InitStruct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Pin = ADC_PIN;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
//	GPIO_PinAFConfig(GPIOC, GPIO_PinSource5,GPIO_AF)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_1;
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
	//////////////////////////////////////////////
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	DMA_DeInit(DMA_STREAMx);
	DMA_InitStruct.DMA_Channel = DMA_CHANNELx;
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)ADCx_DR_ADDRESS;
	DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t)&uhADCConvertedValue;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStruct.DMA_BufferSize = 1;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA_STREAMx, &DMA_InitStruct);

	DMA_Cmd(DMA_STREAMx, ENABLE);

	ADC_DMARequestAfterLastTransferCmd(ADCx_SENSOR, ENABLE);
	ADC_DMACmd(ADCx_SENSOR, ENABLE);


	ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 1, ADC_SampleTime_15Cycles);
	ADC_TempSensorVrefintCmd(ENABLE);
	ADC_Cmd(ADC1, ENABLE);

	ADC_SoftwareStartConv(ADC1);
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
uint16_t LightSenSor_MeasureUseDMA(void){
	return uhADCConvertedValue;
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
		Light = LightSenSor_MeasureUseDMA();
		USART_SendData(USART2, Light);
		dwTimeInit = dwTimeCurrent;
	}
}
int main(void){
	SystemCoreClockUpdate();
	TimerInit();
	USART2_Init();
	LightSensor_Init();
	dwTimeInit = GetMilSecTick();
	while(1){
		MultiSensorScan();
	}
	return 0;
}
