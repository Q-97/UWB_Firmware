/*****************************************************************************
* File: ds_twr.c
*
* Descirption: this file contains the functions support ds_twr ranging.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#include "gconfig.h"
#include "phy_cmd.h"
#include "phy_test.h"
#include "hal_uart.h"
#include "hal_gpio.h"
#include "hal_delay.h"
#include "hal_radar.h"
#include "user_app.h"
#include "hal_ant.h"

uint8_t     g_work_mode     = WORK_MODE_NULL;
uci_mode_t  g_uci_mode      = UCI_UART;//UCI_CAN  UCI_UART  UCI_NULL

hal_uwb_instance_t  uwb_instance = 
{
    .phy_config = 
    {
        .channel_num = CHANNEL_9,
        .frame_type = RFRAME_SP0,
        .preamble_code_idx = PREAMBLE_CODE_INDEX_10,
        .sfd_id = SFD_ID_SFD8,
        .psdu_data_rate= PSDU_RATE_681,
        .bprf_phr_data_rate = BPRF_PHR_RATE_850,
        .preamble_duration = PREAMBLE_512,
        .prf_mode = PRF_624,
        .tia_level = TIA_LEVEL_5,
        .pa_level = PA_LEVEL_15,
        .sts_seg_num = STS_SEG_1,
        .sts_seg_len = STS_SEG_LEN_64,
        .sfd_to = 512 + 8, //preamble len + sfd len
        .ant_delay = ANT_DELAY,
        .rx_ts_left_find_len = 70,
        .rx_ts_thresold_len = 200,
    },
    
    .aoa_config = 
    {
        .aoa_en = 1,
        .aoa_mode = TYPE_AOA,
        .aoa_dimension_mode = TYPE_3D,
        .ant_sel = RX2_INPUT,
        .phase_compen_rx0_rx1 = 0.0,
        .phase_compen_rx0_rx2 = 0.0,
        .ant_distance_rx0_rx1 = 1.8,
        .ant_distance_rx0_rx2 = 1.8,
        .delay_rx0_rx1 = 0,
    },
        
    .interrupt_config = 
    {
        .bits.bit0_int_en = 1,
        .bits.bit7_tx_frs = 1,
        .bits.bit8_rx_prd = 1,
        .bits.bit14_rx_fcg = 1,
        .bits.bit13_rx_dfr = 1,
        .bits.bit28_rx_cperr = 1,
        .bits.bit17_rx_rfto = 1,
        .bits.bit26_rx_sfdto = 1,
    },
    
    .radar_config = 
    {
        .radar_en = 1,
        .tap_len = 16,
        .frame_interval = 100,
        .pulse_num = 0x7fff,        
        .pulse_period = 0x09,
        .rx_gain_index = 25, 
        .tx_power_idx = PA_LEVEL_12,    
        .tap_start_idx = 6, 
        .ant_type = FOUR_T_FOUR_R_MODE,
         
    },

    
    .delay_mode = MODE_UNBLOCK,
    .driver_timer_id = TIMER0
};


