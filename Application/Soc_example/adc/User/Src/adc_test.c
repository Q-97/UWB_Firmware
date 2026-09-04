/*****************************************************************************
* File: adc_test.c
* Descirption: this file contains the functions support adc test.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/

#include "adc_test.h"
#include "hal_delay.h"



void user_init(void)
{
    hal_uart_t uart_cfg = {0};
    
    uart_cfg.is_block_mode = 0;
    uart_cfg.is_tx_int_en = 0;
    uart_cfg.is_rx_int_en = 0;
    uart_cfg.baurdrate = B115200;
    hal_uart_init(&uart_cfg);

    hal_adc_cali_init();
}


void user_test(void)
{
    double cur_vbat = 0.0;
    double cur_vtestp = 0.0;
    double cur_temperature = 0.0;
    
    cur_vbat = hal_adc_get_cur_vbat_voltage();
    cur_vtestp = hal_adc_get_cur_vtestp_voltage();
    cur_temperature = hal_adc_get_cur_temperature();
    
    LOG_INFO("current vbat is %3.2f, current vtestp is %3.2f, current temperature is %3.2f", cur_vbat, cur_vtestp, cur_temperature);

    hal_delay_ms(3000);
}