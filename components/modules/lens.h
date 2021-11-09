/*
 * lens.h
 *
 *  Created on: 2019年7月30日
 *      Author: wt
 */

#ifndef LENS_H_
#define LENS_H_
#include "stm32f1xx_hal.h"
#include "object.h"
#include "user_errno.h"
#include "motor.h"
#include "pid.h"

#define ENCODER_VALUE_LENGTH 383

#define MOTOR_TARGET_MIN 500
#define MOTOR_TARGET_MAX 65000

typedef enum
{
	left_motor = 0,
	right_motor = 1,
}motor_e;

#ifdef NEW_001
typedef enum
{
	left_motor_zp = 10000,
	right_motor_zp = 1000,
}motor_zero_point_e;

#endif

#ifdef NEW_002
typedef enum
{
	left_motor_zp = 500,
	right_motor_zp = 500,
}motor_zero_point_e;

#endif

struct zero_point
{
	uint16_t left_motor_zero_point;
	uint16_t right_motor_zero_point;
};

struct lens
{
	struct   object parent;
	struct   zero_point zero_point;
	struct   motor_device motor[2];
	struct   pid motor_pid[2];
	uint8_t  auto_focus_flag;
};
#endif /* LENS_H_ */

typedef struct lens *lens_t;

int32_t lens_pid_register(struct lens *lens, const char *name);
lens_t lens_find(const char *name);
int32_t lens_execute(struct lens *lens);
void lens_set_left_motor_target(int16_t target, struct lens *lens);
void lens_set_right_motor_target(int16_t target, struct lens *lens);
void lens_set_motors_target_by_distance(uint16_t distance, struct lens *lens);



