
#include "user_periph_setup.h"
#include "gpio.h"
#include "tasks.h"
#include "rwip.h"
#include "user_spss.h"
#include "aes.h"

uint8_t key[16] = {0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01};//{0x06,0xa9,0x21,0x40,0x36,0xb8,0xa1,0x5b,0x51,0x2e,0x03,0xd5,0x34,0x12,0x00,0x06};
uint8_t temp[MaxMessageLength - 2];
uint8_t result[MaxMessageLength - 2];

void encrypt_write_task(void * p)
{
	OS_EVENT *encrypt_write_q = ((struct common_data *)p)->encrypt_write_q;
	INT8U err;
	
	while (true)
	{
		uint8_t *content = (uint8_t *)OSQPend(encrypt_write_q, 0, &err);
		
		//测试
		int length = content[0] > 66 ? 64 : content[0] - 2;
		aes_operation(key, 16, content + 2, length, temp, length, 1, NULL, 0);
		rwip_schedule();
		aes_operation(key, 16, temp, length, result, length, 0, NULL, 0);
		rwip_schedule();
		user_send_ble_data(result, 16);
		//测试结束
		
		//写入flash，假定content[2]开始是待加密的数据，content每位一个字节
	}
}
