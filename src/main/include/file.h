
#ifndef _FILE_H_
#define _FILE_H_

#include "spi_flash.h"

typedef struct _flash_file
{
	uint32_t addr;
	uint32_t length;
	uint8_t session_key[16];
	uint8_t buffer[16];
	char mode;
} flash_file;

bool file_open(uint32_t addr, char mode, flash_file *FILE);

bool file_putc(flash_file *FILE, uint8_t data);

bool file_getc(flash_file *FILE, uint8_t *data);

bool file_close(flash_file *FILE);

#endif
