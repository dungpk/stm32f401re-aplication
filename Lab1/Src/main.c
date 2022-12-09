#include <stdint.h>
#include "stm32"
#define RCC_BASE_ADDR		0x40023800UL
#define RCC_CFGR_REG_OFFSET	0x08UL
#define RCC_CFGR_REG_ADDR	(RCC_BASE_ADDR + RCC_CFGR_REG_OFFSET)
#define GPIOA_BASE_ADDR		0x40020000UL

int main()
{
	uint32_t *pRccCfgrReg = (uint32_t*)RCC_CFGR_REG_ADDR;
	*pRccCfgrReg &= ~(0x03 << 21); // Clear 21, 22 bit positions.
	// Set prescaler = 4(110)
	*pRccCfgrReg |= (1 << 25);
	*pRccCfgrReg |=(1 << 26);
	// Set enable clock for AHB1 bus
	uint32_t *pRCCAhb1Enr = (uint32_t*)(RCC_BASE_ADDR + 0x30);
	*pRCCAhb1Enr |= (1 << 0);
	uint32_t *pGPIOAModeReg = (uint32_t *)(GPIOA_BASE_ADDR);
	*pGPIOAModeReg &= ~(0x03 << 16);// clear bit 16,17 position
	*pGPIOAModeReg |=(0x02 << 16);// Set bit 16
	// Set alternation function for PA8
	uint32_t *pGPIOAAltFunHighReg  = (uint32_t*)(GPIOA_BASE_ADDR + 0x24);
	*pGPIOAAltFunHighReg &= ~(0x0f << 0);
	return 0;
}
