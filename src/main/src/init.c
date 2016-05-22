
#include "tasks.h"

void init_task(void * p)
{
	__enable_irq();
	
	p = p;
	
	OS_CPU_SysTickInit(1000);
	
	led_q = OSQCreate(led_queue, QUEUE_SIZE);
	ble_receive_q = OSQCreate(ble_receive_queue, QUEUE_SIZE);
	OSTaskCreate(led_blink_task, led_q, &led_blink_stack[MaxStkSize - 1], LED_BLINK_TASK_PRIO);
	//OSTaskCreate(ble_queue_task, NULL, &ble_queue_stack[MaxStkSize - 1], BLE_QUEUE_TASK_PRIO);
	//OSTaskCreate(ble_receive_task, NULL, &ble_receive_stack[MaxStkSize - 1], BLE_RECEIVE_TASK_PRIO);
	
	OSTaskDel(OS_PRIO_SELF);
}
