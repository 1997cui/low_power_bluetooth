
#include "user_periph_setup.h"
#include "tasks.h"
#include "rwip.h"
#include "user_spss.h"
#include "spi_flash.h"
#include "aes.h"


uint8_t key[16] = {0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01};//{0x06,0xa9,0x21,0x40,0x36,0xb8,0xa1,0x5b,0x51,0x2e,0x03,0xd5,0x34,0x12,0x00,0x06};
uint8_t temp[MaxMessageLength - 2];
uint8_t message[MaxMessageLength - 2];

void encrypt_write_task(void * p)
{
	OS_EVENT *encrypt_write_q = ((struct common_data *)p)->encrypt_write_q;
	INT8U err;
	INT8U buffer_rd[4];
	INT32U start_addr;
	INT32U data_addr;
	/*spi_flash_read_data(buffer_rd, 0x00, 2);
	if ((buffer_rd[0] == (INT8U)0x70) && (buffer_rd[1] == (INT8U)0x50)) 
	{
		spi_flash_read_data(buffer_rd, 6, 2);
		start_addr = 8 + buffer_rd[0] << 8 + buffer_rd[1];
	} else
	{
			start_addr = 16;
	}
	*/
	start_addr = 0x10000;
	
	while (true)
	{
		uint8_t *content = (uint8_t *)OSQPend(encrypt_write_q, 0, &err);
		
		
		if (content != NULL)
		{
			message[0] = content[0] - 2;
			u_strncpy(message + 1, content + 3, content[0] - 3);
			aes_operation(key, 16, message, message[0], temp, message[0], 1, NULL, 0);
			data_addr = start_addr + 0x1000 * content[2];
			spi_flash_block_erase(data_addr, SECTOR_ERASE);
			spi_flash_write_data(temp, data_addr, content[0] - 3);
		}
		
		//写入flash，假定content[2]开始是待加密的数据，content每位一个字 
		//假设content[2]是所要写入的sector号，从0开始到15号结束
		
	
		//测试
		/*int length = content[0] > 34 ? 32 : content[0] - 2;
		aes_operation(key, 16, content + 2, length, temp, length, 1, NULL, 0);
		rwip_schedule();
		aes_operation(key, 16, temp, length, result, length, 0, NULL, 0);
		rwip_schedule();
		user_send_ble_data(result, 16);*/
		//测试结束
		
	}
}
