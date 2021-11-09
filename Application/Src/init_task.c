/*
 * init_task.c
 *
 *  Created on: Aug 5, 2019
 *      Author: wt
 */
#include <drv_flash.h>
#include "init_task.h"
#include "2d_bracket.h"
#include "gpio.h"
#include "drv_uart.h"
#include "charge_test.h"
#include "adc_data_handle.h"

void init_task(void const * argument)
{
	writer_u writer;
	bracket_t bracket = bracket_find("bracket");
	uint8_t write_flash_flag = FALSE;
	for(;;)
	{
		if(HAL_GPIO_ReadPin(bracket->stepper[up_down_stepper].limit_gpio_port_handle,bracket->stepper[up_down_stepper].limit_gpio_Pin))
		{
			if((bracket->stepper[up_down_stepper].position == left) || (bracket->stepper[up_down_stepper].position == right))
			{
				bracket->stepper[up_down_stepper].position = middle;
				// TODO: update status into flash
				write_flash_flag=TRUE;
			}
		}
		else
		{
			if(bracket->stepper[up_down_stepper].position == middle)
			{
				bracket->stepper[up_down_stepper].position = bracket->stepper[up_down_stepper].last_position;
				// TODO: update status into flash
				write_flash_flag=TRUE;
			}
		}

		if(HAL_GPIO_ReadPin(bracket->stepper[left_right_stepper].limit_gpio_port_handle,bracket->stepper[left_right_stepper].limit_gpio_Pin))
		{
			if((bracket->stepper[left_right_stepper].position == left) || (bracket->stepper[left_right_stepper].position == right))
			{
				bracket->stepper[left_right_stepper].position = middle;
				// TODO: update status into flash
				write_flash_flag=TRUE;
			}
		}
		else
		{
			if(bracket->stepper[left_right_stepper].position == middle)
			{
				bracket->stepper[left_right_stepper].position = bracket->stepper[left_right_stepper].last_position;
				// TODO: update status into flash
				write_flash_flag=TRUE;
			}
		}

		if(write_flash_flag)
		{
			write_flash_flag = FALSE;
			writer.data[0] = bracket->stepper[up_down_stepper].position;
			writer.data[1] = bracket->stepper[left_right_stepper].position;
			write_word_to_flash(writer);
		}

		adh_prase_adc_dam_data();

		charge_test();

		osDelay(20);
	}
}


