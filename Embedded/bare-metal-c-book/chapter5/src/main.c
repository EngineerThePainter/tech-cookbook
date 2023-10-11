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
			

int main(void)
{
	GPIO_InitTypeDef GPIO_LedInit; // Init. for the LED
	GPIO_InitTypeDef GPIO_ButtonInit;  // Init. for push button
	GPIO_PinState result; // The result of reading the pin

	HAL_Init();

	// LED clock initialization
	LED2_GPIO_CLK_ENABLE();

	// Initialize LED.
	GPIO_LedInit.Pin = LED2_PIN;
	GPIO_LedInit.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_LedInit.Pull = GPIO_PULLUP;
	GPIO_LedInit.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED2_GPIO_PORT, &GPIO_LedInit);

	// Push button clock initialization
	USER_BUTTON_GPIO_CLK_ENABLE();

	/* Configure GPIO pin : For button */
	GPIO_ButtonInit.Pin = USER_BUTTON_PIN;
	GPIO_ButtonInit.Mode = GPIO_MODE_INPUT;
	GPIO_ButtonInit.Pull = GPIO_PULLDOWN;
	GPIO_ButtonInit.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(USER_BUTTON_GPIO_PORT, &GPIO_ButtonInit);

	for(;;) {
		// Get the current state of the push button
	    result = HAL_GPIO_ReadPin(USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN);
	    if (result == GPIO_PIN_SET) {
            HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_PIN, GPIO_PIN_SET);
	    } else {
            HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_PIN,GPIO_PIN_RESET);
	    }
	}
}
