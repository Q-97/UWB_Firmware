/******************************************************************************
 *  File: uart_test.h
 *
 *  Description: this file contains the functions support uart test operations.
 *
 *  Copyright (C) : 2022 Hangzhou ultraception.com.
 *
 *  Author: sxg
 *  Date:   May 13 2025
 *
 *****************************************************************************/

#ifndef __WDT_TEST_H__
#define __WDT_TEST_H__


#include "hal_uart.h"
#include "hal_uwb.h"
#include "hal_watchdog.h"
#include "hal_delay.h"

//#define WDT_TESET_INTERRUPT



void user_init(void);
void user_test(void);
#endif