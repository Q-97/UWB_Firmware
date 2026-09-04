/*****************************************************************************
 *  File: hal_dma.c
 *
 * Descirption: this file contains the functions support dma operations.
 *
 *  Copyright (C) : 2025 ultraception.com
 *
 *  Author: sxg
 *  Mail:   
 *  Date:   2025-5-12
 *
 *****************************************************************************/
 
 #include "hal_dma.h"
 
 
ERROR_Type hal_dma_init(hal_dma_t* dma_cfg)
{
    DMA_ConfigType   dma_config = {0};
    DMA_ChConfigType dma_channel_cnfig = {0};
    
    if(NULL == dma_cfg)
    {
        LOG_ERROR("null pointer");
        return ERROR;
    }
    
    sys_clear_bit(CLK_ICG_REG,CLK_ICG_REG_DMA_CLK_ICG_SHIFT);
    sys_set_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_DMA_SW_RSTN_SHIFT);
    
    dma_config.irq           = DMA0_IRQn;
    dma_config.interruptEn   = dma_cfg->interrupt_config.interrupt_en;
    dma_config.interruptType = (DMA_IntType)dma_cfg->interrupt_config.interrupt_type;
    dma_config.callBack      = dma_cfg->interrupt_config.func;
    
    dma_init(dma_cfg->dma_id, &dma_config);
    
    /*DMA+UART0+RX channel_0 config, RX FIFO->MEM*/
    dma_channel_cnfig.srcAddr      = dma_cfg->channel_config.src_mem.addr;
    dma_channel_cnfig.destAddr     = dma_cfg->channel_config.dst_mem.addr;
    dma_channel_cnfig.srcMsize     = (DMA_BusrtTransferSize)dma_cfg->channel_config.src_mem.burst_len;
    dma_channel_cnfig.destMsize    = (DMA_BusrtTransferSize)dma_cfg->channel_config.dst_mem.burst_len; 
    dma_channel_cnfig.srcAddrInc   = (DMA_AddressIncType)dma_cfg->channel_config.src_mem.addr_change_mode;
    dma_channel_cnfig.destAddrInc  = (DMA_AddressIncType)dma_cfg->channel_config.dst_mem.addr_change_mode;
    dma_channel_cnfig.srcTrWidth   = (DMA_TransferWidth)dma_cfg->channel_config.src_mem.transer_width;
    dma_channel_cnfig.destTrWidth  = (DMA_TransferWidth)dma_cfg->channel_config.dst_mem.transer_width;  
    dma_channel_cnfig.transferDir  = (DMA_TransferDir)dma_cfg->channel_config.transfer_dir;
    dma_channel_cnfig.blockCnt     = dma_cfg->channel_config.block_count;
    dma_channel_cnfig.channel      = dma_cfg->channel_config.channel;
    dma_channel_cnfig.priority     = (DMA_PriorityType)dma_cfg->channel_config.priority;
    dma_channel_cnfig.interruptEn  = dma_cfg->channel_config.interrupt_en;

    dma_chan_init(dma_cfg->dma_id,&dma_channel_cnfig);
    
    return SUCCESS;
}

void hal_dma_start_recv(uint8_t dma_id, uint8_t channel, uint8_t* buffer, uint32_t len)
{
    write_mreg32(DMAC_DAR(dma_id, channel), (uint32_t)buffer);
    write_mreg32(DMAC_CTLH(dma_id, channel), len);
    dma_chan_start(dma_id, channel);
}

void hal_dma_start_send(uint8_t dma_id, uint8_t channel, uint8_t* buffer, uint32_t len)
{
    write_mreg32(DMAC_SAR(dma_id, channel), (uint32_t)buffer);
    write_mreg32(DMAC_CTLH(dma_id, channel), len);
    dma_chan_start(dma_id, channel);
}

void hal_dma_channel_start(uint8_t dma_id, uint8_t channel)
{
    dma_chan_start(dma_id, channel);
}

void hal_dma_channel_close(uint8_t dma_id, uint8_t channel)
{
    dma_chan_close(dma_id, channel);
}

uint8_t hal_dma_channel_done(uint8_t dma_id, uint8_t channel)
{
    return dma_chan_check_done_poll(dma_id, channel);
}