#include "cali_reg.h"
FileConfig reg08_ana_xo_enable = {
.baseAddress = 0x081C,
.baseOffset = 8U,
.baseLength = 1U,
};
FileConfig reg08_ana_clkpll_enable = {
.baseAddress = 0x081C,
.baseOffset = 7U,
.baseLength = 1U,
};
FileConfig reg08_ana_rfpll_enable = {
.baseAddress = 0x081C,
.baseOffset = 6U,
.baseLength = 1U,
};
FileConfig reg08_ana_rx_enable = {
.baseAddress = 0x081C,
.baseOffset = 5U,
.baseLength = 1U,
};
FileConfig reg08_ana_tx_enable = {
.baseAddress = 0x081C,
.baseOffset = 4U,
.baseLength = 1U,
};
FileConfig reg08_dout_rfpll_vcocal7b_enable = {
.baseAddress = 0x081C,
.baseOffset = 3U,
.baseLength = 1U,
};
FileConfig reg08_dout_clkpll_vcocal5b_enable = {
.baseAddress = 0x081C,
.baseOffset = 2U,
.baseLength = 1U,
};
FileConfig reg08_dout_rfpllcal_lock_det = {
.baseAddress = 0x081C,
.baseOffset = 1U,
.baseLength = 1U,
};
FileConfig reg08_dout_clkpll_lock_det = {
.baseAddress = 0x081C,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg08_d_clkpll_ndiv = {
.baseAddress = 0x0800,
.baseOffset = 28U,
.baseLength = 4U,
};
FileConfig reg08_d_rfpll_enablemode_reg_overwrite = {
.baseAddress = 0x0800,
.baseOffset = 27U,
.baseLength = 1U,
};
FileConfig reg08_d_xo_ldo_vout_sel = {
.baseAddress = 0x0800,
.baseOffset = 24U,
.baseLength = 3U,
};
FileConfig reg08_d_dff_rstn_sel = {
.baseAddress = 0x0800,
.baseOffset = 23U,
.baseLength = 1U,
};
FileConfig reg08_d_xo_swc_o = {
.baseAddress = 0x0800,
.baseOffset = 16U,
.baseLength = 6U,
};
FileConfig reg08_d_clkpll_cp_ibias = {
.baseAddress = 0x0800,
.baseOffset = 14U,
.baseLength = 2U,
};
FileConfig reg08_d_xo_swf = {
.baseAddress = 0x0800,
.baseOffset = 8U,
.baseLength = 6U,
};
FileConfig reg08_d_clkpll_cp_iout_sel = {
.baseAddress = 0x0800,
.baseOffset = 6U,
.baseLength = 2U,
};
FileConfig reg08_d_xo_swc_i = {
.baseAddress = 0x0800,
.baseOffset = 0U,
.baseLength = 6U,
};
FileConfig reg08_otp_sel = {
 .baseAddress = 0x0804,
.baseOffset = 28U,
.baseLength = 4U,
};
FileConfig reg08_d_xo_loop_force_dis = {
.baseAddress = 0x0804,
.baseOffset = 23U,
.baseLength = 1U,
};
FileConfig reg08_d_xo_sucntred = {
.baseAddress = 0x0804,
.baseOffset = 22U,
.baseLength = 1U,
};
FileConfig reg08_d_clkpll_cp_en = {
.baseAddress = 0x0804,
.baseOffset = 20U,
.baseLength = 1U,
};
FileConfig reg08_d_clkpll_fbdiven = {
.baseAddress = 0x0804,
.baseOffset = 19U,
.baseLength = 1U,
};
FileConfig reg08_d_clkpll_fbdivrstn = {
.baseAddress = 0x0804,
.baseOffset = 18U,
.baseLength = 1U,
};
FileConfig reg08_d_clkpll_fbdivtsten = {
.baseAddress = 0x0804,
.baseOffset = 17U,
.baseLength = 1U,
};
FileConfig reg08_d_clkpll_pfd_cal_en = {
.baseAddress = 0x0804,
.baseOffset = 16U,
.baseLength = 1U,
};
FileConfig reg08_d_clkpll_pfd_en = {
.baseAddress = 0x0804,
.baseOffset = 15U,
.baseLength = 1U,
};
FileConfig reg08_d_clkpll_pfd_frcupdn = {
.baseAddress = 0x0804,
.baseOffset = 13U,
.baseLength = 2U,
};
FileConfig reg08_d_rfpll_analog_calibration_decoder_en = {
.baseAddress = 0x0804,
.baseOffset = 12U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_bwcal_frcupdn = {
.baseAddress = 0x0804,
.baseOffset = 10U,
.baseLength = 2U,
};
FileConfig reg08_d_rfpll_cp_amp_en = {
.baseAddress = 0x0804,
.baseOffset = 9U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_cp_current_sel_reg_overwrite = {
.baseAddress = 0x0804,
.baseOffset = 8U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_cp_en = {
.baseAddress = 0x0804,
.baseOffset = 7U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_div2_buf_en = {
.baseAddress = 0x0804,
.baseOffset = 6U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_div2_decoder_en = {
.baseAddress = 0x0804,
.baseOffset = 5U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_div2_en = {
.baseAddress = 0x0804,
.baseOffset = 4U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_cp_current_sel_reg = {
.baseAddress = 0x0804,
.baseOffset = 0U,
.baseLength = 4U,
};
FileConfig reg08_d_clkpll_ldo_vout_sel = {
.baseAddress = 0x0808,
.baseOffset = 27U,
.baseLength = 3U,
};
FileConfig reg08_d_clkpll_pfdpol = {
.baseAddress = 0x0808,
.baseOffset = 26U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_fbdiv_ldo_vout_sel = {
.baseAddress = 0x0808,
.baseOffset = 23U,
.baseLength = 3U,
};
FileConfig reg08_d_rfpll_div2_vb2_din = {
.baseAddress = 0x0808,
.baseOffset = 19U,
.baseLength = 4U,
};
FileConfig reg08_d_rfpll_div2_vb1_din = {
.baseAddress = 0x0808,
.baseOffset = 15U,
.baseLength = 4U,
};
FileConfig reg08_d_rfpll_div2_ibias_5uA_1 = {
.baseAddress = 0x0808,
.baseOffset = 13U,
.baseLength = 2U,
};
FileConfig reg08_d_rfpll_analog_calibration_vref_h_din = {
.baseAddress = 0x0808,
.baseOffset = 10U,
.baseLength = 3U,
};
FileConfig reg08_d_rfpll_analog_calibration_vref_l_din = {
.baseAddress = 0x0808,
.baseOffset = 7U,
.baseLength = 3U,
};
FileConfig reg08_d_rfpll_cp_amp_drive_increase = {
.baseAddress = 0x0808,
.baseOffset = 6U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_cp_ibias_sel = {
.baseAddress = 0x0808,
.baseOffset = 3U,
.baseLength = 3U,
};
FileConfig reg08_d_rfpll_cpldo_vout_sel = {
.baseAddress = 0x0808,
.baseOffset = 0U,
.baseLength = 3U,
};
FileConfig reg08_d_mixer_bias_trim_2nd = {
.baseAddress = 0x080C,
.baseOffset = 27U,
.baseLength = 3U,
};
FileConfig reg08_d_lna_ldo2_vout_sel_2nd = {
.baseAddress = 0x080C,
.baseOffset = 24U,
.baseLength = 3U,
};
FileConfig reg08_d_rfpll_div2_ibias_en = {
.baseAddress = 0x080C,
.baseOffset = 23U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_div2_res_sel_reg_overwrite = {
.baseAddress = 0x080C,
.baseOffset = 22U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_fbdiv_en = {
.baseAddress = 0x080C,
.baseOffset = 21U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_fbdiv_ldo_en = {
.baseAddress = 0x080C,
.baseOffset = 20U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_fbdiv_rstn = {
.baseAddress = 0x080C,
.baseOffset = 19U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_fbdiv_tsten = {
.baseAddress = 0x080C,
.baseOffset = 18U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_hc_ibias_reg_overwrite = {
.baseAddress = 0x080C,
.baseOffset = 17U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_lockdet_decoder_en = {
.baseAddress = 0x080C,
.baseOffset = 16U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_lockdet_rstn = {
.baseAddress = 0x080C,
.baseOffset = 15U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_lpf_tsten = {
.baseAddress = 0x080C,
.baseOffset = 14U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_pfd_bwcalen = {
.baseAddress = 0x080C,
.baseOffset = 13U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_pfd_en = {
.baseAddress = 0x080C,
.baseOffset = 12U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_vcobias_en = {
.baseAddress = 0x080C,
.baseOffset = 11U,
.baseLength = 1U,
};
FileConfig reg08_d_main_bg_force_off_1p1 = {
.baseAddress = 0x080C,
.baseOffset = 10U,
.baseLength = 1U,
};
FileConfig reg08_d_ldoh1p8_bleeder_off_1p1 = {
.baseAddress = 0x080C,
.baseOffset = 9U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_vcobuf_en = {
.baseAddress = 0x080C,
.baseOffset = 8U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_vcoldo_en = {
.baseAddress = 0x080C,
.baseOffset = 7U,
.baseLength = 1U,
};
FileConfig reg08_d_lna_ldo_en = {
.baseAddress = 0x080C,
.baseOffset = 6U,
.baseLength = 1U,
};
FileConfig reg08_d_clkpll_vco_core_en = {
.baseAddress = 0x080C,
.baseOffset = 4U,
.baseLength = 1U,
};
FileConfig reg08_d_efuse_vref_sel_1p1 = {
.baseAddress = 0x080C,
.baseOffset = 0U,
.baseLength = 2U,
};
FileConfig reg08_d_rfpll_sd_ndiv = {
.baseAddress = 0x0810,
.baseOffset = 24U,
.baseLength = 8U,
};
FileConfig reg08_d_rfpll_vcoldo_vout_sel = {
.baseAddress = 0x0810,
.baseOffset = 21U,
.baseLength = 3U,
};
FileConfig reg08_d_rfpll_lpf_highorder_cap_sel = {
.baseAddress = 0x0810,
.baseOffset = 18U,
.baseLength = 3U,
};
FileConfig reg08_d_rfpll_pfd_rstdelay = {
.baseAddress = 0x0810,
.baseOffset = 16U,
.baseLength = 2U,
};
FileConfig reg08_d_rfpll_vco_ct = {
.baseAddress = 0x0810,
.baseOffset = 9U,
.baseLength = 7U,
};
FileConfig reg08_d_rfpll_pfd_pol = {
.baseAddress = 0x0810,
.baseOffset = 8U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_lockdet_delay = {
.baseAddress = 0x0810,
.baseOffset = 5U,
.baseLength = 3U,
};
FileConfig reg08_d_rfpll_div2_ibias_15uA = {
.baseAddress = 0x0810,
.baseOffset = 2U,
.baseLength = 3U,
};
FileConfig reg08_d_rfpll_vco_ibias_var = {
.baseAddress = 0x0810,
.baseOffset = 0U,
.baseLength = 2U,
};
FileConfig reg08_d_mixer_bias_trim = {
.baseAddress = 0x0814,
.baseOffset = 29U,
.baseLength = 3U,
};
FileConfig reg08_d_lna_ldo1_vout_sel = {
.baseAddress = 0x0814,
.baseOffset = 26U,
.baseLength = 3U,
};
FileConfig reg08_d_rfpll_vcobuf_driver = {
.baseAddress = 0x0814,
.baseOffset = 24U,
.baseLength = 2U,
};
FileConfig reg08_d_lna_stage2_vcm_sel = {
.baseAddress = 0x0814,
.baseOffset = 21U,
.baseLength = 3U,
};
FileConfig reg08_d_lna_stage1_vcm_sel = {
.baseAddress = 0x0814,
.baseOffset = 18U,
.baseLength = 3U,
};
FileConfig reg08_d_rfpll_div2_ibias_5uA_2 = {
.baseAddress = 0x0814,
.baseOffset = 16U,
.baseLength = 2U,
};
FileConfig reg08_d_rfpll_vco_kvco = {
.baseAddress = 0x0814,
.baseOffset = 12U,
.baseLength = 4U,
};
FileConfig reg08_d_rfpll_lpf_res_sel = {
.baseAddress = 0x0814,
.baseOffset = 10U,
.baseLength = 2U,
};
FileConfig reg08_d_rfpll_lpf_third_cap_sel = {
.baseAddress = 0x0814,
.baseOffset = 8U,
.baseLength = 2U,
};
FileConfig reg08_d_rfpll_vcoldo_endly = {
.baseAddress = 0x0814,
.baseOffset = 7U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_vco_icore = {
.baseAddress = 0x0814,
.baseOffset = 0U,
.baseLength = 7U,
};
FileConfig reg08_d_lna_ldo_endly = {
.baseAddress = 0x0818,
.baseOffset = 31U,
.baseLength = 1U,
};
FileConfig reg08_d_lna_stage2_agc = {
.baseAddress = 0x0818,
.baseOffset = 29U,
.baseLength = 2U,
};
FileConfig reg08_d_i_tia_fb_cap = {
.baseAddress = 0x0818,
.baseOffset = 24U,
.baseLength = 5U,
};
FileConfig reg08_d_lna_fast_charge = {
.baseAddress = 0x0818,
.baseOffset = 23U,
.baseLength = 1U,
};
FileConfig reg08_d_i_tia_stag1_isel = {
.baseAddress = 0x0818,
.baseOffset = 21U,
.baseLength = 2U,
};
FileConfig reg08_d_i_tia_stg1_itrim = {
.baseAddress = 0x0818,
.baseOffset = 18U,
.baseLength = 3U,
};
FileConfig reg08_d_i_tia_vcm_sel = {
.baseAddress = 0x0818,
.baseOffset = 15U,
.baseLength = 3U,
};
FileConfig reg08_d_i_tia_fb_res = {
.baseAddress = 0x0818,
.baseOffset = 10U,
.baseLength = 5U,
};
FileConfig reg08_d_clkpll_ld_delay_sel = {
.baseAddress = 0x0818,
.baseOffset = 7U,
.baseLength = 3U,
};
FileConfig reg08_d_rfpll_vcocal7b_enable = {
.baseAddress = 0x0818,
.baseOffset = 6U,
.baseLength = 1U,
};
FileConfig reg08_d_clkpll_vcocal5b_enable = {
.baseAddress = 0x0818,
.baseOffset = 5U,
.baseLength = 1U,
};
FileConfig reg08_d_clkpll_lock_det_force_hi = {
.baseAddress = 0x0818,
.baseOffset = 4U,
.baseLength = 1U,
};
FileConfig reg08_d_pll_atest_en = {
.baseAddress = 0x0818,
.baseOffset = 3U,
.baseLength = 1U,
};
FileConfig reg08_d_pll_atest_sel = {
.baseAddress = 0x0818,
.baseOffset = 0U,
.baseLength = 3U,
};
FileConfig reg08_d_i_vga_dcoc_sel_pn_1 = {
.baseAddress = 0x0820,
.baseOffset = 24U,
.baseLength = 7U,
};
FileConfig reg08_d_q_tia_vcm_sel = {
.baseAddress = 0x0820,
.baseOffset = 21U,
.baseLength = 3U,
};
FileConfig reg08_d_q_tia_fb_cap = {
.baseAddress = 0x0820,
.baseOffset = 16U,
.baseLength = 5U,
};
FileConfig reg08_d_q_tia_fb_res = {
.baseAddress = 0x0820,
.baseOffset = 11U,
.baseLength = 5U,
};
FileConfig reg08_d_q_vga_dcoc_sel_nn_2_2nd = {
.baseAddress = 0x0820,
.baseOffset = 1U,
.baseLength = 7U,
};
FileConfig reg08_d_rx_rf_iref_en = {
.baseAddress = 0x0820,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_vco_core_en = {
.baseAddress = 0x0824,
.baseOffset = 31U,
.baseLength = 1U,
};
FileConfig reg08_d_tx_mode_sel = {
.baseAddress = 0x0824,
.baseOffset = 30U,
.baseLength = 1U,
};
FileConfig reg08_d_tx_dco_ldo_v1p2_sel = {
.baseAddress = 0x0824,
.baseOffset = 27U,
.baseLength = 3U,
};
FileConfig reg08_d_tx_main_ldo_v1p2_sel = {
.baseAddress = 0x0824,
.baseOffset = 24U,
.baseLength = 3U,
};
FileConfig reg08_d_tx_pa_cw_out = {
.baseAddress = 0x0824,
.baseOffset = 23U,
.baseLength = 1U,
};
FileConfig reg08_d_tx_pa_phase_swap = {
.baseAddress = 0x0824,
.baseOffset = 22U,
.baseLength = 1U,
};
FileConfig reg08_d_tx_dco_loop_dly_ctrl = {
.baseAddress = 0x0824,
.baseOffset = 16U,
.baseLength = 3U,
};
FileConfig reg08_d_tx_dco_pfd_dly_ctrl = {
.baseAddress = 0x0824,
.baseOffset = 13U,
.baseLength = 3U,
};
FileConfig reg08_d_tx_dco_vbn_bypass = {
.baseAddress = 0x0824,
.baseOffset = 12U,
.baseLength = 1U,
};
FileConfig reg08_d_tx_atest = {
.baseAddress = 0x0824,
.baseOffset = 10U,
.baseLength = 2U,
};
FileConfig reg08_d_tx_atest_en = {
.baseAddress = 0x0824,
.baseOffset = 9U,
.baseLength = 1U,
};
FileConfig reg08_d_tx_rstn_sel = {
.baseAddress = 0x0824,
.baseOffset = 8U,
.baseLength = 1U,
};
FileConfig reg08_d_tx_dco_vbn_rdac = {
.baseAddress = 0x0824,
.baseOffset = 0U,
.baseLength = 8U,
};
FileConfig reg08_d_q_adc_vref_tune_ch1_03_2nd = {
.baseAddress = 0x0828,
.baseOffset = 28U,
.baseLength = 3U,
};
FileConfig reg08_d_q_adc_vref_tune_ch1_04_2nd = {
.baseAddress = 0x0828,
.baseOffset = 25U,
.baseLength = 3U,
};
FileConfig reg08_d_q_tia_stag1_isel = {
.baseAddress = 0x0828,
.baseOffset = 23U,
.baseLength = 2U,
};
FileConfig reg08_d_xo_ibias_sel = {
.baseAddress = 0x0828,
.baseOffset = 20U,
.baseLength = 3U,
};
FileConfig reg08_d_main_bg_rtuning_1p1 = {
.baseAddress = 0x0828,
.baseOffset = 17U,
.baseLength = 3U,
};
FileConfig reg08_d_rfpll_iq_buffer_en = {
.baseAddress = 0x0828,
.baseOffset = 16U,
.baseLength = 1U,
};
FileConfig reg08_d_rx_bias_force_on = {
.baseAddress = 0x0828,
.baseOffset = 15U,
.baseLength = 1U,
};
FileConfig reg08_d_rx_ldo_lpf_force_on = {
.baseAddress = 0x0828,
.baseOffset = 14U,
.baseLength = 1U,
};
FileConfig reg08_d_aoa_mode_sel = {
.baseAddress = 0x0828,
.baseOffset = 13U,
.baseLength = 1U,
};
FileConfig reg08_d_rx_ldo_force_on_ch1 = {
.baseAddress = 0x0828,
.baseOffset = 12U,
.baseLength = 1U,
};
FileConfig reg08_d_rx_block_force_on_ch1 = {
.baseAddress = 0x0828,
.baseOffset = 11U,
.baseLength = 1U,
};
FileConfig reg08_d_lna_force_on_ch1 = {
.baseAddress = 0x0828,
.baseOffset = 10U,
.baseLength = 1U,
};
FileConfig reg08_d_mixer_force_on_ch1 = {
.baseAddress = 0x0828,
.baseOffset = 9U,
.baseLength = 1U,
};
FileConfig reg08_d_rx_lo_force_on_ch1 = {
.baseAddress = 0x0828,
.baseOffset = 8U,
.baseLength = 1U,
};
FileConfig reg08_d_i_tia_force_on_ch1 = {
.baseAddress = 0x0828,
.baseOffset = 7U,
.baseLength = 1U,
};
FileConfig reg08_d_i_vga_force_on_ch1 = {
.baseAddress = 0x0828,
.baseOffset = 6U,
.baseLength = 1U,
};
FileConfig reg08_d_i_adc_refgen_force_on_ch1 = {
.baseAddress = 0x0828,
.baseOffset = 5U,
.baseLength = 1U,
};
FileConfig reg08_d_i_adc_force_on_ch1 = {
.baseAddress = 0x0828,
.baseOffset = 4U,
.baseLength = 1U,
};
FileConfig reg08_d_q_tia_force_on_ch1 = {
.baseAddress = 0x0828,
.baseOffset = 3U,
.baseLength = 1U,
};
FileConfig reg08_d_q_vga_force_on_ch1 = {
.baseAddress = 0x0828,
.baseOffset = 2U,
.baseLength = 1U,
};
FileConfig reg08_d_q_adc_refgen_force_on_ch1 = {
.baseAddress = 0x0828,
.baseOffset = 1U,
.baseLength = 1U,
};
FileConfig reg08_d_q_adc_force_on_ch1 = {
.baseAddress = 0x0828,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg08_d_i_vga_dcoc_comp_en = {
.baseAddress = 0x082C,
.baseOffset = 31U,
.baseLength = 1U,
};
FileConfig reg08_d_q_adc_vref_tune_ch1_05_2nd = {
.baseAddress = 0x082C,
.baseOffset = 28U,
.baseLength = 3U,
};
FileConfig reg08_d_q_vga_dcoc_comp_en = {
.baseAddress = 0x082C,
.baseOffset = 23U,
.baseLength = 1U,
};
FileConfig reg08_d_i_vga_en = {
.baseAddress = 0x082C,
.baseOffset = 22U,
.baseLength = 1U,
};
FileConfig reg08_d_tia_ldo_vout_sel = {
.baseAddress = 0x082C,
.baseOffset = 19U,
.baseLength = 3U,
};
FileConfig reg08_d_i_vga_vcm_sel = {
.baseAddress = 0x082C,
.baseOffset = 16U,
.baseLength = 3U,
};
FileConfig reg08_d_ldol_dsm_mode_sel_1p1 = {
.baseAddress = 0x082C,
.baseOffset = 15U,
.baseLength = 1U,
};
FileConfig reg08_d_q_vga_vcm_sel = {
.baseAddress = 0x082C,
.baseOffset = 11U,
.baseLength = 3U,
};
FileConfig reg08_d_i_vga_vcm_sel_2nd = {
.baseAddress = 0x082C,
.baseOffset = 8U,
.baseLength = 3U,
};
FileConfig reg08_vga_dcoc_finish = {
.baseAddress = 0x082C,
.baseOffset = 7U,
.baseLength = 1U,
};
FileConfig reg08_vga_dcoc_finish_2nd = {
.baseAddress = 0x082C,
.baseOffset = 6U,
.baseLength = 1U,
};
FileConfig reg08_d_q_vga_vcm_sel_2nd = {
.baseAddress = 0x082C,
.baseOffset = 3U,
.baseLength = 3U,
};
FileConfig reg08_d_vga_ldo_vout_sel = {
.baseAddress = 0x082C,
.baseOffset = 0U,
.baseLength = 3U,
};
FileConfig reg08_d_adc_inter_rstn_force = {
.baseAddress = 0x0830,
.baseOffset = 31U,
.baseLength = 1U,
};
FileConfig reg08_d_adc_inter_rstn_reg_sel = {
.baseAddress = 0x0830,
.baseOffset = 30U,
.baseLength = 1U,
};
FileConfig reg08_d_bb_clk_rstn_force = {
.baseAddress = 0x0830,
.baseOffset = 29U,
.baseLength = 1U,
};
FileConfig reg08_d_bb_clk_rstn_reg_sel = {
.baseAddress = 0x0830,
.baseOffset = 28U,
.baseLength = 1U,
};
FileConfig reg08_d_bbf_iref_en = {
.baseAddress = 0x0830,
.baseOffset = 27U,
.baseLength = 1U,
};
FileConfig reg08_d_i_tia_en = {
.baseAddress = 0x0830,
.baseOffset = 26U,
.baseLength = 1U,
};
FileConfig reg08_d_i_tia_vcm_en = {
.baseAddress = 0x0830,
.baseOffset = 25U,
.baseLength = 1U,
};
FileConfig reg08_d_q_tia_en = {
.baseAddress = 0x0830,
.baseOffset = 24U,
.baseLength = 1U,
};
FileConfig reg08_d_q_adc_refgen_en = {
.baseAddress = 0x0830,
.baseOffset = 15U,
.baseLength = 1U,
};
FileConfig reg08_d_en_adc_ldo = {
.baseAddress = 0x0830,
.baseOffset = 7U,
.baseLength = 1U,
};
FileConfig reg08_d_i_aux_vga = {
.baseAddress = 0x0830,
.baseOffset = 4U,
.baseLength = 3U,
};
FileConfig reg08_d_q_aux_vga = {
.baseAddress = 0x0830,
.baseOffset = 1U,
.baseLength = 3U,
};
FileConfig reg08_d_adc_clk_force_off = {
.baseAddress = 0x0830,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg08_i_adc_offset_calwr_ch0 = {
.baseAddress = 0x0834,
.baseOffset = 24U,
.baseLength = 8U,
};
FileConfig reg08_i_adc_offset_calwr_ch1 = {
.baseAddress = 0x0834,
.baseOffset = 16U,
.baseLength = 8U,
};
FileConfig reg08_i_adc_offset_calwr_ch2 = {
.baseAddress = 0x0834,
.baseOffset = 8U,
.baseLength = 8U,
};
FileConfig reg08_i_adc_offset_calwr_ch3 = {
.baseAddress = 0x0834,
.baseOffset = 0U,
.baseLength = 8U,
};
FileConfig reg08_i_adc_offset_calwr_ch4 = {
.baseAddress = 0x0838,
.baseOffset = 24U,
.baseLength = 8U,
};
FileConfig reg08_i_adc_offset_calwr_ch5 = {
.baseAddress = 0x0838,
.baseOffset = 16U,
.baseLength = 8U,
};
FileConfig reg08_i_adc_offset_calwr_ch6 = {
.baseAddress = 0x0838,
.baseOffset = 8U,
.baseLength = 8U,
};
FileConfig reg08_i_adc_offset_calwr_ch7 = {
.baseAddress = 0x0838,
.baseOffset = 0U,
.baseLength = 8U,
};
FileConfig reg08_q_adc_offset_calwr_ch0 = {
.baseAddress = 0x083C,
.baseOffset = 24U,
.baseLength = 8U,
};
FileConfig reg08_q_adc_offset_calwr_ch1 = {
.baseAddress = 0x083C,
.baseOffset = 16U,
.baseLength = 8U,
};
FileConfig reg08_q_adc_offset_calwr_ch2 = {
.baseAddress = 0x083C,
.baseOffset = 8U,
.baseLength = 8U,
};
FileConfig reg08_q_adc_offset_calwr_ch3 = {
.baseAddress = 0x083C,
.baseOffset = 0U,
.baseLength = 8U,
};
FileConfig reg08_q_adc_offset_calwr_ch4 = {
.baseAddress = 0x0840,
.baseOffset = 24U,
.baseLength = 8U,
};
FileConfig reg08_q_adc_offset_calwr_ch5 = {
.baseAddress = 0x0840,
.baseOffset = 16U,
.baseLength = 8U,
};
FileConfig reg08_q_adc_offset_calwr_ch6 = {
.baseAddress = 0x0840,
.baseOffset = 8U,
.baseLength = 8U,
};
FileConfig reg08_q_adc_offset_calwr_ch7 = {
.baseAddress = 0x0840,
.baseOffset = 0U,
.baseLength = 8U,
};
FileConfig reg08_d_rx_lo_div_en = {
.baseAddress = 0x0844,
.baseOffset = 31U,
.baseLength = 1U,
};
FileConfig reg08_d_lna_ldo_en_2nd = {
.baseAddress = 0x0844,
.baseOffset = 30U,
.baseLength = 1U,
};
FileConfig reg08_d_i_adc_vref_tune_ch1_01 = {
.baseAddress = 0x0844,
.baseOffset = 27U,
.baseLength = 3U,
};
FileConfig reg08_d_i_adc_vref_tune_ch1_02 = {
.baseAddress = 0x0844,
.baseOffset = 24U,
.baseLength = 3U,
};
FileConfig reg08_d_ldoh1p8_bleeder_res_1p1 = {
.baseAddress = 0x0844,
.baseOffset = 22U,
.baseLength = 2U,
};
FileConfig reg08_d_i_adc_vref_tune_ch1_03 = {
.baseAddress = 0x0844,
.baseOffset = 19U,
.baseLength = 3U,
};
FileConfig reg08_d_i_adc_vref_tune_ch1_04 = {
.baseAddress = 0x0844,
.baseOffset = 16U,
.baseLength = 3U,
};
FileConfig reg08_d_ldoh3v_bleeder_res_1p1 = {
.baseAddress = 0x0844,
.baseOffset = 14U,
.baseLength = 2U,
};
FileConfig reg08_d_i_adc_vref_tune_ch1_05 = {
.baseAddress = 0x0844,
.baseOffset = 11U,
.baseLength = 3U,
};
FileConfig reg08_d_i_adc_vref_tune_ch1_06 = {
.baseAddress = 0x0844,
.baseOffset = 8U,
.baseLength = 3U,
};
FileConfig reg08_d_clkpll_pfd_delay = {
.baseAddress = 0x0844,
.baseOffset = 6U,
.baseLength = 2U,
};
FileConfig reg08_d_i_adc_vref_tune_ch1_07 = {
.baseAddress = 0x0844,
.baseOffset = 3U,
.baseLength = 3U,
};
FileConfig reg08_d_q_adc_vref_tune_ch0 = {
.baseAddress = 0x0844,
.baseOffset = 0U,
.baseLength = 3U,
};
FileConfig reg08_d_q_adc_vref_tune_ch1_01 = {
.baseAddress = 0x0848,
.baseOffset = 27U,
.baseLength = 3U,
};
FileConfig reg08_d_q_adc_vref_tune_ch1_02 = {
.baseAddress = 0x0848,
.baseOffset = 24U,
.baseLength = 3U,
};
FileConfig reg08_d_q_adc_vref_tune_ch1_03 = {
.baseAddress = 0x0848,
.baseOffset = 19U,
.baseLength = 3U,
};
FileConfig reg08_d_q_adc_vref_tune_ch1_04 = {
.baseAddress = 0x0848,
.baseOffset = 16U,
.baseLength = 3U,
};
FileConfig reg08_d_bbf_dcoc_finish = {
.baseAddress = 0x0848,
.baseOffset = 15U,
.baseLength = 1U,
};
FileConfig reg08_d_bbf_dcoc_finish_2nd = {
.baseAddress = 0x0848,
.baseOffset = 14U,
.baseLength = 1U,
};
FileConfig reg08_d_q_adc_vref_tune_ch1_05 = {
.baseAddress = 0x0848,
.baseOffset = 11U,
.baseLength = 3U,
};
FileConfig reg08_d_q_adc_vref_tune_ch1_06 = {
.baseAddress = 0x0848,
.baseOffset = 8U,
.baseLength = 3U,
};
FileConfig reg08_d_en_head_pow = {
.baseAddress = 0x0848,
.baseOffset = 7U,
.baseLength = 1U,
};
FileConfig reg08_d_q_vga_en_2nd = {
.baseAddress = 0x0848,
.baseOffset = 6U,
.baseLength = 1U,
};
FileConfig reg08_d_q_adc_vref_tune_ch1_07 = {
.baseAddress = 0x0848,
.baseOffset = 3U,
.baseLength = 3U,
};
FileConfig reg08_d_adc_ldo_vout_1p2_sel = {
.baseAddress = 0x0848,
.baseOffset = 0U,
.baseLength = 3U,
};
FileConfig reg08_ana_rfpll_auto_en = {
.baseAddress = 0x084C,
.baseOffset = 31U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_all_enable = {
.baseAddress = 0x084C,
.baseOffset = 30U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_ldo_en = {
.baseAddress = 0x084C,
.baseOffset = 29U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_iqldo_en = {
.baseAddress = 0x084C,
.baseOffset = 28U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_ldo_endly = {
.baseAddress = 0x084C,
.baseOffset = 27U,
.baseLength = 1U,
};
FileConfig reg08_d_rfpll_iqldo_endly = {
.baseAddress = 0x084C,
.baseOffset = 26U,
.baseLength = 1U,
};
FileConfig reg08_ana_clkpll_auto_en = {
.baseAddress = 0x084C,
.baseOffset = 25U,
.baseLength = 1U,
};
FileConfig reg08_d_clkpll_ldo_en = {
.baseAddress = 0x084C,
.baseOffset = 24U,
.baseLength = 1U,
};
FileConfig reg08_d_clkpll_all_enable_not_used = {
.baseAddress = 0x084C,
.baseOffset = 23U,
.baseLength = 1U,
};
FileConfig reg08_d_clkpll_ldo_endly = {
.baseAddress = 0x084C,
.baseOffset = 22U,
.baseLength = 1U,
};
FileConfig reg08_ana_rx_auto_en = {
.baseAddress = 0x084C,
.baseOffset = 21U,
.baseLength = 1U,
};
FileConfig reg08_d_rx_bias_en = {
.baseAddress = 0x084C,
.baseOffset = 20U,
.baseLength = 1U,
};
FileConfig reg08_d_rx_block_en = {
.baseAddress = 0x084C,
.baseOffset = 19U,
.baseLength = 1U,
};
FileConfig reg08_d_rx_ldo_en = {
.baseAddress = 0x084C,
.baseOffset = 18U,
.baseLength = 1U,
};
FileConfig reg08_d_rx_ldo_lpf_en = {
.baseAddress = 0x084C,
.baseOffset = 17U,
.baseLength = 1U,
};
FileConfig reg08_ana_tx_auto_en = {
.baseAddress = 0x084C,
.baseOffset = 16U,
.baseLength = 1U,
};
FileConfig reg08_d_tx_ldo_en = {
.baseAddress = 0x084C,
.baseOffset = 15U,
.baseLength = 1U,
};
FileConfig reg08_d_tx_ana_en = {
.baseAddress = 0x084C,
.baseOffset = 14U,
.baseLength = 1U,
};
FileConfig reg08_d_tx_rstn = {
.baseAddress = 0x084C,
.baseOffset = 13U,
.baseLength = 1U,
};
FileConfig reg08_d_rx_ldo_force_on_ch2 = {
.baseAddress = 0x084C,
.baseOffset = 12U,
.baseLength = 1U,
};
FileConfig reg08_d_rx_block_force_on_ch2 = {
.baseAddress = 0x084C,
.baseOffset = 11U,
.baseLength = 1U,
};
FileConfig reg08_d_lna_force_on_ch2 = {
.baseAddress = 0x084C,
.baseOffset = 10U,
.baseLength = 1U,
};
FileConfig reg08_d_mixer_force_on_ch2 = {
.baseAddress = 0x084C,
.baseOffset = 9U,
.baseLength = 1U,
};
FileConfig reg08_d_rx_lo_force_on_ch2 = {
.baseAddress = 0x084C,
.baseOffset = 8U,
.baseLength = 1U,
};
FileConfig reg08_d_i_tia_force_on_ch2 = {
.baseAddress = 0x084C,
.baseOffset = 7U,
.baseLength = 1U,
};
FileConfig reg08_d_i_vga_force_on_ch2 = {
.baseAddress = 0x084C,
.baseOffset = 6U,
.baseLength = 1U,
};
FileConfig reg08_d_i_adc_refgen_force_on_ch2 = {
.baseAddress = 0x084C,
.baseOffset = 5U,
.baseLength = 1U,
};
FileConfig reg08_d_i_adc_force_on_ch2 = {
.baseAddress = 0x084C,
.baseOffset = 4U,
.baseLength = 1U,
};
FileConfig reg08_d_q_tia_force_on_ch2 = {
.baseAddress = 0x084C,
.baseOffset = 3U,
.baseLength = 1U,
};
FileConfig reg08_d_q_vga_force_on_ch2 = {
.baseAddress = 0x084C,
.baseOffset = 2U,
.baseLength = 1U,
};
FileConfig reg08_d_q_adc_refgen_force_on_ch2 = {
.baseAddress = 0x084C,
.baseOffset = 1U,
.baseLength = 1U,
};
FileConfig reg08_d_q_adc_force_on_ch2 = {
.baseAddress = 0x084C,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg08_d_i_tia_fb_cap_2nd = {
.baseAddress = 0x0850,
.baseOffset = 27U,
.baseLength = 5U,
};
FileConfig reg08_d_q_tia_fb_res_2nd = {
.baseAddress = 0x0850,
.baseOffset = 19U,
.baseLength = 5U,
};
FileConfig reg08_d_i_tia_stg1_itrim_2nd = {
.baseAddress = 0x0850,
.baseOffset = 16U,
.baseLength = 3U,
};
FileConfig reg08_d_i_tia_fb_res_2nd = {
.baseAddress = 0x0850,
.baseOffset = 11U,
.baseLength = 5U,
};
FileConfig reg08_d_i_tia_vcm_sel_2nd = {
.baseAddress = 0x0850,
.baseOffset = 8U,
.baseLength = 3U,
};
FileConfig reg08_d_i_keep_dcoc_2nd = {
.baseAddress = 0x0850,
.baseOffset = 7U,
.baseLength = 1U,
};
FileConfig reg08_d_i_tia_dcoc_dac_seln_2nd = {
.baseAddress = 0x0850,
.baseOffset = 0U,
.baseLength = 7U,
};
FileConfig reg08_d_i_tia_stag1_isel_2nd = {
.baseAddress = 0x0854,
.baseOffset = 30U,
.baseLength = 2U,
};
FileConfig reg08_d_vga_ldo_vout_sel_2nd = {
.baseAddress = 0x0854,
.baseOffset = 27U,
.baseLength = 3U,
};
FileConfig reg08_d_i_vga_gain_sel_1_2nd = {
.baseAddress = 0x0854,
.baseOffset = 24U,
.baseLength = 3U,
};
FileConfig reg08_d_q_tia_stag1_isel_2nd = {
.baseAddress = 0x0854,
.baseOffset = 22U,
.baseLength = 2U,
};
FileConfig reg08_d_q_tia_stg1_itrim_2nd = {
.baseAddress = 0x0854,
.baseOffset = 19U,
.baseLength = 3U,
};
FileConfig reg08_d_lna_ldo1_vout_sel_2nd = {
.baseAddress = 0x0854,
.baseOffset = 16U,
.baseLength = 3U,
};
FileConfig reg08_d_lna_stage2_agc_2nd = {
.baseAddress = 0x0854,
.baseOffset = 14U,
.baseLength = 2U,
};
FileConfig reg08_d_lna_ldo2_vout_sel = {
.baseAddress = 0x0854,
.baseOffset = 11U,
.baseLength = 3U,
};
FileConfig reg08_d_lna_stage2_vcm_sel_2nd = {
.baseAddress = 0x0854,
.baseOffset = 8U,
.baseLength = 3U,
};
FileConfig reg08_d_i_adc_vref_tune_ch0 = {
.baseAddress = 0x0854,
.baseOffset = 3U,
.baseLength = 3U,
};
FileConfig reg08_d_tia_ldo_vout_sel_2nd = {
.baseAddress = 0x0854,
.baseOffset = 0U,
.baseLength = 3U,
};
FileConfig reg08_d_q_keep_dcoc_2nd = {
.baseAddress = 0x0858,
.baseOffset = 31U,
.baseLength = 1U,
};
FileConfig reg08_d_i_vga_dcoc_sel_pn_1_2nd = {
.baseAddress = 0x0858,
.baseOffset = 24U,
.baseLength = 7U,
};
FileConfig reg08_d_vga_ldo_endly_2nd = {
.baseAddress = 0x0858,
.baseOffset = 23U,
.baseLength = 1U,
};
FileConfig reg08_d_i_vga_dcoc_sel_pn_2_2nd = {
.baseAddress = 0x0858,
.baseOffset = 16U,
.baseLength = 7U,
};
FileConfig reg08_d_i_vga_dcoc_keep_on_2nd = {
.baseAddress = 0x0858,
.baseOffset = 15U,
.baseLength = 1U,
};
FileConfig reg08_d_i_vga_dcoc_sel_nn_1_2nd = {
.baseAddress = 0x0858,
.baseOffset = 8U,
.baseLength = 7U,
};
FileConfig reg08_d_tia_ldo_1p2_endly_2nd = {
.baseAddress = 0x0858,
.baseOffset = 7U,
.baseLength = 1U,
};
FileConfig reg08_d_q_vga_dcoc_sel_pn_1_2nd = {
.baseAddress = 0x0858,
.baseOffset = 0U,
.baseLength = 7U,
};
FileConfig reg08_d_clkpll_lock_det_rstn = {
.baseAddress = 0x085C,
.baseOffset = 31U,
.baseLength = 1U,
};
FileConfig reg08_d_q_adc_vref_tune_ch1_01_2nd = {
.baseAddress = 0x085C,
.baseOffset = 28U,
.baseLength = 3U,
};
FileConfig reg08_d_q_adc_vref_tune_ch1_02_2nd = {
.baseAddress = 0x085C,
.baseOffset = 24U,
.baseLength = 3U,
};
FileConfig reg08_d_rfpll_pfd_bw_calen = {
.baseAddress = 0x085C,
.baseOffset = 23U,
.baseLength = 1U,
};
FileConfig reg08_d_q_vga_dcoc_sel_nn_1_2nd = {
.baseAddress = 0x085C,
.baseOffset = 16U,
.baseLength = 7U,
};
FileConfig reg08_d_q_vga_dcoc_sel_pn_2_2nd = {
.baseAddress = 0x085C,
.baseOffset = 8U,
.baseLength = 7U,
};
FileConfig reg08_d_i_vga_dcoc_sel_nn_2_2nd = {
.baseAddress = 0x085C,
.baseOffset = 1U,
.baseLength = 7U,
};
FileConfig reg08_d_q_vga_dcoc_keep_on_2nd = {
.baseAddress = 0x085C,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg08_i_adc_offset_calwr_ch0_2nd = {
.baseAddress = 0x0860,
.baseOffset = 24U,
.baseLength = 8U,
};
FileConfig reg08_i_adc_offset_calwr_ch1_2nd = {
.baseAddress = 0x0860,
.baseOffset = 16U,
.baseLength = 8U,
};
FileConfig reg08_i_adc_offset_calwr_ch2_2nd = {
.baseAddress = 0x0860,
.baseOffset = 8U,
.baseLength = 8U,
};
FileConfig reg08_i_adc_offset_calwr_ch3_2nd = {
.baseAddress = 0x0860,
.baseOffset = 0U,
.baseLength = 8U,
};
FileConfig reg08_i_adc_offset_calwr_ch4_2nd = {
.baseAddress = 0x0864,
.baseOffset = 24U,
.baseLength = 8U,
};
FileConfig reg08_i_adc_offset_calwr_ch5_2nd = {
.baseAddress = 0x0864,
.baseOffset = 16U,
.baseLength = 8U,
};
FileConfig reg08_i_adc_offset_calwr_ch6_2nd = {
.baseAddress = 0x0864,
.baseOffset = 8U,
.baseLength = 8U,
};
FileConfig reg08_i_adc_offset_calwr_ch7_2nd = {
.baseAddress = 0x0864,
.baseOffset = 0U,
.baseLength = 8U,
};
FileConfig reg08_q_adc_offset_calwr_ch0_2nd = {
.baseAddress = 0x0868,
.baseOffset = 24U,
.baseLength = 8U,
};
FileConfig reg08_q_adc_offset_calwr_ch1_2nd = {
.baseAddress = 0x0868,
.baseOffset = 16U,
.baseLength = 8U,
};
FileConfig reg08_q_adc_offset_calwr_ch2_2nd = {
.baseAddress = 0x0868,
.baseOffset = 8U,
.baseLength = 8U,
};
FileConfig reg08_q_adc_offset_calwr_ch3_2nd = {
.baseAddress = 0x0868,
.baseOffset = 0U,
.baseLength = 8U,
};
FileConfig reg08_q_adc_offset_calwr_ch4_2nd = {
.baseAddress = 0x086C,
.baseOffset = 24U,
.baseLength = 8U,
};
FileConfig reg08_q_adc_offset_calwr_ch5_2nd = {
.baseAddress = 0x086C,
.baseOffset = 16U,
.baseLength = 8U,
};
FileConfig reg08_q_adc_offset_calwr_ch6_2nd = {
.baseAddress = 0x086C,
.baseOffset = 8U,
.baseLength = 8U,
};
FileConfig reg08_q_adc_offset_calwr_ch7_2nd = {
.baseAddress = 0x086C,
.baseOffset = 0U,
.baseLength = 8U,
};
FileConfig reg08_d_i_adc_vref_tune_ch0_2nd = {
.baseAddress = 0x0870,
.baseOffset = 27U,
.baseLength = 3U,
};
FileConfig reg08_d_i_adc_vref_tune_ch1_01_2nd = {
.baseAddress = 0x0870,
.baseOffset = 24U,
.baseLength = 3U,
};
FileConfig reg08_d_i_adc_vref_tune_ch1_02_2nd = {
.baseAddress = 0x0870,
.baseOffset = 19U,
.baseLength = 3U,
};
FileConfig reg08_d_i_adc_vref_tune_ch1_03_2nd = {
.baseAddress = 0x0870,
.baseOffset = 16U,
.baseLength = 3U,
};
FileConfig reg08_d_i_adc_vref_tune_ch1_04_2nd = {
.baseAddress = 0x0870,
.baseOffset = 11U,
.baseLength = 3U,
};
FileConfig reg08_d_i_adc_vref_tune_ch1_05_2nd = {
.baseAddress = 0x0870,
.baseOffset = 8U,
.baseLength = 3U,
};
FileConfig reg08_d_i_adc_vref_tune_ch1_06_2nd = {
.baseAddress = 0x0870,
.baseOffset = 3U,
.baseLength = 3U,
};
FileConfig reg08_d_i_adc_vref_tune_ch1_07_2nd = {
.baseAddress = 0x0870,
.baseOffset = 0U,
.baseLength = 3U,
};
FileConfig reg08_d_rx_lo_hdsw_en = {
.baseAddress = 0x0874,
.baseOffset = 17U,
.baseLength = 4U,
};
FileConfig reg08_d_q_adc_en = {
.baseAddress = 0x0874,
.baseOffset = 16U,
.baseLength = 1U,
};
FileConfig reg08_d_q_tia_dcoc_en_2nd = {
.baseAddress = 0x0874,
.baseOffset = 12U,
.baseLength = 1U,
};
FileConfig reg08_d_tia_ldo_1p2_en_2nd = {
.baseAddress = 0x0874,
.baseOffset = 11U,
.baseLength = 1U,
};
FileConfig reg08_d_vga_ldo_en_2nd = {
.baseAddress = 0x0874,
.baseOffset = 8U,
.baseLength = 1U,
};
FileConfig reg08_d_i_vga_en_2nd = {
.baseAddress = 0x0874,
.baseOffset = 7U,
.baseLength = 1U,
};
FileConfig reg08_d_i_vga_dcoc_comp_en_2nd = {
.baseAddress = 0x0874,
.baseOffset = 6U,
.baseLength = 1U,
};
FileConfig reg08_d_q_tia_fb_cap_2nd = {
.baseAddress = 0x0874,
.baseOffset = 0U,
.baseLength = 5U,
};
FileConfig reg08_d_q_adc_en_2nd = {
.baseAddress = 0x0878,
.baseOffset = 31U,
.baseLength = 1U,
};
FileConfig reg08_d_q_adc_refgen_en_2nd = {
.baseAddress = 0x0878,
.baseOffset = 29U,
.baseLength = 1U,
};
FileConfig reg08_d_i_adc_en_2nd = {
.baseAddress = 0x0878,
.baseOffset = 28U,
.baseLength = 1U,
};
FileConfig reg08_d_i_adc_refgen_en_2nd = {
.baseAddress = 0x0878,
.baseOffset = 27U,
.baseLength = 1U,
};
FileConfig reg08_d_ldol_vout_sel_1p1 = {
.baseAddress = 0x0878,
.baseOffset = 24U,
.baseLength = 3U,
};
FileConfig reg08_d_q_vga_dcoc_comp_en_2nd = {
.baseAddress = 0x0878,
.baseOffset = 23U,
.baseLength = 1U,
};
FileConfig reg08_d_fsyn_bias_en = {
.baseAddress = 0x0878,
.baseOffset = 22U,
.baseLength = 1U,
};
FileConfig reg08_d_rx_rf_iref_en_2nd = {
.baseAddress = 0x0878,
.baseOffset = 21U,
.baseLength = 1U,
};
FileConfig reg08_d_mixer_en_2nd = {
.baseAddress = 0x0878,
.baseOffset = 20U,
.baseLength = 1U,
};
FileConfig reg08_d_lna_stage1_en_2nd = {
.baseAddress = 0x0878,
.baseOffset = 19U,
.baseLength = 1U,
};
FileConfig reg08_d_lna_stage2_en_2nd = {
.baseAddress = 0x0878,
.baseOffset = 18U,
.baseLength = 1U,
};
FileConfig reg08_d_i_adc_refgen_en = {
.baseAddress = 0x0878,
.baseOffset = 17U,
.baseLength = 1U,
};
FileConfig reg08_d_bbf_iref_en_2nd = {
.baseAddress = 0x0878,
.baseOffset = 16U,
.baseLength = 1U,
};
FileConfig reg08_d_i_tia_en_2nd = {
.baseAddress = 0x0878,
.baseOffset = 15U,
.baseLength = 1U,
};
FileConfig reg08_d_i_tia_vcm_en_2nd = {
.baseAddress = 0x0878,
.baseOffset = 14U,
.baseLength = 1U,
};
FileConfig reg08_d_q_tia_en_2nd = {
.baseAddress = 0x0878,
.baseOffset = 13U,
.baseLength = 1U,
};
FileConfig reg08_d_q_tia_vcm_en_2nd = {
.baseAddress = 0x0878,
.baseOffset = 12U,
.baseLength = 1U,
};
FileConfig reg08_d_rx_lo_div_en_2nd = {
.baseAddress = 0x0878,
.baseOffset = 11U,
.baseLength = 1U,
};
FileConfig reg08_d_rx_lo_hdsw_en_2nd = {
.baseAddress = 0x0878,
.baseOffset = 7U,
.baseLength = 4U,
};
FileConfig reg08_d_ldoh1p8_out_sel_1p1 = {
.baseAddress = 0x0878,
.baseOffset = 3U,
.baseLength = 3U,
};
FileConfig reg08_d_ldoh1p8_out_selb = {
.baseAddress = 0x0878,
.baseOffset = 0U,
.baseLength = 3U,
};
FileConfig reg08_d_q_adc_vref_tune_ch1_06_2nd = {
.baseAddress = 0x087C,
.baseOffset = 27U,
.baseLength = 3U,
};
FileConfig reg08_d_q_adc_vref_tune_ch1_07_2nd = {
.baseAddress = 0x087C,
.baseOffset = 24U,
.baseLength = 3U,
};
FileConfig reg08_d_adc_ldo_vout_1p2_sel_2nd = {
.baseAddress = 0x087C,
.baseOffset = 19U,
.baseLength = 3U,
};
FileConfig reg08_d_rx_ldo_v1p2_endly = {
.baseAddress = 0x087C,
.baseOffset = 15U,
.baseLength = 1U,
};
