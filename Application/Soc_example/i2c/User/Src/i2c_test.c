/*****************************************************************************
* File: i2c_test.c
* Descirption: this file contains the functions support i2c test.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/

#include "i2c_test.h"
#include "hal_gpio.h"

#define I2c_INDEX  0

uint8_t g_rx_buff[I2C_TEST_NUM] = {0};
uint8_t g_tx_buff[I2C_TEST_NUM] = {0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27};
volatile uint8_t iic_slave_intr_flag = 0;

static void i2c_master_test(void)
{
    uint8_t        idx                = 0;
    uint8_t        buff[I2C_TEST_NUM] = {0};
    hal_i2c_info_t info_cfg           = {0};
    
    info_cfg.i2c_id = I2c_INDEX;
    info_cfg.buffer = buff;
    info_cfg.len = I2C_TEST_NUM;
    info_cfg.dev_addr = SLAVE_ADDR;
    
    if(SUCCESS == hal_i2c_read_poll(&info_cfg))
    {
        printf("i2c read success!\r\n");
        
        for(idx = 0; idx < I2C_TEST_NUM; idx++)
        {
            printf("%02X ", buff[idx]);
        }
        printf("\r\n");
    }
    else
    {
        printf("i2c read failure!\r\n");
    }
    
    info_cfg.buffer = buff;
    info_cfg.len = I2C_TEST_NUM;
    info_cfg.dev_addr = SLAVE_ADDR;
    
    if(SUCCESS == hal_i2c_write_poll(&info_cfg))
    {
        printf("i2c write success!\r\n");
    }
    else
    {
        printf("i2c write failure!\r\n");
    }
}

static void i2c_slave_irq_callback(void *device, uint32_t wpara, uint32_t lpara)
{
    uint8_t    idx    = 0;
    uint32_t   status = 0;
    
    
    device = device;
    wpara = wpara;
    lpara = lpara;

    status = hal_i2c_get_interrupt_state(I2c_INDEX);

    if ((status & EVENT_RD_REQ) != 0)
    {     
        for (idx = 0; idx < I2C_TEST_NUM; idx++)
        {
            hal_i2c_write_byte(I2c_INDEX, g_tx_buff[idx]);
        }
        hal_i2c_clear_interrrupt_state(I2c_INDEX, EVENT_RD_REQ);
        iic_slave_intr_flag = 2;
    } 
    else if ((status & EVENT_RX_FULL) != 0) 
    {
        for (idx = 0; idx < I2C_TEST_NUM; idx++) 
        {
            g_rx_buff[idx] = hal_i2c_read_byte(I2c_INDEX);
        }
        hal_i2c_clear_interrrupt_state(I2c_INDEX, EVENT_RX_FULL);
        iic_slave_intr_flag=1;
        //DPRINTF("\ti2c-%u slave receive 8 bytes data from master!\n",id);
    }
}

void i2c_slave_test(void)
{
    uint8_t idx = 0;
    
    iic_slave_intr_flag = 0;
    
    while(iic_slave_intr_flag == 0);
    
    printf("i2c rx:");
    for(idx = 0; idx < I2C_TEST_NUM; idx++)
    {
        printf("%02X ", g_rx_buff[idx]);
    }
    
    while(iic_slave_intr_flag == 1);
    
    printf("\r\ni2c tx:");
    for(idx = 0; idx < I2C_TEST_NUM; idx++)
    {
        printf("%02X ", g_tx_buff[idx]);
    }
    printf("\r\n");
}


void user_init(void)
{
    hal_uart_t uart_cfg = {0};
    
    uart_cfg.is_block_mode = 0;
    uart_cfg.is_tx_int_en = 0;
    uart_cfg.is_rx_int_en = 0;
    uart_cfg.baurdrate = B115200;
    hal_uart_init(&uart_cfg);
    
    hal_i2c_t i2c_cfg = {0};
    
    #if(I2C_TEST_MODE == I2C_TEST_MASTER)
    i2c_cfg.i2c_role = 1;
    i2c_cfg.interrupt_en = 0;
    i2c_cfg.i2c_speed = SPEED_FAST;
    #elif(I2C_TEST_MODE == I2C_TEST_SLAVE)
    i2c_cfg.i2c_role = 0;
    i2c_cfg.tx_fifo_trigger_level = 0;
    i2c_cfg.rx_fifo_trigger_level = I2C_TEST_NUM - 1;
    i2c_cfg.interrupt_en = 1;
    i2c_cfg.interrupt_mask = EVENT_RD_REQ | EVENT_RX_FULL;
    i2c_cfg.i2c_speed = SPEED_FAST;
    i2c_cfg.func = (DeviceCallback_Type)&i2c_slave_irq_callback;
    i2c_cfg.slaver_addr = SLAVE_ADDR;
    #endif
    
    hal_i2c_init(&i2c_cfg);
}

void user_test(void)
{
    #if(I2C_TEST_MODE == I2C_TEST_MASTER)
    i2c_master_test();
    #elif(I2C_TEST_MODE == I2C_TEST_SLAVE)
    i2c_slave_test();
    #endif
    
    while(1)
    {
        ;
    }
    
}