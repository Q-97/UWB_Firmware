/*****************************************************************************
 *  File: zn_dma.h
 *
 *  Descirption: contains the functions support dma.
 *
 *  Copyright (C) : 2023 ultraception.com
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2023-5-31
 *
 *****************************************************************************/

#ifndef __ZN_DMA_H__
#define __ZN_DMA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_dma_reg.h"

#define DMA_MAX_BLK_SIZE   (1023)

typedef void (*DMA_CallbackType)(uint32_t arg[3]);  

/*!
* @brief DMA priority enumeration.A priority of 3( DMAH_NUM_CHANNELS-1) is the highest priority, and 0 is the lowest.
*/
typedef enum
{
    DMA_CH_PRIOR_0 = 0,        /*Channel priority is 0 */
    DMA_CH_PRIOR_1,            /*Channel priority is 1 */
    DMA_CH_PRIOR_2,            /*Channel priority is 2 */
    DMA_CH_PRIOR_3,            /*Channel priority is 3 */
}DMA_PriorityType;


/*!
* @brief DMA address Increments enumeration.
*/
typedef enum
{
    DMA_ADDRESS_INC = 0,         /*0: Increments address*/
    DMA_ADDRESS_DEC,             /* 1: Decrements address*/
    DMA_ADDRESS_NO_CHANGE,       /* 2: No change in address */

}DMA_AddressIncType;


/*!
* @brief DMA  Burst Transaction Length enumeration.Number of data items,each of width CTLx.SRC_TR_WIDTH.
*/
typedef enum
{
    DMA_MSIZE_0 = 0,         /*0:  Number of data items to be transferred is 1*/
    DMA_MSIZE_1,             /*1:  Number of data items to be transferred is 4*/
    DMA_MSIZE_2,             /*1:  Number of data items to be transferred is 8*/
    DMA_MSIZE_3,             /*1:  Number of data items to be transferred is 16*/
    DMA_MSIZE_4,             /*1:  Number of data items to be transferred is 32*/
    DMA_MSIZE_5,             /*1:  Number of data items to be transferred is 64*/
    DMA_MSIZE_6,             /*1:  Number of data items to be transferred is 128*/
    DMA_MSIZE_7,             /*1:  Number of data items to be transferred is 256*/
}DMA_BusrtTransferSize;


/*!
* @brief DMA  Transfer Width.Mapped to AHB bus hsize.For a non-memory peripheral, typically the peripheral FIFO width.
*/
typedef enum
{
    DMA_TR_WIDTH_0 = 0,         /*0:transfer width is 8 bits*/
    DMA_TR_WIDTH_1,             /*0:transfer width is 16 bits*/
    DMA_TR_WIDTH_2,             /*0:transfer width is 32 bits*/
}DMA_TransferWidth;



typedef enum
{
	DMA_MEM_TO_SPI0_TX = 0,       /* 0: Memory to SPI0_TX Peripheral, also for  peripheral_ID value*/
    DMA_SPI0_RX_TO_MEM = 1,       /* 1: SPI0_RX Peripheral to Memory,also for  peripheral_ID value */
    DMA_MEM_TO_SPI1_TX = 2,       /* 2: Memory to SPI1_TX Peripheral,also for  peripheral_ID value */
    DMA_SPI1_RX_TO_MEM = 3,       /* 3: SPI1_RX Peripheral to Memory,also for  peripheral_ID value */
	DMA_MEM_TO_UART1_TX = 4,       /* 8: Memory to UART_TX Peripheral,also for  peripheral_ID value */
    DMA_UART1_RX_TO_MEM = 5,       /* 9: UART_RX Peripheral to Memory,also for  peripheral_ID value */
    DMA_MEM_TO_I2C0_TX  = 6,       /* 6: Memory to I2C_TX Peripheral,also for  peripheral_ID value */
    DMA_I2C0_RX_TO_MEM  = 7,       /* 7: I2C_RX Peripheral to Memory,also for  peripheral_ID value */
	DMA_MEM_TO_UART0_TX = 8,       /* 8: Memory to UART_TX Peripheral,also for  peripheral_ID value */
    DMA_UART0_RX_TO_MEM = 9,       /* 9: UART_RX Peripheral to Memory,also for  peripheral_ID value */
	DMA_MEM_TO_I2C1_TX  = 10,       /* 10: Memory to I2C1_TX Peripheral,also for  peripheral_ID value */
    DMA_I2C1_RX_TO_MEM  = 11,       /* 11: I2C1_RX Peripheral to Memory,also for  peripheral_ID value */
    DMA_MEM_TO_MEM,               /* 0: Memory to Memory */  

}DMA_TransferDir;
/********************************************************************
Interrupt type 
********************************************************************/
typedef enum 
{
    DMAC_INTERRUPT_NO = 0,
    DMAC_INTERRUPT_BLOCK = 1,
    DMAC_INTERRUPT_TFR = 2,
    DMAC_INTERRUPT_ERROR = 4,
} DMA_IntType;

typedef struct
{                                      
    ACTION_Type           interruptEn;               /*interrupt:  0:disable 1:enable */
    DMA_IntType           interruptType;             /*interrupt tye*/
    IRQn_Type             irq;                       /*interrupt num*/
    DMA_CallbackType      callBack;                  /*IRQ Callback pointer */
    //uint32_t            llpx;                      /*When block chaining, using Linked Lists.*/
}DMA_ConfigType;


typedef struct
{                                      
    uint32_t              srcAddr;                   /*source address */
    uint32_t              destAddr;                  /*destination address */
    DMA_BusrtTransferSize srcMsize;                  /*Source Burst Transaction Length*/
    DMA_BusrtTransferSize destMsize;                 /*Destination Burst Transaction Length*/
    DMA_AddressIncType    srcAddrInc;                /*source address  Increment*/
    DMA_AddressIncType    destAddrInc;               /*destination  Increment*/
    DMA_TransferWidth     srcTrWidth;                /*Source Transfer Width*/
    DMA_TransferWidth     destTrWidth;               /*Destination Transfer Width*/
    uint8_t               srcReload;                 /* 0 - Contiguous,1- Auto reload; */
    uint8_t               destReload;                /* 0 - Contiguous,1- Auto reload;  when srcReload=0,destReload=0, SARx Update Method None(single),DARx Update Method None(single)*/
    DMA_TransferDir       transferDir;               /*Transfer Type Direction*/
    uint16_t              blockCnt;                  /*Block Transfer Siz: 0~1023*/
    uint8_t               channel;                   /*dma channel:0-3*/
    DMA_PriorityType      priority;                  /*0:low; 1:medium; 2:high; 3: very high */
    ACTION_Type           interruptEn;               /*interrupt:  0:disable 1:enable */
    uint32_t              llpx;                      /*When block chaining, using Linked Lists.*/
}DMA_ChConfigType;

/********************************************************************
Channel-related information
********************************************************************/
typedef struct 
{
    uint32_t sarx;                    /*Source address register                                     */
    uint32_t darx;                    /*Destination address register                                */
    uint32_t ctlHx;                    /*Control register high 32-bit                                */
    uint32_t ctlLx;                    /*Control register low 32-bit                                 */
    uint32_t cfgHx;                    /*Configuration register high 32-bit                          */
    uint32_t cfgLx;                    /*Configuration register low 32-bit                           */
    uint32_t sgrx;                    /*Source gather register, this function is not supported      */
    uint32_t dsrx;                    /*Destination scatter register,this function is not supported */
    uint32_t llpx;                                                                                
} DMA_ChanInfo;


typedef struct LLI
{
    volatile uint32_t SAR;
    volatile uint32_t DAR;
    struct LLI  volatile *LLP;
    volatile uint32_t CTL_L;
    volatile uint32_t CTL_H;
    volatile uint32_t Rev[2];
}DMA_LLI;



int dma_interrupt_en(uint32_t id, DMA_IntType type);
int dma_chan_config(uint32_t id, DMA_ChanInfo *channel, uint8_t channel_number, uint16_t BlockSize);
void dma_chan_start(uint32_t id, uint8_t channel_number);
void dma_chan_close(uint32_t id, uint8_t channel_number);
void dma_chan_set_fifo_mode(uint32_t id, uint8_t channel_number);
BOOL_Type dma_chan_check_done_poll(uint32_t id, uint8_t channel_number);
int dma_init(uint32_t id, DMA_ConfigType *config);
int dma_chan_init(uint32_t id, DMA_ChConfigType *chConfig);

#ifdef __cplusplus
}
#endif

#endif
