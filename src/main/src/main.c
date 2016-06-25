
#include "arch_main.h"
#include "tasks.h"
#include "spi.h"
#include "spi_flash.h"
#define SPI_GPIO_PORT  GPIO_PORT_0 
#define SPI_CLK_PIN    GPIO_PIN_0
#define SPI_CS_PIN     GPIO_PIN_3
#define SPI_DI_PIN     GPIO_PIN_5
#define SPI_DO_PIN     GPIO_PIN_6
#define SPI_FLASH_SIZE 262144              // SPI Flash memory size in bytes
#define SPI_FLASH_PAGE 256
OS_STK init_stack[MaxStkSize];
static void spi_flash_peripheral_init()
{
		int8_t detected_spi_flash_device_index;
		SPI_Pad_t spi_FLASH_CS_Pad;
    spi_FLASH_CS_Pad.pin = SPI_CS_PIN;
    spi_FLASH_CS_Pad.port = SPI_GPIO_PORT;
    // Enable SPI & SPI FLASH

    spi_init(&spi_FLASH_CS_Pad, SPI_MODE_8BIT, SPI_ROLE_MASTER, SPI_CLK_IDLE_POL_LOW, SPI_PHA_MODE_0, SPI_MINT_DISABLE, SPI_XTAL_DIV_8);

    detected_spi_flash_device_index = spi_flash_auto_detect();

    if(detected_spi_flash_device_index == SPI_FLASH_AUTO_DETECT_NOT_DETECTED)
    {
        // The device was not identified.
        // The default parameters are used (SPI_FLASH_SIZE, SPI_FLASH_PAGE)
        // Alternatively, an error can be asserted here.
        spi_flash_init(SPI_FLASH_SIZE, SPI_FLASH_PAGE);
    }
}

void flash_init()
{unsigned int jedec_id;
	spi_flash_peripheral_init();
	spi_cs_low();
  spi_cs_high();
	jedec_id = spi_read_flash_jedec_id();
}
void main_func(void)
{
    //global initialise
  system_init();
	flash_init();
	OSInit();
	OSTaskCreate(init_task, NULL, &init_stack[MaxStkSize - 1], INIT_TASK_PRIO);
	OSStart();
}
