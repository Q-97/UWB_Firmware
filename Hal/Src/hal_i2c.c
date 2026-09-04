/*****************************************************************************
 *  File: hal_i2c_timer.c
 *
 * Descirption: this file contains the functions support i2c operations.
 *
 *  Copyright (C) : 2025 ultraception.com
 *
 *  Author: sxg
 *  Mail:   
 *  Date:   2025-5-12
 *
 *****************************************************************************/

#include "hal_i2c.h"


ERROR_Type hal_i2c_init(hal_i2c_t *i2c_config)
{
    uint32_t       gp_sel = 0;
    I2C_ConfigType config = {0};
    ZN_I2cType*    i2cx   = I2C_BASE(i2c_config->i2c_id);
    
    if(NULL == i2c_config)
    {
        LOG_ERROR("null pointer");
        return ERROR;
    }

    config.master          = i2c_config->i2c_role;
    config.txFifoTrigLevel = i2c_config->tx_fifo_trigger_level;
    config.rxFifoTrigLevel = i2c_config->rx_fifo_trigger_level;
    config.interruptEn     = i2c_config->interrupt_en;
    config.interruptType   = i2c_config->interrupt_mask;
    config.irq             = i2c_config->i2c_id ? I2C1_IRQn : I2C0_IRQn;
    config.clk             = 38400000;
    config.speed           = i2c_config->i2c_speed;
    config.callBack        = i2c_config->func;
    config.slaver_addr     = i2c_config->slaver_addr;
    
    sys_set_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_I2C_SW_PRSTN_SHIFT);   /*i2c_SW_PRSTN set*/
    sys_clear_bit(CLK_ICG_REG,CLK_ICG_REG_I2C_PCLK_ICG_SHIFT);   /*i2c PCLK normal*/
    if(1 == i2c_config->i2c_id)
    {
        sys_clear_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_I2C1_SW_RSTN_SHIFT);   /*i2c_SW_RSTN set*/
        sys_set_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_I2C1_SW_RSTN_SHIFT);   /*i2c_SW_RSTN set*/
        sys_clear_bit(CLK_ICG_REG,CLK_ICG_REG_I2C1_CLK_ICG_MASK);    /*i2c CLK normal*/
        gp_sel = ((i2c_config->i2c_group_sel << SEL_GROUP_SELGP_I2C1_SCL_SHIFT) & SEL_GROUP_SELGP_I2C1_SCL_MASK) | ((i2c_config->i2c_group_sel << SEL_GROUP_SELGP_I2C1_SDA_SHIFT) & SEL_GROUP_SELGP_I2C1_SDA_MASK);
        gp_sel |= pad_reg_read(SEL_GROUP);
        pad_reg_write(SEL_GROUP, gp_sel);

        if(0 == i2c_config->i2c_group_sel)
        {
            pad_reg_write(SWDIO_PREG, 0x17b);
            pad_reg_write(SWCLK_PREG, 0x17b);
        }
        else
        {
            pad_reg_write(SPI0_CLK_PREG, 0x17b);
            pad_reg_write(SPI0_MISO_PREG, 0x17b);
        }
    }
    else
    {
        sys_clear_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_I2C_SW_RSTN_SHIFT);   /*i2c_SW_RSTN set*/
        sys_set_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_I2C_SW_RSTN_SHIFT);   /*i2c_SW_RSTN set*/
        sys_clear_bit(CLK_ICG_REG,CLK_ICG_REG_I2C_CLK_ICG_SHIFT);    /*i2c CLK normal*/
        pad_reg_write(I2C0_SCL_PREG, 0x178);
        pad_reg_write(I2C0_SDA_PREG, 0x178);
    }

    i2c_init(i2cx, &config);
    
    return SUCCESS;
}

ERROR_Type hal_i2c_write_poll(hal_i2c_info_t* i2c_info)
{
    I2C_DeviceType device_cfg = {0};
    ZN_I2cType*    i2cx       = I2C_BASE(i2c_info->i2c_id);
    
    device_cfg.devAddr    = i2c_info->dev_addr;
    device_cfg.offset     = i2c_info->offset;
    device_cfg.offsetSize = i2c_info->offset_size;
    device_cfg.buffer     = i2c_info->buffer;
    device_cfg.len        = i2c_info->len;
    
    if(0 == i2c_master_write_poll(i2cx, &device_cfg))
    {
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}


ERROR_Type hal_i2c_read_poll(hal_i2c_info_t* i2c_info)
{
    I2C_DeviceType device_cfg = {0};
    ZN_I2cType*    i2cx       = I2C_BASE(i2c_info->i2c_id);
    
    device_cfg.devAddr    = i2c_info->dev_addr;
    device_cfg.offset     = i2c_info->offset;
    device_cfg.offsetSize = i2c_info->offset_size;
    device_cfg.buffer     = i2c_info->buffer;
    device_cfg.len        = i2c_info->len;
    
    if(0 == i2c_master_read_poll(i2cx, &device_cfg))
    {
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

void hal_i2c_write_byte(uint8_t i2c_id, uint8_t data)
{
    ZN_I2cType* i2cx = I2C_BASE(i2c_id);
    
    i2cx->ic_cmd_data = data;
}

uint8_t hal_i2c_read_byte(uint8_t i2c_id)
{
    ZN_I2cType* i2cx = I2C_BASE(i2c_id);
    
    return i2cx->ic_cmd_data & 0xff;
}


uint32_t hal_i2c_get_interrupt_state(uint8_t i2c_id)
{
    ZN_I2cType* i2cx = I2C_BASE(i2c_id);
    
    return i2cx->ic_intr_stat;
}

void hal_i2c_clear_interrrupt_state(uint8_t i2c_id, uint32_t event)
{
    uint32_t    status = 0;
    ZN_I2cType* i2cx   = I2C_BASE(i2c_id);
    
    switch(event)
    {
        case IC_RX_UNDER : status = i2cx->ic_clr_rx_under; break;
        case IC_RX_OVER  : status = i2cx->ic_clr_rx_over;  break;
        case IC_TX_OVER  : status = i2cx->ic_clr_tx_over;  break;
        case IC_RD_REQ   : status = i2cx->ic_clr_rd_req;   break;
        case IC_TX_ABRT  : status = i2cx->ic_clr_tx_abrt;  break;
        case IC_RX_DONE  : status = i2cx->ic_clr_rx_done;  break;
        case IC_ACTIVITY : status = i2cx->ic_clr_activity; break;
        case IC_STOP_DET : status = i2cx->ic_clr_stop_det; break;
        case IC_START_DET: status = i2cx->ic_clr_start_det;break;
        case IC_GEN_CALL : status = i2cx->ic_clr_gen_call; break;
        default: status = i2cx->ic_clr_intr; break;
    }
}

