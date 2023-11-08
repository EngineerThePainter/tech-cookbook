
#include <stdbool.h>
#include "stm32f0xx.h"
#include "stm32f0xx_nucleo.h"
			
const char hello[] = "Hello World! Master of disaster\r\n";
const char hello2[] = "Master of disaster! World Hello!\r\n";

bool switchMessage = false;

UART_HandleTypeDef uartHandle;

#define BUFFER_SIZE 8

struct CircularBuffer {
	// Where the next character will be
	uint32_t putIndex;
	// Where to get next character
	uint32_t getIndex;
	// Number of characters in the buffer
	uint32_t nCharacters;
	char data[BUFFER_SIZE];
};

volatile struct CircularBuffer buffer = {0,0,0,{'\0'}};

struct LogEvent {
	uint32_t line;
	uint32_t putIndex;
	uint32_t getIndex;
	uint32_t nCharacters;
};

#define N_EVENTS 100
uint32_t nextEvent = 0;
struct LogEvent debugEvents[N_EVENTS];

void debugEvent(const uint32_t line) {
	debugEvents[nextEvent].line = line;
	debugEvents[nextEvent].putIndex = buffer.putIndex;
	debugEvents[nextEvent].getIndex = buffer.getIndex;
	debugEvents[nextEvent].nCharacters = buffer.nCharacters;
	++nextEvent;
	if (nextEvent == N_EVENTS) {
		nextEvent = 0;
	}
}

void ErrorHandler(void) {
	HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_PIN, GPIO_PIN_SET);
	while(true) {
		HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
		HAL_Delay(1000);
	}
}

void USART2_IRQHandler(void) {
	if ((uartHandle.Instance->ISR & USART_ISR_TXE) != 0) {
		if (buffer.nCharacters == 0) {
			// Turn off interrupt
			uartHandle.Instance->CR1 &= ~(USART_CR1_TXEIE);
			return;
		}
		// Send to UART
		uartHandle.Instance->TDR = buffer.data[buffer.getIndex];
		++buffer.getIndex;
		if (buffer.getIndex == BUFFER_SIZE) {
			buffer.getIndex = 0;
		}
		debugEvent(__LINE__);
		--buffer.nCharacters;
		debugEvent(__LINE__);
		if (buffer.nCharacters == 0) {
			uartHandle.Instance->CR1 &= ~(USART_CR1_TXEIE);
			return;
		}
	}
}

void myPutChar(const char ch) {
	// Wait until there is room
	while(buffer.nCharacters == BUFFER_SIZE) {
		continue;
	}
	buffer.data[buffer.putIndex] = ch;
	++buffer.putIndex;
	if (buffer.putIndex == BUFFER_SIZE) {
		buffer.putIndex = 0;
	}
	debugEvent(__LINE__);
	__disable_irq();
	++buffer.nCharacters;
	__enable_irq();
	debugEvent(__LINE__);
	// Enable or re-enable the interrupt
	uartHandle.Instance->CR1 |= USART_CR1_TXEIE;
}

void myPuts(const char* str) {
	for (;*str != '\0'; ++str) {
		myPutChar(*str);
	}
}

void led2_Init(void) {
	LED2_GPIO_CLK_ENABLE();
	GPIO_InitTypeDef led_init;
	led_init.Pin = LED2_PIN;
	led_init.Mode = GPIO_MODE_IT_RISING;
	led_init.Pull = GPIO_NOPULL;
	led_init.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED2_GPIO_PORT, &led_init);
}

void uart2_Init(void) {
	// Which UART on the board should be used
	uartHandle.Instance = USART2;
	// Number of bits per second
	uartHandle.Init.BaudRate = 9600;
	// The length of the word
	uartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	// the number of time in bits between words
	uartHandle.Init.StopBits = UART_STOPBITS_1;
	// Parity for simple error checking
	uartHandle.Init.Parity = UART_PARITY_NONE;
	// Enable transmitter and receiver
	uartHandle.Init.Mode = UART_MODE_TX_RX;
	// No uart hardware control flow on my board
	uartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;

	uartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	uartHandle.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	uartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

	if (HAL_UART_Init(&uartHandle) != HAL_OK) {
		ErrorHandler();
	}
}

void buttonInit(void) {
	USER_BUTTON_GPIO_CLK_ENABLE();
	GPIO_InitTypeDef buttonInit;
	buttonInit.Pin = USER_BUTTON_PIN;
	buttonInit.Pull = GPIO_NOPULL;
	buttonInit.Mode = GPIO_MODE_IT_RISING;
	buttonInit.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(USER_BUTTON_GPIO_PORT, &buttonInit);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_PIN, GPIO_PIN_SET);
	for(int i = 0; i < 20; ++i) {
		HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
		HAL_Delay(200);
	}
}

void EXTI4_15_IRQHandler(void) {
	switchMessage = switchMessage ? false : true;
	__HAL_GPIO_EXTI_CLEAR_IT(USER_BUTTON_EXTI_LINE);
}

int main(void)
{
	HAL_Init();
	led2_Init();
	uart2_Init();
	buttonInit();
	// Enable interrupt vector for USART2
	NVIC_EnableIRQ(USART2_IRQn);

	HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);


	for(;;) {
		myPuts(switchMessage ? hello2 : hello);
		HAL_Delay(500);
	}
}

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

