/*
 * motor.c
 *
 *  Created on: July 3, 2019
 *      Author: wt
 */

#include "motor.h"

#define MAX_MOTOR_NUM 6

int32_t motor_device_register(motor_device_t motor_dev,
                              const char *name,
                              uint16_t flags)
{
  if (motor_dev == NULL)
    return -WT_INVAL;

  if (device_find(name) != NULL)
    return -WT_EXISTED;

  motor_dev->parent.type = Device_Class_Motor;

  device_register( &(motor_dev->parent), name, flags);

  return WT_OK;
}

motor_device_t motor_device_find(const char *name)
{
  device_t dev;
  enum device_type type;

  dev = device_find(name);
  
  if(dev == NULL) 
    return NULL;

  type = dev->type;

  if (type == Device_Class_Motor)
  {
    return (motor_device_t)dev;
  }
  else
  {
    return NULL;
  }
}

int32_t motor_device_set_current(motor_device_t motor_dev, int16_t current)
{
  if (motor_dev != NULL)
  {
    motor_dev->current = current;
	//zsy
	//ARR=1000,
	//here set CCR register,
	//if CCR=(500-motor_dev->current)=500,it means duty cycle=CCR/ARR=50%.
    __HAL_TIM_SET_COMPARE(motor_dev->pwm_tim_handle,motor_dev->pwm_channel,500-motor_dev->current);
    return WT_OK;
  }
  return -WT_ERROR;
}

void motor_device_run(motor_device_t motor_dev,uint16_t speed)
{
	__HAL_TIM_SET_COMPARE(motor_dev->pwm_tim_handle,motor_dev->pwm_channel,speed);
}

void motor_device_set_encoder(motor_device_t motor_dev,uint16_t encoder)
{
	__HAL_TIM_SET_COUNTER(motor_dev->encoder_tim_handle,encoder);
}

