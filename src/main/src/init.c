
#include "tasks.h"

void init_task(void * p)
{
	__enable_irq();
	
	p = p;
	
	OS_CPU_SysTickInit(1000);
	
	_common_data.led_q = OSQCreate(led_queue, QUEUE_SIZE);
	_common_data.ble_receive_q = OSQCreate(ble_receive_queue, QUEUE_SIZE);
	OSTaskCreate(led_blink_task, &_common_data, &led_blink_stack[MaxStkSize - 1], LED_BLINK_TASK_PRIO);
	OSTaskCreate(led_blink_task, &_common_data, &ble_queue_stack[MaxStkSize - 1], BLE_QUEUE_TASK_PRIO);
	//OSTaskCreate(ble_receive_task, NULL, &ble_receive_stack[MaxStkSize - 1], BLE_RECEIVE_TASK_PRIO);
	
	OSTaskDel(OS_PRIO_SELF);
}
