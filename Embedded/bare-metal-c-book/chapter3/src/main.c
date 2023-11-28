/**
  ******************************************************************************
  * @file    main.c
  * @author  WernherVonData
  * @version V1.0
  * @date    05-October-2023
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f0xx.h"
#include "stm32f0xx_nucleo.h"

#include <stdbool.h>

int main(void)
{
	bool shorter_delay=true;
	// Initializes the hardware, e.g. system clock
	HAL_Init();
	// Initialize the LED2 clock
	LED2_GPIO_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = LED2_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStruct);
	for(;;) {
		// Toggle LED2
		HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
		HAL_Delay(shorter_delay ? 300 : 900);
		shorter_delay = !shorter_delay;
	}
}
