/*****************************************************************************
* File: c_simple_tx.c
*
* Descirption: this file contains the functions support tx test.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#include <string.h>
#include "phy_cmd.h"
#include "hal_uwb.h"
#include "hal_delay.h"


static volatile uint8_t tx_done_flag = 0;

static uint8_t tx_msg[MAX_FRAME_LEN] = {0};
static uint32_t tx_count = 0;


static void tx_done_phy(const zn_cb_data_t *cb_data)
{
    tx_done_flag = 1;
}

static void quick_loop_tx(uint8_t tx_flag)
{
    if(tx_flag != PHY_TRANSFER_STOP)
    {
        tx_done_flag = 0;
        hal_uwb_immediate_tx();

        while(!tx_done_flag && (tx_flag != PHY_TRANSFER_STOP));
    }
}


void phy_simple_tx(void)
{
    uint16_t            delay_ms      = 0;
    uint16_t            psdu_len      = 0;
    uint32_t            packet_num    = 0;
    phy_cmd_t*          phy_cmd       = get_phy_cmd_addr();
    zn_driver_config_t* driver_config = zn_get_dirver_config_addr();
    
    if(phy_cmd->quick_loop_en && (phy_cmd->tx_flag != PHY_TRANSFER_STOP))
	{
		quick_loop_tx(phy_cmd->tx_flag);
		return;
	}
    
    driver_config->zn_interrupt_callback.cb_tx_done = &tx_done_phy;
    

    tx_msg[17] = tx_count & 0xff;
    tx_msg[16] = (tx_count >> 8) & 0xff;
    tx_msg[15] = (tx_count >> 16) & 0xff;
    tx_msg[14] = (tx_count >> 24) & 0xff;

    packet_num = ((uint32_t)tx_msg[14] << 24) | ((uint32_t)tx_msg[15] << 16) | 
                 ((uint32_t)tx_msg[16] << 8) | (uint32_t)tx_msg[17];
    
    if(phy_cmd->tx_flag != PHY_TRANSFER_STOP)
    {
        psdu_len = (phy_cmd->psdu_len > 0) ? phy_cmd->psdu_len : 20;
        hal_uwb_write_tx_buffer(tx_msg, psdu_len - 2);
        
        tx_done_flag = 0;
        hal_uwb_immediate_tx();
        #ifdef POWER_TEST
        uint32_t reg = sys_ctrl_read(UWB_CLK_ICG_REG);
        reg |= 0x00001000;
        sys_ctrl_write(UWB_CLK_ICG_REG, reg);
        __asm__("wfi");
        #endif
        if(phy_cmd->interrupt_en)
        {
            while(!tx_done_flag && (phy_cmd->tx_flag != PHY_TRANSFER_STOP));
        }
        else
        {
            while(!(hal_read_uwb_register(SYS_STATUS_ID) & UWB_TX_DONE_EVENT) && (phy_cmd->tx_flag != PHY_TRANSFER_STOP));
            hal_write_uwb_register(SYS_STATUS_ID, SYS_MASK_MASK);
        }
        
        
        if(PHY_TRANSFER_SIGNLE == phy_cmd->tx_flag)
        {
            phy_cmd->tx_flag = PHY_TRANSFER_STOP;
        }
        #ifndef POWER_TEST
        LOG_INFO("tx_cnt = %d, packetnum = %d", tx_count, packet_num);
        #endif
        tx_count++;
        
        delay_ms = (phy_cmd->tx_delay_ms > 0) ? phy_cmd->tx_delay_ms : 50;
        #ifndef POWER_TEST
        hal_delay_ms(delay_ms);
        #endif
    }
}
    