
#include "tasks.h"

struct common_data _common_data;

OS_STK ble_receive_stack[MaxStkSize];
void *ble_receive_queue[QUEUE_SIZE];

OS_STK led_blink_stack[MaxStkSize];
void *led_queue[QUEUE_SIZE];

OS_STK ble_queue_stack[MaxStkSize];

void init_task(void * p)
{
	__enable_irq();
	
	p = p;
	
	OS_CPU_SysTickInit(1000);
	
	_common_data.led_q = OSQCreate(led_queue, QUEUE_SIZE);
	_common_data.ble_receive_q = OSQCreate(ble_receive_queue, QUEUE_SIZE);
	_common_data.ble_data_ptr = OSMboxCreate(NULL);
	OSTaskCreate(led_blink_task, &_common_data, &led_blink_stack[MaxStkSize - 1], LED_BLINK_TASK_PRIO);
	OSTaskCreate(ble_queue_task, &_common_data, &ble_queue_stack[MaxStkSize - 1], BLE_QUEUE_TASK_PRIO);
	OSTaskCreate(ble_receive_task, &_common_data, &ble_receive_stack[MaxStkSize - 1], BLE_RECEIVE_TASK_PRIO);
	
	OSTaskDel(OS_PRIO_SELF);
}
