/*****************************************************************************
 *  File: zn_spi.h
 *
 *  Descirption: this file contains the functions support spi operations.
 *
 *  Copyright (C) : 2022 ultraception.com
 *
 *  Author: WangJiying
 *  Mail:   
 *  Date:   2022-5-6
 *
 *****************************************************************************/
#ifndef __ZN_SPI_H__
#define __ZN_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_spi_reg.h"
typedef struct
{
    uint8_t     spiMode; /*0-3,ckpl/ckph*/
    uint8_t     master;   /*0-slaver,1-master*/
    uint8_t     lsb;     /*0-msb,1-lsb*/
    uint8_t     dataSize; /*spi length bits,value is 4-32 */
    uint8_t     txFifoTriggerEn; /*0-disable; 1-enable*/
    uint8_t     rxFifoTriggerEn; /*0-disable; 1-enable*/
    uint8_t     dmaMode;         /*0-normal access mode;1- DMA access mode*/
    uint8_t     interruptEn;    /* 0 - disable spi interrupt ;1 - enable  spi interrupt*/
    uint16_t    clkDiv; /*spi_clk div,value is 2-65535*/
    DeviceCallback_Type callBack;   /*IRQ Callback pointer */
}SPI_ConfigType;

#define SPI_CKPLH                   (1 << CKPL_POS)
#define SPI_CKPLL                   (0 << CKPL_POS)
#define SPI_CKPHH                   (1 << CKPH_POS)
#define SPI_CKPHL                   (0 << CKPH_POS)

/*
mode ckpl  ckph
0     0     1
1     0     0
2     1     1
3     1     0
*/
#define SPI_MODE0                (0)
#define SPI_MODE1                (1)
#define SPI_MODE2                (2)
#define SPI_MODE3                (3)


#define SPI_INDEX(SPIx)    ((SPIx == SPI0)?0:1)

int spi_init(ZN_SpiType *SPIx, SPI_ConfigType *config);
int spi_deinit(ZN_SpiType *SPIx);
int spi_receive_poll(ZN_SpiType *SPIx,uint8_t slecetCS, uint8_t *rxBuffer, uint32_t length);
int spi_transmit_poll(ZN_SpiType *SPIx,uint8_t slecetCS,const uint8_t *txBuffer, uint32_t length);
uint8_t spi_read_write_byte(ZN_SpiType *SPIx,uint8_t txdata);
void spi_write_byte(ZN_SpiType *SPIx,uint8_t txdata);
uint8_t spi_read_byte(ZN_SpiType *SPIx);

#ifdef __cplusplus
}
#endif

#endif