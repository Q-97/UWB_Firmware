/*****************************************************************************
 *  File: zn_i2c_reg.h
 *
 *  Descirption: contains the functions support i2c.
 *
 *  Copyright (C) : 2023 ultraception.com.
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2023-5-18
 *
 *****************************************************************************/

#ifndef __ZN_I2C_REG_H__
#define __ZN_I2C_REG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_soc.h"

typedef  struct
{  
    __IO uint32_t  ic_con;                  /*I2C Control Register                             */            
    __IO uint32_t  ic_tar;                  /*I2C Target Address Register                      */
    __IO uint32_t  ic_sar;                  /*I2C Slave Address Register                       */
    __IO uint32_t  ic_hs_maddr;             /*I2C High Speed Master Mode Code Address Register */
    __IO uint32_t  ic_cmd_data;             /*I2C Rx/Tx Data Buffer and Command Register       */
    __IO uint32_t  ic_ss_scl_hcnt;          /*Standard Speed I2C Clock SCL High Count Register */
    __IO uint32_t  ic_ss_scl_lcnt;          /*Standard Speed I2C Clock SCL Low Count Register  */
    __IO uint32_t  ic_fs_scl_hcnt;          /*Fast Speed I2C Clock SCL High Count Register     */
    __IO uint32_t  ic_fs_scl_lcnt;          /*Fast Speed I2C Clock SCL Low Count Register      */
    __IO uint32_t  ic_hs_scl_hcnt;          /*High Speed I2C Clock SCL High Count Register     */
    __IO uint32_t  ic_hs_scl_lcnt;          /*High Speed I2C Clock SCL Low Count Register      */
    __IO uint32_t  ic_intr_stat;            /*I2C Interrupt Status Register                    */
    __IO uint32_t  ic_intr_mask;            /*I2C Interrupt Mask Register                      */
    __I  uint32_t  ic_raw_intr_stat;        /*I2C Raw Interrupt Status Register                */
    __IO uint32_t  ic_rx_tl;                /*I2C Receive FIFO Threshold Register              */
    __IO uint32_t  ic_tx_tl;                /*I2C Transmit FIFO Threshold Register             */
    __I  uint32_t  ic_clr_intr;             /*Clear Combined and Individual Interrupt Register */
    __I  uint32_t  ic_clr_rx_under;         /*Clear RX_UNDER Interrupt Register                */
    __I  uint32_t  ic_clr_rx_over;          /*Clear RX_OVER Interrupt Register                 */
    __I  uint32_t  ic_clr_tx_over;          /*Clear TX_OVER Interrupt Register                 */
    __I  uint32_t  ic_clr_rd_req;           /*Clear RD_REQ Interrupt Register                  */
    __I  uint32_t  ic_clr_tx_abrt;          /*Clear TX_ABRT Interrupt Register                 */
    __I  uint32_t  ic_clr_rx_done;          /*Clear RX_DONE Interrupt Register                 */
    __I  uint32_t  ic_clr_activity;         /*Clear ACTIVITY Interrupt Register                */
    __I  uint32_t  ic_clr_stop_det;         /*Clear STOP_DET Interrupt Register                */
    __I  uint32_t  ic_clr_start_det;        /*Clear START_DET Interrupt Register               */
    __I  uint32_t  ic_clr_gen_call;         /*Clear GEN_CALL Interrupt Register                */
    __IO uint32_t  ic_enable;               /*I2C Enable Register                              */
    __I  uint32_t  ic_status;               /*I2C Status Register                              */
    __I  uint32_t  ic_txflr;                /*I2C  Transmit FIFO Level Register                */
    __I  uint32_t  ic_rxflr;                /*I2C  Receive FIFO Level Register                 */
    __IO uint32_t  ic_sda_hold;             /*I2C SDA Hold Time Length Register                */
    __I  uint32_t  ic_tx_abrt_source;       /*I2C Transmit Abort Source Register               */
    __IO uint32_t  ic_slv_data_nack_only;   /*Generate Slave Data NACK Register                */
    __IO uint32_t  ic_dma_cr;               /*DMA Control Register                             */
    __IO uint32_t  ic_dma_tdlr;             /*DMA Transmit Data Level Register                 */
    __IO uint32_t  ic_dma_rdlr;             /*DMA Receive Data Level Register                  */
    __IO uint32_t  ic_sda_setup;            /*I2C  SDA Setup Register                          */
    __IO uint32_t  ic_ack_general_call;     /*I2C  ACK General Call Register                   */
    __I  uint32_t  ic_enable_status;        /*I2C Enable Status Register                       */
    __IO uint32_t  ic_fs_spklen;            /*I2C SS and FS Spike Suppression Limit Register   */
    __IO uint32_t  ic_hs_spklen;            /*I2C HS Spike Suppression Limit Register          */
    __I  uint32_t  ic_clr_restart_det;      /*Clear RESTART_DET Interrupt Register             */   
} ZN_I2cType; 

#define I2C0             ((ZN_I2cType *)  (I2C0_BASE_ADDR))         /* I2C0 address                              */
#define I2C1             ((ZN_I2cType *)  (I2C1_BASE_ADDR))         /* I2C1 address                              */

/* i2c control register definitions */
#define IC_CON_SD                   0x0040
#define IC_CON_RE                   0x0020
#define IC_CON_10BITADDRMASTER      0x0010
#define IC_CON_10BITADDR_SLAVE      0x0008
#define IC_CON_SPD_MSK              0x0006
#define IC_CON_SPD_SS               0x0002
#define IC_CON_SPD_FS               0x0004
#define IC_CON_SPD_HS               0x0006
#define IC_CON_MM                   0x0001

/* i2c data buffer and command register definitions */
#define IC_CMD                      0x0100  
#define IC_STOP                     0x0200
#define IC_RESTART                  0x0400

/* i2c interrupt status register definitions */
#define IC_MST_ON_HOLD              0x2000
#define IC_GEN_CALL                 0x0800
#define IC_START_DET                0x0400
#define IC_STOP_DET                 0x0200
#define IC_ACTIVITY                 0x0100
#define IC_RX_DONE                  0x0080
#define IC_TX_ABRT                  0x0040
#define IC_RD_REQ                   0x0020
#define IC_TX_EMPTY                 0x0010
#define IC_TX_OVER                  0x0008
#define IC_RX_FULL                  0x0004
#define IC_RX_OVER                  0x0002
#define IC_RX_UNDER                 0x0001

/* i2c enable register definitions */
#define IC_ENABLE_ABORT             0x0002
#define IC_ENABLE_0B                0x0001

/* i2c status register  definitions */
#define IC_STATUS_SA            0x0040      /* Slave FSM Activity Status.*/
#define IC_STATUS_MA            0x0020      /*Master FSM Activity Status.*/
#define IC_STATUS_RFF           0x0010      /*Receive FIFO Completely Full.*/
#define IC_STATUS_RFNE          0x0008      /*Receive FIFO Not Empty.*/
#define IC_STATUS_TFE           0x0004      /*Transmit FIFO Completely Empty.*/
#define IC_STATUS_TFNF          0x0002      /*Transmit FIFO Not Full*/
#define IC_STATUS_ACT           0x0001      /*I2C Activity Status.*/

/* IC_DMA_CR Register   */
#define IC_DMA_CR_TDMAE     0x2
#define IC_DMA_CR_RDMAE     0x1

/* IC_TX_ABRT_SOURCE     */
#define IC_ABRT_7B_ADDR_NOACK   0x1

#ifdef __cplusplus
}
#endif

#endif