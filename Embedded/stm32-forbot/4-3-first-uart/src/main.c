#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

void setup_led(void);

void setup_led(void)
{
    rcc_periph_clock_enable(RCC_GPIOA);
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);
}

int main(void)
{
    setup_led();
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
    while (1)
    {
        usart_send(USART2, 'A');
        gpio_toggle(GPIOA, GPIO5);
        for (int i = 0; i < 1000000; i++)
        {
            __asm__("nop");
        }
    }
    return 0;
}