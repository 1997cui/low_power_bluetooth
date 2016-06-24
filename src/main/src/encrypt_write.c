
#include "user_periph_setup.h"
#include "tasks.h"
#include "rwip.h"
#include "user_spss.h"
#include "spi_flash.h"
#include "aes.h"

uint8_t key[16] = {0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01};//{0x06,0xa9,0x21,0x40,0x36,0xb8,0xa1,0x5b,0x51,0x2e,0x03,0xd5,0x34,0x12,0x00,0x06};
uint8_t temp[MaxMessageLength - 2];
uint8_t result[MaxMessageLength - 2];


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

		//Ğ´Èëflash£¬¼Ù¶¨content[2]¿ªÊ¼ÊÇ´ı¼ÓÃÜµÄÊı¾İ£¬contentÃ¿Î»Ò»¸ö×Ö½  
		//¼ÙÉècontent[2]ÊÇËùÒªĞ´ÈëµÄsectorºÅ£¬´Ó0¿ªÊ¼µ½15ºÅ½áÊø
		data_addr = start_addr + 0x1000 * content[2];
		spi_flash_block_erase(data_addr, SECTOR_ERASE);
		spi_flash_write_data(&content[3], data_addr, content[0] - 3);

		
		//²âÊÔ
		int length = content[0] > 66 ? 64 : content[0] - 2;
		aes_operation(key, 16, content + 2, length, temp, length, 1, NULL, 0);
		rwip_schedule();
		aes_operation(key, 16, temp, length, result, length, 0, NULL, 0);
		rwip_schedule();
		user_send_ble_data(result, 16);
		//²âÊÔ½áÊø
		
		//Ğ´Èëflash£¬¼Ù¶¨content[2]¿ªÊ¼ÊÇ´ı¼ÓÃÜµÄÊı¾İ£¬contentÃ¿Î»Ò»¸ö×Ö½Ú

	}
}
