#ifndef __TASKS_H_
#define __TASKS_H_
#include <stddef.h>
#include <stdint.h>
#include "ucos_ii.h"
#include "sps_server_task.h"

#define MaxStkSize 64
#define MaxMessageLength 128
static const INT16U QUEUE_SIZE = 64;


#define INIT_TASK_PRIO 1
void init_task(void *);
static OS_STK init_stack[MaxStkSize];

#define BLE_RECEIVE_TASK_PRIO 2
void ble_receive_task(void *);
static OS_STK ble_receive_stack[MaxStkSize];
static void *ble_receive_queue[QUEUE_SIZE];
static OS_EVENT *ble_receive_q;
static uint8_t temp_message[MaxMessageLength];

#define LED_BLINK_TASK_PRIO 4
void led_blink_task(void *);
static OS_STK led_blink_stack[MaxStkSize];
static void *led_queue[QUEUE_SIZE];
static OS_EVENT *led_q;
static uint8_t led_message[MaxMessageLength];

#define BLE_QUEUE_TASK_PRIO 3
void ble_queue_task(void *);
static OS_STK ble_queue_stack[MaxStkSize];

typedef struct sps_server_data_rx_ind ble_content;

// ble data mailbox
static OS_EVENT *ble_data_ptr;

struct common_data
{
	OS_EVENT *ble_receive_q;
	OS_EVENT *led_q;
	OS_EVENT *ble_data_ptr;
};
static struct common_data _common_data;

#endif
