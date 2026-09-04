/*****************************************************************************
 *  File: hal_gp_timer.c
 *
 * Descirption: this file contains the functions support systick operations.
 *
 *  Copyright (C) : 2025 ultraception.com
 *
 *  Author: sxg
 *  Mail:   
 *  Date:   2025-5-12
 *
 *****************************************************************************/

#include "hal_gp_timer.h"

static uint32_t s_timer_clk_freq[TIMER_NUM] = {0};

static uint32_t get_timer_clk_freq(uint8_t div, uint8_t sel)
{
    uint32_t clk_freq_val = 0;
    uint32_t clk_freq[2]  = {124800000, 38400000};
    
    if(RC_CLK == sel)
    {
        clk_freq_val = 1000000;         //if select rc clk, timer1 is original count value, not us
    }
    else
    {
        if(sel > XO_CLK)
        {
            return 0;
        }
        clk_freq_val = clk_freq[sel] / (div + 1);
    }
    
    
    return clk_freq_val;
}

ERROR_Type hal_gp_timer_init(hal_gp_timer_t *timer_config)
{
    uint32_t clk_cfg_val = 0; 
    uint32_t clk_freq    = 0;
    TIMER_ConfigType config = {0};
    
    if((NULL == timer_config) || (timer_config->timer_id >= TIMER_NUM)) 
    {
        return ERROR;
    }
    sys_clear_bit(CLK_ICG_REG,CLK_ICG_REG_TIMER_PCLK_ICG_SHIFT);   /*timer PCLK normal*/
    sys_set_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_TIMER_SW_PRSTN_SHIFT);   /*timer RST set*/
    sys_clear_bit(CLK_ICG_REG,(CLK_ICG_REG_TIMER0_CLK_ICG_SHIFT + timer_config->timer_id));   /*timer clk set*/
    sys_set_bit(BLK_SW_RSTN0, (BLK_SW_RSTN0_TIMER0_SW_RSTN_SHIFT + timer_config->timer_id));
    
    config.timerId = timer_config->timer_id;
    config.timerMode = timer_config->mode;
    
    clk_cfg_val = ((timer_config->clk_div << TIMER_CLK_DIV_BITOFFSET) & TIMER_CLK_DIV_BITMASK) |
                  ((timer_config->clk_src << TIMER_CLK_SEL_BITOFFSET) & (TIMER_CLK_SEL_BITMASK));
    
    sys_ctrl_write(TIMER0_CLK_CFG + timer_config->timer_id * 4, clk_cfg_val);
    
    clk_freq = get_timer_clk_freq(timer_config->clk_div, timer_config->clk_src);
    s_timer_clk_freq[timer_config->timer_id] = clk_freq;
    config.loadCnt = USEC_TO_COUNT(timer_config->time1, clk_freq);
    
    if(timer_config->interrupt_en)
    {
        config.interruptEn = 1;
        timer_set_callback(timer_config->timer_id, timer_config->func);
    }
    
    if(timer_config->pwm_en)
    {
        config.interruptEn = 0;
        config.pwmEn = 1;
        config.loadCnt2 = USEC_TO_COUNT(timer_config->time2, clk_freq);
    }
    
    timer_init(&config);
    
    return SUCCESS;
}

ERROR_Type hal_gp_timer_deinit(uint8_t timer_id)
{
    if (timer_id >= TIMER_NUM)
    {
        return ERROR;
    }
    
    timer_deinit(timer_id);
    
    return SUCCESS;
}


ERROR_Type hal_gp_timer_start(uint8_t timer_id)
{
    if (timer_id >= TIMER_NUM)
    {
        return ERROR;
    }
    
    timer_enable(timer_id);
    
    return SUCCESS;
}

ERROR_Type hal_gp_timer_close(uint8_t timer_id)
{
    if (timer_id >= TIMER_NUM)
    {
        return ERROR;
    }
    
    timer_disable(timer_id);
    
    return SUCCESS;
}

ERROR_Type hal_gp_timer_interrupt_enable(uint8_t timer_id)
{
    if (timer_id >= TIMER_NUM)
    {
        return ERROR;
    }

    NVIC_EnableIRQ(timer_id);
    timer_enable_int(timer_id);
    
    return SUCCESS;
}

ERROR_Type hal_gp_timer_interrupt_disable(uint8_t timer_id)
{
    if (timer_id >= TIMER_NUM)
    {
        return ERROR;
    }

    NVIC_DisableIRQ(timer_id);
    timer_disable_int(timer_id);
    
    return SUCCESS;
}

void hal_gp_timer_set_loadval(uint8_t timer_id, uint32_t loadval)
{
    timer_set_loadval(timer_id, loadval);
}

void hal_gp_timer_set_loadval2(uint8_t timer_id, uint32_t loadval)
{
    timer_set_loadval2(timer_id, loadval);
}

void hal_gp_timer_reset_cnt(uint8_t timer_id)
{
    timer_reset_cnt(timer_id);
}

uint32_t hal_get_gp_timer_clk_freq(uint8_t timer_id)
{
    if(timer_id >= TIMER_NUM)
    {
        LOG_ERROR("error timer id");
        return 0;
    }
    return s_timer_clk_freq[timer_id];
}

