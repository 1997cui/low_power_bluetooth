
#include "tasks.h"

void init_task(void * p)
{
	__enable_irq();
	
	p = p;
	
	OS_CPU_SysTickInit(1000);
	
	OS_EVENT *led_q = OSQCreate(led_queue, QUEUE_SIZE);
	OSTaskCreate(led_blink_task, led_q, &led_blink_stack[MaxStkSize - 1], LED_BLINK_TASK_PRIO);
	OSTaskCreate(ble_queue_task, led_q, &ble_queue_stack[MaxStkSize - 1], BLE_QUEUE_TASK_PRIO);
	
	OSTaskDel(OS_PRIO_SELF);
}
