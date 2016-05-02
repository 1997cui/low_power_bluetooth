
#include "user_periph_setup.h"
#include "gpio.h"

#include "tasks.h"

OS_STK led_blink_stack[MaxStkSize];

void led_blink_task(void * p)
{
    OS_EVENT *ble_service_queue = (OS_EVENT *)p;
	
	OSTimeDlyHMSM(0, 0, 0, 500);

    while (1)
    {
        GPIO_SetActive(GPIO_LED_PORT, GPIO_LED_PIN);
        OSTimeDlyHMSM(0, 0, 1, 0);
        GPIO_SetInactive(GPIO_LED_PORT, GPIO_LED_PIN);
        OSTimeDlyHMSM(0, 0, 1, 0);
		OSQPost(ble_service_queue, NULL);
    }
}
