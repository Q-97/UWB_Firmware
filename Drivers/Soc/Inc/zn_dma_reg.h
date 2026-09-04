
/*****************************************************************************
 *  File: zn_dma_reg.h
 *
 *  Descirption: contains the functions support dma.
 *
 *  Copyright (C) : 2023 ultraception.com.
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2023-5-31
 *
 *****************************************************************************/

#ifndef __ZN_DMA_REG_H__
#define __ZN_DMA_REG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_soc.h"

/*The DMA channels have 4*/
#define DMAC_NUM_CHANNELS  (4)
#define DMA_CHANNEL_0           0
#define DMA_CHANNEL_1           1
#define DMA_CHANNEL_2           2
#define DMA_CHANNEL_3           3

/****************************************************************
DMA  Register address
****************************************************************/

#define AHB_DMA_CONTROL(x)                (DMA_BASE_ADDR + (x * 0x100000))

#define DMAC_CH_START_ADDR(x, ch)       (AHB_DMA_CONTROL(x) + (ch)*0x58)
#define DMAC_COMMON_START_ADDR(x)       (AHB_DMA_CONTROL(x) + 0x2c0)

                                        
#define DMAC_SAR_ADDRESS_OFFSET         (0x000)
#define DMAC_DAR_ADDRESS_OFFSET         (0x008)
#define DMAC_LLP_ADDRESS_OFFSET         (0x010)
#define DMAC_CTL_ADDRESS_OFFSET         (0x018)
#define DMAC_SSTAT_ADDRESS_OFFSET       (0x020)
#define DMAC_DSTAT_ADDRESS_OFFSET       (0x028)
#define DMAC_SSTATAR_ADDRESS_OFFSET     (0x030)
#define DMAC_DSTATAR_ADDRESS_OFFSET     (0x038)
#define DMAC_CFG_ADDRESS_OFFSET         (0x040)
#define DMAC_SGR_ADDRESS_OFFSET         (0x048)
#define DMAC_DSR_ADDRESS_OFFSET         (0x050)
                                               

#define DMAC_SAR(x, n)                  (DMAC_CH_START_ADDR(x, n) + DMAC_SAR_ADDRESS_OFFSET)           /* Source Address for Channel*/
#define DMAC_DAR(x, n)                  (DMAC_CH_START_ADDR(x, n) + DMAC_DAR_ADDRESS_OFFSET)           /* Destination Address Register for Channel*/
#define DMAC_LLP(x, n)                  (DMAC_CH_START_ADDR(x, n) + DMAC_LLP_ADDRESS_OFFSET)           /* Linked List Pointer Register for Channel*/
#define DMAC_CTL(x, n)                  (DMAC_CH_START_ADDR(x, n) + DMAC_CTL_ADDRESS_OFFSET)           /* Control Register for Channel */
#define DMAC_CTLH(x, n)                 (DMAC_CTL(x, n) + 4)
#define DMAC_SSTAT(x, n)                (DMAC_CH_START_ADDR(x, n) + DMAC_SSTAT_ADDRESS_OFFSET)         /* Source Status Register for Channel*/
#define DMAC_DSTAT(x, n)                (DMAC_CH_START_ADDR(x, n) + DMAC_DSTAT_ADDRESS_OFFSET)         /* Destination Status Register for Channel*/
#define DMAC_SSTATAR(x, n)              (DMAC_CH_START_ADDR(x, n) + DMAC_SSTATAR_ADDRESS_OFFSET)       /* Source Status Address Register for Channel*/
#define DMAC_DSTATAR(x, n)              (DMAC_CH_START_ADDR(x, n) + DMAC_DSTATAR_ADDRESS_OFFSET)       /* Destination Status Address Register for Channel*/
#define DMAC_CFG(x, n)                  (DMAC_CH_START_ADDR(x, n) + DMAC_CFG_ADDRESS_OFFSET)           /* Configuration Register for Channel x*/
#define DMAC_CFGH(x, n)                 (DMAC_CFG(x, n) + 4)
#define DMAC_SGR(x, n)                  (DMAC_CH_START_ADDR(x, n) + DMAC_SGR_ADDRESS_OFFSET)           /* Source Gather Register for Channel x, not ues*/
#define DMAC_DSR(x, n)                  (DMAC_CH_START_ADDR(x, n) + DMAC_DSR_ADDRESS_OFFSET)           /* Destination Scatter Register for Channel, not use*/

#define DMAC_RAWTFR(x)                    (DMAC_COMMON_START_ADDR(x) + 0x000) /*Raw Status for IntTfr Interrupt*/
#define DMAC_RAWBLOCK(x)                  (DMAC_COMMON_START_ADDR(x) + 0x008) /*Raw Status for IntBlock Interrupt*/
#define DMAC_RAWSRCTRAN(x)                (DMAC_COMMON_START_ADDR(x) + 0x010) /*Raw Status for IntSrcTran Interrupt*/
#define DMAC_RAWDSTTRAN(x)                (DMAC_COMMON_START_ADDR(x) + 0x018) /*Raw Status for IntDstTran Interrupt*/
#define DMAC_RAWERR(x)                    (DMAC_COMMON_START_ADDR(x) + 0x020) /*Raw Status for IntErr Interrupt*/
#define DMAC_STATUSTFR(x)                 (DMAC_COMMON_START_ADDR(x) + 0x028) /*Status for IntTfr Interrupt*/
#define DMAC_STATUSBLOCK(x)               (DMAC_COMMON_START_ADDR(x) + 0x030) /*Status for IntBlock Interrupt*/
#define DMAC_STATUSSRCTRAN(x)             (DMAC_COMMON_START_ADDR(x) + 0x038) /*Status for IntSrcTran Interrupt*/
#define DMAC_STATUSDSTTRAN(x)             (DMAC_COMMON_START_ADDR(x) + 0x040) /*Status for IntDstTran Interrupt*/
#define DMAC_STATUSERR(x)                 (DMAC_COMMON_START_ADDR(x) + 0x048) /* Status for IntErr Interrupt*/
#define DMAC_MASKTFR(x)                   (DMAC_COMMON_START_ADDR(x) + 0x050) /*Status for IntTfr Interrupt*/
#define DMAC_MASKBLOCK(x)                 (DMAC_COMMON_START_ADDR(x) + 0x058) /*Mask for IntBlock Interrupt*/
#define DMAC_MASKSRCTRAN(x)               (DMAC_COMMON_START_ADDR(x) + 0x060) /*Status for IntSrcTran Interrupt*/
#define DMAC_MASKDSTTRAN(x)               (DMAC_COMMON_START_ADDR(x) + 0x068) /*Mask for IntDstTran Interrupt*/
#define DMAC_MASKERR(x)                   (DMAC_COMMON_START_ADDR(x) + 0x070) /*Mask for IntErr Interrupt*/
#define DMAC_CLEARTFR(x)                  (DMAC_COMMON_START_ADDR(x) + 0x078) /*Clear for IntTfr Interrupt*/
#define DMAC_CLEARBLOCK(x)                (DMAC_COMMON_START_ADDR(x) + 0x080) /*Clear for IntBlock Interrupt*/
#define DMAC_CLEARSRCTRAN(x)              (DMAC_COMMON_START_ADDR(x) + 0x088) /*Clear for IntSrcTran Interrupt*/
#define DMAC_CLEARDSTTRAN(x)              (DMAC_COMMON_START_ADDR(x) + 0x090) /*Clear for IntDstTran Interrupt*/
#define DMAC_CLEARERR(x)                  (DMAC_COMMON_START_ADDR(x) + 0x098) /*Clear for IntErr Interrupt*/
#define DMAC_STATUSINT(x)                 (DMAC_COMMON_START_ADDR(x) + 0x0a0) /*Status for each Interrupt type*/
#define DMAC_REQSRCREG(x)                 (DMAC_COMMON_START_ADDR(x) + 0x0a8) /*Source Software Transaction Request register*/
#define DMAC_REQDSTREG(x)                 (DMAC_COMMON_START_ADDR(x) + 0x0b0) /*Destination Software Transaction Request register*/
#define DMAC_SGLRQSRCREG(x)               (DMAC_COMMON_START_ADDR(x) + 0x0b8) /*Source Single Transaction Request register*/
#define DMAC_SGLRQDSTREG(x)               (DMAC_COMMON_START_ADDR(x) + 0x0c0) /*Destination Single Transaction Request register*/
#define DMAC_LSTSRCREG(x)                 (DMAC_COMMON_START_ADDR(x) + 0x0c8) /*Source Last Transaction Request register*/
#define DMAC_LSTDSTREG(x)                 (DMAC_COMMON_START_ADDR(x) + 0x0d0) /*Destination Last Transaction Request register*/
#define DMAC_DMACFGREG(x)                 (DMAC_COMMON_START_ADDR(x) + 0x0d8) /*DMA Configuration Register*/
#define DMAC_CHENREG(x)                   (DMAC_COMMON_START_ADDR(x) + 0x0e0) /*DMA Channel Enable Register*/
#define DMAC_DMAIDREG(x)                  (DMAC_COMMON_START_ADDR(x) + 0x0e8) /*DMA ID register*/
#define DMAC_DMATESTREG(x)                (DMAC_COMMON_START_ADDR(x) + 0x0f0)
#define DMAC_DMA_COMP_PARAM_6(x)          (DMAC_COMMON_START_ADDR(x) + 0x108)
#define DMAC_DMA_COMP_PARAM_5(x)          (DMAC_COMMON_START_ADDR(x) + 0x110)
#define DMAC_DMA_COMP_PARAM_4(x)          (DMAC_COMMON_START_ADDR(x) + 0x118)
#define DMAC_DMA_COMP_PARAM_3(x)          (DMAC_COMMON_START_ADDR(x) + 0x120)
#define DMAC_DMA_COMP_PARAM_2(x)          (DMAC_COMMON_START_ADDR(x) + 0x128)
#define DMAC_DMA_COMP_PARAM_1(x)          (DMAC_COMMON_START_ADDR(x) + 0x130)
#define DMAC_DMA_COMP_ID(x)               (DMAC_COMMON_START_ADDR(x) + 0x138)


/********************************************************************
Control register.
********************************************************************/
/*CTLHx*/
#define DMAC_CTL_DONE           (1<<12)
#define DMAC_CTL_BLOCK_TS(n)    (n<<0)
/*CTLLx*/
#define DMAC_CTL_LLP_SRC_EN     (1L<<28)
#define DMAC_CTL_LLP_DST_EN     (1L<<27)
#define DMAC_CTL_SMS_M1         (0L<<25)
#define DMAC_CTL_SMS_M2         (1L<<25)
#define DMAC_CTL_SMS_M3         (2L<<25)
#define DMAC_CTL_SMS_M4         (3L<<25)
#define DMAC_CTL_DMS_M1         (0L<<23)
#define DMAC_CTL_DMS_M2         (1L<<23)
#define DMAC_CTL_DMS_M3         (2L<<23)
#define DMAC_CTL_DMS_M4         (3L<<23)
#define DMAC_CTL_M2M_DW         (0L<<20)
#define DMAC_CTL_M2P_DW         (1L<<20)
#define DMAC_CTL_P2M_DW         (2L<<20)
#define DMAC_CTL_P2P_DW         (3L<<20)
#define DMAC_CTL_P2M_PER        (4L<<20)
#define DMAC_CTL_P2P_SRCP       (5L<<20)
#define DMAC_CTL_M2P_PER        (6L<<20)
#define DMAC_CTL_P2P_DESP       (7L<<20)
#define DMAC_CTL_DST_SCATTER_EN (1L<<18)
#define DMAC_CTL_SRC_GATHER_EN  (1L<<17)
#define DMAC_CTL_SRC_MSIZE1     (0L<<14)
#define DMAC_CTL_SRC_MSIZE4     (1L<<14)
#define DMAC_CTL_SRC_MSIZE8     (2L<<14)
#define DMAC_CTL_SRC_MSIZE16    (3L<<14)
#define DMAC_CTL_SRC_MSIZE32    (4L<<14)
#define DMAC_CTL_SRC_MSIZE64    (5L<<14)
#define DMAC_CTL_SRC_MSIZE128   (6L<<14)
#define DMAC_CTL_SRC_MSIZE256   (7L<<14)
#define DMAC_CTL_DEST_MSIZE1    (0L<<11)
#define DMAC_CTL_DEST_MSIZE4    (1L<<11)
#define DMAC_CTL_DEST_MSIZE8    (2L<<11)
#define DMAC_CTL_DEST_MSIZE16   (3L<<11)
#define DMAC_CTL_DEST_MSIZE32   (4L<<11)
#define DMAC_CTL_DEST_MSIZE64   (5L<<11)
#define DMAC_CTL_DEST_MSIZE128  (6L<<11)
#define DMAC_CTL_DEST_MSIZE256  (7L<<11)
#define DMAC_CTL_SINC_INC       (0L<<9)
#define DMAC_CTL_SINC_DEC       (1L<<9)
#define DMAC_CTL_SINC_NO        (2L<<9)
#define DMAC_CTL_DINC_INC       (0L<<7)
#define DMAC_CTL_DINC_DEC       (1L<<7)
#define DMAC_CTL_DINC_NO        (2L<<7)
#define DMAC_CTL_SRC_TR_WIDTH8  (0L<<4)
#define DMAC_CTL_SRC_TR_WIDTH16 (1L<<4)
#define DMAC_CTL_SRC_TR_WIDTH32 (2L<<4)
#define DMAC_CTL_SRC_TR_WIDTH64 (3L<<4)
#define DMAC_CTL_DST_TR_WIDTH8  (0L<<1)
#define DMAC_CTL_DST_TR_WIDTH16 (1L<<1)
#define DMAC_CTL_DST_TR_WIDTH32 (2L<<1)
#define DMAC_CTL_DST_TR_WIDTH64 (3L<<1)
#define DMAC_CTL_INT_EN         (1<<0)
#define DMAC_CTL_INT_DIS        (0<<0)

#define DMAC_CTL_LLP_SREC_EN_POS    (28) /*Block chaining is enabled on the source side only if the LLP_SRC_EN field is high and LLPx.LOC is non-zero.*/
#define DMAC_CTL_LLP_DST_EN_POS     (27) /*Block chaining is enabled on the destination side only if LLP_DST_EN field is high and LLPx.LOC is non-zero.*/
#define DMAC_CTL_SMS_POS            (25) /*Source Master Select. How use*/
#define DMAC_CTL_DMS_POS            (23) /*Destination Master Select.How use*/
#define DMAC_CTL_TT_FC_POS          (20) /*Transfer Type and Flow Control.Flow control can be assigned to the DW_ahb_dmac, the source peripheral, or the destination peripheral.*/
#define DMAC_CTL_DST_SCATTER_EN_POS (18) /*Destination scatter enable.not support*/
#define DMAC_CTL_SRC_GATHER_EN_POS  (17) /*Source gather enable.not support*/
#define DMAC_CTL_SRC_MSIZE_POS      (14) /*Source Burst Transaction Length*/
#define DMAC_CTL_DEST_MSIZE_POS     (11) /*Destination Burst Transaction Length.*/  
#define DMAC_CTL_SINC_POS            (9) /*Source Address Increment*/
#define DMAC_CTL_DINC_POS            (7) /*Destination Address Increment.*/
#define DMAC_CTL_SRC_TR_WIDTH_POS    (4) /*Source Transfer Width.*/
#define DMAC_CTL_DST_TR_WIDTH_POS    (1) /*Destination Transfer Width.*/
#define DMAC_CTL_INT_EN_POS          (0) /*Interrupt Enable Bit.*/

/********************************************************************
Configuration register
********************************************************************/
/*CFGHx:*/
#define DMAC_CFG_DEST_PER(n)      (n<<11)    //Hardware handshake interface
#define DMAC_CFG_SRC_PER(n)       (n<<7)    //Hardware handshake interface
#define DMAC_CFG_SS_UPD_EN        (1<<6)    //Status update enable
#define DMAC_CFG_DS_UPD_EN        (1<<5)    //Status update enable
#define DMAC_CFG_PROTCTL(n)       (n<<2)  
/* Data available is greater than or equal to half the FIFO depth for destination transfers 
and space available is greater than half the fifo depth for source transfers.*/
#define DMAC_CFG_FIFO_MODE_1      (1<<1) 
/* Space/data available for single AHB transfer of the specified transfer width*/
#define DMAC_CFG_FIFO_MODE_0      (0<<1)    
#define DMAC_CFG_FCMODE_1         (1<<0)    //Enable prefetch
#define DMAC_CFG_FCMODE_0         (0<<0)    //Enable prefetch
/*CFGLx:*/
#define DMAC_CFG_RELOAD_DST(x)    (x<<31)   /*x should be 0 or 1*/
#define DMAC_CFG_RELOAD_SRC(x)    (x<<30)   /*x should be 0 or 1*/
#define DMAC_CFG_SRC_HS_POL_H     (0L<<19)    //Handshake polarity
#define DMAC_CFG_SRC_HS_POL_L     (1L<<19)    //Handshake polarity
#define DMAC_CFG_DST_HS_POL_H     (0L<<18)    //Handshake polarity
#define DMAC_CFG_DST_HS_POL_L     (1L<<18)    //Handshake polarity
#define DMAC_CFG_LOCK_B           (1L<<17)
#define DMAC_CFG_LOCK_CH          (1L<<16)
#define DMAC_CFG_LOCK_B_TSF       (0L<<14)    //Lock level
#define DMAC_CFG_LOCK_B_BLK       (1L<<14)    //Lock level
#define DMAC_CFG_LOCK_B_TSC       (2L<<14)    //Lock level
#define DMAC_CFG_LOCK_CH_TSF      (0L<<12)    //Lock level
#define DMAC_CFG_LOCK_CH_BLK      (1L<<12)    //Lock level
#define DMAC_CFG_LOCK_CH_TSC      (2L<<12)    //Lock level
#define DMAC_CFG_HS_SRC_HARDWARE  (0L<<11)    //Handshake mode
#define DMAC_CFG_HS_SRC_SOFTWARE  (1L<<11)    //Handshake mode
#define DMAC_CFG_HS_DST_HARDWARE  (0L<<10)    //Handshake mode
#define DMAC_CFG_HS_DST_SOFTWARE  (1L<<10)    //Handshake mode
#define DMAC_CFG_FIFO_EMPTY       (1<<9)
#define DMAC_CFG_CH_SUSP          (1<<8)
#define DMAC_CFG_CH_PRIOR(n)      (n<<5)    //n should be 0 to 7

/********************************************************************
Interrupt register
********************************************************************/
/*interrupt RAW status registers(0x2c0 to 0x2e0) and interrupt status registers(0x2e8 to 0x308)*/
#define DMAC_INT_STATUS(n)      (1L<<n)
/*interrupt mask register(0x310 to 0x330)  */
#define DMAC_INT_MASK(n)      (((0L<<n) | (1L<<(n+8))))
#define DMAC_INT_UNMASK(n)      (((1L<<n) | (1L<<(n+8))))
/*interrupt clear register(0x338 to 0x358)*/
#define DMAC_INT_CLR(n)       (1L<<n)
/*combined interrupt status register(0x360)*/
#define DMAC_INT_ERR        (1L<<4)
#define DMAC_INT_DSTT       (1L<<3)
#define DMAC_INT_SRCT       (1L<<2)
#define DMAC_INT_BLOCK      (1L<<1)
#define DMAC_INT_TFR        (1L<<0)
#define DMAC_ALL_MASK       ((1L<<DMAC_NUM_CHANNELS)-1)

/********************************************************************
Software handshake register
********************************************************************/
#define DMAC_SW_REQ(n)        (((1<<n) | (1<<(n+8))))
#define DMAC_SW_REQ_DIS(n)    (1<<(n+8))

/********************************************************************
DMA channel enable register
********************************************************************/
#define DMAC_CH_EN(n)       ((1<<n) | (1<<(n+8)))
#define DMAC_CH_DIS(n)        (1<<(n+8))

/********************************************************************
DMA configuration register
********************************************************************/
#define DMAC_EN           (1<<0)

/*DMA0 peripheral_ID: 2 spi,1 i2c,1 uart */
#define PERIPH_SPI_TX(id)       (0 + 2 * id)
#define PERIPH_SPI_RX(id)       (1 + 2 * id)

#define PERIPH_I2C_TX(id)       (6 + 2 * id)
#define PERIPH_I2C_RX(id)       (7 + 2 * id)

#define PERIPH_UART_TX(id)      (8 + 2 * id)
#define PERIPH_UART_RX(id)      (9 + 2 * id)


/*******************************************************************
Miscellaneous DMA register
********************************************************************/
#define DMAC_NORMAL_MODE      (0<<0)

#ifdef __cplusplus
}
#endif

#endif

