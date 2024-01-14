#define STM32F0 1

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#define LED_PORT GPIOC
#define LED_PIN GPIO8

static void gpioSetup(void)
{
    rcc_periph_clock_enable(RCC_GPIOC);
    gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);
}

int main(void)
{
    gpioSetup();
    while (1)
    {
        gpio_toggle(LED_PORT, LED_PIN);
        for (int i = 0; i < 1000000; ++i)
        {
            __asm__("nop");
        }
    }
    return 0;
}