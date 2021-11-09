/*
 * motor.h
 *
 *  Created on: July 3, 2019
 *      Author: wt
 */

#ifndef __MOTOR_H__
#define __MOTOR_H__

#ifdef MOTOR_H_GLOBAL
  #define MOTOR_H_EXTERN
#else
  #define MOTOR_H_EXTERN extern
#endif

#include "device.h"
#include "tim.h"

typedef struct motor_device *motor_device_t;

typedef void (*set_encoder_f)(void);
typedef void (*motor_run_f)(void);

struct motor_device
{
  struct device parent;
  uint8_t goto_zp_flag;
  uint16_t zero_point;
  int16_t target;
  TIM_HandleTypeDef *encoder_tim_handle;
  TIM_HandleTypeDef *pwm_tim_handle;
  uint32_t pwm_channel;
  int16_t current;
};

motor_device_t motor_device_find(const char *name);
int32_t motor_device_register(motor_device_t motor_dev, const char *name, uint16_t flags);
int32_t motor_device_set_current(motor_device_t motor_dev, int16_t current);
void motor_device_run(motor_device_t motor_dev,uint16_t speed);
void motor_device_set_encoder(motor_device_t motor_dev,uint16_t encoder);

#endif // __MOTOR_H__
