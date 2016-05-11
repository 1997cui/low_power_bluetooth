
#include "tasks.h"

static void *ble_service_queue_space[BLE_SERVICE_QUEUE_LENGTH];

void init_task(void * p)
{
	__enable_irq();
	
	p = p;
	
	OS_CPU_SysTickInit(1000);
	
	OS_EVENT *ble_service_queue = (OS_EVENT *)OSQCreate(ble_service_queue_space, BLE_SERVICE_QUEUE_LENGTH);
	
	OSTaskCreate(ble_service_task, ble_service_queue, &ble_service_stack[MaxStkSize - 1], BLE_SERVICE_TASK_PRIO);
	OSTaskCreate(led_blink_task, ble_service_queue, &led_blink_stack[MaxStkSize - 1], LED_BLINK_TASK_PRIO);
	
	OSTaskDel(OS_PRIO_SELF);
}
