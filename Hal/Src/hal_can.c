/*****************************************************************************
 *  File: hal_can.c
 *
 * Descirption: this file contains the functions support can operations.
 *
 *  Copyright (C) : 2025 ultraception.com
 *
 *  Author: sxg
 *  Mail:   
 *  Date:   2025-5-12
 *
 *****************************************************************************/

#include "hal_can.h"
#include "zn_timer.h"
#include "zn_delay.h"

static void can_clock_set(uint8_t src, uint8_t div)
{
    uint32_t value = 0;
    
    value = (div << 4) | src;
    
    sys_ctrl_write(CAN_CLK_CFG, value);
}

ERROR_Type hal_can_init(hal_can_t *can_config)
{
    CAN_Config           config          = {0};
    CAN_BaudrateConfig   bandrate_config = {0};
    CAN_FDBaudrateConfig datarate_config = {0};
    
    if(NULL == can_config)
    {
        LOG_ERROR("null pointer");
        return ERROR;
    }

    /*
    tSeg1 = (S_SEG_1 + 2); tSeg2 = (S_SEG_2 + 1).
    BandRate  = (CAN_CLK / (S_PRESC + 1) / ((S_SEG_1 + 2) + (S_SEG_2 + 1)))
    SamplePoint = (tSeg1 / (tSeg1 + tSeg2)).
    */

    sys_clear_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_CAN_SW_PRSTN_SHIFT);  /*CAN_SW_PRSTN reset*/
    sys_set_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_CAN_SW_PRSTN_SHIFT);   /*CAN_SW_PRSTN set*/
    sys_clear_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_CAN_SW_RSTN_SHIFT); /*CAN_SW_RSTN reset*/
    sys_set_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_CAN_SW_RSTN_SHIFT);   /*CAN_SW_RSTN set*/    
    sys_clear_bit(CLK_ICG_REG,CLK_ICG_REG_CAN_PCLK_ICG_SHIFT);
    sys_clear_bit(CLK_ICG_REG,CLK_ICG_REG_CAN_CLK_ICG_SHIFT);
    
    NVIC_SetPriority(CAN_IRQn, 10);
    
    /*gpio->can*/
//    pad_reg_write(CAN_TXD_PREG,0x178);
//    pad_reg_write(CAN_STBY_PREG,0x178);
    pad_reg_write(GPIO_3_PREG,0x178);
    pad_reg_write(GPIO_4_PREG,0x178);
    pad_reg_write(CAN_RXD_PREG,0x178);
    
    sys_clear_bit(UWB_CLK_ICG_REG , UWB_CLK_ICG_REG_UWB_HCLK_ICG_SHIFT);
    write_mreg32(UWB_BASE_ADDR+0x1064, read_mreg32(UWB_BASE_ADDR+0x1064)|0x00022820);
    cpu_delay(200);
    
    if(!(read_mreg32(UWB_BASE_ADDR+0x107c)&(0x1<<10)))
    {
        printf("can switch to clk failed!\r\n");
    }
    
    can_clock_set(can_config->config.clock_src, can_config->config.clock_div);
    
    bandrate_config.S_PRESC = can_config->baudrate_config.presc;
    bandrate_config.S_SEG_1 = can_config->baudrate_config.seg_1;
    bandrate_config.S_SEG_2 = can_config->baudrate_config.seg_2;
    bandrate_config.S_SJW = can_config->baudrate_config.sjw;
    
    datarate_config.F_PRESC = can_config->datarate_config.presc;
    datarate_config.F_SEG_1 = can_config->datarate_config.seg_1;
    datarate_config.F_SEG_2 = can_config->datarate_config.seg_2;
    datarate_config.F_SJW = can_config->datarate_config.sjw;
    
    config.canMode = can_config->config.can_mode;
    config.interruptEnable = can_config->config.interrupt_en;
    config.autoReset = can_config->config.auto_reset;
    config.TPSS = can_config->config.tpss;
    config.TSSS = can_config->config.tsss;
    config.TSMODE = can_config->config.ts_mode;
    config.ROM = can_config->config.rom;
    config.TIMEEN = can_config->config.time_en;
    config.TIMEPOS = can_config->config.time_pos;
    config.fdModeEn = can_config->config.fd_mode_en;
    config.fdIsoEn = can_config->config.fd_iso_en;
    config.tdcEnable = can_config->config.tdc_en;
    config.sspOffset = can_config->config.ssp_offset;
    config.filterEn = can_config->config.filter_en;
    config.filter_num = (can_config->config.filter_num > MAX_CAN_FILTER_NUM) ? MAX_CAN_FILTER_NUM : can_config->config.filter_num;
    config.filterList = (CAN_FilterControl*)can_config->config.filter_list;
    config.callbackFunc = can_config->config.func;
    
    if(config.fdModeEn)
    {
        canfd_init(CAN0, &config, &bandrate_config, &datarate_config);
    }
    else
    {
        can_init(CAN0, &config, &bandrate_config);
    }
    
    return SUCCESS;
}

void hal_can_deinit(void)
{
    can_reset(CAN0, 1);
    
    sys_clear_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_CAN_SW_PRSTN_SHIFT);  /*CAN_SW_PRSTN reset*/
    sys_set_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_CAN_SW_PRSTN_SHIFT);   /*CAN_SW_PRSTN set*/
    sys_clear_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_CAN_SW_RSTN_SHIFT); /*CAN_SW_RSTN reset*/
    sys_set_bit(BLK_SW_RSTN0,BLK_SW_RSTN0_CAN_SW_RSTN_SHIFT);   /*CAN_SW_RSTN set*/   
    
    sys_set_bit(CLK_ICG_REG,CLK_ICG_REG_CAN_PCLK_ICG_SHIFT);
    sys_set_bit(CLK_ICG_REG,CLK_ICG_REG_CAN_CLK_ICG_SHIFT);
    sys_set_bit(UWB_CLK_ICG_REG , UWB_CLK_ICG_REG_UWB_HCLK_ICG_SHIFT);
    sys_ctrl_write(CAN_CLK_CFG, 1);
}

ERROR_Type hal_can_msg_send(hal_can_msg_info_t* msg_info, uint8_t type)
{
    int32_t ret = 0;
    CAN_MSG_INFO info = {0};
    
    info.ID = msg_info->can_id;
    info.ESI = msg_info->esi;
    info.DLC = msg_info->dlc;
    info.BRS = msg_info->brs;
    info.FDF = msg_info->fdf;
    info.RTR = msg_info->rtr;
    info.IDE = msg_info->ide;
    memcpy(info.Data, msg_info->data, MAX_CAN_BUFFER_LEN * sizeof(info.Data[0]));
    info.RTS[0] = msg_info->rts[0];
    info.RTS[1] = msg_info->rts[1];    
    
    ret = can_msg_send(CAN0, &info, type);
    
    if(0 == ret)
    {
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

ERROR_Type hal_can_msg_read(hal_can_msg_info_t *msg_info)
{
    uint8_t ret = 0;
    CAN_MSG_INFO info = {0};
    
    ret = can_msg_read(CAN0, &info);
    
    if(0 == ret)
    {
        msg_info->can_id = info.ID;
        msg_info->esi = info.ESI;
        msg_info->brs = info.BRS;
        msg_info->fdf = info.FDF;
        msg_info->rtr = info.RTR;
        msg_info->ide = info.IDE;
        msg_info->dlc = info.DLC;
        
        memcpy(msg_info->data, info.Data, MAX_CAN_BUFFER_LEN * sizeof(info.Data[0]));
        
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
    
}

uint8_t hal_can_wait_transmission_idle(uint8_t type)
{
    uint8_t ret = 0;
    
    ret = can_wait_transmission_idle(CAN0, type);
    
    return ret;
}

uint8_t hal_can_get_payload_size(uint8_t dlc)
{
    return can_get_payload_size(dlc);
}

uint8_t hal_can_is_transmit_busy(uint8_t type)
{
    return can_is_transmit_busy(CAN0, type);
}

uint8_t hal_can_is_transmit_idle(uint8_t type)
{
    return can_is_transmit_idle(CAN0, type);
}

uint8_t hal_can_fd_dlc_to_len(uint8_t dlc)
{
    return can_fd_dlc2len(dlc);
}

uint8_t hal_can_fd_len_to_dlc(uint8_t len)
{
    return can_fd_len2dlc(len);
}

void hal_can_reset(uint8_t reset)
{
    can_reset(CAN0, reset);
}

uint8_t hal_can_is_msg_in_rxbuff(void)
{
    return can_is_msg_in_rxbuff(CAN0);
}

void hal_can_set_int_enalbe(uint8_t int_en, uint8_t err_int_en)
{
    can_set_int_enable(CAN0, int_en, err_int_en);
}

void hal_can_set_ewl(uint8_t ewl)
{
    can_set_ewl(CAN0, ewl);
}

uint32_t hal_can_get_tts0(void)
{
    return can_get_tts0(CAN0);
}

uint32_t hal_can_get_tts1(void)
{
    return can_get_tts1(CAN0);
}
    