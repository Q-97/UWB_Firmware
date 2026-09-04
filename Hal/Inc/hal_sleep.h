/*****************************************************************************
* File: hal_uart.h
*
* Descirption: this file contains the sleep hal functions.
*
* Copyright (C) : 2025 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2025 - 5
*****************************************************************************/
#ifndef _HAL_SLEEP_H
#define _HAL_SLEEP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "zn_dca.h"

#define US_TO_32K_COUNT(x)    (((x) * 32.768) / 1000)

#define AUTO_SLEEP     0
#define DEEP_SLEEP     1

#define INTERNAL_RC_CLK   0
#define EXTERNAL_XO_CLK   1

#define POWER_ON            0
#define WAKEUP_BY_SPI0_CSN  1
#define WAKEUP_BY_SPI1_CSN  2
#define WAKEUP_BY_AUTO_CNT  4
#define WAKEUP_BY_CAN_RXD   8

#define CLK_SOURCE_INTERNAL 0
#define CLK_SOURCE_EXTERNAL 1

#define MODE_NOT_CLEAR    0
#define MODE_CLEAR        1
#define MODE_RELOAD       2

#define WAKEUP_MODE_LEVEL    0
#define WAKEUP_MODE_POSEDGE  1
#define WAKEUP_MODE_NEGEDGE  2
#define WAKEUP_MODE_BOTHEDGE 3

#define WAKEUP_LEVEL_HIGH  1
#define WAKEUP_LEVEL_LOW   0

#define CODE_SRAM_ADDR       (0x1FFE5000)
#define SLEEP_FLAG_VAL       (0x5A5AA5A5)
#define SLEEP_FLAG_ADDR      (0x1FFE0000)
#define TOP_SP_ADDR          (0x1FFE0004)
#define CUR_SP_ADDR          (0x1FFE0008)
#define STACK_BACK           (0x1FFE0400)

typedef union wakeup_src
{
    uint8_t mask;
    struct
    {
        uint8_t rsv: 4;
        uint8_t spi0_csn : 1;
        uint8_t spi1_csn : 1;
        uint8_t can_rxd : 1;
        uint8_t rsv2 : 1;
    }bits;
}wakeup_src_t;

typedef union wakeup_mode
{
    uint8_t mask;
    struct
    {
        uint8_t spi0_csn_mode : 2;
        uint8_t spi1_csn_mode : 2;
        uint8_t can_rxd_mode : 2;
        uint8_t rsv: 2;
    }bits;
}wakeup_mode_t;

typedef union wakeup_level
{
    uint8_t mask;
    struct
    {
        uint8_t rsv : 5;
        uint8_t spi0_csn_level : 1;
        uint8_t spi1_csn_level : 1;
        uint8_t can_rxd_level : 1;
    }bits;
}wakeup_level_t;

typedef struct wakeup_cfg
{
    wakeup_src_t wakeup_src;     //select wakeup source
    wakeup_mode_t wakeup_mode;   //select wakeup mode  0b00: level, 0b01: posedge edge, 0b10 negedge, 0b11:both edge
    wakeup_level_t wakeup_level; //select wakeup level, only used when wakeup_mode is 0b00, 0: high, 1:low
}wakeup_cfg_t;

typedef struct retention_cfg
{
    uint8_t ret_en;     //0: disable, 1: enable
    uint8_t ret_size;   //uint Kbytes, 16K, 32K, 48k, 64K, 80K, 96K, 112K, 128K
    uint8_t boot_en;    //0: disable retention boot, 1: enable retention boot, bootaddr is the start address of retention ram 0x1ffe0000
}retention_cfg_t;

typedef struct hal_sleep
{
    uint8_t  sleep_type : 1;      //0 auto sleep  1 deepsleep
    uint8_t  clk_sel : 1;         //sleep clk select 0 internal 32KHz clk(note: internal rc clk is not acuracy), 1 external xo 32KHz clk
    uint8_t  sleep_cnt_mode : 2;  //auto sleep count mode. 0: current sleep cnt not clear, 1: current sleep cnt clear, 2: current sleep reload
    uint8_t  latch_en : 1;        //0: disable all wakeup source latch, 1: enable all wakeup source latch
    uint8_t  rsv : 3;
    uint32_t count_load;          //only used when sleep_cnt_mode is 2.
    uint32_t time_us;             //sleep time uinti us
    wakeup_cfg_t wakeup_cofig;    //wakeup source config
    retention_cfg_t ret_cfg;      //retention memory config
}hal_sleep_t;



ERROR_Type hal_sleep_go_sleep(hal_sleep_t *sleep_config);
uint8_t hal_sleep_get_wakeup_status(void);
uint32_t hal_sleep_get_cur_counter(void);
void hal_store_stack_and_sleep(uint32_t sleep_us);
void hal_restore_stack(void);
uint8_t hal_sleep_get_retention_en(void);
#ifdef __cplusplus
}
#endif

#endif
