
#include "tasks.h"
#include "arch_main.h"

void ble_service_task(void * p)
{
  OS_EVENT *queue = (OS_EVENT *)p;
	INT8U err;
	
	while (true)
	{
		struct ble_content *content = (struct ble_content *)OSQPend(queue, 100, &err);
		
		if (content != NULL)
		{
			if (content->content[2])
			{
				GPIO_SetActive(GPIO_LED_PORT, GPIO_LED_PIN);
			}
			
			OSTaskSuspend(OS_PRIO_SELF);
		}
	}
}
