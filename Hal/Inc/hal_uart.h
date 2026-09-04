/*****************************************************************************
* File: hal_uart.h
*
* Descirption: this file contains the uart hal functions.
*
* Copyright (C) : 2025 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2025 - 5
*****************************************************************************/
#ifndef _HAL_UART_H
#define _HAL_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "zn_uart.h"

#define UART_BASE(x)   ((0 == x) ? UART0 : UART1)
#define UART_ID(x)   ((UART0 == x) ? 0 : 1)

typedef struct hal_uart
{
    uint8_t uart_id : 1; // 0-1
    uint8_t is_block_mode : 1;
    uint8_t is_tx_int_en : 1;
    uint8_t is_rx_int_en : 1;
    uint8_t group_sel : 2; //uart1 group sel, 0: use GPIOA5 GPIOA6 as rxd txd, 1: use GPIOA7 GPIOA8 as rxd txd, 2: use GPIOA9 GPIOA10 as rxd txd
    uint8_t rsv : 2;
    UART_Baudrate baurdrate;
    DeviceCallback_Type func;
}hal_uart_t;



ERROR_Type hal_uart_init(hal_uart_t *uart_config);
uint8_t hal_uart_get_rx_data(uint8_t id);
uint8_t hal_uart_get_int_state(uint8_t id);
uint8_t hal_uart_tx_buff_is_empty(uint8_t id);
uint8_t hal_uart_rx_buff_is_not_empty(uint8_t id);
uint8_t hal_uart_get_char(uint8_t id);
void hal_uart_put_char(uint8_t id, uint8_t data);
uint32_t hal_uart_send_data(uint8_t id, uint8_t *buf, uint32_t len);
uint32_t hal_uart_get_rx_addr(uint8_t id);
uint32_t hal_uart_get_tx_addr(uint8_t id);

#ifdef __cplusplus
}
#endif

#endif
