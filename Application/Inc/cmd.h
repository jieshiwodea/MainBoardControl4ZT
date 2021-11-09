/*
 * cmd.h
 *
 *  Created on: 2019年7月26日
 *      Author: wt
 */

#ifndef INC_CMD_H_
#define INC_CMD_H_

#include "stm32f1xx_hal.h"

#define PROTOCOL_CMD_MAX_NUM            (80)

typedef int8_t (*rcv_handle_fn_t)(uint8_t *buff, uint16_t len);

struct rcv_cmd_info
{
  uint8_t used;
  uint8_t cmd;
  rcv_handle_fn_t rcv_callback;
};


typedef struct{
	uint8_t pdata[50];
	uint8_t len;
}attr_pack_t;

typedef struct{
	uint8_t attr_id;
	uint8_t attr_value_len;
	uint8_t *pdata;
}attr_pack_desc_t;

int8_t protocol_rcv_cmd_register(uint16_t cmd, rcv_handle_fn_t rcv_callback);
int8_t protocol_rcv_cmd_unregister(uint16_t cmd);
void protocol_rcv_pack_handle(uint8_t *pack_data, uint16_t cmd);

#endif /* INC_CMD_H_ */
