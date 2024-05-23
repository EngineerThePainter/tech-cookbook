// Green - PC3 SPI2_MOSI
// Orange - PB13 SPI2_SCK
// Yellow - PB12 SPI2_NSS / CS
// Blue - DC - PB11
// Brown - RST - PB2

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>

static void setupClock(void)
{
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOC);
}

int main(void)
{
    setupClock();

    gpio_mode_setup(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO3); // SPI2_MOSI
    gpio_set_af(GPIOC, GPIO_AF1, GPIO3);                         // SPI2_MOSI

    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO13); // SPI2_SCK
    gpio_set_af(GPIOB, GPIO_AF0, GPIO13);                         // SPI2_SCK

    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO12); // SPI2_NSS
    gpio_set_af(GPIOB, GPIO_AF0, GPIO12);                         // SPI2_NSS

    spi_enable(SPI2);
    // spi_init_master(SPI2, SPI_CR1_BAUDRATE_FPCLK_DIV_8,)
    return 0;
}