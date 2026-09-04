
/*****************************************************************************
* File: zn_regs_zn2014.h
*
* Descirption: this file contains the functions support driver regs.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#ifndef __ZN_RADAR_REG_H
#define __ZN_RADAR_REG_H
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct zn_radar_config
{

    uint8_t                 dt;
    uint8_t                 pulse_period;
//    uint16_t                pulse_num;
    uint8_t                 pulse_position;
    uint8_t                 tap_len;
    uint8_t                 start_idx;
    uint8_t                 rx_gain_index;    
}zn_radar_t;

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
void zn_radar_antenna_switch();
void zn_to_radar_trx_state(void);
typedef void (*radar_data_handler)(int32_t *buffer_I, int32_t *buffer_Q);
void zn_read_radar_cir_memory();

#endif