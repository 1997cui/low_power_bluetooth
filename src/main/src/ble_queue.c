#include "tasks.h"
#include "arch_main.h"
#include <string.h>

void ble_queue_task(void *p)
{
	OS_EVENT *led_q = ((struct common_data *)p)->led_q;
	OS_EVENT *ble_receive_q = ((struct common_data *)p)->ble_receive_q;
	INT8U err;
	
	for (;;)
	{
		uint8_t *content = (uint8_t *)OSQPend(ble_receive_q, 100, &err);
		
		if (content != NULL && content[1] == 'l')	//led_task
		{
			strncpy(led_message, content, content[0]);
			OSQPost(led_q, (void *)led_message);
			OSTimeDlyHMSM(0, 0, 1, 0);
		}
	}
}
