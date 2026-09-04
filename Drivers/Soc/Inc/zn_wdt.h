/*****************************************************************************
 *  File: zn_wdt.h
 *
 *  Descirption: contains the functions support Watchdog Timer.
 *
 *  Copyright (C) : 2023 ultraception.com
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2023-4-24
 *
 *****************************************************************************/

#ifndef __ZN_WDT_H__
#define __ZN_WDT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_wdt_reg.h"

typedef void (*WDT_EventCallback)(void);

typedef struct
{
    uint8_t wdtEn;        /* 0 - disable;1 - enable */
    uint8_t wdtRmode;     /* 0 - Generate a system reset.1 - First generate an interrupt and if it is not cleared by the time a second timeout.*/
    uint8_t wdtTimeout;   /* Timeout period,value 0-15*/
} WDT_ConfigType;


void wdt_init(WDT_ConfigType * config);
void wdt_deinit(void);
uint32_t  wdt_get_intc_flag(void);
void  wdt_clr_intc_flag(void);
uint32_t wdt_get_curval(void);
void wdt_set_callback(WDT_EventCallback callback);

#ifdef __cplusplus
}
#endif

#endif
