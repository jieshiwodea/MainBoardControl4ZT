/*
 * ceju_task.c
 *
 *  Created on: Jul 29, 2019
 *      Author: wt
 */
#include <ceju_data_handle.h>
#include <stdlib.h>
#include "cmsis_os.h"
#include "fifo.h"
#include "drv_uart.h"
#include "communicate.h"
#include "system_cmd.h"
#include "package.h"

#define CJ_FIFO_BUFLEN 128

static unpack_ceju_data_t cj_unpack_obj;
static fifo_s_t  cj_rxdata_fifo;
static uint8_t   cj_rxdata_buf[CJ_FIFO_BUFLEN];
static hold_distance_t hold_distance;

void cj_param_init(void)
{
  fifo_s_init(&cj_rxdata_fifo, cj_rxdata_buf, CJ_FIFO_BUFLEN);
  /* initial judge data unpack object */
  cj_unpack_obj.data_fifo = &cj_rxdata_fifo;
  cj_unpack_obj.index = 0;
  cj_unpack_obj.frame_len = 0;
  cj_unpack_obj.unpack_step = STEP_CEJU_HRADER_FIRST;
}

uint32_t cj_uart_rx_data_handle(uint8_t *data, uint32_t len)
{
//	data[len]='\0';
//	usart1_printf("len: %d Str: %s\n",len, data);

	fifo_s_puts(&cj_rxdata_fifo, (char *)data, len);
	osSignalSet(CommunicateTaskHandle, RECV_CEJU_SIGNAL);

	return 0;
}

void cj_data_handler(uint8_t *p_frame, uint8_t len)
{
	uint16_t dis = 0;
	/* When distance measure fail: D=-----m , don't change the value of distance*/
	if( (p_frame[2]!='-') && (p_frame[6]!='-') )
	{
		dis = (uint16_t)(atof((char*)(&p_frame[2]))+0.5);
		manifold_cmd.distance = dis;
		osSignalSet(CmdTaskHandle, MANIFOLD2_DISTANCE_SIGNAL);
	}
//	else
//	{
//		start_distance_measure();
//	}

	/* upload the distance to android app */
	upload_attr_t
	// len-4去除D=和\r\n
	upload_attr = pack_upload_data(MEASURE_DISTANCE,&p_frame[2],len-4);
	pdh_data_upload(upload_attr.pdata,upload_attr.len);
	// save the distance
	memcpy(hold_distance.distance,&p_frame[2],len-4);
	hold_distance.len = len-4;

	stop_distance_measure();
}


void cj_get_distance(void)
{
	upload_attr_t upload_attr = pack_upload_data(MEASURE_DISTANCE,hold_distance.distance,hold_distance.len);
	pdh_data_upload(upload_attr.pdata,upload_attr.len);
}

void cj_unpack_fifo_data(void)
{
	uint8_t byte = 0;
	unpack_ceju_data_t *p_obj = &cj_unpack_obj;

	while ( fifo_s_used(p_obj->data_fifo) )
	{
		byte = fifo_s_get(p_obj->data_fifo);
		switch(p_obj->unpack_step)
		{
			case STEP_CEJU_HRADER_FIRST:
			{
				if(byte == CEJU_HRADER_FIRST_C)
				{
					p_obj->unpack_step = STEP_CEJU_HEADER_SECOND;
					p_obj->protocol_packet[p_obj->index++] = byte;
				}
				else
				{
					p_obj->index = 0;
					p_obj->unpack_step = STEP_CEJU_HRADER_FIRST;
				}
			}break;

			case STEP_CEJU_HEADER_SECOND:
			{
				if(byte == CEJU_HRADER_SECOND_C)
				{
				p_obj->unpack_step = STEP_CEJU_END;
				p_obj->protocol_packet[p_obj->index++] = byte;
				}
				else
				{
				p_obj->index = 0;
				p_obj->unpack_step = STEP_CEJU_HRADER_FIRST;
				}
			}break;

			case STEP_CEJU_END:
			{
				p_obj->protocol_packet[p_obj->index++] = byte;
				if (byte == CEJU_END_SECOND_C)
				{
					p_obj->frame_len = p_obj->index;
					p_obj->unpack_step = STEP_CEJU_HRADER_FIRST;
					p_obj->index = 0;
					cj_data_handler(p_obj->protocol_packet, p_obj->frame_len);
				}
			}break;

			default:
			{
				p_obj->unpack_step = STEP_CEJU_HRADER_FIRST;
				p_obj->index = 0;
			}break;
		}
	}
}

void start_distance_measure(void)
{
	uint8_t i;
	for(i=0;i<10;i++)
	{
		uint8_t start[7] = {0x0D, 0x0A, 0x4F, 0x3D, 0x31, 0x0D, 0x0A};
		usart3_transmit(start,7);
		osDelay(5);
	}
    stop_distance_measure();
}

void stop_distance_measure(void)
{
	uint8_t stop[7] = {0x0D, 0x0A, 0x4F, 0x46, 0x46, 0x0D, 0x0A};
	usart3_transmit(stop,7);
}

