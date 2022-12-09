#include <stdio.h>
#include <string.h>


#include "system_stm32f4xx.h"
#include "stm32f401re_usart.h"
#include "stm32f401re_gpio.h"
#include "stm32f401re_rcc.h"
#include "buzzer.h"
#include "led.h"
#include "lightsensor.h"
#include "temhumsensor.h"
#include "serial.h"
//#include "uartcmd.h"
#include "timer.h"
#include "melody.h"
#include "Ucglib.h"
#include "misc.h"
#include "buff.h"

#define USART2_RX		GPIO_Pin_3
#define USART2_Baud 	9600

#define SIZE_QUEUE_DATA_RX 256
#if (SIZE_QUEUE_DATA_RX & (SIZE_QUEUE_DATA_RX - 1)) != 0
#error "SIZE_QUEUE_DATA_RX must be a power of two"
#endif


/* ! @ brief Size of rx buffer*/
#define RX_BUFFER_SIZE 16
/*! @brief Start of frame*/
#define FRAME_SOF 0xB1
/*! @brief frame ack and nack*/
#define FRAME_ACK 0x06
#define FRAME_NACK 0x15
/*! @brief Field type*/
#define CMD_TYPE_GET 0x00
#define CMD_TYPE_RES 0x01
#define CMD_TYPE_SET 0x02
/*! @brief Check xor init*/
#define CXOR_INIT_VAL 0xFF
/*! @brief Field Command*/
#define CMD_ID_DEVICE 0x00
#define CMD_ID_LED 0x01
#define CMD_ID_BUZZER 0x04
#define CMD_ID_BUTTON 0x82
#define CMD_ID_TEMP_SENSOR 0x84
#define CMD_ID_HUMI_SENSOR 0x85
#define CMD_ID_LIGHT_SENSOR 0x86
#define CMD_ID_LCD 0x87

#define CMD_ID byRxBuffer[2]
#define CMD_TYPE byRxBuffer[3]
#define CMD_DATA_EPOINT byRxBuffer[4]
#define CMD_DATA_STATE byRxBuffer[5]
#define FRAME_SIZE_MAX 9
///////////////////////////////////////////////////////////
static uint8_t byRxBufState;
static uint8_t byIndexRxBuf;
static uint8_t byCheckXorRxBuf;
buffqueue_t serialQueueRx;
static uint8_t pBuffDataRx[SIZE_QUEUE_DATA_RX];
uint8_t byRxBufferData[RX_BUFFER_SIZE] = {0};
uint16_t Data_Receive;
ucg_t ucg;
///////////////////////////////////////////////////////////
typedef struct
{
	uint8_t cmdid;
	uint8_t type;
} frm_common_t;

typedef struct
{
	uint8_t cmdid;
	uint8_t type;
	uint8_t epoint;
	uint8_t state;
} frm_button_state_t;

typedef struct
{
	uint8_t cmdid;
	uint8_t type;
	uint8_t state;
} frm_buzzer_state_t;

typedef struct
{
	uint8_t cmdid;
	uint8_t type;
	uint8_t text[20];
} frm_lcd_display_t;

typedef struct
{
	uint8_t cmdid;
	uint8_t type;
	uint8_t numID;
	uint8_t color;
	uint8_t counter;
	uint8_t interval;
	uint8_t laststate;
	uint8_t reserved;
} frm_led_indicator_t;

typedef struct
{
	uint8_t cmdid;
	uint8_t type;
	uint8_t mode;
	uint8_t data[2];
} frm_setup_config_t;

typedef union
{
	frm_common_t cmdCommon;
	frm_button_state_t buttonState;
	frm_buzzer_state_t buzzerState;
	frm_led_indicator_t ledIndicator;
	frm_lcd_display_t lcdDisplay;
	frm_setup_config_t setConfig;
} frm_receive_t, *frm_receive_p;

void USART2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_InitStruct.GPIO_Pin = USART2_RX | GPIO_Pin_2;

	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	USART_InitStruct.USART_BaudRate = USART2_Baud;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx;

	USART_Init(USART2, &USART_InitStruct);
	USART_Cmd(USART2, ENABLE);

	// Enable USARTx Receive interrupts--------------------------------------
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART2, USART_IT_TXE, DISABLE);

	// NVIC configuration----------------------------------------------------
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	// Enable the USARTx Interrupt-------------------------------------------
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
/*
 *Function Init queue and usart2
*/
void SerialReceive_Init(void)
{
	bufInit(pBuffDataRx, &serialQueueRx, sizeof(pBuffDataRx[0]), SIZE_QUEUE_DATA_RX);
	USART2_Init();
}
/*
 * function serialpoll return USART state
*/
uint8_t serialPoll(void)
{
	uint8_t byRxData;
	uint8_t byUartState = (uint8_t)UART_STATE_IDLE;
	while (bufNumItems(&serialQueueRx) != 0 && byUartState == UART_STATE_IDLE)
	{
		bufDeDat(&serialQueueRx, &byRxData);
		uint8_t numItiem = bufNumItems(&serialQueueRx);
		switch (byRxBufState)
		{
		case RX_STATE_START_BYTE:
			if (byRxData == FRAME_SOF)
			{
				byIndexRxBuf = 0;
				byCheckXorRxBuf = CXOR_INIT_VAL;
				byRxBufState = RX_STATE_DATA_BYTES;
			}
			else if (byRxData == FRAME_ACK)
				byUartState = UART_STATE_ACK_RECEIVED;
			else if (byRxData == FRAME_NACK)
				byUartState = UART_STATE_NACK_RECEIVED;
			else
				byUartState = UART_STATE_ERROR;
			break;
		case RX_STATE_DATA_BYTES:
			if (byIndexRxBuf < RX_BUFFER_SIZE)
			{
				byRxBufferData[byIndexRxBuf] = byRxData;
				if (byIndexRxBuf > 0)
					byCheckXorRxBuf ^= byRxData;
				if (++byIndexRxBuf == *byRxBufferData)
					byRxBufState = RX_STATE_CXOR_BYTE;
			}
			else
			{
				byRxBufState = RX_STATE_START_BYTE;
				byUartState = UART_STATE_ERROR;
			}
			break;
		case RX_STATE_CXOR_BYTE:
			if (byRxData == byCheckXorRxBuf)
				byUartState = UART_STATE_DATA_RECEIVED;
			else
				byUartState = UART_STATE_ERROR;
		default:
			byRxBufState = RX_STATE_START_BYTE;
			break;
		}
	}
	return byUartState;
}
/*
 * fuction uart command process
*/
void UartCommandProcess(void *arg)
{
	frm_receive_p pCmd = (frm_receive_p)arg;
	switch (pCmd->cmdCommon.cmdid)
	{
	case CMD_ID_LED:
		if(pCmd->ledIndicator.laststate == LED_COLOR_BLACK ){
			LedControl_SetColorGeneral(pCmd->ledIndicator.numID, pCmd->ledIndicator.color, 0);
		} else {
			LedControl_SetColorGeneral(pCmd->ledIndicator.numID, pCmd->ledIndicator.color, 100);
		}
		break;
	case CMD_ID_BUZZER:
		if(pCmd->buzzerState.state == 1)
		BuzzerControl_SetMelody(pbeep);
		else
		BuzzerControl_SetMelody(0);
		break;
	case CMD_ID_HUMI_SENSOR:
		ucg_ClearScreen(&ucg);
		static char humi[20] = "";
		uint16_t humidity = (uint8_t)(TemHumSensor_GetHumi() / 100);
		// Display output
		memset(humi, 0, sizeof(humi));
		sprintf(humi, "Humi = %ld %%", humidity);
		ucg_DrawString(&ucg, 0, 32, 0, humi);
		break;
	case CMD_ID_LIGHT_SENSOR:
		ucg_ClearScreen(&ucg);
		static char light[20] = "";
		uint16_t lightValue = LightSensor_MeasureUseDMAMode();
		// Display output
		memset(light, 0, sizeof(light));
		sprintf(light, "Light = %d", lightValue);
		ucg_DrawString(&ucg, 0, 32, 0, light);
	case CMD_ID_TEMP_SENSOR:
		ucg_ClearScreen(&ucg);
		static char temp[20] = "";
		uint16_t temperature = (uint8_t)(TemHumSensor_GetTemp() / 100);
		// Display output
		memset(temp, 0, sizeof(temp));
		sprintf(temp, "Temp = %d oC", temperature);
		ucg_DrawString(&ucg, 0, 32, 0, temp);
		break;
	case CMD_ID_LCD:
		ucg_ClearScreen(&ucg);
		ucg_DrawString(&ucg, 0, 32, 0, pCmd->lcdDisplay.text);
	default:
		break;
	}
}
void ProcessSerialReceive()
{
	uint8_t stateRx = serialPoll();
//	uint8_t stateRx = UART_STATE_IDLE;
	if (stateRx != UART_STATE_IDLE)
	{
		switch (stateRx)
		{
		case UART_STATE_ACK_RECEIVED:
			printf(" UART_STATE_ACK_RECEIVED\r\n");
			break;
		case UART_STATE_NACK_RECEIVED:
			printf(" UART_STATE_NACK_RECEIVED\r\n");
			break;
		case UART_STATE_DATA_RECEIVED:
			UartCommandProcess(&byRxBufferData[2]);
			break;
		case UART_STATE_ERROR:
		case UART_STATE_RX_TIMEOUT:
			printf("UART_STATE_RX_TIMEOUT\r\n");
			break;
		default:
			break;
		}
	}
}
int main()
{
	SystemCoreClockUpdate();
	TimerInit();
	SerialReceive_Init();
	LedControl_Init();
	BuzzerControl_Init();
	LightSensor_Init(ADC_READ_MODE_DMA);
	TemHumSensor_Init();
	Ucglib4WireSWSPI_begin(&ucg, UCG_FONT_MODE_SOLID);
	ucg_ClearScreen(&ucg);
	ucg_SetFont(&ucg, ucg_font_ncenR12_hr);
	ucg_SetColor(&ucg, 0, 255, 255, 255);
	ucg_SetColor(&ucg, 1, 0, 0, 0);
	ucg_SetRotate180(&ucg);
	while (1)
	{
		processTimerScheduler();
		ProcessSerialReceive();
	}
	return 0;
}

void USART2_IRQHandler(void)
{
	__disable_irq();
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{
		uint8_t byRecv = USART_ReceiveData(USART2);
		bufEnDat(&serialQueueRx, &byRecv);
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}
	__enable_irq();
}
