/*****************************************************************************
* File: hal_otp.h
*
* Descirption: this file contains the otp hal functions.
*
* Copyright (C) : 2025 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2025 - 5
*****************************************************************************/
#ifndef _HAL_OTP_H
#define _HAL_OTP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "zn_regs.h"
#include "zn_interface.h"

void hal_otp_write(uint16_t addr, uint32_t* data, uint8_t len);
void hal_otp_read(uint16_t addr, uint32_t* data, uint8_t len);
BOOL_Type hal_opt_key_locked(void);
ERROR_Type hal_otp_key_write(uint32_t* key);
ERROR_Type hal_otp_key_read(uint32_t* key);



#ifdef __cplusplus
}
#endif

#endif