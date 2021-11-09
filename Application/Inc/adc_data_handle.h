/*
 * adh_data_handle.h
 *
 *  Created on: Aug 2, 2019
 *      Author: wt
 */

#ifndef INC_ADC_DATA_HANDLE_H_
#define INC_ADC_DATA_HANDLE_H_
#include "cmsis_os.h"

extern osThreadId CommunicateTaskHandle;

#define BATTERY_AND_RSSI_VOLTAGE  0x0F

typedef void (*adc_upload_handler_t)(uint8_t *buf, uint8_t len);

typedef enum
{
	NTC_ADC1_CH4 = 0,
	Battery_Voltage_ADC1_CH10 = 1,
	RSSI1_ADC1_CH12 = 2,
	RSSI2_ADC1_CH13 = 3,
}voltage_e;

void adh_param_init(void);
void adc_upload_data_register(adc_upload_handler_t upload_t);
void adh_prase_adc_dam_data(void);
void adh_adc_dma_data_handle(uint8_t *buf, uint32_t len);

#endif /* INC_ADC_DATA_HANDLE_H_ */
