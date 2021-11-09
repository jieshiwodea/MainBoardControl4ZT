/*
 * init_task.h
 *
 *  Created on: Aug 5, 2019
 *      Author: wt
 */

#ifndef INC_INIT_TASK_H_
#define INC_INIT_TASK_H_
#include "cmsis_os.h"

extern osThreadId LensTaskHandle;

void right_motor_awd_trigger_handle(void);
void left_motor_awd_trigger_handle(void);

#endif /* INC_INIT_TASK_H_ */
