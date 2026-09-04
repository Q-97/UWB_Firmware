
/******************************************************************************
 *  File: zn_delay.h
 *
 *  Description: this file contains the functions support timer operations.
 *
 *  Copyright (C) : 2022 Hangzhou ultraception.com.
 *
 *  Author: sxg
 *  Date:   May 13 2025
 *
 *****************************************************************************/

#ifndef __ZN_DELAY_H__
#define __ZN_DELAY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_soc.h"
#include "zn_sys_timer.h"

void zn_delay_init(void);
void udelay(uint32_t usec);
void mdelay(uint32_t msec);
void cpu_delay(uint32_t lparam);

#ifdef __cplusplus
}
#endif

#endif
