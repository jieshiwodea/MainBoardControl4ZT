/****************************************************************************
 *  Copyright (C) 2019 RoboMaster.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#ifdef DRV_UART_H_GLOBAL
#define DRV_UART_H_EXTERN
#else
#define DRV_UART_H_EXTERN extern
#endif

#include "sys.h"

#define USART3_RX_BUFFER_SIZE (128)
#define USART3_TX_BUFFER_SIZE (128)
#define USART3_TX_FIFO_SIZE (512)

#define USART1_RX_BUFFER_SIZE (512)
#define USART1_TX_BUFFER_SIZE (512)
#define USART1_TX_FIFO_SIZE (1024)

//wb
#define USART4_RX_BUFFER_SIZE (512)	//wb
#define USART4_TX_BUFFER_SIZE (512) //wb
#define USART4_TX_FIFO_SIZE (1024)  //wb

#define USART1_PRINTF_BUFF_SIZE (128)

typedef uint32_t (*usart_call_back)(uint8_t *buf, uint32_t len);

typedef struct
{
  UART_HandleTypeDef *uart_h;
  DMA_HandleTypeDef *dma_h;
  uint16_t rx_buffer_size;
  uint8_t *rx_buffer;
  uint16_t read_start_index;
  usart_call_back call_back_f;

  uint8_t *tx_buffer;
  uint16_t tx_buffer_size;
  fifo_s_t tx_fifo;
  uint8_t *tx_fifo_buffer;
  uint16_t tx_fifo_size;
  uint8_t is_sending;
} usart_manage_obj_t;

typedef enum
{
  INTERRUPT_TYPE_UART = 0,
  INTERRUPT_TYPE_DMA_HALF = 1,
  INTERRUPT_TYPE_DMA_ALL = 2
} interrput_type;

typedef enum
{
  ERR_DATA_SIZE_TOO_LARGE = -1,
  ERR_NORAML = 0
} UART_Err;

void usart3_manage_init(void);
void usart4_manage_init(void);
void usart1_manage_init(void); //wb
void usart_rx_callback_register(usart_manage_obj_t *m_obj, usart_call_back fun);
UART_Err usart_transmit(usart_manage_obj_t *m_obj, uint8_t *buf, uint16_t len);
int usart1_printf(char *fmt, ...);
void usart1_transmit(uint8_t *buff, uint16_t len);
void usart3_transmit(uint8_t *buff, uint16_t len);
void usart4_transmit(uint8_t *buff, uint16_t len);  // wb
void usart1_idle_callback(void);
void usart3_idle_callback(void);
void usart4_idle_callback(void);	//wb
uint32_t uart1_rx_data_handle(uint8_t *buff, uint32_t len);
void usart1_rx_callback_register(usart_call_back fun);
void usart3_rx_callback_register(usart_call_back fun);
void usart4_rx_callback_register(usart_call_back fun);	//wb
#endif // __DRV_UART_H__
