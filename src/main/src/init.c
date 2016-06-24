
#include "tasks.h"
#include "aes.h"

struct common_data _common_data;

OS_STK ble_receive_stack[MaxStkSize];
void *ble_receive_queue[QUEUE_SIZE];

OS_STK led_blink_stack[MaxStkSize];
void *led_queue[QUEUE_SIZE];
void *led_send_queue[QUEUE_SIZE];

OS_STK ble_queue_stack[MaxStkSize];

OS_STK ble_send_stack[MaxStkSize];

OS_STK encrypt_write_stack[MaxStkSize];
void *encrypt_write_queue[QUEUE_SIZE];

OS_STK encrypt_read_stack[MaxStkSize];
void *encrypt_read_queue[QUEUE_SIZE];

void init_task(void * p)
{
	__enable_irq();
	
	p = p;
	
	OS_CPU_SysTickInit(1000);
	
	_common_data.led_q = OSQCreate(led_queue, QUEUE_SIZE);
	_common_data.ble_receive_q = OSQCreate(ble_receive_queue, QUEUE_SIZE);
	_common_data.ble_data_ptr = OSMboxCreate(NULL);
	_common_data.led_send_q = OSQCreate(led_send_queue, QUEUE_SIZE);
	_common_data.encrypt_write_q = OSQCreate(encrypt_write_queue, QUEUE_SIZE);
	_common_data.encrypt_read_q = OSQCreate(encrypt_read_queue, QUEUE_SIZE);
	OSTaskCreate(led_blink_task, &_common_data, &led_blink_stack[MaxStkSize - 1], LED_BLINK_TASK_PRIO);
	OSTaskCreate(ble_queue_task, &_common_data, &ble_queue_stack[MaxStkSize - 1], BLE_QUEUE_TASK_PRIO);
	OSTaskCreate(ble_receive_task, &_common_data, &ble_receive_stack[MaxStkSize - 1], BLE_RECEIVE_TASK_PRIO);
	OSTaskCreate(ble_send_task, &_common_data, &ble_send_stack[MaxStkSize - 1], BLE_SEND_TASK_PRIO);
	OSTaskCreate(encrypt_write_task, &_common_data, &encrypt_write_stack[MaxStkSize - 1], ENCRYPT_WRITE_TASK_PRIO);
	OSTaskCreate(encrypt_read_task, &_common_data, &encrypt_read_stack[MaxStkSize - 1], ENCRYPT_READ_TASK_PRIO);
	
	aes_init(false, NULL);
	
	OSTaskDel(OS_PRIO_SELF);
}
