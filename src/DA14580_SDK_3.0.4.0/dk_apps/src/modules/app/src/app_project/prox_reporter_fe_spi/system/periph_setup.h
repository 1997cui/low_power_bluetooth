/**
 ****************************************************************************************
 *
 * @file periph_setup.h
 *
 * @brief Peripherals setup header file. 
 *
 * Copyright (C) 2012. Dialog Semiconductor Ltd, unpublished work. This computer 
 * program includes Confidential, Proprietary Information and is a Trade Secret of 
 * Dialog Semiconductor Ltd.  All use, disclosure, and/or reproduction is prohibited 
 * unless authorized in writing. All Rights Reserved.
 *
 * <bluetooth.support@diasemi.com> and contributors.
 *
 ****************************************************************************************
 */
/*
 * INCLUDE FILES
 ****************************************************************************************
 */
 
#include "global_io.h"
#include "gpio.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/// define UART pins
#define UART_GPIO_PORT  GPIO_PORT_0
#define UART_TX_PIN     GPIO_PIN_4
#define UART_RX_PIN     GPIO_PIN_5
#undef  UART_ENABLED

/// define SPI pins
#define SPI_GPIO_PORT   GPIO_PORT_0
#define SPI_CLK_PIN     GPIO_PIN_0
#define SPI_CS_PIN      GPIO_PIN_1
#define SPI_DO_PIN      GPIO_PIN_2
#define SPI_DI_PIN      GPIO_PIN_3
#define SPI_DREADY_PIN  GPIO_PIN_7


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
 
void periph_init(void);

void GPIO_reservations(void);

void set_pad_functions(void);
