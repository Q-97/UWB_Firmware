/******************************************************************************
 *  File: adc_test.h
 *
 *  Description: this file contains the functions support adc test operations.
 *
 *  Copyright (C) : 2022 Hangzhou ultraception.com.
 *
 *  Author: sxg
 *  Date:   May 13 2025
 *
 *****************************************************************************/

#ifndef __ADC_TEST_H__
#define __ADC_TEST_H__

#include "hal_uart.h"
#include "hal_uwb.h"
#include "hal_otp.h"


#define MAX_OTP_NUM  0x80
#define CUST_OTP_ADDR  0x20


void user_init(void);
void user_test(void);
#endif