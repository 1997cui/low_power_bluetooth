#include "tasks.h"
#include "arch_main.h"
#include <string.h>

void ble_queue_task(void *p)
{
	INT8U LED_NAME[31] = {1, 2, 0};
	OS_EVENT *led_q = OSQCreate(led_queue, QUEUE_SIZE);
	OSTaskCreate(led_blink_task, led_q, &led_blink_stack[MaxStkSize - 1], LED_BLINK_TASK_PRIO);
	
	for (;;)
	{
		OSTaskSuspend(LED_BLINK_TASK_PRIO);
		schedule_while_ble_on();
		struct ble_content attempt = {{1, 2, 0}, 0, {0, 0, 1, 0}};
		INT8U *message = (INT8U *)(&attempt);
		struct ble_content led_message = *((struct ble_content *)message);
		
		if (!strcmp(led_message.name, LED_NAME))
		{
			OSTaskResume(LED_BLINK_TASK_PRIO);
			OSQPost(led_q, (void *)message);
			OSTimeDlyHMSM(0, 0, 1, 0);
		}
	}
	
}
