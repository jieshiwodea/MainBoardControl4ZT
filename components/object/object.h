/*
 * object.h
 *
 *  Created on: July 3, 2019
 *      Author: wt
 */

#ifndef __OBJECT_H__
#define __OBJECT_H__

#ifdef OBJECT_H_GLOBAL
  #define OBJECT_H_EXTERN
#else
  #define OBJECT_H_EXTERN extern
#endif

#include "sys.h"

//This macro must be greater than 16.
#define OBJECT_NAME_MAX_LEN 32

#if OBJECT_NAME_MAX_LEN < 16
  #error "Macro OBJECT_NAME_MAX_LEN must be greater than 16."
#endif

enum object_class_type
{
  Object_Class_Device = 0,
  Object_Class_Module = 1,
  Object_Class_Controller = 2,
  Object_Class_Protect_Structure = 3,
  Object_Class_Bracket = 4,
  Object_Class_Lens = 5,
  Object_Class_Unknown,
};

struct object
{
  char name[OBJECT_NAME_MAX_LEN];
  enum object_class_type type;
  uint8_t flag;
  list_t list;
};

typedef struct object *object_t;

struct object_information
{
  enum object_class_type type; /**< object class type */
  list_t object_list;          /**< object list */
};

object_t object_find(const char *name, enum object_class_type type);
int32_t object_init(struct object *object,
                    enum object_class_type type,
                    const char *name);
void object_detach(object_t object);
struct object_information *
object_get_information(enum object_class_type type);

#endif // __OBJECT_H__
