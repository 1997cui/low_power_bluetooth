
#include "tasks.h"
#include "arch_main.h"

static uint8_t message[MaxMessageLength];

void ble_queue_task(void *p)
{
	OS_EVENT *led_q = ((struct common_data *)p)->led_q;
	OS_EVENT *ble_receive_q = ((struct common_data *)p)->ble_receive_q;
	OS_EVENT *encrypt_write_q = ((struct common_data *)p)->encrypt_write_q;
	OS_EVENT *encrypt_read_command_q = ((struct common_data *)p)->encrypt_read_command_q;
	INT8U err;
	
	for (;;)
	{
		uint8_t *content = (uint8_t *)OSMboxPend(ble_receive_q, 0, &err);
		if (!content || err) continue;
		
		u_strncpy(message, content, content[0]);
		switch (content[1])
		{
			case 'l':  OSMboxPost(led_q,                  (void *)message); break;
			case 0x08: OSMboxPost(encrypt_write_q,        (void *)message); break;
			case 0x09: OSMboxPost(encrypt_read_command_q, (void *)message); break;
		}
	}
}
