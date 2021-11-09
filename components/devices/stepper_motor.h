/*
 * stepper_motor.h
 *
 *  Created on: Aug 4, 2019
 *      Author: Administrator
 */

#ifndef DEVICES_STEPPER_MOTOR_H_
#define DEVICES_STEPPER_MOTOR_H_
#include "device.h"
#include "tim.h"
#include "drv_flash.h"

typedef struct stepper_device* stepper_device_t;

typedef enum
{
	up_down_stepper = 0,
	left_right_stepper = 1,
}stepper_e;

typedef enum
{
	leftward = 0,
	rightward = 1,
}stepper_direction_e;

typedef enum
{
	left = 0,
	middle = 1,
	right = 2,
}stepper_position_e;

struct stepper_device
{
	struct device parent;
	TIM_HandleTypeDef *pwm_tim_handle;
	uint32_t pwm_channel;
	TIM_HandleTypeDef *cascade_tim_handle;
	GPIO_TypeDef *dir_gpio_port_handle;
	uint16_t dir_gpio_Pin;
	GPIO_TypeDef *limit_gpio_port_handle;
	uint16_t limit_gpio_Pin;
	GPIO_TypeDef *sleep_gpio_port_handle;
	uint16_t sleep_gpio_Pin;
	uint16_t step;
	stepper_direction_e direction;
	stepper_position_e position;
	stepper_position_e last_position;
};

int32_t setpper_device_register(stepper_device_t stepper_dev,const char *name,uint16_t flags);
stepper_device_t setpper_device_find(const char *name);

#endif /* DEVICES_STEPPER_MOTOR_H_ */
