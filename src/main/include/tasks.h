
#include <stddef.h>
#include "ucos_ii.h"

#define MaxStkSize 64

#define INIT_TASK_PRIO 1
void init_task(void *);
extern OS_STK init_stack[MaxStkSize];

#define BLE_SERVICE_TASK_PRIO 2
void ble_service_task(void *);
extern OS_STK ble_service_stack[MaxStkSize];
#define BLE_SERVICE_QUEUE_LENGTH 128

#define LED_BLINK_TASK_PRIO 3
void led_blink_task(void *);
extern OS_STK led_blink_stack[MaxStkSize];
