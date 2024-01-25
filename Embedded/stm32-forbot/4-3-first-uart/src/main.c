#include <string.h>

#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#define LED_PORT GPIOA
#define LED_PIN GPIO5

#define BUFFER 10

void setup_led(void);
void setup_uart(void);
void send_data(void);

void setup_led(void)
{
    rcc_periph_clock_enable(RCC_GPIOA);
    gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);
}

void setup_uart(void)
{
    // The pins for USART2 are PA2 (TX) and PA3 (RX).
    // These pins are connected to the ST-Link Virtual COM port.
    // Pins must be set to alternate function mode to use USART.
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);
    gpio_set_af(GPIOA, GPIO_AF1, GPIO2);
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO3);
    gpio_set_af(GPIOA, GPIO_AF1, GPIO3);

    rcc_periph_clock_enable(RCC_USART2);
    usart_set_mode(USART2, USART_MODE_TX_RX);
    usart_set_baudrate(USART2, 9600);
    usart_set_databits(USART2, 8);
    usart_set_parity(USART2, USART_PARITY_NONE);
    usart_set_stopbits(USART2, USART_CR2_STOPBITS_1);
    usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);
    usart_enable(USART2);
}

void send_data(void)
{
    char *data = "Hello!\r\n";
    for (int i = 0; i < BUFFER; i++)
    {
        if (data[i] == '\0')
        {
            break;
        }
        usart_send_blocking(USART2, data[i]);
    }
}

int main(void)
{
    setup_led();
    setup_uart();

    while (1)
    {
        send_data();
        gpio_toggle(LED_PORT, LED_PIN);
        for (int i = 0; i < 1000000; i++)
        {
            __asm__("nop");
        }
    }
    return 0;
}