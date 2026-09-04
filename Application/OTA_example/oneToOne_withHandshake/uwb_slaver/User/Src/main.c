/*****************************************************************************
* File: main.c
* Descirption: this file contains the functions support rx test.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#include "hal_soc.h"
#include "hal_uart.h"

void user_init(void)
{
    hal_uart_t uart_cfg = {0};
    
    uart_cfg.is_block_mode = 0;
    uart_cfg.is_tx_int_en = 0;
    uart_cfg.is_rx_int_en = 1;
    uart_cfg.baurdrate = B115200;
    uart_cfg.func = (DeviceCallback_Type)NULL;
    
    hal_uart_init(&uart_cfg);
}

int main(void)
{
    hal_soc_init();
    
    user_init();

    LOG_INFO("\r\n ota successed! now ver:20260604\r\n");
    while (1)
    {
        
    }

    return 0;
}