
/******************************************************************************
 *  File: hal_uwb.h
 *
 *  Description: this file contains the functions support uwb operations.
 *
 *  Copyright (C) : 2022 Hangzhou ultraception.com.
 *
 *  Author: sxg
 *  Date:   May 13 2025
 *
 *****************************************************************************/

#ifndef __HAL_UWB_H__
#define __HAL_UWB_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_soc.h"
#include "zn_gpio.h"
#include "zn_timer.h"
#include "zn_dca.h"
#include "zn_interface.h"
#include "zn_qspi_gd25q40.h"


#define US_TO_UWB_SYS_TIME(x)      (((x) * 1000) / 4.0064)  //uwb systcounter 1 means 4.0064ns
#define US_TO_UWB_TS_TIME(x)       (((x) * 1000000) / 15.65) //uwb timestamp counter 1 means 15.65ps
#define UWB_SYMBLE_LEN             (double)1.016 //uwb symble len unit us
#define DELAY_OFFSET 190 //unit us

#define MODE_BLOCK      (uint8_t)0
#define MODE_UNBLOCK    (uint8_t)1

#define US_TO_SYS(x)    ((x) * 249.6)
#define SYS_TO_US(x)    ((x) * 4.0064 / 1000)

#define CRC_LEN  2

#define ANT_TYPE_TRIANGLE    0x00
#define ANT_TYPE_RIGHT       0x01

#define PLL_STAT_MASK        0x01

#define UWB_TX_DONE_EVENT      SYS_STATUS_TXDONE_BIT_MASK
#define UWB_RX_OK_EVENT        SYS_STATUS_RXFCG_BIT_MASK
#define UWB_RX_ERROR_EVENT     SYS_STATUS_ALL_RX_ERR
#define UWB_RX_FINISH_EVENT    (SYS_STATUS_RXDONE_BIT_MASK | SYS_STATUS_ALL_RX_ERR | SYS_STATUS_ALL_RX_TO)
#define UWB_RX_TIMEOUT_EVENT   SYS_STATUS_ALL_RX_TO
#define UWB_RX_STS_ERROR_EVENT SYS_STATUS_RXSTSE_BIT_MASK


typedef struct hal_uwb_phy_config
{
    uint8_t           channel_num;         //3:ch5, 6:ch9 default:ch9 must be same with app_cfg.h
    uint8_t           frame_type;          //0:SP0, 1:SP1, 3:SP3; default:sp0
    uint8_t           frame_ext_en;        //0:normal frame mode, 1:extend frame mode
    uint8_t           preamble_code_idx;   //0:INDEX_9, 1:INDEX_10, ..., 31:INDEX_32; default:INDEX_10
    uint8_t           sfd_id;              //0:LEGACY_SFD8, 1:SFD8, 2:SFD16, SFD4; default:SFD8
    uint8_t           psdu_data_rate;      //1:850k, 2:6.81M, 3:27.2M; default:2
    uint8_t           bprf_phr_data_rate;  //0:850k; default:0
    uint8_t           preamble_duration;   //0:16,1:64,2:1024,3:4096,4:32,5:128,6:256,7:512,8:2048; default:1
    uint8_t           prf_mode;            //0:BPRF 62.4MHZ,1:HPRF 124.8MHZ,2:HPRF 249.6MHZ
    uint8_t           tia_level;           //0-5: tia gain level
    uint8_t           pa_level;            //pa level: PA_LEVEL_0 -PA_LEVEL_7
    uint8_t           sts_seg_num;         //0:SEG_1, 1:SEG_2, 2:SEG_3, 4:SEG_4; default:0
    uint16_t          sts_seg_len;         //16, 32, 64, 128;default:64
    uint16_t          sfd_to;              //set sfd timeout time which value is preamble_len + sfd_len
    uint16_t          ant_delay;           //antenna delay
    uint16_t          rx_ts_left_find_len; //rx timestamp retry function param left_find_len
    uint16_t          rx_ts_thresold_len;  //rx timestamp retry function param thresold_len
    uint32_t          tx_ts_offset;        //offset between delay tx time and tx timestamp
}hal_uwb_phy_config_t;

typedef union hal_uwb_interrupt_config
{
    uint32_t      interrupt_mask;
    struct{
        uint32_t  bit0_int_en    : 1;
        uint32_t  bit1_rsv       : 1;
        uint32_t  bit2_rsv       : 1;
        uint32_t  bit3_rsv       : 1;
        uint32_t  bit4_tx_frb    : 1;
        uint32_t  bit5_tx_prs    : 1;
        uint32_t  bit6_tx_phs    : 1;
        uint32_t  bit7_tx_frs    : 1;
        uint32_t  bit8_rx_prd    : 1;
        uint32_t  bit9_rx_sfdd   : 1;
        uint32_t  bit10_cia_done : 1;
        uint32_t  bit11_rx_phd   : 1;
        uint32_t  bit12_rx_phe   : 1;
        uint32_t  bit13_rx_dfr   : 1;
        uint32_t  bit14_rx_fcg   : 1;
        uint32_t  bit15_rx_fce   : 1;
        uint32_t  bit16_rx_fsl   : 1;
        uint32_t  bit17_rx_rfto  : 1;
        uint32_t  bit18_cia_err  : 1;
        uint32_t  bit19_mv_warn  : 1;
        uint32_t  bit20_rx_ovrr  : 1;
        uint32_t  bit21_rx_pto   : 1;
        uint32_t  bit22_lcss_err : 1;
        uint32_t  bit23_rsv      : 1;
        uint32_t  bit24_rsv      : 1;
        uint32_t  bit25_rsv      : 1;
        uint32_t  bit26_rx_sfdto : 1;
        uint32_t  bit27_hpd_warn : 1;
        uint32_t  bit28_rx_cperr : 1;
        uint32_t  bit29_affrej   : 1;
        uint32_t  bit30_rsv      : 1;
        uint32_t  bit31_rsv      : 1;
    }bits;        
}hal_uwb_interrupt_config_t;

typedef struct hal_uwb_interrupt_callback
{
    zn_cb_t             cb_tx_done;               // Callback for TX confirmation event
    zn_cb_t             cb_rx_ok;                 // Callback for RX good frame events
    zn_cb_t             cb_rx_timeout;            // Callback for RX timeout event
    zn_cb_t             cb_rx_err;                // Callback for RX error events
    zn_cb_t             cb_rx_done;               // Callback for RX done event
    zn_cb_t             cb_cp_err;                // Callback for RX sts error event
    zn_cb_t             cb_prd;                   // Callback for RX preamble done event
    zn_cb_t             cb_rx_preamble_timeout;   // Callback for RX preamble detect timeout event
    zn_cb_t             cb_rx_sfd_timeout;        // Callback for RX sfd detect timeout event
    zn_cb_t             cb_rx_sfd_done;           // Callback for RX sfd done event
    zn_cb_t             cb_rx_phr_err;            // Callback for RX phr error event
    zn_cb_t             cb_rx_phd;                // Callback for RX phr done event
}hal_uwb_interrupt_callback_t;


typedef struct hal_uwb_aoa_config
{
    uint8_t                 aoa_en;
    aoa_mode_e              aoa_mode;
    aoa_dimension_mode_e    aoa_dimension_mode;
    aoa_3d_ant_type_e       aoa_3d_ant_type;
    pdoa_ant_state_e        ant_sel;
    double                  phase_compen_rx0_rx1;
    double                  phase_compen_rx0_rx2;
    double                  ant_distance_rx0_rx1;
    double                  ant_distance_rx0_rx2;
    double                  ant_distance_rx1_rx2;
    int32_t                 delay_rx0_rx1;
}hal_uwb_aoa_config_t;

typedef struct hal_uwb_radar_config
{
    uint8_t     radar_en;
    uint8_t     dt;
    uint16_t    pulse_num;
    uint8_t     pulse_period ;
    uint8_t     pulse_position ;
    uint8_t     rx_gain_index ;
    uint32_t    frame_interval ;
    uint8_t     tap_len;  
    uint8_t     tap_start_idx; 
    uint8_t     tx_power_idx;  
    uint8_t     ant_type;           // 0: 1T1R 1:1T2R
    uint8_t     is_gain_cali_enable;
    uint8_t     step_temperature;
    
}hal_uwb_radar_config_t;
typedef struct hal_radar_old_cfg
{
    uint8_t     radar_en;
    uint8_t     pulse_type;
    uint16_t    tx_power_level;
    uint8_t     rx_gain_level;
    uint8_t     preamble_length;
    uint32_t    fp_threshold;
    uint8_t     cir_tap_len;
    uint16_t    frame_interval;
    uint16_t    acc_Threshold;
    uint8_t     user_algo_flag;
    uint8_t     win_leftLen;
    uint8_t     win_startshift;
    uint8_t     cir_type;    
    uint32_t    timeout;
    uint8_t     radar_ant_type;

}hal_uwb_radar_old_config_t;

typedef struct hal_uwb_fem_config
{
    uint8_t    fem_en;                  //0: disable, 1: enable
    uint8_t    fem_ctrl_mode;           //0: auto mode, 1: manual mode, SP0 aoa must be set to manual mode
    uint8_t    tx_en_pin_id;
    uint8_t    rx0_en_pin_id;
    uint8_t    rx1_en_pin_id;
    uint8_t    rx2_en_pin_id;
}hal_uwb_fem_config_t;



typedef struct hal_uwb_instance
{
    uint8_t                       rx_ts_retry_en;
    uint8_t                       rx_sfd_ts_flag;
    uint8_t                       rx2_sfd_ts_flag;
    uint8_t                       driver_timer_id;
    uint8_t                       delay_mode;
    hal_uwb_phy_config_t          phy_config;
    hal_uwb_interrupt_config_t    interrupt_config;
    hal_uwb_interrupt_callback_t  interrupt_callback;
    hal_uwb_aoa_config_t          aoa_config;
    hal_uwb_radar_config_t        radar_config;
    hal_uwb_radar_old_config_t    radar_old_config;
    hal_uwb_fem_config_t          fem_config;
}hal_uwb_instance_t;


typedef union
{
    double pdoa;
    double aoa;
}aoa_result_t;

typedef union
{
    uint8_t pdoa_flag;
    uint8_t aoa_flag;
}flag_result_t;

typedef struct hal_aoa_result
{
    aoa_result_t rlt1;
    aoa_result_t rlt2;
    flag_result_t flag1;
    flag_result_t flag2;
}hal_aoa_result_t;



inline __attribute__((always_inline)) void hal_write_uwb_register(uint32_t addr, uint32_t val)
{
    *(volatile uint32_t *)(UWB_BASE_ADDR + addr)= (volatile uint32_t)(val);
}

inline __attribute__((always_inline)) uint32_t hal_read_uwb_register(uint32_t addr)
{
    return *(volatile uint32_t *)(UWB_BASE_ADDR + addr);
}


uint64_t hal_get_tx_timestamp(void);
uint64_t hal_get_rx_timestamp(hal_uwb_instance_t * uwb_instance);
uint64_t hal_get_rx2_timestamp(hal_uwb_instance_t * uwb_instance);
void hal_uwb_config_init(hal_uwb_instance_t * uwb_instance);
ERROR_Type hal_uwb_immediate_tx(void);
ERROR_Type hal_uwb_delay_tx(uint32_t tx_delay_sys, hal_uwb_instance_t * uwb_instance);
ERROR_Type hal_uwb_rx_after_tx(uint32_t rx_after_tx_us);
ERROR_Type hal_uwb_rx_after_tx_delay(uint32_t tx_delay_sys, uint32_t rx_after_tx_time, hal_uwb_instance_t * uwb_instance);
ERROR_Type hal_uwb_immediate_rx(void);
ERROR_Type hal_uwb_delay_rx(uint32_t rx_delay_sys, hal_uwb_instance_t * uwb_instance);
void hal_uwb_tia_calc(void);
void hal_uwb_agc_one_time_clac_rx0(void);
void hal_uwb_agc_one_time_clac_rx1(void);
void hal_uwb_agc_auto_clac_rx0(void);
void hal_uwb_agc_auto_clac_rx1(void);
void hal_uwb_read_adc_mem(uint8_t mem_id);
void hal_uwb_read_cir_mem_rx0(void);
void hal_uwb_read_cir_mem_rx1(void);
void hal_uwb_read_sts_mem_rx0(void);
void hal_uwb_read_sts_mem_rx1(void);
void hal_uwb_agc_gain_mem_read(void);
void hal_uwb_show_rx0_info(void);
void hal_uwb_show_rx1_info(void);
void hal_read_uwb_mem(uint16_t addr, uint8_t* buffer, uint16_t len);
void hal_write_uwb_mem(uint16_t addr, uint8_t* buffer, uint16_t len);
void hal_force_uwb_off(void);
void hal_uwb_to_tx_state(void);
void hal_uwb_to_rx_state(void);
void hal_uwb_to_idle_state(void);
void hal_uwb_fem_to_tx_state(void);
void hal_uwb_fem_to_rx_state(void);
void hal_uwb_fem_to_idle_state(void);
void hal_uwb_set_rx_timeout(uint32_t time_us);
void hal_uwb_write_tx_buffer(uint8_t* buffer, uint16_t len);
void hal_uwb_read_rx_buffer(uint8_t* buffer, uint16_t len);
void hal_uwb_rx_antenna_switch(uint8_t ant_sel);
uint16_t hal_uwb_get_rx_data_len(void);
uint8_t hal_get_cur_channel(void);
uint32_t hal_get_cur_sys_time(void);
uint8_t hal_get_cur_frame_type(void);
double hal_uwb_get_freq_offset(void);
void hal_uwb_read_2d_pdoa_nlos_result(double *pdoa1, uint8_t *detectLevel);
void hal_uwb_read_2d_angle(double *pdoa, double *aoa, uint8_t *valid_flag);
void hal_uwb_cal_2d_angle_by_pdoa(double pdoa, double *aoa, uint8_t *valid_flag);
void hal_uwb_read_3d_pdoa_nlos_result(double *pdoa1, double *pdoa2, uint8_t *detectLevel);
void hal_uwb_read_3d_angle(double *pdoa_sfd, double *pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);
void hal_uwb_cal_3d_angle_by_pdoa_with_antenna_ceiling_type1(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);
void hal_uwb_cal_3d_angle_by_pdoa_with_antenna_ceiling_type2(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);
void hal_uwb_cal_3d_angle_by_pdoa_with_antenna_ceiling_type3(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);
void hal_uwb_cal_3d_angle_by_pdoa_with_antenna_vertical_type1(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);
void hal_uwb_cal_3d_angle_by_pdoa_with_antenna_vertical_type2(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);
void hal_uwb_cal_3d_angle_by_pdoa_with_antenna_vertical_type3(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);
void hal_uwb_cal_3d_angle_by_pdoa_with_antenna_vertical_type4(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);
void hal_uwb_cal_3d_angle_by_pdoa_with_antenna_vertical_type5(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);
void hal_uwb_cal_3d_angle_by_pdoa_with_antenna_vertical_type6(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);
void hal_uwb_cal_3d_angle_by_pdoa_with_antenna_vertical_type7(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);
double hal_uwb_get_frame_header_len(uint8_t preamble_duration, uint8_t sfd_id);
double hal_uwb_get_frame_payload_len(uint8_t psdu_rate, uint16_t payload_size);
void hal_uwb_check_and_restore_pll_clock(uint8_t channel);

void hal_32k_calib(void);
void hal_vga_calib(void);
void hal_tia_calib(void);
void hal_cfg_after_calib(void);
void hal_calib_reg_wr_rd_test(void);
void hal_calib_word_map_check(void);
void hal_read_ana_reg_cfg(void);
void hal_fixed_ana_gain_cfg_rx0(uint32_t lna_case,uint32_t tia_case,uint32_t vga_case);
void hal_fixed_ana_gain_cfg_rx1(uint32_t lna_case,uint32_t tia_case,uint32_t vga_case);
void hal_fixed_gain_cfg_rx0(uint32_t lna_case,uint32_t tia_case,uint32_t vga_case);
void hal_fixed_gain_cfg_rx1(uint32_t lna_case,uint32_t tia_case,uint32_t vga_case);
void hal_fix_gain_calib_rx0(uint32_t lna_case,uint32_t tia_case,uint32_t vga_case);
void hal_fix_gain_calib_rx1(uint32_t lna_case,uint32_t tia_case,uint32_t vga_case);
void hal_read_rx0_lna_tia_vga(void);
void hal_read_rx1_lna_tia_vga(void);
void hal_get_rx0_dc(void);
void hal_get_rx1_dc(void);
void hal_scan_dc(void);
void hal_vga_recalib_once_rx0(uint32_t lna_case,uint32_t tia_case,uint32_t vga_case);
void hal_vga_recalib_once_rx1(uint32_t lna_case,uint32_t tia_case,uint32_t vga_case);
void hal_clkpll_calib(void);
void hal_rfpll_calib(void);
void hal_uwb_set_frame_type(uint8_t frame_type);
void hal_uwb_set_rx_preamble(uint8_t sts_cfg, uint8_t preamble_duration);
void hal_uwb_param_update(zn_config_t *config, hal_uwb_instance_t *uwb_instance);
void hal_uwb_switch_rx1_to_auto_gain();
void hal_uwb_soc_reset(void);

#ifdef __cplusplus
}
#endif

#endif
