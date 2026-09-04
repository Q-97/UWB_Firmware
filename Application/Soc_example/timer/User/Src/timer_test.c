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

#include "timer_test.h"

uint32_t count = 0;
hal_gp_timer_t timer_cfg = {0};


static void timer_irq_callback(uint8_t arg)
{
    if(count++ % 2)
    {
        hal_gpio_set_value(GPIO_PIN0, 1);
    }
    else
    {
        hal_gpio_set_value(GPIO_PIN0, 0);
    }
}


void user_init(void)
{
    hal_uart_t uart_cfg = {0};
    
    uart_cfg.is_block_mode = 0;
    uart_cfg.is_tx_int_en = 0;
    uart_cfg.is_rx_int_en = 0;
    uart_cfg.baurdrate = B115200;
    hal_uart_init(&uart_cfg);
    
    hal_gpio_set_output_default_config(GPIO_PIN0);
    hal_gpio_set_value(GPIO_PIN0, 0);
    
    timer_cfg.timer_id = TIMER1;
    timer_cfg.clk_src = PLL_CLK;
    timer_cfg.clk_div = 0;
    timer_cfg.mode = TIMER_USER_DEFINE;
    timer_cfg.interrupt_en = 1;
    timer_cfg.time1 = (uint32_t)(DEFAULT_TEST_DUTY);
    timer_cfg.func = (TIMER_CallbackType)&timer_irq_callback;
    
    hal_gp_timer_init(&timer_cfg);
}


void user_test(void)
{
    uint8_t  data[10] = {0};
    uint8_t  idx      = 0;
    uint32_t time_out = 1000;
    uint8_t  timer_id = timer_cfg.timer_id;
    uint32_t clk_freq = hal_get_gp_timer_clk_freq(timer_id);

    hal_gp_timer_close(timer_id);
    hal_gp_timer_set_loadval(timer_id, USEC_TO_COUNT(time_out, clk_freq));
    hal_gp_timer_start(timer_id);
    
    LOG_INFO("now timer count time is %d us", time_out);
}