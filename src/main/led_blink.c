
#include "user_periph_setup.h"
#include "gpio.h"

#include "tasks.h"

OS_STK led_blink_stack[MaxStkSize];

void led_blink_task(void * p)
{
    p = p;
	
	OSTimeDlyHMSM(0, 0, 0, 500);

    while (1)
    {
        GPIO_SetActive(LED_PORT, LED_PIN);
        OSTimeDlyHMSM(0, 0, 1, 0);
        GPIO_SetInactive(LED_PORT, LED_PIN);
        OSTimeDlyHMSM(0, 0, 1, 0);
    }
}
