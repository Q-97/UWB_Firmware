/******************************************************************************
 *  File: flash_test.h
 *
 *  Description: this file contains the functions support internal flash test operations.
 *
 *  Copyright (C) : 2022 Hangzhou ultraception.com.
 *
 *  Author: sxg
 *  Date:   May 13 2025
 *
 *****************************************************************************/

#ifndef __FLASH_TEST_H__
#define __FLASH_TEST_H__

#include "hal_uart.h"
#include "hal_uwb.h"
#include "hal_flash.h"

#define FLASH_TEST_ADDR         0x0007d000
#define MAX_FLASH_TEST_SIZE     1024



void user_init(void);
void user_test(void);
#endif