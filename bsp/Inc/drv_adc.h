/*
 * drv_adc.h
 *
 *  Created on: Aug 2, 2019
 *      Author: wt
 */

#ifndef INC_DRV_ADC_H_
#define INC_DRV_ADC_H_
#include "adc.h"

//#define SAMPLE_CHANNEL_NUM 3
//#define SAMPLE_PER_CHANNEL 50

typedef void (*adc_conv_cplt_call_back)(uint8_t *buf, uint32_t len);
typedef void (*adc_awd_trigger_call_back)(void);

void adc1_manage_init(void);
void adc2_manage_init(void);
void adc3_manage_init(void);
void adc1_conv_cplt_callback_register(adc_conv_cplt_call_back fun);
void right_motor_awd_trigger_callback_register(adc_awd_trigger_call_back fun);
void left_motor_awd_trigger_callback_register(adc_awd_trigger_call_back fun);
void get_adc_value(void);


#endif /* INC_DRV_ADC_H_ */
