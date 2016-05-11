
#include "user_periph_setup.h"
#include "gpio.h"

#include "tasks.h"

void led_blink_task(void * p)
{
    OS_EVENT *ble_service_queue = (OS_EVENT *)p;
	
    GPIO_SetActive(GPIO_LED_PORT, GPIO_LED_PIN);

    while (1)
    {
        OSTimeDlyHMSM(0, 0, 1, 0);
		OSQPost(ble_service_queue, NULL);
    }
}
