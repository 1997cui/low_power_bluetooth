
#include "user_periph_setup.h"
#include "gpio.h"
#include "tasks.h"
#include "user_spss.h"

void encrypt_write_task(void * p)
{
	OS_EVENT *encrypt_write_q = ((struct common_data *)p)->encrypt_write_q;
	INT8U err;
	
	while (true)
	{
		uint8_t *content = (uint8_t *)OSQPend(encrypt_write_q, 0, &err);
		
		aa
		//д��flash���ٶ�content[2]��ʼ�Ǵ����ܵ����ݣ�contentÿλһ���ֽ�
	}
}
