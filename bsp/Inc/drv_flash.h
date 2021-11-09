#ifndef __FLASH_H__
#define __FLASH_H__

#include "stm32f1xx_hal.h"

#define FLASH_START_ADDRESS 0x0801E000
#define PAGE_SIZE               (uint32_t)FLASH_PAGE_SIZE  /* Page size */

#define WT_GET_NEW_ADDR (1<<0)
#define WT_GET_USED_ADDR (1<<1)

typedef union
{
	uint32_t data;
	uint8_t buff[4];
}flash_pack_u;


typedef struct
{
	uint32_t flash_start_address;
	uint32_t current_addr;
	uint32_t new_addr;
	uint16_t page_size;
	flash_pack_u buff;
}Flasher;

#define newFlasher(start_address,page_size){ \
		start_address,start_address,start_address,page_size,{0} \
}


typedef union
{
	uint8_t data[2];
	uint16_t data16;
}writer_u;


void update_volume_data_to_flash(uint32_t addr,uint32_t value[2]);
uint16_t read_half_word_from_flash(uint32_t addr);
uint32_t read_word_from_flash(uint32_t addr);

void easer_flash(void);
void find_new_entry(void);
uint32_t find_used_entry(void);
void write_word_to_flash(writer_u writer);

#endif

