
#include "tasks.h"
#include "arch_main.h"
#include <string.h>

enum {UNFINISHED, FINISHED};

void ble_receive_task(void *p)
{
	p = p;
	
	for (;;)
	{
		uint8_t state = UNFINISHED, err;
		ble_content *message_ptr, ble_message;
		uint16_t sum_length = 0;
		
		while (state == UNFINISHED)
		{
			if ((message_ptr = (ble_content *)OSMboxPend(ble_data_ptr, 100, &err)) == NULL)
			{
				continue;
			}
			
			ble_message = *message_ptr;
			
			if (ble_message.length == 0)
			{
				continue;
			}
			else
			{
				strncpy(&temp_message[sum_length], ble_message.data, ble_message.length);
				sum_length += ble_message.length;
				
				if (sum_length >= temp_message[0])
				{
					state = FINISHED;
					sum_length = 0;
					OSQPost(ble_receive_q, (void *)temp_message);
				}
			}
		}
		
		OSTimeDlyHMSM(0, 0, 1, 0);
	}
}
