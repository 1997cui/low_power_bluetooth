
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
		
		if (content != NULL)
		{
			ble_content _ble_content;										//这里是否需要改成静态变量
			_ble_content.length = content[0] - 1;
			strncpy(_ble_content.data, (const char *)(&content[1]), content[0] - 1);
		}
	}
}
