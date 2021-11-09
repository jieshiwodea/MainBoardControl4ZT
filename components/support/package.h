/*
 * package.h
 *
 *  Created on: Aug 4, 2019
 *      Author: Administrator
 */

#ifndef SUPPORT_PACKAGE_H_
#define SUPPORT_PACKAGE_H_
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "string.h"

extern osMutexId packMutexHandle;

typedef struct {
	uint8_t *pdata;
	uint8_t len;
}upload_attr_t;

upload_attr_t pack_upload_data(uint8_t attr_id,uint8_t *data, uint8_t len);


#endif /* SUPPORT_PACKAGE_H_ */
