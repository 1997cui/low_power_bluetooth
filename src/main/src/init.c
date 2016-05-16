
#include "tasks.h"

void init_task(void * p)
{
	__enable_irq();
	
	p = p;
	
	OS_CPU_SysTickInit(1000);
	
	OSTaskCreate(ble_queue_task, NULL, &ble_queue_stack[MaxStkSize - 1], BLE_QUEUE_TASK_PRIO);
	
	OSTaskDel(OS_PRIO_SELF);
}
