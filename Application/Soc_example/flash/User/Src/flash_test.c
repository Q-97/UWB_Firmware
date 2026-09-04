/*****************************************************************************
* File: spi_test.c
* Descirption: this file contains the functions support spi test.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*    addr 0x00000000-0x00080000 is offset, the flash base addr is 0x08000000
*    last 8K  are reserved by the manufacturer to store agc calculate paramters
*
*    ------------  0x00000000
*   |            |
*   |            |
*   |            |
*   |            |
*   |            |
*   |            |
*   |            |
*   |------------|0x0007e000
*   |  reserved  |
*   |            |
*    ------------ 0x00080000
*****************************************************************************/

#include "flash_test.h"

uint8_t g_wr_buff[MAX_FLASH_TEST_SIZE] = {0};
uint8_t g_rd_buff[MAX_FLASH_TEST_SIZE] = {0};





void user_init(void)
{
    hal_uart_t uart_cfg = {0};
    
    uart_cfg.is_block_mode = 0;
    uart_cfg.is_tx_int_en = 0;
    uart_cfg.is_rx_int_en = 0;
    uart_cfg.baurdrate = B115200;
    uart_cfg.func = NULL;
    
    hal_uart_init(&uart_cfg);
    
    hal_flash_init();

}


void user_test(void)
{
    uint16_t idx      = 0;
    uint8_t  cmp_flag = 0;
    
    for(idx = 0; idx < MAX_FLASH_TEST_SIZE; idx++)
    {
        g_wr_buff[idx] = idx;
    }
    
    __disable_irq();
    
    if(SUCCESS == hal_flash_write_data_bytes(g_wr_buff, FLASH_TEST_ADDR, MAX_FLASH_TEST_SIZE))
    {
        LOG_INFO("flash write success!");
        
        if(SUCCESS == hal_flash_read_data((uint32_t *)g_rd_buff, FLASH_TEST_ADDR, MAX_FLASH_TEST_SIZE/4))
        {
            LOG_INFO("flash read success!");
            for(idx = 0; idx < MAX_FLASH_TEST_SIZE; idx++)
            {
                if(g_rd_buff[idx] != g_wr_buff[idx])
                {
                    cmp_flag = 1;
                    break;
                }
            }
            
            if(!cmp_flag)
            {
                LOG_INFO("test success, read data are the same with write data!");
            }
            else
            {
                LOG_INFO("test failure, read data are the same with write data!");
            }
        }
        else
        {
            LOG_INFO("flash read failure!");
        }
    }
    else
    {
        LOG_INFO("flash write failure!");
    }
    __enable_irq();
}



