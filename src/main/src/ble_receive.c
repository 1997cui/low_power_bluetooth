
#include "tasks.h"
#include "arch_main.h"

static uint8_t temp_message[MaxMessageLength];

void ble_receive_task(void *p)
{
	OS_EVENT *ble_receive_q = ((struct common_data *)p)->ble_receive_q;
	OS_EVENT *ble_data_ptr = ((struct common_data *)p)->ble_data_ptr;
	
	for (;;)
	{
		uint8_t err;
		ble_content *message_ptr;
		uint16_t sum_length = 0;
		
		do
		{
			message_ptr = (ble_content *)OSMboxPend(ble_data_ptr, 0, &err);
			if (!message_ptr || err)
				continue;
			if (message_ptr->length)
			{
				u_strncpy(&temp_message[sum_length], message_ptr->data, message_ptr->length);
				sum_length += message_ptr->length;
				
				if (sum_length >= temp_message[0])
				{
					sum_length = 0;
					OSMboxPost(ble_receive_q, (void *)temp_message);
				}
			}
		} while (sum_length);
	}
}
