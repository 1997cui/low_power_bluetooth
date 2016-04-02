/**************************************************************************//**
 * @file     system_ARMCM0.c
 * @brief    CMSIS Cortex-M0 Device System Source File
 *           for CM0 Device Series
 * @version  V1.05
 * @date     26. July 2011
 *
 * @note
 * Copyright (C) 2010-2011 ARM Limited. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M 
 * processor based microcontrollers.  This file can be freely distributed 
 * within development tools that are supporting such ARM based processors. 
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/
 

#include "ARMCM0.h"
#include <string.h>
#include "user_periph_setup.h"
#include "gpio.h"
#include "oled.h"

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void SystemInit (void)
{
	SetWord16(TIMER0_CTRL_REG,0x6);      // stop timer
	NVIC_DisableIRQ(SWTIM_IRQn);     // disable software timer interrupt

	if ((GetWord16(CLK_CTRL_REG) & RUNNING_AT_XTAL16M) == 0)
	{
		while( (GetWord16(SYS_STAT_REG) & XTAL16_SETTLED) == 0 );     // wait for XTAL16 settle
		SetBits16(CLK_CTRL_REG , SYS_CLK_SEL ,0);                     // switch to XTAL16
		while( (GetWord16(CLK_CTRL_REG) & RUNNING_AT_XTAL16M) == 0 ); // wait for actual switch
	}

	SetWord16(CLK_AMBA_REG, 0x00);                 // set clocks (hclk and pclk ) 16MHz
	SetWord16(SET_FREEZE_REG,FRZ_WDOG);            // stop watch dog
	SetBits16(SYS_CTRL_REG, PAD_LATCH_EN, 1);      // open pads
	SetBits16(SYS_CTRL_REG, DEBUGGER_ENABLE, 1);   // open debugger
	SetBits16(PMU_CTRL_REG, PERIPH_SLEEP, 0);      // exit peripheral power down
	
    // Power up peripherals' power domain
    SetBits16(PMU_CTRL_REG, PERIPH_SLEEP, 0);
    while (!(GetWord16(SYS_STAT_REG) & PER_IS_UP));

    //Init pads
    GPIO_ConfigurePin(UART2_GPIO_PORT, UART2_TX_PIN, OUTPUT, PID_UART2_TX, false);
    GPIO_ConfigurePin(UART2_GPIO_PORT, UART2_RX_PIN, INPUT, PID_UART2_RX, false);
    // Init LED
    GPIO_ConfigurePin(LED_PORT, LED_PIN, OUTPUT, PID_GPIO, false);
	
	LCD_Init();
}
