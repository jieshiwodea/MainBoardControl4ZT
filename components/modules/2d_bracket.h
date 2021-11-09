/*
 * 2d_bracket.h
 *
 *  Created on: Aug 4, 2019
 *      Author: Administrator
 */
#include "stepper_motor.h"
#include "user_errno.h"
//struct limit_switch
//{
//
//
//};

typedef struct bracket* bracket_t;

struct bracket
{
	struct object parent;
	struct stepper_device stepper[2];
};

int32_t bracket_register(struct bracket *bracket, const char *name);
bracket_t bracket_find(const char *name);
void stepper_run(stepper_device_t stepper_device, int16_t setp);
void update_stepper_positon(uint16_t gpio_Pin);
void tim_rcr_uev_callback(void);

