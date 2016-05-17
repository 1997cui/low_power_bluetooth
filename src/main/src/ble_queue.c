#include "tasks.h"
#include "arch_main.h"
#include <string.h>

static struct ble_content attempt = {{1, 2, 0}, 0, {0, 0, 1, 0}};

void ble_queue_task(void *p)
{
	OS_EVENT *queue = (OS_EVENT *)p;
	INT8U LED_NAME[31] = {1, 2, 0};
	
	for (;;)
	{
		INT8U *message = (INT8U *)(&attempt);
		struct ble_content led_message = *((struct ble_content *)message);
		
		if (!strcmp(led_message.name, LED_NAME))
		{
			OSQPost(queue, message);
			OSTimeDlyHMSM(0, 0, 1, 0);
		}
	}
}
