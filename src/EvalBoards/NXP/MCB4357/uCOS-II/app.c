/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                             (c) Copyright 2013; Micrium, Inc.; Weston, FL
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
*                                            EXAMPLE CODE
*
*                                            NXP LPC4357
*                                               on the
*                                            Keil MCB4357
*
* Filename      : app.c
* Version       : V1.00.00
* Programmer(s) : MD
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <lib_math.h>

#include  <ucos_ii.h>

#include  <app_cfg.h>
#include  <bsp.h>

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  QUEUE_SIZE                          1

#define  APP_TASK_EQ_ITERATION_NBR          16


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

static  OS_STK          AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE];

static  OS_STK          AppTaskLEDStk[APP_CFG_TASK_LED2_STK_SIZE];
static  OS_STK          AppTaskSemLEDStk[APP_CFG_TASK_LED3_STK_SIZE];
static  OS_STK          AppTaskQLEDStk[APP_CFG_TASK_LED4_STK_SIZE];

static  OS_STK          AppTaskEqFpStk[APP_CFG_TASK_FP_EQ_STK_SIZE];

        OS_TMR         *AppSemTmr;
        OS_EVENT       *AppLEDSemEvent;

        OS_TMR         *AppQTmr;
        OS_EVENT       *AppLEDQEvent;

        void           *AppLEDNbr[QUEUE_SIZE];                  /* Keeps track of current LED value for Queue           */        


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppTaskStart              (void       *p_arg);
static  void  AppTaskCreate             (void);
static  void  AppEventCreate            (void);

static  void  AppTaskLED                (void        *p_arg);   /* Toggle timer for LED 2                               */
static  void  AppTaskSemLED             (void        *p_arg);   /* Toggle timer for LED 3                               */
static  void  AppTaskQLED               (void        *p_arg);   /* Toggle timer for LED 4                               */

static  void  AppTaskEqFP               (void        *p_arg);   /* Floating Point Equation Task                         */

                                                                /* Timer callback functions for LED applications        */
        void  AppSemTmrCallBack         (OS_TMR *p_tmr,
                                         void   *p_arg);

        void  AppQTmrCallBack           (OS_TMR *p_tmr,
                                         void   *p_arg);


/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

int  main(void)
{
    CPU_INT08U  os_err;
        

    BSP_PreInit();                                              /* Initialize the interrupts                            */

    CPU_Init();

    OSInit();                                                   /* Initialize "uC/OS-II, The Real-Time Kernel"          */

    OSTaskCreateExt((void (*)(void *)) AppTaskStart,            /* Create the start task                                */
                    (void           *) 0,
                    (OS_STK         *)&AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE - 1],
                    (INT8U           ) APP_CFG_TASK_START_PRIO,
                    (INT16U          ) APP_CFG_TASK_START_PRIO,
                    (OS_STK         *)&AppTaskStartStk[0],
                    (INT32U          ) APP_CFG_TASK_START_STK_SIZE,
                    (void           *) 0,
                    (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP));

#if (OS_TASK_NAME_EN > 0)
    OSTaskNameSet((INT8U     ) APP_CFG_TASK_START_PRIO,
                  (INT8U    *)"Start_Task",
                  (INT8U    *)&os_err);
#endif

    OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II)   */

    return (1);
}


/*
*********************************************************************************************************
*                                          AppTaskStart()
*
* Description : The startup task.  The uC/OS-II ticker should only be initialize once multitasking starts.
*
* Argument(s) : p_arg       Argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Note(s)     : (1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                   used.  The compiler should not generate any code for this statement.
*
*               (2) Interrupts are enabled once the task starts because the I-bit of the CCR register was
*                   set to 0 by 'OSTaskCreate()'.
*********************************************************************************************************
*/

static  void  AppTaskStart (void *p_arg)
{
    CPU_INT32U  cnts;

    
    BSP_PostInit();

    cnts = BSP_CPU_ClkGet() / OS_TICKS_PER_SEC;
    OS_CPU_SysTickInit(cnts);                                   /* Initialize the SysTick.                              */

    Mem_Init();                                                 /* Initialize the Memory Managment module               */
    Math_Init();                                                /* Initialize the Mathematical module                   */

#if (OS_TASK_STAT_EN > 0)
    OSStatInit();                                               /* Determine CPU capacity                               */
#endif

#if (APP_CFG_SERIAL_EN == DEF_ENABLED)
    App_SerialInit();
#endif

    AppEventCreate();                                           /* Create Application Events                            */

//    APP_TRACE_INFO(("Creating Application Tasks...\n\r"));
    AppTaskCreate();                                            /* Create application tasks                             */


    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
        BSP_LED_Toggle(1);
        OSTimeDlyHMSM(0, 0, 1, 0);
    }
}


/*
*********************************************************************************************************
*                                      AppEventCreate()
*
* Description : Create the application Events
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : App_TasStart()
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  AppEventCreate (void)
{
    CPU_INT08U  os_err;

    AppLEDSemEvent = OSSemCreate(0);                                /* Activate semaphore event for use with sem task   */

#if (OS_EVENT_NAME_EN > 0)
    OSEventNameSet((OS_EVENT    *)AppLEDSemEvent,
                   (INT8U       *)"LED Semaphore",
                   (INT8U       *)&os_err);
#endif

    AppLEDQEvent = OSQCreate((void  *)&AppLEDNbr,               /* Create queue event for use with Q task               */
                             (INT8U  )QUEUE_SIZE);

#if (OS_EVENT_NAME_EN > 0)
    OSEventNameSet((OS_EVENT    *)AppLEDQEvent,
                   (INT8U       *)"LED Q Message",
                   (INT8U       *)&os_err);
#endif


    AppSemTmr = OSTmrCreate((INT32U          ) 4,               /* Delay of timer                                       */
                            (INT32U          ) 400,             /* Period of timer                                      */
                            (INT8U           ) OS_TMR_OPT_PERIODIC,
                            (OS_TMR_CALLBACK ) AppSemTmrCallBack,
                            (void           *) 0,
                            (INT8U          *) "LEDTimer Sem",
                            (INT8U          *) &os_err);

    AppQTmr   = OSTmrCreate((INT32U            )1,             
                            (INT32U            )5,
                            (INT8U             )OS_TMR_OPT_PERIODIC,
                            (OS_TMR_CALLBACK   )AppQTmrCallBack,
                            (void             *)0,
                            (INT8U            *)"Blink LED Q timer",
                            (INT8U            *)&os_err);
}


/*
*********************************************************************************************************
*                                      AppTaskCreate()
*
* Description : Create the application tasks.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : App_TaskStart()
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  AppTaskCreate (void)
{
#if (OS_TASK_NAME_EN > 0)
    CPU_INT08U  os_err;
#endif

    OSTaskCreateExt((void (*)(void   *))AppTaskLED,             /* Create the task for LED2 to blink                    */
                    (void            *) 0,
                    (OS_STK          *)&AppTaskLEDStk[APP_CFG_TASK_LED2_STK_SIZE - 1],
                    (INT8U            ) APP_CFG_TASK_LED_PRIO,
                    (INT16U           ) APP_CFG_TASK_LED_PRIO,
                    (OS_STK          *)&AppTaskLEDStk[0],
                    (INT32U           ) APP_CFG_TASK_LED2_STK_SIZE,
                    (void            *) 0,
                    (INT16U           ) OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);


#if (OS_TASK_NAME_EN > 0)
    OSTaskNameSet((INT8U  )APP_CFG_TASK_LED_PRIO,
                  (INT8U *)"AppTaskLED",
                  (INT8U *)&os_err);
#endif

    OSTaskCreateExt((void (*)(void   *))AppTaskSemLED,          /* Create the task for LED3 semaphore blinking          */
                    (void            *) 0,
                    (OS_STK          *)&AppTaskSemLEDStk[APP_CFG_TASK_LED3_STK_SIZE - 1],
                    (INT8U            ) APP_CFG_TASK_LED_SEM_PRIO,
                    (INT16U           ) APP_CFG_TASK_LED_SEM_PRIO,
                    (OS_STK          *)&AppTaskSemLEDStk[0],
                    (INT32U           ) APP_CFG_TASK_LED3_STK_SIZE,
                    (void            *) 0,
                    (INT16U           )OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

#if  (OS_TASK_NAME_EN > 0)
     OSTaskNameSet((INT8U   )APP_CFG_TASK_LED_SEM_PRIO,
                   (INT8U  *)"App Task LED Sem",
                   (INT8U  *)&os_err);
#endif

    OSTaskCreateExt((void (*)(void   *))AppTaskQLED,            /* Task creation for LED 4 queue control with LED 3 too */
                    (void            *) 0,
                    (OS_STK          *)&AppTaskQLEDStk[APP_CFG_TASK_LED4_STK_SIZE - 1],
                    (INT8U            ) APP_CFG_TASK_LED_QUE_PRIO,
                    (INT16U           ) APP_CFG_TASK_LED_QUE_PRIO,
                    (OS_STK          *)&AppTaskQLEDStk[0],
                    (INT32U           ) APP_CFG_TASK_LED4_STK_SIZE,
                    (void            *) 0,
                    (INT16U           ) OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

#if  (OS_TASK_NAME_EN > 0)
     OSTaskNameSet((INT8U   )APP_CFG_TASK_LED_QUE_PRIO,
                   (INT8U  *)"App Task LED Q",
                   (INT8U  *)&os_err);
#endif

    OSTaskCreateExt((void (*)(void   *))AppTaskEqFP,            /* Task creation for Floating Point Test Function       */
                    (void            *) 0,
                    (OS_STK          *)&AppTaskEqFpStk[APP_CFG_TASK_FP_EQ_STK_SIZE - 1],
                    (INT8U            ) APP_CFG_TASK_FP_EQ_PRIO,
                    (INT16U           ) APP_CFG_TASK_FP_EQ_PRIO,
                    (OS_STK          *)&AppTaskEqFpStk[0],
                    (INT32U           ) APP_CFG_TASK_FP_EQ_STK_SIZE,
                    (void            *) 0,
                    (INT16U           ) OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);

#if  (OS_TASK_NAME_EN > 0)
     OSTaskNameSet((INT8U   )APP_CFG_TASK_LED_QUE_PRIO,
                   (INT8U  *)"App Task Float Point Test",
                   (INT8U  *)&os_err);
#endif
}


/*
*********************************************************************************************************
*                                         AppTaskLED()
*
* Description : Task to activate and toggle LED2 after timer tick system expires.
*
* Argument(s) : p_arg   is the argument passed to 'AppTaskLED()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  AppTaskLED(void *p_arg)
{
    (void)p_arg;

    while(DEF_TRUE) {
        BSP_LED_Toggle(2);
        OSTimeDlyHMSM(0, 0, 0, 300);
    }
}


/*
*********************************************************************************************************
*                                         AppTaskSemLED()
*
* Description : Toggle LED3 using semaphore services.
*
* Argument(s) : p_arg   is the argument passed to 'AppTaskSemLED()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : Calls the LED function to activate LED 3.
*********************************************************************************************************
*/


static  void  AppTaskSemLED(void *p_arg)
{
    CPU_BOOLEAN  status;
    CPU_BOOLEAN  led_toggle;
    INT8U        os_err;


    (void)p_arg;
    
    led_toggle = 0;                                             /* Initialize to turn on LED 3 first                    */

    while (DEF_TRUE) {
        status = OSTmrStart(AppSemTmr, &os_err);
        if (status != DEF_OK) {
            while (DEF_TRUE) {
                ;
            }
        } else {
            OSSemPend((OS_EVENT *)AppLEDSemEvent,
                      (INT32U    )0,
                      (INT8U    *)&os_err);
        }
        if (led_toggle == DEF_TRUE) {
            BSP_LED_Toggle(4);
        } else {
            BSP_LED_Toggle(3);
        }

        led_toggle = !led_toggle;        
        
    }
}


/*
*********************************************************************************************************
*                                         AppSemTmrCallBack()
*
* Description : Task to activate and toggle LED2 after timer tick system expires.
*
* Argument(s) : p_tmr   is the argument passed with the Timer to which this callback belongs
*               
*               p_arg   Pointer to calling object
*
*********************************************************************************************************
*/

void  AppSemTmrCallBack (OS_TMR   *p_tmr,
                          void     *p_arg)
{
    OSSemPost((OS_EVENT *)AppLEDSemEvent);
}


/*
*********************************************************************************************************
*                                         AppTaskQLED()
*
* Description : Toggle LED3 and LED4 using a message queue service.
*
* Argument(s) : p_arg   is the argument passed to 'AppTaskQLED()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : Calls the LED function to activate LED Queue after timer expires.
*********************************************************************************************************
*/

static  void  AppTaskQLED (void *p_arg)
{
    CPU_INT32U     *p_msg;
    CPU_INT08U      led_nbr;
    CPU_BOOLEAN     status;
    INT8U           os_err;
    CPU_INT08U      cnt; 


    (void)p_arg;

    status = OSTmrStart(AppQTmr, &os_err);
    if (status != DEF_OK) {                                     /* Check if timer has started correctly                 */
        while (DEF_TRUE) {
                ;
        }
    }
    
    while (DEF_TRUE) {
        switch(led_nbr) {
            case 0:                                             /* Case for 1st LED sequence                            */
                 for(cnt = 5; cnt < 9; cnt++) {
                     BSP_LED_On(cnt);
                     OSTimeDlyHMSM(0, 0, 0, 50);
                 }
                 break;
                 
                 
            case 1:                                             /* Case for 2nd LED sequence                            */
                 for(cnt = 8; cnt > 4; cnt--) {
                     BSP_LED_Off(cnt);
                     OSTimeDlyHMSM(0, 0, 0, 50);
                 }
                 break;
                 
                 
            case 2:                                             /* Case for 3rd LED sequence                            */
                 for(cnt = 8; cnt > 4; cnt--) {
                     BSP_LED_On(cnt);
                     OSTimeDlyHMSM(0, 0, 0, 50);
                 }
                 break;


            case 3:                                             /* Case for 4th LED sequence                            */
                 for(cnt = 5; cnt < 9; cnt++) {
                     BSP_LED_Off(cnt);
                     OSTimeDlyHMSM(0, 0, 0, 50);
                 }                
                 break;
            
            
            default:
                 break;
        }

        p_msg = (CPU_INT32U *)(OSQPend((OS_EVENT    *)AppLEDQEvent,
                                       (INT8U        )0,
                                       (INT8U       *)&os_err));

        if (os_err == OS_ERR_NONE) {
            led_nbr++;
            led_nbr %= 4;
        }
    }    
}


/*
*********************************************************************************************************
*                                         AppQTmrCallBack()
*
* Description : Task to activate and toggle LED2 after timer tick system expires.
*
* Argument(s) : p_tmr   is the argument passed with the Timer to which this callback belongs
*               
*               p_arg   Pointer to calling object
*
*********************************************************************************************************
*/

void  AppQTmrCallBack(OS_TMR *p_tmr,
                         void   *p_arg)
{
   OSQPost((OS_EVENT   *)AppLEDQEvent,
            (void       *)&AppLEDNbr);
}


/*
*********************************************************************************************************
*                                             AppTaskEqFP()
*
* Description : This task performs several simple float operations that demonstrate the
*               floating point unit is working correctly.
*
* Argument(s) : p_arg   is the argument passed to 'App_TaskEqFp' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Note(s)     : Simply set a breakpoint inside the function to check the output and if the FPU registers
*               are being properly modified.
*********************************************************************************************************
*/

void  AppTaskEqFP (void  *p_arg)
{
    CPU_FP32    a;
    CPU_FP32    b;
    CPU_FP32    c;


    a = 3.4;                                                    /* Basic arith operations to test FPU                   */
    b = 5.7;
    c = (a + b) / 2.00;

    if (a > b) {
        c = 3.6;
    } else {
        c = 3.2;
    }
        
    if (c > b) {
        b = 4.56;
    }
}
