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

void spi_transfer(uint8_t *tx, uint16_t len)
{
    for (uint16_t i = 0; i < len; ++i)
    {
        SPI_CS_LOW;
        while (!(SPI2_SR & SPI_SR_TXE))
        {
            spi_send(SPI2, tx[i]);
        }
        SPI_CS_HIGH;
    }
}

int main(void)
{
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_SPI2);

    gpio_mode_setup(SPI_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, SPI_SCK | SPI_SI | SPI_SO);
    gpio_set_af(SPI_PORT, GPIO_AF0, SPI_SCK | SPI_SI | SPI_SO);

    gpio_mode_setup(SPI_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, SPI_CS);
    SPI_CS_HIGH;

    spi_init_master(
        SPI_PORT,                        // SPI port
        SPI_CR1_BAUDRATE_FPCLK_DIV_256,  // Baud rate
        SPI_CR1_CPOL_CLK_TO_1_WHEN_IDLE, // Clock polarity
        SPI_CR1_CPHA_CLK_TRANSITION_1,   // Clock phase
        SPI_CR1_MSBFIRST                 // Most significant bit first
    );
    spi_enable(SPI2);
    uint8_t gpio_config[3] = {WRITE, MCP_IODIR, 0xFF};

    while (true)
    {
        uint8_t turn_gpio0[3] = {WRITE, MCP_OLAT, 0x01};
        spi_transfer(turn_gpio0, 3);
    }

    return 0;
}