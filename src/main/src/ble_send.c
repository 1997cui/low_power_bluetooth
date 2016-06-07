
#include "tasks.h"
#include "arch_main.h"
#include <string.h>

void ble_send_task(void *p)
{
	OS_EVENT *led_send_q = ((struct common_data *)p)->led_send_q;
	INT8U err;
	
	for (;;)
	{
		uint8_t *content = (uint8_t *)OSQPend(led_send_q, 0, &err);
		
		if (err == OS_ERR_NONE && content != NULL)
			user_send_ble_data(content + 1, *content - 1);
	}
}
