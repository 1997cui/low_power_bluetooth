
#include "user_periph_setup.h"
#include "gpio.h"
#include "tasks.h"

void led_blink_task(void * p)
{
	OS_EVENT *led_q = p;
	INT8U err;
	
	while (true)
	{
		uint8_t *content = (uint8_t *)OSQPend(led_q, 100, &err);
		
		if (err == OS_ERR_NONE && content != NULL && content[2] == 'y')
		{
			GPIO_SetActive(GPIO_LED_PORT, GPIO_LED_PIN);
			OSTimeDlyHMSM(0, 0, 1, 0);
		}
	}
}
