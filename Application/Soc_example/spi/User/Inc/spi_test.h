/******************************************************************************
 *  File: spi_test.h
 *
 *  Description: this file contains the functions support spi test operations.
 *
 *  Copyright (C) : 2022 Hangzhou ultraception.com.
 *
 *  Author: sxg
 *  Date:   May 13 2025
 *
 *****************************************************************************/

#ifndef __SPI_TEST_H__
#define __SPI_TEST_H__

#include "hal_uart.h"
#include "hal_uwb.h"
#include "hal_spi.h"

#define SPI_RX_BUFF_LENGTH     16
#define SPI_TX_BUFF_LENGTH     16

//#define SPI_TEST_MASTER

#define SPI_TEST_ID  1


void user_init(void);
void user_test(void);
#endif