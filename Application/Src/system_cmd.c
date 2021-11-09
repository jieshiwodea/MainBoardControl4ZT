/*
 * system_cmd.c
 * tetsestetst
 *  Created on: Jul 31, 2019
 *      Author: wt
 */
#include "protocal_data_handle.h"
#include "cmsis_os.h"
#include "system_cmd.h"
#include "lens.h"
#include "ceju_data_handle.h"
#include "drv_uart.h"
#include "cmd.h"
#include "2d_bracket.h"
#include "protect_structure.h"
#include "m62429.h"
#include "package.h"

struct manifold_cmd manifold_cmd;
static uint8_t   focus_mode;			// wb
static uint16_t  last_distance;			// wb
static uint16_t  distance_delta;		// wb
static uint8_t	 moto_run_flag; 		// wb
static uint16_t  distance_sum;			// wb

static int8_t auto_focus(uint8_t *buff, uint16_t len);
static int8_t left_motor_move(uint8_t *buff, uint16_t len);
static int8_t right_motor_move(uint8_t *buff, uint16_t len);
static int8_t ud_stepper_move(uint8_t *buff, uint16_t len);
static int8_t lr_stepper_move(uint8_t *buff, uint16_t len);
static int8_t protect_stepper_move(uint8_t *buff, uint16_t len);
static int8_t set_volume(uint8_t *buff, uint16_t len);
static int8_t get_distance(uint8_t *buff, uint16_t len);

// wb add new func : 2021/01/22
static int8_t auto_focus_en_fun(uint8_t *buff, uint16_t len);
static int8_t auto_focus_dis_fun(uint8_t *buff, uint16_t len);
static int8_t get_moto_cnt_fun(uint8_t *buff, uint16_t len);

int16_t stride;

lens_t plens;
bracket_t pbracket;
protect_structure_t pprotect_structure;
void system_cmd_task(void const * argument)
{
	focus_mode 			= 0;			// wb
	last_distance 		= 0;			// wb
    distance_delta		= 0;			// wb
    moto_run_flag       = 0;			// wb
    distance_sum  		= 0;			// wb

	osDelay(1000);
	stop_distance_measure();
	osDelay(1000);
    stop_distance_measure();
    osDelay(1000);
    stop_distance_measure();
	plens = lens_find("lens");
	pbracket = bracket_find("bracket");
	pprotect_structure = protect_structure_find("protect_structure");
	osEvent event;

	protocol_rcv_cmd_register(AUTO_FOCUS,auto_focus);

	protocol_rcv_cmd_register(LEFT_MOTOR_MANUAL_FOCUS_PLUS,left_motor_move);
	protocol_rcv_cmd_register(LEFT_MOTOR_MANUAL_FOCUS_MINUS,left_motor_move);

	protocol_rcv_cmd_register(RIGHT_MOTOR_MANUAL_FOCUS_PLUS,right_motor_move);
	protocol_rcv_cmd_register(RIGHT_MOTOR_MANUAL_FOCUS_MINUS,right_motor_move);

	protocol_rcv_cmd_register(M3_FORWARD,ud_stepper_move);
	protocol_rcv_cmd_register(M3_REVERSAL,ud_stepper_move);

	protocol_rcv_cmd_register(M4_FORWARD,lr_stepper_move);
	protocol_rcv_cmd_register(M4_REVERSAL,lr_stepper_move);

	protocol_rcv_cmd_register(PROTECT_STEPPER_MOVE,protect_stepper_move);

	protocol_rcv_cmd_register(SET_VOLUME,set_volume);

	protocol_rcv_cmd_register(MEASURE_DISTANCE,get_distance);

	// wb add: 2021/01/22
	protocol_rcv_cmd_register(AUTO_FOCUS_EN, auto_focus_en_fun);

	protocol_rcv_cmd_register(AUTO_FOCUS_DIS,auto_focus_dis_fun);

	protocol_rcv_cmd_register(GET_MOTO_CNT,get_moto_cnt_fun);
	// add end


  for(;;)
  {
  	event = osSignalWait(MANIFOLD2_DISTANCE_SIGNAL, osWaitForever);

		if (event.status == osEventSignal)
		{
			if(manifold_cmd.distance > last_distance)	distance_delta = manifold_cmd.distance - last_distance;
			if(manifold_cmd.distance <= last_distance)	distance_delta = last_distance - manifold_cmd.distance;

			distance_sum = distance_sum + distance_delta;

			if(distance_delta >= 2)  moto_run_flag = 1;
			else					moto_run_flag = 0;

			if(event.value.signals & MANIFOLD2_DISTANCE_SIGNAL )
			{

             if(((focus_mode==1) && (moto_run_flag==1)) || ((focus_mode==0))) {
				osThreadSuspend(LensTaskHandle);
				plens->auto_focus_flag = TRUE;
				plens->motor[left_motor].goto_zp_flag = TRUE;
				plens->motor[right_motor].goto_zp_flag = TRUE;
				//zsy
				//here set CCR=1000
				//so,duty cycle=CCR/ARR=1% to stop pwm.
				__HAL_TIM_SET_COMPARE(plens->motor[left_motor].pwm_tim_handle,plens->motor[left_motor].pwm_channel,1000);
				__HAL_TIM_SET_COMPARE(plens->motor[right_motor].pwm_tim_handle,plens->motor[right_motor].pwm_channel,1000);
				lens_set_motors_target_by_distance(manifold_cmd.distance,plens);

				distance_sum = 0;	// wb
				last_distance = manifold_cmd.distance;	// wb
             }
             	 stop_distance_measure();

			}
		}

    osDelay(1);
  }
}


static int8_t auto_focus(uint8_t *buff, uint16_t len)
{
	start_distance_measure();
	return 0;
}

static int8_t left_motor_move(uint8_t *buff, uint16_t len)
{
	if(buff[0] == LEFT_MOTOR_MANUAL_FOCUS_PLUS)
	{
		stride = /*500*/32;
	}else if(buff[0] == LEFT_MOTOR_MANUAL_FOCUS_MINUS)
	{
		stride = /*-500*/-32;
	}
	else
	{
		return -1;
	}

	plens->motor[left_motor].target += stride;
	VAL_LIMIT(plens->motor[left_motor].target,MOTOR_TARGET_MIN,MOTOR_TARGET_MAX);
	return 0;
}


static int8_t right_motor_move(uint8_t *buff, uint16_t len)
{
	if(buff[0] == RIGHT_MOTOR_MANUAL_FOCUS_PLUS)
		{
			stride = /*500*/32;
		}
		else if(buff[0] == RIGHT_MOTOR_MANUAL_FOCUS_MINUS)
		{
			stride = /*-500*/-32;
		}
		else
		{
			return -1;
		}
		plens->motor[right_motor].target += stride;
		VAL_LIMIT(plens->motor[right_motor].target,MOTOR_TARGET_MIN,MOTOR_TARGET_MAX);
	return 0;
}

static int8_t ud_stepper_move(uint8_t *buff, uint16_t len)
{
	if(buff[0] == M3_FORWARD)
	{
		stride = -300;
	}
	else if(buff[0] == M3_REVERSAL)
	{
		stride = 300;
	}
	else
	{
		return -1;
	}

	stepper_run(&pbracket->stepper[up_down_stepper], stride);

	return 0;
}

static int8_t lr_stepper_move(uint8_t *buff, uint16_t len)
{
	if(buff[0] == M4_FORWARD)
	{
		stride = 200;
	}
	else if(buff[0] == M4_REVERSAL)
	{
		stride = -200;
	}
	else
	{
		return -1;
	}

	stepper_run(&pbracket->stepper[left_right_stepper], stride);

	return 0;
}


static int8_t protect_stepper_move(uint8_t *buff, uint16_t len)
{

	if(buff[0] == PROTECT_STEPPER_MOVE)
	{
		stride = (int16_t)(buff[2]<<8 | buff[3]);
	}
	else
	{
		return -1;
	}

//	protect_structure_stepper_run(pprotect_structure, stride);
	protect_structure_motor_run(stride);
	return 0;
}

static int8_t set_volume(uint8_t *buff, uint16_t len)
{
  return 0;
}

static int8_t get_distance(uint8_t *buff, uint16_t len)
{
	if(buff[0] == MEASURE_DISTANCE)
	{
		cj_get_distance();
	}
	return 0;
}

static int8_t get_moto_cnt_fun(uint8_t *buff, uint16_t len)
{

	  unsigned int tim3_cnt;
	  unsigned int tim5_cnt;
	  uint8_t buff1[4];

		tim3_cnt = __HAL_TIM_GET_COUNTER(&htim3);		// LEFT MOTOR
		tim5_cnt = __HAL_TIM_GET_COUNTER(&htim5);		// RIGHT MOTOR

	    buff1[0] = tim3_cnt>>8;
	    buff1[1] = tim3_cnt;

	    buff1[2] = tim5_cnt>>8;
	    buff1[3] = tim5_cnt;

	    upload_attr_t upload_attr = pack_upload_data(GET_MOTO_CNT,buff1,4);
	    pdh_data_upload(upload_attr.pdata,upload_attr.len);

		//usart1_transmit(buff, 2);
	    uint8_t stop[7] = {0x0D, 0x0A, 0x4F, 0x46, 0x46, 0x0D, 0x0A};
	   	  	usart4_transmit(stop,7);

		return 0;

}


static int8_t auto_focus_en_fun(uint8_t *buff, uint16_t len)
{
   focus_mode = 1;
   return 0;
}

static int8_t auto_focus_dis_fun(uint8_t *buff, uint16_t len)
{
   focus_mode = 0;
   return 0;
}


