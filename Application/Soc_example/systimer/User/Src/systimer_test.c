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

#include "systimer_test.h"

hal_sys_timer_t sys_timer_cfg = {0};
uint32_t cap_count = 0;

static void sys_timer_test_irq_callback(uint32_t status)
{  
    if(status & IRQ_CMP_STATUS(0))
    {
        printf("campare ch0 interrupt! cur val is 0x%x\r\n", hal_get_cur_sys_timer_val());
    }
    
    if(status & IRQ_CAP_STATUS(0))
    {
        printf("capture ch0 interrupt! cur val is 0x%x\r\n", hal_get_cap_val(0));
    }

}

static void compare_mode_test(void)
{
    sys_timer_cfg.cmpare_cfg.channel_en.bits.bit0 = 1;
    sys_timer_cfg.cmpare_cfg.compare_val[0] = 8000;
    sys_timer_cfg.cmpare_cfg.interrupt_mask.bits.bit0 = 1;
    sys_timer_cfg.func = (SysTimerCallback)&sys_timer_test_irq_callback;
    
    hal_sys_timer_init(&sys_timer_cfg);
}

static void capture_mode_test(void)
{
    sys_timer_cfg.capture_cfg.channel_en.bits.bit0 = 1;
    sys_timer_cfg.capture_cfg.gpio_sel[0] = 0;
    sys_timer_cfg.capture_cfg.dege_cfg[0] = CAP_RISE_EDGE;
    sys_timer_cfg.capture_cfg.interrupt_mask.bits.bit0 = 1;
    sys_timer_cfg.func = (SysTimerCallback)&sys_timer_test_irq_callback;
    
    hal_sys_timer_init(&sys_timer_cfg);
}

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
    #ifdef SYS_TIMER_TEST_CMP
    compare_mode_test();
    #else
    capture_mode_test();
    #endif
}