/*****************************************************************************
* File: hal_gp_timer.h
*
* Descirption: this file contains the uart hal functions.
*
* Copyright (C) : 2025 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2025 - 5
*****************************************************************************/
#ifndef _HAL_GP_TIMER_H
#define _HAL_GP_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "zn_timer.h"

#define PLL_CLK     0
#define XO_CLK      1
#define RC_CLK      2

#define TIMER_CLK_DIV_BITOFFSET    4
#define TIMER_CLK_DIV_BITMASK      0xf0
#define TIMER_CLK_SEL_BITOFFSET    0
#define TIMER_CLK_SEL_BITMASK      0x3

#define TIMER_FREE_RUNNING   0
#define TIMER_USER_DEFINE    1

typedef struct hal_gp_timer
{
    uint8_t timer_id : 2;         //timer id, 0 TIMER0, 1 TIMER1, 2 TIMER2
    uint8_t interrupt_en : 1;     //deassert an interrupt when count down to 0
    uint8_t pwm_en : 1;           //if this bit set, interrupt_en bit will be ignored.
    uint8_t mode : 1;             //timer mode, 0 free runging mode, 1 user defined mode
    uint8_t rsv : 3;
    uint8_t clk_div : 4;          //clock divider factor, 4bits
    uint8_t clk_src : 2;          //clock source select  0: PLL_CLK(125M), 1: XO_CLK(38.4M), 2: RC_CLK(inner 13K or ext 32K)
    uint8_t rsv1 : 2;
    uint32_t time1;               //time set for timer uint us
    uint32_t time2;               //time for second half duty uint us only used when pwm_en set 1
    TIMER_CallbackType func;      //interruput callback function
}hal_gp_timer_t;



ERROR_Type hal_gp_timer_init(hal_gp_timer_t *gp_timer_config);
ERROR_Type hal_gp_timer_deinit(uint8_t timer_id);
ERROR_Type hal_gp_timer_start(uint8_t timer_id);
ERROR_Type hal_gp_timer_close(uint8_t timer_id);
ERROR_Type hal_gp_timer_interrupt_enable(uint8_t timer_id);
ERROR_Type hal_gp_timer_interrupt_disable(uint8_t timer_id);
void hal_gp_timer_set_loadval(uint8_t timer_id, uint32_t loadval);
void hal_gp_timer_set_loadval2(uint8_t timer_id, uint32_t loadval);
void hal_gp_timer_reset_cnt(uint8_t timer_id);
uint32_t hal_get_gp_timer_clk_freq(uint8_t timer_id);

#ifdef __cplusplus
}
#endif

#endif
