
#include "arch_main.h"
#include  <ucos_ii.h>

#if (OS_APP_HOOKS_EN > 0)

/*
*********************************************************************************************************
*                                      TASK CREATION HOOK (APPLICATION)
*
* Description : This function is called when a task is created.
*
* Argument(s) : ptcb   is a pointer to the task control block of the task being created.
*
* Note(s)     : (1) Interrupts are disabled during this call.
*********************************************************************************************************
*/

void  App_TaskCreateHook (OS_TCB *ptcb)
{
#if (APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED) && (OS_PROBE_HOOKS_EN > 0)
    OSProbe_TaskCreateHook(ptcb);
#endif
}

/*
*********************************************************************************************************
*                                    TASK DELETION HOOK (APPLICATION)
*
* Description : This function is called when a task is deleted.
*
* Argument(s) : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note(s)     : (1) Interrupts are disabled during this call.
*********************************************************************************************************
*/

void  App_TaskDelHook (OS_TCB *ptcb)
{
    (void)ptcb;
}

/*
*********************************************************************************************************
*                                      IDLE TASK HOOK (APPLICATION)
*
* Description : This function is called by OSTaskIdleHook(), which is called by the idle task.  This hook
*               has been added to allow you to do such things as STOP the CPU to conserve power.
*
* Argument(s) : none.
*
* Note(s)     : (1) Interrupts are enabled during this call.
*********************************************************************************************************
*/

#if OS_VERSION >= 251
void  App_TaskIdleHook (void)
{
	schedule_while_ble_on();
    user_ble_pull(true, NULL);

/*
#if OS_CRITICAL_METHOD == 3u
    OS_CPU_SR  cpu_sr = 0u;
#endif
	OS_ENTER_CRITICAL();

	app_asynch_sleep_proc();
            
	// get the allowed sleep mode
	// time from rwip_power_down() to WFI() must be kept as short as possible!!
	sleep_mode_t sleep_mode = rwip_power_down();
	
	if ((sleep_mode == mode_ext_sleep) || (sleep_mode == mode_deep_sleep)) {
		//power down the radio and whatever is allowed
		arch_goto_sleep(sleep_mode);

		//wait for an interrupt to resume operation
		WFI();

		//resume operation
		arch_resume_from_sleep();
	}
	else if (sleep_mode == mode_idle)
	{
		if (((!BLE_APP_PRESENT) && check_gtl_state()) ||
			(BLE_APP_PRESENT))
			//wait for an interrupt to resume operation
			WFI();
	}
	
	OS_EXIT_CRITICAL();*/
}
#endif

/*
*********************************************************************************************************
*                                        STATISTIC TASK HOOK (APPLICATION)
*
* Description : This function is called by OSTaskStatHook(), which is called every second by uC/OS-II's
*               statistics task.  This allows your application to add functionality to the statistics task.
*
* Argument(s) : none.
*********************************************************************************************************
*/

void  App_TaskStatHook (void)
{
}

/*
*********************************************************************************************************
*                                            TASK RETURN HOOK (APPLICATION)
*
* Description: This function is called if a task accidentally returns.  In other words, a task should
*              either be an infinite loop or delete itself when done.
*
* Arguments  : ptcb      is a pointer to the task control block of the task that is returning.
*
* Note(s)    : none
*********************************************************************************************************
*/


#if OS_VERSION >= 289
void  App_TaskReturnHook (OS_TCB  *ptcb)
{
    (void)ptcb;
}
#endif

/*
*********************************************************************************************************
*                                        TASK SWITCH HOOK (APPLICATION)
*
* Description : This function is called when a task switch is performed.  This allows you to perform other
*               operations during a context switch.
*
* Argument(s) : none.
*
* Note(s)     : (1) Interrupts are disabled during this call.
*
*               (2) It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                   will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the
*                  task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/

#if OS_TASK_SW_HOOK_EN > 0
void  App_TaskSwHook (void)
{
#if (APP_CFG_PROBE_OS_PLUGIN_EN > 0) && (OS_PROBE_HOOKS_EN > 0)
    OSProbe_TaskSwHook();
#endif
}
#endif

/*
*********************************************************************************************************
*                                     OS_TCBInit() HOOK (APPLICATION)
*
* Description : This function is called by OSTCBInitHook(), which is called by OS_TCBInit() after setting
*               up most of the TCB.
*
* Argument(s) : ptcb    is a pointer to the TCB of the task being created.
*
* Note(s)     : (1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/

#if OS_VERSION >= 204
void  App_TCBInitHook (OS_TCB *ptcb)
{
    (void)ptcb;
}
#endif

/*
*********************************************************************************************************
*                                        TICK HOOK (APPLICATION)
*
* Description : This function is called every tick.
*
* Argument(s) : none.
*
* Note(s)     : (1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/

#if OS_TIME_TICK_HOOK_EN > 0
void  App_TimeTickHook (void)
{
#if (APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED) && (OS_PROBE_HOOKS_EN > 0)
    OSProbe_TickHook();
#endif
}
#endif
#endif
