#include "tasks.h"
#include "arch_main.h"
#include <string.h>

void ble_queue_task(void *p)
{
	p = p;
	
	for (;;)
	{
		uint8_t *content = (uint8_t)OSQPend(queue, 100, &err);
		
		if (content != NULL && content[1] == 'l')	//led_task
		{
			strncpy(led_message, content, content[0]);
			OSQPost(led_q, (void *)led_message);
			OSTimeDlyHMSM(0, 0, 1, 0);
		}
	}
}
