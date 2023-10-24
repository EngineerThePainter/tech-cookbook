/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#define XON 0x11
#define XOFF 0x13

#include <stdbool.h>
#include "stm32f0xx.h"
#include "stm32f0xx_nucleo.h"
			
char hello[] = "Hello World\r\n";
int current_char;
uint8_t read_value;

/*
 * @brief this function is called in case of error
 *
 * Blinks led
 * */
void ErrorHandler(void) {
	HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_PIN, GPIO_PIN_SET);
	while(true) {
		HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
		HAL_Delay(1000);
	}
}

UART_HandleTypeDef uart_handle;

void myPutChar(const char ch) {
	/* Reads and saves the value of UART_FLAG_TXE at call time.
	 * ISR is a interrupt and status register electrically connected on the board
	 * When it's zero it means we can send another character to the TDR.
	 * TDR is "Transmit Data Register" and just sends anything that it receives.
	 * */
	int result __attribute__((unused)) = (uart_handle.Instance-> ISR | UART_FLAG_TXE);

	// Block until the transmit empty (TXE) flag is set
	while ((uart_handle.Instance->ISR & UART_FLAG_TXE) == 0) {
		continue;
	}
	// Send character to UART
	uart_handle.Instance->TDR = ch;
}

void led2_Init(void) {
	LED2_GPIO_CLK_ENABLE();
	GPIO_InitTypeDef led_init;
	led_init.Pin = LED2_PIN;
	led_init.Mode = GPIO_MODE_OUTPUT_PP;
	led_init.Pull = GPIO_PULLUP;
	led_init.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED2_GPIO_PORT, &led_init);
}

void uart2_Init(void) {
	// Which UART on the board should be used
	uart_handle.Instance = USART2;
	// Number of bits per second
	uart_handle.Init.BaudRate = 9600;
	// The length of the word
	uart_handle.Init.WordLength = UART_WORDLENGTH_8B;
	// the number of time in bits between words
	uart_handle.Init.StopBits = UART_STOPBITS_1;
	// Parity for simple error checking
	uart_handle.Init.Parity = UART_PARITY_NONE;
	// Enable transmitter and receiver
	uart_handle.Init.Mode = UART_MODE_TX_RX;
	// No uart hardware control flow on my board
	uart_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;

	uart_handle.Init.OverSampling = UART_OVERSAMPLING_16;
	uart_handle.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	uart_handle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

	if (HAL_UART_Init(&uart_handle) != HAL_OK) {
		ErrorHandler();
	}
}

int main(void)
{
	HAL_Init();
	led2_Init();
	uart2_Init();

	for (;;) {
		for(current_char = 0;hello[current_char] != '\0'; ++current_char) {
			while (read_value == XOFF) {
				HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
				HAL_Delay(500);
				HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
				HAL_UART_Receive(&uart_handle, &read_value, 1, 100);
				if (read_value == XON) {
					break;
				}
			}

			myPutChar(hello[current_char]);

			HAL_UART_Receive(&uart_handle, &read_value, 1, 100);
		}
	}
}

/**
 * Magic function that's called by the HAL layer to actually
 * initialize the UART. In this case we need to
 * put the UART pins in alternate mode so they act as
 * UART pins and not like GPIO pins.
 *
 * @note: Only works for UART2, the one connected to the USB serial
 * converter
 *
 * @param uart The UART information
 */
void HAL_UART_MspInit(UART_HandleTypeDef* uart)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    if(uart->Instance == USART2)
    {
        /* Peripheral clock enable */
        __HAL_RCC_USART2_CLK_ENABLE();

        /*
         * USART2 GPIO Configuration
         * PA2     ------> USART2_TX
         * PA3     ------> USART2_RX
         */
        GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        // Alternate function -- that of UART
        GPIO_InitStruct.Alternate = GPIO_AF1_USART2;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }

}

/**
 * Magic function called by HAL layer to de-initialize the
 * UART hardware. It's something we never do, but we put it
 * in here for the sake of completeness.
 *
 * @note: Only works for UART2, the one connected to the USB serial
 * converter
 *
 * @param uart The UART information
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef* uart)
{
    if(uart->Instance == USART2)
    {
        /* Peripheral clock disable */
        __HAL_RCC_USART2_CLK_DISABLE();

        /*
         * USART2 GPIO Configuration
         * PA2     ------> USART2_TX
         * PA3     ------> USART2_RX
         */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);
    }
}
