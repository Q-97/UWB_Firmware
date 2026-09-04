/*****************************************************************************
 *  File: dca.c
 *
 *  Descirption: this file contains the functions dca
 *
 *  Copyright (C) : 2022 ultraception.com
 *
 *  Author: WangJiying
 *  Mail:   
 *  Date:   2022-3-22
 *
 *****************************************************************************/

#include "zn_dca.h"

void dca_write(uint32_t addr, uint32_t data)
{
    uint32_t rdata;
    uint32_t reg0A0C = read_mreg32(UWB_BASE_ADDR + 0x0a0c); 
    uint32_t reg_uwb_icg = sys_ctrl_read(UWB_CLK_ICG_REG);
    
    write_mreg32(UWB_BASE_ADDR + 0x0a0c, 0x01);
    sys_ctrl_write(UWB_CLK_ICG_REG, reg_uwb_icg & ~(UWB_CLK_ICG_REG_UWB_ANA_REG_CLK_ICG_MASK | UWB_CLK_ICG_REG_UWB_HCLK_ICG_MASK));
    
    write_mreg32(UWB_BASE_ADDR+AON_DCA_CTRL,0x90|(data<<8)|(addr<<16));
    do
    {
        rdata = read_mreg32(UWB_BASE_ADDR+AON_DCA_CTRL);
    }while((rdata&0x08)==0x08);
    
    write_mreg32(UWB_BASE_ADDR + 0x0a0c, reg0A0C);
    sys_ctrl_write(UWB_CLK_ICG_REG, reg_uwb_icg);
}

uint32_t dca_read(uint32_t addr)
{
    uint32_t rdata;
    uint32_t reg0A0C = read_mreg32(UWB_BASE_ADDR + 0x0a0c); 
    uint32_t reg_uwb_icg = sys_ctrl_read(UWB_CLK_ICG_REG);
    
    write_mreg32(UWB_BASE_ADDR + 0x0a0c, 0x01);
    sys_ctrl_write(UWB_CLK_ICG_REG, reg_uwb_icg & ~(UWB_CLK_ICG_REG_UWB_ANA_REG_CLK_ICG_MASK | UWB_CLK_ICG_REG_UWB_HCLK_ICG_MASK));
    
    write_mreg32(UWB_BASE_ADDR+AON_DCA_CTRL,0x88|(addr<<16));
    
    do
    {
        rdata = read_mreg32(UWB_BASE_ADDR+AON_DCA_CTRL);
    }while((rdata&0x08)==0x08);
    
    rdata = read_mreg32(UWB_BASE_ADDR+AON_DCA_RDAT);
    write_mreg32(UWB_BASE_ADDR + 0x0a0c, reg0A0C);
    sys_ctrl_write(UWB_CLK_ICG_REG, reg_uwb_icg);
    
    return  rdata;  
}

void dca_set_bit(uint32_t addr, uint32_t n)
{
    uint32_t rdata = 0;;
    
    rdata = dca_read(addr);

    rdata |= (1<<n);
    
    dca_write(addr,rdata);
}

void dca_clear_bit(uint32_t addr, uint32_t n)
{
    uint32_t rdata = 0;;
    
    rdata = dca_read(addr);

    rdata &= ~(1<<n);
    
    dca_write(addr,rdata);
}