#define STM32F0 1

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>

// PB13 - red - SCK
// PB12 - green - CS
// PB14 - purple - SO
// PB15 - black - SI

#define SPI_PORT GPIOB
#define SPI_SCK GPIO13
#define SPI_CS GPIO12
#define SPI_SO GPIO14
#define SPI_SI GPIO15

#define SPI_CS_LOW gpio_clear(SPI_PORT, SPI_CS)
#define SPI_CS_HIGH gpio_set(SPI_PORT, SPI_CS)

// Register addresses of MCP23S08
#define MCP_IODIR 0x00
#define MCP_IPOL 0x01
#define MCP_GPINTEN 0x02
#define MCP_DEFVAL 0x03
#define MCP_INTCON 0x04
#define MCP_IOCON 0x04
#define MCP_GPPU 0x05
#define MCP_INTF 0x06
#define MCP_INTCAP 0x07
#define MCP_GPIO 0x08
#define MCP_OLAT 0x0A

#define WRITE 0x40
#define READ 0x41

void sendData(uint8_t *data, int n);

int main(void)
{
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_SPI2);

    gpio_mode_setup(SPI_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, SPI_SCK | SPI_SO | SPI_SI);
    gpio_set_af(SPI_PORT, GPIO_AF0, SPI_SCK | SPI_SO | SPI_SI);

    gpio_mode_setup(SPI_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, SPI_CS);
    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO8);

    gpio_set(SPI_PORT, SPI_CS);
    gpio_set(GPIOB, GPIO8);
    spi_reset(SPI2);

    spi_init_master(
        SPI2,
        SPI_CR1_BAUDRATE_FPCLK_DIV_32,
        SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE,
        SPI_CR1_CPHA_CLK_TRANSITION_1,
        SPI_CR1_MSBFIRST);

    spi_enable_software_slave_management(SPI2);
    spi_enable_ss_output(SPI2);
    spi_set_nss_high(SPI2);
    spi_set_unidirectional_mode(SPI2);
    // spi_set_data_size(SPI2, SPI_CR2_DS_8BIT);
    spi_enable(SPI2);

    uint8_t init_data[3] = {WRITE, MCP_IODIR, 0xFC};
    sendData(init_data, 3);
    uint8_t current_value = 0;
    while (true)
    {
        uint8_t data[3] = {WRITE, MCP_OLAT, current_value};
        gpio_clear(GPIOB, GPIO8);
        for (int i = 0; i < 1000000; ++i)
        {
            __asm("nop");
        }
        sendData(data, 3);
        gpio_set(GPIOB, GPIO8);
        for (int i = 0; i < 1000000; ++i)
        {
            __asm("nop");
        }
        current_value = current_value == 3 ? 0 : current_value + 1;
    }
    return 0;
}

void sendData(uint8_t *data, int n)
{
    gpio_clear(SPI_PORT, SPI_CS);
    for (int i = 0; i < n; ++i)
    {
        spi_send8(SPI2, data[i]);
    }
    while (SPI_SR(SPI2) & SPI_SR_BSY)
        ;
    gpio_set(SPI_PORT, SPI_CS);
}