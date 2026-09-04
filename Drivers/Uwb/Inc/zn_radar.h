
/*****************************************************************************
* File: zn_radar.h
*
* Descirption: this file contains the functions support radar driver.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#ifndef __ZN_RADAR_H
#define __ZN_RADAR_H


#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "zn_soc.h"

/*two tx two rx*/
#define TRX_SWITCH GPIO_PIN12   
/*four tx four rx swich*/
#define  RX2_V1    GPIO_PIN14
#define  RX2_V2    GPIO_PIN12
#define  TRX_V1    GPIO_PIN9
#define  TRX_V2    GPIO_PIN11
#define RADAR_CIA_BASE_ADDR	 	0x20010000
typedef void (*zn_radar_data_cbk)(int32_t *buffer_I, int32_t *buffer_Q,uint8_t ant_num);
typedef struct zn_radar_config
{

    uint8_t                 ant_type;
    uint8_t                 start_idx;
    zn_radar_data_cbk     func;                
}zn_radar_config_t;

typedef struct zn_radar_driver_cfg
{
    uint16_t frame_interval;
    uint8_t tap_len;
    uint16_t pulse_num;
    uint8_t dt_config;
    uint16_t pulse_period;
    uint8_t rx_gain_idx;
    uint8_t tx_power_idx;
    uint8_t tap_start_idx;
    uint8_t ant_type;

    uint8_t is_gain_cali_enable;
    uint8_t step_temperature;
}zn_radar_driver_cfg_t;

typedef enum radar_ant_sel
{
    ANT_TX_SWITCH1_SEL,
    ANT_TX_SWITCH2_SEL,
    ANT_TX_SWITCH3_SEL,
    ANT_TX_SWITCH4_SEL,
    ANT_RX_SWITCH1_SEL,
    ANT_RX_SWITCH2_SEL,
    ANT_RX_SWITCH3_SEL,    
    ANT_RX_SWITCH4_SEL, 
    ANT_MAX,

}radar_ant_sel_t;
typedef enum radar_ant_mode_sel
{
    TX_SWTICH1_RX_SWITCH1,
    TX_SWTICH1_RX_SWITCH2,
    TX_SWTICH1_RX_SWITCH3,
    TX_SWTICH1_RX_SWITCH4,
    TX_SWTICH2_RX_SWITCH1,
    TX_SWTICH2_RX_SWITCH2,
    TX_SWTICH2_RX_SWITCH3,    
    TX_SWTICH2_RX_SWITCH4, 
    TX_SWTICH3_RX_SWITCH1,
    TX_SWTICH3_RX_SWITCH2,
    TX_SWTICH3_RX_SWITCH3,
    TX_SWTICH3_RX_SWITCH4,
    TX_SWTICH4_RX_SWITCH1,
    TX_SWTICH4_RX_SWITCH2,
    TX_SWTICH4_RX_SWITCH3,
    TX_SWTICH4_RX_SWITCH4,
    MAX_TX_RX_SWITCH_NUM,

}radar_ant_mode_sel_t;
typedef enum
{
    ONE_T_ONE_R_MODE,
    ONE_T_TWO_R_MODE,
    TWO_T_TWO_R_MODE,
    FOUR_T_FOUR_R_MODE,
}radar_mode_t;

typedef struct radar_rx_gain_index_cfg
{
    uint8_t lna_level;
    uint8_t tia_level;
    uint8_t vag_level;
}zn_radar_rx_gain_index_t;

typedef struct zn_radar_ant_status
{
    uint8_t    ant_seq;
    uint8_t    valid;
    uint8_t    pre_status;
}zn_radar_ant_status_t;

extern zn_radar_driver_cfg_t zn_radar_driver_cfg;
extern zn_radar_config_t zn_radar_cfg;
extern zn_radar_ant_status_t zn_radar_ant_switch_seq[MAX_TX_RX_SWITCH_NUM + 1];
/***************************************************************************************************
   radar interface
******************************************************************************************************/
void zn_set_radar_en();
void zn_set_radar_off();
void zn_set_radar_sys_ctrl_reg0(uint8_t dt,uint8_t chunk_num,uint8_t pulse_period);
void zn_set_radar_sys_ctrl_reg1(uint32_t chunkt);
void zn_set_radar_sys_ctrl_reg2(uint16_t pulse_num);
void zn_set_radar_tx_register(uint8_t clk_sel,uint8_t pulse_posiotn,uint8_t pulse_type,uint8_t swflg,uint8_t swdly);
void zn_set_radar_rx_peak_detection(uint8_t peak_phase_offset,uint8_t peak_dis_offset,uint8_t peak_phase_en,uint8_t peak_threshold,uint8_t peak_window,uint8_t peak_offset,uint8_t peak_detion_en);
void zn_set_radar_rx_ctrl_register(uint8_t tap_len,uint8_t acc_avge_num,uint8_t acc_avge_en,uint8_t adc_sel);
void zn_set_radar_rx_store_ctrl_register(uint8_t bit_width,uint8_t store_seq_mode,uint8_t store_mode);
void zn_set_radar_rx_ce_ctrl_register(uint8_t ce_tap_len,uint8_t ce_pulse_num,uint8_t ce_mode);
void zn_set_radar_rx_ce_ctrl_register1(uint8_t ce_gap_pulse_num,uint32_t mode_peak_threshold);
void zn_set_radar_int_mask(uint8_t avg_done,uint8_t over_flow_err,uint8_t collision_err,uint8_t radar_done_pulse,uint8_t chunk_done_puse);
void zn_set_radar_extend_ctrl_register(uint8_t rx_extend_flip_gap,uint8_t rx_extend_delay,uint8_t pulse_extend);
void zn_set_radar_extend_seq_register(uint16_t extend_seq);
void zn_set_radar_acc_data_disable_register(uint8_t p2s_en,uint8_t acc_data_disable);
void zn_radar_read_from_device(uint32_t reg_file_id, uint16_t length, uint8_t *buffer);
void zn_radar_antenna_switch(uint8_t ant_sel);
void zn_to_radar_trx_state(void);
typedef void (*radar_data_handler)(int32_t *buffer_I, int32_t *buffer_Q);
void zn_read_radar_cir_memory();
zn_radar_config_t* zn_radar_config_addr(void);
uint8_t zn_radar_calib(void);
void zn_radar_config(void);
zn_radar_driver_cfg_t *zn_radar_driver_config_addr();
void zn_radar_fixed_gain_cfg(uint8_t rx_gain_level);
void zn_radar_four_t_four_r_chan_set_pre_status(uint8_t seq,uint8_t status);
void zn_radar_four_t_r_mode_sel(uint8_t ant_mode);
uint8_t zn_radar_four_t_r_mode_find_first_valid_swtich(void);
void zn_radar_tx_power_rx_cali_check(double init_tmp,double curr_tmp,uint8_t temperature_step,uint8_t enable);
void zn_radar_tap_cali();
void zn_radar_start();
#endif