/******************************************************************************
 *  File: timer_test.h
 *
 *  Description: this file contains the functions support uart test operations.
 *
 *  Copyright (C) : 2022 Hangzhou ultraception.com.
 *
 *  Author: sxg
 *  Date:   May 13 2025
 *
 *****************************************************************************/

#ifndef __TIMER_TEST_H__
#define __TIMER_TEST_H__

#include "hal_gp_timer.h"
#include "hal_uart.h"
#include "hal_uwb.h"
#include "hal_gpio.h"

#define DEFAULT_TEST_DUTY  1000  //uint us

void user_init(void);
void user_test(void);
#endif