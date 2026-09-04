/*****************************************************************************
 *  File: hal_dma.h
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
#ifndef __HAL_DMA_H__
#define __HAL_DMA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "zn_dma.h"

#define CHANNEL_NO_0    DMA_CHANNEL_0
#define CHANNEL_NO_1    DMA_CHANNEL_1
#define CHANNEL_NO_2    DMA_CHANNEL_2
#define CHANNEL_NO_3    DMA_CHANNEL_3

#define ADDRESS_INCREMENT    0x00
#define ADDRESS_DECREMENT    0x01
#define ADDRESS_NOCHANGE     0x02

#define BURST_SIZE_1         0x00        //Number of data items to be transferred is 1
#define BURST_SIZE_4         0x01        //Number of data items to be transferred is 4
#define BURST_SIZE_8         0x02        //Number of data items to be transferred is 8
#define BURST_SIZE_16        0x03        //Number of data items to be transferred is 16
#define BURST_SIZE_32        0x04        //Number of data items to be transferred is 32
#define BURST_SIZE_64        0x05        //Number of data items to be transferred is 64
#define BURST_SIZE_128       0x06        //Number of data items to be transferred is 128
#define BURST_SIZE_256       0x07        //Number of data items to be transferred is 256

#define TRANSFER_WIDTH_8BITS   0x00
#define TRANSFER_WIDTH_16BITS  0x01
#define TRANSFER_WIDTH_32BITS  0x02

#define MEM_TO_SPI0_TX         0x00
#define SPI0_RX_TO_MEM         0x01
#define MEM_TO_SPI1_TX         0x02
#define SPI1_RX_TO_MEM         0x03
#define MEM_TO_UART1_TX        0x04
#define UART1_RX_TO_MEM        0x05
#define MEM_TO_I2C0_TX         0x06
#define I2C0_RX_TO_MEM         0x07
#define MEM_TO_UART0_TX        0x08
#define UART0_RX_TO_MEM        0x09
#define MEM_TO_I2C1_TX         0x0A
#define I2C1_RX_TO_MEM         0x0B
#define MEM_TO_MEM             0x0C


#define INTERRUPT_BLOCK        0x01
#define INTERRUPT_TFR          0x02
#define INTERRUPT_ERROR        0x04

#define LOW_PRIORITY       0
#define MIDDLE_PRIORITY    1
#define HIGH_PRIORITY      2
#define VERY_HIGH_PRIORITY 3

typedef struct dma_interrupt
{
    uint8_t interrupt_en : 1;        //0:disable, 1:enable
    uint8_t interrupt_type : 3;      //0: no interrupt 1:block, 2:transfer, 4:error
    uint8_t rsv:4;                      
    DMA_CallbackType func;           //interrupt callback
}dma_interrupte_t;

typedef struct mem_cfg
{
    uint8_t  burst_len : 3;          //burst transaction length 0: 1, 1-7: 2^(len+1)
    uint8_t  addr_change_mode : 2;   //0: increment, 1:decrement, 2:no change
    uint8_t  transer_width : 2;      //0: width 8bits, 1:width 16bits, 2:width 32bits
    uint8_t  reload : 1;             //0: contiguous, 1: auto reload 
    uint32_t addr;
}mem_cfg_t;

typedef struct dma_channel_cfg
{
    mem_cfg_t    src_mem;          //source memory config
    mem_cfg_t    dst_mem;          //destination memory config
    uint8_t      channel : 2;      //dma channel no. 0-3
    uint8_t      priority: 2;      //channel priority, 0:low, 1:mdeium, 2:high, 3:very high 
    uint8_t      interrupt_en : 1; //0: disable, 1: enable
    uint8_t      transfer_dir;     //transfer type direction    
    uint16_t     block_count;      //bolck transfer size:0-1023
    uint32_t     llpx;             //when block chainging, u sing linked lists    
}dma_channel_cfg_t;

typedef struct hal_dma
{
    uint8_t dma_id;                          //dma id 0-2
    dma_interrupte_t  interrupt_config;      //dma interrupt config
    dma_channel_cfg_t channel_config;        //dma channel config
}hal_dma_t;


ERROR_Type hal_dma_init(hal_dma_t* dma_cfg);
void hal_dma_start_recv(uint8_t dma_id, uint8_t channel, uint8_t* buffer, uint32_t len);
void hal_dma_start_send(uint8_t dma_id, uint8_t channel, uint8_t* buffer, uint32_t len);
void hal_dma_channel_start(uint8_t dma_id, uint8_t channel);
void hal_dma_channel_close(uint8_t dma_id, uint8_t channel);
uint8_t hal_dma_channel_done(uint8_t dma_id, uint8_t channel);

#ifdef __cplusplus
}
#endif

#endif
