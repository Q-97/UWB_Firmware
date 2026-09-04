/*****************************************************************************
* File: zntest.c
*
* Descirption: this file contains the functions support phy test.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#include <string.h>
#include "phy_test.h"
#include "stdio.h"
#include "string.h"
#include "phy_cfg_test.h"
#include "phy_cmd.h"
#include "hal_delay.h"
#include "hal_sleep.h"
#include "hal_gpio.h"
#include "hal_gp_timer.h"

extern void phy_simple_tx(void);
extern void phy_simple_rx(void);

static void user_msg_to_idle_state(uint8_t* msg, uint8_t len);
static void user_msg_auto_sleep(uint8_t* msg, uint8_t len);
static void user_msg_deep_sleep(uint8_t* msg, uint8_t len);
static void user_msg_contiuous_pulse_switch(uint8_t* msg, uint8_t len);
static void user_msg_sine_wave_switch(uint8_t* msg, uint8_t len);
static void user_msg_read_adc_mem(uint8_t* msg, uint8_t len);
static void user_msg_read_sfd_cir_mem_switch(uint8_t* msg, uint8_t len);
static void user_msg_read_sts_cir_mem_switch(uint8_t* msg, uint8_t len);
static void user_msg_psdu_lenght_set(uint8_t* msg, uint8_t len);
static void user_msg_tia_calc(uint8_t* msg, uint8_t len);
static void user_msg_calib(uint8_t* msg, uint8_t len);
static void user_msg_vga_cal_rx0_one_time(uint8_t* msg, uint8_t len);
static void user_msg_vga_cal_rx1_one_time(uint8_t* msg, uint8_t len);
static void user_msg_vga_cal_rx0_auto(uint8_t* msg, uint8_t len);
static void user_msg_vga_cal_rx1_auto(uint8_t* msg, uint8_t len);
static void user_msg_agc_mem_switch(uint8_t* msg, uint8_t len);
static void user_msg_agc_mem_read(uint8_t* msg, uint8_t len);
static void user_msg_log_level_set(uint8_t* msg, uint8_t len);
static void user_msg_software_reset(uint8_t* msg, uint8_t len);
static void user_msg_psdu_print_switch(uint8_t* msg, uint8_t len);
static void user_msg_quick_loop_switch(uint8_t* msg, uint8_t len);
static void user_msg_rx_timeout_set(uint8_t* msg, uint8_t len);
static void user_msg_tx_delay_set(uint8_t* msg, uint8_t len);
static void user_msg_power_save_switch(uint8_t* msg, uint8_t len);
static void user_msg_radar_timer_switch(uint8_t* msg, uint8_t len);

static user_msg_state_table_t user_msg_state_table[USER_MSG_TYPE_MAX] =
{
    {USER_MSG_TYPE_TO_IDLE_STATE, user_msg_to_idle_state},
    {USER_MSG_TYPE_AUTO_SLEEP, user_msg_auto_sleep},
    {USER_MSG_TYPE_DEEP_SLEEP, user_msg_deep_sleep},
    {USER_MSG_TYPE_CONTINUOUS_PULSE_SWITCH, user_msg_contiuous_pulse_switch},
    {USER_MSG_TYPE_SINE_WAVE_SWITCH, user_msg_sine_wave_switch},
    {USER_MSG_TYPE_READ_ADC_MEM, user_msg_read_adc_mem},
    {USER_MSG_TYPE_READ_SFD_CIR_MEM_SWITCH, user_msg_read_sfd_cir_mem_switch},
    {USER_MSG_TYPE_READ_STS_CIR_MEM_SWITCH, user_msg_read_sts_cir_mem_switch},
    {USER_MSG_TYPE_PSDU_LENGTH_SET, user_msg_psdu_lenght_set},
    {USER_MSG_TYPE_CALIB, user_msg_calib},
    {USER_MSG_TYPE_VGA_RX0_ONETIME_CALC,  },
    {USER_MSG_TYPE_VGA_RX1_ONETIME_CALC,  },
    {USER_MSG_TYPE_VGA_RX0_AUTO_CALC,  },
    {USER_MSG_TYPE_VGA_RX1_AUTO_CALC,  },
    {USER_MSG_TYPE_AGC_MEM_SWITCH, user_msg_agc_mem_switch},
    {USER_MSG_TYPE_AGC_MEM_READ, user_msg_agc_mem_read},
    {USER_MSG_TYPE_VGA_LOG_LEVEL_SET, user_msg_log_level_set},
    {USER_MSG_TYPE_SOFTWARE_RESET, user_msg_software_reset},
    {USER_MSG_TYPE_PSDU_PRINT_SWITCH, user_msg_psdu_print_switch},
    {USER_MSG_TYPE_QUICK_LOOP_SWITCH, user_msg_quick_loop_switch},
    {USER_MSG_TYPE_RX_TIMEOUT_SET, user_msg_rx_timeout_set},
    {USER_MSG_TYPE_TX_DELAY_SET, user_msg_tx_delay_set},
    {USER_MSG_TYPE_POWER_SAVE_SWITCH, user_msg_power_save_switch},
    {USER_MSG_TYPE_RADAR_TIMER_SWITCH, user_msg_radar_timer_switch},
};

    

static void user_msg_to_idle_state(uint8_t* msg, uint8_t len)
{
    hal_uwb_to_idle_state();
}

static void user_msg_auto_sleep(uint8_t* msg, uint8_t len)
{
    hal_sleep_t sleep_cfg = {0};
    
    sleep_cfg.clk_sel = msg[0];
    sleep_cfg.time_us = 5000000;
    sleep_cfg.sleep_type = AUTO_SLEEP;
    
    hal_sleep_go_sleep(&sleep_cfg);
}

static void user_msg_deep_sleep(uint8_t* msg, uint8_t len)
{
    hal_sleep_t sleep_cfg = {0};
   
    sleep_cfg.wakeup_cofig.wakeup_src.bits.can_rxd  = 1;
    sleep_cfg.wakeup_cofig.wakeup_src.bits.spi0_csn = 1;
    sleep_cfg.wakeup_cofig.wakeup_src.bits.spi1_csn = 1;
    sleep_cfg.sleep_type = DEEP_SLEEP;
    hal_sleep_go_sleep(&sleep_cfg);
}

static void user_msg_contiuous_pulse_switch(uint8_t* msg, uint8_t len)
{
    uint8_t             fem_ctrl_mode = 0;
    uint16_t            idx           = 0;
    uint32_t            rand_value    = 0;
    zn_driver_config_t* driver_config = zn_get_dirver_config_addr();
    
    fem_ctrl_mode = driver_config->phy_config.fem_ctrl_mode;
 
    hal_write_uwb_register(0x1844, 0x1c000000);
    
    if(msg[0])
    {
        if(driver_config->phy_config.fem_en)
        {
            if(!driver_config->phy_config.fem_ctrl_mode)
            {
                hal_gpio_set_output_default_config(driver_config->phy_config.fem_tx_pin);
                hal_gpio_set_value(driver_config->phy_config.fem_tx_pin, 1);
            }
        }
        hal_uwb_to_tx_state();
        
        for(idx = 0; idx < 1024; idx++)
        {
            rand_value += 0x12345678;
            hal_write_uwb_register((0xa000 + (idx * 4)), rand_value);
        }
        hal_write_uwb_register(0x1844, 0x1c020000);
        hal_write_uwb_register(0x1844, 0x1c060000);
        
        LOG_INFO("tx contiunous pulse on");
    }
    else
    {
        if(driver_config->phy_config.fem_en)
        {
            if(!driver_config->phy_config.fem_ctrl_mode)
            {
                hal_gpio_set_tx_en_mode(driver_config->phy_config.fem_tx_pin);
            }
        }
        
        hal_uwb_to_idle_state();
        hal_write_uwb_register(0x1844, 0x1c000000);
        LOG_INFO("tx contiunous pulse off");
    }
}

static void user_msg_sine_wave_switch(uint8_t* msg, uint8_t len)
{
    if(1 == msg[0])
    {
        NVIC_DisableIRQ(UWB_IRQn);
        hal_uwb_to_tx_state();
        zn_start_send_cw();
        LOG_INFO("tx sine wave on");
    }
    else
    {
        zn_stop_send_cw();
        hal_uwb_to_idle_state();
        NVIC_EnableIRQ(UWB_IRQn);
        LOG_INFO("tx sine wave off");
    }
}

static void user_msg_read_adc_mem(uint8_t* msg, uint8_t len)
{
    uint8_t mem_sel   = 0;
    uint8_t read_time = 0;
    
    mem_sel   = msg[0];
    read_time = (msg[1] > 0) ? msg[1] : 1;
    
    while(read_time--)
    {
        hal_uwb_read_adc_mem(mem_sel);
    }
}

static void user_msg_read_sfd_cir_mem_switch(uint8_t* msg, uint8_t len)
{
    phy_cmd_t* phy_cmd = get_phy_cmd_addr();
    
    phy_cmd->sfd_cir_mem_en = msg[0];
}

static void user_msg_read_sts_cir_mem_switch(uint8_t* msg, uint8_t len)
{
    phy_cmd_t* phy_cmd = get_phy_cmd_addr();
    
    phy_cmd->sts_cir_mem_en = msg[0];
}

static void user_msg_psdu_lenght_set(uint8_t* msg, uint8_t len)
{
    uint16_t  psdu_len = 0;
    phy_cmd_t* phy_cmd = get_phy_cmd_addr();
    
    psdu_len = ((uint16_t)msg[0] << 8) | msg[1];
    phy_cmd->psdu_len = psdu_len;
}

static void user_msg_tia_calc(uint8_t* msg, uint8_t len)
{
    hal_uwb_tia_calc();
}

static void user_msg_calib(uint8_t* msg, uint8_t len)
{
    hal_uwb_to_rx_state();
    if(msg[0] == 0x00){
        hal_32k_calib();
    }
    else if (msg[0] == 0x01){
        hal_tia_calib();
    }
    else if (msg[0] == 0x02){
        hal_vga_calib();
    }
    else if (msg[0] == 0x03){
        hal_calib_word_map_check();
    }
    else if (msg[0] == 0x04){
        hal_calib_reg_wr_rd_test();
    }
    else if (msg[0] == 0x05){
        hal_read_ana_reg_cfg();
    }
    else if (msg[0] == 0x06){
        hal_read_rx0_lna_tia_vga();
    }
    else if (msg[0] == 0x07){
        hal_read_rx1_lna_tia_vga();
    }
    else if (msg[0] == 0x08){
        hal_get_rx0_dc();
    }
    else if (msg[0] == 0x09){
        hal_get_rx1_dc();
    }
    else if (msg[0] == 0x0a){
        hal_scan_dc();
    }
    else if (msg[0] == 0x0b){
        uint32_t lna_case = msg[1];
        uint32_t tia_case = msg[2];
        uint32_t vga_case = msg[3];
        printf("lna: %x, tia: %x, vga: %x \n",lna_case,tia_case,vga_case);   
        hal_fixed_ana_gain_cfg_rx0(lna_case,tia_case,vga_case);
        printf("Fixed_ana_gain_cfg_rx0 done \n");
    }
    else if (msg[0] == 0x0c){
        uint32_t lna_case = msg[1];
        uint32_t tia_case = msg[2];
        uint32_t vga_case = msg[3];
        printf("lna: %x, tia: %x, vga: %x \n",lna_case,tia_case,vga_case);   
        hal_fixed_ana_gain_cfg_rx1(lna_case,tia_case,vga_case);
        printf("Fixed_ana_gain_cfg_rx1 done \n");
    }
    else if (msg[0] == 0x0d){
        hal_cfg_after_calib();
        uint32_t lna_case = msg[1];
        uint32_t tia_case = msg[2];
        uint32_t vga_case = msg[3];
        printf("lna: %x, tia: %x, vga: %x \n",lna_case,tia_case,vga_case);   
        hal_fixed_gain_cfg_rx0(lna_case,tia_case,vga_case);
        printf("Fixed_gain_cfg_rx0 done \n");
    }
    else if (msg[0] == 0x0e){
        hal_cfg_after_calib();
        uint32_t lna_case = msg[1];
        uint32_t tia_case = msg[2];
        uint32_t vga_case = msg[3];
        printf("lna: %x, tia: %x, vga: %x \n",lna_case,tia_case,vga_case);   
        hal_fixed_gain_cfg_rx1(lna_case,tia_case,vga_case);
        printf("Fixed_gain_cfg_rx1 done \n");
    }
    else if (msg[0] == 0x0f){
        hal_cfg_after_calib();
        uint32_t lna_case = msg[1];
        uint32_t tia_case = msg[2];
        uint32_t vga_case = msg[3];
        printf("lna: %x, tia: %x, vga: %x \n",lna_case,tia_case,vga_case);   
        hal_fix_gain_calib_rx0(lna_case,tia_case,vga_case);
        printf("Fix_gain_calib_rx0 done \n");
    }
    else if (msg[0] == 0x10){
        hal_cfg_after_calib();
        uint32_t lna_case = msg[1];
        uint32_t tia_case = msg[2];
        uint32_t vga_case = msg[3];
        printf("lna: %x, tia: %x, vga: %x \n",lna_case,tia_case,vga_case);   
        hal_fix_gain_calib_rx1(lna_case,tia_case,vga_case);
        printf("Fix_gain_calib_rx1 done \n");
    }
    else if (msg[0] == 0x11){
        hal_cfg_after_calib();
        uint32_t lna_case = msg[1];
        uint32_t tia_case = msg[2];
        uint32_t vga_case = msg[3];
        printf("lna: %x, tia: %x, vga: %x \n",lna_case,tia_case,vga_case);   
        hal_vga_recalib_once_rx0(lna_case,tia_case,vga_case);
        printf("vga_recalib_once_rx0 done \n");
    }
    else if (msg[0] == 0x12){
        hal_cfg_after_calib();
        uint32_t lna_case = msg[1];
        uint32_t tia_case = msg[2];
        uint32_t vga_case = msg[3];
        printf("lna: %x, tia: %x, vga: %x \n",lna_case,tia_case,vga_case);   
        hal_vga_recalib_once_rx1(lna_case,tia_case,vga_case);
        printf("vga_recalib_once_rx1 done \n");
    }
    else if (msg[0] == 0x13){
        hal_clkpll_calib();
    }
    else if (msg[0] == 0x14){
        hal_rfpll_calib();
    }
    
}

static void user_msg_vga_cal_rx0_one_time(uint8_t* msg, uint8_t len)
{
    hal_uwb_agc_one_time_clac_rx0();
}

static void user_msg_vga_cal_rx1_one_time(uint8_t* msg, uint8_t len)
{
    hal_uwb_agc_one_time_clac_rx1();
}

static void user_msg_vga_cal_rx0_auto(uint8_t* msg, uint8_t len)
{
    hal_uwb_agc_auto_clac_rx0(); 
}

static void user_msg_vga_cal_rx1_auto(uint8_t* msg, uint8_t len)
{
    hal_uwb_agc_auto_clac_rx1();
}

static void user_msg_agc_mem_switch(uint8_t* msg, uint8_t len)
{
    phy_cmd_t* phy_cmd = get_phy_cmd_addr();
    
    
    if(msg[0])
    {
        phy_cmd->agc_mem_en = 1;
        LOG_INFO("agc mem enable");
    }
    else
    {    
        phy_cmd->agc_mem_en = 0;
        LOG_INFO("agc mem disable");
    }
}

static void user_msg_agc_mem_read(uint8_t* msg, uint8_t len)
{
    hal_uwb_agc_gain_mem_read();
}

static void user_msg_log_level_set(uint8_t* msg, uint8_t len)
{
    int8_t level = (int8_t)msg[0] - 3;
    
    g_log_level = level;
    
    LOG_INFO("log level is %d",g_log_level);
}

static void user_msg_software_reset(uint8_t* msg, uint8_t len)
{
    LOG_INFO("software reset");
    NVIC_SystemReset();
}

static void user_msg_psdu_print_switch(uint8_t* msg, uint8_t len)
{
    phy_cmd_t* phy_cmd = get_phy_cmd_addr();
    
    phy_cmd->psdu_print_en = msg[0];
}

static void user_msg_quick_loop_switch(uint8_t* msg, uint8_t len)
{
    phy_cmd_t* phy_cmd = get_phy_cmd_addr();
    
    phy_cmd->quick_loop_en = msg[0];
}

static void user_msg_rx_timeout_set(uint8_t* msg, uint8_t len)
{
    uint16_t time = 0;
    phy_cmd_t* phy_cmd = get_phy_cmd_addr();
    
    time = ((uint16_t)msg[0] << 8) | msg[1];
    phy_cmd->rx_timeout_ms = time;
    
}

static void user_msg_tx_delay_set(uint8_t* msg, uint8_t len)
{
    uint16_t time = 0;
    phy_cmd_t* phy_cmd = get_phy_cmd_addr();
    
    time = ((uint16_t)msg[0] << 8) | msg[1];
    phy_cmd->tx_delay_ms = time;
}

static void user_msg_power_save_switch(uint8_t* msg, uint8_t len)
{
    zn_driver_config_t* driver_config = zn_get_dirver_config_addr();
    
    driver_config->paver_save_flag = msg[0];
    LOG_INFO("paver_save_flag=%d\n",msg[0]);
}

void phy_test_debug_switch(uint8_t *msg_payload, uint8_t msg_len)
{
    phy_cmd_t*          phy_cmd          = get_phy_cmd_addr();
    zn_driver_config_t* driver_config    = zn_get_dirver_config_addr();
    
    if(msg_len != 1)
    {
        LOG_ERROR("msg len %d error", msg_len);
        return;
    }
    
    if(0 == msg_payload[0])
    {
        phy_cmd->phy_debug_flag = WORK_MODE_NORMAL;
        if(phy_cmd->interrupt_en)
        {
            phy_cmd->interrupt_en = 0;
            memcpy(&driver_config->zn_interrupt_callback, &phy_cmd->loacal_data_back, sizeof(zn_local_data_t));
        }
        LOG_INFO("phy debug mode off");
    }
    else
    {
        phy_cmd->phy_debug_flag = WORK_MODE_PHY_DEBUG;
        if(driver_config->zn_interrupt_callback.cb_rx_ok != NULL)
        {
            phy_cmd->interrupt_en = 1;
            memcpy(&phy_cmd->loacal_data_back, &driver_config->zn_interrupt_callback, sizeof(zn_local_data_t));
        }
        phy_cmd->rx_timeout_ms = 400;
        hal_force_uwb_off();
        LOG_INFO("phy debug mode on");
    }
    
}

void phy_test_register_operation(uint8_t *msg_payload, uint8_t msg_len)
{
    uint16_t addr = 0;
    uint32_t val  = 0;
    
    if(msg_len != 7)
    {
        LOG_ERROR("msg len %d error", msg_len);
    }
    
    if(msg_payload[0])
    {
        addr = ((uint16_t)msg_payload[1] << 8) + msg_payload[2];
        val  = ((uint32_t)msg_payload[3] << 24) + ((uint32_t)msg_payload[4] << 16) + ((uint32_t)msg_payload[5] << 8) + msg_payload[6];
        hal_write_uwb_register(addr, val);
        
        LOG_INFO("write: addr = 0x%02x, val = 0x%08x", addr, val);
    }
    else
    {
        addr = ((uint16_t)msg_payload[1] << 8) + msg_payload[2];
        val  = hal_read_uwb_register(addr);
        
        LOG_INFO("read: addr = 0x%02x, val = 0x%08x", addr, val);
    }
}

void phy_test_transfer_operation(uint8_t *msg_payload, uint8_t msg_len)
{
    phy_cmd_t* phy_cmd = get_phy_cmd_addr();
    
    if(msg_len != 2)
    {
        LOG_ERROR("msg len %d error", msg_len);
    }
    
    if(0 == msg_payload[0])
    {
        phy_cmd->tx_flag = msg_payload[1];
    }
    else
    {
        phy_cmd->rx_flag = msg_payload[1];
        phy_cmd->ok_count = 0;
        phy_cmd->packet_count = 0;
    }
}

void phy_test_user_defined_operation(uint8_t *msg_payload, uint8_t msg_len)
{
    msg_type_user_defined_e msg_type     = USER_MSG_TYPE_NULL;
    uint8_t*                buffer       = NULL;
    uint8_t                 user_msg_len = 0;
    
    if(msg_len != 3)
    {
        LOG_ERROR("msg len %d error", msg_len);
    }
    
    msg_type = msg_payload[0];
    buffer = &msg_payload[1];
    user_msg_len = 2;
    
    for(uint8_t index = 0; index < USER_MSG_TYPE_MAX; index++)
    {
        if(msg_type == user_msg_state_table[index].user_msg_type)
        {
            user_msg_state_table[index].user_msg_handler(buffer, user_msg_len);
            break;
        }
    }
}

void phy_test_aon_register_operation(uint8_t *msg_payload, uint8_t msg_len)
{
    uint16_t addr = 0;
    uint32_t val  = 0;
    
    if(msg_len != 6)
    {
        LOG_ERROR("msg len %d error", msg_len);
    }
    
    if(msg_payload[0])
    {
        addr = ((uint16_t)msg_payload[1] << 8) + msg_payload[2];
        val  = ((uint32_t)msg_payload[3]);
        dca_write(addr,val);
        LOG_INFO("write aon reg addr = 0x%04X, val = 0x%02X", addr, val);
    }
    else
    {
        addr = ((uint16_t)msg_payload[1] << 8) + msg_payload[2];
        val  = dca_read(addr);
        
        LOG_INFO("read  aon reg addr = 0x%04X, val = 0x%02X", addr, val);
    }
}

void phy_test_full_register_operation(uint8_t *msg_payload, uint8_t msg_len)
{
    uint32_t addr = 0;
    uint32_t val  = 0;
    
    if(msg_len != 0x0b)
    {
        LOG_ERROR("msg len %d error", msg_len);
    }
    
    if(msg_payload[0])
    {
        addr = ((uint32_t)msg_payload[1] << 24) + ((uint32_t)msg_payload[2] << 16) + ((uint32_t)msg_payload[3] << 8)  + ((uint32_t)msg_payload[4]);
        val  = ((uint32_t)msg_payload[5] << 24) + ((uint32_t)msg_payload[6] << 16) + ((uint32_t)msg_payload[7] << 8)  + ((uint32_t)msg_payload[8]) ;
        write_mreg32(addr,val);
        LOG_INFO("write reg addr = 0x%08X, val = 0x%08X", addr, val);
    }
    else
    {
        addr = ((uint32_t)msg_payload[1] << 24) + ((uint32_t)msg_payload[2] << 16) + ((uint32_t)msg_payload[3] << 8)  + ((uint32_t)msg_payload[4]);
        LOG_INFO("read  reg addr = 0x%08X, val = 0x%08X", addr, read_mreg32(addr));
    }
}
static void user_msg_radar_timer_switch(uint8_t* msg, uint8_t len)
{
    uint8_t flag = msg[0];
    uint8_t timer_id = msg[1];
    if(flag == 0)
    {
        printf("open timer%d \r\n",timer_id);
        hal_gp_timer_start(timer_id);
    }
    else
    {
        printf("close timer%d \r\n",timer_id);
        hal_gp_timer_close(timer_id);
    }

}


void phy_test_loop(void)
{
    phy_cmd_t* phy_cmd = get_phy_cmd_addr();
    

    phy_cmd_recv_loop();
    

    if(phy_cmd->tx_flag)
    {
        printf("tx test start.... \r\n");
        phy_simple_tx();
        printf("tx test stop.... \r\n");
        
        if(PHY_TRANSFER_SIGNLE == phy_cmd->tx_flag)
        {
            phy_cmd->tx_flag = PHY_TRANSFER_STOP;
        }
    }
    
    if(phy_cmd->rx_flag)
    {
        printf("\r\n&&&&& rx test start &&&&&& \r\n");
        phy_simple_rx();
        printf("&&&&& rx test stop &&&&&&\r\n");
        
        if(PHY_TRANSFER_SIGNLE == phy_cmd->rx_flag)
        {
            phy_cmd->rx_flag = PHY_TRANSFER_STOP;
        }
    }
}
