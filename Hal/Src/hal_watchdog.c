/*****************************************************************************
 *  File: hal_watchdog.c
 *
 * Descirption: This file contains the functions support watchdog operations.
 *
 *  Copyright (C) : 2022 ultraception.com
 *
 *  Author: sxg
 *  Mail:   
 *  Date:   2025-5-14
 *
 *****************************************************************************/

#include "hal_watchdog.h"

ERROR_Type hal_watchdog_init(hal_watchdaog_t* wdt_config)
{
    WDT_ConfigType config = {0};
    
    if(NULL == wdt_config)
    {
        LOG_ERROR("null pointer");
        return ERROR;
    }
    sys_ctrl_write(WDT_CLK_CFG, 0x00);
    
    wdt_deinit();
    config.wdtEn = wdt_config->wdt_en;
    config.wdtRmode = wdt_config->wdt_rmode;
    config.wdtTimeout = wdt_config->wdt_timeout;
    
    if(WDT_INTC_RST == wdt_config->wdt_rmode)
    {
        wdt_set_callback(wdt_config->func);
    }
    wdt_init(&config);
    
    return SUCCESS;
}

void hal_watchdog_feed(void)
{
    wdt_feed();
}

void hal_watchdog_enable(void)
{
    wdt_enable();
}

void hal_watchdog_disable(void)
{
    wdt_disable();
}

void hal_watchdog_intc_clear(void)
{
    wdt_clr_intc_flag();
}

uint32_t hal_watchdog_get_intc_status(void)
{
    return wdt_get_intc_flag();
}

uint32_t hal_watchdog_get_cur_value(void)
{
    return wdt_get_curval();
}