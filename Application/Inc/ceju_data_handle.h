/*
 * ceju_task.h
 *
 *  Created on: Jul 29, 2019
 *      Author: wt
 */

#ifndef INC_CEJU_H_
#define INC_CEJU_H_
#include <protocal_data_handle.h>
#include "stm32f1xx_hal.h"
#include "lens.h"

extern osThreadId CommunicateTaskHandle;

#define CJ_PROTOCOL_FRAME_MAX_SIZE (15)

#define CEJU_HRADER_FIRST_C  'D'
#define CEJU_HRADER_SECOND_C '='
#define CEJU_END_FIRST_C     '\r'
#define CEJU_END_SECOND_C    '\n'

#define MEASURE_DISTANCE     0x03

typedef void (*ceju_upload_handler_f)(uint8_t *buf, uint8_t len);

typedef enum{
	STEP_CEJU_HRADER_FIRST  = 0,
	STEP_CEJU_HEADER_SECOND = 1,
	STEP_CEJU_END           = 2,
}unpack_ceju_setp_e;

typedef struct
{
	uint8_t distance[10];
	uint8_t len;
}hold_distance_t;

typedef struct
{
  fifo_s_t       *data_fifo;
  uint8_t        frame_len;
  uint8_t        protocol_packet[CJ_PROTOCOL_FRAME_MAX_SIZE];
  unpack_ceju_setp_e  unpack_step;
  uint8_t        index;
} unpack_ceju_data_t;


void cj_param_init(void);
uint32_t cj_uart_rx_data_handle(uint8_t *data, uint32_t len);
void ceju_upload_data_register(ceju_upload_handler_f upload_f);
void cj_unpack_fifo_data(void);
void start_distance_measure(void);
void stop_distance_measure(void);
void cj_get_distance(void);

#endif /* INC_CEJU_H_ */
