/*****************************************************************************
 *  File: zn_soc_hal.h
 *
 * Descirption: this file contains the functions support systick operations.
 *
 *  Copyright (C) : 2023 ultraception.com
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2023-6-12
 *
 *****************************************************************************/
#ifndef __ZN_SYS_TICK_H
#define __ZN_SYS_TICK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_soc.h"

#define HAL_MAX_DELAY      0xFFFFFFFFU

typedef enum
{
  SYS_TICK_1US         = 1000000U,
  SYS_TICK_10US        = 100000U,
  SYS_TICK_100US       = 10000U,
  SYS_TICK_1MS         = 1000U,
  SYS_TICK_10MS        = 100U,
  SYS_TICK_100MS       = 10U,
} SYS_TickCycle;


uint8_t sys_tick_init(SYS_TickCycle tick_cycle);
void sys_tick_delay(uint32_t delayMs);
uint32_t sys_tick_get(void);

#ifdef __cplusplus
}
#endif

#endif

