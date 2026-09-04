#include <stdio.h>
#include <string.h>
#include "zn_interface.h"
#include "zn_soc.h"
#include "math.h"
#include "zn_radar.h"
#include "hal_radar.h"
#include "hal_gp_timer.h"
#include "hal_uwb.h"
#include "zn_radar_reg.h"
#include "hal_gpio.h"
#include "zn_radar.h"
#include "hal_ant.h"
#include "gconfig.h" 
#include "math.h"
#include "hal_sleep.h"
#include "hal_adc.h"
#include "hal_dca.h"

extern uint8_t g_radar_done_flag;
extern uint8_t g_ant_id;
uint8_t g_read_start_idx = 0;
uint32_t g_pulse_num_scale = 0;
double g_start_temperature = 40;
extern void user_radar_call_back(int32_t *buffer_i,int32_t *buffer_q,uint8_t ant_id);
extern uint8_t g_radar_cali_flag;
double g_init_tmp = 0;
uint8_t g_tx_power = 0;
static uint8_t g_vaild_port_num = 1;

uint16_t g_delta_time_ms = 2100;  
void hal_radar_para_cfg_update(hal_uwb_instance_t * uwb_instance)
{
    uint8_t flag = 0;
    zn_radar_config_t* zn_radar_cfg = zn_radar_config_addr();
    //zn_radar_driver_cfg_t *zn_radar_driver_cfg = zn_radar_driver_config_addr();
    
    zn_radar_driver_cfg.dt_config      = uwb_instance->radar_config.dt;
    zn_radar_driver_cfg.pulse_period   = uwb_instance->radar_config.pulse_period;
    zn_radar_driver_cfg.pulse_period   = 0x09;
    zn_radar_driver_cfg.rx_gain_idx    = uwb_instance->radar_config.rx_gain_index;
    zn_radar_driver_cfg.tap_start_idx  = uwb_instance->radar_config.tap_start_idx;
    zn_radar_driver_cfg.tx_power_idx   = uwb_instance->radar_config.tx_power_idx;
    zn_radar_driver_cfg.is_gain_cali_enable = uwb_instance->radar_config.is_gain_cali_enable;
    zn_radar_driver_cfg.step_temperature = uwb_instance->radar_config.step_temperature;
    
    dca_write(0,0); 
    if((g_init_tmp > g_start_temperature)&& (zn_radar_driver_cfg.is_gain_cali_enable == TRUE))
    {
        zn_radar_driver_cfg.tx_power_idx = zn_radar_driver_cfg.tx_power_idx + 1;
        dca_write(0,0x5a); 
    }        
    zn_radar_driver_cfg.frame_interval = uwb_instance->radar_config.frame_interval;
    zn_radar_driver_cfg.tap_len        = uwb_instance->radar_config.tap_len;
    zn_radar_driver_cfg.pulse_num      = uwb_instance->radar_config.pulse_num;   
    zn_radar_driver_cfg.ant_type     = uwb_instance->radar_config.ant_type;
    g_pulse_num_scale = (uint32_t)(log2(zn_radar_driver_cfg.pulse_num + 1));
    zn_radar_cfg->start_idx = zn_radar_driver_cfg.tap_start_idx;
    zn_radar_cfg->ant_type = zn_radar_driver_cfg.ant_type;
    zn_radar_cfg->func = user_radar_call_back;
    
    g_delta_time_ms = g_delta_time_ms + (zn_radar_driver_cfg.pulse_period - 2)*200;

}


void hal_radar_cfg(void)
{
    uint32_t reg0828 = zn_read_32bit_reg(0x0828);
    reg0828 |= 0x06ff;
    uint8_t calib_suc_flag;

    zn_pa_set(zn_radar_driver_cfg.tx_power_idx);
    
    zn_write_32bit_reg(0x0828, reg0828);//close rx0 for low power
    
    calib_suc_flag = zn_radar_calib();
    
    if(calib_suc_flag == FALSE)
    {
        hal_uwb_soc_reset();
    }

    g_radar_cali_flag = TRUE;
    
    g_read_start_idx += zn_radar_driver_cfg.tap_start_idx; 
    
    zn_radar_tap_cali(); 
}


void hal_radar_start(void)
{
    zn_to_radar_trx_state();
    g_radar_done_flag = 0;
    zn_radar_start();    
}

void hal_radar_stop(void)
{
    g_radar_done_flag = 0;
    zn_set_radar_off();  
    hal_gp_timer_close(TIMER1);
    hal_uwb_switch_rx1_to_auto_gain();
}

void hal_radar_timer_irq_proc(void)
{
    uint8_t seq = 0xff;
    if(zn_radar_driver_cfg.ant_type == FOUR_T_FOUR_R_MODE)
    {
        seq = zn_radar_four_t_r_mode_find_first_valid_swtich();
        if(seq == 0xff )
        {
            LOG_ERROR("no valid ant,switch default ant id 0");
            seq = 0;
        }
        zn_radar_four_t_four_r_chan_set_pre_status(seq,TRUE);
        zn_radar_four_t_r_mode_sel(seq); 
        g_ant_id = seq;
    }
    hal_radar_start();
}

void hal_radar_timer_init(void)
{
    hal_gp_timer_t timer_cfg = {0}; 
    uint32_t time1 = 0;
    
    timer_cfg.timer_id = TIMER1;
    timer_cfg.clk_src = PLL_CLK;
    timer_cfg.clk_div = 0;
    timer_cfg.mode = TIMER_USER_DEFINE;
    timer_cfg.interrupt_en = 1;
    if(g_vaild_port_num >1)
    {
        time1 = (uint32_t)(zn_radar_driver_cfg.frame_interval*1000) - g_delta_time_ms * g_vaild_port_num;
       
    }
    else
    {
        time1 = (uint32_t)(zn_radar_driver_cfg.frame_interval*1000);
    }
    timer_cfg.time1 = time1;
    timer_cfg.func = (TIMER_CallbackType)&hal_radar_timer_irq_proc;
    
    hal_gp_timer_init(&timer_cfg);
    hal_gp_timer_start(TIMER1);
}

void hal_radar_default_antanna_cfg(void)
{
    zn_radar_antenna_switch(RX2_INPUT);
}

void hal_radar_fixed_gain_cfg(void)
{
    zn_radar_fixed_gain_cfg(zn_radar_driver_cfg.rx_gain_idx);
}

void hal_radar_init_temperature(void)
{
    for(uint8_t i = 0; i < 10; i++)
    {
        g_init_tmp = hal_adc_get_cur_temperature();
    }
    printf("init_tmp = %.2f\r\n",g_init_tmp);
}

void hal_radar_tx_rx_check_by_temperature(double curr_tmp)
{
    zn_radar_tx_power_rx_cali_check(g_init_tmp,curr_tmp,zn_radar_driver_cfg.step_temperature,zn_radar_driver_cfg.is_gain_cali_enable);
}

void hal_radar_init(hal_uwb_instance_t * uwb_instance)
{
    
    uint32_t tmp = 0;
    
    hal_radar_init_temperature();    
    
    hal_radar_para_cfg_update(uwb_instance);   

    if(uwb_instance->radar_config.ant_type ==  FOUR_T_FOUR_R_MODE)
    {
        hal_ant_four_t_r_mode_ant_gpio_init();
        g_vaild_port_num = hal_ant_get_four_t_four_r_valid_ant_num();
    }
    else if(uwb_instance->radar_config.ant_type == TWO_T_TWO_R_MODE)
    {
        hal_ant_two_t_two_r_ant_init();
        g_vaild_port_num = 4;
    }
    hal_radar_fixed_gain_cfg();
    
    hal_radar_default_antanna_cfg();
           
    hal_radar_cfg();
             
}



void RADAR_IRQHandler()
{
   zn_radar_isr();
    
}
