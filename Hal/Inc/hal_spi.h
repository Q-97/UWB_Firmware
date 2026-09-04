/*****************************************************************************
* File: hal_uart.h
*
* Descirption: this file contains the spi hal functions.
*
* Copyright (C) : 2025 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2025 - 5
*****************************************************************************/
#ifndef _HAL_SPI_H
#define _HAL_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "zn_spi.h"

#define SPI_BASE(x)    ((0 == (x)) ? SPI0 : SPI1)
#define SPI_ID(x)      ((SPI0 == (x)) ? 0 : 1)

typedef struct hal_spi
{
    uint8_t spi_id : 1;          //0 spi0, 1 spi1
    uint8_t spi_cs : 1;          //0 cs0, 1 cs1
    uint8_t spi_role : 1;        //0 slave , 1 master
    uint8_t is_lsb : 1;          //0 msb, 1 lsb
    uint8_t tx_fifo_en : 1;      //0 disable  1 enable
    uint8_t rx_fifo_en : 1;      //0 disable  1 enable
    uint8_t access_mode : 1;     //0 normal mode  1 dma mode
    uint8_t tx_interrupt_en : 1; //0 disable 1 enable
    uint8_t rx_interrupt_en : 1; //0 disable 1 enable
    uint8_t spi_mode : 2;        //spi mode 0-3 ckpl/ckph
    uint8_t data_size : 6;       //bits length, range 4-32 bits
    uint16_t clk_div;            //spi clk div ,rage 2-65535         
    DeviceCallback_Type func;    //interrupt callback
}hal_spi_t;



ERROR_Type hal_spi_init(hal_spi_t *spi_config);
ERROR_Type hal_spi_deinit(hal_spi_t *spi_config);
void hal_spi_tx_enable(uint8_t spi_id);
void hal_spi_tx_disable(uint8_t spi_id);
void hal_spi_rx_enable(uint8_t spi_id);
void hal_spi_rx_disable(uint8_t spi_id);
uint32_t hal_spi_get_rx_addr(uint8_t spi_id);
uint32_t hal_spi_get_tx_addr(uint8_t spi_id);
void hal_spi_cs_low(uint8_t spi_id, uint8_t spi_cs);
void hal_spi_cs_high(uint8_t spi_id, uint8_t spi_cs);
void hal_spi_write_byte(uint8_t spi_id, uint8_t data);
uint8_t hal_spi_read_byte(uint8_t spi_id);
uint8_t hal_spi_tx_is_full(uint8_t spi_id);
uint8_t hal_spi_tx_is_empty(uint8_t spi_id);
uint8_t hal_spi_rx_is_byte_avliable(uint8_t spi_id);
uint8_t hal_spi_rx_is_word_avliable(uint8_t spi_id);
uint8_t hal_spi_read_write_byte(uint8_t spi_id, uint8_t tx_data);
void hal_spi_rx_match_num_set(uint8_t spi_id, uint16_t num);
ERROR_Type hal_spi_transmit_poll(uint8_t spi_id, uint8_t spi_cs, uint8_t* buffer, uint32_t len);
ERROR_Type hal_spi_recv_poll(uint8_t spi_id, uint8_t spi_cs, uint8_t* buffer, uint32_t len);
uint32_t hal_spi_send_data(uint8_t spi_id, uint8_t *buf, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif
