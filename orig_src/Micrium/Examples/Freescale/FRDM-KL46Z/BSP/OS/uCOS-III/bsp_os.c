/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                          (c) Copyright 2003-2015; Micrium, Inc.; Weston, FL
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
*                                       BOARD SUPPORT PACKAGE
*                                          uCOS-III LAYER
*
* Filename      : bsp_os.c
* Version       : V1.00
* Programmer(s) : DC
*                 JFT
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define  BSP_OS_MODULE
#include <bsp.h>
#include <bsp_os.h>
                                                                /* Should remove and redefine used bit fields and ...   */
                                                                /* ... registers.                                       */
#include <MKL46Z4.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  BSP_OS_TICK_NEXT_SET_CALL_STACK_SIZE      100
#define  BSP_OS_USE_LPTMR                          DEF_ENABLED
#define  BSP_OS_LPTMR_PSR_PCS_MCGIRCLK_SEL         DEF_BIT_MASK(0u, 0u)
#define  BSP_OS_LPTMR_PSR_PCS_LPO_SEL              DEF_BIT_MASK(1u, 0u)
#define  BSP_OS_LPTMR_PSR_PCS_ERCLK32K_SEL         DEF_BIT_MASK(2u, 0u)
#define  BSP_OS_LPTMR_PSR_PCS_OSCERCLK_SEL         DEF_BIT_MASK(3u, 0u)
#define  BSP_OS_LPTIMER_TICK_RATE_HZ              (1000u)
#define  BSP_OS_LPTICK_TO_OSTICK(lptick)        (((lptick)*OSCfg_TickRate_Hz)/BSP_OS_LPTIMER_TICK_RATE_HZ)
#define  BSP_OS_OSTICK_TO_LPTICK(ostick)        (((ostick)*BSP_OS_LPTIMER_TICK_RATE_HZ)/OSCfg_TickRate_Hz)


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


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
                                                                /* Stored in OS Tick units.                             */
static  OS_TICK  BSP_OS_TicksToGo;
                                                                /* Stored in OS Tick units.                             */
static  OS_TICK  BSP_OS_LastTick;
                                                                /* Stored in OS Tick units.                             */
static  OS_TICK  BSP_OS_UnTick;


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  OS_TICK  BSP_OS_LP_TickGet(void);


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*********************************************************************************************************
**                                         GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
**                                     BSP OS LOCKS FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*********************************************************************************************************
**                                     BSP OS LOCKS FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      BSP_OS_SemCreate()
*
* Description : Creates a sempahore to lock/unlock
*
* Argument(s) : p_sem        Pointer to a BSP_OS_SEM structure
*
*               sem_val      Initial value of the semaphore.
*
*               p_sem_name   Pointer to the semaphore name.
*
* Return(s)   : DEF_OK       if the semaphore was created.
*               DEF_FAIL     if the sempahore could not be created.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_OS_SemCreate (BSP_OS_SEM       *p_sem,
                               BSP_OS_SEM_VAL    sem_val,
                               CPU_CHAR         *p_sem_name)
{
    OS_ERR     err;


    OSSemCreate((OS_SEM    *)p_sem,
                (CPU_CHAR  *)p_sem_name,
                (OS_SEM_CTR )sem_val,
                (OS_ERR    *)&err);

    if (err != OS_ERR_NONE) {
        return (DEF_FAIL);
    }

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                     BSP_OS_SemWait()
*
* Description : Wait on a semaphore to become available
*
* Argument(s) : sem          sempahore handler
*
*               dly_ms       delay in miliseconds to wait on the semaphore
*
* Return(s)   : DEF_OK       if the semaphore was acquire
*               DEF_FAIL     if the sempahore could not be acquire
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_OS_SemWait (BSP_OS_SEM  *p_sem,
                             CPU_INT32U   dly_ms)
{
    OS_ERR      err;
    CPU_INT32U  dly_ticks;


    dly_ticks  = ((dly_ms * DEF_TIME_NBR_mS_PER_SEC) / OSCfg_TickRate_Hz);

    OSSemPend((OS_SEM *)p_sem,
              (OS_TICK )dly_ticks,
              (OS_OPT  )OS_OPT_PEND_BLOCKING,
              (CPU_TS  )0,
              (OS_ERR *)&err);

    if (err != OS_ERR_NONE) {
       return (DEF_FAIL);
    }

    return (DEF_OK);
}

/*
*********************************************************************************************************
*                                      BSP_OS_SemPost()
*
* Description : Post a semaphore
*
* Argument(s) : sem          Semaphore handler
*
* Return(s)   : DEF_OK     if the semaphore was posted.
*               DEF_FAIL      if the sempahore could not be posted.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_OS_SemPost (BSP_OS_SEM *p_sem)
{
    OS_ERR  err;


    OSSemPost((OS_SEM *)p_sem,
              (OS_OPT  )OS_OPT_POST_1,
              (OS_ERR *)&err);

    if (err != OS_ERR_NONE) {
        return (DEF_FAIL);
    }

    return (DEF_OK);
}


/*
*********************************************************************************************************
*********************************************************************************************************
**                                     uC/OS-III TIMER FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                    BSP_TimeDlyMs()
*
* Description : This function delay the exceution for specifi amount of miliseconds
*
* Argument(s) : dly_ms       Delay in miliseconds
*
* Return(s)   : none.
*
* Caller(s)   : Application
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void   BSP_OS_TimeDlyMs (CPU_INT32U  dly_ms)
{
    CPU_INT16U  ms;
    CPU_INT16U  sec;
    OS_ERR      err;


    if (dly_ms > 10000u) {                                       /* Limit delays to 10 seconds.                        */
        dly_ms = 10000u;
    }

    if (dly_ms >= 1000u) {
        ms  = dly_ms / 1000u;
        sec = dly_ms % 1000u;
    } else {
        ms  = dly_ms;
        sec = 0u;
    }


    OSTimeDlyHMSM((CPU_INT16U) 0u,
                  (CPU_INT16U) 0u,
                  (CPU_INT16U) sec,
                  (CPU_INT32U) ms,
                  (OS_OPT    ) OS_OPT_TIME_HMSM_STRICT,
                  (OS_ERR   *)&err);
}


/*
*********************************************************************************************************
*                                     BSP_TimeDly()
*
* Description : This function delay the exceution for specific amount of clk ticks
*
* Argument(s) : dly_tick     Delay in clk ticks
*
* Return(s)   : none.
*
* Caller(s)   : Application
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void   BSP_OS_TimeDly (CPU_INT32U  dly_tick)
{
    OS_ERR err;

    OSTimeDly(dly_tick, OS_OPT_TIME_DLY, &err);

   (void)&err;
}


/*
*********************************************************************************************************
*********************************************************************************************************
**                                       uC/OS-III Low Power Tick
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          BSP_OS_LP_TickInit()
*
* Description : Initialize the Low-Power Timer to enable dynamic ticking.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Tick_Init.
*
*               This function is an INTERNAL uC/OS-III function & MUST NOT be called by application
*               function(s).
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_OS_LP_TickInit (void)
{
    CPU_INT32U lpt_reg;


    BSP_OS_TicksToGo   = 0;
    BSP_OS_LastTick    = 0;
    BSP_OS_UnTick      = 0;

                                                                /* ------- Enable Low-Power Timer module clock -------- */
    DEF_BIT_SET(SIM_SCGC5, SIM_SCGC5_LPTMR_MASK);
    DEF_BIT_CLR(LPTMR0_PSR, LPTMR_CSR_TEN_MASK);

                                                                /* --------------- Set Control Register --------------- */
    lpt_reg  = 0;
    DEF_BIT_SET(lpt_reg, LPTMR_CSR_TIE_MASK);
    LPTMR0_CSR = lpt_reg;
                                                                /* -------------- Set Prescaler Register -------------- */
    lpt_reg  = 0;                                               /* Read current PSR                                     */
    DEF_BIT_SET(lpt_reg, LPTMR_PSR_PBYP_MASK);                  /* Set bypass                                           */
    DEF_BIT_CLR(lpt_reg, LPTMR_PSR_PCS_MASK);                   /* Set clock source to LPO                              */
    DEF_BIT_SET(lpt_reg, BSP_OS_LPTMR_PSR_PCS_LPO_SEL);
    LPTMR0_PSR = lpt_reg;
                                                                /* --------------- Set Compare Register --------------- */
    LPTMR0_CMR = 0;
                                                                /* ------------------ Enable timer -------------------- */
    BSP_IntEn(BSP_INT_ID_LPTMR0);
    DEF_BIT_SET(LPTMR0_CSR, LPTMR_CSR_TEN_MASK);
}


/*
*********************************************************************************************************
*                                        BSP_OS_LP_TickHandler()
*
* Description : Handle LPTimer interrupt.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This is an ISR.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_OS_LP_TickHandler (void)
{
    CPU_SR_ALLOC();


    if (LPTMR0_CSR & LPTMR_CSR_TCF_MASK) {
        DEF_BIT_SET(LPTMR0_CSR, LPTMR_CSR_TCF_MASK);

        CPU_CRITICAL_ENTER();
        OSIntEnter();
        CPU_CRITICAL_EXIT();


        if (BSP_OS_TicksToGo != 0) {
            LPTMR0_CNR = 0;
            OSTimeDynTick(BSP_OS_TicksToGo + BSP_OS_UnTick + BSP_OS_LPTICK_TO_OSTICK(LPTMR0_CNR));
            BSP_OS_LastTick += BSP_OS_TicksToGo + BSP_OS_LPTICK_TO_OSTICK(LPTMR0_CNR);

            BSP_OS_TicksToGo = 0;
            BSP_OS_UnTick    = 0;
        } else {
                                                                /* No tasks need to be awakened only keep track of time */
            BSP_OS_LastTick += BSP_OS_LPTICK_TO_OSTICK(LPTMR0_CMR);
            BSP_OS_UnTick   += BSP_OS_LPTICK_TO_OSTICK(LPTMR0_CMR);
        }

        OSIntExit();
    }
}


/*
*********************************************************************************************************
*                                            BSP_OS_TickGet()
*
* Description : Get the OS Tick Counter as if it was running continuously.
*
* Argument(s) : none.
*
* Return(s)   : The effective OS Tick Counter.
*
* Caller(s)   : OS_TaskBlock, OS_TickListInsertDly and OSTimeGet.
*
*               This function is an INTERNAL uC/OS-III function & MUST NOT be called by application
*               function(s).
*
* Note(s)     : none.
*********************************************************************************************************
*/

OS_TICK  BSP_OS_TickGet (void)
{
    OS_TICK  tick;


    tick = BSP_OS_LastTick + BSP_OS_LPTICK_TO_OSTICK(BSP_OS_LP_TickGet());

    return (tick);
}


/*
*********************************************************************************************************
*                                          BSP_OS_TickNextSet()
*
* Description : Set the number of OS Ticks to wait before calling OSTimeTick.
*
* Argument(s) : ticks       number of OS Ticks to wait.
*
* Return(s)   : Number of effective OS Ticks until next OSTimeTick.
*
* Caller(s)   : OS_TickTask and OS_TickListInsert.
*
*               This function is an INTERNAL uC/OS-III function & MUST NOT be called by application
*               function(s).
*
* Note(s)     : none.
*********************************************************************************************************
*/

OS_TICK  BSP_OS_TickNextSet (OS_TICK  ticks)
{
    OS_TICK     lpticks;
    CPU_INT32U  lpt_csr;
    CPU_INT32U  lpt_psr;

                                                                /* Check if OSTimeTick needs to be called.              */
    if (ticks != (OS_TICK)-1) {
                                                                /* Get tick count in LPTMR units.                       */
        lpticks = BSP_OS_OSTICK_TO_LPTICK(ticks);
                                                                /* Adjust for maximum value.                            */
        if (lpticks > DEF_INT_16U_MAX_VAL) {
            BSP_OS_TicksToGo = BSP_OS_LPTICK_TO_OSTICK(DEF_INT_16U_MAX_VAL);
            lpticks          = DEF_INT_16U_MAX_VAL;
        } else {
            BSP_OS_TicksToGo = ticks;
        }
                                                                /* Adjust for invalid value.                            */
        if (lpticks & 0xFFFF == 0) {
            lpticks          = DEF_INT_16U_MAX_VAL;
            BSP_OS_TicksToGo = BSP_OS_LPTICK_TO_OSTICK(DEF_INT_16U_MAX_VAL);
        }
    } else if (ticks == 0) {
        lpticks = 1;
        BSP_OS_TicksToGo = 1;
    } else {
        lpticks = DEF_INT_16U_MAX_VAL-5;
        BSP_OS_TicksToGo = 0;
    }

                                                                /* Save pre-scaler and clock configuration.             */
    lpt_psr = LPTMR0_PSR;
                                                                /* Stop timer.                                          */
    DEF_BIT_CLR(LPTMR0_CSR, LPTMR_CSR_TEN_MASK);

                                                                /* Re-configure timer.                                  */
    lpt_csr  = 0;
    LPTMR0_CSR = lpt_csr;
                                                                /* Restore pre-scaler and clock configuration.          */
    LPTMR0_PSR = lpt_psr;
                                                                /* Set compare value.                                   */
    LPTMR0_CMR = lpticks;
                                                                /* Enable timer.                                        */
    DEF_BIT_SET(LPTMR0_CSR, LPTMR_CSR_TEN_MASK);

                                                                /* Enable interrupts from timer.                        */
    DEF_BIT_SET(LPTMR0_CSR, LPTMR_CSR_TIE_MASK);

    return (BSP_OS_TicksToGo);
}


/*
*********************************************************************************************************
*                                          BSP_OS_LP_TickGet()
*
* Description : Gets the LPTimer state.
*
* Argument(s) : none.
*
* Return(s)   : LPTImer state.
*
* Caller(s)   : BSP_OS_TickNextSet and BSP_OS_TickGet.
*
*               This function is an INTERNAL uC/OS-III function & MUST NOT be called by application
*               function(s).
*
* Note(s)     : none.
*********************************************************************************************************
*/

OS_TICK  BSP_OS_LP_TickGet (void)
{
    OS_TICK  ticks;


    LPTMR0_CNR = 0xDEADBEEF;
    ticks    = LPTMR0_CNR;

    return (ticks);
}

