/*****************************************************************************
 *  File: hal_watchdog.h
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
#ifndef _HAL_WATCHDOG_H
#define _HAL_WATCHDOG_H

#include "zn_wdt.h"
#include "zn_soc.h"

#ifdef __cplusplus
extern "C" {
#endif
 
 typedef struct hal_watchdog
 {
     uint8_t wdt_en : 1;       //0: disable, 1: enable
     uint8_t wdt_rmode : 1;    //0: generate a system reset.
                               //1: first generate an interrupt and if it is not cleared by the time a second timeout occurs, then it generates a system reset
     uint8_t wdt_timeout : 4;  //0-15: timeout period if set x, interrupt or reset after (2^(16+x)/38400000)s.
     uint8_t rsv : 2;
     WDT_EventCallback func;   //interrupt callback
 }hal_watchdaog_t;
 
 
 
 
ERROR_Type hal_watchdog_init(hal_watchdaog_t* wdt_config);
void hal_watchdog_feed(void);
void hal_watchdog_enable(void);
void hal_watchdog_disable(void);
void hal_watchdog_intc_clear(void);
uint32_t hal_watchdog_get_intc_status(void);
uint32_t hal_watchdog_get_cur_value(void);

#ifdef __cplusplus
}
#endif

#endif
