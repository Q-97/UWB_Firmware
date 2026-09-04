/******************************************************************************
 *  File: systimer_test.h
 *
 *  Description: this file contains the functions support systimer test operations.
 *
 *  Copyright (C) : 2022 Hangzhou ultraception.com.
 *
 *  Author: sxg
 *  Date:   May 13 2025
 *
 *****************************************************************************/

#ifndef __SYSTIMER_TEST_H__
#define __SYSTIMER_TEST_H__

#include "hal_sys_timer.h"
#include "hal_uart.h"
#include "hal_uwb.h"
#include "hal_gpio.h"

#define SYS_TIMER_TEST_CMP


void user_init(void);
void user_test(void);
#endif