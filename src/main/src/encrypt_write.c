
#include "user_periph_setup.h"
#include "gpio.h"
#include "tasks.h"
#include "rwip.h"
#include "user_spss.h"
#include "aes.h"

void encrypt_write_task(void * p)
{
	OS_EVENT *encrypt_write_q = ((struct common_data *)p)->encrypt_write_q;
	INT8U err;
	
	while (true)
	{
		uint8_t *content = (uint8_t *)OSQPend(encrypt_write_q, 0, &err);
		
		//测试
		uint8_t key[16]={ 
  0x06,0xa9,0x21,0x40,0x36,0xb8,0xa1,0x5b,0x51,0x2e,0x03,0xd5,0x34,0x12,0x00,0x06};
		uint8_t temp[16];
		uint8_t result[16];
		
		aes_operation(key, sizeof(key), content, sizeof(content), temp, sizeof(temp), 1, NULL, 0);
		rwip_schedule();
		aes_operation(key, sizeof(key), temp, 16, result, 16, 0, NULL, 0);
		rwip_schedule();
		user_send_ble_data(result, 16);
		//测试结束
		
		//写入flash，假定content[2]开始是待加密的数据，content每位一个字节
	}
}
