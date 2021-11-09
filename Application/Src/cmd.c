/*
 * cmd.c
 *
 *  Created on: 2019年7月26日
 *      Author: wt
 */
#include "cmd.h"

struct rcv_cmd_info rcv_cmds[PROTOCOL_CMD_MAX_NUM];

int8_t protocol_rcv_cmd_register(uint16_t cmd, rcv_handle_fn_t rcv_callback)
{
  for (int i = 0; i < PROTOCOL_CMD_MAX_NUM; i++)
  {
    if (rcv_cmds[i].used == 0)
    {
      rcv_cmds[i].used = 1;
      rcv_cmds[i].cmd = cmd;
      rcv_cmds[i].rcv_callback = rcv_callback;
      return 0;
    }
  }
  return -1;
}

int8_t protocol_rcv_cmd_unregister(uint16_t cmd)
{
  for (int i = 0; i < PROTOCOL_CMD_MAX_NUM; i++)
  {
    if ((rcv_cmds[i].cmd == cmd) && (rcv_cmds[i].used == 1))
    {
      rcv_cmds[i].used = 0;
      return 0;
    }
  }
  return -1;
}

void protocol_rcv_pack_handle(uint8_t *pack_data, uint16_t cmd)
{
  attr_pack_t *pack = (attr_pack_t *)(pack_data);

  for (int i = 0; i < PROTOCOL_CMD_MAX_NUM; i++)
  {
    if ((rcv_cmds[i].cmd == cmd) && (rcv_cmds[i].rcv_callback != NULL) && (rcv_cmds[i].used == 1))
    {
      rcv_cmds[i].rcv_callback(pack->pdata, pack->len);
    }
  }

  return;
}
