#ifndef __TASKS_H_
#define __TASKS_H_
#include <stddef.h>
#include <stdint.h>
#include "ucos_ii.h"
#include "sps_server_task.h"

#define MaxStkSize 64
#define MaxMessageLength 32
#define QUEUE_SIZE 32


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

#define ENCRYPT_WRITE_TASK_PRIO 6
void encrypt_write_task(void *);

#define ENCRYPT_READ_TASK_PRIO 7
void encrypt_read_task(void *);

typedef struct sps_server_data_rx_ind ble_content;

struct common_data
{
	OS_EVENT *ble_receive_q;
	OS_EVENT *led_q;
	OS_EVENT *ble_data_ptr;
	OS_EVENT *led_send_q;
	OS_EVENT *encrypt_write_q;
	OS_EVENT *encrypt_read_q;
	OS_EVENT *encrypt_read_command;
};

extern struct common_data _common_data;

#endif
