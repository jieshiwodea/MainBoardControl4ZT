/*
 * device.h
 *
 *  Created on: July 3, 2019
 *      Author: wt
 */

#ifndef __DEVICE_H__
#define __DEVICE_H__

#ifdef DEVICE_H_GLOBAL
  #define DEVICE_H_EXTERN 
#else
  #define DEVICE_H_EXTERN extern
#endif
  
#include "object.h"

#define DEV_LOG_ENABLE

#define DEVICE_FLAG_DEACTIVATE 0X000

#define DEVICE_FLAG_RDONLY     0x001
#define DEVICE_FLAG_WRONLY     0x002
#define DEVICE_FLAG_RDWR       0x003

#define DEVICE_FLAG_REMOVABLE  0x004
#define DEVICE_FLAG_STANDALONE 0x008
#define DEVICE_FLAG_ACTIVATED   0x010
#define DEVICE_FLAG_SUSPENDED  0x020
#define DEVICE_FLAG_STREAM     0x040

#define DEVICE_OFLAG_CLOSE    0x000
#define DEVICE_OFLAG_RDONLY   0x001
#define DEVICE_OFLAG_WRONLY   0x002
#define DEVICE_OFLAG_RDWR     0x003
#define DEVICE_OFLAG_OPEN     0x008
#define DEVICE_OFLAG_MASK     0xf0f

typedef struct device *device_t;

enum device_type
{
  Device_Class_Motor = 0,
  Device_Class_Stepper = 1,
  Device_Class_Detect = 2,
  Device_Class_Unknown,
};

struct device
{
  struct object parent;
  enum device_type type;
  uint16_t flag;
  uint16_t open_flag;

  uint8_t ref_count;
  uint8_t device_id;

  void *user_data;
};

int32_t device_register(struct device *dev, const char *name, uint16_t flags);
int32_t device_unregister(struct device *dev);
device_t device_find(const char* name);

#endif // __DEVICE_H__
