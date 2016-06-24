
#include "tasks.h"
#include "arch_main.h"
#include <string.h>

static uint8_t encrypt_read_message[MaxMessageLength];

void encrypt_read_task(void *p)
{
	OS_EVENT *encrypt_read_q = ((struct common_data *)p)->encrypt_read_q;
	INT8U err;
	
	//读出flash上被加密的内容，存到encrypt_read_message[MaxMessageLength]
	
	OSQPost(encrypt_read_q, (void *)encrypt_read_message);
}
