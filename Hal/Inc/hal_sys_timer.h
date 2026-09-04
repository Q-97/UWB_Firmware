/*****************************************************************************
* File: hal_sys_timer.h
*
* Descirption: this file contains the systimer hal functions.
*
* Copyright (C) : 2025 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2025 - 5
*****************************************************************************/
#ifndef _HAL_SYS_TIMER_H
#define _HAL_SYS_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "zn_soc.h"
#include "zn_sys_timer.h"

#define MAX_CMP_CH_NUM    8
#define MAX_CAP_CH_NUM    4

#define CAP_RISE_EDGE     0x00
#define CAP_FALL_EDGE     0x01
#define CAP_BOTH_EDGE     0x10

#define CAP_EDGE_OFFSET   2
#define CAP_GPIO_OFFSET   8

#define IRQ_CMP_STATUS(ch)  (1 << ch)
#define IRQ_CAP_STATUS(ch)  (1 << (9 + ch))
#define IRQ_OVF_STATUS      (1 << 8)



typedef union octet
{
    uint8_t mask;
    struct
    {
        uint8_t bit0 : 1;
        uint8_t bit1 : 1;
        uint8_t bit2 : 1;
        uint8_t bit3 : 1;
        uint8_t bit4 : 1;
        uint8_t bit5 : 1;
        uint8_t bit6 : 1;
        uint8_t bit7 : 1;
    }bits;
}octet_t;

typedef struct compare_config
{
    octet_t  channel_en;                    //bit0 - bit7 correspond to channel 0 - channel 7, and multiple channels can be configured simultaneously
    octet_t  interrupt_mask;                //bitx correspond to interrupt for channel x 
    uint32_t compare_val[MAX_CMP_CH_NUM];   //compare value for each channel
}compare_config_t;

typedef struct capture_config
{
    octet_t  channel_en;                //bit0 - bit3 correspond to channel 0 - channel 3, and multiple channels can be configured simultaneously
    octet_t  interrupt_mask;            //bitx correspond to interrupt for channel x 
    uint8_t  dege_cfg[MAX_CAP_CH_NUM];  //capture edge of gpio for each channel
    uint8_t  gpio_sel[MAX_CAP_CH_NUM];  //capture gpio sel for each channel value 0-31    
}capture_config_t;

typedef struct hal_sys_timer
{
    uint8_t overflow_interrupt_en;      //systimer overflow interrupt enable 0: disable, 1: enable
    compare_config_t cmpare_cfg;        //compare use config
    capture_config_t capture_cfg;       //capture use config
    SysTimerCallback func;           //systimer interrupt callback
}hal_sys_timer_t;



ERROR_Type hal_sys_timer_init(hal_sys_timer_t *sys_timer_config);
uint32_t hal_get_cur_sys_timer_val(void);
uint32_t hal_get_cap_val(uint8_t ch);
void hal_sys_timer_clear_en(uint8_t status);
void hal_sys_timer_pause_en(uint8_t status);
void hal_sys_timer_cmp_channel_en(uint8_t ch, uint8_t status);
void hal_sys_timer_cap_channel_en(uint8_t ch, uint8_t status);
void hal_sys_timer_cmp_all_channel_disable(void);
void hal_sys_timer_cap_all_channel_disable(void);

#ifdef __cplusplus
}
#endif

#endif
