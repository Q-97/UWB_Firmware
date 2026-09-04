/******************************************************************************
 *  File: gpio_test.h
 *
 *  Description: this file contains the functions support gpio test operations.
 *
 *  Copyright (C) : 2022 Hangzhou ultraception.com.
 *
 *  Author: sxg
 *  Date:   May 13 2025
 *
 *****************************************************************************/

#ifndef __GPIO_TEST_H__
#define __GPIO_TEST_H__


#include "hal_uart.h"
#include "hal_uwb.h"
#include "hal_gpio.h"


#define TEST_PIN GPIO_PIN0

void user_init(void);
void user_test(void);


#endif