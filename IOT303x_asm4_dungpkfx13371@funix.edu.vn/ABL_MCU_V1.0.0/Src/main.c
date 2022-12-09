#include "stm32f401re.h"
#include "stm32f401re_gpio.h"
#include "stm32f401re_rcc.h"
#include "stm32f401re_adc.h"
#include "stm32f401re_usart.h"
#include "timer.h"
#include "stm32f401re_dma.h"
#include "stm32f401re_tim.h"
#include "kalman_filter.h"

#define ADC_PORT			GPIOC
#define ADC_PIN				GPIO_Pin_5
#define ADCx_SENSOR			ADC1
#define ADCx_CLK			RCC_APB2Periph_ADC1
#define DMA_CHANNELx		DMA_Channel_0
#define DMA_STREAMx			DMA2_Stream0
#define ADCx_DR_ADDRESS		((uint32_t) 0x4001204C)

#define Tim_Update			(TIM2->CNT)
#define TIM_PERIOD			8399

static uint32_t dwTimeTotal, dwTimeInit,dwTimeCurrent;
static uint32_t uhADCConvertedValue = 0;
/*
 * Function Init Light Sensor use DMA
*/
void LightSensor_Init(void){
	ADC_InitTypeDef ADC_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	DMA_InitTypeDef DMA_InitStruct;
	// Config GPIO for ADC
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Pin = ADC_PIN;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	// Config ADC commit
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent; // Chọn chế độ Indêpndent
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div2;// Chọn hệ số chia tần số là 1
	ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_1;// Sử dụng DMA
	ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;// Chọn thời gian chuyển là 5 cycle
	ADC_CommonInit(&ADC_CommonInitStruct);
	// Config ADC1
	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;// bit chuyển đổi là 12bit
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;// không cho phép sử dụng chuyển đổi không liên tục
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;// Cho phép chuyển đổi liên tục
	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;// CHọn số kênh sử dụng là 1
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;// cho ghi dữ liệu từ bên phải
	ADC_InitStruct.ADC_NbrOfConversion = 1;

	ADC_Init(ADC1, &ADC_InitStruct);
	//////////////////////////////////////////////
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	DMA_DeInit(DMA_STREAMx);
	DMA_InitStruct.DMA_Channel = DMA_CHANNELx; //CHọn kênh DMA
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)ADCx_DR_ADDRESS;// Địa chỉ thanh ghi chưa data
	DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t)&uhADCConvertedValue;// địa chỉ của biến chưa data
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;// cấu hình chiều dữ liệu từ ngoại vi tới bộ nhớ
	DMA_InitStruct.DMA_BufferSize = 1;// số lượng data truyền là 1
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;// KHông cho phép tăng địa chỉ ngoại vi
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;//Khoogn cho phép tăng địa chỉ bộ nhớ
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;// Chuyển đổi liên tục
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;// ưu tiên cao
	DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA_STREAMx, &DMA_InitStruct);
	// DMA stream0 enable
	DMA_Cmd(DMA_STREAMx, ENABLE);
	// enable DMA request after last transfer (Single ADC mode)
	ADC_DMARequestAfterLastTransferCmd(ADCx_SENSOR, ENABLE);
	// Enable ADC1 DMA
	ADC_DMACmd(ADCx_SENSOR, ENABLE);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 1, ADC_SampleTime_15Cycles);
	ADC_TempSensorVrefintCmd(ENABLE);
	ADC_Cmd(ADC1, ENABLE);
// Start ADC1 Softwware Conversion
	ADC_SoftwareStartConv(ADC1);
}
void LedControl_TimerOCInit(){
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	// Enable GPIO Clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	//Config AF for TIM1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_TIM1);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;

	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// Config Tim1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;// đếm lên
	TIM_TimeBaseStructure.TIM_Prescaler = 0; // hệ số chia tần = 0
	TIM_TimeBaseStructure.TIM_Period = 8399;// tần số 10Khz
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;// hệ ssoso chia tần sử dụng timer
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;// bộ đến lặp lại = 0

	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	TIM_OCInitStructure.TIM_OCMode  = TIM_OCMode_PWM2; // chọn chế đọ PWM
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;// cho phép PWM hoạt động
	TIM_OCInitStructure.TIM_Pulse = 0;// tỉ lệ phần trăm cưng mức cao so với period
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

	TIM_OC4Init(TIM1, &TIM_OCInitStructure);

	TIM_Cmd(TIM1, ENABLE);

	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}
// return value adc dma
uint16_t LightSensor_AdcDMARead(){
	return uhADCConvertedValue;
}
uint16_t Kalman_Filter(uint16_t value){
	KalmanFilterInit(1, 1, 1);
	return KalmanFilter_updateEstimate(value);
}
void LedControl_TimerOCSetPwm(uint16_t Duty_cycle){
	static uint16_t pulse_length = 0;
	pulse_length = ((TIM_PERIOD * Duty_cycle)/100);
	TIM_SetCompare4(TIM1, pulse_length);
}
void ABL_StepBrightness(uint16_t AdcValue){
	if(AdcValue >= 150){
		LedControl_TimerOCSetPwm(10);
	}else if(AdcValue >=100 && AdcValue < 150){
		LedControl_TimerOCSetPwm(30);
	}else if(AdcValue >= 60 && AdcValue < 100){
		LedControl_TimerOCSetPwm(50);
	}else if (AdcValue >= 50 && AdcValue < 60){
		LedControl_TimerOCSetPwm(70);
	}else {
		LedControl_TimerOCSetPwm(100);
	}
}
void ABL_Process(){
	dwTimeCurrent = GetMilSecTick();
		if(dwTimeCurrent >= dwTimeInit){
			dwTimeTotal = dwTimeCurrent - dwTimeInit;
		}else{
			dwTimeTotal = 0xFFFFFFFFU - dwTimeCurrent + dwTimeInit;
		}
		if(dwTimeTotal >= 100){
			dwTimeTotal = 0;
			uint16_t AdcValue = Kalman_Filter(LightSensor_AdcDMARead());
			ABL_StepBrightness(AdcValue);
			dwTimeInit = dwTimeCurrent;
		}
}
int main(void){
	SystemCoreClockUpdate();
	TimerInit();
	LightSensor_Init();
	LedControl_TimerOCInit();
	dwTimeInit = GetMilSecTick();
	while(1){
		processTimerScheduler();
		ABL_Process();
	}
	return 0;
}
