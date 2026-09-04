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

#include "wdt_test.h"
#include "hal_soc.h"

uint32_t g_wdt_intc_count = 0;
uint8_t g_wdt_feed_flag = 0;
hal_watchdaog_t wdt_cfg = {0};


static void wdt_irq_callback(void)
{
    g_wdt_intc_count++;
    hal_soc_global_reset();
}

void user_init(void)
{
    hal_uart_t uart_cfg = {0};

    uart_cfg.is_block_mode = 0;
    uart_cfg.is_tx_int_en = 0;
    uart_cfg.is_rx_int_en = 0;
    uart_cfg.baurdrate = B115200;

    hal_uart_init(&uart_cfg);


    wdt_cfg.wdt_en = 0;
    wdt_cfg.wdt_rmode = 1;
    wdt_cfg.wdt_timeout = 10;
    wdt_cfg.func = (WDT_EventCallback)&wdt_irq_callback;

    hal_watchdog_init(&wdt_cfg);
}

void user_test(void)
{
    uint8_t test_ins = 0;

    LOG_INFO("input test instruction, 1: no reset, 2: reset");
    
    test_ins = hal_uart_get_char(0);
    
    if('1' == test_ins)
    {
        g_wdt_feed_flag = 1;
        LOG_INFO("input command 1, not reset");
    }
    else
    {
        g_wdt_feed_flag = 0;
        LOG_INFO("input command 2, reset");
    }
    
    hal_watchdog_enable();

    while(1)
    {
        hal_delay_ms(200);
        LOG_INFO("system running");

        if(g_wdt_feed_flag)
        {
            hal_watchdog_feed();
        }

    }
}    