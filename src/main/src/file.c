
#include "file.h"
#include "aes.h"
#include "util.h"

static uint8_t sector_status[8] = {0};

static uint8_t MASTER_KEY[16] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01}; // TODO: Change this!
static uint8_t AVAILABLE_CHECK[12] = {0x03, 0x02, 0x10, 0x33, 0x44, 0x21, 0x32, 0x09, 0xF6, 0xC8, 0x9E, 0x27};
static uint8_t temp[16];

static uint32_t seed = 1032797;
uint8_t random(void)
{
    seed = (seed * 749 + 61) % 65536;
    return (uint8_t)seed;
}

bool file_open(uint32_t addr, char mode, flash_file *FILE)
{
	addr &= 0xFFFFF000;
	if (addr >= 0x40000) return false;
	
	// Check the status
	uint8_t sec_addr = addr >> 12; // 4KB Sector
	uint8_t status = sector_status[sec_addr >> 3];
	uint8_t bit_addr = sec_addr & 0x7;
	status = (status << (0x7 - bit_addr)) >> 0x7;
	if (status) return false;
	
	switch (mode)
	{
		case 'r':
			// Read the available checking string
			if (12 != spi_flash_read_data(temp, addr + 16, 12))
				return false;
			
			// Check it
			if (!u_strncmp(temp, AVAILABLE_CHECK, 12))
				return false;
			
			// Read the random number stored
			if (16 != spi_flash_read_data(temp, addr, 16))
				return false;
			
			// Read the length out
			if (4 != spi_flash_read_data((uint8_t *)&(FILE->length), addr + 28, 4))
				return false;
			
			// Regenerate the session key
			aes_operation(MASTER_KEY, 16, temp, 16, FILE->session_key, 16, 1, NULL, 0xF0);
			break;
		case 'w':
			// Erase the sector
			if (ERR_OK != spi_flash_block_erase(addr, SECTOR_ERASE))
				return false;
			
			// Generate random number
			for (int i = 0; i < 16; ++i)
				temp[i] = random();
			
			// Write random number to flash
			if (16 != spi_flash_write_data(temp, addr, 16))
				return false;
			
			// Write available checking string to flash
			if (12 != spi_flash_write_data(AVAILABLE_CHECK, addr + 16, 12))
			{
				spi_flash_block_erase(addr, SECTOR_ERASE);
				return false;
			}
			
			// Initialize file structure with session key
			FILE->length = 0;
			aes_operation(MASTER_KEY, 16, temp, 16, FILE->session_key, 16, 1, NULL, 0xF0);
			break;
		default:
			return false;
	}
	
	// Write status bit
	sector_status[sec_addr >> 3] |= (1 << bit_addr);
	
	// Initialize file structure
	FILE->addr = addr + 32;
	FILE->mode = mode;
	return true;
}

bool file_putc(flash_file *FILE, uint8_t data)
{
	// Check mode
	if (FILE->mode != 'w') return false;
	
	// Check full
	if (FILE->addr & 0x00000FFF == 0) return false;
	
	// Put to buffer
	FILE->buffer[FILE->length++ & 0x0F] = data;
	
	// Write to flash when buffer full
	if (!(FILE->length & 0x0F))
	{
		aes_operation(FILE->session_key, 16, FILE->buffer, 16, temp, 16, 1, NULL, 0xF0);
		if (16 != spi_flash_write_data(temp, FILE->addr, 16))
		{
			FILE->mode = 'e'; // Error
			return false;
		}
		FILE->addr += 16;
	}
	
	return true;
}

bool file_getc(flash_file *FILE, uint8_t *data)
{
	// Check mode
	if (FILE->mode != 'r') return false;
	
	// Check end
	if ((FILE->addr & 0x00000FFF) - 32 > FILE->length) return false;
	
	// Read out of flash when buffer empty
	if (!(FILE->addr & 0x0F))
	{
		if (16 != spi_flash_read_data(temp, FILE->addr, 16))
		{
			FILE->mode = 'e'; // Error
			return false;
		}
		aes_operation(FILE->session_key, 16, temp, 16, FILE->buffer, 16, 0, NULL, 0xF0);
	}
	
	// Get the output
	*data = FILE->buffer[FILE->addr & 0x0F];
	FILE->addr++;
	return true;
}

bool file_close(flash_file *FILE)
{
	// Check status
	uint8_t sec_addr = FILE->addr >> 12; // 4KB Sector
	uint8_t status = sector_status[sec_addr >> 3];
	uint8_t bit_addr = sec_addr & 0x7;
	status = (status << (0x7 - bit_addr)) >> 0x7;
	if (status != 1) return false;
	// Reset status
	sector_status[sec_addr >> 3] &= (0 << bit_addr);
	
	// When writing...
	if (FILE->mode == 'w')
	{
		aes_operation(FILE->session_key, 16, FILE->buffer, 16, temp, 16, 1, NULL, 0xF0);
		if (16 != spi_flash_write_data(temp, FILE->addr, 16))
		{
			spi_flash_block_erase(FILE->addr, SECTOR_ERASE);
			return false;
		}
		FILE->addr &= 0xFFFFF000;
		FILE->addr += 28;
		if (4 != spi_flash_write_data((uint8_t *)&(FILE->length), FILE->addr, 4))
		{
			spi_flash_block_erase(FILE->addr, SECTOR_ERASE);
			return false;
		}
	}
	
	return true;
}
