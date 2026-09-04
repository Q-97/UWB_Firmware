#ifndef _HAL_RADAR_H_
#define _HAL_RADAR_H_
#include "stdint.h"

#include "zn_radar.h"
#include "hal_uwb.h"

extern uint8_t g_radar_done_flag;


void hal_radar_init(hal_uwb_instance_t * uwb_instance);
void hal_radar_start();
void hal_radar_stop();
void hal_radar_timer_init();
void hal_radar_default_antanna_cfg();
void hal_radar_fixed_gain_cfg();
void hal_radar_single();
void hal_radar_tx_rx_check_by_temperature(double curr_tmp);

#endif