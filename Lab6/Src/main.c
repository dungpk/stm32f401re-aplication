#include"stm32f401re.h"
#include"stm32f401re_rcc.h"
#include"stm32f401re_usart.h"
#include"stm32f401re_gpio.h"
#include"misc.h"

#define GPIO_PIN_SET			1
#define GPIO_PIN_RESET			0
#define GPIO_PIN_LOW			0
#define GPIO_PIN_HIGH			1

#define LED					GPIO_Pin_5
#define PIN_LED					5
#define BUTTON				GPIO_Pin_13
#define PIN_BUTTON				13

#define USART6_TX			GPIO_Pin_6
#define USART6_GPIO			GPIOC
#define USART6_GPIO_CLOCK	RCC_AHB1Periph_GPIOC
#define USART6_CLOCK		RCC_APB2Periph_USART6

#define USART1_RX			GPIO_Pin_7
#define USART1_GPIO			GPIOB
#define USART1_GPIO_CLOCK	RCC_AHB1Periph_GPIOB
#define USART1_CLOCK		RCC_APB2Periph_USART1

#define USARTx_Baud			9600

#define Check_Data			0x10

uint16_t Data_Receive = 0;

void Led_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void Button_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = BUTTON;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
void Delay_ms(uint32_t milliseconds){
	for(int i = 0; i < milliseconds; i++){
		for(int j = 0; j < 5000; j++);
	}
}
static
void Led_Control(GPIO_TypeDef *pGPIOx, uint8_t GPIO_PIN, uint8_t Status){
	if(Status == GPIO_PIN_SET){
		pGPIOx->BSRRL |= 1 << GPIO_PIN;
	}else{
		pGPIOx->BSRRH |= 1 << GPIO_PIN;
	}
}
static
uint8_t GPIO_READ_PIN(GPIO_TypeDef *pGOIOx, uint8_t GPIO_PIN){
	uint8_t Read_Pin;

	Read_Pin = ((pGOIOx->IDR) >>  GPIO_PIN) & 0x01;
	return Read_Pin;
}
/**
 * @func   Initializes Use USART6 Periperal
 * @brief  USART6_Init
 * @param  None
 * @retval None
 */
static
void USART6_Init(void)
{
	GPIO_InitTypeDef     GPIO_InitStructure;
	USART_InitTypeDef    USART_InitStructure;

	//Enable Clock USART1 And GPIOC------------------------------------------
	RCC_AHB1PeriphClockCmd(USART6_GPIO_CLOCK, ENABLE);

	//Initializes GPIO Use USART6 Periperal----------------------------------
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_InitStructure.GPIO_Pin = USART6_TX;
	GPIO_Init(USART6_GPIO, &GPIO_InitStructure);

	//Initializes GPIO As Alternate function mode----------------------------
	GPIO_PinAFConfig(USART6_GPIO, GPIO_PinSource6, GPIO_AF_USART6);

	//Initializes USART6 Periperal-------------------------------------------
	RCC_APB2PeriphClockCmd(USART6_CLOCK,ENABLE);

	USART_InitStructure.USART_BaudRate = USARTx_Baud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx;

	USART_Init(USART6, &USART_InitStructure);

	USART_Cmd(USART6, ENABLE);

}

/**
 * @func   Initializes Use USART1 Periperal
 * @brief  USART1_Init
 * @param  None
 * @retval None
 */
static
void USART1_Init(void)
{
    GPIO_InitTypeDef     GPIO_InitStructure;
    USART_InitTypeDef    USART_InitStructure;
    NVIC_InitTypeDef     NVIC_InitStructure;

    //Enable clock GPIO And USART1------------------------------------------
    RCC_AHB1PeriphClockCmd(USART1_GPIO_CLOCK, ENABLE);

    //Initializes GPIO Use USART1 Periperal---------------------------------
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;

    GPIO_InitStructure.GPIO_Pin = USART1_RX ;
    GPIO_Init(USART1_GPIO, &GPIO_InitStructure);


    //Initializes GPIO As Alternate function mode---------------------------
	GPIO_PinAFConfig(USART1_GPIO, GPIO_PinSource7, GPIO_AF_USART1);

	//Initializes USART1 Periperal------------------------------------------
	RCC_APB2PeriphClockCmd(USART1_CLOCK, ENABLE);

    USART_InitStructure.USART_BaudRate = USARTx_Baud;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx;

    USART_Init(USART1, &USART_InitStructure);

	//Enable USART----------------------------------------------------------
    USART_Cmd(USART1, ENABLE);

    //Enable USARTx Receive interrupts--------------------------------------
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	//NVIC configuration----------------------------------------------------
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	//Enable the USARTx Interrupt-------------------------------------------
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void USART1_IRQHandler(void){
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET){
		Data_Receive = USART_ReceiveData(USART1);
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}

int main(){
	SystemCoreClockUpdate();
	Button_Init();
	Led_Init();
	USART1_Init();
	USART6_Init();
	while(1){
	//	Delay_ms(1000);
		if(GPIO_READ_PIN(GPIOC, PIN_BUTTON) == 0){
				USART_SendData(USART6, 0x10);
		}
//		Delay_ms(100);
//		if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET){
//			Data_Receive = USART_ReceiveData(USART1);
//		}
		//Data_Receive = USART_ReceiveData(USART1);
			if(Data_Receive == Check_Data){
				for(int i = 0; i < 5; i++){
					Led_Control(GPIOA, PIN_LED, GPIO_PIN_SET);
					Delay_ms(1000);
					Led_Control(GPIOA, PIN_LED, GPIO_PIN_RESET);
					Delay_ms(1000);
				}
				Data_Receive = 0;
			}
	}
	return 0;
}
