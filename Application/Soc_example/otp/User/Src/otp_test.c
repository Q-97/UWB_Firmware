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

#include "otp_test.h"
#include "hal_delay.h"

static uint32_t key_test[8] = {
    0x01010101, 0x02020202, 0x03030303, 0x04040404, 0x05050505, 0x06060606, 0x07070707, 0x08080808,
};
static uint32_t zero_data[8] = {0};
static uint32_t customer_data[MAX_OTP_NUM] = {0};

static void otp_key_programmed_test(void)
{
    uint32_t key[8] = {0};

    
    //programm 0-7 addr and read
    if(SUCCESS == hal_otp_key_write(key_test))
    {
        hal_delay_us(100);
        if(SUCCESS == hal_otp_key_read(key))
        {
            if(0 == memcmp(key, key_test, 8*4))
            {
                LOG_INFO("key addr lock success!");
            }
            else
            {
                LOG_INFO("key addr lock failure!");
            }
        }
        else
        {
            LOG_INFO("key locked can not read");
            if(0 == memcmp(key, zero_data, 8*4))
            {
                LOG_INFO("key addr lock success!\n");
            }
            else
            {
                LOG_INFO("key addr lock failure!\n");
            }
        }
    }
    else
    {
        LOG_INFO("key locked can not write");
        LOG_INFO("reg0-7 data is : ");
        for(uint8_t idx = 0; idx < 8; idx++)
        {
            printf("0x%08x, ",key[idx]);
        }
        LOG_INFO("\r\n");
    }  
}

static void otp_customer_addr_test(void)
{
    uint32_t data = 0;
    uint32_t test_data[128] = {0};

    for(uint8_t idx = 0; idx < MAX_OTP_NUM; idx++)
    {
        customer_data[idx] = idx << 24;
    }
    
    hal_otp_write(CUST_OTP_ADDR, customer_data, MAX_OTP_NUM - CUST_OTP_ADDR);
    hal_delay_us(100);
    hal_otp_read(CUST_OTP_ADDR, test_data, MAX_OTP_NUM - CUST_OTP_ADDR);

    LOG_INFO("read data is : \r\n");
    for(uint8_t idx = 0; idx < (MAX_OTP_NUM - CUST_OTP_ADDR); idx++)
    {
        printf("0x%08x, ",test_data[idx]);
        if(0 == ((idx+1) % 8))
        {
            printf("\r\n");
        }
    }
    LOG_INFO("\r\n");
}


void user_init(void)
{
    hal_uart_t uart_cfg = {0};
    
    uart_cfg.is_block_mode = 0;
    uart_cfg.is_tx_int_en = 0;
    uart_cfg.is_rx_int_en = 0;
    uart_cfg.baurdrate = B115200;
    hal_uart_init(&uart_cfg);
}


void user_test(void)
{
    otp_key_programmed_test();
    otp_customer_addr_test();
}