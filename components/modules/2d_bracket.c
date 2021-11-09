/*
 * 2d_bracket.c
 *
 *  Created on: Aug 4, 2019
 *      Author: Administrator
 */
#include "2d_bracket.h"

int32_t bracket_register(struct bracket *bracket, const char *name)
{
	char motor_name[2][OBJECT_NAME_MAX_LEN] = {0};
	uint8_t name_len;
	int32_t err;

	if (bracket == NULL)
		return -WT_INVAL;
	if (bracket_find(name) != NULL)
		return -WT_EXISTED;

	object_init(&(bracket->parent), Object_Class_Bracket, name);

	name_len = strlen(name);

	if (name_len > OBJECT_NAME_MAX_LEN / 2)
	{
		name_len = OBJECT_NAME_MAX_LEN / 2;
	}

	for (int i = 0; i < 2; i++)
	{
		memcpy(&motor_name[i], name, name_len);
	}

	flash_pack_u flash_pack;
	flash_pack.data = find_used_entry();

	bracket->stepper[up_down_stepper].pwm_tim_handle = &htim8;
	bracket->stepper[up_down_stepper].cascade_tim_handle = NULL;
	bracket->stepper[up_down_stepper].pwm_channel = TIM_CHANNEL_2;
	bracket->stepper[up_down_stepper].dir_gpio_port_handle = Stepper_Up_Dir_GPIO_Port;
	bracket->stepper[up_down_stepper].dir_gpio_Pin = Stepper_Up_Dir_Pin;
	bracket->stepper[up_down_stepper].limit_gpio_port_handle = UD_Limit_Switch_GPIO_Port;
	bracket->stepper[up_down_stepper].limit_gpio_Pin = UD_Limit_Switch_Pin;
	bracket->stepper[up_down_stepper].sleep_gpio_port_handle = Stepper_UD_Sleep_GPIO_Port;
	bracket->stepper[up_down_stepper].sleep_gpio_Pin = Stepper_UD_Sleep_Pin;
	bracket->stepper[up_down_stepper].last_position = middle;
	bracket->stepper[up_down_stepper].position = flash_pack.buff[1];

	bracket->stepper[left_right_stepper].pwm_tim_handle = &htim2;
	bracket->stepper[left_right_stepper].cascade_tim_handle = &htim4;
	bracket->stepper[left_right_stepper].pwm_channel = TIM_CHANNEL_1;
	bracket->stepper[left_right_stepper].dir_gpio_port_handle = Stepper_LR_Dir_GPIO_Port;
	bracket->stepper[left_right_stepper].dir_gpio_Pin = Stepper_LR_Dir_Pin;
	bracket->stepper[left_right_stepper].limit_gpio_port_handle = LR_Limit_Switch_GPIO_Port;
	bracket->stepper[left_right_stepper].limit_gpio_Pin = LR_Limit_Switch_Pin;
	bracket->stepper[left_right_stepper].sleep_gpio_port_handle = Stepper_LR_Sleep_GPIO_Port;
	bracket->stepper[left_right_stepper].sleep_gpio_Pin = Stepper_LR_Sleep_Pin;
	bracket->stepper[left_right_stepper].last_position = middle;
	bracket->stepper[left_right_stepper].position = flash_pack.buff[2];

	memcpy(&motor_name[up_down_stepper][name_len], "_UD\0", 4);
	memcpy(&motor_name[left_right_stepper][name_len], "_LR\0", 4);

	for (int i = 0; i < 2; i++)
	{
		err = setpper_device_register(&(bracket->stepper[i]), motor_name[i], 0);
		if (err != WT_OK)
			goto end;
	}

	return WT_OK;

end:
	object_detach(&(bracket->parent));

	return err;
}


bracket_t bracket_find(const char *name)
{
  struct object *object;

  object = object_find(name, Object_Class_Bracket);

  return (bracket_t)object;
}


/*
 *
 * one step is 251 pluse
 *
 */
void stepper_run(stepper_device_t stepper_device, int16_t step)
{
	GPIO_PinState pin_state;

	// leftward
	if(step>=0)
	{
		if(stepper_device->position == left)
		{
			return;
		}
		stepper_device->step += step;
		stepper_device->direction = leftward;
		pin_state = GPIO_PIN_RESET;
	}
	// rightward
	else if(step<0)
	{
		if(stepper_device->position == right)
		{
			return;
		}
		step = -step;
		stepper_device->step -= step;
		stepper_device->direction = rightward;
		pin_state = GPIO_PIN_SET;
	}

//	stepper_device->position = middle;
	HAL_GPIO_WritePin(stepper_device->sleep_gpio_port_handle,stepper_device->sleep_gpio_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(stepper_device->dir_gpio_port_handle, stepper_device->dir_gpio_Pin, pin_state);
	if(stepper_device->cascade_tim_handle == NULL)
	{
		stepper_device->pwm_tim_handle->Instance->RCR = 60;
	}
	else
	{
		__HAL_TIM_SET_AUTORELOAD(stepper_device->cascade_tim_handle,step);
	}

	HAL_TIM_PWM_Start(stepper_device->pwm_tim_handle, stepper_device->pwm_channel);
}

void update_stepper_positon(uint16_t gpio_Pin)
{
	stepper_device_t stepper;
	bracket_t b = bracket_find("bracket");
	if(gpio_Pin==UD_Limit_Switch_Pin)
	{
		stepper = &b->stepper[up_down_stepper];
	}
	else if(gpio_Pin==LR_Limit_Switch_Pin)
	{
		stepper = &b->stepper[left_right_stepper];
	}

	stepper->last_position = stepper->position;

	if(!HAL_GPIO_ReadPin(stepper->limit_gpio_port_handle,stepper->limit_gpio_Pin))
	{
		if(stepper->direction == leftward)
		{
			stepper->position = left;
		}
		else if(stepper->direction == rightward)
		{
			stepper->position = right;
		}

		HAL_TIM_PWM_Stop(stepper->pwm_tim_handle, stepper->pwm_channel);
	}
	else
	{
		stepper->position = middle;
	}

	// TODO: update status into flash
	writer_u writer;
	writer.data[0] = b->stepper[up_down_stepper].position;
	writer.data[1] = b->stepper[left_right_stepper].position;
	write_word_to_flash(writer);
}

static uint8_t rcr_cnt = 0;
void tim_rcr_uev_callback(void)
{
	if(rcr_cnt++ >= 2)
	{
		rcr_cnt = 0;
		HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_2);
		HAL_GPIO_WritePin(Stepper_UD_Sleep_GPIO_Port,Stepper_UD_Sleep_Pin,GPIO_PIN_RESET);
	}
}
