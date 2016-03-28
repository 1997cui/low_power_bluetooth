/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                             (c) Copyright 2010-2013; Micrium, Inc.; Weston, FL
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
*                                    MICRIUM BOARD SUPPORT PACKAGE
*
*                                            NXP LPC4357
*                                               on the
*                                            Keil MCB4357
*
* Filename      : bsp.c
* Version       : V1.00.00
* Programmer(s) : MD
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define   BSP_MODULE
#include  <bsp.h>
#include  <bsp_int.h>


/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      REGISTER & BIT FIELD DEFINES
*********************************************************************************************************
*/


                                                                /* --------- EXTERNAL MEMORY CONTROLLER(EMC) ---------- */
#define  BSP_EMC_BASE_ADDR                      ( (CPU_INT32U )(0x40005000u))
#define  BSP_REG_EMC_STATICWAITRD0              (*(CPU_REG32 *)(BSP_EMC_BASE_ADDR + 0x20Cu))

#define  BSP_FLASH_WAITSTATE_MAX                DEF_BIT_FIELD(5u, 0u)

                                                                /* ----------- CLOCK GENERATION UNIT (CGU) ------------ */
#define  BSP_CGU_BASE_ADDR                      ( (CPU_INT32U )(0x40050000u))
#define  BSP_REG_CGU_XTAL_OSC_CTRL              (*(CPU_REG32 *)(BSP_CGU_BASE_ADDR + 0x018u))
#define  BSP_REG_CGU_PLL1_STAT                  (*(CPU_REG32 *)(BSP_CGU_BASE_ADDR + 0x040u))
#define  BSP_REG_CGU_PLL1_CTRL                  (*(CPU_REG32 *)(BSP_CGU_BASE_ADDR + 0x044u))
#define  BSP_REG_CGU_BASE_M4_CLK                (*(CPU_REG32 *)(BSP_CGU_BASE_ADDR + 0x06Cu))


#define  BSP_CLK_CTRL_PD                        DEF_BIT_00
#define  BSP_CLK_CTRL_BYPASS                    DEF_BIT_01
#define  BSP_CLK_CTRL_HF                        DEF_BIT_02
#define  BSP_CLK_CTRL_FBSEL                     DEF_BIT_06
#define  BSP_CLK_CTRL_DIRECT                    DEF_BIT_07
#define  BSP_CLK_CTRL_AUTOBLOCK                 DEF_BIT_11

                                                                /* ------------ CLOCK CONTROL UNIT (CCU) -------------- */
#define  BSP_CCU_BASE_ADDR                      ( (CPU_INT32U )(0x40051000u))
#define  BSP_REG_CCU_CLK_M4_GPIO_CFG            (*(CPU_REG32 *)(BSP_CCU_BASE_ADDR + 0x410u))
#define  BSP_REG_CCU_CLK_M4_GPIO_STAT           (*(CPU_REG32 *)(BSP_CCU_BASE_ADDR + 0x414u))

#define  BSP_CCU_CLK_CFG_RUN                    DEF_BIT_00
#define  BSP_CCU_CLK_CFG_AUTO                   DEF_BIT_01

#define  BSP_CCU_GPIO_STAT_RUN                  DEF_BIT_00

                                                                /* ----------- PLL1 CONFIGURATION DEFINES ------------- */
#define  BSP_PLL1_MED_PSEL                       0u             /* Range [0 -   3]: Post-divider ratio P                */
#define  BSP_PLL1_MED_NSEL                       2u             /* Range [0 -   3]: Pre-divider ratio N                 */
#define  BSP_PLL1_MED_MSEL                      39u             /* Range [0 - 255]: Feedback-divider ratio M            */

#define  BSP_PLL1_FINAL_PSEL                     0u             /* Range [0 -   3]: Post-divider ratio P                */
#define  BSP_PLL1_FINAL_NSEL                     0u             /* Range [0 -   3]: Pre-divider ratio N                 */
#define  BSP_PLL1_FINAL_MSEL                    14u             /* Range [0 - 255]: Feedback-divider ratio M            */

#define  BSP_PLL1_BYPASS                         0u             /* 0: Use PLL, 1: PLL is bypassed                       */
#define  BSP_PLL1_DIRECT                         1u             /* 0: Use PSEL, 1: Don't use PSEL                       */
#define  BSP_PLL1_FBSEL                          0u             /* 0: FCCO is used as PLL feedback ...                  */
                                                                /* ... 1: FCLKOUT is used as PLL feedback               */

#define  BSP_PLL_STAT_LOCK                      DEF_BIT_00

                                                                /* ---------- RESET GENERATION UNIT (RGU) ------------- */
#define  BSP_RGU_BASE_ADDR                      ( (CPU_INT32U )(0x40050000u))                                                                
#define  BSP_REG_RGU_RESET_CRTL0                (*(CPU_REG32 *)(BSP_RGU_BASE_ADDR + 0x3100u))
#define  BSP_REG_RGU_RESET_CRTL1                (*(CPU_REG32 *)(BSP_RGU_BASE_ADDR + 0x3104u))

#define  BSP_RGU_M0APP_RST                      DEF_BIT_24


/*
*********************************************************************************************************
*                                       EXTERN  GLOBAL VARIABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           LOCAL DEFINES
*********************************************************************************************************
*/

#define  BSP_REG_TO_VAL                             0x000FFFFFu

                                                                /* ----------------- LEDS BIT DEFINES ----------------- */
#define  BSP_LED0                                   DEF_BIT_14
#define  BSP_LED1                                   DEF_BIT_13
#define  BSP_LED2                                   DEF_BIT_12
#define  BSP_LED10                                  DEF_BIT_28
#define  BSP_LED11                                  DEF_BIT_27
#define  BSP_LED12                                  DEF_BIT_26
#define  BSP_LED13                                  DEF_BIT_25
#define  BSP_LED14                                  DEF_BIT_24
#define  BSP_LEDS_PORT4_GRP                        (BSP_LED0 | BSP_LED1 | BSP_LED2)
#define  BSP_LEDS_PORT6_GRP                        (BSP_LED10 | BSP_LED11 | BSP_LED12 | BSP_LED13 | BSP_LED14)


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  BSP_LED_Init(void);
static  CPU_INT32S  BSP_ClkSrcGet         (CPU_INT32U  clk_src);


/*
***********************************************************************************************************
***********************************************************************************************************
**                                        GLOBAL FUNCTIONS
***********************************************************************************************************
***********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                         BSP_LowLevelInit()
*
* Description : Board Support Package Low Level Initialization.
*
* Argument(s) : none.
*
* Returns(s)  : none
*
* Caller(s)   : Startup code.
*
* Note(s)     : Clock initialization is included in this function.
*********************************************************************************************************
*/

void  BSP_LowLevelInit (void)
{
    CPU_INT32U  reg_to;
    CPU_INT32U  reg_val;


    BSP_REG_EMC_STATICWAITRD0 = BSP_FLASH_WAITSTATE_MAX;        /* Set Flash wait states to maximum.                    */

    BSP_REG_CGU_BASE_M4_CLK = ((BSP_CLK_CTRL_AUTOBLOCK) |       /* Enable Autoblock.                                    */
                               (BSP_CLK_SRC_IRC << 24u));       /* Switch Base M3 clk source to IRC.                    */

                                                                /* Enable oscillator pad & Operation w/ XTAL connected  */
                                                                /* Select Oscillator Low frequency mode.                */
    DEF_BIT_CLR(BSP_REG_CGU_XTAL_OSC_CTRL, (BSP_CLK_CTRL_PD      |
                                            BSP_CLK_CTRL_BYPASS  |
                                            BSP_CLK_CTRL_HF));

                                                                /* --------- CFG PLL1 MID CPU CLOCK FREQUENCY --------- */
                                                                /* See Note 1. and 2.                                   */
    DEF_BIT_SET(BSP_REG_CGU_PLL1_CTRL, BSP_CLK_CTRL_PD);        /* Power down PLL1.                                     */
    BSP_REG_CGU_PLL1_CTRL = (0                    << 0u)  |     /* PLL1 Enabled.                                        */
                            (BSP_PLL1_BYPASS      << 1u)  |     /* CCO out sent to post-dividers.                       */
                            (BSP_PLL1_FBSEL       << 6u)  |     /* PLL output used as feedback.                         */
                            (BSP_PLL1_DIRECT      << 7u)  |     /* Direct on/off.                                       */
                            (BSP_PLL1_MED_PSEL    << 8u)  |     /* PSEL.                                                */
                            (0                    << 11u) |     /* Autoblock Disabled.                                  */
                            (BSP_PLL1_MED_NSEL    << 12u) |     /* NSEL.                                                */
                            (BSP_PLL1_MED_MSEL    << 16u) |     /* MSEL.                                                */
                            (BSP_CLK_SRC_XTAL_OSC << 24u);      /* Clock source.                                        */


    reg_to  = BSP_REG_TO_VAL;
    reg_val = BSP_REG_CGU_PLL1_STAT;
                                                                /* Wait for PLL1 lock.                                  */
    while ((DEF_BIT_IS_CLR(reg_val, BSP_PLL_STAT_LOCK)) &
           (reg_to > 0u)) {
        reg_val = BSP_REG_CGU_PLL1_STAT;
        reg_to--;
    }

                                                                /* CPU base clock @ 160 MHz before final clock set.     */
    BSP_REG_CGU_BASE_M4_CLK = ((BSP_CLK_CTRL_AUTOBLOCK)  |      /* Autoblock En.                                        */
                               (BSP_CLK_SRC_PLL1 << 24)) ;      /* Clock source: PLL1.                                  */

    for (reg_to = 0; reg_to < 1000; reg_to++) {                 /* Wait about 4000 cycles.                              */
        ;
    }

                                                                /* --------- CFG PLL1 MAX CPU CLOCK FREQUENCY --------- */
                                                                /* See note 2.                                          */
    BSP_REG_CGU_PLL1_CTRL = (0                    << 0)   |     /* PLL1 Enabled.                                        */
                            (BSP_PLL1_BYPASS      << 1)   |     /* CCO out sent to post-dividers.                       */
                            (BSP_PLL1_FBSEL       << 6)   |     /* PLL output used as feedback.                         */
                            (BSP_PLL1_DIRECT      << 7)   |     /* Direct on/off.                                       */
                            (BSP_PLL1_FINAL_PSEL  << 8)   |     /* PSEL.                                                */
                            (BSP_CLK_CTRL_AUTOBLOCK)      |     /* Autoblock En.                                        */
                            (BSP_PLL1_FINAL_NSEL  << 12)  |     /* NSEL.                                                */
                            (BSP_PLL1_FINAL_MSEL  << 16)  |     /* MSEL.                                                */
                            (BSP_CLK_SRC_XTAL_OSC << 24);       /* Clock source.                                        */

    reg_to  = BSP_REG_TO_VAL;
    reg_val = BSP_REG_CGU_PLL1_STAT;
                                                                /* Wait for PLL1 lock                                   */
    while ((DEF_BIT_IS_CLR(reg_val, BSP_PLL_STAT_LOCK)) &
           (reg_to > 0u)) {
        reg_val = BSP_REG_CGU_PLL1_STAT;
        reg_to--;
    }
                                                                 /* Set CPU base clock source                           */
    BSP_REG_CGU_BASE_M4_CLK = (BSP_CLK_CTRL_AUTOBLOCK)  |        /* Autoblock En                                        */
                              (BSP_CLK_SRC_PLL1 << 24) ;         /* Set clock source                                    */
}


/*
*********************************************************************************************************
*                                          BSP_PreInit()
*
* Description : System Pre-Initialization. Initializes all peripherals that don't require OS services (LEDs, PBs)
*               or modules than need to be initialized before the OS (External memories).
*
* Argument(s) : none.
*
* Return(s)   : none.

* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_PreInit (void)
{
    BSP_IntInit();
}


/*
*********************************************************************************************************
*                                          BSP_PostInit()
*
* Description : Initialize all the peripherals that required OS services (OS initialized)
*
* Argument(s) : none.
*
* Return(s)   : none.

* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_PostInit (void)
{
    BSP_LED_Init();
}


/*
*********************************************************************************************************
*                                             BSP_LED_Init()
*
* Description : This function is used to initialize the LEDs on the board.
*
* Arguments   : none
*
* Return(s)   : none.

* Caller(s)   : Application.
*
* Note(s)     : Sets the port modes to allow writing to the LED controlled port bits.
*********************************************************************************************************
*/

static  void  BSP_LED_Init (void)
{
                                                                /* Enable CCU Clock                                     */
    DEF_BIT_SET(BSP_REG_CCU_CLK_M4_GPIO_CFG, BSP_CCU_CLK_CFG_RUN |
                                             BSP_CCU_CLK_CFG_AUTO);
    while(!(DEF_BIT_IS_SET(BSP_REG_CCU_CLK_M4_GPIO_STAT,
                           BSP_CCU_GPIO_STAT_RUN)));
    
                                                                /* Set the ports to allow setting of the LEDs           */
    BSP_REG_SCU_SFSP9(0)  = BSP_SFSPX_MODE_FNCT_00;             /* Select GPIO4[12] mode for LED                        */
    BSP_REG_SCU_SFSP9(1)  = BSP_SFSPX_MODE_FNCT_00;             /* Select GPIO4[12] mode for LED                        */
    BSP_REG_SCU_SFSP9(2)  = BSP_SFSPX_MODE_FNCT_00;             /* Select GPIO4[12] mode for LED                        */
    BSP_REG_SCU_SFSPD(10) = BSP_SFSPX_MODE_FNCT_04;             /* Select GPIO6[24] mode for LED                        */
    BSP_REG_SCU_SFSPD(11) = BSP_SFSPX_MODE_FNCT_04;             /* Select GPIO6[25] mode for LED                        */
    BSP_REG_SCU_SFSPD(12) = BSP_SFSPX_MODE_FNCT_04;             /* Select GPIO6[26] mode for LED                        */
    BSP_REG_SCU_SFSPD(13) = BSP_SFSPX_MODE_FNCT_04;             /* Select GPIO6[27] mode for LED                        */
    BSP_REG_SCU_SFSPD(14) = BSP_SFSPX_MODE_FNCT_04;             /* Select GPIO6[28] mode for LED                        */

                                                                /* Set GPIO pins direction as output                    */
    DEF_BIT_SET(BSP_REG_GPIO_DIR(4), (BSP_LED0   |
                                      BSP_LED1   |
                                      BSP_LED2  ));

                                                                /* Set GPIO pins direction as output                    */
    DEF_BIT_SET(BSP_REG_GPIO_DIR(6), (BSP_LED10  |
                                      BSP_LED11  |
                                      BSP_LED12  |
                                      BSP_LED13  |
                                      BSP_LED14 ));

    BSP_LED_Off(0);
}


/*
*********************************************************************************************************
*                                            BSP_LED_Off()
*
* Description : Turns OFF any or all of the LEDs on the board.
*
* Argument(s) : led    The ID of the LED control:
*                      0    turns OFF ALL the LEDs in the circle (LED3 - LED15).
*                      4    turns OFF LED4 on the board.
*                      5    turns OFF LED5 on the board.
*                      .
*                      .
*                     15    turns OFF LED15 on the board.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : LED P9_2  = BEP_LED0
*               LED P9_1  = BEP_LED1
*               LED P9_0  = BEP_LED2
*               LED PD_14 = BEP_LED10
*               LED PD_13 = BEP_LED11
*               LED PD_12 = BEP_LED12
*               LED PD_11 = BEP_LED13
*               LED PD_10 = BEP_LED14
*********************************************************************************************************
*/

void  BSP_LED_Off (CPU_INT08U led)
{
    switch (led) {
        case 0u:
             DEF_BIT_SET(BSP_REG_GPIO_CLR(4), BSP_LEDS_PORT4_GRP);
             DEF_BIT_SET(BSP_REG_GPIO_CLR(6), BSP_LEDS_PORT6_GRP);
             break;


        case 1u:
             DEF_BIT_SET(BSP_REG_GPIO_CLR(4), BSP_LED0);
             break;


        case 2u:
             DEF_BIT_SET(BSP_REG_GPIO_CLR(4), BSP_LED1);
             break;


        case 3u:
             DEF_BIT_SET(BSP_REG_GPIO_CLR(4), BSP_LED2);
             break;


        case 4u:
             DEF_BIT_SET(BSP_REG_GPIO_CLR(6), BSP_LED10);
             break;


        case 5u:
             DEF_BIT_SET(BSP_REG_GPIO_CLR(6), BSP_LED11);
             break;


        case 6u:
             DEF_BIT_SET(BSP_REG_GPIO_CLR(6), BSP_LED12);
             break;


        case 7u:
             DEF_BIT_SET(BSP_REG_GPIO_CLR(6), BSP_LED13);
             break;


        case 8u:
             DEF_BIT_SET(BSP_REG_GPIO_CLR(6), BSP_LED14);
             break;


        default:
             break;
    }
}


/*
*********************************************************************************************************
*                                             BSP_LED_On()
*
* Description : Turn ON any or all the LEDs on the board.
*
* Argument(s) : led    The ID of the LED control:
*                      0    turns ON ALL the LEDs in the circle (LED3 - LED15).
*                      4    turns ON LED4 on the board.
*                      5    turns ON LED5 on the board.
*                      .
*                      .
*                     15    turns ON LED15 on the board
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : LED P9_2  = BEP_LED0
*               LED P9_1  = BEP_LED1
*               LED P9_0  = BEP_LED2
*               LED PD_14 = BEP_LED10
*               LED PD_13 = BEP_LED11
*               LED PD_12 = BEP_LED12
*               LED PD_11 = BEP_LED13
*               LED PD_10 = BEP_LED14
*********************************************************************************************************
*/

void  BSP_LED_On (CPU_INT08U led)
{
    switch (led) {
        case 0u:
             DEF_BIT_SET(BSP_REG_GPIO_SET(4), BSP_LEDS_PORT4_GRP);
             DEF_BIT_SET(BSP_REG_GPIO_SET(6), BSP_LEDS_PORT6_GRP);
             break;

        case 1u:
             DEF_BIT_SET(BSP_REG_GPIO_SET(4), BSP_LED0);
             break;


        case 2u:
             DEF_BIT_SET(BSP_REG_GPIO_SET(4), BSP_LED1);
             break;


        case 3u:
             DEF_BIT_SET(BSP_REG_GPIO_SET(4), BSP_LED2);
             break;


        case 4u:
             DEF_BIT_SET(BSP_REG_GPIO_SET(6), BSP_LED10);
             break;


        case 5u:
             DEF_BIT_SET(BSP_REG_GPIO_SET(6), BSP_LED11);
             break;


        case 6u:
             DEF_BIT_SET(BSP_REG_GPIO_SET(6), BSP_LED12);
             break;


        case 7u:
             DEF_BIT_SET(BSP_REG_GPIO_SET(6), BSP_LED13);
             break;


        case 8u:
             DEF_BIT_SET(BSP_REG_GPIO_SET(6), BSP_LED14);
             break;


        default:
             break;
    }
}


/*
*********************************************************************************************************
*                                             BSP_LED_Toggle()
*
* Description : Toggles any or all the LEDs on the board.
*
* Argument(s) : led    The LED number on the board(3-15)
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : LED P9_2  = BEP_LED0
*               LED P9_1  = BEP_LED1
*               LED P9_0  = BEP_LED2
*               LED PD_14 = BEP_LED10
*               LED PD_13 = BEP_LED11
*               LED PD_12 = BEP_LED12
*               LED PD_11 = BEP_LED13
*               LED PD_10 = BEP_LED14
*********************************************************************************************************
*/

void  BSP_LED_Toggle (CPU_INT08U led)
{
    switch (led) {
        case 0u:
             DEF_BIT_SET(BSP_REG_GPIO_NOT(4), BSP_LEDS_PORT4_GRP);
             DEF_BIT_SET(BSP_REG_GPIO_NOT(6), BSP_LEDS_PORT6_GRP);
             break;

        case 1u:
             DEF_BIT_SET(BSP_REG_GPIO_NOT(4), BSP_LED0);
             break;


        case 2u:
             DEF_BIT_SET(BSP_REG_GPIO_NOT(4), BSP_LED1);
             break;


        case 3u:
             DEF_BIT_SET(BSP_REG_GPIO_NOT(4), BSP_LED2);
             break;


        case 4u:
             DEF_BIT_SET(BSP_REG_GPIO_NOT(6), BSP_LED10);
             break;


        case 5u:
             DEF_BIT_SET(BSP_REG_GPIO_NOT(6), BSP_LED11);
             break;


        case 6u:
             DEF_BIT_SET(BSP_REG_GPIO_NOT(6), BSP_LED12);
             break;


        case 7u:
             DEF_BIT_SET(BSP_REG_GPIO_NOT(6), BSP_LED13);
             break;


        case 8u:
             DEF_BIT_SET(BSP_REG_GPIO_NOT(6), BSP_LED14);
             break;


        default:
             break;
    }
}


/*
*********************************************************************************************************
*********************************************************************************************************
**                                       CPU CLOCK FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            BSP_CPU_ClkGet()
*
* Description : Gets the CPU clock frequency(Fclk).
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

CPU_INT32U  BSP_CPU_ClkGet (void)
{
    CPU_INT08U  clk_src;
    CPU_INT32U  cpu_clk;


    clk_src = ((BSP_REG_CGU_BASE_M4_CLK >> 24u) & 0x1Fu);

    cpu_clk = BSP_ClkSrcFreqGet(clk_src);

    return (cpu_clk);
}


/*
*********************************************************************************************************
*                                            BSP_ClkSrcFreqGet()
*
* Description : Gets clock frequency for specified clock source.
*
* Argument(s) : clk_src      the ID of the clock source.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

CPU_INT32U  BSP_ClkSrcFreqGet (CPU_INT32U  clk_src)
{
    CPU_INT32U  mul;
    CPU_INT32U  div;
    CPU_INT32U  p;
    CPU_INT32U  clk_freq;
    CPU_INT32S  clk_sel;
    CPU_INT32U  reg_val;

    clk_sel  = clk_src;
    mul      = 1u;
    div      = 1u;
    clk_freq = 0u;

    do {
        switch (clk_sel) {
            case BSP_CLK_SRC_32KHZ_OSC:
                 clk_freq = BSP_32KHZ_OSC_FREQ_HZ;
                 break;


            case BSP_CLK_SRC_IRC:
                 clk_freq = BSP_12MHZ_IRC_FREQ_HZ;
                 break;

            case BSP_CLK_SRC_ENET_RX_CLK:
                 clk_freq = BSP_ENET_RX_FREQ_HZ;
                 break;


            case BSP_CLK_SRC_ENET_TX_CLK:
                 clk_freq = BSP_ENET_TX_FREQ_HZ;
                 break;


            case BSP_CLK_SRC_XTAL_OSC:
                 clk_freq = BSP_MAIN_XTAL_OSC_FREQ_HZ;
                 break;


            case BSP_CLK_SRC_PLL1:
                 reg_val = BSP_REG_CGU_PLL1_CTRL;
                 p       = ((reg_val >>  8u) & 0x03u) + 1u;
                 div     = ((reg_val >> 12u) & 0x03u) + 1u;
                 mul     = ((reg_val >> 16u) & 0xFFu) + 1u;

                 if (DEF_BIT_IS_SET(reg_val, BSP_CLK_CTRL_BYPASS)) {
                                                                /* Bypass = 1, PLL1 input clock sent to post-dividers.  */
                     if (DEF_BIT_IS_SET(reg_val, BSP_CLK_CTRL_DIRECT)) {
                         div *= (2u * p);
                     }
                 } else {
                                                                /* Direct and Integer mode.                             */
                     if ((DEF_BIT_IS_CLR(reg_val, BSP_CLK_CTRL_DIRECT)) &&
                         (DEF_BIT_IS_CLR(reg_val, BSP_CLK_CTRL_FBSEL))) {
                         div *= (2u * p);                       /* Non-integer mode.                                    */
                     }
                 }

                 break;


            case BSP_CLK_SRC_IDIVA:
            case BSP_CLK_SRC_IDIVB:
            case BSP_CLK_SRC_IDIVC:
            case BSP_CLK_SRC_IDIVD:
            case BSP_CLK_SRC_IDIVE:
            case BSP_CLK_SRC_PLL0USB:
            case BSP_CLK_SRC_PLL0AUDIO:
            case BSP_CLK_SRC_GP_CLKIN:
            default:
                 return (0u);
        }

        if (clk_freq == 0) {
            clk_sel = BSP_ClkSrcGet(clk_sel);
        }
    } while (clk_freq == 0u);

    clk_freq = ((clk_freq * mul) / div);

    return (clk_freq);

}


/*
*********************************************************************************************************
*                                            BSP_ClkSrcGet()
*
* Description : Get input clock source for specified clock generation block.
*
* Argument(s) : clk_src      the ID of the clock source.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

CPU_INT32S  BSP_ClkSrcGet (CPU_INT32U  clk_src)
{
    CPU_INT32U  reg_val;
    CPU_INT32S  clk_sel;


    clk_sel = -1;

    switch (clk_src) {
        case BSP_CLK_SRC_IRC:
        case BSP_CLK_SRC_ENET_RX_CLK:
        case BSP_CLK_SRC_ENET_TX_CLK:
        case BSP_CLK_SRC_GP_CLKIN:
             return (clk_src);


        case BSP_CLK_SRC_XTAL_OSC:
             return (BSP_REG_CGU_XTAL_OSC_CTRL & 1) ? (-1) : (BSP_CLK_SRC_XTAL_OSC);


        case BSP_CLK_SRC_PLL1:
             reg_val = (BSP_REG_CGU_PLL1_STAT & 1) ? (BSP_REG_CGU_PLL1_CTRL) : (0u);
             break;


        case BSP_CLK_SRC_IDIVA:
        case BSP_CLK_SRC_IDIVB:
        case BSP_CLK_SRC_IDIVC:
        case BSP_CLK_SRC_IDIVD:
        case BSP_CLK_SRC_IDIVE:
        case BSP_CLK_SRC_PLL0USB:
        case BSP_CLK_SRC_PLL0AUDIO:
        case BSP_CLK_SRC_32KHZ_OSC:
        default:
             return (clk_sel);
    }

    if (!(reg_val & 1)) {
        clk_sel = (reg_val >> 24u) & 0x1F;
    }

    return (clk_sel);
}
