/*****************************************************************************
 *  File: zn_i2c.h
 *
 *  Descirption: contains the functions support iic.
 *
 *  Copyright (C) : 2023 ultraception.com.
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2023-5-18
 *
 *****************************************************************************/

#ifndef __ZN_I2C_H__
#define __ZN_I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_i2c_reg.h"
#include "zn_dma.h"
typedef enum
{
    I2C_STANDARD_SPEED = 100000,
    I2C_FAST_SPEED = 400000,
    I2C_FAST_PLUS_SPEED = 1000000,
    I2C_MAX_SPEED    =    3400000
}I2C_SPEED;

typedef struct
{                                   
    uint8_t  master;                /*0-slaver,1-master*/
    uint8_t  txFifoTrigLevel;       /*value is from 0 t0 63 ,corresponding is from 1 entry to 64 entries*/
    uint8_t  rxFifoTrigLevel;       /*value is from 0 t0 63 ,corresponding is from 1 entry to 64 entries*/
    uint8_t  interruptEn;           /* 0 - disable i2c interrupt ;1 - enable  i2c interrupt*/
    uint32_t  interruptType;        /*opens the interrupt type when interrupt enable*/
    uint32_t slaver_addr;           /*i2c slaver address*/
    IRQn_Type irq;                  /*interrupt num*/
    uint32_t clk;                   /*i2c clock*/
    I2C_SPEED speed;                /*i2c speed*/
    DeviceCallback_Type callBack;   /*IRQ Callback pointer */
}I2C_ConfigType;


typedef struct
{
    uint32_t devAddr;
    uint32_t offset;
    uint8_t  offsetSize;
    uint8_t *buffer;
    uint32_t len;    
}I2C_DeviceType;

#define NANO_TO_MICRO        1000
/* High and low times in different speed modes (in ns) */
#define MIN_SS_SCL_HIGHTIME           4000
#define MIN_SS_SCL_LOWTIME            4700
#define MIN_FS_SCL_HIGHTIME           600
#define MIN_FS_SCL_LOWTIME            1300
#define MIN_FS_PLUS_SCL_HIGHTIME      260
#define MIN_FS_PLUS_SCL_LOWTIME       500
#define MIN_HS_SCL_HIGHTIME           60
#define MIN_HS_SCL_LOWTIME            160

/* Speed Selection */
#define IC_SPEED_MODE_STANDARD    1
#define IC_SPEED_MODE_FAST        2
#define IC_SPEED_MODE_FAST_PLUS   3
#define IC_SPEED_MODE_MAX         4

#define I2C_SLAVER_ADDR  (0x0b)
#define IC_FIFO_DEPTH  16

void i2c_init(ZN_I2cType *I2Cx, I2C_ConfigType *config);
uint32_t i2c_master_read_poll(ZN_I2cType *I2Cx,I2C_DeviceType *deviceCfg);
uint32_t i2c_master_write_poll(ZN_I2cType *I2Cx,I2C_DeviceType *deviceCfg);
void i2c_dma_tx_control(ZN_I2cType *I2Cx,ACTION_Type action, uint8_t txDataLevel);
void i2c_dma_rx_control(ZN_I2cType *I2Cx,ACTION_Type action, uint8_t rxDataLevel);
uint32_t i2c_dma_master_read_poll(ZN_I2cType *I2Cx,I2C_DeviceType *deviceCfg,uint8_t dma_id, DMA_ChConfigType *dmaChConfig);
uint32_t i2c_dma_master_write_poll(ZN_I2cType *I2Cx, I2C_DeviceType *deviceCfg, uint8_t dma_id, DMA_ChConfigType *dmaChConfig);

#ifdef __cplusplus
}
#endif

#endif