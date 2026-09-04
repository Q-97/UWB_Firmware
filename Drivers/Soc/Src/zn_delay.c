/*****************************************************************************
 *  File: timer.c
 *
 * Descirption: This file contains the functions support timer operations.
 *
 *  Copyright (C) : 2022 ultraception.com
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2023-4-17
 *
 *****************************************************************************/

#include "zn_delay.h"

void zn_delay_init(void)
{
    SYSTIMER_CfgCmpType   sys_timer_compare_config = {0};
    
    sys_ctrl_write(SYSTIMER_CLK_CFG, 0x01);     //systimer sel 38.4M XO clk no div
    
    sys_timer_compare_config.cmpId = 0;
    sys_timer_compare_config.cmpval = 0xffffffff;
    sys_timer_compare_config.interruptEn = 0;
    systimer_cmp_init(&sys_timer_compare_config);
    systimer_cmp_channel_ctrl(sys_timer_compare_config.cmpId, ENABLE);
}


void udelay(uint32_t usec)
{
    uint32_t sys_val = 0;
    uint32_t cnt_val = usec * 38.4;
    
    systimer_timer_clear(ENABLE);
    systimer_cmp_channel_ctrl(0,ENABLE);
    
    do
    {
        systimer_cmp_get_compare_value(&sys_val);
    }while(sys_val < cnt_val);
}

void mdelay(uint32_t msec)
{
    uint32_t i;
    for (i = 0; i < msec; i++) {
        udelay(1000);
    }
}

void cpu_delay(uint32_t lparam)
{
    volatile uint32_t i, j;

    for(i = 0; i < lparam; i++)
    {
        for(j = 0; j < 30U; j++)
        {
            __NOP();
        }
    }
}

