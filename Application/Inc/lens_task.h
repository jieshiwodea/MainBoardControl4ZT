/*
 * lens_task.h
 *
 *  Created on: Aug 5, 2019
 *      Author: wt
 */

#ifndef INC_LENS_TASK_H_
#define INC_LENS_TASK_H_
#include "lens.h"
#include "cmsis_os.h"
#include "drv_uart.h"

extern osThreadId LensTaskHandle;

void right_motor_awd_trigger_handle(void);
void left_motor_awd_trigger_handle(void);

#endif /* INC_LENS_TASK_H_ */
