/*
 * communicate.c
 *
 *  Created on: Jul 26, 2019
 *      Author: wt
 */
#include <protocal_data_handle.h>
#include "ceju_data_handle.h"
#include "communicate.h"
#include "cmsis_os.h"
#include "drv_uart.h"
#include "cmd.h"
#include "adc_data_handle.h"

void communicate_task(void const * argument)
{
  for(;;)
  {
  	osEvent event;
  	event = osSignalWait(RECV_PROTOCOL_SIGNAL | RECV_CEJU_SIGNAL | RECV_ADC_DMA_SIGNAL, osWaitForever);

  	if (event.status == osEventSignal)
		{
			if (event.value.signals & RECV_PROTOCOL_SIGNAL)
			{
				pdh_unpack_fifo_data();
			}

			if (event.value.signals & RECV_CEJU_SIGNAL)
			{
				cj_unpack_fifo_data();
			}

			if (event.value.signals & RECV_ADC_DMA_SIGNAL)
			{
//				adh_prase_adc_dam_data();
			}
		}
  }
}
