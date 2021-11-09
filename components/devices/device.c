/*
 * device.c
 *
 *  Created on: July 3, 2019
 *      Author: wt
 */

#include "device.h"

int32_t device_register(struct device *dev,
                        const char *name,
                        uint16_t flags)
{
  if (dev == NULL)
    return -WT_INVAL;
  if (device_find(name) != NULL)
    return -WT_EXISTED;

  object_init(&(dev->parent), Object_Class_Device, name);

  dev->flag = flags;
  dev->ref_count = 0;
  dev->open_flag = 0;

  return WT_OK;
}

int32_t device_unregister(struct device *dev)
{
  if (dev == NULL)
    return -WT_INVAL;
  if (device_find(((object_t)dev)->name) == NULL)
    return WT_OK;

  object_detach(&(dev->parent));

  return WT_OK;
}

device_t device_find(const char *name)
{
  struct object *object;

  object = object_find(name, Object_Class_Device);

  return (device_t)object;
}

