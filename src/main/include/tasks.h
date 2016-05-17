#ifndef __TASKS_H_
#define __TASKS_H_
#include <stddef.h>
#include "ucos_ii.h"

#define MaxStkSize 64
static const INT16U QUEUE_SIZE = 64;

#define INIT_TASK_PRIO 1
void init_task(void *);
static OS_STK init_stack[MaxStkSize];

#define LED_BLINK_TASK_PRIO 3
void led_blink_task(void *);
static OS_STK led_blink_stack[MaxStkSize];
static void *led_queue[QUEUE_SIZE];

#define BLE_QUEUE_TASK_PRIO 2
void ble_queue_task(void *);
static OS_STK ble_queue_stack[MaxStkSize];

struct ble_content
{
	INT8U name[31];
	INT8U length;
	INT8U content[32];
};

// ble data mailbox
static OS_EVENT *ble_data_ptr;
#endif
