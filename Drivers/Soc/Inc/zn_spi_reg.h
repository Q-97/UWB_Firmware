/*****************************************************************************
 *  File: zn_spi_reg.h
 *
 *  Descirption: this file contains the functions support spi operations.
 *
 *  Copyright (C) : 2022 ultraception.com
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2023-5-6
 *
 *****************************************************************************/
#ifndef __ZN_SPI_REG_H__
#define __ZN_SPI_REG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_soc.h"


/*
 * define number of the spi
 */
#define SPI_NUM   (2)

/*
SPI FIFO depth max  is 32, FIFO tirgger is 16 (Half FIFO_DEPTH_MAX)
*/
typedef struct
{                                   
    __IO uint32_t  TxDataReg;        /*Transmit Data Register*/
    __I  uint32_t  RxDataReg;       /*Receive Data Register*/
    __I  uint32_t  CurStatusReg;    /*Current Status Register*/
    __I  uint32_t  IntStatusReg;    /*Interrupt Status Register*/
    __IO uint32_t  IntEnableReg;    /*Interrupt Enable Register*/
    __O  uint32_t  IntClrReg;       /*Interrupt Clear Register*/
    __IO uint32_t  GlobalConReg;    /*Global Control Register*/
    __IO uint32_t  CommonConReg;    /*Common Control Register*/
    __IO uint32_t  BaudRateReg;     /*Baud Rate Generator*/
    __IO uint32_t  RxDataNumReg;    /*Receive data number register.bits 15:0*/
    __IO uint32_t  SlaveCsReg;      /*Slave Chip Select register*/
    
} ZN_SpiType;


#define SPI0 (ZN_SpiType *)SPI0_BASE_ADDR
#define SPI1 (ZN_SpiType *)SPI1_BASE_ADDR

/*Current Status Register */        
#define RXAVL_4BYTE_POS                (3) 
#define RXAVL_4BYTE_MSK                (1<<RXAVL_4BYTE_POS)
#define TX_FULL_POS                    (2)
#define TX_FULL_MSK                    (1<<TX_FULL_POS)
#define RXAVL_POS                      (1)
#define RXAVL_MSK                      (1<<RXAVL_POS)
#define TX_EMPTY_POS                   (0)     
#define TX_EMPTY_MSK                   (1<<TX_EMPTY_POS)
        
/*Interrupt Status Register*/
#define TX_EMPTY_INTF_POS               (6)
#define TX_EMPTY_INTF_MSK               (1<<TX_EMPTY_INTF_POS)
#define RX_FULL_INTF_POS                (5)
#define RX_FULL_INTF_MSK                (1<<RX_FULL_INTF_POS)
#define RX_MATCH_INTF_POS               (4) /*SPI master mode use*/
#define RX_MATCH_INTF_MSK               (1<<RX_MATCH_INTF_POS)
#define RX_OVERRUN_INTF_POS             (3)
#define RX_OVERRUN_INTF_MSK             (1<<RX_OVERRUN_INTF_POS)
#define TX_UNDERRUN_INTF_POS            (2) /*SPI slave transmitter use*/
#define TX_UNDERRUN_INTF_MSK            (1<<TX_UNDERRUN_INTF_POS)
#define RX_AVL_INTF_POS                 (1)
#define RX_AVL_INTF_MSK                 (1<<RX_AVL_INTF_POS)
#define TX_AVL_INTF_POS                 (0)
#define TX_AVL_INTF_MSK                 (1<<TX_AVL_INTF_POS)

/*Interrupt Enable Register */
#define TX_EMPTY_INTEN_POS              (6)
#define TX_EMPTY_INTEN_MSK              (1<<TX_EMPTY_INTEN_POS)
#define RX_FULL_INTEN_POS               (5)
#define RX_FULL_INTEN_MSK               (1<<RX_FULL_INTEN_POS)
#define RX_MATCH_INTEN_POS              (4)
#define RX_MATCH_INTEN_MSK              (1<<RX_MATCH_INTEN_POS)
#define RX_OVERRUN_INTEN_POS            (3)
#define RX_OVERRUN_INTEN_MSK            (1<<RX_OVERRUN_INTEN_POS)
#define TX_UNDERRUN_INTEN_POS           (2)
#define TX_UNDERRUN_INTEN_MSK           (1<<TX_UNDERRUN_INTEN_POS)
#define RX_INTEN_POS                    (1)
#define RX_INTEN_MSK                    (1<<RX_INTEN_POS)
#define TX_INTEN_POS                    (0)
#define TX_INTEN_MSK                    (1<<TX_INTEN_POS)

/*Interrupt Clear Register*/
#define TX_EMPTY_INTCLR_POS             (6)
#define TX_EMPTY_INTCLR_MSK             (1<<TX_EMPTY_INTCLR_POS)
#define RXFIFO_FULL_INTCLR_POS          (5)
#define RXFIFO_FULL_INTCLR_MSK          (1<<RXFIFO_FULL_INTCLR_POS)
#define RX_MATCH_INTCLR_POS             (4)
#define RX_MATCH_INTCLR_MSK             (1<<RX_MATCH_INTCLR_POS)
#define RX_OVERRUN_INTCLR_POS           (3)
#define RX_OVERRUN_INTCLR_MSK           (1<<RX_OVER_ERR_INTCLR_POS)
#define TX_UNDERRUN_INTCLR_POS          (2)
#define TX_UNDERRUN_INTCLR_MSK          (1<<TX_SLAVE_UNDERRUN_INTCLR_POS)
#define RX_INTCLR_POS                   (1)
#define RX_INTCLR_MSK                   (1<<RX_AVL_INTCLR_POS)
#define TX_INTCLR_POS                   (0)
#define TX_INTCLR_MSK                   (1<<TX_AVL_INTCLR_POS)
                                     

/*Global Control Register*/
#define DMA_MODE_POS                    (9)
#define DMA_MODE_MSK                    (1<<DMA_MODE_POS)
#define TXFIFO_TRIGGER_LEVEL_POS        (7)
#define TXFIFO_TRIGGER_LEVEL_MSK        (1<<TXFIFO_TRIGGER_LEVEL_POS)
#define RXFIFO_TRIGGER_LEVEL_POS        (5)
#define RXFIFO_TRIGGER_LEVEL_MSK        (1<<RXFIFO_TRIGGER_LEVEL_POS)
#define RX_ENABLE_POS                   (4)
#define RX_ENABLE_MSK                   (1<<RX_ENABLE_POS)
#define TX_ENABLE_POS                   (3)
#define TX_ENABLE_MSK                   (1<<TX_ENABLE_POS)
#define MASTER_MODE_POS                 (2)
#define MASTER_MODE_MSK                 (1<<MASTER_MODE_POS)
#define INT_ENABLE_POS                  (1)
#define INT_ENABLE_MSK                  (1<<INT_ENABLE_POS)
#define SPI_ENABLE_POS                  (0)
#define SPI_ENABLE_MSK                  (1<<SPI_ENABLE_POS)

/*Common Control Register*/
#define SPI_LEN_BITS_POS             (8)
#define SPI_LEN_BITS_MSK(x)          ((x-1)<<SPI_LEN_BITS_POS)  /*4<=x<=32*/ 
#define TX_EDGE_POS                  (5)                      /*Slave mode TX.1:SPBRG==4,fast speed use,0: SPBRG>4,low speed use*/
#define TX_EDGE_MSK                  (1<<TX_EDGE_POS)
#define RX_EDGE_POS                  (4)                      /*Master mode RX.1:fast speed use,0:,low speed use*/
#define RX_EDGE_MSK                  (1<<RX_EDGE_POS)
#define LSB_ENBALE_POS               (2)                    
#define LSB_ENBALE_MSK               (1<<LSB_ENBALE_POS)
#define CKPL_POS                     (1)    /*SPI Clock Polarity Select bit*/                  
#define CKPL_MSK                     (1<<CKPL_POS)
#define CKPH_POS                     (0)    /*Clock Phase Select bit*/                 
#define CKPH_MSK                     (1<<CKPH_POS)

/**
* spi_cs_low
*
* @param[in]  SPIx: Pointer to ZN_SpiType structure
* @param[in]  cs_id: Chip Select ID
* @return none
*
* @brief Set the specified SPI chip select to low
*/
__STATIC_INLINE void spi_cs_low(ZN_SpiType *SPIx,uint8_t cs_id)
{
    SPIx->SlaveCsReg &= ~(1<<cs_id);
}

 /**
* spi_cs_high
*
* @param[in]  SPIx: Pointer to ZN_SpiType structure
* @param[in]  cs_id: Chip Select ID
* @return none
*
* @brief Set the specified SPI chip select to high
*/
__STATIC_INLINE void spi_cs_high(ZN_SpiType *SPIx,uint8_t cs_id)
{
    SPIx->SlaveCsReg |= (1<<cs_id);
}

 /**
* spi_rx_enable
*
* @param[in]  SPIx: Pointer to ZN_SpiType structure
* @return none
*
* @brief Enable SPI receive
*/
__STATIC_INLINE void spi_rx_enable(ZN_SpiType *SPIx)
{
    SPIx->GlobalConReg |= RX_ENABLE_MSK;
}

 /**
* spi_rx_disable
*
* @param[in]  SPIx: Pointer to ZN_SpiType structure
* @return none
*
* @brief Disable SPI receive
*/
__STATIC_INLINE void spi_rx_disable(ZN_SpiType *SPIx)
{
    SPIx->GlobalConReg &= ~RX_ENABLE_MSK;
}

 /**
* spi_clear_tx_buf
*
* @param[in]  SPIx: Pointer to ZN_SpiType structure
* @return none
*
* @brief Enable SPI transmit
*/
__STATIC_INLINE void spi_clear_tx_buf(ZN_SpiType *SPIx)
{
    uint32_t temp = SPIx->GlobalConReg;
    SPIx->GlobalConReg &= ~TX_ENABLE_MSK;
    SPIx->GlobalConReg &= ~SPI_ENABLE_MSK;
    SPIx->GlobalConReg = temp;
}
 /**
* spi_tx_enable
*
* @param[in]  SPIx: Pointer to ZN_SpiType structure
* @return none
*
* @brief Enable SPI transmit
*/
__STATIC_INLINE void spi_tx_enable(ZN_SpiType *SPIx)
{
    SPIx->GlobalConReg |= TX_ENABLE_MSK;
}

 /**
* spi_tx_disable
*
* @param[in]  SPIx: Pointer to ZN_SpiType structure
* @return none
*
* @brief Disable SPI transmit
*/
__STATIC_INLINE void spi_tx_disable(ZN_SpiType *SPIx)
{
    SPIx->GlobalConReg &= ~TX_ENABLE_MSK;
}
/**
* spi_txrx_enable
*
* @param[in]  SPIx: SPI module pointer
* @return none
*
* @brief Enable both the SPI Transmit and Receive
*/
__STATIC_INLINE void spi_txrx_enable(ZN_SpiType *SPIx)
{
    SPIx->GlobalConReg |= (TX_ENABLE_MSK|RX_ENABLE_MSK);
}

/**
* spi_txrx_disable
*
* @param[in]  SPIx: SPI module pointer
* @return none
*
* @brief Disable both the SPI Transmit and Receive
*/
__STATIC_INLINE void spi_txrx_disable(ZN_SpiType *SPIx)
{
    SPIx->GlobalConReg &= ~(TX_ENABLE_MSK|RX_ENABLE_MSK);
}



/**
* spi_dma_enable
*
* @param[in]  SPIx: Pointer to ZN_SpiType structure
* @return none
*
* @brief Enable SPI DMA mode
*/
__STATIC_INLINE void spi_dma_enable(ZN_SpiType *SPIx)
{
    SPIx->GlobalConReg |= DMA_MODE_MSK;
}

 /**
* spi_dma_disable
*
* @param[in]  SPIx: Pointer to ZN_SpiType structure
* @return none
*
* @brief Disable SPI DMA mode
*/
__STATIC_INLINE void spi_dma_disable(ZN_SpiType *SPIx)
{
    SPIx->GlobalConReg &= ~DMA_MODE_MSK;
}

 /**
* spi_rx_match_num
*
* @param[in]  SPIx: Pointer to ZN_SpiType structure
* @param[in]  num: Number of received data to match
* @return none
*
* @brief Set the number of received data to match in SPI master single receive mode
*/
__STATIC_INLINE void spi_rx_match_num(ZN_SpiType *SPIx,uint16_t num)
{
    /*
    The register is only valid in SPI master single receive mode.Note do not write "0" to the register.
    The register is only valid in SPI master single receive mode.
    */
    SPIx->RxDataNumReg = num;
}


 /**
* spi_int_tx_empty_enable
*
* @param[in]  SPIx: Pointer to ZN_SpiType structure
* @return none
*
* @brief Enable transmit empty interrupt
*/
__STATIC_INLINE void spi_int_tx_empty_enable(ZN_SpiType *SPIx)
{
    SPIx->IntEnableReg |= TX_EMPTY_INTEN_MSK;
}

 /**
* spi_int_tx_empty_disable
*
* @param[in]  SPIx: Pointer to ZN_SpiType structure
* @return none
*
* @brief Disable transmit empty interrupt
*/
__STATIC_INLINE void spi_int_tx_empty_disable(ZN_SpiType *SPIx)
{
    SPIx->IntEnableReg &= ~TX_EMPTY_INTEN_MSK;
}

/**
* spi_int_rx_full_enable
*
* @param[in]  SPIx: Pointer to ZN_SpiType structure
* @return none
*
* @brief Enable receive full interrupt
*/
__STATIC_INLINE void spi_int_rx_full_enable(ZN_SpiType *SPIx)
{
    SPIx->IntEnableReg |= RX_FULL_INTEN_MSK;
}

 /**
* spi_int_rx_full_disable
*
* @param[in]  SPIx: Pointer to ZN_SpiType structure
* @return none
*
* @brief Disable receive full interrupt
*/
__STATIC_INLINE void spi_int_rx_full_disable(ZN_SpiType *SPIx)
{
    SPIx->IntEnableReg &= ~RX_FULL_INTEN_MSK;
}

 /**
* spi_int_rx_match_enable
*
* @param[in]  SPIx: Pointer to ZN_SpiType structure
* @return none
*
* @brief Enable receive data match interrupt
*/
__STATIC_INLINE void spi_int_rx_match_enable(ZN_SpiType *SPIx)
{
    /*Receive data complete interrupt enable*/
    /*When receive data match the RXDNR number, the receive process will be completed and generate the interrupt.*/
    SPIx->IntEnableReg |= RX_MATCH_INTEN_MSK;
}

 /**
* spi_int_rx_match_disable
*
* @param[in]  SPIx: Pointer to ZN_SpiType structure
* @return none
*
* @brief Disable receive data match interrupt
*/
__STATIC_INLINE void spi_int_rx_match_disable(ZN_SpiType *SPIx)
{
    /*Receive data complete interrupt disable*/
    SPIx->IntEnableReg &= ~RX_MATCH_INTEN_MSK;
}

 /**
* spi_int_rx_overrun_enable
*
* @param[in]  SPIx: Pointer to ZN_SpiType structure
* @return none
*
* @brief Enable receive overrun interrupt
*/
__STATIC_INLINE void spi_int_rx_overrun_enable(ZN_SpiType *SPIx)
{
    SPIx->IntEnableReg |= RX_OVERRUN_INTEN_MSK;
}

 /**
* spi_int_rx_overrun_disable
*
* @param[in]  SPIx: Pointer to ZN_SpiType structure
* @return none
*
* @brief Disable receive overrun interrupt
*/
__STATIC_INLINE void spi_int_rx_overrun_disable(ZN_SpiType *SPIx)
{
    SPIx->IntEnableReg &= ~RX_OVERRUN_INTEN_MSK;
}

 /**
* spi_int_tx_underrun_enable
*
* @param[in]  SPIx: Pointer to ZN_SpiType structure
* @return none
*
* @brief Enable SPI slave transmitter underrun interrupt
*/
__STATIC_INLINE void spi_int_tx_underrun_enable(ZN_SpiType *SPIx)
{
    /*SPI slave transmitter underrun */
    SPIx->IntEnableReg |= TX_UNDERRUN_INTEN_MSK;
}

 /**
* spi_int_tx_underrun_disable
*
* @param[in]  SPIx: Pointer to ZN_SpiType structure
* @return none
*
* @brief Disable SPI slave transmitter underrun interrupt
*/
__STATIC_INLINE void spi_int_tx_underrun_disable(ZN_SpiType *SPIx)
{
    SPIx->IntEnableReg &= ~TX_UNDERRUN_INTEN_MSK;
}

/**
* spi_int_rx_avl_enable
*
* @param[in]  SPIx: SPI module pointer
* @return none
*
* @brief Enable the Receiver Available Interrupt of SPI communication
*/
__STATIC_INLINE void spi_int_rx_avl_enable(ZN_SpiType *SPIx)
{
    /*Enable Receiver available interrupt. Receiver when  FIFO has received enough data,depend on rxtlf(Global Control Register bit 6)*/
    SPIx->IntEnableReg |= RX_INTEN_MSK;
}

/**
* spi_int_rx_avl_disable
*
* @param[in]  SPIx: SPI module pointer
* @return none
*
* @brief Disable the Receiver Available Interrupt of SPI communication
*/
__STATIC_INLINE void spi_int_rx_avl_disable(ZN_SpiType *SPIx)
{
    SPIx->IntEnableReg &= ~RX_INTEN_MSK;
}

/**
* spi_int_tx_avl_enable
*
* @param[in]  SPIx: SPI module pointer
* @return none
*
* @brief Enable the Transmit FIFO Available Interrupt of SPI communication
*/
__STATIC_INLINE void spi_int_tx_avl_enable(ZN_SpiType *SPIx)
{
    /*Enable Transmit FIFO available interrupt, the interrupt depend on txtlf(Global Control Register bit 7)*/
    SPIx->IntEnableReg |= TX_INTEN_MSK;
}

/**
* spi_int_tx_avl_disable
*
* @param[in]  SPIx: SPI module pointer
* @return none
*
* @brief Disable the Transmit FIFO Available Interrupt of SPI communication
*/
__STATIC_INLINE void spi_int_tx_avl_disable(ZN_SpiType *SPIx)
{
    
    SPIx->IntEnableReg &= ~TX_INTEN_MSK;
}

/**
* spi_get_cur_status
*
* @param[in]  SPIx: SPI module pointer
* @return uint32_t: the status of SPI communication
*
* @brief Get the current status of SPI communication
*/
__STATIC_INLINE uint32_t spi_get_cur_status(ZN_SpiType *SPIx)
{
    return SPIx->CurStatusReg;
}

/**
* spi_get_int_flag
*
* @param[in]  SPIx: SPI module pointer
* @return uint32_t: the interrupt status of SPI communication
*
* @brief Get the interrupt status of SPI communication
*/
__STATIC_INLINE uint32_t spi_get_int_flag(ZN_SpiType *SPIx)
{
    return SPIx->IntStatusReg;
}

/**
* spi_clear_int_flag
*
* @param[in]  SPIx: SPI module pointer
* @param[in]  flag: interrupt flag to clear
* @return none
*
* @brief Clear the specified interrupt flag of SPI communication
*/
__STATIC_INLINE void spi_clear_int_flag(ZN_SpiType *SPIx, uint32_t flag)
{
    SPIx->IntClrReg = flag;
}

/**
* spi_tx_is_empty
*
* @param[in]  SPIx: SPI module pointer
* @return BOOL_Type: whether the SPI Transmit FIFO is empty or not
*
* @brief Check whether the SPI Transmit FIFO is empty or not
*/
__STATIC_INLINE BOOL_Type spi_tx_is_empty(ZN_SpiType *SPIx)
{
    return (spi_get_cur_status(SPIx) & TX_EMPTY_MSK) >> TX_EMPTY_POS;
}

/**
* spi_rx_is_avl
*
* @param[in]  SPIx: SPI module pointer
* @return BOOL_Type: whether the SPI Receive FIFO has available data or not
*
* @brief Check whether the SPI Receive FIFO has available data or not
*/
__STATIC_INLINE BOOL_Type spi_rx_is_avl(ZN_SpiType *SPIx)
{
    return (spi_get_cur_status(SPIx) & RXAVL_MSK) >> RXAVL_POS;
}

/**
* spi_tx_is_full
*
* @param[in]  SPIx: SPI module pointer
* @return BOOL_Type: whether the SPI Transmit FIFO is full or not
*
* @brief Check whether the SPI Transmit FIFO is full or not
*/
__STATIC_INLINE BOOL_Type spi_tx_is_full(ZN_SpiType *SPIx)
{
    return (spi_get_cur_status(SPIx) & TX_FULL_MSK) >> TX_FULL_POS;
}

/**
* spi_rx_is_avl4byte
*
* @param[in]  SPIx: SPI module pointer
* @return BOOL_Type: whether the SPI Receive FIFO has available data for 4 bytes or not
*
* @brief Check whether the SPI Receive FIFO has available data for 4 bytes or not
*/
__STATIC_INLINE BOOL_Type spi_rx_is_avl4byte(ZN_SpiType *SPIx)
{
    return (spi_get_cur_status(SPIx) & RXAVL_4BYTE_MSK) >> RXAVL_4BYTE_POS;
}

/**
* spi_read_data
*
* @param[in]  SPIx: SPI module pointer
* @return uint32_t: the data read from SPI Receive FIFO
*
* @brief Read data from the SPI Receive FIFO
*/
#define spi_read_data(SPIx) SPIx->RxDataReg

/**
* spi_write_data
*
* @param[in]  SPIx: SPI module pointer
* @param[in]  data: data to write to the SPI Transmit FIFO
* @return none
*
* @brief Write data to the SPI Transmit FIFO
*/
#define spi_write_data(SPIx,data) SPIx->TxDataReg = data

/**
* spi_is_master
*
* @param[in]  SPIx: SPI module pointer
* @return BOOL_Type: whether the SPI is configured as the master or not
*
* @brief Check whether the SPI is configured as the master or not
*/
#define spi_is_master(SPIx)  (SPIx->GlobalConReg & MASTER_MODE_MSK) >> MASTER_MODE_POS

#ifdef __cplusplus
}
#endif

#endif