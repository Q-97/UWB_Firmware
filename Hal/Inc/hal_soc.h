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
#ifndef __ZN_SOC_HAL_H
#define __ZN_SOC_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_soc.h"
#include "zn_sys_tick.h"


void hal_soc_init(void);
void hal_soc_get_unique_id(uint8_t* data);

#ifdef __cplusplus
}
#endif

#endif

