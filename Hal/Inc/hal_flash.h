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
#ifndef _HAL_FLASH_H
#define _HAL_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "zn_qspi.h"
#include "zn_qspi_gd25q40.h"

void hal_flash_init(void);
void hal_flash_chip_erase(void);
ERROR_Type hal_flash_sector_erase(uint32_t address);
ERROR_Type hal_flash_read_data(uint32_t* data, uint32_t addr, uint32_t len);
ERROR_Type hal_flash_write_data_bytes(uint8_t* data, uint32_t addr, uint32_t len);
ERROR_Type hal_flash_write_data_short(uint8_t* data, uint32_t addr, uint32_t len);
ERROR_Type hal_flash_write_data_words(uint8_t* data, uint32_t addr, uint32_t len);


#ifdef __cplusplus
}
#endif

#endif