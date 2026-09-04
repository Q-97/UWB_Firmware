/*****************************************************************************
* File: initiator.c
*
* Descirption: this file contains the functions support initiator.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "initiator.h"
#include "range.h"
#include "hal_gpio.h"
#include "phy_cmd.h"
#include "hal_delay.h"
#include "ota.h"


static uint8_t s_initiator_state = 0;
static uint8_t s_poll_count = 0;
static uint8_t s_range_flag = 0;

static double s_header = 0.0;
static double s_payload_len = 0.0;

static uint64_t s_poll_tx_ts = 0;
static uint64_t s_resp_rx_ts = 0;
static uint64_t s_final_tx_ts = 0;

static void tx_done_proc(const zn_cb_data_t* cb_data);
static void rx_ok_proc(const zn_cb_data_t* cb_data);
static void rx_error_proc(const zn_cb_data_t* cb_data);
static void rx_timeout_proc(const zn_cb_data_t* cb_data);

static void contrust_poll_msg(void)
{
    g_poll_msg[DST_ADDR_IDX] = REMOTE_ADDR & 0xff;
    g_poll_msg[DST_ADDR_IDX + 1] = (REMOTE_ADDR >> 8) & 0xff;
    g_poll_msg[SRC_ADDR_IDX] = LOCAL_ADDR & 0xff;
    g_poll_msg[SRC_ADDR_IDX + 1] = (LOCAL_ADDR >> 8) & 0xff;
    g_poll_msg[POLL_MSG_IDX] = s_poll_count;
    
    hal_uwb_write_tx_buffer(g_poll_msg, POLL_MSG_LEN);
}

static void contrust_final_msg(void)
{
    s_poll_tx_ts += uwb_instance.phy_config.ant_delay;
    s_resp_rx_ts -= uwb_instance.phy_config.ant_delay;
    s_final_tx_ts += uwb_instance.phy_config.ant_delay;
    
    g_final_msg[DST_ADDR_IDX] = REMOTE_ADDR & 0xff;
    g_final_msg[DST_ADDR_IDX + 1] = (REMOTE_ADDR >> 8) & 0xff;
    g_final_msg[SRC_ADDR_IDX] = LOCAL_ADDR & 0xff;
    g_final_msg[SRC_ADDR_IDX + 1] = (LOCAL_ADDR >> 8) & 0xff;
    
    final_msg_set_ts(&g_final_msg[POLL_TS_IDX], s_poll_tx_ts);
    final_msg_set_ts(&g_final_msg[RESP_TS_IDX], s_resp_rx_ts);
    final_msg_set_ts(&g_final_msg[FINAL_TS_IDX], s_final_tx_ts);
    
    hal_uwb_write_tx_buffer(g_final_msg, FINAL_MSG_LEN);
}




#ifdef LOGIC_DEBUG
static void uwb_gpio_debug_init(void)
{
    
    hal_gpio_set_tx_en_mode(GPIO_PIN13);
    hal_gpio_set_rx_en_mode(GPIO_PIN0);
    hal_gpio_set_output_default_config(GPIO_PIN12);
    
}
#endif


static void uwb_irq_init(hal_uwb_interrupt_callback_t* irq_callback)
{
    irq_callback->cb_tx_done = &tx_done_proc;
    irq_callback->cb_rx_ok = &rx_ok_proc;
    irq_callback->cb_rx_err = &rx_error_proc;
    irq_callback->cb_rx_timeout = &rx_timeout_proc;
    
}


static void tx_done_proc(const zn_cb_data_t* cb_data)
{
    zn_driver_config_t* driver_config     = zn_get_dirver_config_addr();
    uint32_t            delay_rx_sys_time = 0;
    uint64_t            tx_ts             = 0;
    
    hal_gpio_set_value(LED_PIN, 0);
    tx_ts = hal_get_tx_timestamp();
    if(POLL_STATE == s_initiator_state)
    {
        s_poll_count++;
        s_poll_tx_ts = tx_ts;
        s_payload_len = hal_uwb_get_frame_payload_len(uwb_instance.phy_config.psdu_data_rate, POLL_MSG_LEN + CRC_LEN);
        delay_rx_sys_time = (uint64_t)(s_poll_tx_ts + US_TO_UWB_TS_TIME(s_payload_len + MSG_GAP - RX_OFFSET)) >> 8;
        hal_uwb_set_rx_timeout(RX_TIMEOUT);
        hal_uwb_delay_rx(delay_rx_sys_time, &uwb_instance);
        s_initiator_state = RESP_STATE;
    }
    else
    {
        if((tx_ts - driver_config->inside_ant_delay) != s_final_tx_ts)
        {
            LOG_ERROR("final tx ts error %lld, %lld, %d", s_final_tx_ts, tx_ts, driver_config->inside_ant_delay);
        }
        s_range_flag = 1;
        s_initiator_state = FINAL_STATE;
    }
}

static void rx_ok_proc(const zn_cb_data_t* cb_data)
{
    uint16_t addr              = 0;
    uint32_t delay_tx_sys_time = 0;
    
    if(cb_data->data_length > MAX_BUFFER_SIZE)
    {
        s_initiator_state = FINISH_STATE;
        LOG_ERROR("error rx data len %d", cb_data->data_length);
        return;
    }
    hal_uwb_read_rx_buffer(g_recv_buf, cb_data->data_length);
    
    if(!memcmp(g_recv_buf, g_ota_req_msg_head, 3))
    {
        OTA_Slave_Req_Proc(g_recv_buf);
        return;
    }
    
    if(0 == memcmp(g_recv_buf, g_resp_msg, VENDOR_LEN))
    {
        addr = ((uint16_t)g_recv_buf[DST_ADDR_IDX + 1] << 8) + g_recv_buf[DST_ADDR_IDX];
        if(addr == LOCAL_ADDR)
        {
            s_resp_rx_ts = hal_get_rx_timestamp(&uwb_instance);
            
            if(0 == s_resp_rx_ts)
            {
                s_initiator_state = FINISH_STATE;
                LOG_ERROR("error rx timestamp is 0!");
            }
            else
            {
                s_payload_len = hal_uwb_get_frame_payload_len(uwb_instance.phy_config.psdu_data_rate, RESP_MSG_LEN + CRC_LEN);
                delay_tx_sys_time = (uint64_t)(s_resp_rx_ts + US_TO_UWB_TS_TIME(s_payload_len + MSG_GAP)) >> 8;
                s_final_tx_ts = (((uint64_t)((delay_tx_sys_time & 0xfffffffe) + uwb_instance.phy_config.tx_ts_offset)) << 8);
                
                contrust_final_msg();
                hal_uwb_delay_tx(delay_tx_sys_time, &uwb_instance);
                s_initiator_state = FINAL_STATE;
            }
        }
        else
        {
            s_initiator_state = FINISH_STATE;
            LOG_ERROR("error destination address: %d", addr);
        }
    }
    else
    {
        s_initiator_state = FINISH_STATE;
        LOG_ERROR("error vendor id");
    }
}

static void rx_error_proc(const zn_cb_data_t* cb_data)
{
    s_initiator_state = FINISH_STATE;
}

static void rx_timeout_proc(const zn_cb_data_t* cb_data)
{
    s_initiator_state = FINISH_STATE;
}

static void timer_irq_callback(uint8_t arg)
{
    phy_cmd_t* phy_cmd = get_phy_cmd_addr();
    
    if(phy_cmd->phy_debug_flag == WORK_MODE_PHY_DEBUG)
    {
        return;
    }
    hal_force_uwb_off();
    s_initiator_state = INITIAL_STATE;
}
void initiator_init(void)
{
    hal_uwb_phy_config_t*         uwb_phy_config   = &uwb_instance.phy_config;
    hal_uwb_interrupt_callback_t* uwb_irq_callback = &uwb_instance.interrupt_callback;
    
    uwb_irq_init(uwb_irq_callback);
    hal_uwb_config_init(&uwb_instance);
    s_header = hal_uwb_get_frame_header_len(uwb_phy_config->preamble_duration, uwb_phy_config->sfd_id);
    
    g_log_level = LOG_LEVEL_OFF;
    
    gp_timer.timer_id = TIMER1;
    gp_timer.clk_src = PLL_CLK;
    gp_timer.clk_div = 0;
    gp_timer.mode = TIMER_USER_DEFINE;
    gp_timer.interrupt_en = 1;
    gp_timer.time1 = (uint32_t)(RANGE_INTERVAL * 1000);
    gp_timer.func = (TIMER_CallbackType)&timer_irq_callback;
    
    hal_gp_timer_init(&gp_timer);
    hal_gp_timer_start(gp_timer.timer_id);
    
    #ifdef LOGIC_DEBUG
    uwb_gpio_debug_init();
    #endif
}



void initiator_loop(void)
{
    if(INITIAL_STATE == s_initiator_state)
    {
        contrust_poll_msg();
        hal_gpio_set_value(LED_PIN, 1);
        hal_uwb_immediate_tx();
        s_initiator_state = POLL_STATE;
    }
    
    if(FINISH_STATE == s_initiator_state)
    {
        if(s_range_flag)
        {
            s_range_flag = 0;
            LOG_INFO("initiator range success!");
        }
        else
        {
            LOG_DEBUG("initiator range failure!");
        }
    }
}