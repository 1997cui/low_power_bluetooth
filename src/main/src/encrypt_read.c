
#include "tasks.h"
#include "arch_main.h"
#include "spi_flash.h"
#include "aes.h"

static uint8_t encrypt_read_message[MaxMessageLength];
uint8_t encrypt[MaxMessageLength + 6];
uint8_t decrypt[MaxMessageLength + 6];

void encrypt_read_task(void *p)
{
	OS_EVENT *ble_send_q = ((struct common_data *)p)->ble_send_q;
	OS_EVENT *encrypt_read_command_q = ((struct common_data *)p)->encrypt_read_command_q;
	INT8U err;
	INT32U start_addr;
	INT32U data_addr;
	start_addr = 0x00000;
	
	//读出flash上被加密的内容，存到encrypt_read_message[MaxMessageLength]
	while (1)
	{
		uint8_t *content = (uint8_t *)OSMboxPend(encrypt_read_command_q, 0, &err);
			
		data_addr = start_addr + 0x1000 * content[2];
		spi_flash_read_data(encrypt + 3, data_addr, MaxMessageLength-2);
		aes_operation(key, 16, encrypt + 4, encrypt[0] - 1, decrypt + 4, encrypt[0] - 1, 0, NULL, 0);
		rwip_schedule();
		decrypt[3] = encrypt[3];
		u_strncpy(encrypt_read_message, decrypt + 3, decrypt[3]);
		OSMboxPost(ble_send_q, (void *)encrypt_read_message);
	}
	
}
