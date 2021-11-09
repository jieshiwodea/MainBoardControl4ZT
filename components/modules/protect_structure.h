/*
 * protect_structure.h
 *
 *  Created on: Aug 7, 2019
 *      Author: wt
 */

#ifndef MODULES_PROTECT_STRUCTURE_H_
#define MODULES_PROTECT_STRUCTURE_H_
#include "motor.h"
#include "user_errno.h"

typedef struct protect_structure* protect_structure_t;


struct protect_structure
{
	struct object parent;
	struct motor_device motor;
};


int32_t protect_structure_register(protect_structure_t protect_structure, const char *name);
protect_structure_t protect_structure_find(const char *name);
void protect_structure_stepper_run(protect_structure_t protect_structure, int16_t stride);
void protect_structure_motor_run(int16_t current);

#endif /* MODULES_PROTECT_STRUCTURE_H_ */
