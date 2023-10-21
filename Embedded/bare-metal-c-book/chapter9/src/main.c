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
			
char hello[] = "Hello World\n";
int current_char;

void uart2_Init(void) {
	UART_HandleTypeDef uart_handle;
	uart_handle.Instance = USART2;
	uart_handle.Init.BaudRate = 9600;
	uart_handle.Init.WordLength = UART_WORDLENGTH_8B;
	uart_handle.Init.StopBits = UART_STOPBITS_1;
	uart_handle.Init.Parity = UART_PARITY_NONE;
	uart_handle.Init.Mode = UART_MODE_TX_RX;
	uart_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;

	uart_handle.Init.OverSampling = UART_OVERSAMPLING_16;
	uart_handle.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	uart_handle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

	if (HAL_UART_Init(&uart_handle) != HAL_OK) {
		ErrorHandler();
	}
}

void myPutChar(const char c) {

}

int main(void)
{
	HAL_Init();
	led2_Init();
	uart2_Init();

	for (;;) {
		for(current_char = 0;hello[current_char] != '\0'; ++current_char) {
			myPutChar(hello[current_char]);
		}
		HAL_Delay(500);
	}
}
