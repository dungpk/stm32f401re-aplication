/**
  ******************************************************************************
  * @file    GPIO/IOToggle/main.c
  * @author  MCD Application Team
  * @version V3.6.0
  * @date    20-September-2021
  * @brief   Main program body.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2011 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
//#include "stm32_eval.h"
#define USE_FULL_ASSERT

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured,
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */

  /* GPIOD Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

  /* Configure PD0 and PD2 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* To achieve GPIO toggling maximum frequency, the following  sequence is mandatory.
     You can monitor PD0 or PD2 on the scope to measure the output signal.
     If you need to fine tune this frequency, you can add more GPIO set/reset
     cycles to minimize more the infinite loop timing.
     This code needs to be compiled with high speed optimization option.  */
  while (1)
  {
    /* Set PD0 and PD2 */
    GPIOD->BSRR = 0x00000005;
    /* Reset PD0 and PD2 */
    GPIOD->BRR  = 0x00000005;

    /* Set PD0 and PD2 */
    GPIOD->BSRR = 0x00000005;
    /* Reset PD0 and PD2 */
    GPIOD->BRR  = 0x00000005;

    /* Set PD0 and PD2 */
    GPIOD->BSRR = 0x00000005;
    /* Reset PD0 and PD2 */
    GPIOD->BRR  = 0x00000005;

    /* Set PD0 and PD2 */
    GPIOD->BSRR = 0x00000005;
    /* Reset PD0 and PD2 */
    GPIOD->BRR  = 0x00000005;

    /* Set PD0 and PD2 */
    GPIOD->BSRR = 0x00000005;
    /* Reset PD0 and PD2 */
    GPIOD->BRR  = 0x00000005;

    /* Set PD0 and PD2 */
    GPIOD->BSRR = 0x00000005;
    /* Reset PD0 and PD2 */
    GPIOD->BRR  = 0x00000005;

    /* Set PD0 and PD2 */
    GPIOD->BSRR = 0x00000005;
    /* Reset PD0 and PD2 */
    GPIOD->BRR  = 0x00000005;

    /* Set PD0 and PD2 */
    GPIOD->BSRR = 0x00000005;
    /* Reset PD0 and PD2 */
    GPIOD->BRR  = 0x00000005;

    /* Set PD0 and PD2 */
    GPIOD->BSRR = 0x00000005;
    /* Reset PD0 and PD2 */
    GPIOD->BRR  = 0x00000005;

    /* Set PD0 and PD2 */
    GPIOD->BSRR = 0x00000005;
    /* Reset PD0 and PD2 */
    GPIOD->BRR  = 0x00000005;
  }
}

