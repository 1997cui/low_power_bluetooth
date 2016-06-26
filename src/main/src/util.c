
#include "util.h"

void u_strncpy(uint8_t *dst, uint8_t *src, uint8_t length)
{
	uint8_t i;
	
	for (i = 0;i < length;i++)
	{
		dst[i] = src[i];
	}
}

bool u_strncmp(uint8_t *dst, uint8_t *src, uint8_t length)
{
	for (int i = 0; i < length; ++i)
		if (dst[i] != src[i])
			return false;
	return true;
}