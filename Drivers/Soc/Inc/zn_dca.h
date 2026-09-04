/*****************************************************************************
 *  File: dca.h
 *
 *  Descirption: this file contains the functions dca
 *
 *  Copyright (C) : 2022 ultraception.com
 *
 *  Author: WangJiying
 *  Mail:   
 *  Date:   2022-3-22
 *
 *****************************************************************************/
#ifndef __ZN_DCA_H__
#define __ZN_DCA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_soc.h"
#include "aon_reg.h"

#define AON_DCA_CTRL (0x0A04)
#define AON_DCA_RDAT (0x0A08)
#define AON_DCA_ADDR (0x0A0C)
#define AON_DCA_WDAT (0x0A10)


void dca_write(uint32_t addr, uint32_t data);
uint32_t dca_read(uint32_t addr);
void dca_set_bit(uint32_t addr, uint32_t n);
void dca_clear_bit(uint32_t addr, uint32_t n);

#ifdef __cplusplus
}
#endif

#endif