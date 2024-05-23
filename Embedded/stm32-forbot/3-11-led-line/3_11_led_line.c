#define STM32F0 1

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#define LEDS_PORT GPIOA
#define LED GPIO5

#define BUTTON_PORT GPIOB
#define BUTTON GPIO10

static void gpioSetup(void)
{
    // Enable clock for LEDS_PORT
    rcc_periph_clock_enable(RCC_GPIOA);
    // Set leds as output
    for (int i = 0; i < 3; ++i)
    {
        gpio_mode_setup(LEDS_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED << i);
    }
}

static void buttonSetup(void)
{
    rcc_periph_clock_enable(RCC_GPIOB);
    gpio_mode_setup(BUTTON_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, BUTTON);
}

int main(void)
{
    gpioSetup();
    buttonSetup();
    while (true)
    {
        for (int i = 0; i < 3; ++i)
        {
            if (gpio_get(BUTTON_PORT, BUTTON) == BUTTON)
            {
                for (int j = 0; j < 3; ++j)
                {
                    gpio_set(LEDS_PORT, LED << j);
                }
                continue;
            }

            gpio_toggle(LEDS_PORT, LED << i);
            for (int j = 0; j < 100000; ++j)
            {
                __asm__("nop");
            }
        }
    }
    return 0;
}