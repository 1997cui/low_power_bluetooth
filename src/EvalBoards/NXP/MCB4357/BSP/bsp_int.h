/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                            (c) Copyright 2009-2013; Micrium, Inc.; Weston, FL
*
*                   All rights reserved.  Protected by international copyright laws.
*                   Knowledge of the source code may not be used to write a similar
*                   product.  This file may only be used in accordance with a license
*                   and should not be redistributed in any way.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                     MICRIUM BOARD SUPPORT PACKAGE
*                                         INTERRUPT CONTROLLER
*
*                                            NXP LPC4357
*                                               on the
*                                            Keil MCB4357
*
* Filename      : bsp_int.h
* Version       : V1.00.00
* Programmer(s) : MD
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               BSP_INT present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  BSP_INT_PRESENT
#define  BSP_INT_PRESENT


/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/


#ifdef   BSP_INT_MODULE
#define  BSP_INT_EXT
#else
#define  BSP_INT_EXT  extern
#endif

/*
*********************************************************************************************************
*                                        DEFAULT CONFIGURATION
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

                                                                /* ------------ INTERRUPT PRIORITY DEFINES ---------- */
#define  BSP_INT_PRIO_LEVEL_MASK             DEF_BIT_MASK(7, 0)
#define  BSP_INT_PRIO_LEVEL_00               0u
#define  BSP_INT_PRIO_LEVEL_01               1u
#define  BSP_INT_PRIO_LEVEL_02               2u
#define  BSP_INT_PRIO_LEVEL_03               3u


/*
*********************************************************************************************************
*                                           INTERRUPT DEFINES
*********************************************************************************************************
*/

                                                                /* -------------- CORTEX-M4 INTERRUPTS ---------------- */
#define  BSP_INT_ID_DAC                              0u         /* Digital to Analog Converter                          */
#define  BSP_INT_ID_M0CORE                           1u         /* CORTEX-M0 Communication line Interrupt from M0       */
#define  BSP_INT_ID_DMA                              2u         /* Direct Memory Access                                 */
#define  BSP_INT_ID_RSVD_00                          3u         /* RESERVED                                             */
#define  BSP_INT_ID_FLASHEEPROM                      4u         /*                                                      */
#define  BSP_INT_ID_ETHERNET                         5u         /*                                                      */
#define  BSP_INT_ID_SDIO                             6u         /*                                                      */
#define  BSP_INT_ID_LCD                              7u         /*                                                      */

#define  BSP_INT_ID_USB0                             8u         /*                                                      */
#define  BSP_INT_ID_USB1                             9u         /*                                                      */

#define  BSP_INT_ID_SCT                             10u         /*                                                      */

#define  BSP_INT_ID_RITIMER                         11u         /*                                                      */
#define  BSP_INT_ID_TIMER0                          12u         /*                                                      */

#define  BSP_INT_ID_TIMER1                          13u         /*                                                      */

#define  BSP_INT_ID_TIMER2                          14u         /*                                                      */
#define  BSP_INT_ID_TIMER3                          15u         /*                                                      */

#define  BSP_INT_ID_MCPWM                           16u         /*                                                      */
#define  BSP_INT_ID_ADC0                            17u         /*                                                      */

#define  BSP_INT_ID_I2C0                            18u         /*                                                      */
#define  BSP_INT_ID_I2C1                            19u         /*                                                      */
#define  BSP_INT_ID_SPI                             20u         /*                                                      */
#define  BSP_INT_ID_ADC1                            21u         /*                                                      */

#define  BSP_INT_ID_SSP0                            22u         /*                                                      */
#define  BSP_INT_ID_SSP1                            23u         /*                                                      */
#define  BSP_INT_ID_USART0                          24u         /*                                                      */
#define  BSP_INT_ID_UART1                           25u         /*                                                      */

#define  BSP_INT_ID_USART2                          26u         /*                                                      */
#define  BSP_INT_ID_USART3                          27u         /*                                                      */

#define  BSP_INT_ID_I2S0                            28u         /*                                                      */

#define  BSP_INT_ID_I2S1                            29u         /*                                                      */
#define  BSP_INT_ID_SPIFI                           30u         /*                                                      */
#define  BSP_INT_ID_SGPIO                           31u         /*                                                      */
#define  BSP_INT_ID_PIN_INT0                        32u         /*                                                      */

#define  BSP_INT_ID_PIN_INT1                        33u         /*                                                      */
#define  BSP_INT_ID_PIN_INT2                        34u         /*                                                      */
#define  BSP_INT_ID_PIN_INT3                        35u         /*                                                      */
#define  BSP_INT_ID_PIN_INT4                        36u         /*                                                      */
#define  BSP_INT_ID_PIN_INT5                        37u         /*                                                      */
#define  BSP_INT_ID_PIN_INT6                        38u         /*                                                      */

#define  BSP_INT_ID_PIN_INT7                        39u         /*                                                      */
#define  BSP_INT_ID_GINT0                           40u         /*                                                      */
#define  BSP_INT_ID_GINT1                           41u         /*                                                      */

#define  BSP_INT_ID_EVENTROUTER                     42u         /*                                                      */
#define  BSP_INT_ID_C_CAN1                          43u         /*                                                      */
#define  BSP_INT_ID_RSVD_01                         44u         /* RESERVED                                             */
#define  BSP_INT_ID_RSVD_02                         45u         /* RESERVED                                             */
#define  BSP_INT_ID_ATIMER                          46u         /*                                                      */
#define  BSP_INT_ID_RTC                             47u         /*                                                      */

#define  BSP_INT_ID_RSVD_03                         48u         /* RESERVED                                             */
#define  BSP_INT_ID_WWDT                            49u         /*                                                      */
#define  BSP_INT_ID_RSVD_04                         50u         /* RESERVED                                             */
#define  BSP_INT_ID_C_CAN0                          51u         /*                                                      */
#define  BSP_INT_ID_QEI                             52u         /*                                                      */

                                                                /* -------------- CORTEX-M0 INTERRUPTS ---------------- */
#define  BSP_INT_ID_M0_RTC                           0u         /*                                                      */
#define  BSP_INT_ID_M0_M4CORE                        1u         /* Interrupt from the M4 core                           */
#define  BSP_INT_ID_M0_DMA                           2u         /*                                                      */
#define  BSP_INT_ID_RSVD_05                          3u         /* RESERVED                                             */
#define  BSP_INT_ID_M0_FLASHEEPROMAT                 4u         /*                                                      */

#define  BSP_INT_ID_M0_ETHERNET                      5u         /*                                                      */
#define  BSP_INT_ID_M0_SDIO                          6u         /*                                                      */

#define  BSP_INT_ID_M0_LCD                           7u         /*                                                      */

#define  BSP_INT_ID_M0_USB0                          8u         /*                                                      */
#define  BSP_INT_ID_M0_USB1                          9u         /*                                                      */

#define  BSP_INT_ID_M0_SCT                          10u         /*                                                      */

#define  BSP_INT_ID_M0_RITIMER_OR_WWDT              11u         /*                                                      */
#define  BSP_INT_ID_M0_TIMER0                       12u         /*                                                      */

#define  BSP_INT_ID_M0_GINT1                        13u         /*                                                      */
#define  BSP_INT_ID_M0_PIN_INT4                     14u         /*                                                      */
#define  BSP_INT_ID_M0_TIMER3                       15u         /*                                                      */
#define  BSP_INT_ID_M0_MCPWM                        16u         /*                                                      */

#define  BSP_INT_ID_M0_ADC0                         17u         /*                                                      */
#define  BSP_INT_ID_M0_I2C0_OR_I2C1                 18u         /*                                                      */
#define  BSP_INT_ID_M0_SGPIO                        19u         /*                                                      */
#define  BSP_INT_ID_M0_SPI_OR_DAC                   20u         /*                                                      */

#define  BSP_INT_ID_M0_ADC1                         21u         /*                                                      */
#define  BSP_INT_ID_M0_SSP0_OR_SSP1                 22u         /*                                                      */
#define  BSP_INT_ID_M0_EVENTROUTER                  23u         /*                                                      */
#define  BSP_INT_ID_M0_USART0                       24u         /*                                                      */
#define  BSP_INT_ID_M0_UART1                        25u         /*                                                      */
#define  BSP_INT_ID_M0_USART_OR_C_CAN               26u         /*                                                      */
#define  BSP_INT_ID_M0_USART3                       27u         /*                                                      */
#define  BSP_INT_ID_M0_I2S0_OR_I2S1_QEI             28u         /*                                                      */

#define  BSP_INT_ID_M0_C_CAN0                       29u         /*                                                      */
#define  BSP_INT_ID_RSVD_06                         30u         /* RESERVED                                             */
#define  BSP_INT_ID_RSVD_07                         31u         /* RESERVED                                             */


                                                                /* Check if Cortex-M0 or M4 is being used               */
#ifndef CORTEX_M0
#ifndef CORTEX_M4
#error "Cortex Core is not defined properly in the Defines tab under C/C++"
#endif
#endif

#ifndef CORTEX_M0
#define  BSP_INT_ID_MAX                             53u
#else
#define  BSP_INT_ID_MAX                             32u
#endif


/*
*********************************************************************************************************
*                                             PERIPH DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void         BSP_IntClr           (CPU_INT08U     int_id);
void         BSP_IntDis           (CPU_INT08U     int_id);
void         BSP_IntDisAll        (void);
void         BSP_IntEn            (CPU_INT08U     int_id);
void         BSP_IntInit          (void);
void         BSP_IntVectSet       (CPU_INT08U     int_id,
                                   CPU_FNCT_VOID  isr_fnct);
void         BSP_IntHandler       (CPU_INT16U     src_nbr);


/*
*********************************************************************************************************
*                                              ERROR CHECKING
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of module include.                               */

