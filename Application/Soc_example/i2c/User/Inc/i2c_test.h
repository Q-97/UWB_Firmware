/******************************************************************************
 *  File: i2c_test.h
 *
 *  Description: this file contains the functions support i2c test operations.
 *
 *  Copyright (C) : 2022 Hangzhou ultraception.com.
 *
 *  Author: sxg
 *  Date:   May 13 2025
 *
 *****************************************************************************/

#ifndef __I2C_TEST_H__
#define __I2C_TEST_H__

#include "hal_uart.h"
#include "hal_uwb.h"
#include "hal_i2c.h"

#define I2C_TEST_MASTER    0
#define I2C_TEST_SLAVE     1

#define I2C_TEST_MODE    I2C_TEST_SLAVE

#define I2C_TEST_NUM 8

#define SLAVE_ADDR    0x0b


void user_init(void);
void user_test(void);
#endif