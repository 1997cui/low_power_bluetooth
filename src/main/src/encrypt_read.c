
#include "tasks.h"
#include "arch_main.h"
#include <string.h>
#include "spi_flash.h"
#include "aes.h"

static uint8_t encrypt_read_message[MaxMessageLength];

void encrypt_read_task(void *p)
{
	OS_EVENT *encrypt_read_q = ((struct common_data *)p)->led_send_q;
	OS_EVENT *encrypt_read_command_q = ((struct common_data *)p)->encrypt_read_command_q;
	INT8U err;
	INT32U start_addr;
	INT32U data_addr;
	start_addr = 0x00000;
	
	//读出flash上被加密的内容，存到encrypt_read_message[MaxMessageLength]
	while (1)
	{
		uint8_t *content = (uint8_t *)OSQPend(encrypt_read_command_q, 0, &err);
			
		data_addr = start_addr + 0x1000 * content[2];
		spi_flash_read_data(encrypt_read_message+1, data_addr, MaxMessageLength-2);
		encrypt_read_message[0] = MaxMessageLength-1;
		OSQPost(encrypt_read_q, (void *)encrypt_read_message);
	}
	
}
