/******************************************************************************
 *  File: dma_test.h
 *
 *  Description: this file contains the functions support dma test operations.
 *
 *  Copyright (C) : 2022 Hangzhou ultraception.com.
 *
 *  Author: sxg
 *  Date:   May 13 2025
 *
 *****************************************************************************/

#ifndef __DMA_TEST_H__
#define __DMA_TEST_H__


#include "hal_uart.h"
#include "hal_spi.h"
#include "hal_i2c.h"
#include "hal_dma.h"
#include "hal_uwb.h"
#include "hal_delay.h"

#define DMA_I2C_TEST        0
#define DMA_MEM_TO_MEM_TEST 1
#define DMA_SPI_MASTER_TEST 2
#define DMA_SPI_SLAVR_TEST  3
#define DMA_UART_TEST       4

#define DMA_TEST_TYPE    DMA_UART_TEST

#define MEM_TEST_TEMP            0x1fff0000
#define MEM_TEST_SRC             0x1fff0000
#define MEM_TEST_DST             0x1fff1000
#define DMA_MOVE_BYTES	         0x10
#define MEM2MEM_TEST_L	         0x100

#define DMA_UART_DEMO_POLLING    0
#define DMA_UART_DEMO_IRQ        1
#define DMA_UART_DEMO            DMA_UART_DEMO_IRQ



void user_init(void);
void user_test(void);
#endif