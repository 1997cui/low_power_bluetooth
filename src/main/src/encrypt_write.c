
#include "user_periph_setup.h"
#include "tasks.h"
#include "rwip.h"
#include "user_spss.h"
#include "spi_flash.h"
#include "aes.h"
#include "util.h"

#include "file.h"


uint8_t key[16] = {0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01};//{0x06,0xa9,0x21,0x40,0x36,0xb8,0xa1,0x5b,0x51,0x2e,0x03,0xd5,0x34,0x12,0x00,0x06};
//uint8_t encrypted[MaxMessageLength - 2];
//uint8_t message[MaxMessageLength - 2];
static flash_file file;

void encrypt_write_task(void * p)
{
	OS_EVENT *encrypt_write_q = ((struct common_data *)p)->encrypt_write_q;
	INT8U err;
	INT32U start_addr;
	INT32U data_addr;
	INT32U write_byte;
	/*
	INT8U buffer_rd[4];
	spi_flash_read_data(buffer_rd, 0x00, 2);
	if ((buffer_rd[0] == (INT8U)0x70) && (buffer_rd[1] == (INT8U)0x50)) 
	{
		spi_flash_read_data(buffer_rd, 6, 2);
		start_addr = 8 + buffer_rd[0] << 8 + buffer_rd[1];
	} else
	{
			start_addr = 16;
	}
	*/
	start_addr = 0x00000;
	
	while (true)
	{
		uint8_t *content = (uint8_t *)OSMboxPend(encrypt_write_q, 0, &err);
		
		
		if (content != NULL)
		{
			/*
			message[0] = content[0] - 2;
			u_strncpy(message + 1, content + 3, content[0] - 3);
			aes_operation(key, 16, message + 1, message[0] - 1, encrypted + 1, ((message[0]-1-1)/16+1)*16, 1, NULL, 0);
			rwip_schedule();
			encrypted[0] = message[0];
			data_addr = start_addr + 0x1000 * content[2];
			err = spi_flash_block_erase(data_addr, SECTOR_ERASE);
			if (err != ERR_OK) __asm("BKPT #0\n");
			//spi_flash_write_data(&content[3], data_addr, content[0] - 3);
			write_byte = spi_flash_write_data(encrypted, data_addr, ((message[0]-1-1)/16+1)*16+1);
			if (write_byte != (1+((message[0]-1-1)/16+1)*16)) __asm("BKPT #0\n");
			*/
			data_addr = start_addr + 0x1000 * content[2];
			if (!file_open(data_addr, 'w', &file)) __asm("BKPT #0");
			for (int i = 3; i < content[0]; ++i)
				if (!file_putc(&file, content[i])) __asm("BKPT #0");
			if (!file_close(&file)) __asm("BKPT #0");
		}
		
		//写入flash，假定content[2]开始是待加密的数据，content每位一个字 
		//假设content[2]是所要写入的sector号，从0开始到15号结束
		//data_addr = start_addr + 0x1000 * content[2];
		//err = spi_flash_block_erase(data_addr, SECTOR_ERASE);
		//if (err != ERR_OK) __asm("BKPT #0\n");
		//write_byte = spi_flash_write_data(&content[3], data_addr, content[0] - 3);
		//if (write_byte != content[0] - 3) __asm("BKPT #0\n");
		//user_send_ble_data();
		/*int length = content[0] > 34 ? 32 : content[0] - 2;
		aes_operation(key, 16, content + 2, length, temp, length, 1, NULL, 0);
		rwip_schedule();
		aes_operation(key, 16, temp, length, result, length, 0, NULL, 0);
		rwip_schedule();
		user_send_ble_data(result, 16);*/
		//测试结束
		
	}
}
