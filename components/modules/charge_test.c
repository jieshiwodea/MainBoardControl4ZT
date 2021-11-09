/*
 * charge_test.c
 *
 *  Created on: Aug 19, 2019
 *      Author: wt
 */
#include "charge_test.h"

extern void pdh_data_upload(uint8_t *p_frame, uint8_t len);

void charge_test(void)
{
	upload_attr_t upload_attr;
	charge_status_e status;
	// It is high when charging
	if(HAL_GPIO_ReadPin(Charge_Test_GPIO_Port,Charge_Test_Pin))
	{
		status = charging;

	}
	else
	{
		status = no_charge;
	}

	upload_attr = pack_upload_data(CHARGE_STATUS,(uint8_t*)&status,1);
	pdh_data_upload(upload_attr.pdata,upload_attr.len);
}


