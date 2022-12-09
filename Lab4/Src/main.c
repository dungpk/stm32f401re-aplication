hưng #include"stm32f401re.h"
#include"stm32f401re_rcc.h"
#include"stm32f401re_spi.h"
#include"stm32f401re_gpio.h"
#include"misc.h"

#define GPIO_PIN_SET			1
#define GPIO_PIN_RESET			0
#define GPIO_PIN_LOW			0
#define GPIO_PIN_HIGH			1

#define LED					GPIO_Pin_11
#define PIN_LED					11
#define BUTTON				GPIO_Pin_13
#define PIN_BUTTON				13
#define PIN_NSS					12

#define SPI_MASTER_GPIO_CLOCK	RCC_AHB1Periph_GPIOB
#define SPI_MASTER_CLOCK		RCC_APB1Periph_SPI2
#define SPI_MASTER_GPIO			GPIOB
#define SPI_MASTER				SPI2
#define NSS_MASTER				GPIO_Pin_12
#define SCK_MASTER				GPIO_Pin_13
#define MISO_MASTER				GPIO_Pin_14
#define MOSI_MASTER				GPIO_Pin_15

#define SPI_SLAVE_GPIO_CLOCK	RCC_AHB1Periph_GPIOA
#define SPI_SLAVE_CLOCK			RCC_APB2Periph_SPI1
#define SPI_SLAVE_GPIO			GPIOA
#define SPI_SLAVE				SPI1
#define NSS_SLAVE				GPIO_Pin_4
#define SCK_SLAVE				GPIO_Pin_5
#define MISO_SLAVE				GPIO_Pin_6
#define MOSI_SLAVE				GPIO_Pin_7

#define Check_DataSlave			0xB1

#define DEBUG_BREAK           __asm__("BKPT #0");

static uint16_t Receive_Data = 0;
static uint16_t Receive_Data_Slave, Receive_Data_Master;
uint32_t msTicks = 0;
/******************************************************************************
 * @func					delay_ms
 * @brief					This func delay milisecond
 * @param					uint32_t milisecond
 * @return					none
 * @Note					none
*/
void Delay(uint32_t dlyTicks)
{
      uint32_t curTicks;

      curTicks = msTicks;
      while ((msTicks - curTicks) < dlyTicks) ;
}
void SPI1_SlaveConfig(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(SPI_SLAVE_GPIO_CLOCK, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = MISO_SLAVE| MOSI_SLAVE|SCK_SLAVE;
	GPIO_Init(SPI_SLAVE_GPIO, &GPIO_InitStructure);

//	// Config SPI1_SCK on GPIOB - PB3
//	RCC_AHB1PeriphClockCmd(GPIOB, ENABLE);
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_InitStructure.GPIO_Pin = SCK_SLAVE;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);

//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);
	GPIO_PinAFConfig(SPI_SLAVE_GPIO, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(SPI_SLAVE_GPIO, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(SPI_SLAVE_GPIO, GPIO_PinSource7, GPIO_AF_SPI1);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = NSS_SLAVE;
	GPIO_Init(SPI_SLAVE_GPIO, &GPIO_InitStructure);

	// enable peripheral clock SPI1
	RCC_APB2PeriphClockCmd(SPI_SLAVE_CLOCK, ENABLE);

	// set to full deplex mode, seperate MOSI and MISO Lines
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;

	// Use SPI1 as slave mode
	SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;

	// One packet of data is 8 bits wide
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;

	// Clock is low when idle
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;

	// Data sampled at first edge
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;

	//SPI frequency is APB2 frequency
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;

	// Set NSS us software
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;

	// data is trasmitted MSB first
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;

	SPI_Init(SPI_SLAVE, &SPI_InitStructure);

	// Enable SPI1
	SPI_Cmd(SPI_SLAVE, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	SPI_ITConfig(SPI_SLAVE, SPI_I2S_IT_RXNE, ENABLE);
}
void SPI2_MasterConfig(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(SPI_MASTER_GPIO_CLOCK, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = SCK_MASTER| MISO_MASTER| MOSI_MASTER;
	GPIO_Init(SPI_MASTER_GPIO, &GPIO_InitStructure);

	GPIO_PinAFConfig(SPI_MASTER_GPIO, GPIO_PinSource13, GPIO_AF_SPI2);
	GPIO_PinAFConfig(SPI_MASTER_GPIO, GPIO_PinSource14, GPIO_AF_SPI2);
	GPIO_PinAFConfig(SPI_MASTER_GPIO, GPIO_PinSource15, GPIO_AF_SPI2);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_InitStructure.GPIO_Pin = NSS_MASTER;
	GPIO_Init(SPI_MASTER_GPIO, &GPIO_InitStructure);

	// enable peripheral clock SPI1
	RCC_APB1PeriphClockCmd(SPI_MASTER_CLOCK, ENABLE);

	// set to full deplex mode, seperate MOSI and MISO Lines
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;

	// Use SPI1 as slave mode
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;

	// One packet of data is 8 bits wide
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;

	// Clock is low when idle
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;

	// Data sampled at first edge
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;

	//SPI frequency is APB2 frequency
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;

	// Set NSS us software
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;

	// data is trasmitted LSB first
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;

	SPI_Init(SPI_MASTER, &SPI_InitStructure);

	// Enable SPI2
	SPI_Cmd(SPI_MASTER, ENABLE);

}

void GPIO_PinControl(GPIO_TypeDef *pGPIO, uint8_t GPIO_Pin, uint8_t newstate)
{
	if(newstate == GPIO_PIN_SET){
		pGPIO->BSRRL |= 1 << GPIO_Pin;
	}else{
		pGPIO->BSRRH |= 1 << GPIO_Pin;
	}
}

void Send_Data(SPI_TypeDef *SPIx, uint8_t data){
	// Allow Send data to slave
	GPIO_PinControl(SPI_MASTER_GPIO, PIN_NSS, GPIO_PIN_SET);
	while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET){;}
	SPI_I2S_SendData(SPIx, data);

	// Allow Send Data to Slave
	GPIO_PinControl(SPI_MASTER_GPIO, PIN_NSS, GPIO_PIN_RESET);
}

uint16_t Receiver_Data_Slave(SPI_TypeDef *SPIx){
	uint16_t Data_Revice = 0;
	Data_Revice = SPI_I2S_ReceiveData(SPIx);
	return Data_Revice;
}
void Receiver_Data_Master(SPI_TypeDef *SPIx, uint16_t *My_Data){
	SPI2->DR &= 0xff;
	Delay(10);
	*My_Data = SPI_I2S_ReceiveData(SPIx);
	while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET);
}
void Led_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

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
uint8_t GPIO_Read_Pin(GPIO_TypeDef *pGPIO, uint32_t GPIO_PIN){
	uint32_t Read_Pin;

	// Read but un IDR Registers
	Read_Pin = (pGPIO->IDR) >> GPIO_PIN;
	Read_Pin = Read_Pin & 0x01;
	return Read_Pin;
}

int main(){
	SystemCoreClockUpdate();
	Button_Init();
	Led_Init();
	SPI2_MasterConfig();
	SPI1_SlaveConfig();
	uint32_t returncode = SysTick_Config(SystemCoreClock/1000);
	if(returncode != 0)
	{
		DEBUG_BREAK;
	}
	while(1){
		if(GPIO_Read_Pin(GPIOC, PIN_BUTTON) == GPIO_PIN_LOW){
			Send_Data(SPI2, 0xB1);
		}
	//Receive_Data = Receiver_Data_Slave(SPI1);
		if(Receive_Data == Check_DataSlave){
			for(int i = 0; i < 5; i++){
				GPIO_PinControl(GPIOA, PIN_LED, GPIO_PIN_SET);
				Delay(200);
				GPIO_PinControl(GPIOA, PIN_LED, GPIO_PIN_RESET);
				Delay(200);
			}
			Receive_Data = 0;
		}
		GPIO_PinControl(GPIOA, PIN_LED, GPIO_PIN_RESET);
	}
	// Lab4_2
//	while(1){
//		if(GPIO_Read_Pin(GPIOC, PIN_BUTTON) == GPIO_PIN_LOW){
//			Send_Data(SPI2, 0xB1);
//		}
//		if(Receive_Data == Check_DataSlave){
//			for(int i = 0; i < 5; i++){
//				GPIO_PinControl(GPIOA,PIN_LED, GPIO_PIN_SET);
//				Delay(1000);
//				GPIO_PinControl(GPIOA,PIN_LED, GPIO_PIN_RESET);
//				Delay(1000);
//			}
//			Receive_Data_Slave = 0;
//			Send_Data(SPI1, 0x43);
//			Receiver_Data_Master(SPI2, &Receive_Data_Master);
//			if(Receive_Data_Master == 0x43){
//				GPIO_PinControl(GPIOA, PIN_LED, GPIO_PIN_SET);
//				Receive_Data_Master = 0;
//			}
//		}
//	}
	return 0;
}
void SysTick_Handler(void)
{
	/* Increment counter necessary in Delay()*/
	msTicks++;
}
void SPI1_IRQHandler(void){
	if(SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_RXNE)== SET)
	{
		Receive_Data = Receiver_Data_Slave(SPI1);
		SPI_I2S_ClearITPendingBit(SPI1, SPI_I2S_IT_RXNE);
	}
}


