/*
 * package.c
 *
 *  Created on: Aug 4, 2019
 *      Author: Administrator
 */
#include "package.h"

static upload_attr_t upload_attr;
static uint8_t buff[10];
upload_attr_t pack_upload_data(uint8_t attr_id,uint8_t *data, uint8_t len)
{
	osMutexWait(packMutexHandle,osWaitForever);
	uint8_t data_frame_length = len+2;
	buff[0]=attr_id;
	buff[1]=len;
	memcpy(&buff[2],data,len);
	upload_attr.pdata = buff;
	upload_attr.len = data_frame_length;
	osMutexRelease(packMutexHandle);
	return upload_attr;
}

