
#include "user_periph_setup.h"
#include "gpio.h"
#include "tasks.h"
#include "user_spss.h"

static uint8_t led_send_message[MaxMessageLength];

void led_blink_task(void * p)
{
	OS_EVENT *led_q = ((struct common_data *)p)->led_q;
	OS_EVENT *ble_send_q = ((struct common_data *)p)->ble_send_q;
	INT8U err, cnt = 0;
	
	while (true)
	{
		uint8_t *content = (uint8_t *)OSMboxPend(led_q, 0, &err);
		
		if (err == OS_ERR_NONE && content != NULL && content[4] == 'y')
		{
			GPIO_SetActive(GPIO_LED_PORT, GPIO_LED_PIN);
			led_send_message[0] = 2;
			led_send_message[1] = '0' + cnt % 10;
			cnt++;
			OSMboxPost(ble_send_q, (void *)led_send_message);
		}
	}
}
