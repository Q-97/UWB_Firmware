/*****************************************************************************
 *  File: hal_delay.h
 *
 * Descirption: this file contains the functions support delay operations.
 *
 *  Copyright (C) : 2025 ultraception.com
 *
 *  Author: sxg
 *  Mail:   
 *  Date:   2025-5-12
 *
 *****************************************************************************/

#ifndef __HAL_DELAY_H__
#define __HAL_DELAY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "zn_delay.h"

void hal_delay_us(uint32_t time_us);
void hal_delay_ms(uint32_t time_ms);

#ifdef __cplusplus
}
#endif

#endif
