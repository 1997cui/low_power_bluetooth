
#include "tasks.h"
#include "arch_main.h"
#include <string.h>

void ble_send_task(void *p)
{
	OS_EVENT *led_send_q = ((struct common_data *)p)->led_send_q;
	OS_EVENT *encrypt_read_q = ((struct common_data *)p)->encrypt_read_q;
	INT8U err;
	
	for (;;)
	{
		uint8_t *content;
		
		if ((content = (uint8_t *)OSQPend(led_send_q, 0, &err)) != NULL && err == OS_ERR_NONE)
		{
			user_send_ble_data(content + 1, *content - 1);
		}
		
		if ((content = (uint8_t *)OSQPend(encrypt_read_q, 0, &err)) != NULL && err == OS_ERR_NONE)
		{
			user_send_ble_data(content + 1, *content - 1);
		}
	}
}
