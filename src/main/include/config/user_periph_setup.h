/**
 ****************************************************************************************
 *
 * @file user_periph_setup.h
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
 
#ifndef _USER_PERIPH_SETUP_H_
    #define _USER_PERIPH_SETUP_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

    #include "rwip_config.h"
    #include "global_io.h"
    #include "arch.h"
    #include "da1458x_periph_setup.h"
    #include "i2c_eeprom.h"
/*
 * DEFINES
 ****************************************************************************************
 */

#define CFG_UART_HW_FLOW_CTRL
#undef CFG_UART_SW_FLOW_CTRL

/// Available baud rates 115200, 57600, 38400, 19200, 9600
#define CFG_UART_SPS_BAUDRATE       UART_BAUDRATE_115K2

/* Enable WKUPCT. Required by wkupct_quadec driver. */
    #define WKUP_ENABLED


/*
 * DEFINES
 ****************************************************************************************
 */

//*** <<< Use Configuration Wizard in Context Menu >>> ***

// <o> DK selection <0=> As in da1458x_periph_setup.h <1=> Basic <2=> Pro <3=> Expert
    #define HW_CONFIG (0)

    #define HW_CONFIG_BASIC_DK  ((HW_CONFIG==0 && SDK_CONFIG==1) || HW_CONFIG==1)
    #define HW_CONFIG_PRO_DK    ((HW_CONFIG==0 && SDK_CONFIG==2) || HW_CONFIG==2)
    #define HW_CONFIG_EXPERT_DK ((HW_CONFIG==0 && SDK_CONFIG==3) || HW_CONFIG==3)

//*** <<< end of configuration section >>>    ***


/****************************************************************************************/
/* i2c eeprom configuration                                                             */
/****************************************************************************************/

    #define I2C_EEPROM_SIZE   0x20000         // EEPROM size in bytes
    #define I2C_EEPROM_PAGE   256             // EEPROM's page size in bytes
    #define I2C_SPEED_MODE    I2C_FAST        // 1: standard mode (100 kbits/s), 2: fast mode (400 kbits/s)
    #define I2C_ADDRESS_MODE  I2C_7BIT_ADDR   // 0: 7-bit addressing, 1: 10-bit addressing
    #define I2C_ADDRESS_SIZE  I2C_2BYTES_ADDR // 0: 8-bit memory address, 1: 16-bit memory address, 3: 24-bit memory address




/****************************************************************************************/ 
/* UART configuration                                                                   */
/****************************************************************************************/  

    #define GPIO_UART1_TX_PORT   GPIO_PORT_0
    #define GPIO_UART1_TX_PIN    GPIO_PIN_4
    #define GPIO_UART1_RX_PORT   GPIO_PORT_0
    #define GPIO_UART1_RX_PIN    GPIO_PIN_5
    #define GPIO_UART1_RTS_PORT  GPIO_PORT_0
    #define GPIO_UART1_RTS_PIN   GPIO_PIN_3
    #define GPIO_UART1_CTS_PORT  GPIO_PORT_0
    #define GPIO_UART1_CTS_PIN   GPIO_PIN_2

/****************************************************************************************/ 
/* UART2 GPIO configuration                                                             */
/****************************************************************************************/ 

    #ifdef CFG_PRINTF_UART2
        #define  GPIO_UART2_TX_PORT     GPIO_PORT_1
        #define  GPIO_UART2_TX_PIN      GPIO_PIN_2
        
        #define  GPIO_UART2_RX_PORT     GPIO_PORT_1
        #define  GPIO_UART2_RX_PIN      GPIO_PIN_3
    #endif
		
		
/****************************************************************************************/
/* LED configuration                                                                    */
/****************************************************************************************/

    #if HW_CONFIG_BASIC_DK
        #define GPIO_LED_PORT     GPIO_PORT_1
        #define GPIO_LED_PIN      GPIO_PIN_0
    #elif HW_CONFIG_PRO_DK
        #define GPIO_LED_PORT     GPIO_PORT_1
        #define GPIO_LED_PIN      GPIO_PIN_0
    #else // HW_CONFIG_EXPERT_DK
        #define GPIO_LED_PORT     GPIO_PORT_0
        #define GPIO_LED_PIN      GPIO_PIN_7
    #endif
	
	
/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
 
void periph_init(void);

void GPIO_reservations(void);



#endif // _USER_PERIPH_SETUP_H_
