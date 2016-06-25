
#include "tasks.h"
#include "arch_main.h"

static uint8_t led_message[MaxMessageLength];
static uint8_t encrypt_write_message[MaxMessageLength];
static uint8_t encrypt_read_command_message[MaxMessageLength];

void ble_queue_task(void *p)
{
	OS_EVENT *led_q = ((struct common_data *)p)->led_q;
	OS_EVENT *ble_receive_q = ((struct common_data *)p)->ble_receive_q;
	OS_EVENT *encrypt_write_q = ((struct common_data *)p)->encrypt_write_q;
	OS_EVENT *encrypt_read_command_q = ((struct common_data *)p)->encrypt_read_command_q;
	INT8U err;
	
	for (;;)
	{
		uint8_t *content = (uint8_t *)OSQPend(ble_receive_q, 0, &err);
		
		if (content != NULL && content[1] == 'l')
		{
			u_strncpy(led_message, content, content[0]);
			OSQPost(led_q, (void *)led_message);
		}
		else if (content != NULL && content[1] == 0x08)
		{
			u_strncpy(encrypt_write_message, content, content[0]);
			OSQPost(encrypt_write_q, (void *)encrypt_write_message);
		}
		else if (content != NULL && content[1] == 0x09)
		{
			u_strncpy(encrypt_read_command_message, content, content[0]);
			OSQPost(encrypt_read_command_q, (void *)encrypt_read_command_message);
		}
	}
}
