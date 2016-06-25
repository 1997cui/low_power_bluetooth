
#include "tasks.h"
#include "arch_main.h"

void ble_send_task(void *p)
{
	OS_EVENT *ble_send_q = ((struct common_data *)p)->ble_send_q;
	INT8U err;
	
	for (;;)
	{
		uint8_t *content;
		
		if ((content = (uint8_t *)OSMboxPend(ble_send_q, 0, &err)) != NULL && err == OS_ERR_NONE)
		{
			user_send_ble_data(content + 1, *content - 1);
		}
	}
}
