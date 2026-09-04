/*****************************************************************************
 *  File: zn_soc_hal.c
 *
 * Descirption: this file contains the functions support systick operations.
 *
 *  Copyright (C) : 2023 ultraception.com
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2023-6-12
 *
 *****************************************************************************/
#include "zn_delay.h"
#include "zn_interface.h"
#include "zn_sys_tick.h"
#include "hal_soc.h"
#include "hal_flash.h"



void hal_soc_clk_init(uint8_t div)
{
    uint32_t val = sys_ctrl_read(SOC_CLK_CFG);

    val |= (div & 0x0f) << 4;

    sys_ctrl_write(SOC_CLK_CFG, val);

    zn_delay_init();
}

void hal_soc_get_unique_id(uint8_t* data)
{
    zn_get_device_id(data);
}

void hal_soc_init(void)
{
    hal_soc_clk_init(0);
    //zn_otp_load();   // to reduce initiation time, delete this function call  should delete for low power use
    hal_flash_init();// to reduce initiation time, delete this function call  should delete for low power use
    __enable_irq();
}
