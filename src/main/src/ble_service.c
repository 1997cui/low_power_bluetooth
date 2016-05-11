
#include "tasks.h"
#include "arch_main.h"

void ble_service_task(void * p)
{
    OS_EVENT *ble_service_queue = (OS_EVENT *)p;
	
	INT8U err;
	
	while (true)
	{
		schedule_while_ble_on();
		OSQPend(ble_service_queue, 100, &err);
	}
}
