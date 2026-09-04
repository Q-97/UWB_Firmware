/*****************************************************************************
* File: spi_test.c
* Descirption: this file contains the functions support spi test.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/

#include "spi_test.h"
#include "hal_gpio.h"


uint8_t g_spi_rx_data_buff[SPI_RX_BUFF_LENGTH] = {0};
uint8_t g_spi_tx_data_buff[SPI_TX_BUFF_LENGTH] = {0};
volatile uint8_t g_spi_rx_index = 0;
volatile uint8_t g_spi_tx_index = 0;
uint8_t g_spi_data_size_msk = 0xFF;

static void spi_irq_callback(ZN_SpiType *SPIx, uint32_t wpara, uint32_t lpara);

hal_spi_t spi_cfg = 
{
    #ifdef SPI_TEST_MASTER
    .spi_id = SPI_TEST_ID,
    .spi_cs = 0,
    .spi_role = 1,
    .is_lsb = 0,
    .tx_fifo_en = 1,
    .rx_fifo_en = 1,
    .access_mode = 0,
    .tx_interrupt_en = 0,
    .rx_interrupt_en = 0,
    .spi_mode = SPI_MODE3,
    .data_size = 8,
    .clk_div = 6,
    .func = NULL
    #else
    .spi_id = SPI_TEST_ID,
    .spi_cs = 0,
    .spi_role = 0,
    .is_lsb = 0,
    .tx_fifo_en = 0,
    .rx_fifo_en = 0,
    .access_mode = 0,
    .tx_interrupt_en = 0,
    .rx_interrupt_en = 1,
    .spi_mode = SPI_MODE3,
    .data_size = 8,
    .clk_div = 6,
    .func = (DeviceCallback_Type)&spi_irq_callback
    #endif
};

/**
 * wait_for_reply - Waits for a reply on UART0
 *
 * @param[in] None
 * @return 0 if the reply is 'n', 1 if the reply is 'y', and 2 otherwise
 *
 * @brief This function waits for a reply on UART0 and returns the result. 
 */
uint32_t wait_for_reply(void)
{
    uint8_t i;
    uint8_t ch;
    char answer[20];

    for(i = 0; i < 20; i++)
    {
        answer[i] = '\0';
    }
    i = 0;
    while(1)
    {
        ch = hal_uart_get_char(0);

        //JJJ_DEBUG CK_Uart_PutChar(consoleuart,ch);
        if ((ch == '\n' || ch == '\r'))
        {
            if(!i)
            {
                continue;
            }
            else
            {
                answer[i] = '\0';
                break;
            }
        }
        if(ch == '\b')
        {
             if(i > 0)
             {
                i--;
                hal_uart_put_char(0, ch);
             }
        }
        else
        {
            answer[i++] = ch;
            hal_uart_put_char(0, ch);
        }
    }
    if((i == 1) && (answer[0] == 'y'))
    {
        return 1;
    }
    else if((i == 1) && (answer[0] == 'n'))
    {
        return 0;
    }
    return 2;
}
static void spi_irq_callback(ZN_SpiType *SPIx, uint32_t wpara, uint32_t lpara)
{
    uint8_t spi_id = SPI_ID(SPIx);
    uint32_t temp = 0;
    
    if (wpara & TX_AVL_INTF_MSK)
    {
        while(!hal_spi_tx_is_full(spi_id))
        {
            if (g_spi_tx_index < SPI_TX_BUFF_LENGTH)
            {
                spi_write_data(SPIx, g_spi_tx_data_buff[g_spi_tx_index]);
                g_spi_tx_index++;
            }
            else
            {
                spi_int_tx_avl_disable(SPIx);
                break;
            }
        }
    }
    if (wpara & RX_AVL_INTF_MSK) /*This bit is set when Receiver FIFO has received enough data(depend on rxtlf--Global Control Register bit 5).*/
    {
        /*receiver FIFO has available data*/
        while(hal_spi_rx_is_byte_avliable(spi_id))
        {
            if (g_spi_rx_index < SPI_RX_BUFF_LENGTH)
            {
                g_spi_rx_data_buff[g_spi_rx_index] = spi_read_data(SPIx) & g_spi_data_size_msk;
                g_spi_rx_index++;
            }
            else
            {
                temp = spi_read_data(SPIx) & g_spi_data_size_msk;
            }
        }
    }
}

void user_init(void)
{
    hal_uart_t uart_cfg = {0};
    
    uart_cfg.is_block_mode = 0;
    uart_cfg.is_tx_int_en = 0;
    uart_cfg.is_rx_int_en = 0;
    uart_cfg.baurdrate = B115200;
    hal_uart_init(&uart_cfg);

    hal_spi_init(&spi_cfg); 
}


void user_test(void)
{
    uint8_t idx = 0;
    
    g_spi_rx_index = 0;
    g_spi_tx_index = 0;
    
#ifdef SPI_TEST_MASTER
    //spi master
    for(idx = 0; idx < SPI_TX_BUFF_LENGTH; idx++)
    {
        g_spi_tx_data_buff[idx] = idx;
        g_spi_rx_data_buff[idx] = 0;
    }
    //master send
    if(SUCCESS == hal_spi_transmit_poll(spi_cfg.spi_id, spi_cfg.spi_cs, g_spi_tx_data_buff, SPI_TX_BUFF_LENGTH))
    {
        LOG_INFO("spi master send: ");
        for(idx = 0; idx < SPI_TX_BUFF_LENGTH; idx++)
        {
            printf("%02X ", g_spi_tx_data_buff[idx]);
        }
        LOG_INFO();
    }
//    while(!hal_gpio_get_val(SPI_TEST_PIN));
    
    LOG_INFO("spi slave is send? [y/n]");
    if(wait_for_reply() != 1)
    {
        ;
    }
    //master recv
    if(SUCCESS == hal_spi_recv_poll(spi_cfg.spi_id, spi_cfg.spi_cs, g_spi_rx_data_buff, SPI_RX_BUFF_LENGTH))
    {
        LOG_INFO("spi master recv: ");
        for(idx = 0; idx < SPI_RX_BUFF_LENGTH; idx++)
        {
            printf("%02X ", g_spi_rx_data_buff[idx]);
        }
        LOG_INFO();
    }
#else
    //spi slave 
    for(idx = 0; idx < SPI_TX_BUFF_LENGTH; idx++)
    {
        g_spi_tx_data_buff[idx] = 0;
        g_spi_rx_data_buff[idx] = 0;
    }
    //slave rx
    hal_spi_rx_enable(spi_cfg.spi_id);
    while(!(g_spi_rx_index >= SPI_RX_BUFF_LENGTH));
    hal_spi_rx_disable(spi_cfg.spi_id);
    
    LOG_INFO("spi slave recv: ");
    for(idx = 0; idx < SPI_RX_BUFF_LENGTH; idx++)
    {
        g_spi_tx_data_buff[idx] = g_spi_rx_data_buff[idx] + 0x80;
        printf("%02X ", g_spi_rx_data_buff[idx]);
    }
    LOG_INFO();
    
    spi_transmit_poll(SPI_BASE(spi_cfg.spi_id), 0, g_spi_tx_data_buff, SPI_TX_BUFF_LENGTH);
    
#endif
}