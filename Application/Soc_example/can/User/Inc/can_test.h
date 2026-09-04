/******************************************************************************
 *  File: can_test.h
 *
 *  Description: this file contains the functions support can test operations.
 *
 *  Copyright (C) : 2022 Hangzhou ultraception.com.
 *
 *  Author: sxg
 *  Date:   May 13 2025
 *
 *****************************************************************************/

#ifndef __CAN_TEST_H__
#define __CAN_TEST_H__

#include "hal_uart.h"
#include "hal_uwb.h"
#include "hal_can.h"

#define MSG_QUIT_ID   (0x7FF)

#define CAN_TEST   0
#define CANFD_TEST 1

#define CAN_TEST_MODE   CANFD_TEST


void user_init(void);
void user_test(void);
#endif