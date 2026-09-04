/*****************************************************************************
 *  File: hal_uwb.c
 *
 * Descirption: This file contains the functions support uwb operations.
 *
 *  Copyright (C) : 2022 ultraception.com
 *
 *  Author: sxg
 *  Mail:   
 *  Date:   2025-5-14
 *
 *****************************************************************************/

#include "hal_uwb.h"
#include "hal_gp_timer.h"
#include "hal_gpio.h"
#include "hal_delay.h"
#include "hal_sleep.h"

static uint8_t s_to_tx_state_flag = 0;
static uint8_t s_to_rx_state_flag = 0; 


static void zn_driver_timer_irq_proc(uint8_t timer_id)
{
    zn_driver_config_t* driver_config  = zn_get_dirver_config_addr();
    zn_local_data_t*    local_data     = &driver_config->zn_interrupt_callback;
    
    hal_gp_timer_close(timer_id);
    
    if(s_to_tx_state_flag)
    {
        zn_to_tx_state();
        s_to_tx_state_flag = 0;
    }
    else if(s_to_rx_state_flag)
    {
        zn_to_rx_state();
        s_to_rx_state_flag = 0;
    }
    else if(driver_config->rx_after_tx_flag)
    {
        zn_to_rx_state();
        driver_config->rx_after_tx_flag = 0;
    }
    else
    {
        zn_force_trx_off();
        zn_rf_to_idle_state();
        if(driver_config->rx_ok_flag)
        {
            uint32_t info32   = zn_read_32bit_reg(RX_INFO_BUF0_ID);
            local_data->cb_data.data_length = (info32 & RX_INFO_BUF0_RXFLEN_BIT_MASK) >> RX_INFO_BUF0_RXFLEN_BIT_OFFSET;
            if(local_data->cb_rx_ok != NULL)
            {
                local_data->cb_rx_ok(&local_data->cb_data);
            }
            driver_config->rx_ok_flag = 0;
        }
        else
        {
            if(local_data->cb_rx_timeout != NULL)
            {
                local_data->cb_rx_timeout(&local_data->cb_data);
            }
        }
    }
}


static void uwb_interrupt_init(hal_uwb_instance_t * uwb_instance)
{
    uint32_t                      interrupt_mask     = 0;
    hal_uwb_interrupt_config_t*   interrupt_config   = &uwb_instance->interrupt_config;
    hal_uwb_interrupt_callback_t* interrupt_callback = &uwb_instance->interrupt_callback;
    zn_driver_config_t*           driver_config      = zn_get_dirver_config_addr();


    if(interrupt_config->bits.bit0_int_en)
    {
        interrupt_mask = interrupt_config->interrupt_mask & 0xfffffffe;
        zn_set_interrupt(interrupt_mask);
        zn_force_trx_off();
        zn_write_32bit_reg(SYS_STATUS_ID, 0xffffffff);
        zn_write_32bit_reg(SYS_STATUS1_ID, 0xffffffff);
        
        driver_config->timer_id                                     = uwb_instance->driver_timer_id;
        driver_config->zn_interrupt_callback.cb_cp_err              = interrupt_callback->cb_cp_err;
        driver_config->zn_interrupt_callback.cb_prd                 = interrupt_callback->cb_prd;
        driver_config->zn_interrupt_callback.cb_rx_done             = interrupt_callback->cb_rx_done;
        driver_config->zn_interrupt_callback.cb_rx_err              = interrupt_callback->cb_rx_err;
        driver_config->zn_interrupt_callback.cb_rx_ok               = interrupt_callback->cb_rx_ok;
        driver_config->zn_interrupt_callback.cb_rx_phd              = interrupt_callback->cb_rx_phd;
        driver_config->zn_interrupt_callback.cb_rx_phr_err          = interrupt_callback->cb_rx_phr_err;
        driver_config->zn_interrupt_callback.cb_rx_preamble_timeout = interrupt_callback->cb_rx_preamble_timeout;
        driver_config->zn_interrupt_callback.cb_rx_sfd_done         = interrupt_callback->cb_rx_sfd_done;
        driver_config->zn_interrupt_callback.cb_rx_sfd_timeout      = interrupt_callback->cb_rx_sfd_timeout;
        driver_config->zn_interrupt_callback.cb_rx_timeout          = interrupt_callback->cb_rx_timeout;
        driver_config->zn_interrupt_callback.cb_tx_done             = interrupt_callback->cb_tx_done;
        
        hal_gp_timer_t timer_config = {0};
        
        timer_config.timer_id     = uwb_instance->driver_timer_id;
        timer_config.mode         = 1;
        timer_config.clk_div      = 0;
        timer_config.clk_src      = 0;
        timer_config.interrupt_en = 1;
        timer_config.func         = (TIMER_CallbackType)&zn_driver_timer_irq_proc;
        
        hal_gp_timer_init(&timer_config);
        
        driver_config->timer_freq = hal_get_gp_timer_clk_freq(uwb_instance->driver_timer_id);
        NVIC_EnableIRQ(UWB_IRQn);
    }
    else
    {
        zn_force_trx_off();
        zn_write_32bit_reg(SYS_STATUS_ID, 0xffffffff);
        NVIC_DisableIRQ(UWB_IRQn);
    }
        
}


static void uwb_param_calc_init(hal_uwb_instance_t * uwb_instance)
{
    hal_uwb_phy_config_t* hal_phy_config    = &uwb_instance->phy_config;
    hal_uwb_aoa_config_t* hal_aoa_config    = &uwb_instance->aoa_config;
    hal_uwb_fem_config_t* hal_fem_config    = &uwb_instance->fem_config;     
    zn_driver_config_t*   driver_config     = zn_get_dirver_config_addr();
    zn_config_t*          driver_phy_config = &driver_config->phy_config;
    uint8_t               status            = ((hal_sleep_get_wakeup_status() & WAKEUP_BY_AUTO_CNT)&hal_sleep_get_retention_en());
    uint8_t               cal_en            = status ? 0 : 1;
    hal_uwb_radar_config_t* hal_radar_config = &uwb_instance->radar_config;
    hal_uwb_radar_old_config_t *hal_radar_old_config =  &uwb_instance->radar_old_config;
    
    driver_phy_config->channel_num          = hal_phy_config->channel_num;
    driver_phy_config->rf_cfg               = hal_phy_config->frame_type;
    driver_phy_config->rf_ext_en            = hal_phy_config->frame_ext_en;
    driver_phy_config->preamble_code_idx    = hal_phy_config->preamble_code_idx;
    driver_phy_config->sfd_id               = hal_phy_config->sfd_id;
    driver_phy_config->psdu_data_rate       = hal_phy_config->psdu_data_rate;
    driver_phy_config->bprf_phr_data_rate   = hal_phy_config->bprf_phr_data_rate;
    driver_phy_config->preamble_duration    = hal_phy_config->preamble_duration;
    driver_phy_config->prf_mode             = hal_phy_config->prf_mode;
    driver_phy_config->tia_level            = hal_phy_config->tia_level;
    driver_phy_config->pa_level             = hal_phy_config->pa_level;
    driver_phy_config->sts_seg_num          = hal_phy_config->sts_seg_num;
    driver_phy_config->sts_seg_len          = hal_phy_config->sts_seg_len;
    driver_phy_config->sfd_to               = hal_phy_config->sfd_to;
    driver_phy_config->aoa_en               = hal_aoa_config->aoa_en;
    driver_phy_config->aoa_mode             = hal_aoa_config->aoa_mode;
    driver_phy_config->aoa_dimension_mode   = hal_aoa_config->aoa_dimension_mode;
    driver_phy_config->ant_sel              = hal_aoa_config->ant_sel;
    driver_phy_config->aoa_3d_ant_type      = hal_aoa_config->aoa_3d_ant_type;
    driver_phy_config->ant_distance_rx0_rx1 = hal_aoa_config->ant_distance_rx0_rx1;
    driver_phy_config->ant_distance_rx0_rx2 = hal_aoa_config->ant_distance_rx0_rx2;
    driver_phy_config->delay_rx0_rx1        = hal_aoa_config->delay_rx0_rx1;
    driver_phy_config->phase_compen_rx0_rx1 = hal_aoa_config->phase_compen_rx0_rx1;
    driver_phy_config->phase_compen_rx0_rx2 = hal_aoa_config->phase_compen_rx0_rx2;
    driver_phy_config->fem_en               = hal_fem_config->fem_en;
    driver_phy_config->fem_ctrl_mode        = hal_fem_config->fem_ctrl_mode;
    driver_phy_config->fem_tx_pin           = hal_fem_config->tx_en_pin_id;
    driver_phy_config->fem_rx0_pin          = hal_fem_config->rx0_en_pin_id;
    driver_phy_config->fem_rx1_pin          = hal_fem_config->rx1_en_pin_id;
    driver_phy_config->fem_rx2_pin          = hal_fem_config->rx2_en_pin_id;
    
    driver_phy_config->rx_signle_switch_en  = 1;
    driver_phy_config->flash_save_en        = 0;
    driver_phy_config->agc_mode             = 1;
    if(driver_phy_config->aoa_en)
    {
        //driver_config->paver_save_flag = 1;
    }
    
    if(hal_radar_config->radar_en || hal_radar_old_config->radar_en)
    {
        driver_phy_config->radar_en = 1;
        driver_phy_config->agc_mode = 2;
    }
    else
    {
        driver_phy_config->radar_en = 0;
    }
    
    zn_digit_regs_init();
    zn_analog_regs_init();
    zn_pdoa_init();
    zn_config(driver_phy_config);
    if(driver_phy_config->fem_en)
    {
        hal_gpio_set_output_default_config(driver_phy_config->fem_tx_pin);
        hal_gpio_set_output_default_config(driver_phy_config->fem_rx0_pin);
        if(driver_phy_config->aoa_en)
        {
            hal_gpio_set_output_default_config(driver_phy_config->fem_rx1_pin);
            if(TYPE_3D == driver_phy_config->aoa_dimension_mode)
            {
                hal_gpio_set_output_default_config(driver_phy_config->fem_rx2_pin);
            }
        }
        zn_fem_to_rx_state();
    }

    if(driver_phy_config->flash_save_en)
    {
        if(FLASH_WR_FLAG == zn_get_flash_flag(driver_phy_config->channel_num))
        {
            cal_en = 0;
        }
        else
        {
            cal_en = 1;
        }
    }
    zn_pll_calib(driver_phy_config->channel_num, cal_en);

    zn_calibration(driver_phy_config->channel_num, cal_en);

    if(driver_phy_config->fem_en)
    {
        zn_fem_to_idle_state();
    }
    hal_phy_config->tx_ts_offset = zn_get_tx_ts_offset();

}

static void read_rx_timestamp(uint8_t *rx_timestamp)
{
    zn_read_rx_timestamp(rx_timestamp);
}

static void read_rx2_timestamp(uint8_t *rx_timestamp)
{
    zn_read_rx2_timestamp(rx_timestamp);
}


static void read_tx_timestamp(uint8_t *tx_timestamp)
{
    zn_read_tx_timestamp(tx_timestamp);
}

static uint64_t range_save_timestamp(uint8_t *time_buf)
{
    uint64_t timestamp = 0;

    timestamp = time_buf[4];
    timestamp <<= 32;
    timestamp += (uint32_t)time_buf[0] + ((uint32_t)time_buf[1] << 8) + ((uint32_t)time_buf[2] << 16) + ((uint32_t)time_buf[3] << 24);

    return timestamp;
}

static uint64_t get_correction_rx_timestamp(hal_uwb_phy_config_t* phy_config)
{
    uint64_t timestamp_raw           = 0;

    timestamp_raw = timestamp_raw_calc();

    timestamp_retry_peak(phy_config->rx_ts_left_find_len, phy_config->rx_ts_thresold_len, timestamp_raw, &timestamp_raw);
    return timestamp_raw;
}

static uint64_t get_correction_rx2_timestamp(hal_uwb_phy_config_t* phy_config)
{
    uint64_t timestamp_raw           = 0;

    timestamp_raw = timestamp_raw_calc_rx2();

    timestamp_retry_peak_rx2(phy_config->rx_ts_left_find_len, phy_config->rx_ts_thresold_len, timestamp_raw, &timestamp_raw);
    return timestamp_raw;
}

static void change_to_tx_state(uint32_t tx_sys, hal_uwb_instance_t * uwb_instance)
{
    uint32_t cur_sys  = hal_get_cur_sys_time();
    uint32_t diff     = (cur_sys > tx_sys) ? (tx_sys + 0xffffffff - cur_sys) : (tx_sys - cur_sys);
    uint32_t delay_us = SYS_TO_US(diff);
    uint8_t  timer_id = uwb_instance->driver_timer_id;
    uint32_t clk_freq = hal_get_gp_timer_clk_freq(timer_id);
    
    if((delay_us <= DELAY_OFFSET) || ((delay_us - DELAY_OFFSET) < 100))
    {
        zn_to_tx_state();
    }
    else if(MODE_BLOCK == uwb_instance->delay_mode)
    {
        delay_us -= DELAY_OFFSET;
        hal_delay_us(delay_us);
        zn_to_tx_state();
    }
    else
    {
        s_to_tx_state_flag = 1;
        delay_us -= DELAY_OFFSET;
        hal_gp_timer_set_loadval(timer_id, USEC_TO_COUNT(delay_us, clk_freq));
        hal_gp_timer_start(timer_id);
    }
    
}

static void change_to_rx_state(uint32_t rx_sys, hal_uwb_instance_t * uwb_instance)
{
    uint32_t cur_sys  = hal_get_cur_sys_time();
    uint32_t diff     = (cur_sys > rx_sys) ? (rx_sys + 0xffffffff - cur_sys) : (rx_sys - cur_sys);
    uint32_t delay_us = SYS_TO_US(diff);
    uint8_t  timer_id = uwb_instance->driver_timer_id;
    uint32_t clk_freq = hal_get_gp_timer_clk_freq(timer_id);

    if((delay_us <= DELAY_OFFSET) || ((delay_us - DELAY_OFFSET) < 100))
    {
        zn_to_rx_state();
    }
    else if(MODE_BLOCK == uwb_instance->delay_mode)
    {
        delay_us -= DELAY_OFFSET;
        hal_delay_us(delay_us);
        zn_to_rx_state();
    }
    else
    {
        s_to_rx_state_flag = 1;
        delay_us -= DELAY_OFFSET;
        hal_gp_timer_set_loadval(timer_id, USEC_TO_COUNT(delay_us, clk_freq));
        hal_gp_timer_start(timer_id);
    } 
}

static void uwb_fem_ctrl_init(hal_uwb_fem_config_t* fem_config, hal_uwb_aoa_config_t* aoa_config)
{
    uint8_t    txen_fun[14] = {3, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 3};
    uint8_t    rxen_fun[8]  = {4, 4, 4, 0, 0, 0, 0, 3};
    hal_gpio_t gpio_cfg     = {0};
    uint8_t    tx_en_pin    = fem_config->tx_en_pin_id;
    uint8_t    rx0_en_pin   = fem_config->rx0_en_pin_id;
    uint8_t    rx1_en_pin   = fem_config->rx1_en_pin_id;
    uint8_t    rx2_en_pin   = fem_config->rx2_en_pin_id;
    
    if(FEM_CTRL_AUTO == fem_config->fem_ctrl_mode)
    {
        hal_gpio_set_tx_en_mode(tx_en_pin);
        hal_gpio_set_rx_en_mode(rx0_en_pin);
        if(aoa_config->aoa_en)
        {
            if(TYPE_3D == aoa_config->aoa_dimension_mode)
            {
                hal_gpio_set_rx_en_mode(rx1_en_pin);
                hal_gpio_set_rx_en_mode(rx2_en_pin);
            }
            hal_gpio_set_rx_en_mode(rx1_en_pin);
        }
        
    }
    else
    {
        hal_gpio_set_output_default_config(tx_en_pin);
        hal_gpio_set_value(tx_en_pin, 0);
        hal_gpio_set_output_default_config(rx0_en_pin);
        hal_gpio_set_value(rx0_en_pin, 0);
        if(aoa_config->aoa_en)
        {
            hal_gpio_set_output_default_config(rx1_en_pin);
            hal_gpio_set_value(rx1_en_pin, 0);
            if(TYPE_3D == aoa_config->aoa_dimension_mode)
            {
                hal_gpio_set_output_default_config(rx2_en_pin);
                hal_gpio_set_value(rx2_en_pin, 0);
            }
        }
    }
}


void hal_uwb_config_init(hal_uwb_instance_t * uwb_instance)
{
    __disable_irq();
    
    uwb_param_calc_init(uwb_instance);
    uwb_interrupt_init(uwb_instance);
    
    if(uwb_instance->fem_config.fem_en)
    {
        uwb_fem_ctrl_init(&uwb_instance->fem_config, &uwb_instance->aoa_config);
    }

    __enable_irq();
}

void hal_uwb_param_update(zn_config_t *config, hal_uwb_instance_t *uwb_instance)
{
    zn_driver_config_t *driver_config = zn_get_dirver_config_addr();

    if(NULL == config || NULL == uwb_instance || NULL == driver_config)
    {
        return;
    }

    uwb_instance->phy_config.channel_num        = config->channel_num;
    uwb_instance->phy_config.frame_type         = config->rf_cfg;
    uwb_instance->phy_config.preamble_code_idx  = config->preamble_code_idx;
    uwb_instance->phy_config.sfd_id             = config->sfd_id;
    uwb_instance->phy_config.psdu_data_rate     = config->psdu_data_rate;
    uwb_instance->phy_config.bprf_phr_data_rate = config->bprf_phr_data_rate;
    uwb_instance->phy_config.preamble_duration  = config->preamble_duration;
    uwb_instance->phy_config.prf_mode           = config->prf_mode;
    uwb_instance->phy_config.sts_seg_num        = config->sts_seg_num;
    uwb_instance->phy_config.sts_seg_len        = config->sts_seg_len;
    uwb_instance->phy_config.sfd_to             = config->sfd_to;

    driver_config->phy_config.channel_num        = config->channel_num;
    driver_config->phy_config.rf_cfg             = config->rf_cfg;
    driver_config->phy_config.preamble_code_idx  = config->preamble_code_idx;
    driver_config->phy_config.sfd_id             = config->sfd_id;
    driver_config->phy_config.psdu_data_rate     = config->psdu_data_rate;
    driver_config->phy_config.bprf_phr_data_rate = config->bprf_phr_data_rate;
    driver_config->phy_config.preamble_duration  = config->preamble_duration;
    driver_config->phy_config.prf_mode           = config->prf_mode;
    driver_config->phy_config.sts_seg_num        = config->sts_seg_num;
    driver_config->phy_config.sts_seg_len        = config->sts_seg_len;
    driver_config->phy_config.sfd_to             = config->sfd_to;
}


uint64_t hal_get_tx_timestamp(void)
{
    zn_driver_config_t* driver_config = zn_get_dirver_config_addr();

    uint8_t  timestamp[5] = {0};
    uint64_t rlt          = 0;
    read_tx_timestamp(timestamp); 
    rlt = range_save_timestamp(timestamp) + driver_config->inside_ant_delay;
    return rlt;
}


uint64_t hal_get_rx_timestamp(hal_uwb_instance_t * uwb_instance)
{
    uint8_t  timestamp[5]            = {0};
    uint64_t rlt                     = 0;
    uint8_t flag                     = 0;
    uint8_t frame_type               = 0;
    hal_uwb_phy_config_t* phy_config = &uwb_instance->phy_config;
    uint8_t *rx_ts_flag              = &uwb_instance->rx_sfd_ts_flag;

    read_rx_timestamp(timestamp);
    rlt = range_save_timestamp(timestamp);

    if(0 == rlt)
    {
        rlt = get_correction_rx_timestamp(phy_config);
        *rx_ts_flag = 0;
    }
    else if(uwb_instance->rx_ts_retry_en)
    {
        flag = timestamp_retry(phy_config->rx_ts_left_find_len, phy_config->rx_ts_thresold_len, rlt, &rlt);
        if(flag == 1)
        {
            *rx_ts_flag = 2;
        }
        else
        {
            *rx_ts_flag = ranging_confidence_calc();
        }
    }

    return rlt;
}

uint64_t hal_get_rx2_timestamp(hal_uwb_instance_t * uwb_instance)
{
    uint8_t  timestamp[5]            = {0};
    uint64_t rlt                     = 0;
    uint8_t flag                     = 0;
    uint8_t frame_type               = 0;
    hal_uwb_phy_config_t* phy_config = &uwb_instance->phy_config;
    uint8_t *rx_ts_flag              = &uwb_instance->rx2_sfd_ts_flag;

    frame_type = hal_get_cur_frame_type();
    read_rx2_timestamp(timestamp);
    rlt = range_save_timestamp(timestamp); 

    if(0 == rlt)
    {
        rlt = get_correction_rx2_timestamp(phy_config);
        *rx_ts_flag = 0;
    }
    else if(uwb_instance->rx_ts_retry_en)
    {
        flag = timestamp_retry_rx2(phy_config->rx_ts_left_find_len, phy_config->rx_ts_thresold_len, rlt, &rlt);
        if(flag == 1)
        {
            *rx_ts_flag = 2;
        }
        else
        {
            *rx_ts_flag = ranging_confidence_calc_rx2();
        }
    }
    return rlt;
}

#ifdef POWER_TEST
static void sys_ctrl_write_t(uint32_t addr, uint32_t val)
{
    sys_ctrl_write(addr, val);
}
#endif

ERROR_Type hal_uwb_immediate_tx(void)
{
    int32_t ret = 0;
    
    zn_to_tx_state();
    #ifdef POWER_TEST
    sys_ctrl_write_t(UWB_CLK_ICG_REG, 0xff1);
    zn_soc_to_idle_state();
    #endif
    ret = zn_start_tx(ZN_START_TX_IMMEDIATE);
    
    if(ZN_SUCCESS == ret)
    {
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

ERROR_Type hal_uwb_delay_tx(uint32_t tx_delay_sys, hal_uwb_instance_t * uwb_instance)
{
    int32_t ret = 0;
    uint32_t cur_sys = hal_get_cur_sys_time();
    uint64_t diff = (cur_sys > tx_delay_sys) ? (cur_sys - tx_delay_sys) : (tx_delay_sys - cur_sys);


    if(((cur_sys > tx_delay_sys) && (diff > 0x80000000)) ||  
       ((cur_sys < tx_delay_sys) && (diff > US_TO_SYS(50)) && (diff < 0x80000000)) 
      )
    {
        zn_set_delayed_trx_time(tx_delay_sys);
        change_to_tx_state(tx_delay_sys, uwb_instance);
        ret = zn_start_tx(ZN_START_TX_DELAYED);
    }
    else
    {
        zn_to_tx_state();
        ret = zn_start_tx(ZN_START_TX_IMMEDIATE);
    }
    
    if(ZN_SUCCESS == ret)
    {
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}


ERROR_Type hal_uwb_rx_after_tx(uint32_t rx_after_tx_us)
{
    int32_t ret                         = 0;
    zn_driver_config_t*  driver_config  = zn_get_dirver_config_addr();
    
    driver_config->rx_after_tx_flag = 1;
    driver_config->rx_after_tx_us = rx_after_tx_us;
    
    zn_set_rx_after_tx_delay(rx_after_tx_us);
    zn_to_tx_state();
    ret = zn_start_tx(ZN_RX_EN_AFTER_TX);
    
    if(ZN_SUCCESS == ret)
    {
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

ERROR_Type hal_uwb_rx_after_tx_delay(uint32_t tx_delay_sys, uint32_t rx_after_tx_us, hal_uwb_instance_t * uwb_instance)
{
    int32_t ret                         = 0;
    uint32_t cur_sys                    = 0;
    uint64_t diff                       = 0;
    zn_driver_config_t*  driver_config  = zn_get_dirver_config_addr();
    
    driver_config->rx_after_tx_flag = 1;
    driver_config->rx_after_tx_us = rx_after_tx_us;
    
    zn_set_rx_after_tx_delay(rx_after_tx_us);
    
    cur_sys = hal_get_cur_sys_time();
    diff = (cur_sys > tx_delay_sys) ? (cur_sys - tx_delay_sys) : (tx_delay_sys - cur_sys);

    if(((cur_sys > tx_delay_sys) && (diff > 0x80000000)) ||  
       ((cur_sys < tx_delay_sys) && (diff > US_TO_SYS(50)) && (diff < 0x80000000)) 
      )
    {
        zn_set_delayed_trx_time(tx_delay_sys);
        change_to_tx_state(tx_delay_sys, uwb_instance);
        ret = zn_start_tx(ZN_RX_EN_AFTER_TX_DELAY);
    }
    else
    {
        zn_to_tx_state();
        ret = zn_start_tx(ZN_RX_EN_AFTER_TX);
    }
    if(ZN_SUCCESS == ret)
    {
        return SUCCESS;        
    }
    else
    {
        return ERROR;
    }
}

void hal_uwb_rx_state_loop(void)
{
    zn_rx_state_check();
}

ERROR_Type hal_uwb_immediate_rx(void)
{
    int32_t ret = 0;
    
    zn_to_rx_state();
    #ifdef POWER_TEST
    zn_soc_to_idle_state();
    #endif
    ret = zn_rx_enable(ZN_START_RX_IMMEDIATE);
    
    if(ZN_SUCCESS == ret)
    {
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

ERROR_Type hal_uwb_delay_rx(uint32_t rx_delay_sys, hal_uwb_instance_t * uwb_instance)
{
    int32_t ret = 0;
    uint32_t cur_sys = hal_get_cur_sys_time();
    uint64_t diff = (cur_sys > rx_delay_sys) ? (cur_sys - rx_delay_sys) : (rx_delay_sys - cur_sys);

    if(((cur_sys > rx_delay_sys) && (diff > 0x80000000)) ||  
       ((cur_sys < rx_delay_sys) && (diff > US_TO_SYS(200)) && (diff < 0x80000000)) 
      )
    {
        zn_set_delayed_trx_time(rx_delay_sys);
        change_to_rx_state(rx_delay_sys, uwb_instance);
        ret = zn_rx_enable(ZN_START_RX_DELAYED);
    }
    else
    {
        zn_to_rx_state();
        ret = zn_rx_enable(ZN_START_RX_IMMEDIATE);
    }
    
    if(ZN_SUCCESS == ret)
    {
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

void hal_uwb_tia_calc(void)
{
    zn_tia_calc();
}

void hal_uwb_agc_one_time_clac_rx0(void)
{
    zn_agc_one_time_clac_rx0();
}

void hal_uwb_agc_one_time_clac_rx1(void)
{
    zn_agc_one_time_clac_rx1();
}

void hal_uwb_agc_auto_clac_rx0(void)
{
    zn_agc_auto_clac_rx0();
}

void hal_uwb_agc_auto_clac_rx1(void)
{
    zn_agc_auto_clac_rx1();
}


void hal_uwb_read_adc_mem(uint8_t mem_id)
{
    zn_read_adc_mem(mem_id);
}

void hal_uwb_read_cir_mem_rx0(void)
{
    zn_read_cir_mem_rx0();
}

void hal_uwb_read_cir_mem_rx1(void)
{
    zn_read_cir_mem_rx1();
}

void hal_uwb_read_sts_mem_rx0(void)
{
    zn_read_sts_mem_rx0(); 
}

void hal_uwb_read_sts_mem_rx1(void)
{
    zn_read_sts_mem_rx1();
}

void hal_uwb_agc_gain_mem_read(void)
{
    zn_agc_gain_mem_read();
}

    
void hal_uwb_show_rx0_info(void)
{
    int32_t cir_peak_value = hal_read_uwb_register(0x1a24) >> 8;
    int32_t nacc0          = hal_read_uwb_register(IP_NACC0_ID) >> 20;
    int32_t pulseIdx       = hal_read_uwb_register(0x1a74) >> 22;
    double  power          = 0;
    uint8_t lna_tia        = 0;
    uint8_t vga            = 0;
    uint8_t ant_flag       = 0;
    uint8_t lna_flag       = 0;
    uint16_t f_idx_rx0 = zn_read_32bit_reg(0x1a38) >> 22;
	
    zn_rx0_agcout(&lna_tia, &vga, &ant_flag, &lna_flag);
    
    LOG_INFO("rx0 agc out--->lna_tia = %d,vga = %d, ant_flag = %d, lna_flag = %d",lna_tia, vga, ant_flag, lna_flag);
    LOG_INFO("rx0 done! CIR peak----> %d", cir_peak_value);
    LOG_INFO("rx0 rcv data, peak/nacc =: %0.2f, accumulated number in SFD is %d:", (double)(cir_peak_value * 1.0 / nacc0), nacc0);
    LOG_INFO("rx0 done! pulseIdx---->%d", pulseIdx);
    LOG_INFO("rx0 done! f_idx_rx0---->%d",f_idx_rx0);

    power = zn_recv_power_for_first_path();
    LOG_INFO("rx0 recv power is ----> %3.2f", power);
    
    int dcReg = hal_read_uwb_register(0x1a7c);
    uint32_t I_Tmp = ( dcReg >> 27 ) & 0x1F;
    uint32_t Q_Tmp = ( dcReg >> 19 ) & 0x1F;
    int32_t I = I_Tmp > 15 ? I_Tmp - 32 : I_Tmp;
    int32_t Q = Q_Tmp > 15 ? Q_Tmp - 32 : Q_Tmp;
    LOG_INFO("RX0 dc_i=%d,dc_q=%d",I,Q);
    
}

void hal_uwb_show_rx1_info(void)
{
    int32_t cir_peak_value = hal_read_uwb_register(0x1b00) >> 8;
    int32_t nacc0          = hal_read_uwb_register(IP_NACC1_ID) >> 20;
    int32_t pulseIdx       = hal_read_uwb_register(0x1b1c) >> 22;
    double  power          = 0;
    uint8_t lna_tia        = 0;
    uint8_t vga            = 0;
    uint8_t lna_flag       = 0;
    uint16_t f_idx_rx1 = zn_read_32bit_reg(0x1b14) >> 22;
    
    zn_rx1_agcout(&lna_tia, &vga, &lna_flag);
    LOG_INFO("rx1 agc out--->lna_tia = %d,vga = %d, lna_flag = %d",lna_tia, vga, lna_flag);
    LOG_INFO("rx1 done! CIR peak----> %d", cir_peak_value);
    LOG_INFO("rx1 rcv data, peak/nacc =: %0.2f, accumulated number in SFD is %d:", (double)(cir_peak_value * 1.0 / nacc0), nacc0);
    LOG_INFO("rx1 done! pulseIdx---->%d", pulseIdx);
    LOG_INFO("rx1 done! f_idx_rx1---->%d",f_idx_rx1);

    power = zn_recv_power_for_second_path();
    LOG_INFO("rx1 recv power is ----> %3.2f", power);
}

void hal_read_uwb_mem(uint16_t addr, uint8_t* buffer, uint16_t len)
{
    zn_read_from_device(addr, len, buffer);
}

void hal_write_uwb_mem(uint16_t addr, uint8_t* buffer, uint16_t len)
{
    zn_write_to_device(addr, len, buffer);
}

void hal_force_uwb_off(void)
{
    zn_force_trx_off();
    hal_write_uwb_register(SYS_STATUS_ID, SYS_MASK_MASK);
}

void hal_uwb_to_tx_state(void)
{
    zn_to_tx_state();
}

void hal_uwb_to_rx_state(void)
{
    zn_to_rx_state();
}

void hal_uwb_to_idle_state(void)
{
    zn_rf_to_idle_state();
}

void hal_uwb_fem_to_tx_state(void)
{
    zn_fem_to_tx_state();
}

void hal_uwb_fem_to_rx_state(void)
{
    zn_fem_to_rx_state();
}

void hal_uwb_fem_to_idle_state(void)
{
    zn_fem_to_idle_state();
}

void hal_uwb_set_rx_timeout(uint32_t time_us)
{
    zn_set_rx_timeout(time_us);
}
void hal_uwb_set_rx_preamble(uint8_t sts_cfg, uint8_t preamble_duration)
{
    zn_set_rx_preamble_config(sts_cfg, preamble_duration);
}

void hal_uwb_write_tx_buffer(uint8_t* buffer, uint16_t len)
{
    if(len >= TX_BUFFER_MAX_LEN)
    {
        LOG_ERROR("error len max than tx buffer size");
        return;
    }
    
    zn_write_tx_data(len, buffer, 0);
    zn_write_tx_frame_ctrl(len + 2, 0, 0);
}

void hal_uwb_read_rx_buffer(uint8_t* buffer, uint16_t len)
{
    if(len > RX_BUFFER_MAX_LEN)
    {
        LOG_ERROR("error len max than rx buffer size");
        return;
    }
    
    zn_read_rx_data(buffer, len);
}

void hal_uwb_rx_antenna_switch(uint8_t ant_sel)
{
    zn_driver_config_t *driver_config = zn_get_dirver_config_addr();

    driver_config->phy_config.ant_sel = ant_sel;
    zn_pdoa_antenna_switch(ant_sel);
}

uint16_t hal_uwb_get_rx_data_len(void)
{
    return ((hal_read_uwb_register(RX_INFO_BUF0_ID) & RX_INFO_BUF0_RXFLEN_BIT_MASK) >> RX_INFO_BUF0_RXFLEN_BIT_OFFSET);
}

uint8_t hal_get_cur_channel(void)
{
    return ((hal_read_uwb_register(SYSTEM_PARAM_ID) & SYSTEM_PARAM_RF_CHAN_BIT_MASK) >> SYSTEM_PARAM_RF_CHAN_BIT_OFFSET);
}

uint32_t hal_get_cur_sys_time(void)
{
    return zn_get_sys_time();
}

void hal_uwb_set_frame_type(uint8_t frame_type)
{
    zn_driver_config_t* driver_config = zn_get_dirver_config_addr();
    driver_config->phy_config.rf_cfg = frame_type;
    zn_modify_rframe_cfg(frame_type);
}

uint8_t hal_get_cur_frame_type(void)
{
    return ((hal_read_uwb_register(SYS_CFG_ID) & SYS_CFG_STS_MODE_BIT_MASK) >> SYS_CFG_STS_MODE_BIT_OFFSET);
}

double hal_uwb_get_freq_offset(void)
{
    uint32_t status_reg = hal_read_uwb_register(COE_PPM_ID);
    double   foffset     = 0;
    
    status_reg = status_reg >> 16;
    foffset = status_reg >= 32768 ? status_reg - 32768 : status_reg + 32768;
    foffset -= 32768;
    foffset = foffset / 512;
    
    return foffset;
}

void hal_uwb_read_2d_pdoa_nlos_result(double *pdoa1, uint8_t *detectLevel)
{
    zn_read_2d_pdoa_nlos_result(pdoa1, detectLevel);
}

void hal_uwb_read_2d_angle(double *pdoa, double *aoa, uint8_t *valid_flag)
{
    zn_read_2d_angle(pdoa, aoa, valid_flag);
}

void hal_uwb_cal_2d_angle_by_pdoa(double pdoa, double *aoa, uint8_t *valid_flag)
{
    zn_cal_2d_angle_by_pdoa(pdoa, aoa, valid_flag);
}

void hal_uwb_read_3d_pdoa_nlos_result(double *pdoa1, double *pdoa2, uint8_t *detectLevel)
{
    zn_read_3d_pdoa_nlos_result(pdoa1, pdoa2, detectLevel);
}

void hal_uwb_read_3d_angle(double *pdoa_sfd, double *pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag)
{
    zn_driver_config_t *driver_config = zn_get_dirver_config_addr();

    switch(driver_config->phy_config.aoa_3d_ant_type)
    {
        case AOA_3D_ANTENNA_TYPE_CEILING_TYPE1:
        {
             zn_read_3d_angle_with_antenna_ceiling_type1(pdoa_sfd, pdoa_sts, azimuth_angle, elevation_angle, valid_flag);
             break;
        }
        case AOA_3D_ANTENNA_TYPE_CEILING_TYPE2:
        {
             zn_read_3d_angle_with_antenna_ceiling_type2(pdoa_sfd, pdoa_sts, azimuth_angle, elevation_angle, valid_flag);
             break;
        }
        case AOA_3D_ANTENNA_TYPE_CEILING_TYPE3:
        {
             zn_read_3d_angle_with_antenna_ceiling_type3(pdoa_sfd, pdoa_sts, azimuth_angle, elevation_angle, valid_flag);
             break;
        }
        case AOA_3D_ANTENNA_TYPE_VERTICAL_TYPE1:
        {
             zn_read_3d_angle_result_with_antenna_vertical_type1(pdoa_sfd, pdoa_sts, azimuth_angle, elevation_angle, valid_flag);
             break;
        }
        case AOA_3D_ANTENNA_TYPE_VERTICAL_TYPE2:
        {
             zn_read_3d_angle_result_with_antenna_vertical_type2(pdoa_sfd, pdoa_sts, azimuth_angle, elevation_angle, valid_flag);
             break;
        }
        case AOA_3D_ANTENNA_TYPE_VERTICAL_TYPE3:
        {
             zn_read_3d_angle_result_with_antenna_vertical_type3(pdoa_sfd, pdoa_sts, azimuth_angle, elevation_angle, valid_flag);
             break;
        }
        case AOA_3D_ANTENNA_TYPE_VERTICAL_TYPE4:
        {
             zn_read_3d_angle_result_with_antenna_vertical_type4(pdoa_sfd, pdoa_sts, azimuth_angle, elevation_angle, valid_flag);
             break;
        }
        case AOA_3D_ANTENNA_TYPE_VERTICAL_TYPE5:
        {
             zn_read_3d_angle_result_with_antenna_vertical_type5(pdoa_sfd, pdoa_sts, azimuth_angle, elevation_angle, valid_flag);
             break;
        }
        case AOA_3D_ANTENNA_TYPE_VERTICAL_TYPE6:
        {
             zn_read_3d_angle_result_with_antenna_vertical_type6(pdoa_sfd, pdoa_sts, azimuth_angle, elevation_angle, valid_flag);
             break;
        }
        case AOA_3D_ANTENNA_TYPE_VERTICAL_TYPE7:
        {
             zn_read_3d_angle_result_with_antenna_vertical_type7(pdoa_sfd, pdoa_sts, azimuth_angle, elevation_angle, valid_flag);
             break;
        }
        default:
        {
             break;
        }
    }
}

void hal_uwb_cal_3d_angle_by_pdoa_with_antenna_ceiling_type1(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag)
{
    zn_cal_3d_angle_by_pdoa_with_antenna_ceiling_type1(pdoa_sfd, pdoa_sts, azimuth_angle, elevation_angle, valid_flag);
}

void hal_uwb_cal_3d_angle_by_pdoa_with_antenna_ceiling_type2(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag)
{
    zn_cal_3d_angle_by_pdoa_with_antenna_ceiling_type2(pdoa_sfd, pdoa_sts, azimuth_angle, elevation_angle, valid_flag);
}

void hal_uwb_cal_3d_angle_by_pdoa_with_antenna_ceiling_type3(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag)
{
    zn_cal_3d_angle_by_pdoa_with_antenna_ceiling_type3(pdoa_sfd, pdoa_sts, azimuth_angle, elevation_angle, valid_flag);
}

void hal_uwb_cal_3d_angle_by_pdoa_with_antenna_vertical_type1(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag)
{
    zn_cal_3d_angle_by_pdoa_with_antenna_vertical_type1(pdoa_sfd, pdoa_sts, azimuth_angle, elevation_angle, valid_flag);
}

void hal_uwb_cal_3d_angle_by_pdoa_with_antenna_vertical_type2(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag)
{
    zn_cal_3d_angle_by_pdoa_with_antenna_vertical_type2(pdoa_sfd, pdoa_sts, azimuth_angle, elevation_angle, valid_flag);
}

void hal_uwb_cal_3d_angle_by_pdoa_with_antenna_vertical_type3(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag)
{
    zn_cal_3d_angle_by_pdoa_with_antenna_vertical_type3(pdoa_sfd, pdoa_sts, azimuth_angle, elevation_angle, valid_flag);
}

void hal_uwb_cal_3d_angle_by_pdoa_with_antenna_vertical_type4(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag)
{
    zn_cal_3d_angle_by_pdoa_with_antenna_vertical_type4(pdoa_sfd, pdoa_sts, azimuth_angle, elevation_angle, valid_flag);
}

void hal_uwb_cal_3d_angle_by_pdoa_with_antenna_vertical_type5(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag)
{
    zn_cal_3d_angle_by_pdoa_with_antenna_vertical_type5(pdoa_sfd, pdoa_sts, azimuth_angle, elevation_angle, valid_flag);
}

void hal_uwb_cal_3d_angle_by_pdoa_with_antenna_vertical_type6(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag)
{
    zn_cal_3d_angle_by_pdoa_with_antenna_vertical_type6(pdoa_sfd, pdoa_sts, azimuth_angle, elevation_angle, valid_flag);
}

void hal_uwb_cal_3d_angle_by_pdoa_with_antenna_vertical_type7(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag)
{
    zn_cal_3d_angle_by_pdoa_with_antenna_vertical_type7(pdoa_sfd, pdoa_sts, azimuth_angle, elevation_angle, valid_flag);
}

double hal_uwb_get_frame_header_len(uint8_t preamble_duration, uint8_t sfd_id)
{
    uint16_t        preamble_len[9] = {16, 64, 1024, 4096, 32, 128, 256, 512, 2048};
    uint8_t         sfd_len[4]      = {8, 8, 16, 4};
    double          header_len      = {0};
    
    if((preamble_duration > PREAMBLE_2048) || (sfd_id > SFD_ID_USER16))
    {
        LOG_ERROR("error input paramater!");
        return 0.0;
    }
    
    header_len = (double)(preamble_len[preamble_duration] + sfd_len[sfd_id]) * UWB_SYMBLE_LEN;
    
    return header_len;
    
}

double hal_uwb_get_frame_payload_len(uint8_t psdu_rate, uint16_t payload_size)
{
    double  psdu_rate_m[5]  = {0.0, 0.85, 6.81, 2.72, 5.40};
    double  psdu_len        = {0};
    
    if((psdu_rate < PSDU_RATE_850) || (psdu_rate > PSDU_RATE_540))
    {
        LOG_ERROR("error input paramater!");
        return 0.0;
    }
    
    psdu_len = payload_size * 8 / psdu_rate_m[psdu_rate];
    
    return psdu_len;
}

void hal_uwb_check_and_restore_pll_clock(uint8_t channel)
{
    uint32_t pll_state            = 0;
    
    pll_state = hal_read_uwb_register(PLL_STATUS_ID) & PLL_STAT_MASK; 
    
    if(pll_state != PLL_STAT_MASK)
    {   
        zn_pll_calib(channel, 1);
        zn_calibration(channel, 1);
    }
}

void UWB_IRQHandler()
{
    #ifdef POWER_TEST
    uint32_t reg = sys_ctrl_read(UWB_CLK_ICG_REG);
    reg &= 0xffffefff;
    sys_ctrl_write(UWB_CLK_ICG_REG, reg);
    zn_soc_to_work_state();
    #endif
    zn_isr();
}

void hal_32k_calib(void){
    zn_32k_calib();
}

void hal_vga_calib(void){
    zn_vga_calib();
}
void hal_tia_calib(void){
    zn_tia_calib();
}
void hal_cfg_after_calib(void){
    zn_cfg_after_calib();
}

void hal_calib_reg_wr_rd_test(void){
    zn_calib_reg_wr_rd_test();
}

void hal_calib_word_map_check(void){
    zn_calib_word_map_check();
}

void hal_read_ana_reg_cfg(void){
    read_ana_reg_cfg();
}

void hal_fixed_ana_gain_cfg_rx0(uint32_t lna_case,uint32_t tia_case,uint32_t vga_case){
    zn_fixed_ana_gain_cfg_rx0(lna_case,tia_case,vga_case);
}
void hal_fixed_ana_gain_cfg_rx1(uint32_t lna_case,uint32_t tia_case,uint32_t vga_case){
    zn_fixed_ana_gain_cfg_rx1(lna_case,tia_case,vga_case);
}
void hal_fixed_gain_cfg_rx0(uint32_t lna_case,uint32_t tia_case,uint32_t vga_case){
    zn_fixed_gain_cfg_rx0(lna_case,tia_case,vga_case);
}
void hal_fixed_gain_cfg_rx1(uint32_t lna_case,uint32_t tia_case,uint32_t vga_case){
    zn_fixed_gain_cfg_rx1(lna_case,tia_case,vga_case);
}
void hal_fix_gain_calib_rx0(uint32_t lna_case,uint32_t tia_case,uint32_t vga_case){
    zn_fix_gain_calib_rx0(vga_case,lna_case,tia_case);
}
void hal_fix_gain_calib_rx1(uint32_t lna_case,uint32_t tia_case,uint32_t vga_case){
    zn_fix_gain_calib_rx1(vga_case,lna_case,tia_case);
}
void hal_read_rx0_lna_tia_vga(void){
    zn_read_rx0_lna_tia_vga();
}
void hal_read_rx1_lna_tia_vga(void){
    zn_read_rx1_lna_tia_vga();
}
void hal_get_rx0_dc(void){
    zn_get_rx0_dc();
}
void hal_get_rx1_dc(void){
    zn_get_rx1_dc();
}
void hal_scan_dc(void){
    zn_scan_dc();
}
void hal_vga_recalib_once_rx0(uint32_t lna_case,uint32_t tia_case,uint32_t vga_case){
    zn_vga_recalib_once_rx0(vga_case,lna_case,tia_case);
}
void hal_vga_recalib_once_rx1(uint32_t lna_case,uint32_t tia_case,uint32_t vga_case){
    zn_vga_recalib_once_rx1(vga_case,lna_case,tia_case);
}
void hal_clkpll_calib(void){
    zn_clkpll_calib();
}
void hal_rfpll_calib(void){
    zn_rfpll_calib();
}

uint16_t hal_uwb_get_sysmbol_num_from_premble_duration(uint8_t duration)
{
    uint16_t sysmbol_num = 0;
    
    sysmbol_num = zn_preamble_duration_to_preamble_symbol_num(duration);
    
    return sysmbol_num;
}

uint8_t hal_uwb_get_sysmbol_num_from_sfd(uint8_t sfd)
{
    uint8_t sysmbol_num = 0;
    
    sysmbol_num = zn_uci_sfd_id_to_sfd_symbol_num(sfd);
    
    return sysmbol_num;
}

uint8_t hal_uwb_get_cfg_channel_from_uci(uint8_t uci_channel)
{
    uint8_t channel_no = 0;
    
    channel_no = zn_uci_channel_num_to_zn_cfg(uci_channel);
    
    return channel_no;
}

uint8_t hal_uwb_get_cfg_sfd_from_uci(uint8_t uci_sfd)
{
    uint8_t sfd_id = 0;
    
    sfd_id = zn_uci_sfd_id_to_zn_cfg(uci_sfd);
    
    return sfd_id;
}

uint8_t hal_uwb_get_cfg_preamble_code_from_uci(uint8_t uci_preamble_code)
{
    uint8_t preamble_code = 0;
    
    preamble_code = zn_preamble_code_idx_to_zn_cfg(uci_preamble_code);
    
    return preamble_code;
}

void hal_uwb_switch_rx1_to_auto_gain()
{
    zn_clear_bit(0x1994,22);
}

void hal_uwb_soc_reset(void)
{
    sys_ctrl_write(SOC_CLK_CFG, 0x01);
    sys_ctrl_write(REG_GLB_SW_RST, 0xaa55);    
}