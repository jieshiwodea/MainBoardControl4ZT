/*
 * stepper_motor.c
 *
 *  Created on: Aug 4, 2019
 *      Author: Administrator
 */
#include "stepper_motor.h"

int32_t setpper_device_register(stepper_device_t stepper_dev,
                              const char *name,
                              uint16_t flags)
{
  if (stepper_dev == NULL)
    return -WT_INVAL;

  if (device_find(name) != NULL)
    return -WT_EXISTED;

  stepper_dev->parent.type = Device_Class_Stepper;

  device_register( &(stepper_dev->parent), name, flags);

  return WT_OK;
}

stepper_device_t setpper_device_find(const char *name)
{
  device_t dev;
  enum device_type type;

  dev = device_find(name);

  if(dev == NULL)
    return NULL;

  type = dev->type;

  if (type == Device_Class_Stepper)
  {
    return (stepper_device_t)dev;
  }
  else
  {
    return NULL;
  }
}



