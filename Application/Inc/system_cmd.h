/*
 * system_cmd.h
 *
 *  Created on: Jul 31, 2019
 *      Author: wt
 */

#ifndef INC_SYSTEM_CMD_H_
#define INC_SYSTEM_CMD_H_

#define MANIFOLD2_LEFT_MOTOR_MOVE_SIGNAL        (1 << 0)
#define MANIFOLD2_RIGHTT_MOTOR_MOVE_SIGNAL      (1 << 1)
#define MANIFOLD2_DISTANCE_SIGNAL               (1 << 2)
#define MANIFOLD2_AUTO_FOCUS_SIGNAL             (1 << 3)
#define MANIFOLD2_UD_STEPPER_MOVE               (1 << 4)
#define MANIFOLD2_LR_STEPPER_MOVE               (1 << 5)

extern struct manifold_cmd manifold_cmd;
extern osThreadId CmdTaskHandle;
extern osThreadId LensTaskHandle;

struct manifold_cmd
{
  uint16_t left_motor_target;
  uint16_t right_motor_target;
  uint16_t auto_focus_target;
  uint16_t distance;
  int16_t  left_motor_stride;
  int16_t  right_motor_stride;
  int16_t  ud_stepper_stride;
  int16_t  lr_stepper_stride;
};

#endif /* INC_SYSTEM_CMD_H_ */
