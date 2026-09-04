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

#ifndef __HUART_TEST_H__
#define __HUART_TEST_H__


#include "hal_uart.h"
#include "hal_uwb.h"

//#define POLL_REQUEST_TEST

void user_init(void);

#ifdef POLL_REQUEST_TEST
void user_test(void);
#endif

#endif