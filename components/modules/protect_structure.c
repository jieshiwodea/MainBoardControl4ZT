/*
 * protect_structure.c
 *
 *  Created on: Aug 7, 2019
 *      Author: wt
 */
#include "protect_structure.h"
#include "cmsis_os.h"

int32_t protect_structure_register(protect_structure_t protect_structure, const char *name)
{
	char motor_name[OBJECT_NAME_MAX_LEN] = {0};
	uint8_t name_len;
	int32_t err;

	if (protect_structure == NULL)
		return -WT_INVAL;
	if (protect_structure_find(name) != NULL)
		return -WT_EXISTED;

	object_init(&(protect_structure->parent), Object_Class_Protect_Structure, name);

	name_len = strlen(name);

	if (name_len > OBJECT_NAME_MAX_LEN / 2)
	{
		name_len = OBJECT_NAME_MAX_LEN / 2;
	}

	memcpy(motor_name, name, name_len);

//	protect_structure->stepper.pwm_tim_handle = &htim8;
//	protect_structure->stepper.pwm_channel = TIM_CHANNEL_3;
//	protect_structure->stepper.dir_gpio_port_handle = Stepper_Up_Dir_GPIO_Port;
//	protect_structure->stepper.dir_gpio_Pin = Stepper_Protect_Dir_Pin;
//	protect_structure->stepper.sleep_gpio_port_handle = Stepper_Protect_Sleep_GPIO_Port;
//	protect_structure->stepper.sleep_gpio_Pin = Stepper_Protect_Sleep_Pin;


	protect_structure->motor.pwm_tim_handle = &htim1;
	protect_structure->motor.pwm_channel = TIM_CHANNEL_3;

	memcpy(&motor_name[name_len], "_PROTECT\0", 9);

//	err = setpper_device_register(&(protect_structure->stepper), motor_name, 0);
//	if (err != WT_OK)
//		goto end;

	return WT_OK;

//end:
//	object_detach(&(protect_structure->parent));

	return err;
}

protect_structure_t protect_structure_find(const char *name)
{
  struct object *object;

  object = object_find(name, Object_Class_Protect_Structure);

  return (protect_structure_t)object;
}

//void protect_structure_stepper_run(protect_structure_t protect_structure, int16_t stride)
//{
//	GPIO_PinState pin_state;
//	if(stride >= 0)
//	{
//		pin_state = GPIO_PIN_RESET;
//	}
//	else if(stride < 0)
//	{
//		pin_state = GPIO_PIN_SET;
//		stride =- stride;
//	}
//
//	HAL_GPIO_WritePin(protect_structure->stepper.sleep_gpio_port_handle,protect_structure->stepper.sleep_gpio_Pin,GPIO_PIN_SET);
//	HAL_GPIO_WritePin(protect_structure->stepper.dir_gpio_port_handle, protect_structure->stepper.dir_gpio_Pin, pin_state);
//	HAL_TIM_PWM_Start(protect_structure->stepper.pwm_tim_handle, protect_structure->stepper.pwm_channel);
//}

extern osTimerId once_timerHandle;
void protect_structure_motor_run(int16_t current)
{
	HAL_GPIO_WritePin(Sleep2_GPIO_Port,Sleep2_Pin,GPIO_PIN_SET);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,500-current);

	osTimerStart(once_timerHandle,100);
}

void stop_protect_motor(void const * argument)
{
	HAL_GPIO_WritePin(Sleep2_GPIO_Port,Sleep2_Pin,GPIO_PIN_RESET);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,500);
}
