#ifndef __TASKS_H_
#define __TASKS_H_
#include <stddef.h>
#include <stdint.h>
#include "ucos_ii.h"
#include "sps_server_task.h"

#define MaxStkSize 64
#define MaxMessageLength 128
#define QUEUE_SIZE 64


#define INIT_TASK_PRIO 1
void init_task(void *);

#define BLE_RECEIVE_TASK_PRIO 2
void ble_receive_task(void *);

#define BLE_QUEUE_TASK_PRIO 3
void ble_queue_task(void *);

#define BLE_SEND_TASK_PRIO 4
void ble_send_task(void *);

#define LED_BLINK_TASK_PRIO 5
void led_blink_task(void *);

typedef struct sps_server_data_rx_ind ble_content;

struct common_data
{
	OS_EVENT *ble_receive_q;
	OS_EVENT *led_q;
	OS_EVENT *ble_data_ptr;
	OS_EVENT *led_send_q;
};

extern struct common_data _common_data;

#endif
