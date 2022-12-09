#include <stdio.h>
#include "temhumsensor.h"
#include "Ucglib.h"
#include "timer.h"
#include <string.h>
#include "stm32f401re.h"
#include "stm32f401re_rcc.h"
#include "stm32f401re_gpio.h"
#include "stm32f401re_spi.h"
#include "stm32f401re_i2c.h"
#include "kalman_filter.h"
#define SPI1_CS_PORT			GPIOB
#define SPI1_CS_PIN				GPIO_Pin_6
#define SPI1_RST_PORT			GPIOC
#define SPI1_RST_PIN			GPIO_Pin_7
#define SPI1_MOSI_PORT			GPIOA
#define SPI1_MOSI_PIN			GPIO_Pin_7
#define SPI1_SCK_PORT			GPIOA
#define SPI1_SCK_PIN			GPIO_Pin_5
#define SPI1_RS_PORT			GPIOA
#define SPI1_RS_PIN				GPIO_Pin_9
#define SPI1_ENABLE_PORT		GPIOB
#define SPI1_ENABLE_PIN			GPIO_Pin_10
#define SPI1_MODE_PORT			GPIOA
#define SPI1_MODE_PIN			GPIO_Pin_8

#define I2Cx_RCC				RCC_APB1Periph_I2C1
#define I2Cx_SENSOR				I2C1
#define I2C_GPIO_RCC		    RCC_AHB1Periph_GPIOB
#define I2C_GPIO				GPIOB
#define I2C_PIN_SDA				GPIO_Pin_9
#define I2C_PIN_SCL				GPIO_Pin_8

#define RECEIVER				0x01
#define TRANSMIT				0x00

#define CMDR_MEASURE_TEMP_VALUE                   0xE3
#define CMDR_MEASURE_HUMI_VALUE                   0xE5
#define CMDR_MEASURE_TEMP_FROM_HUMI_PREV		  0xE0
#define SI7020_ADDR                         	  0x40


static ucg_t ucg;
uint32_t dwTimer_Init = 0, dwTimer_Current = 0;
/******************************************************************************
* @func					SPI1_Init
* @brief					This func Init SPI1 mode master
* @param					none
* @return					none
* @Note					none
*/
void SPI1_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	// Enable clock for GPIOA - GPIOB - GPIOC
	/* GPIOA, GPIOB and GPIOC Clocks enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_InitStructure.GPIO_Pin = SPI1_SCK_PIN | SPI1_MOSI_PIN | SPI1_RS_PIN | SPI1_MODE_PIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SPI1_CS_PIN | SPI1_ENABLE_PIN;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SPI1_RST_PIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	 //enable peripheral clock SPI1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

	// set to hafl deplex mode, seperate MOSI Lines
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;

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

	// data is trasmitted MSB first
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;

	SPI_Init(SPI1, &SPI_InitStructure);

	// Enable SPI1
	SPI_Cmd(SPI1, ENABLE);
}
/******************************************************************************
* @func					I2C1_Init
* @brief					This func Init I2C1_Init mode master
* @param					none
* @return					none
* @Note					none
*/
void I2C1_Init(void){
	I2C_InitTypeDef  I2C_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_APB1PeriphClockCmd(I2Cx_RCC, ENABLE);
	RCC_AHB1PeriphClockCmd(I2C_GPIO_RCC, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_InitStruct.GPIO_Pin = I2C_PIN_SCL | I2C_PIN_SDA;
	GPIO_Init(I2C_GPIO, &GPIO_InitStruct);

	// Connect PA8 to I2C1 SCL
	GPIO_PinAFConfig(I2C_GPIO, GPIO_PinSource8, GPIO_AF_I2C1);

	// Connect PC9 to I2C1 SDA
	GPIO_PinAFConfig(I2C_GPIO, GPIO_PinSource9, GPIO_AF_I2C1);

	I2C_InitStruct.I2C_ClockSpeed = 400000;
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

	I2C_Init(I2Cx_SENSOR, &I2C_InitStruct);
	I2C_Cmd(I2Cx_SENSOR, ENABLE);
}
/******************************************************************************
* @func					I2C_Start
* @brief					This func transmit bit start
* @param					none
* @return					none
* @Note					none
*/
static
void I2C_Start(void)
{
	// wait untill i2Cx is not busy anymore
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

	// Generate start condition
	I2C_GenerateSTART(I2Cx_SENSOR, ENABLE);

	// wait for I2C EV5.
	// It means that the start conditionhas been correctly released
	// on the I2C bus (the bus is free, no other devoces is communicating
	while(!I2C_CheckEvent(I2Cx_SENSOR, I2C_EVENT_MASTER_MODE_SELECT));
}
/******************************************************************************
* @func					I2C_SendAddress
* @brief					This func transmit address and mode select
* @param					uint8_t address, uint8_t mode_select
* @return					none
* @Note					none
*/
static
void I2C_SendAddress(uint8_t address, uint8_t mode_select){
	//I2C_Send7bitAddress(I2C1, address, mode_select);
	if(mode_select == RECEIVER){
		I2C_Send7bitAddress(I2C1, address, I2C_Direction_Receiver);
		while(!I2C_CheckEvent(I2C1,  I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	}else if(mode_select == TRANSMIT){
		I2C_Send7bitAddress(I2C1, address, I2C_Direction_Transmitter);
		while(!I2C_CheckEvent(I2C1,  I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	}
}
/******************************************************************************
* @func					I2C_Transmit
* @brief					This func transmit byte(address) data
* @param					uint8_t byte
* @return					none
* @Note					none
*/
static
void I2C_Transmit(uint8_t byte){
	// Send data byte
	I2C_SendData(I2Cx_SENSOR, byte);
	// wait for I2C Ev8_2
	// It means that the data has been physically shfted out and out put the bus
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_SLAVE_BYTE_TRANSMITTED));
}
/******************************************************************************
* @func					I2C_Stop
* @brief					This func transmit bit stop
* @param					none
* @return					none
* @Note					none
*/

void I2C_Stop(void){
	// generate I2C stop condition
	I2C_GenerateSTOP(I2C1, ENABLE);
}
/******************************************************************************
* @func					I2C_Receive_ACK
* @brief					This func receiver wwith bit ACK
* @param					none
* @return					none
* @Note					none
*/
uint8_t I2C_Receive_ACK(void){
	I2C_AcknowledgeConfig(I2Cx_SENSOR, ENABLE);
	while(!I2C_CheckEvent(I2Cx_SENSOR, I2C_EVENT_MASTER_BYTE_RECEIVED));
	return I2C_ReceiveData(I2Cx_SENSOR);
}
/******************************************************************************
* @func					I2C_Receive_NACK
* @brief					This func receiver wwith bit NACK
* @param					none
* @return					none
* @Note					none
*/
uint8_t I2C_Receive_NACK(void){
	// Disable ACK of received data
	I2C_AcknowledgeConfig(I2Cx_SENSOR, DISABLE);
	while(!I2C_CheckEvent(I2Cx_SENSOR, I2C_EVENT_MASTER_BYTE_RECEIVED));
	return I2C_ReceiveData(I2Cx_SENSOR);
}
void Delay_ms(uint32_t milliseconds){
	for(int i = 0; i < milliseconds; i++){
		for(int j = 0; j < 5000; j++);
	}
}
/******************************************************************************
* @func					TemHumSensor_readRegister
* @brief					This func read data from register
* @param					uint8_t address // address register data
* 							uint8_t address_sensor// address sensor(0x400
* 							uint8_t time_delay
* @return					none
* @Note					none
*/
uint16_t TemHumSensor_readRegister(uint8_t Address_cmd, uint8_t Address_sensor, uint32_t time_delay){
	uint16_t data = 0;
	I2C_Start();
	I2C_SendAddress(Address_sensor<<1, TRANSMIT);
	I2C_Transmit(Address_cmd);	//Command ID -> Read temperature or humidity
	Delay_ms(time_delay);
	I2C_Stop();
	I2C_Start();
	I2C_SendAddress(Address_sensor<<1, RECEIVER);
	data = I2C_Receive_ACK();
	data = (data << 8) + I2C_Receive_NACK();
	I2C_Stop();
	return data;
}
float TemHumSensor_GetTempValue(void){
	uint16_t data = TemHumSensor_readRegister(CMDR_MEASURE_TEMP_VALUE, SI7020_ADDR, 100);
	float temp_value = ((float)(175.72 * data) / 65536) - 46.85;
	return temp_value;
}
float TemHumSensor_GetHumiValue(void){
	uint16_t data = TemHumSensor_readRegister(CMDR_MEASURE_HUMI_VALUE, SI7020_ADDR, 100);
	float humi_value = ((float)(125 * data) / 65536) - 6;
	return humi_value;
}
void Display_TemHum(void){
	static char strtemp[20] = "";
	static char strhumi[20] = "";
	static char src1[20] = "";
	static char src2[20] = "";
	memset(strhumi, 0, sizeof(strhumi));
	memset(strtemp, 0, sizeof(strtemp));
	memset(src1, 0 , sizeof(src1));
	memset(src1, 0 , sizeof(src2));
	float temp = TemHumSensor_GetTempValue();
	uint8_t temp_v = (uint8_t)KalmanFilter_updateEstimate(temp);
	uint8_t humi_v = (uint8_t)TemHumSensor_GetHumiValue();
	uint8_t temperature = (uint8_t)(TemHumSensor_GetTemp() / 100);
	uint8_t humidity = (uint8_t)(TemHumSensor_GetHumi() / 100);
	sprintf(strtemp, "Temp_v = %d oC", temp_v);
	sprintf(strhumi, "Humi_v = %d %% ", humi_v);
	sprintf(src1, "Temp = %d oC", temperature);
	sprintf(src2, "Humi = %d %%", humidity);
	ucg_DrawString(&ucg, 0, 32, 0, src1);
	ucg_DrawString(&ucg, 0, 52, 0, src2);
	ucg_DrawString(&ucg, 0, 72, 0, strtemp);
	ucg_DrawString(&ucg, 0, 92, 0, strhumi);
}
// Kalman filter for temperature
void Kalman_filter(void){
	float temp = TemHumSensor_GetTempValue();
	temp = KalmanFilter_updateEstimate(temp);

}
// Function process
void processGetValueSensor(void){
	dwTimer_Current = GetMilSecTick();
	if(dwTimer_Current - dwTimer_Init >= 5000){
		Display_TemHum();
		dwTimer_Init = dwTimer_Current;
	}
	if((dwTimer_Current - dwTimer_Init) % 1000 == 0 && dwTimer_Current - dwTimer_Init < 5000)
	{
		Kalman_filter();
	}
}

int main(void){
	SystemCoreClockUpdate();
	I2C1_Init();
	TimerInit();
	TemHumSensor_Init();
	Ucglib4WireSWSPI_begin(&ucg, UCG_FONT_MODE_SOLID);
	SPI1_Init();

	ucg_ClearScreen(&ucg);
	ucg_SetFont(&ucg, ucg_font_ncenR12_hr);
	ucg_SetColor(&ucg, 0, 255, 255, 255);
	ucg_SetColor(&ucg, 1, 0, 0, 0);
	ucg_SetRotate180(&ucg);
	KalmanFilterInit(1, 1, 1);
	dwTimer_Init = GetMilSecTick();
	while(1){
		processTimerScheduler();
		processGetValueSensor();
	}
	return 0;
}



