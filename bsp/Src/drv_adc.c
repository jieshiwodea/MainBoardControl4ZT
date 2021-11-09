#include "drv_adc.h"

uint16_t adc1_conv_buff[SAMPLE_PER_CHANNEL][SAMPLE_CHANNEL_NUM] ={0};

//static adc_conv_cplt_call_back adc1_conv_cplt_call_back_f = NULL;
static adc_awd_trigger_call_back right_motor_awd_trigger_call_back_f = NULL;
static adc_awd_trigger_call_back left_motor_awd_trigger_call_back_f = NULL;

void adc1_manage_init(void)
{
	//  HAL_ADCEx_Calibration_Start(&hadc1);
	HAL_ADC_Start_DMA(&hadc1,(uint32_t *)adc1_conv_buff,SAMPLE_PER_CHANNEL*SAMPLE_CHANNEL_NUM);
}

void adc2_manage_init(void)
{
  HAL_ADC_Start(&hadc2);

}

void adc3_manage_init(void)
{
	HAL_ADC_Start(&hadc3);
}


//void adc1_conv_cplt_callback_register(adc_conv_cplt_call_back fun)
//{
//	adc1_conv_cplt_call_back_f = fun;
//}

void right_motor_awd_trigger_callback_register(adc_awd_trigger_call_back fun)
{
	right_motor_awd_trigger_call_back_f = fun;
}

void left_motor_awd_trigger_callback_register(adc_awd_trigger_call_back fun)
{
	left_motor_awd_trigger_call_back_f = fun;
}

//void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
//{
//	if(hadc->Instance == ADC1)
//	{
//		if(adc1_conv_cplt_call_back_f != NULL)
//		{
//			adc1_conv_cplt_call_back_f((uint8_t *)adc1_conv_buff,SAMPLE_PER_CHANNEL*SAMPLE_CHANNEL_NUM*2);
//		}
//	}
//}

void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc)
{

	if(hadc->Instance == ADC2)
	{
		if (__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_AWD) != RESET)
		{
			if(right_motor_awd_trigger_call_back_f != NULL)
			{
				right_motor_awd_trigger_call_back_f();
			}

		}
	}
	else if(hadc->Instance == ADC3)
	{
		if (__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_AWD) != RESET)
		{
			if(left_motor_awd_trigger_call_back_f != NULL)
			{
				left_motor_awd_trigger_call_back_f();
			}
		}
	}
}


