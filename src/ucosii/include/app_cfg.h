
#ifndef  APP_CFG_MODULE_PRESENT
#define  APP_CFG_MODULE_PRESENT


/*
*********************************************************************************************************
*                                       ADDITIONAL uC/MODULE ENABLES
*********************************************************************************************************
*/

#define  APP_CFG_PROBE_COM_EN                       DEF_DISABLED
#define  APP_CFG_SERIAL_EN                          DEF_DISABLED


/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define  APP_CFG_TASK_START_PRIO                          2u

#define  APP_CFG_TASK_LED_PRIO                            4u
#define  APP_CFG_TASK_LED_SEM_PRIO                        5u
#define  APP_CFG_TASK_LED_QUE_PRIO                        6u

#define  APP_CFG_TASK_FP_EQ_PRIO                          7u

#define  OS_TASK_TMR_PRIO                        (OS_LOWEST_PRIO - 2u)


/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*********************************************************************************************************
*/

#define  APP_CFG_TASK_START_STK_SIZE                    256u

#define  APP_CFG_TASK_LED1_STK_SIZE                     128u
#define  APP_CFG_TASK_LED2_STK_SIZE                     128u
#define  APP_CFG_TASK_LED3_STK_SIZE                     128u
#define  APP_CFG_TASK_LED4_STK_SIZE                     128u

#define  APP_CFG_TASK_FP_EQ_STK_SIZE                    512u


/*
*********************************************************************************************************
*                                       TRACE / DEBUG CONFIGURATION
*********************************************************************************************************
*/

#ifndef  TRACE_LEVEL_OFF
#define  TRACE_LEVEL_OFF                           0
#endif

#ifndef  TRACE_LEVEL_INFO
#define  TRACE_LEVEL_INFO                          1
#endif

#ifndef  TRACE_LEVEL_DBG
#define  TRACE_LEVEL_DBG                           2
#endif

#ifndef  TRACE_LEVEL_LOG
#define  TRACE_LEVEL_LOG                           3
#endif

//#include <cpu.h>
//void  App_SerPrintf (CPU_CHAR  *p_fmt, ...);

#define  APP_CFG_TRACE_LEVEL                    TRACE_LEVEL_DBG
//#define  APP_CFG_TRACE                          App_SerPrintf
#define  APP_CFG_TRACE                          printf

#define  BSP_CFG_TRACE_LEVEL                    TRACE_LEVEL_OFF
#define  BSP_CFG_TRACE                          printf

#define  APP_TRACE_INFO(x)               ((APP_CFG_TRACE_LEVEL >= TRACE_LEVEL_INFO)  ? (void)(APP_CFG_TRACE x) : (void)0)
#define  APP_TRACE_DBG(x)                ((APP_CFG_TRACE_LEVEL >= TRACE_LEVEL_DBG)   ? (void)(APP_CFG_TRACE x) : (void)0)

#define  BSP_TRACE_INFO(x)               ((BSP_CFG_TRACE_LEVEL  >= TRACE_LEVEL_INFO) ? (void)(BSP_CFG_TRACE x) : (void)0)
#define  BSP_TRACE_DBG(x)                ((BSP_CFG_TRACE_LEVEL  >= TRACE_LEVEL_DBG)  ? (void)(BSP_CFG_TRACE x) : (void)0)

#endif
