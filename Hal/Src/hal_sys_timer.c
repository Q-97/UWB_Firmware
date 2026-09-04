/*****************************************************************************
 *  File: hal_sys_timer.c
 *
 * Descirption: This file contains the functions support systimer operations.
 *
 *  Copyright (C) : 2022 ultraception.com
 *
 *  Author: sxg
 *  Mail:   
 *  Date:   2025-5-14
 *
 *****************************************************************************/

#include "hal_sys_timer.h"


ERROR_Type hal_sys_timer_init(hal_sys_timer_t *sys_timer_config)
{
    uint8_t             idx            = 0;
    SYSTIMER_CfgCmpType compare_config = {0};
    SYSTIMER_CfgCapType capture_config = {0};
    uint8_t             cmp_irq_mask   = 0;
    uint8_t             cap_irq_mask   = 0;
    uint8_t             ovf_irq_en     = 0;
    
    if(NULL == sys_timer_config)
    {
        LOG_ERROR("null pointer");
        return ERROR;
    }
    
    sys_clear_bit(CLK_ICG_REG,CLK_ICG_REG_SYSTIMER_PCLK_ICG_SHIFT);   /*systimer PCLK normal*/
    sys_clear_bit(CLK_ICG_REG,CLK_ICG_REG_SYSTIMER_CLK_ICG_SHIFT);   /*systimer CLK normal*/

    sys_clear_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_SYSTIMER_SW_PRSTN_SHIFT);  /*SYSTIMER_SW_PRSTN reset*/
    sys_set_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_SYSTIMER_SW_PRSTN_SHIFT);  /*SYSTIMER_SW_PRSTN set*/
    sys_clear_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_SYSTIMER_SW_RSTN_SHIFT);   /*SYSTIMER_SW_RSTN reset*/
    sys_set_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_SYSTIMER_SW_RSTN_SHIFT);   /*SYSTIMER_SW_RSTN set*/
    
    sys_ctrl_write(SYSTIMER_CLK_CFG, 0x01); //systimer sel 38.4M XO clk no div

    compare_config.cmpId = sys_timer_config->cmpare_cfg.channel_en.mask;
    while(idx < MAX_CMP_CH_NUM)
    {
        if(sys_timer_config->cmpare_cfg.channel_en.mask & (1 << idx))
        {
            compare_config.cmpId = idx;
            compare_config.cmpval = sys_timer_config->cmpare_cfg.compare_val[idx];
            compare_config.interruptEn = sys_timer_config->cmpare_cfg.interrupt_mask.mask & (1 << idx);
            systimer_cmp_init(&compare_config);
            systimer_cmp_channel_ctrl(compare_config.cmpId, ENABLE);
        }
        idx++;
    }
    
    idx=0;
    while(idx < MAX_CAP_CH_NUM)
    {
        if(sys_timer_config->capture_cfg.channel_en.mask & (1 << idx))
        {
            capture_config.capId = idx;
            capture_config.capMode = sys_timer_config->capture_cfg.dege_cfg[idx];
            capture_config.gpio_pin = sys_timer_config->capture_cfg.gpio_sel[idx];
            capture_config.interruptEn = sys_timer_config->capture_cfg.interrupt_mask.mask & (1 << idx);
            systimer_cap_init(&capture_config);
            systimer_cap_channel_ctrl(capture_config.capId, ENABLE);
        }
        idx++;
    }
    if(!sys_timer_config->overflow_interrupt_en)
    {
        systimer_ovf_set_irq_disable();
    }
    
    systimer_set_callback(sys_timer_config->func);

    
    return SUCCESS;
}

uint32_t hal_get_cur_sys_timer_val(void)
{
    return systimer_get_cur_val();
}

uint32_t hal_get_cap_val(uint8_t ch)
{
    uint32_t val = 0;
    
    if(ch >= MAX_CAP_CH_NUM)
    {
        LOG_ERROR("error channel bigger than max cap channel");
        return 0;
    }
    systimer_get_cap_val(ch, &val);
    return val;
}

void hal_sys_timer_clear_en(uint8_t status)
{
    systimer_timer_clear(status);
}

void hal_sys_timer_pause_en(uint8_t status)
{
    systimer_timer_pause(status);
}


void hal_sys_timer_cmp_channel_en(uint8_t ch, uint8_t status)
{
    if(ch >= MAX_CMP_CH_NUM)
    {
        LOG_ERROR("error channel bigger than max cap channel");
        return;
    }

    systimer_cmp_channel_ctrl(ch, status);
}

void hal_sys_timer_cap_channel_en(uint8_t ch, uint8_t status)
{
    if(ch >= MAX_CAP_CH_NUM)
    {
        LOG_ERROR("error channel bigger than max cap channel");
        return;
    }
    
    systimer_cap_channel_ctrl(ch, status);
}

void hal_sys_timer_cmp_all_channel_disable(void)
{  
    for(uint8_t idx = 0; idx < MAX_CMP_CH_NUM; idx++)
    {
        systimer_cmp_channel_ctrl(idx, DISABLE);
    }
}

void hal_sys_timer_cap_all_channel_disable(void)
{
    for(uint8_t idx = 0; idx < MAX_CMP_CH_NUM; idx++)
    {
        systimer_cap_channel_ctrl(idx, DISABLE);
    }
}