void u_strncpy(uint8_t *dst, uint8_t *src, uint8_t length)
{
	uint8_t i;
	
	for (i = 0;i < length;i++)
	{
		dst[i] = src[i];
	}
}