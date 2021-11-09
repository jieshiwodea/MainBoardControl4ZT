/*
 * lens_task.c
 *
 *  Created on: Jul 31, 2019
 *      Author: wt
 */
#include "lens_task.h"
#include "usart.h"

static void resume_the_task(void);
static uint8_t left_motor_arrive_zero,right_motor_arrive_zero = 0;

void lens_task(void const * argument)
{
	uint32_t period = osKernelSysTick();

	lens_t plens = lens_find("lens");
  for(;;)
  {
  	lens_execute(plens);
  	osDelayUntil(&period, 5);
  }
}

void left_motor_awd_trigger_handle(void)
{
	lens_t plens = lens_find("lens");
	static uint16_t left_awd_conut =0;
	if(plens->motor[left_motor].goto_zp_flag)
	{
		if(left_awd_conut++ >= 10000)
		{
			plens->motor[left_motor].goto_zp_flag = FALSE;
			left_awd_conut = 0;
			left_motor_arrive_zero = 1;

			//zsy
			//here set CCR register.
			//ARR=1000,CCR=500.
			//so here, duty cycle=CCR/ARR=50%.
			//this only control the speed.
			motor_device_run(&plens->motor[left_motor], 500);
			if(left_motor_arrive_zero && right_motor_arrive_zero)
			{
				left_motor_arrive_zero = 0;
				resume_the_task();
			}
		}
	}

}

void right_motor_awd_trigger_handle(void)
{
	lens_t plens = lens_find("lens");
	static uint16_t right_awd_conut = 0;
	if(plens->motor[right_motor].goto_zp_flag)
	{
		if(right_awd_conut++ >= 10000)
		{
			plens->motor[right_motor].goto_zp_flag = FALSE;
			right_awd_conut = 0;
			right_motor_arrive_zero = 1;
			
			//zsy
			//here set CCR register.
			//ARR=1000,CCR=500.
			//so here, duty cycle=CCR/ARR=50%.
			//this only control the speed.
			motor_device_run(&plens->motor[right_motor], 500);
			if(left_motor_arrive_zero && right_motor_arrive_zero)
			{
				right_motor_arrive_zero = 0;
				resume_the_task();
			}
		}
	}
}

static void resume_the_task(void)
{
	lens_t plens = lens_find("lens");
	if(!plens->auto_focus_flag)
	{
		plens->motor[left_motor].target = left_motor_zp;
		plens->motor[right_motor].target = right_motor_zp;
	}
	//zsy
	//here set CNT register.
	//the new DC motor outputs 16 pulses per circle.
	motor_device_set_encoder(&plens->motor[left_motor], 500);
	motor_device_set_encoder(&plens->motor[right_motor],500);
	osThreadResume(LensTaskHandle);
}
