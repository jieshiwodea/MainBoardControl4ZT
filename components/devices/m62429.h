/*
 * m62429.h
 *
 *  Created on: Aug 8, 2019
 *      Author: wt
 */

#ifndef DEVICES_M62429_H_
#define DEVICES_M62429_H_
#include "gpio.h"

#define SET_VOLUME 0x22

#define CONTROL_D9D10	0x0060

#define CLK_L HAL_GPIO_WritePin(M62429_CLK_GPIO_Port,M62429_CLK_Pin,GPIO_PIN_RESET)
#define CLK_H HAL_GPIO_WritePin(M62429_CLK_GPIO_Port,M62429_CLK_Pin,GPIO_PIN_SET)
#define DAT_L HAL_GPIO_WritePin(M62429_D_GPIO_Port,M62429_D_Pin,GPIO_PIN_RESET)
#define DAT_H HAL_GPIO_WritePin(M62429_D_GPIO_Port,M62429_D_Pin,GPIO_PIN_SET)

void m62429_init(void);
int8_t m62429_control(uint8_t *volume_data,uint16_t len);
#endif /* DEVICES_M62429_H_ */
