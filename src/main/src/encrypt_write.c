
#include "user_periph_setup.h"
#include "tasks.h"
#include "user_spss.h"
#include "spi_flash.h"

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
		//写入flash，假定content[2]开始是待加密的数据，content每位一个字�  
		//假设content[2]是所要写入的sector号，从0开始到15号结束
		data_addr = start_addr + 0x1000 * content[2];
		spi_flash_block_erase(data_addr, SECTOR_ERASE);
		spi_flash_write_data(&content[3], data_addr, content[0] - 3);
	}
}
