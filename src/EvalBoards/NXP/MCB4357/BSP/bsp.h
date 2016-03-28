/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*                          (c) Copyright 2003-2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                      MICRIUM BOARD SUPPORT PACKAGE
*
*                                            NXP LPC4357
*                                               on the
*                                            Keil MCB4357
*
* Filename      : bsp.h
* Version       : V1.00.00
* Programmer(s) : MD
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               BSP present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  BSP_PRESENT
#define  BSP_PRESENT


/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <cpu_core.h>

#include  <lib_def.h>
#include  <lib_ascii.h>

#include  <bsp_int.h>


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/


#ifdef   BSP_MODULE
#define  BSP_EXT
#else
#define  BSP_EXT  extern
#endif

/*
*********************************************************************************************************
*                                        DEFAULT CONFIGURATION
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           LOCAL DEFINES
*********************************************************************************************************
*/

#define  BSP_MAIN_XTAL_OSC_FREQ_HZ                  12000000u
#define  BSP_32KHZ_OSC_FREQ_HZ                         32768u
#define  BSP_12MHZ_IRC_FREQ_HZ                      12000000u
#define  BSP_ENET_RX_FREQ_HZ                        50000000u
#define  BSP_ENET_TX_FREQ_HZ                        50000000u


/*
*********************************************************************************************************
*                                      REGISTER & BIT FIELD DEFINES
*********************************************************************************************************
*/

                                                                /* -------- SYSTEM CONTROL UNIT(SCU) REGISTERS -------- */
#define  BSP_SCU_BASE_ADDR                    ( (CPU_INT32U )(0x40086000u))
#define  BSP_REG_SCU_SFSP0(pin_nbr)           (*(CPU_REG32 *)(BSP_SCU_BASE_ADDR + 0x000u + 4u *(pin_nbr)))
#define  BSP_REG_SCU_SFSP1(pin_nbr)           (*(CPU_REG32 *)(BSP_SCU_BASE_ADDR + 0x008u + 4u *(pin_nbr)))
#define  BSP_REG_SCU_SFSP2(pin_nbr)           (*(CPU_REG32 *)(BSP_SCU_BASE_ADDR + 0x100u + 4u *(pin_nbr)))
#define  BSP_REG_SCU_SFSP3(pin_nbr)           (*(CPU_REG32 *)(BSP_SCU_BASE_ADDR + 0x180u + 4u *(pin_nbr)))
#define  BSP_REG_SCU_SFSP4(pin_nbr)           (*(CPU_REG32 *)(BSP_SCU_BASE_ADDR + 0x200u + 4u *(pin_nbr)))
#define  BSP_REG_SCU_SFSP5(pin_nbr)           (*(CPU_REG32 *)(BSP_SCU_BASE_ADDR + 0x280u + 4u *(pin_nbr)))
#define  BSP_REG_SCU_SFSP6(pin_nbr)           (*(CPU_REG32 *)(BSP_SCU_BASE_ADDR + 0x300u + 4u *(pin_nbr)))
#define  BSP_REG_SCU_SFSP7(pin_nbr)           (*(CPU_REG32 *)(BSP_SCU_BASE_ADDR + 0x380u + 4u *(pin_nbr)))
#define  BSP_REG_SCU_SFSP8(pin_nbr)           (*(CPU_REG32 *)(BSP_SCU_BASE_ADDR + 0x400u + 4u *(pin_nbr)))
#define  BSP_REG_SCU_SFSP9(pin_nbr)           (*(CPU_REG32 *)(BSP_SCU_BASE_ADDR + 0x480u + 4u *(pin_nbr)))
#define  BSP_REG_SCU_SFSPA(pin_nbr)           (*(CPU_REG32 *)(BSP_SCU_BASE_ADDR + 0x500u + 4u *(pin_nbr)))
#define  BSP_REG_SCU_SFSPB(pin_nbr)           (*(CPU_REG32 *)(BSP_SCU_BASE_ADDR + 0x580u + 4u *(pin_nbr)))
#define  BSP_REG_SCU_SFSPC(pin_nbr)           (*(CPU_REG32 *)(BSP_SCU_BASE_ADDR + 0x600u + 4u *(pin_nbr)))
#define  BSP_REG_SCU_SFSPD(pin_nbr)           (*(CPU_REG32 *)(BSP_SCU_BASE_ADDR + 0x680u + 4u *(pin_nbr)))
#define  BSP_REG_SCU_SFSPE(pin_nbr)           (*(CPU_REG32 *)(BSP_SCU_BASE_ADDR + 0x700u + 4u *(pin_nbr)))
#define  BSP_REG_SCU_SFSPF(pin_nbr)           (*(CPU_REG32 *)(BSP_SCU_BASE_ADDR + 0x780u + 4u *(pin_nbr)))

#define  BSP_SFSPX_MODE_FNCT_00                  0x0u
#define  BSP_SFSPX_MODE_FNCT_01                  0x1u
#define  BSP_SFSPX_MODE_FNCT_02                  0x2u
#define  BSP_SFSPX_MODE_FNCT_03                  0x3u
#define  BSP_SFSPX_MODE_FNCT_04                  0x4u
#define  BSP_SFSPX_MODE_FNCT_05                  0x5u
#define  BSP_SFSPX_MODE_FNCT_06                  0x6u
#define  BSP_SFSPX_MODE_FNCT_07                  0x7u

                                                                /* ---------------- GPIO PORT REGISTERS --------------- */
#define  BSP_GPIO_BASE_ADDR                   ( (CPU_INT32U )(0x400F4000u))
#define  BSP_REG_GPIO_DIR(n)                  (*(CPU_REG32 *)(BSP_GPIO_BASE_ADDR + 0x2000 + 4 *(n)))
#define  BSP_REG_GPIO_MASK(n)                 (*(CPU_REG32 *)(BSP_GPIO_BASE_ADDR + 0x2080 + 4 *(n)))
#define  BSP_REG_GPIO_PIN(n)                  (*(CPU_REG32 *)(BSP_GPIO_BASE_ADDR + 0x2100 + 4 *(n)))
#define  BSP_REG_GPIO_SET(n)                  (*(CPU_REG32 *)(BSP_GPIO_BASE_ADDR + 0x2200 + 4 *(n)))
#define  BSP_REG_GPIO_CLR(n)                  (*(CPU_REG32 *)(BSP_GPIO_BASE_ADDR + 0x2280 + 4 *(n)))
#define  BSP_REG_GPIO_NOT(n)                  (*(CPU_REG32 *)(BSP_GPIO_BASE_ADDR + 0x2300 + 4 *(n)))


/*
*********************************************************************************************************
*                                        CLOCK SOURCES DEFINE
*********************************************************************************************************
*/

#define  BSP_CLK_SRC_32KHZ_OSC                   0x00u
#define  BSP_CLK_SRC_IRC                         0x01u
#define  BSP_CLK_SRC_ENET_RX_CLK                 0x02u
#define  BSP_CLK_SRC_ENET_TX_CLK                 0x03u
#define  BSP_CLK_SRC_GP_CLKIN                    0x04u
#define  BSP_CLK_SRC_RSVD00                      0x05u
#define  BSP_CLK_SRC_XTAL_OSC                    0x06u
#define  BSP_CLK_SRC_PLL0USB                     0x07u
#define  BSP_CLK_SRC_PLL0AUDIO                   0x08u
#define  BSP_CLK_SRC_PLL1                        0x09u
#define  BSP_CLK_SRC_RSVD01                      0x0Au
#define  BSP_CLK_SRC_RSVD02                      0x0Bu
#define  BSP_CLK_SRC_IDIVA                       0x0Cu
#define  BSP_CLK_SRC_IDIVB                       0x0Du
#define  BSP_CLK_SRC_IDIVC                       0x0Eu
#define  BSP_CLK_SRC_IDIVD                       0x0Fu
#define  BSP_CLK_SRC_IDIVE                       0x10u


/*
*********************************************************************************************************
*                                             DATA TYPES
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

void        BSP_LowLevelInit            (void);
void        BSP_PreInit                 (void);
void        BSP_PostInit                (void);


/*
*********************************************************************************************************
*                                            CLOCK SERVICES
*********************************************************************************************************
*/

CPU_INT32U  BSP_CPU_ClkGet     (void);
CPU_INT32U  BSP_ClkSrcFreqGet  (CPU_INT32U  clk_src);


/*
*********************************************************************************************************
*                                            LED SERVICES
*********************************************************************************************************
*/

void         BSP_LED_On        (CPU_INT08U led);
void         BSP_LED_Off       (CPU_INT08U led);
void         BSP_LED_Toggle    (CPU_INT08U led);

/*
*********************************************************************************************************
*                                     PERIPHERAL POWER/CLOCK SERVICES
*********************************************************************************************************
*/

CPU_INT32U   BSP_PeriphClkFreqGet        (CPU_DATA       pwr_clk_id);

void         BSP_PeriphEn                (CPU_DATA       pwr_clk_id);

void         BSP_PeriphDis               (CPU_DATA       pwr_clk_id);



/*
*********************************************************************************************************
*                                          ERROR CHECKING
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of module include.                               */
