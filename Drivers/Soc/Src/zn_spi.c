/*****************************************************************************
 *  File: zn_spi.c
 *
 *  Descirption: this file contains the functions support spi operations.
 *
 *  Copyright (C) : 2023 ultraception.com
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2023-5-6
 *
 *****************************************************************************/

#include "zn_spi.h"
DeviceCallback_Type s_spiCallback[SPI_NUM] = {0};

/** spi_init
*
* @param[in]  SPIx: Pointer to the SPI interface to be initialized
* @param[in]  config: Pointer to the configuration structure for SPI initialization
* @return 0 on success, negative value on error
*
* @brief Initializes the SPI interface based on the configuration structure provided.
*/
int spi_init(ZN_SpiType *SPIx, SPI_ConfigType *config)
{
    uint8_t spiMode = 0;
    uint32_t comConfig = 0;
    uint32_t gloalConfig = 0;
    if ((SPIx != SPI0) && (SPIx != SPI1))
    {
        return -1;
    }
    switch (config->spiMode)
    {
        case SPI_MODE0:
            spiMode = SPI_CKPLL | SPI_CKPHH;     
        break;
        case SPI_MODE1:
            spiMode = SPI_CKPLL | SPI_CKPHL;
        break;
        case SPI_MODE2:
            spiMode = SPI_CKPLH | SPI_CKPHH;     
        break;
        case SPI_MODE3:
            spiMode = SPI_CKPLH | SPI_CKPHL;    
        break;
        default:
            return -2;
        break;        
    }
    comConfig |= spiMode;
    comConfig |= SPI_LEN_BITS_MSK(config->dataSize);
    if (config->lsb)
    {
        comConfig |= LSB_ENBALE_MSK;
    }
    if (config->clkDiv <= 4)
    {
        comConfig |= (TX_EDGE_MSK | RX_EDGE_MSK);
    }
    /*CommonConReg, BaudRateReg Configure once*/
    SPIx->CommonConReg = comConfig;
    SPIx->BaudRateReg = config->clkDiv;

    if (SPIx == SPI0)
    {
        s_spiCallback[0] = config->callBack;
    }
    else
    {
        s_spiCallback[1] = config->callBack;
    }
    
    if (config->interruptEn)
    {
        gloalConfig |= INT_ENABLE_MSK;
    }
    if (config->master)
    {
        gloalConfig |= MASTER_MODE_MSK;
    }
    if (config->rxFifoTriggerEn)
    {
        gloalConfig |= RXFIFO_TRIGGER_LEVEL_MSK;
    }
    if (config->txFifoTriggerEn)
    {
        gloalConfig |= TXFIFO_TRIGGER_LEVEL_MSK;
    }
    if (config->dmaMode)
    {
        gloalConfig |= DMA_MODE_MSK;
    }
    
    /*spi enable*/
    gloalConfig |= SPI_ENABLE_MSK;
    SPIx->GlobalConReg = gloalConfig; /*Other bits of the register will be configured later*/

    return 0;
}

/**
* spi_deinit
*
* @param[in]  SPIx: Pointer to the SPI interface to be de-initialized
* @return 0 on success
*
* @brief De-initializes the SPI interface and disables its interrupt.
*/
int spi_deinit(ZN_SpiType *SPIx)
{
    uint8_t spi_id = SPI_INDEX(SPIx);
    NVIC_DisableIRQ(SPI0_IRQn+spi_id);
    SPIx->IntEnableReg = 0x00;
    SPIx->GlobalConReg = 0x00;
    s_spiCallback[spi_id] = NULL;
    return 0;    
}

/**
* spi_transmit_poll
*
* @param[in]  SPIx: Pointer to the SPI interface to be used for transmission
* @param[in]  slecetCS: Chip select number for the slave device
* @param[in]  txBuffer: Pointer to the buffer containing data to be transmitted
* @param[in]  length: Length of the data to be transmitted
* @return 0 on success; negative value on error
*
* @brief Transmits data over SPI interface in polling mode.
*/
int spi_transmit_poll(ZN_SpiType *SPIx,uint8_t slecetCS,const uint8_t *txBuffer, uint32_t length)
{    
    uint8_t dataSize = ((SPIx->CommonConReg >> SPI_LEN_BITS_POS) & 0x1F) + 1;
    if ((length == 0) || (txBuffer == NULL))
    {
        return -1;
    }
    if (spi_is_master(SPIx))
    {
        spi_cs_low(SPIx,slecetCS);
    }
    spi_tx_enable(SPIx);
    if (4<=dataSize && dataSize<=8)
    {
        for(int i =0; i<length; )
        {
            if(!spi_tx_is_full(SPIx))
            {
                spi_write_data(SPIx,txBuffer[i++]);
            }
        }    
    }
    else if(9<=dataSize && dataSize<=16)
    {
        uint16_t *ptemp = (uint16_t *)txBuffer;
        
        if (((uint32_t)txBuffer&0x01) || (length&0x01)) /* txBuffer is not half-word alignment ,length is not Multiple of 2*/
        {
            return -2;
        }
        
        length = length>>1;
        for(int i =0; i<length; )
        {
            if(!spi_tx_is_full(SPIx))
            {
                spi_write_data(SPIx,ptemp[i++]);
            }
        }
    }
    else if(17<=dataSize && dataSize<=32)
    {
        uint32_t *ptemp = (uint32_t *)txBuffer;
        if (((uint32_t)txBuffer&0x03) || (length&0x03)) /* txBuffer is not word alignment ,length is not Multiple of 4*/
        {
            return -3;
        }
        length = length>>2;
        for(int i =0; i<length; )
        {
            if(!spi_tx_is_full(SPIx))
            {
                spi_write_data(SPIx,ptemp[i++]);
            }
        }
    }

    while(!spi_tx_is_empty(SPIx)); /*send finish*/
    
    if (spi_is_master(SPIx))
    {
        spi_cs_high(SPIx,slecetCS);
    }
    spi_tx_disable(SPIx);    
    return 0;
}
/**
* spi_receive_poll
*
* @param[in]  SPIx: Pointer to the SPI interface to be used for reception
* @param[in]  slecetCS: Chip select number for the slave device
* @param[out] rxBuffer: Pointer to the buffer where received data will be stored
* @param[in]  length: Length of the data to be received
* @return 0 on success; negative value on error
*
* @brief Receives data over SPI interface in polling mode.
*/
int spi_receive_poll(ZN_SpiType *SPIx,uint8_t slecetCS, uint8_t *rxBuffer, uint32_t length)
{
    uint8_t dataSize = ((SPIx->CommonConReg >> SPI_LEN_BITS_POS) & 0x1F) + 1;
    if ((length == 0) || (rxBuffer == NULL))
    {
        return -1;
    }
    
    if (spi_is_master(SPIx))
    {
        spi_cs_low(SPIx,slecetCS);
    }
    if (4<=dataSize && dataSize<=8)
    {
        spi_rx_match_num(SPIx, length);
        spi_rx_enable(SPIx);
        for(int i =0; i<length; )
        {
            if (spi_rx_is_avl(SPIx))
            {
                rxBuffer[i++] = spi_read_data(SPIx);
            }
        }    
    }    
    else if(9<=dataSize && dataSize<=16)
    {
        uint16_t *ptemp = (uint16_t *)rxBuffer;

        if (((uint32_t)rxBuffer&0x01) || (length&0x01)) /* rxBuffer is not half-word alignment ,length is not Multiple of 2*/
        {
            return -2;
        }
        spi_rx_match_num(SPIx, length);
        spi_rx_enable(SPIx);
        length = length>>1;
        for(int i =0; i<length; )
        {
            if (spi_rx_is_avl(SPIx))
            {
                ptemp[i++] = spi_read_data(SPIx);
            }
        }
    }
    else if(17<=dataSize && dataSize<=32)
    {
        uint32_t *ptemp = (uint32_t *)rxBuffer;

        if (((uint32_t)rxBuffer&0x03) || (length&0x03)) /* rxBuffer is not word alignment ,length is not Multiple of 4*/
        {
            return -2;
        }
        
        spi_rx_match_num(SPIx, length);
        spi_rx_enable(SPIx);
        length = length>>2;
        for(int i =0; i<length; )
        {            
            if (spi_rx_is_avl(SPIx))
            {
                ptemp[i++] = spi_read_data(SPIx);
            }
        }
    }
    if (spi_is_master(SPIx))
    {
        spi_cs_high(SPIx,slecetCS);
    }
    spi_rx_disable(SPIx);    
    return 0;
}

/**
* spi_read_write_byte
*
* @param[in]  SPIx: Pointer to the SPI interface to be used for read and write operations
* @param[in]  txdata: Data to be transmitted
* @return Received data
*
* @brief Performs a read and write operation over the SPI interface and returns the received data.
*/
uint8_t spi_read_write_byte(ZN_SpiType *SPIx,uint8_t txdata)
{
    /*when config spi length bits is 8*/
    while(!spi_tx_is_empty(SPIx)){}
    spi_write_data(SPIx,txdata);
    
    while(!spi_rx_is_avl(SPIx));    
    return spi_read_data(SPIx)&0xFF;
}

/**
* spi_write_byte
*
* @param[in]  SPIx: Pointer to the SPI interface to be used for write operation
* @param[in]  txdata: Data to be transmitted
* @return None
*
* @brief Writes a byte of data over the SPI interface.
*/
void spi_write_byte(ZN_SpiType *SPIx,uint8_t txdata)
{
    spi_write_data(SPIx,txdata);
}

/**
* spi_read_byte
*
* @param[in]  SPIx: SPI module pointer
* @return uint8_t: the byte read from SPI Receive FIFO
*
* @brief Read a byte from the SPI Receive FIFO. Wait until the data is available.
*/
uint8_t spi_read_byte(ZN_SpiType *SPIx)
{
    return spi_read_data(SPIx)&0xFF;
}

/**
* SPI0_IRQHandler
*
* @param None
* @return None
*
* @brief Interrupt handler for SPI0 interface.
*/
void SPI0_IRQHandler(void)
{
    ZN_SpiType *SPIx = SPI0;
    uint32_t int_status = SPIx->IntStatusReg;
    uint32_t lpara;
    if (s_spiCallback[0])
    {
        spi_clear_int_flag(SPIx,int_status);
        s_spiCallback[0](SPIx, int_status, lpara);
    }
}

/**
* SPI1_IRQHandler
*
* @param None
* @return None
*
* @brief Interrupt handler for SPI1 interface.
*/
void SPI1_IRQHandler(void)
{
    ZN_SpiType *SPIx = SPI1;
    uint32_t int_status = SPIx->IntStatusReg;
    uint32_t lpara;
    if (s_spiCallback[1])
    {
        spi_clear_int_flag(SPIx,int_status);
        s_spiCallback[1](SPIx, int_status, lpara);
    }
}