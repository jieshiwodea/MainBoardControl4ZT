#include <drv_flash.h>
extern void FLASH_PageErase(uint32_t PageAddress);

void update_volume_data_to_flash(uint32_t addr,uint32_t value[2])
{
 /* -blow- write flash */
	     
  /* -1- Unlock the Flash Bank Program Erase controller */
  HAL_FLASH_Unlock();

  /* -2- Clear All pending flags */
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGERR);

  /* -3- erase the FLASH pages */
  FLASH_PageErase(addr);
  FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
  CLEAR_BIT(FLASH->CR, FLASH_CR_PER);

  /* -4- write data into flash */
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,addr,value[0]);
//  HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,addr+2,value[1]);
	/* -5- Lock the Flash Bank Program Erase controller */
  HAL_FLASH_Lock();
}

uint16_t read_half_word_from_flash(uint32_t addr)
{
	return *(uint16_t*)addr;
}

uint32_t read_word_from_flash(uint32_t addr)
{
	return (*(uint16_t*)addr) | (*(uint16_t*)(addr+2)<<16);
}

/***************************************************************/

static Flasher flasher = newFlasher(FLASH_START_ADDRESS,PAGE_SIZE);

void easer_flash(void)
{
	/* -1- Unlock the Flash Bank Program Erase controller */
	  HAL_FLASH_Unlock();

	  /* -2- Clear All pending flags */
	  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGERR);

	  /* -3- erase the FLASH pages */
	  FLASH_PageErase(FLASH_START_ADDRESS);
	  FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
	  CLEAR_BIT(FLASH->CR, FLASH_CR_PER);

	  /* -5- Lock the Flash Bank Program Erase controller */
	  HAL_FLASH_Lock();
}


void find_new_entry(void)
{
//	flasher.current_addr = flasher.flash_start_address;
	while(flasher.current_addr < flasher.flash_start_address+flasher.page_size)
	{
		flasher.buff.data = read_word_from_flash(flasher.current_addr);
		if(flasher.buff.buff[0] == 0xFF)
		{
			flasher.new_addr = flasher.current_addr;
			return;
		}

		flasher.current_addr += 4;
	}

	if(flasher.current_addr >= flasher.flash_start_address+flasher.page_size)
	{
		easer_flash();
		flasher.current_addr = flasher.flash_start_address;
		flasher.new_addr = flasher.flash_start_address;
	}
}

uint32_t find_used_entry(void)
{
//	flasher.current_addr = flasher.flash_start_address;
	while(flasher.current_addr < flasher.flash_start_address+flasher.page_size)
	{
		flasher.buff.data = read_word_from_flash(flasher.current_addr);
		if(flasher.buff.buff[0] == 0x5A)
		{
			return flasher.buff.data;
		}

		flasher.current_addr += 4;
	}
	return 0;
}

void write_word_to_flash(writer_u writer)
{
	flash_pack_u buf;
	buf.buff[0] = 0x5A;
	buf.buff[1] = writer.data[0];
	buf.buff[2] = writer.data[1];
	buf.buff[3] = 0xA5;

	find_new_entry();

	HAL_FLASH_Unlock();

	if(flasher.new_addr-4 >= flasher.flash_start_address)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,flasher.new_addr-4,0x00);
	}
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,flasher.new_addr,buf.data);

	HAL_FLASH_Lock();
}
