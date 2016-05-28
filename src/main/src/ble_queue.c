
#include "tasks.h"
#include "arch_main.h"
#include <string.h>

static uint8_t led_message[MaxMessageLength];

void ble_queue_task(void *p)
{
	OS_EVENT *led_q = ((struct common_data *)p)->led_q;
	OS_EVENT *ble_receive_q = ((struct common_data *)p)->ble_receive_q;
	INT8U err;
	
	for (;;)
	{
		uint8_t *content = (uint8_t *)OSQPend(ble_receive_q, 0, &err);
		
		if (content != NULL && content[1] == 'l')
		{
			strncpy(led_message, content, content[0]);
			OSQPost(led_q, (void *)led_message);
		}
	}
}
