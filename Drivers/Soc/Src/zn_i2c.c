/*****************************************************************************
 *  File: zn_iic.c
 *
 *  Descirption: this file contains the functions support i2c operations.
 *
 *  Copyright (C) : 2023 ultraception.com
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2023-5-19
 *
 *****************************************************************************/

#include "zn_i2c.h"

#define I2C_TIMEOUT_CNT  (0x50000)
DeviceCallback_Type i2c_callbackFunc = NULL;

/**
 * i2c_clear_int_flag
 *
 * @param[in]  I2Cx: i2c module pointer
 * @param[in]  flag: i2c interrupt flag to be cleared
 * @return none
 *
 * @brief This function clears the specified i2c interrupt flag(s)
 */
void i2c_clear_int_flag(ZN_I2cType *I2Cx, uint32_t flag)
{
    uint32_t tmp32 = 0;
    if ((flag & IC_RX_UNDER) != 0) 
    {
        tmp32 = I2Cx->ic_clr_rx_under;
    }
    if ((flag & IC_RX_OVER) != 0) 
    {
        tmp32 = I2Cx->ic_clr_rx_over;
    }
    if ((flag & IC_TX_OVER) != 0) 
    {
        tmp32 = I2Cx->ic_clr_tx_over;
    }
    if ((flag & IC_RD_REQ) != 0) 
    {
        tmp32 = I2Cx->ic_clr_rd_req;
    }
    if ((flag & IC_TX_ABRT) != 0) 
    {
        tmp32 = I2Cx->ic_tx_abrt_source;
        tmp32 = I2Cx->ic_clr_tx_abrt;
    }
    if ((flag & IC_RX_DONE) != 0) 
    {
        tmp32 = I2Cx->ic_clr_rx_done;
    }
    if ((flag & IC_ACTIVITY) != 0) 
    {
        tmp32 = I2Cx->ic_clr_activity;
    }
    if ((flag & IC_START_DET) != 0) 
    {
        tmp32 = I2Cx->ic_clr_start_det;
    }
    if ((flag & IC_GEN_CALL) != 0) 
    {
        tmp32 = I2Cx->ic_clr_gen_call;
    }    
}

/**
 * I2C0_IRQHandler
 *
 * @param[in]  none
 * @param[out] none
 * @return     none
 *
 * @brief      Interrupt handler for I2C0 module
 */
void I2C0_IRQHandler(void)
{
    if (i2c_callbackFunc)
    {
        i2c_callbackFunc((ZN_I2cType *)I2C0, 0, 0);
    }
}


/**
 * I2C1_IRQHandler
 *
 * @param[in]  none
 * @param[out] none
 * @return     none
 *
 * @brief      Interrupt handler for I2C0 module
 */
void I2C1_IRQHandler(void)
{
    if (i2c_callbackFunc)
    {
        i2c_callbackFunc((ZN_I2cType *)I2C1, 0, 0);
    }
}

/**
 * i2c_set_speed
 *
 * @param[in]  I2Cx: pointer to I2C module
 * @param[in]  i2c_clk: I2C bus clock frequency
 * @param[in]  i2c_speed: I2C speed in Hz
 * @param[out] none
 * @return     none
 *
 * @brief      Set I2C speed by configuring the I2C clock divider registers
 */
void i2c_set_speed(ZN_I2cType *I2Cx, uint32_t i2c_clk, uint32_t i2c_speed)
{
    uint32_t cntl = 0;
    uint32_t hcnt = 0;
    uint32_t lcnt = 0;
    uint32_t i2c_speedLevel = 0;
    
    if (i2c_speed >= I2C_MAX_SPEED) 
    {
        i2c_speedLevel = IC_SPEED_MODE_MAX;
    } 
    else if (i2c_speed >= I2C_FAST_PLUS_SPEED) 
    {
        i2c_speedLevel = IC_SPEED_MODE_FAST_PLUS;
    } 
    else if (i2c_speed >= I2C_FAST_SPEED) 
    {
        i2c_speedLevel = IC_SPEED_MODE_FAST;
    } 
    else 
    {
        i2c_speedLevel = IC_SPEED_MODE_STANDARD;
    }
    
    uint32_t ic_clk = i2c_clk/1000000; /*Convert to XX M*/
    
    /* to set speed cltr must be disabled */
    I2Cx->ic_enable &= ~IC_ENABLE_0B;
    
    /*
    wait until IC_EN goes to 0 in IC_ENABLE_STATUS
    which means it has completely been disabled
    */
    while ((I2Cx->ic_enable_status & IC_ENABLE_0B) != 0);
    
    /*set ic_con bit2 and bit 1*/
    I2Cx->ic_con |= IC_CON_SPD_HS;
    switch (i2c_speedLevel)
    {
        case IC_SPEED_MODE_MAX:
            cntl |= IC_CON_SPD_HS;
            hcnt = (ic_clk * MIN_HS_SCL_HIGHTIME) / NANO_TO_MICRO;
            I2Cx->ic_hs_scl_hcnt = hcnt;
            lcnt = (ic_clk * MIN_HS_SCL_LOWTIME) / NANO_TO_MICRO;
            I2Cx->ic_hs_scl_lcnt = lcnt;
            break;
        case IC_SPEED_MODE_STANDARD:
            cntl |= IC_CON_SPD_SS;
            hcnt = (ic_clk * MIN_SS_SCL_HIGHTIME) / NANO_TO_MICRO;
            I2Cx->ic_ss_scl_hcnt = hcnt;
            lcnt = (ic_clk * MIN_SS_SCL_LOWTIME) / NANO_TO_MICRO;
            I2Cx->ic_ss_scl_lcnt = lcnt;
            break;
        case IC_SPEED_MODE_FAST_PLUS:
            cntl |= IC_CON_SPD_FS;
            hcnt = (ic_clk * MIN_FS_PLUS_SCL_HIGHTIME) / NANO_TO_MICRO;
            I2Cx->ic_fs_scl_hcnt = hcnt;
            lcnt = (ic_clk * MIN_FS_PLUS_SCL_LOWTIME) / NANO_TO_MICRO;
            I2Cx->ic_fs_scl_lcnt = lcnt;
            break;
        case IC_SPEED_MODE_FAST:
        default:
            cntl |= IC_CON_SPD_FS;
            hcnt = (ic_clk * MIN_FS_SCL_HIGHTIME) / NANO_TO_MICRO;
            I2Cx->ic_fs_scl_hcnt = hcnt;
            lcnt = (ic_clk * MIN_FS_SCL_LOWTIME) / NANO_TO_MICRO;
            I2Cx->ic_fs_scl_lcnt = lcnt;
            break;
    }
    
    I2Cx->ic_con &= (0xFFFFFFF9|cntl);

    /* Enable i2c with new speed set */
    I2Cx->ic_enable |= IC_ENABLE_0B;
}

/**
 * i2c_init
 *
 * @param[in]  I2Cx: pointer to I2C module
 * @param[in]  config: pointer to structure containing I2C configuration parameters
 * @param[out] none
 * @return     none
 *
 * @brief      Initialize I2C module with given configuration parameters
 */
void i2c_init(ZN_I2cType *I2Cx, I2C_ConfigType *config)
{
    I2C_SPEED speed = config->speed;
    /* Disable i2c */
    I2Cx->ic_enable &= ~IC_ENABLE_0B;    
    /* 
     wait until IC_EN goes to 0 in IC_ENABLE_STATUS
     which means it has completely been disabled
    */
    while ((I2Cx->ic_enable_status & IC_ENABLE_0B) != 0);
    
    if (config->master)
    {
        if (speed <=I2C_STANDARD_SPEED)
        {
            I2Cx->ic_con = IC_CON_SD | IC_CON_RE | IC_CON_SPD_SS | IC_CON_MM;
        }
        else if (speed >= I2C_FAST_SPEED && speed<=I2C_FAST_PLUS_SPEED)
        {
            I2Cx->ic_con = IC_CON_SD | IC_CON_RE | IC_CON_SPD_FS | IC_CON_MM;
        }
        else if (I2C_FAST_PLUS_SPEED >= I2C_FAST_SPEED && speed<=I2C_MAX_SPEED)
        {
            I2Cx->ic_con = IC_CON_SD | IC_CON_RE | IC_CON_SPD_HS | IC_CON_MM;
        }
        else
        {
            return;
        }
        
    }
    else
    {
        if (speed <=I2C_STANDARD_SPEED)
        {
            I2Cx->ic_con =IC_CON_SPD_SS;
        }
        else if (speed >= I2C_FAST_SPEED && speed<=I2C_FAST_PLUS_SPEED)
        {
            I2Cx->ic_con = IC_CON_SPD_FS;
        }
        else if (I2C_FAST_PLUS_SPEED >= I2C_FAST_SPEED && speed<=I2C_MAX_SPEED)
        {
            I2Cx->ic_con = IC_CON_SPD_HS;
        }
        else
        {
            return;
        }
        I2Cx->ic_sar = config->slaver_addr;
        if(config->slaver_addr > 0x7F)
        {
            I2Cx->ic_con |= IC_CON_10BITADDR_SLAVE;
        }
    }
    
    I2Cx->ic_rx_tl = config->rxFifoTrigLevel;
    I2Cx->ic_tx_tl = config->txFifoTrigLevel;
    
    if (config->interruptEn)
    {
        i2c_callbackFunc = config->callBack;
        I2Cx->ic_intr_mask = config->interruptType;
        NVIC_EnableIRQ(config->irq);
    }
    else 
    {
        I2Cx->ic_intr_mask = 0;
        NVIC_DisableIRQ(config->irq);
    }
    i2c_set_speed(I2Cx, config->clk, (uint32_t)config->speed);
    /* Enable i2c */
    I2Cx->ic_enable = IC_ENABLE_0B;
}

/**
 * i2c_setaddress
 *
 * @param[in]  I2Cx: pointer to I2C module
 * @param[in]  i2c_addr: 7-bit or 10-bit I2C address
 * @param[out] none
 * @return     none
 *
 * @brief      Set I2C address for master transactions
 */
static void i2c_setaddress(ZN_I2cType *I2Cx, uint16_t i2c_addr)
{
    /* Disable i2c */
    I2Cx->ic_enable &= ~IC_ENABLE_0B;

    /* 
    wait until IC_EN goes to 0 in IC_ENABLE_STATUS
    which means it has completely been disabled  
    */
    while ((I2Cx->ic_enable_status & IC_ENABLE_0B) != 0);    
    
    if (i2c_addr>0xFF) /*For 10-bit Address*/
    {
        i2c_addr &= 0x7FF;
        i2c_addr |= (0x1<<12); 
    }

    I2Cx->ic_tar = i2c_addr;/*This is the target address for any master transaction. Slave Address is 7-bit or 10-bit*/

    /* Enable i2c */
    I2Cx->ic_enable |= IC_ENABLE_0B;
}

/**
 * i2c_flush_rxfifo
 *
 * @param[in]  I2Cx: pointer to I2C module
 * @param[out] none
 * @return     none
 *
 * @brief      Flush the I2C receive FIFO
 */
static void i2c_flush_rxfifo(ZN_I2cType *I2Cx) 
{
    uint32_t tmp32 = 0;
    /*Read the rxfifo uintil rxfifo is empty*/
    while ((I2Cx->ic_status & IC_STATUS_RFNE) != 0) 
    {
        tmp32 = I2Cx->ic_cmd_data;
    }
}

/**
 * i2c_wait_for_bb
 *
 * @param[in]  I2Cx: pointer to I2C module
 * @param[out] none
 * @return     0 if I2C bus is idle, 1 if I2C bus is busy
 *
 * @brief      Wait for I2C bus to become idle
 */
static uint32_t i2c_wait_for_bb(ZN_I2cType *I2Cx) 
{
    uint32_t timeout = 0 ;
    while (((I2Cx->ic_status & IC_STATUS_MA) != 0) ||
           ((I2Cx->ic_status & IC_STATUS_TFE) == 0)) 
    {
        /* Evaluate timeout */
        if (timeout++ > I2C_TIMEOUT_CNT) 
        {
            return 1;  /*i2c is busy*/
        }
    }

    return 0; /*i2c is idle*/
}

/**
 * i2c_get_ack
 *
 * @param[in]  I2Cx: pointer to I2C module
 * @param[out] none
 * @return     0 if ACK is received, 1 if NOACK is received and transfer needs to be restarted
 *
 * @brief      Wait for ACK or NOACK from I2C slave device
 */
static uint8_t i2c_get_ack(ZN_I2cType *I2Cx) 
{
    uint32_t tmp32 = 0;

    /* waiting for transmitting done */
    while((I2Cx->ic_raw_intr_stat & IC_MST_ON_HOLD) == 0) 
    {
        if ((I2Cx->ic_raw_intr_stat & IC_STOP_DET) != 0) 
        {
            /*wait for STOP_DET if not MST_ON_HOLD*/
            if ((I2Cx->ic_tx_abrt_source & IC_ABRT_7B_ADDR_NOACK) != 0) 
            {
                /*means we got NOACK, need to restart the transfer*/
                tmp32 = I2Cx->ic_clr_tx_abrt;
                tmp32 = I2Cx->ic_clr_stop_det;
                return 1;
            } 
            else 
            {
                /*
                if it is a read operation without data address,
                then there could be no NOACK, but STOP_DET normally
                after receiving data, so go on normally
                */
                return 0;
            }
        }
    }
    return 0;
}

/**
* i2c_xfer_init
*
* @param[in]  I2Cx: Pointer to ZN_I2cType structure
* @param[in]  chip: I2C chip address
* @param[in]  addr: I2C address
* @param[in]  alen: Length of the address
* 
* @return uint32_t: Returns zero upon successful completion, otherwise returns non-zero error code
*
* @brief Initializes I2C transfer and sends the I2C address and length
*/
static uint32_t i2c_xfer_init(ZN_I2cType *I2Cx, uint32_t chip, uint32_t addr,uint32_t alen) 
{
    uint32_t timeout = 0;
    uint32_t len = alen;
    uint32_t tmp32 = 0;
    uint32_t value= 0;

    if (i2c_wait_for_bb(I2Cx)) 
    {
        return 1;
    }

    i2c_setaddress(I2Cx, chip);

    while (alen) 
    {
        //if ((I2Cx->ic_status & IC_STATUS_TFNF) != 0) 
        {
            alen--;
            /* high byte address going out first */
            value = ((addr >> (alen * 8)) & 0xff);
            /*it must be write operation for setting up the data address */
            I2Cx->ic_cmd_data = value;
//            if (alen == len - 1) 
//            {
//                tmp32 = i2c_get_ack(I2Cx);
//                if (tmp32 == 1) 
//                {
//                    timeout++;
//                    if (timeout > I2C_TIMEOUT_CNT) 
//                    {
//                        return 1;  /*fail for no ack*/
//                    }
//                    alen = len;
//                    continue;
//                }
//            }
        }
    }

    return 0;
}

/**
* i2c_xfer_finish
*
* @param[in]  I2Cx: Pointer to ZN_I2cType structure
* 
* @return uint32_t: Returns zero upon successful completion, otherwise returns non-zero error code
*
* @brief Waits for the completion of I2C transfer, flushes the rest data in FIFO, and disables I2C module
*/
static uint32_t i2c_xfer_finish(ZN_I2cType *I2Cx)
{
    uint32_t timeout = 0;
    uint32_t tmp32 = 0;

    /*wait for all the transfer is finished after a STOP command issued*/

    while (1)
    {
        if ((I2Cx->ic_raw_intr_stat & IC_STOP_DET) != 0)
        {
            tmp32 = I2Cx->ic_clr_stop_det;
            break;
        } 
        else if (timeout++> I2C_TIMEOUT_CNT) 
        {         
            break;
        }
    }

    if (i2c_wait_for_bb(I2Cx))
    {       
        return 1;
    }
    /* Since we have received all we want in read operation, flush the rest data in FIFO  */
    i2c_flush_rxfifo(I2Cx);

    // disable i2c at last
    I2Cx->ic_enable &= ~IC_ENABLE_0B;
    // wait until IC_EN goes to 0 in IC_ENABLE_STATUS
    // which means it has completely been disabled
    while ((I2Cx->ic_enable_status & IC_ENABLE_0B) != 0);

    return 0;
}

/**
* i2c_master_read_poll
*
* @param[in]  I2Cx: Pointer to ZN_I2cType structure
* @param[in]  deviceCfg: Pointer to I2C_DeviceType structure containing 
*                        device address, offset, offset size, buffer and length information
* 
* @return uint32_t: Returns zero upon successful completion, otherwise returns non-zero error code
*
* @brief Initiates I2C transfer for read operation in polling mode, waits for completion of transfer,
*        and stores the received data in buffer
*/
uint32_t i2c_master_read_poll(ZN_I2cType *I2Cx,I2C_DeviceType *deviceCfg)
{
    uint32_t timeout = 0;
    uint32_t timeout_ack = 0;
    uint32_t tmp32 = 0;
    uint32_t tmp_len = deviceCfg->len;
    uint32_t len = deviceCfg->len;
    uint8_t *buffer = deviceCfg->buffer;
    /**/
    if (i2c_xfer_init(I2Cx,deviceCfg->devAddr,deviceCfg->offset,deviceCfg->offsetSize))
    {
        return 1;
    }
    
    while (len) 
    {
        if ((I2Cx->ic_status & IC_STATUS_TFNF) != 0) 
        {
            if (len == 1) 
            {
                I2Cx->ic_cmd_data = IC_CMD | IC_STOP; // CMD = Read
            } 
            else 
            {
                I2Cx->ic_cmd_data = IC_CMD; // CMD = Read
            }
            /* some read operation may not have offset */
            if ((deviceCfg->offsetSize == 0) && (len == tmp_len)) 
            {
                tmp32 = i2c_get_ack(I2Cx);
                if (tmp32 == 1) 
                {
                    timeout_ack++;
                    if (timeout_ack > I2C_TIMEOUT_CNT) 
                    {
                        return 1;
                    }
                    continue;
                }
            }
        }

        while (1) 
        {
            if ((I2Cx->ic_status & IC_STATUS_RFNE) != 0) 
            {
                *buffer = (I2Cx->ic_cmd_data & 0xff);
                buffer++;
                len--;
                timeout = 0;
                break;
            } 
            else if (timeout++ > I2C_TIMEOUT_CNT) 
            {
                return 1;
            }
        }
    }
     return i2c_xfer_finish(I2Cx);
}

/**
* i2c_master_write_poll
*
* @param[in]  I2Cx: Pointer to ZN_I2cType structure
* @param[in]  deviceCfg: Pointer to I2C_DeviceType structure containing device address,
*                        offset, offset size, buffer and length information
* 
* @return uint32_t: Returns zero upon successful completion, otherwise returns non-zero error code
*
* @brief Initiates I2C transfer for write operation in polling mode, 
*        waits for completion of transfer, and sends the data in buffer
*/
uint32_t i2c_master_write_poll(ZN_I2cType *I2Cx,I2C_DeviceType *deviceCfg)
{
    uint32_t timeout = 0;
    uint32_t len = deviceCfg->len;
    uint8_t *buffer = deviceCfg->buffer;
    if (i2c_xfer_init(I2Cx,deviceCfg->devAddr,deviceCfg->offset,deviceCfg->offsetSize))
    {
        return 1;
    }
    while (len) 
    {
        if ((I2Cx->ic_status & IC_STATUS_TFNF) != 0) 
        {
            if (--len == 0) 
            {
                I2Cx->ic_cmd_data = *buffer | IC_STOP;
            } 
            else 
            {
                I2Cx->ic_cmd_data = *buffer;
            }
            buffer++;
            timeout = 0;
        } 
        else if (timeout++ > I2C_TIMEOUT_CNT) 
        {
            return 1;
        }
    }
    return i2c_xfer_finish(I2Cx);
}

/**
 * i2c_dma_tx_control
 *
 * @param[in]  I2Cx: pointer to I2C peripheral type
 * @param[in]  action: action type (ENABLE/DISABLE)
 * @param[in]  txDataLevel: transmit data level
 * @return none
 *
 * @brief Controls the transmit DMA for the specified I2C peripheral.
 */
void i2c_dma_tx_control(ZN_I2cType *I2Cx,ACTION_Type action, uint8_t txDataLevel)
{
    if (ENABLE == action)
    {
        I2Cx->ic_dma_cr |= IC_DMA_CR_TDMAE;
        I2Cx->ic_dma_tdlr = txDataLevel; /* Transmit Data Level.*/
    }
    else
    {
        I2Cx->ic_dma_cr &= ~IC_DMA_CR_TDMAE;
    }
}

/**
* i2c_dma_rx_control
*
* @param[in]  I2Cx: pointer to I2C register structure
* @param[in]  action: enable/disable action
* @param[in]  rxDataLevel: receive data level
* @return none
*
* @brief Control DMA receive for I2C module
*/
void i2c_dma_rx_control(ZN_I2cType *I2Cx,ACTION_Type action, uint8_t rxDataLevel)
{
    if (ENABLE == action)
    {
        I2Cx->ic_dma_cr |= IC_DMA_CR_RDMAE;
        I2Cx->ic_dma_rdlr = rxDataLevel; /*Receive Data Level*/
    }
    else
    {
        I2Cx->ic_dma_cr &= ~IC_DMA_CR_RDMAE;
    }
}

/**
* i2c_dma_master_read_poll
*
* @param[in]  I2Cx: pointer to I2C register structure
* @param[in]  deviceCfg: pointer to I2C device configuration structure
* @param[in]  dma_id: DMA channel ID
* @param[in]  dmaChConfig: pointer to DMA channel configuration structure
* @return 0 if successful, 1 otherwise
*
* @brief Perform I2C master read operation with DMA and polling
*/
uint32_t i2c_dma_master_read_poll(ZN_I2cType *I2Cx,I2C_DeviceType *deviceCfg,uint8_t dma_id, DMA_ChConfigType *dmaChConfig)
{
    uint32_t timeout = 0;
    uint32_t timeout_ack = 0;
    uint32_t tmp32 = 0;
    uint32_t len = deviceCfg->len;
    uint8_t *buffer = deviceCfg->buffer;

    if (i2c_xfer_init(I2Cx,deviceCfg->devAddr,deviceCfg->offset,deviceCfg->offsetSize))
    {
        return 1;
    }

    I2Cx->ic_dma_cr = IC_DMA_CR_RDMAE;
    I2Cx->ic_dma_rdlr = 0; /*Receive Data Level*/
    
    
    /*DMA+I2C+RX channel config, RX FIFO->MEM*/
    dmaChConfig->srcAddr = (uint32_t)(&I2Cx->ic_cmd_data);
    dmaChConfig->destAddr  = (uint32_t)deviceCfg->buffer;
    dmaChConfig->srcMsize     = DMA_MSIZE_0; 
    dmaChConfig->destMsize    = DMA_MSIZE_0;
    dmaChConfig->srcAddrInc   = DMA_ADDRESS_NO_CHANGE;
    dmaChConfig->destAddrInc  = DMA_ADDRESS_INC;
    dmaChConfig->srcTrWidth   = DMA_TR_WIDTH_0;/*according to IIC dataSize*/
    dmaChConfig->destTrWidth  = DMA_TR_WIDTH_0;  
    dmaChConfig->transferDir  = (I2Cx==I2C0)?DMA_I2C0_RX_TO_MEM:DMA_I2C1_RX_TO_MEM;
    dmaChConfig->blockCnt  = deviceCfg->len;
    dmaChConfig->interruptEn = DISABLE;
    dma_chan_init(dma_id,dmaChConfig);
    
    if ((deviceCfg->offsetSize == 0) && (len == deviceCfg->len)) 
    {
        tmp32 = i2c_get_ack(I2Cx);
        if (tmp32 == 1) 
        {
            timeout_ack++;
            if (timeout_ack > I2C_TIMEOUT_CNT) 
            {
                return 1;
            }
        }
    }
    if (deviceCfg->len<=IC_FIFO_DEPTH)
    {
        for(int i=0;i<deviceCfg->len-1;i++)
        {
            I2Cx->ic_cmd_data = IC_CMD; // CMD = Read
        }
        I2Cx->ic_cmd_data = IC_CMD | IC_STOP; // CMD = Read
    }
    dma_chan_start(dma_id, dmaChConfig->channel);
    
    #if 0
    while (len) 
    {
        if ((I2Cx->ic_status & IC_STATUS_TFNF) != 0) 
        {
            if (len == 1) 
            {
                I2Cx->ic_cmd_data = IC_CMD | IC_STOP; // CMD = Read
            } 
            else 
            {
                I2Cx->ic_cmd_data = IC_CMD; // CMD = Read
            }
            /* some read operation may not have offset */
            if ((deviceCfg->offsetSize == 0) && (len == deviceCfg->len)) 
            {
                tmp32 = i2c_get_ack(I2Cx);
                if (tmp32 == 1) 
                {
                    timeout_ack++;
                    if (timeout_ack > I2C_TIMEOUT_CNT) 
                    {
                        return 1;
                    }
                    continue;
                }
            }
            len--;
        }
    }
    #endif
    while(!dma_chan_check_done_poll(dma_id, dmaChConfig->channel))
    {
        timeout++;
        if (timeout > I2C_TIMEOUT_CNT) 
        {
            return 1;
        }    
    }
    
    dma_chan_close(dma_id, dmaChConfig->channel);
    return i2c_xfer_finish(I2Cx);
}

/**
* i2c_dma_master_write_poll
*
* @param[in]  I2Cx: pointer to I2C register structure
* @param[in]  deviceCfg: pointer to I2C device configuration structure
* @param[in]  dma_id: DMA channel ID
* @param[in]  dmaChConfig: pointer to DMA channel configuration structure
* @return 0 if successful, 1 otherwise
*
* @brief Perform I2C master write operation with DMA and polling
*/
uint32_t i2c_dma_master_write_poll(ZN_I2cType *I2Cx, I2C_DeviceType *deviceCfg, uint8_t dma_id, DMA_ChConfigType *dmaChConfig)
{
    uint32_t timeout = 0;
    uint32_t len = deviceCfg->len;
    uint8_t *buffer = deviceCfg->buffer;
    uint32_t tmp32 = 0;
    uint32_t rest_len = 1; 
    if (i2c_xfer_init(I2Cx,deviceCfg->devAddr,deviceCfg->offset,deviceCfg->offsetSize))
    {
        return 1;
    }
    
    /* DMA transfer len-1, and then do last transfer with STOP bit set*/
    if (len-1>0)
    {
        I2Cx->ic_dma_cr = IC_DMA_CR_TDMAE;
        I2Cx->ic_dma_tdlr = 1;
        /*DMA+I2C+TX channel config, MEM->TX FIFO*/
        dmaChConfig->srcAddr = (uint32_t)deviceCfg->buffer;
        dmaChConfig->destAddr  = (uint32_t)(&I2Cx->ic_cmd_data);
        dmaChConfig->srcMsize     = DMA_MSIZE_0; 
        dmaChConfig->destMsize    = DMA_MSIZE_0;
        dmaChConfig->srcAddrInc   = DMA_ADDRESS_INC;
        dmaChConfig->destAddrInc  = DMA_ADDRESS_NO_CHANGE;
        dmaChConfig->srcTrWidth   = DMA_TR_WIDTH_0;/*according to IIC dataSize*/
        dmaChConfig->destTrWidth  = DMA_TR_WIDTH_0;  
        dmaChConfig->transferDir  = (I2Cx==I2C0)?DMA_MEM_TO_I2C0_TX:DMA_MEM_TO_I2C1_TX;
        dmaChConfig->blockCnt  = len-1;
        dmaChConfig->interruptEn = DISABLE;    
        dma_chan_init(dma_id,dmaChConfig);
        dma_chan_start(dma_id, dmaChConfig->channel);
        while(!dma_chan_check_done_poll(dma_id, dmaChConfig->channel))
        {
            timeout++;
            if (timeout > I2C_TIMEOUT_CNT) 
            {
                I2Cx->ic_dma_cr = 0; // clear DMA bit
                I2Cx->ic_enable |= IC_ENABLE_ABORT; // abort
                return 1;
            }    
        }
        dma_chan_close(dma_id, dmaChConfig->channel);
    }
    
    timeout = 0;
    while(0 != rest_len)
    {
         if (I2Cx->ic_status & IC_STATUS_TFNF)
         {
            I2Cx->ic_cmd_data = buffer[len-1] | IC_STOP;
             rest_len--;
         }
         else if (timeout++>I2C_TIMEOUT_CNT)
         {
            return 1;
         }
    }
    return i2c_xfer_finish(I2Cx);
}







