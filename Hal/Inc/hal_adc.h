/*****************************************************************************
* File: hal_adc.h
*
* Descirption: this file contains the adc hal functions.
*
* Copyright (C) : 2025 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2025 - 5
*****************************************************************************/
#ifndef _HAL_ADC_H
#define _HAL_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "zn_regs.h"
#include "zn_interface.h"

void hal_adc_cali_init(void);

double hal_adc_get_cur_vbat_voltage(void);
double hal_adc_get_cur_vtestp_voltage(void);
double hal_adc_get_cur_temperature(void);

#ifdef __cplusplus
}
#endif

#endif