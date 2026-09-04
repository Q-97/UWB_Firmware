/*****************************************************************************
* File: uart_test.c
* Descirption: this file contains the functions support uart test.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/

#include "uart_test.h"

#ifdef POLL_REQUEST_TEST

void user_init(void)
{
    hal_uart_t uart_cfg = {0};
    
    uart_cfg.is_block_mode = 0;
    uart_cfg.is_tx_int_en = 0;
    uart_cfg.is_rx_int_en = 0;
    uart_cfg.baurdrate = B115200;
    
    hal_uart_init(&uart_cfg);
}

void user_test(void)
{
    uint8_t data = 0;
    
    data = hal_uart_get_char(0);
    hal_uart_put_char(0, data);   
}
#else
static void user_uart_irq_callback( ZN_UartType *UARTx, uint32_t wpara, uint32_t lpara)
{
    uint8_t intc_state; 
    uint8_t data;
    intc_state = hal_uart_get_int_state(0);

    /* Received data available.
     * - Receiver data available (non-FIFO mode or FIFOs disabled) 
     * - or RCVR FIFO trigger level reached (FIFO mode and FIFOs enabled)
    */
    if (hal_uart_rx_buff_is_not_empty(0)) 
    {
        data = hal_uart_get_rx_data(0);
        hal_uart_put_char(0, data);
    }
}


void user_init(void)
{
    hal_uart_t uart_cfg = {0};
    
    uart_cfg.is_block_mode = 0;
    uart_cfg.is_tx_int_en = 0;
    uart_cfg.is_rx_int_en = 1;
    uart_cfg.baurdrate = B115200;
    uart_cfg.func = (DeviceCallback_Type)&user_uart_irq_callback;
    
    hal_uart_init(&uart_cfg);
}
#endif