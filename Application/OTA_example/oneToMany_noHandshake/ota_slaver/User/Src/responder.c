/*****************************************************************************
* File: responder.c
*
* Descirption: this file contains the functions support responder.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "responder.h"
#include "range.h"
#include "hal_gpio.h"
#include "ota.h"

extern float kalman_core(uint8_t idx, float distance);

static uint8_t s_responder_state = 0;
static uint8_t s_poll_count = 0;
static uint8_t s_range_flag = 0;
static uint8_t s_first_poll = 0;
static uint8_t s_poll_1024_cnt = 0;
static uint8_t s_poll_recv_flag = 0;
static uint16_t s_range_success_cnt = 0;
static uint32_t s_total_poll_recv_cnt = 0;


static double s_header = 0.0;
static double s_payload_len = 0.0;
static double s_loss_per = 0.0;

static uint64_t s_poll_tx_ts = 0;
static uint64_t s_poll_rx_ts = 0;
static uint64_t s_resp_tx_ts = 0;
static uint64_t s_resp_rx_ts = 0;
static uint64_t s_final_tx_ts = 0;
static uint64_t s_final_rx_ts = 0;
static uint32_t s_round1 = 0;
static uint32_t s_reply1 = 0;
static uint32_t s_round2 = 0;
static uint32_t s_reply2 = 0;
static double s_tof = 0.0;
static double s_distance = 0.0;

static void tx_done_proc(const zn_cb_data_t* cb_data);
static void rx_ok_proc(const zn_cb_data_t* cb_data);
static void rx_error_proc(const zn_cb_data_t* cb_data);
static void rx_timeout_proc(const zn_cb_data_t* cb_data);

static double calc_tof(uint32_t round1, uint32_t reply2, uint32_t round2, uint32_t reply1)
{
    int64_t rb, da, ra, db;

    double ra_rb_x_da_db = 0;
    double rb_y_db = 0;
    double ra_y_da = 0;

    ra = (int64_t)round1;
    db = (int64_t)reply2;

    rb = (int64_t)round2;
    da = (int64_t)reply1;

    ra_rb_x_da_db = (ra * rb) - (da * db);
    rb_y_db = rb + db;
    ra_y_da = ra + da;

    return ra_rb_x_da_db / (rb_y_db + ra_y_da);
}

static double calc_distance(double tof)
{
    double distance = 0.0;
    double aoa_rlt  = 0.0;
    
    distance = (tof / 64.0) * 30.0;

    return distance;
}

static void contrust_resp_msg(void)
{
    g_resp_msg[DST_ADDR_IDX] = REMOTE_ADDR & 0xff;
    g_resp_msg[DST_ADDR_IDX + 1] = (REMOTE_ADDR >> 8) & 0xff;
    g_resp_msg[SRC_ADDR_IDX] = LOCAL_ADDR & 0xff;
    g_resp_msg[SRC_ADDR_IDX + 1] = (LOCAL_ADDR >> 8) & 0xff;
    
    hal_uwb_write_tx_buffer(g_resp_msg, RESP_MSG_LEN);
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
    uint32_t delay_rx_sys_time = 0;
    
    hal_gpio_set_value(LED_PIN, 0);
    s_resp_tx_ts = hal_get_tx_timestamp();
    if(RESP_STATE == s_responder_state)
    {
        s_payload_len = hal_uwb_get_frame_payload_len(uwb_instance.phy_config.psdu_data_rate, RESP_MSG_LEN + CRC_LEN);
        delay_rx_sys_time = (uint64_t)(s_resp_tx_ts + US_TO_UWB_TS_TIME(s_payload_len + MSG_GAP - RX_OFFSET)) >> 8;
        hal_uwb_set_rx_timeout(RX_TIMEOUT);
        hal_uwb_delay_rx(delay_rx_sys_time, &uwb_instance);
        s_responder_state = FINAL_STATE;
    }
    else
    {
        s_responder_state = FINISH_STATE;
    }
}

static void rx_ok_proc(const zn_cb_data_t* cb_data)
{
    uint16_t addr              = 0;
    uint32_t delay_tx_sys_time = 0;
    
    if(cb_data->data_length > MAX_BUFFER_SIZE)
    {
        s_responder_state = FINISH_STATE;
        LOG_ERROR("error rx data len %d", cb_data->data_length);
        return;
    }
    hal_uwb_read_rx_buffer(g_recv_buf, cb_data->data_length);
    
    if(!memcmp(g_recv_buf, g_ota_req_msg_head, 3))
    {
        OTA_Slave_Req_Proc(g_recv_buf);
        return;
    }
    
    if(POLL_STATE == s_responder_state)
    {
        if(0 == memcmp(g_recv_buf, g_poll_msg, VENDOR_LEN))
        {
            addr = ((uint16_t)g_recv_buf[DST_ADDR_IDX + 1] << 8) + g_recv_buf[DST_ADDR_IDX];
            s_poll_count = g_recv_buf[POLL_MSG_IDX];
            if(addr == LOCAL_ADDR)
            {
                s_poll_rx_ts = hal_get_rx_timestamp(&uwb_instance);
                
                if(0 == s_poll_rx_ts)
                {
                    s_responder_state = FINISH_STATE;
                    LOG_ERROR("error rx timestamp is 0!");
                }
                else
                {
                    s_payload_len = hal_uwb_get_frame_payload_len(uwb_instance.phy_config.psdu_data_rate, RESP_MSG_LEN + CRC_LEN);
                    delay_tx_sys_time = (uint64_t)(s_poll_rx_ts + US_TO_UWB_TS_TIME(s_payload_len + MSG_GAP)) >> 8;
                    contrust_resp_msg();
                    hal_uwb_delay_tx(delay_tx_sys_time, &uwb_instance);
                    hal_gpio_set_value(LED_PIN, 1);
                    s_responder_state = RESP_STATE;
                }
                
                if((s_poll_count > 0) && (0 == (s_poll_count % 255)))
                {
                    s_poll_recv_flag = 1;
                }
                
            }
            else
            {
                s_responder_state = FINISH_STATE;
                LOG_ERROR("error destination address: %d", addr);
            }
        }
        else
        {
            s_responder_state = FINISH_STATE;
            LOG_ERROR("error vendor id");
        } 
    }
    else if(FINAL_STATE == s_responder_state)
    {
        if(0 == memcmp(g_recv_buf, g_final_msg, VENDOR_LEN))
        {
            addr = ((uint16_t)g_recv_buf[DST_ADDR_IDX + 1] << 8) + g_recv_buf[DST_ADDR_IDX];
            if(addr == LOCAL_ADDR)
            {
                s_final_rx_ts = hal_get_rx_timestamp(&uwb_instance);
                
                if(0 == s_final_rx_ts)
                {
                    s_responder_state = FINISH_STATE;
                    LOG_ERROR("error rx timestamp is 0!");
                }
                else
                {
                    final_msg_get_ts(&g_recv_buf[POLL_TS_IDX], &s_poll_tx_ts);
                    final_msg_get_ts(&g_recv_buf[RESP_TS_IDX], &s_resp_rx_ts);
                    final_msg_get_ts(&g_recv_buf[FINAL_TS_IDX], &s_final_tx_ts);
                    
                    s_poll_rx_ts -= uwb_instance.phy_config.ant_delay;
                    s_resp_tx_ts += uwb_instance.phy_config.ant_delay;
                    s_final_rx_ts -= uwb_instance.phy_config.ant_delay;
                    
                    s_round1 = s_resp_rx_ts - s_poll_tx_ts;
                    s_reply1 = s_resp_tx_ts - s_poll_rx_ts;
                    s_round2 = s_final_rx_ts - s_resp_tx_ts;
                    s_reply2 = s_final_tx_ts - s_resp_rx_ts;
                    
                    s_tof = calc_tof(s_round1, s_reply2, s_round2, s_reply1);
                    if(s_tof > 0.0)
                    {
                        s_tof = kalman_core(0, s_tof);
                    }
                    s_distance = calc_distance(s_tof);
                    s_range_flag = 1;
                    s_responder_state = FINISH_STATE;
                }
            }
            else
            {
                s_responder_state = FINISH_STATE;
                LOG_ERROR("error destination address: %d", addr);
            }
        }
        else
        {
            s_responder_state = FINISH_STATE;
            LOG_ERROR("error vendor id");
        }
        
    }
    
}

static void rx_error_proc(const zn_cb_data_t* cb_data)
{
    s_responder_state = FINISH_STATE;
}

static void rx_timeout_proc(const zn_cb_data_t* cb_data)
{
    s_responder_state = FINISH_STATE;
}

void responder_init(void)
{
    hal_uwb_phy_config_t*         uwb_phy_config   = &uwb_instance.phy_config;
    hal_uwb_interrupt_callback_t* uwb_irq_callback = &uwb_instance.interrupt_callback;
 
    uwb_irq_init(uwb_irq_callback);
    hal_uwb_config_init(&uwb_instance);
    s_header = hal_uwb_get_frame_header_len(uwb_phy_config->preamble_duration, uwb_phy_config->sfd_id);
    
    #ifdef LOGIC_DEBUG
    uwb_gpio_debug_init();
    #endif
}



void responder_loop(void)
{
    if(INITIAL_STATE == s_responder_state)
    {
        s_responder_state = POLL_STATE;
        hal_uwb_set_rx_timeout(POLL_RX_TIMEOUT);
        hal_uwb_immediate_rx();
    }
    
    if(FINISH_STATE == s_responder_state)
    {
        s_responder_state = INITIAL_STATE;
        if(s_range_flag)
        {
            zn_driver_config_t*  driver_config  = zn_get_dirver_config_addr();
            s_range_flag = 0;
            
            
            s_total_poll_recv_cnt = s_poll_1024_cnt * 256 + s_poll_count;
            
            if(0 == s_first_poll)
            {
                s_range_success_cnt = s_total_poll_recv_cnt;
                s_first_poll = 1;
            }
            
            if(s_total_poll_recv_cnt > 0)
            {
                s_loss_per = (1.0 - (double)s_range_success_cnt / s_total_poll_recv_cnt) * 100.0; 
            }
            else
            {
                s_loss_per = 0.0;
            }
            
            int16_t loss_cnt = s_total_poll_recv_cnt - s_range_success_cnt;
            LOG_INFO("idx: %d, dis: %3.2f, loss_per :(%d/%d)%3.2f%%",s_poll_count, s_distance, loss_cnt, s_total_poll_recv_cnt, s_loss_per);
            s_range_success_cnt++;
        }
        else
        {
//            LOG_DEBUG("responder range failure!");
        }
        
        if(s_poll_recv_flag)
        {
            s_poll_recv_flag = 0;
            s_poll_1024_cnt++;
        }
        if(s_poll_1024_cnt >= 4)
        {
            s_range_success_cnt = 0;
            s_poll_1024_cnt = 0;
        }
    }
    
}