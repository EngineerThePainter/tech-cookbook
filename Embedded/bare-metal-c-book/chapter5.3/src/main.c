/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f0xx.h"
#include "stm32f0xx_nucleo.h"

#define FREQUENCIES_SIZE 4

int main(void)
{
	HAL_Init();

	LED2_GPIO_CLK_ENABLE();
	GPIO_InitTypeDef gpio_led_init;
	gpio_led_init.Pin = LED2_PIN;
	gpio_led_init.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_led_init.Pull = GPIO_PULLUP;
	gpio_led_init.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED2_GPIO_PORT, &gpio_led_init);

	int frequencies[FREQUENCIES_SIZE] = {500, 1000, 1500, 2000};
	for(;;) {
		for (int i = 0; i < FREQUENCIES_SIZE; ++i) {
			HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
			HAL_Delay(frequencies[i]);
			HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
			HAL_Delay(100);
		}
	}
}
