#include<stdint.h>

#define RCC_BASE_ADDR		0x40023800UL
#define RCC_CFGR_REG_OFFSET	0x08UL
#define RCC_CFGR_REG_ADDR	(RCC_BASE_ADDR + RCC_CFGR_REG_OFFSET)
#define RCC_CR_REG_OFFSET	0x00UL
#define RCC_CR_REG_ADDR		(RCC_BASE_ADDR + RCC_CR_REG_OFFSET)
#define GPIOA_BASE_ADDR		0x40020000UL

int main()
{
	uint32_t *pRCCCfgrAddr = (uint32_t*) RCC_CFGR_REG_ADDR;
	uint32_t *pRCCCrAddr  = (uint32_t*) RCC_CR_REG_ADDR;
	// Set bit on HSEON
	*pRCCCrAddr |=(1 << 16);
	// HSERDY On
	while(!(*pRCCCrAddr & (1 << 17)));
	// Set prescaler = 4
	*pRCCCfgrAddr &=(0x7 << 24);
	*pRCCCfgrAddr |=(0x3 << 25);
	// Set IO port A clock enable
	uint32_t * pRCCAhb1Enr = (uint32_t*) (RCC_BASE_ADDR + 0x30);
	*pRCCAhb1Enr |= (1<<0);
	// Set Alternatee fuction mode GPIOA
	uint32_t *pGPIOAModeReg = (uint32_t*)(GPIOA_BASE_ADDR);
	*pGPIOAModeReg &= ~(0x3 << 16);
	*pGPIOAModeReg |= (0x2 << 16);
	// Set Alternate function mode for PA8
	uint32_t *pGPIOAAltFunHighReg  = (uint32_t*)(GPIOA_BASE_ADDR + 0x24);
	*pGPIOAAltFunHighReg &= ~(0x0f << 0);
	return 0;
}
