/*****************************************************************************
 *  File: hal_gp_timer.c
 *
 * Descirption: this file contains the functions support spi operations.
 *
 *  Copyright (C) : 2025 ultraception.com
 *
 *  Author: sxg
 *  Mail:   
 *  Date:   2025-5-12
 *
 *****************************************************************************/

#include "hal_spi.h"


ERROR_Type hal_spi_init(hal_spi_t *spi_config)
{
    SPI_ConfigType config = {0};
    ZN_SpiType*    spix = NULL;
    uint8_t        selectCS = 0;
    
    if(NULL == spi_config)
    {
        LOG_ERROR("null pointer");
        return ERROR;
    }
 
    spix                   = SPI_BASE(spi_config->spi_id);
    config.master          = spi_config->spi_role;
    config.clkDiv          = spi_config->clk_div;
    config.dataSize        = spi_config->data_size;
    config.spiMode         = spi_config->spi_mode;
    config.lsb             = spi_config->is_lsb;
    config.rxFifoTriggerEn = spi_config->rx_fifo_en;
    config.txFifoTriggerEn = spi_config->tx_fifo_en;
    config.dmaMode         = spi_config->access_mode;
    config.interruptEn     = spi_config->rx_interrupt_en | spi_config->tx_interrupt_en;
    config.callBack        = spi_config->func;

    if(1 == spi_config->spi_id)
    {
        sys_clear_bit(CLK_ICG_REG,CLK_ICG_REG_SPI1_CLK_ICG_SHIFT);
        sys_clear_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_SPI1_SW_RSTN_SHIFT);
        sys_set_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_SPI1_SW_RSTN_SHIFT);
        pad_reg_write(SPI1_CLK_PREG,0x178);
        pad_reg_write(SPI1_MISO_PREG,0x178);
        pad_reg_write(SPI1_MOSI_PREG,0x178);
        if(!selectCS)
        {
            pad_reg_write(SPI1_CSN_PREG,GPIOB2_AF_SPI1_CS0);/*SPI1 CS0*/
        }
        else
        {
            pad_reg_write(I2C0_SCL_PREG,GPIOA7_AF_SPI1_CS1);/*SPI1 CS1*/
        }
    }
    else
    {
        sys_clear_bit(CLK_ICG_REG,CLK_ICG_REG_SPI0_CLK_ICG_SHIFT);
        sys_clear_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_SPI0_SW_RSTN_SHIFT);
        sys_set_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_SPI0_SW_RSTN_SHIFT);
        pad_reg_write(SPI0_CLK_PREG,0x178);
        pad_reg_write(SPI0_MISO_PREG,0x178);
        pad_reg_write(SPI0_MOSI_PREG,0x178);
        if(!selectCS)
        {
            pad_reg_write(SPI0_CSN_PREG, GPIOB1_AF_SPI0_CS0);/*SPI0 CS0*/
        }
        else
        {
            pad_reg_write(I2C0_SDA_PREG, GPIOA8_AF_SPI0_CS1);/*SPI0 CS1*/
        }
    }    
    
    spi_init(spix, &config);
    
    if(config.interruptEn)
    {
        if(spi_config->tx_interrupt_en)
        {
            spi_int_tx_avl_enable(spix);
        }
        if(spi_config->rx_interrupt_en)
        {
            spi_int_rx_avl_enable(spix);
        }
        
        NVIC_EnableIRQ(SPI0_IRQn + spi_config->spi_id);
    }
    
    return SUCCESS;
}


ERROR_Type hal_spi_deinit(hal_spi_t *spi_config)
{
    ZN_SpiType*    spix = NULL;
    
    if(NULL == spi_config)
    {
        LOG_ERROR("null pointer");
        return ERROR;
    }
 
    spix = SPI_BASE(spi_config->spi_id);
    spi_deinit(spix);
    
    return SUCCESS;
}

void hal_spi_tx_enable(uint8_t spi_id)
{
    ZN_SpiType* spix = SPI_BASE(spi_id);
    
    spi_tx_enable(spix);
}

void hal_spi_tx_disable(uint8_t spi_id)
{
    ZN_SpiType* spix = SPI_BASE(spi_id);
    
    spi_tx_disable(spix);
}

void hal_spi_rx_enable(uint8_t spi_id)
{
    ZN_SpiType* spix = SPI_BASE(spi_id);
    
    spi_rx_enable(spix);
}

void hal_spi_rx_disable(uint8_t spi_id)
{
    ZN_SpiType* spix = SPI_BASE(spi_id);
    
    spi_rx_disable(spix);
}

uint32_t hal_spi_get_rx_addr(uint8_t spi_id)
{
    ZN_SpiType* spix = SPI_BASE(spi_id);
    
    return (uint32_t)(&spix->RxDataReg);
}

uint32_t hal_spi_get_tx_addr(uint8_t spi_id)
{
    ZN_SpiType* spix = SPI_BASE(spi_id);
    
    return (uint32_t)(&spix->TxDataReg);
}

void hal_spi_cs_low(uint8_t spi_id, uint8_t spi_cs)
{
    ZN_SpiType* spix = SPI_BASE(spi_id);
    
    spi_cs_low(spix, spi_cs);
}

void hal_spi_cs_high(uint8_t spi_id, uint8_t spi_cs)
{
    ZN_SpiType* spix = SPI_BASE(spi_id);
    
    spi_cs_high(spix, spi_cs);
}

void hal_spi_write_byte(uint8_t spi_id, uint8_t data)
{
    ZN_SpiType* spix = SPI_BASE(spi_id);
    
    spi_write_byte(spix,data);
}

uint8_t hal_spi_read_byte(uint8_t spi_id)
{
    ZN_SpiType* spix = SPI_BASE(spi_id);
    
    return spi_read_byte(spix);
}

uint8_t hal_spi_tx_is_full(uint8_t spi_id)
{
    ZN_SpiType* spix = SPI_BASE(spi_id);
    
    return spi_tx_is_full(spix);
}

uint8_t hal_spi_tx_is_empty(uint8_t spi_id)
{
    ZN_SpiType* spix = SPI_BASE(spi_id);
    
    return spi_tx_is_empty(spix);
}

uint8_t hal_spi_rx_is_byte_avliable(uint8_t spi_id)
{
    ZN_SpiType* spix = SPI_BASE(spi_id);
    
    return spi_rx_is_avl(spix);
}

uint8_t hal_spi_rx_is_word_avliable(uint8_t spi_id)
{
    ZN_SpiType* spix = SPI_BASE(spi_id);
    
    return spi_rx_is_avl4byte(spix);
}

uint8_t hal_spi_read_write_byte(uint8_t spi_id, uint8_t tx_data)
{
    ZN_SpiType* spix = SPI_BASE(spi_id);
    
    return spi_read_write_byte(spix, tx_data);
}

void hal_spi_rx_match_num_set(uint8_t spi_id, uint16_t num)
{
    ZN_SpiType* spix = SPI_BASE(spi_id);
    spi_rx_match_num(spix, num);
}

ERROR_Type hal_spi_transmit_poll(uint8_t spi_id, uint8_t spi_cs, uint8_t* buffer, uint32_t len)
{
    ZN_SpiType* spix = SPI_BASE(spi_id);
    
    if(NULL == buffer)
    {
        LOG_ERROR("null pointer");
        return ERROR;
    }
    
    if(spi_transmit_poll(spix, spi_cs, buffer, len) != 0)
    {
        LOG_ERROR("buffer and len not correct");
        return ERROR;
    }
    
    return SUCCESS;
}

ERROR_Type hal_spi_recv_poll(uint8_t spi_id, uint8_t spi_cs, uint8_t* buffer, uint32_t len)
{
    ZN_SpiType* spix = SPI_BASE(spi_id);
    
    if(NULL == buffer)
    {
        LOG_ERROR("null pointer");
        return ERROR;
    }
    
    if(spi_receive_poll(spix, spi_cs, buffer, len) != 0)
    {
        LOG_ERROR("buffer and len not correct");
        return ERROR;
    }
    
    return SUCCESS;
}

uint32_t hal_spi_send_data(uint8_t spi_id, uint8_t *buf, uint32_t len)
{
    ZN_SpiType *spix = SPI_BASE(spi_id);
    uint32_t   index = 0;

    spi_tx_disable(spix);
    spi_tx_enable(spix);

    for(index = 0; index < len; index++)
    {
        while(((spi_get_cur_status(spix) & TX_FULL_MSK) >> TX_FULL_POS) == 0x1);
        spi_write_data(spix, buf[index]);
    }

    return len;
}

