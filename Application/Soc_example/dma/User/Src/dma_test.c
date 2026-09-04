/*****************************************************************************
* File: dma_test.c
* Descirption: this file contains the functions support dma test.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/

#include "dma_test.h"

hal_dma_t dma_cfg = {0};
volatile uint32_t g_dma_int_flag[3] = {0};

static void dma_irq_callback(uint32_t arg[3])
{
    g_dma_int_flag[0] = arg[0];
    g_dma_int_flag[1] = arg[1];
    g_dma_int_flag[2] = arg[2];
}

static void dma_uart_init(void)
{
    uint8_t uart_id = 0;
    
    //DMA_UART0+RX channel_0 config, RX FIFO->MEM
    dma_cfg.dma_id = 0;
    dma_cfg.channel_config.src_mem.burst_len = BURST_SIZE_1;
    dma_cfg.channel_config.src_mem.addr_change_mode = ADDRESS_NOCHANGE;
    dma_cfg.channel_config.src_mem.transer_width = TRANSFER_WIDTH_8BITS;
    dma_cfg.channel_config.src_mem.addr = hal_uart_get_rx_addr(uart_id);
    
    dma_cfg.channel_config.dst_mem.burst_len = BURST_SIZE_1;
    dma_cfg.channel_config.dst_mem.addr_change_mode = ADDRESS_INCREMENT;
    dma_cfg.channel_config.dst_mem.transer_width = TRANSFER_WIDTH_8BITS;
    dma_cfg.channel_config.dst_mem.addr = MEM_TEST_TEMP;
    
    dma_cfg.channel_config.channel = CHANNEL_NO_0;
    dma_cfg.channel_config.priority = LOW_PRIORITY;
    dma_cfg.channel_config.interrupt_en = 1;
    dma_cfg.channel_config.transfer_dir = uart_id ? UART1_RX_TO_MEM : UART0_RX_TO_MEM;   
    dma_cfg.channel_config.block_count = DMA_MOVE_BYTES;

    dma_cfg.interrupt_config.interrupt_en = 1;
    dma_cfg.interrupt_config.interrupt_type = INTERRUPT_TFR;                     
    dma_cfg.interrupt_config.func = (DMA_CallbackType)&dma_irq_callback;
    
    hal_dma_init(&dma_cfg);
    
    //DMA+UART0+TX channel_1 config MEM->TX FIFO
    dma_cfg.dma_id = 0;
    dma_cfg.channel_config.src_mem.burst_len = BURST_SIZE_1;
    dma_cfg.channel_config.src_mem.addr_change_mode = ADDRESS_INCREMENT;
    dma_cfg.channel_config.src_mem.transer_width = TRANSFER_WIDTH_8BITS;
    dma_cfg.channel_config.src_mem.addr = MEM_TEST_TEMP;
    
    dma_cfg.channel_config.dst_mem.burst_len = BURST_SIZE_1;
    dma_cfg.channel_config.dst_mem.addr_change_mode = ADDRESS_NOCHANGE;
    dma_cfg.channel_config.dst_mem.transer_width = TRANSFER_WIDTH_8BITS;
    dma_cfg.channel_config.dst_mem.addr = hal_uart_get_tx_addr(uart_id);
    
    dma_cfg.channel_config.channel = CHANNEL_NO_1;
    dma_cfg.channel_config.priority = MIDDLE_PRIORITY;
    dma_cfg.channel_config.interrupt_en = 1;
    dma_cfg.channel_config.transfer_dir = uart_id ? MEM_TO_UART1_TX : MEM_TO_UART0_TX;   
    dma_cfg.channel_config.block_count = DMA_MOVE_BYTES;
    
    hal_dma_init(&dma_cfg);    
}

static void dma_uart_test(void)
{
    while(1)
    {
        hal_dma_start_recv(0, CHANNEL_NO_0, (uint8_t*)MEM_TEST_TEMP, 16);
        while(1)
        {
            if((g_dma_int_flag[0] >> CHANNEL_NO_0) & 0x01)
            {
                g_dma_int_flag[0] &= ~(1 << CHANNEL_NO_0);
                break;
            }
        }
        
        hal_dma_start_send(0, CHANNEL_NO_1, (uint8_t*)MEM_TEST_TEMP, 16);
        
        while(1)
        {
            if((g_dma_int_flag[0] >> CHANNEL_NO_1) & 0x01)
            {
                g_dma_int_flag[0] &= ~(1 << CHANNEL_NO_1);
                break;
            }
        }
    }
    hal_dma_channel_close(0, CHANNEL_NO_0);
    hal_dma_channel_close(0, CHANNEL_NO_1);
}


static void dma_spi_slave_init(void)
{
    hal_spi_t spi_cfg = {0};
    
    spi_cfg.spi_id = 1;
    spi_cfg.spi_role = 0;
    spi_cfg.clk_div = 6;
    spi_cfg.data_size = 8;
    spi_cfg.spi_mode = 0;
    spi_cfg.is_lsb = 0;
    spi_cfg.rx_fifo_en = 1;
    spi_cfg.tx_fifo_en = 1;
    spi_cfg.access_mode = 1;
    spi_cfg.tx_interrupt_en = 0;
    spi_cfg.rx_interrupt_en = 0;
    hal_spi_init(&spi_cfg);
    
    //DMA+SPI+RX channel_2 config, RX FIFO->MEM
    dma_cfg.dma_id = 0;
    dma_cfg.channel_config.src_mem.burst_len = BURST_SIZE_8;
    dma_cfg.channel_config.src_mem.addr_change_mode = ADDRESS_NOCHANGE;
    dma_cfg.channel_config.src_mem.transer_width = TRANSFER_WIDTH_8BITS;
    dma_cfg.channel_config.src_mem.addr = hal_spi_get_rx_addr(spi_cfg.spi_id);
    
    dma_cfg.channel_config.dst_mem.burst_len = BURST_SIZE_8;
    dma_cfg.channel_config.dst_mem.addr_change_mode = ADDRESS_INCREMENT;
    dma_cfg.channel_config.dst_mem.transer_width = TRANSFER_WIDTH_8BITS;
    dma_cfg.channel_config.dst_mem.addr = MEM_TEST_TEMP;
    
    dma_cfg.channel_config.channel = CHANNEL_NO_2;
    dma_cfg.channel_config.priority = HIGH_PRIORITY;
    dma_cfg.channel_config.interrupt_en = 1;
    dma_cfg.channel_config.transfer_dir = spi_cfg.spi_id ? SPI1_RX_TO_MEM : SPI0_RX_TO_MEM;   
    dma_cfg.channel_config.block_count = DMA_MOVE_BYTES;

    dma_cfg.interrupt_config.interrupt_en = 1;
    dma_cfg.interrupt_config.interrupt_type = INTERRUPT_TFR;                     
    dma_cfg.interrupt_config.func = (DMA_CallbackType)&dma_irq_callback;
    
    hal_dma_init(&dma_cfg);
    
    //DMA+SPI1+TX channel_3 config MEM->TX FIFO
    dma_cfg.dma_id = 0;
    dma_cfg.channel_config.src_mem.burst_len = BURST_SIZE_4;
    dma_cfg.channel_config.src_mem.addr_change_mode = ADDRESS_INCREMENT;
    dma_cfg.channel_config.src_mem.transer_width = TRANSFER_WIDTH_8BITS;
    dma_cfg.channel_config.src_mem.addr = MEM_TEST_TEMP;
    
    dma_cfg.channel_config.dst_mem.burst_len = BURST_SIZE_4;
    dma_cfg.channel_config.dst_mem.addr_change_mode = ADDRESS_NOCHANGE;
    dma_cfg.channel_config.dst_mem.transer_width = TRANSFER_WIDTH_8BITS;
    dma_cfg.channel_config.dst_mem.addr = hal_spi_get_tx_addr(spi_cfg.spi_id);
    
    dma_cfg.channel_config.channel = CHANNEL_NO_3;
    dma_cfg.channel_config.priority = VERY_HIGH_PRIORITY;
    dma_cfg.channel_config.interrupt_en = 1;
    dma_cfg.channel_config.transfer_dir = spi_cfg.spi_id ? MEM_TO_SPI1_TX : MEM_TO_SPI0_TX;   
    dma_cfg.channel_config.block_count = DMA_MOVE_BYTES;
    
    hal_dma_init(&dma_cfg);    
}

static void dma_spi_slave_test(void)
{
    uint32_t val = 0;
    uint8_t  spi_id = 1;
    
    hal_spi_rx_enable(spi_id);
    hal_dma_start_recv(0, CHANNEL_NO_2, (uint8_t*)MEM_TEST_TEMP, DMA_MOVE_BYTES);
    
    while(1)
    {
        if ((g_dma_int_flag[0]&(1<<CHANNEL_NO_2)) ||
            (g_dma_int_flag[1]&(1<<CHANNEL_NO_2)) ||
            (g_dma_int_flag[2]&(1<<CHANNEL_NO_2)))
        {
            LOG_INFO("status_tfr = 0x%x, status_block = 0x%x, status_err= 0x%x",g_dma_int_flag[0],g_dma_int_flag[1],g_dma_int_flag[2]);
            break;
        }
    }
    
    while(hal_spi_rx_is_byte_avliable(spi_id))
    {
        val = hal_spi_read_byte(spi_id);
    }
    hal_spi_rx_disable(spi_id);
    
    g_dma_int_flag[0] = 0;
    g_dma_int_flag[1] = 0;
    g_dma_int_flag[2] = 0;
    
    hal_spi_tx_enable(spi_id);
    hal_dma_start_send(0, CHANNEL_NO_3, (uint8_t*)MEM_TEST_TEMP, DMA_MOVE_BYTES);
    
    while(1)
    {
        if ((g_dma_int_flag[0]&(1 << CHANNEL_NO_3)) ||
            (g_dma_int_flag[1]&(1 << CHANNEL_NO_3)) ||
            (g_dma_int_flag[2]&(1 << CHANNEL_NO_3)))
        {
            LOG_INFO("status_tfr = 0x%x, status_block = 0x%x, status_err= 0x%x",g_dma_int_flag[0],g_dma_int_flag[1],g_dma_int_flag[2]);
            break;
        }
    }
    
    while(!hal_spi_tx_is_empty(spi_id));
    hal_spi_tx_disable(spi_id);
}


static void dma_spi_master_init(void)
{
    hal_spi_t spi_cfg = {0};
    
    spi_cfg.spi_id = 1;
    spi_cfg.spi_role = 1;
    spi_cfg.clk_div = 10;
    spi_cfg.data_size = 8;
    spi_cfg.spi_mode = 0;
    spi_cfg.is_lsb = 0;
    spi_cfg.rx_fifo_en = 1;
    spi_cfg.tx_fifo_en = 1;
    spi_cfg.access_mode = 1;
    spi_cfg.tx_interrupt_en = 0;
    spi_cfg.rx_interrupt_en = 0;
    hal_spi_init(&spi_cfg);
    
        
    //DMA+SPI+TX channel_0 config, MEM -> TX FIFO
    dma_cfg.dma_id = 0;
    dma_cfg.channel_config.src_mem.burst_len = BURST_SIZE_8;
    dma_cfg.channel_config.src_mem.addr_change_mode = ADDRESS_INCREMENT;
    dma_cfg.channel_config.src_mem.transer_width = TRANSFER_WIDTH_8BITS;
    dma_cfg.channel_config.src_mem.addr = MEM_TEST_SRC;
    
    dma_cfg.channel_config.dst_mem.burst_len = BURST_SIZE_8;
    dma_cfg.channel_config.dst_mem.addr_change_mode = ADDRESS_NOCHANGE;
    dma_cfg.channel_config.dst_mem.transer_width = TRANSFER_WIDTH_8BITS;
    dma_cfg.channel_config.dst_mem.addr = hal_spi_get_tx_addr(spi_cfg.spi_id);
    
    dma_cfg.channel_config.channel = CHANNEL_NO_0;
    dma_cfg.channel_config.priority = LOW_PRIORITY;
    dma_cfg.channel_config.interrupt_en = 1;
    dma_cfg.channel_config.transfer_dir = spi_cfg.spi_id ? MEM_TO_SPI1_TX : MEM_TO_SPI0_TX;   
    dma_cfg.channel_config.block_count = DMA_MOVE_BYTES;

    dma_cfg.interrupt_config.interrupt_en = 1;
    dma_cfg.interrupt_config.interrupt_type = INTERRUPT_TFR;                     
    dma_cfg.interrupt_config.func = (DMA_CallbackType)&dma_irq_callback;
    
    hal_dma_init(&dma_cfg);
    
    //DMA+SPI+RX channel_1 config RX FIFO -> MEM
    dma_cfg.dma_id = 0;
    dma_cfg.channel_config.src_mem.burst_len = BURST_SIZE_8;
    dma_cfg.channel_config.src_mem.addr_change_mode = ADDRESS_NOCHANGE;
    dma_cfg.channel_config.src_mem.transer_width = TRANSFER_WIDTH_8BITS;
    dma_cfg.channel_config.src_mem.addr = hal_spi_get_rx_addr(spi_cfg.spi_id);
    
    dma_cfg.channel_config.dst_mem.burst_len = BURST_SIZE_8;
    dma_cfg.channel_config.dst_mem.addr_change_mode = ADDRESS_INCREMENT;
    dma_cfg.channel_config.dst_mem.transer_width = TRANSFER_WIDTH_8BITS;
    dma_cfg.channel_config.dst_mem.addr = MEM_TEST_DST;
    
    dma_cfg.channel_config.channel = CHANNEL_NO_1;
    dma_cfg.channel_config.priority = MIDDLE_PRIORITY;
    dma_cfg.channel_config.interrupt_en = 1;
    dma_cfg.channel_config.transfer_dir = spi_cfg.spi_id ? SPI1_RX_TO_MEM : SPI0_RX_TO_MEM;   
    dma_cfg.channel_config.block_count = DMA_MOVE_BYTES;
    
    hal_dma_init(&dma_cfg);     
}

static void dma_spi_master_test(void)
{
    uint16_t idx    = 0;
    uint32_t val    = 0;
    uint8_t spi_id = 1;
    uint8_t spi_cs = 0;
    
    for(idx = 0; idx < DMA_MOVE_BYTES; idx++)
    {
        *(uint8_t*)(MEM_TEST_SRC + idx) = idx;
    }
    
    hal_spi_tx_enable(spi_id);
    hal_spi_cs_low(spi_id, spi_cs);
    hal_dma_start_send(0, CHANNEL_NO_0, (uint8_t*)MEM_TEST_SRC, DMA_MOVE_BYTES);

    while(1)
    {
        if((g_dma_int_flag[0] >> CHANNEL_NO_0) & 0x01)
        {
            g_dma_int_flag[0] &= ~(1 << CHANNEL_NO_0);
            break;
        }
    }
    
    while(!hal_spi_tx_is_empty(spi_id));
    hal_spi_cs_high(spi_id, spi_cs);
    hal_spi_tx_disable(spi_id);
    
    hal_delay_ms(100);
    
    hal_spi_cs_low(spi_id, spi_cs);
    hal_spi_rx_enable(spi_id);
    hal_spi_rx_match_num_set(spi_id, DMA_MOVE_BYTES);
    hal_dma_start_recv(0, CHANNEL_NO_1, (uint8_t*)MEM_TEST_DST, DMA_MOVE_BYTES);

    while(1)
    {
        if((g_dma_int_flag[0] >> CHANNEL_NO_1) & 0x01)
        {
            g_dma_int_flag[0] &= ~(1 << CHANNEL_NO_1);
            break;
        }
    }
    
    while(hal_spi_rx_is_byte_avliable(spi_id))
    {
        val = hal_spi_read_byte(spi_id);
    }
    hal_spi_rx_disable(spi_id);
    hal_spi_cs_high(spi_id, spi_cs);
    
    for(idx = 0; idx < DMA_MOVE_BYTES; idx++)
    {
        if(*(uint8_t*)(MEM_TEST_DST + idx) != *(uint8_t*)(MEM_TEST_SRC + idx))
        {
            LOG_INFO("transfer DMA+SPI master test is fail....");
            return;
        }
    }
    LOG_INFO("transfer DMA+SPI master test is success....");
    
    hal_dma_channel_close(0, CHANNEL_NO_0);
    hal_dma_channel_close(0, CHANNEL_NO_1);
}

static void dma_mem2mem_poll_test(void)
{
    uint16_t idx = 0;
    
    sys_clear_bit(CLK_ICG_REG,CLK_ICG_REG_DMA_CLK_ICG_SHIFT);
    sys_clear_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_DMA_SW_RSTN_SHIFT); 
    sys_set_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_DMA_SW_RSTN_SHIFT); 
    
    dma_cfg.dma_id = 0;
    dma_cfg.channel_config.src_mem.burst_len = BURST_SIZE_8;
    dma_cfg.channel_config.src_mem.addr_change_mode = ADDRESS_INCREMENT;
    dma_cfg.channel_config.src_mem.transer_width = TRANSFER_WIDTH_32BITS;
    dma_cfg.channel_config.src_mem.addr = MEM_TEST_SRC;
    
    dma_cfg.channel_config.dst_mem.burst_len = BURST_SIZE_8;
    dma_cfg.channel_config.dst_mem.addr_change_mode = ADDRESS_INCREMENT;
    dma_cfg.channel_config.dst_mem.transer_width = TRANSFER_WIDTH_32BITS;
    dma_cfg.channel_config.dst_mem.addr = MEM_TEST_DST;
    
    dma_cfg.channel_config.channel = CHANNEL_NO_0;
    dma_cfg.channel_config.priority = MIDDLE_PRIORITY;
    dma_cfg.channel_config.interrupt_en = 0;
    dma_cfg.channel_config.transfer_dir = MEM_TO_MEM;   
    dma_cfg.channel_config.block_count = MEM2MEM_TEST_L;

    hal_dma_init(&dma_cfg);
    
    LOG_INFO("dma poll: mem2mem");
    LOG_INFO("transfer %d bytes from address 0x%x to 0x%x",MEM2MEM_TEST_L, MEM_TEST_SRC, MEM_TEST_DST);
    
    for(idx = 0; idx < MEM2MEM_TEST_L; idx++)
    {
        *(uint8_t*)(MEM_TEST_SRC + idx) = idx;
    }
    
    hal_dma_channel_start(0, CHANNEL_NO_0);
    while(!hal_dma_channel_done(0, CHANNEL_NO_0));
    hal_dma_channel_close(0, CHANNEL_NO_0);
    
    for(idx = 0; idx < MEM2MEM_TEST_L; idx++)
    {
        if(*(uint8_t*)(MEM_TEST_DST + idx) != *(uint8_t*)(MEM_TEST_SRC + idx))
        {
            LOG_INFO("transfer mem2mem test is fail....");
            return;
        }
    }
    LOG_INFO("transfer mem2mem test is success....");    

}

static void dma_mem2mem_irq_test(void)
{
    uint16_t idx = 0;
    
    sys_clear_bit(CLK_ICG_REG,CLK_ICG_REG_DMA_CLK_ICG_SHIFT);
    sys_clear_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_DMA_SW_RSTN_SHIFT); 
    sys_set_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_DMA_SW_RSTN_SHIFT); 
    
    dma_cfg.dma_id = 0;
    dma_cfg.channel_config.src_mem.burst_len = BURST_SIZE_8;
    dma_cfg.channel_config.src_mem.addr_change_mode = ADDRESS_INCREMENT;
    dma_cfg.channel_config.src_mem.transer_width = TRANSFER_WIDTH_32BITS;
    dma_cfg.channel_config.src_mem.addr = MEM_TEST_SRC;
    
    dma_cfg.channel_config.dst_mem.burst_len = BURST_SIZE_8;
    dma_cfg.channel_config.dst_mem.addr_change_mode = ADDRESS_INCREMENT;
    dma_cfg.channel_config.dst_mem.transer_width = TRANSFER_WIDTH_32BITS;
    dma_cfg.channel_config.dst_mem.addr = MEM_TEST_DST;
    
    dma_cfg.channel_config.channel = CHANNEL_NO_0;
    dma_cfg.channel_config.priority = MIDDLE_PRIORITY;
    dma_cfg.channel_config.interrupt_en = 1;
    dma_cfg.channel_config.transfer_dir = MEM_TO_MEM;   
    dma_cfg.channel_config.block_count = MEM2MEM_TEST_L;

    dma_cfg.interrupt_config.interrupt_en = 1;
    dma_cfg.interrupt_config.interrupt_type = INTERRUPT_TFR;                     
    dma_cfg.interrupt_config.func = (DMA_CallbackType)&dma_irq_callback;
    
    hal_dma_init(&dma_cfg);
    
    LOG_INFO("dma irq: mem2mem");
    LOG_INFO("transfer %d bytes from address 0x%x to 0x%x",MEM2MEM_TEST_L, MEM_TEST_SRC, MEM_TEST_DST);
    
    for(idx = 0; idx < MEM2MEM_TEST_L; idx++)
    {
        *(uint8_t*)(MEM_TEST_SRC + idx) = idx;
    }
    
    hal_dma_channel_start(0, CHANNEL_NO_0);
    while(1)
    {
        if ((g_dma_int_flag[0] & (1 << CHANNEL_NO_0)) ||
            (g_dma_int_flag[1] & (1 << CHANNEL_NO_0)) ||
            (g_dma_int_flag[2] & (1 << CHANNEL_NO_0)))
        {
            LOG_INFO("status_tfr = 0x%x, status_block = 0x%x, status_err= 0x%x",g_dma_int_flag[0],g_dma_int_flag[1],g_dma_int_flag[2]);
            break;
        }
    }
    hal_dma_channel_close(0, CHANNEL_NO_0);
    
    for(idx = 0; idx < MEM2MEM_TEST_L; idx++)
    {
        if(*(uint8_t*)(MEM_TEST_DST + idx) != *(uint8_t*)(MEM_TEST_SRC + idx))
        {
            LOG_INFO("transfer mem2mem test is fail....");
            return;
        }
    }
    LOG_INFO("transfer mem2mem test is success....");
}

void user_init(void)
{
    hal_uart_t uart_cfg = {0};
    
    uart_cfg.uart_id = 0;
    uart_cfg.group_sel = 0;
    uart_cfg.is_block_mode = 0;
    uart_cfg.is_tx_int_en = 0;
    uart_cfg.is_rx_int_en = 0;
    uart_cfg.baurdrate = B115200;
    
    hal_uart_init(&uart_cfg);

    #if(DMA_TEST_TYPE == DMA_UART_TEST)
    dma_uart_init();
    #elif(DMA_TEST_TYPE == DMA_SPI_SLAVR_TEST)
    dma_spi_slave_init();
    #elif(DMA_TEST_TYPE == DMA_SPI_MASTER_TEST)
    dma_spi_master_init();
    #elif(DMA_TEST_TYPE == DMA_I2C_TEST)
    #endif    
}

void user_test(void)
{
    #if(DMA_TEST_TYPE == DMA_UART_TEST)
    dma_uart_test();
    #elif(DMA_TEST_TYPE == DMA_SPI_SLAVR_TEST)
    dma_spi_slave_test();
    #elif(DMA_TEST_TYPE == DMA_SPI_MASTER_TEST)
    dma_spi_master_test();
    #elif(DMA_TEST_TYPE == DMA_MEM_TO_MEM_TEST)
    dma_mem2mem_poll_test();
    dma_mem2mem_irq_test();
    #elif(DMA_TEST_TYPE == DMA_I2C_TEST)
    #endif

}    