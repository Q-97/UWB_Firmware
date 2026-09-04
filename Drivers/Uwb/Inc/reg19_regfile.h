#include "cali_reg.h"
FileConfig reg19_Ant_flag1 = {
.baseAddress = 0x1948,
.baseOffset = 30U,
.baseLength = 1U,
};
FileConfig reg19_agc_gain_cnt1 = {
.baseAddress = 0x1948,
.baseOffset = 24U,
.baseLength = 6U,
};
FileConfig reg19_agc_to_vga1 = {
.baseAddress = 0x1948,
.baseOffset = 0U,
.baseLength = 23U,
};
FileConfig reg19_IQImbAmplitudeInfo_RX0 = {
.baseAddress = 0x1950,
.baseOffset = 16U,
.baseLength = 9U,
};
FileConfig reg19_IQImbPhaseInfo_RX0 = {
.baseAddress = 0x1950,
.baseOffset = 0U,
.baseLength = 9U,
};
FileConfig reg19_IQImbAmplitudeInfo_RX1 = {
.baseAddress = 0x1954,
.baseOffset = 16U,
.baseLength = 9U,
};
FileConfig reg19_IQImbPhaseInfo_RX1 = {
.baseAddress = 0x1954,
.baseOffset = 0U,
.baseLength = 9U,
};
FileConfig reg19_IP0_LED_DetectLevel = {
.baseAddress = 0x1970,
.baseOffset = 0U,
.baseLength = 2U,
};
FileConfig reg19_Rake_FSS_Peak_Mask = {
.baseAddress = 0x19A0,
.baseOffset = 8U,
.baseLength = 8U,
};
FileConfig reg19_Rake_FSS_Mask = {
.baseAddress = 0x19A0,
.baseOffset = 0U,
.baseLength = 8U,
};
FileConfig reg19_AgcOutToPreamFlag1 = {
.baseAddress = 0x19A4,
.baseOffset = 24U,
.baseLength = 1U,
};
FileConfig reg19_AgcSmallWindowCounter1 = {
.baseAddress = 0x19A4,
.baseOffset = 8U,
.baseLength = 16U,
};
FileConfig reg19_isGitRamFull1 = {
.baseAddress = 0x19A4,
.baseOffset = 7U,
.baseLength = 1U,
};
FileConfig reg19_isIQFull1 = {
.baseAddress = 0x19A4,
.baseOffset = 6U,
.baseLength = 1U,
};
FileConfig reg19_LnaSwitchFlag1 = {
.baseAddress = 0x19A4,
.baseOffset = 5U,
.baseLength = 1U,
};
FileConfig reg19_DesireValueFreeze1 = {
.baseAddress = 0x19A4,
.baseOffset = 4U,
.baseLength = 1U,
};
FileConfig reg19_AGC_STATE1 = {
.baseAddress = 0x19A4,
.baseOffset = 0U,
.baseLength = 4U,
};
FileConfig reg19_Select_State = {
.baseAddress = 0x19C4,
.baseOffset = 8U,
.baseLength = 1U,
};
FileConfig reg19_PACW = {
    .baseAddress = 0x1900,
.baseOffset = 28U,
.baseLength = 4U,
};
FileConfig reg19_PADT = {
    .baseAddress = 0x1900,
.baseOffset = 27U,
.baseLength = 1U,
};
FileConfig reg19_PADW = {
    .baseAddress = 0x1900,
.baseOffset = 24U,
.baseLength = 3U,
};
FileConfig reg19_PATH1 = {
   .baseAddress = 0x1900,
.baseOffset = 14U,
.baseLength = 10U,
};
FileConfig reg19_PATH = {
    .baseAddress = 0x1900,
.baseOffset = 6U,
.baseLength = 8U,
};
FileConfig reg19_PAC = {
     .baseAddress = 0x1900,
.baseOffset = 3U,
.baseLength = 3U,
};
FileConfig reg19_PACF = {
    .baseAddress = 0x1900,
.baseOffset = 0U,
.baseLength = 3U,
};
FileConfig reg19_SATH = {
    .baseAddress = 0x1904,
.baseOffset = 29U,
.baseLength = 3U,
};
FileConfig reg19_SAF = {
     .baseAddress = 0x1904,
.baseOffset = 27U,
.baseLength = 2U,
};
FileConfig reg19_SDT = {
     .baseAddress = 0x1904,
.baseOffset = 26U,
.baseLength = 1U,
};
FileConfig reg19_SAT = {
     .baseAddress = 0x1904,
.baseOffset = 25U,
.baseLength = 1U,
};
FileConfig reg19_SALD = {
    .baseAddress = 0x1904,
.baseOffset = 24U,
.baseLength = 1U,
};
FileConfig reg19_SDTH = {
    .baseAddress = 0x1904,
.baseOffset = 14U,
.baseLength = 10U,
};
FileConfig reg19_SANORF = {
  .baseAddress = 0x1904,
.baseOffset = 11U,
.baseLength = 3U,
};
FileConfig reg19_PSDP = {
    .baseAddress = 0x1904,
.baseOffset = 10U,
.baseLength = 1U,
};
FileConfig reg19_SAC = {
     .baseAddress = 0x1904,
.baseOffset = 5U,
.baseLength = 3U,
};
FileConfig reg19_SAN = {
     .baseAddress = 0x1904,
.baseOffset = 2U,
.baseLength = 3U,
};
FileConfig reg19_PSDUAN = {
  .baseAddress = 0x1908,
.baseOffset = 29U,
.baseLength = 3U,
};
FileConfig reg19_PHRAN = {
   .baseAddress = 0x1908,
.baseOffset = 26U,
.baseLength = 3U,
};
FileConfig reg19_PSDUC = {
   .baseAddress = 0x1908,
.baseOffset = 21U,
.baseLength = 3U,
};
FileConfig reg19_PHRC = {
    .baseAddress = 0x1908,
.baseOffset = 18U,
.baseLength = 3U,
};
FileConfig reg19_PSAF = {
    .baseAddress = 0x1908,
.baseOffset = 16U,
.baseLength = 2U,
};
FileConfig reg19_PSAT = {
    .baseAddress = 0x1908,
.baseOffset = 15U,
.baseLength = 1U,
};
FileConfig reg19_MagCalcFlg = {
.baseAddress = 0x1908,
.baseOffset = 8U,
.baseLength = 1U,
};
FileConfig reg19_PSDUTH = {
  .baseAddress = 0x1908,
.baseOffset = 4U,
.baseLength = 4U,
};
FileConfig reg19_PHRATH = {
  .baseAddress = 0x1908,
.baseOffset = 0U,
.baseLength = 4U,
};
FileConfig reg19_CP_SATH = {
 .baseAddress = 0x190C,
.baseOffset = 29U,
.baseLength = 3U,
};
FileConfig reg19_CP_SAF = {
  .baseAddress = 0x190C,
.baseOffset = 27U,
.baseLength = 2U,
};
FileConfig reg19_CP_SAT = {
  .baseAddress = 0x190C,
.baseOffset = 22U,
.baseLength = 1U,
};
FileConfig reg19_CP_SDTH = {
 .baseAddress = 0x190C,
.baseOffset = 6U,
.baseLength = 16U,
};
FileConfig reg19_CP_SAC = {
  .baseAddress = 0x190C,
.baseOffset = 3U,
.baseLength = 3U,
};
FileConfig reg19_CP_SAN = {
  .baseAddress = 0x190C,
.baseOffset = 0U,
.baseLength = 3U,
};
FileConfig reg19_DRX_SFDTOC = {
.baseAddress = 0x1910,
.baseOffset = 16U,
.baseLength = 16U,
};
FileConfig reg19_DRX_PRETOC = {
.baseAddress = 0x1914,
.baseOffset = 16U,
.baseLength = 16U,
};
FileConfig reg19_RX_FWTO = {
 .baseAddress = 0x1918,
.baseOffset = 0U,
.baseLength = 32U,
};
FileConfig reg19_PDOA_Filter_Mode = {
.baseAddress = 0x191C,
.baseOffset = 2U,
.baseLength = 1U,
};
FileConfig reg19_PDOA_DET_TYPE = {
.baseAddress = 0x191C,
.baseOffset = 1U,
.baseLength = 1U,
};
FileConfig reg19_PDOA_TYPE = {
.baseAddress = 0x191C,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg19_PULSE_ADJ = {
.baseAddress = 0x1920,
.baseOffset = 0U,
.baseLength = 10U,
};
FileConfig reg19_DC_SatType = {
.baseAddress = 0x1924,
.baseOffset = 6U,
.baseLength = 1U,
};
FileConfig reg19_DC_Coef = {
 .baseAddress = 0x1924,
.baseOffset = 3U,
.baseLength = 3U,
};
FileConfig reg19_DC_Len = {
  .baseAddress = 0x1924,
.baseOffset = 0U,
.baseLength = 3U,
};
FileConfig reg19_AgcMode1 = {
.baseAddress = 0x1928,
.baseOffset = 24U,
.baseLength = 2U,
};
FileConfig reg19_Agc_G_Is_Set = {
.baseAddress = 0x1928,
.baseOffset = 23U,
.baseLength = 1U,
};
FileConfig reg19_Agc_G_Set_Value = {
.baseAddress = 0x1928,
.baseOffset = 16U,
.baseLength = 7U,
};
FileConfig reg19_AGC_input_7bit = {
.baseAddress = 0x1928,
.baseOffset = 15U,
.baseLength = 1U,
};
FileConfig reg19_agc_detector_big_len1 = {
.baseAddress = 0x1928,
.baseOffset = 8U,
.baseLength = 7U,
};
FileConfig reg19_agc_detector_len1 = {
.baseAddress = 0x1928,
.baseOffset = 0U,
.baseLength = 7U,
};
FileConfig reg19_agc_step1 = {
.baseAddress = 0x192C,
.baseOffset = 16U,
.baseLength = 14U,
};
FileConfig reg19_agc_detector_threshold_max1 = {
.baseAddress = 0x192C,
.baseOffset = 0U,
.baseLength = 14U,
};
FileConfig reg19_agc_quantiz_step1 = {
.baseAddress = 0x1930,
.baseOffset = 16U,
.baseLength = 14U,
};
FileConfig reg19_desire_value1 = {
.baseAddress = 0x1930,
.baseOffset = 0U,
.baseLength = 9U,
};
FileConfig reg19_agc_adj_high_power_thr1 = {
.baseAddress = 0x1934,
.baseOffset = 24U,
.baseLength = 6U,
};
FileConfig reg19_agc_adj_low_power_thr1 = {
.baseAddress = 0x1934,
.baseOffset = 16U,
.baseLength = 6U,
};
FileConfig reg19_agc_table_idx1 = {
.baseAddress = 0x1934,
.baseOffset = 12U,
.baseLength = 2U,
};
FileConfig reg19_agc_quantiz_min1 = {
.baseAddress = 0x1934,
.baseOffset = 0U,
.baseLength = 12U,
};
FileConfig reg19_agc_big_step1 = {
.baseAddress = 0x1938,
.baseOffset = 24U,
.baseLength = 3U,
};
FileConfig reg19_agc_high_power_adj1 = {
.baseAddress = 0x1938,
.baseOffset = 16U,
.baseLength = 6U,
};
FileConfig reg19_agc_low_power_adj1 = {
.baseAddress = 0x1938,
.baseOffset = 8U,
.baseLength = 6U,
};
FileConfig reg19_agc_nor_power_adj1 = {
.baseAddress = 0x1938,
.baseOffset = 0U,
.baseLength = 6U,
};
FileConfig reg19_agc_reset_init1 = {
.baseAddress = 0x193C,
.baseOffset = 16U,
.baseLength = 15U,
};
FileConfig reg19_Agc_Desire_HighPower_Threshold1 = {
.baseAddress = 0x193C,
.baseOffset = 8U,
.baseLength = 6U,
};
FileConfig reg19_Agc_Desire_LowPower_Threshold1 = {
.baseAddress = 0x193C,
.baseOffset = 0U,
.baseLength = 6U,
};
FileConfig reg19_Agc_HighPower_Desier1 = {
.baseAddress = 0x1940,
.baseOffset = 16U,
.baseLength = 13U,
};
FileConfig reg19_Agc_NormalPower_Desire1 = {
.baseAddress = 0x1940,
.baseOffset = 0U,
.baseLength = 13U,
};
FileConfig reg19_Agc_LowPower_Desire1 = {
.baseAddress = 0x1944,
.baseOffset = 16U,
.baseLength = 13U,
};
FileConfig reg19_Detector_Len_After_Preamble1 = {
.baseAddress = 0x1944,
.baseOffset = 8U,
.baseLength = 7U,
};
FileConfig reg19_Detcetor_BigLen_After_Preable1 = {
.baseAddress = 0x1944,
.baseOffset = 0U,
.baseLength = 7U,
};
FileConfig reg19_AccuLen_RX1 = {
.baseAddress = 0x194C,
.baseOffset = 17U,
.baseLength = 11U,
};
FileConfig reg19_IQImbEstFlg_RX1 = {
.baseAddress = 0x194C,
.baseOffset = 16U,
.baseLength = 1U,
};
FileConfig reg19_AccuLen_RX0 = {
.baseAddress = 0x194C,
.baseOffset = 1U,
.baseLength = 11U,
};
FileConfig reg19_IQImbEstFlg_RX0 = {
.baseAddress = 0x194C,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg19_Read_Idx_R0 = {
.baseAddress = 0x1958,
.baseOffset = 29U,
.baseLength = 3U,
};
FileConfig reg19_eP_RX0 = {
  .baseAddress = 0x1958,
.baseOffset = 20U,
.baseLength = 9U,
};
FileConfig reg19_eA_D_RX0 = {
.baseAddress = 0x1958,
.baseOffset = 11U,
.baseLength = 9U,
};
FileConfig reg19_eA_U_RX0 = {
.baseAddress = 0x1958,
.baseOffset = 2U,
.baseLength = 9U,
};
FileConfig reg19_IQImbCompenParamFlag_RX0 = {
.baseAddress = 0x1958,
.baseOffset = 1U,
.baseLength = 1U,
};
FileConfig reg19_IQImbCompenFlag_RX0 = {
.baseAddress = 0x1958,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg19_Read_Idx_R1 = {
.baseAddress = 0x195C,
.baseOffset = 29U,
.baseLength = 3U,
};
FileConfig reg19_eP_RX1 = {
  .baseAddress = 0x195C,
.baseOffset = 20U,
.baseLength = 9U,
};
FileConfig reg19_eA_D_RX1 = {
.baseAddress = 0x195C,
.baseOffset = 11U,
.baseLength = 9U,
};
FileConfig reg19_eA_U_RX1 = {
.baseAddress = 0x195C,
.baseOffset = 2U,
.baseLength = 9U,
};
FileConfig reg19_IQImbCompenParamFlag_RX1 = {
.baseAddress = 0x195C,
.baseOffset = 1U,
.baseLength = 1U,
};
FileConfig reg19_IQImbCompenFlag_RX1 = {
.baseAddress = 0x195C,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg19_Dummy = {
   .baseAddress = 0x1960,
.baseOffset = 0U,
.baseLength = 32U,
};
FileConfig reg19_antena_1_ovrd = {
.baseAddress = 0x1964,
.baseOffset = 3U,
.baseLength = 1U,
};
FileConfig reg19_antena_1_switch = {
.baseAddress = 0x1964,
.baseOffset = 2U,
.baseLength = 1U,
};
FileConfig reg19_antena_ovrd = {
.baseAddress = 0x1964,
.baseOffset = 1U,
.baseLength = 1U,
};
FileConfig reg19_antena_0_switch = {
.baseAddress = 0x1964,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg19_CP_FpThres = {
.baseAddress = 0x1968,
.baseOffset = 0U,
.baseLength = 16U,
};
FileConfig reg19_IP_LED_Extend_Flg = {
.baseAddress = 0x196C,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg19_RX_Preamble_ClockGating = {
.baseAddress = 0x1974,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg19_PType1_ProcMode = {
.baseAddress = 0x1978,
.baseOffset = 1U,
.baseLength = 1U,
};
FileConfig reg19_PSync_Type = {
.baseAddress = 0x1978,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg19_RX_Resulotion_STS = {
.baseAddress = 0x197C,
.baseOffset = 2U,
.baseLength = 1U,
};
FileConfig reg19_RX_Resulotion_SFD = {
.baseAddress = 0x197C,
.baseOffset = 1U,
.baseLength = 1U,
};
FileConfig reg19_RX_Resulotion_SYNC = {
.baseAddress = 0x197C,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg19_After_PRD_Desier1 = {
.baseAddress = 0x1980,
.baseOffset = 16U,
.baseLength = 13U,
};
FileConfig reg19_is_Peak_Out1 = {
.baseAddress = 0x1980,
.baseOffset = 14U,
.baseLength = 1U,
};
FileConfig reg19_Peak_Out_Threshold1 = {
.baseAddress = 0x1980,
.baseOffset = 0U,
.baseLength = 14U,
};
FileConfig reg19_agc_detector_threshold_min1 = {
.baseAddress = 0x1984,
.baseOffset = 16U,
.baseLength = 14U,
};
FileConfig reg19_AgcVariableStep1 = {
.baseAddress = 0x1984,
.baseOffset = 0U,
.baseLength = 14U,
};
FileConfig reg19_Is_Peak_Detect1 = {
.baseAddress = 0x1988,
.baseOffset = 22U,
.baseLength = 1U,
};
FileConfig reg19_Default_Max_Gain1 = {
.baseAddress = 0x1988,
.baseOffset = 17U,
.baseLength = 5U,
};
FileConfig reg19_Last_gain_Bit_Max1 = {
.baseAddress = 0x1988,
.baseOffset = 12U,
.baseLength = 5U,
};
FileConfig reg19_Vga_max1 = {
.baseAddress = 0x1988,
.baseOffset = 8U,
.baseLength = 4U,
};
FileConfig reg19_Tia_Max1 = {
.baseAddress = 0x1988,
.baseOffset = 4U,
.baseLength = 4U,
};
FileConfig reg19_Agc_Out_Mode1 = {
.baseAddress = 0x1988,
.baseOffset = 2U,
.baseLength = 2U,
};
FileConfig reg19_Vga_Mode1 = {
.baseAddress = 0x1988,
.baseOffset = 1U,
.baseLength = 1U,
};
FileConfig reg19_Tia_Mode1 = {
.baseAddress = 0x1988,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg19_Tia_Fix_Gain_Idx1 = {
.baseAddress = 0x198C,
.baseOffset = 25U,
.baseLength = 4U,
};
FileConfig reg19_IQ_Full_Value1 = {
.baseAddress = 0x198C,
.baseOffset = 19U,
.baseLength = 6U,
};
FileConfig reg19_gBit_Ram_Len1 = {
.baseAddress = 0x198C,
.baseOffset = 15U,
.baseLength = 4U,
};
FileConfig reg19_OutPut_Choose_High_Gain1 = {
.baseAddress = 0x198C,
.baseOffset = 14U,
.baseLength = 1U,
};
FileConfig reg19_Adjust_Agc_Bit1 = {
.baseAddress = 0x198C,
.baseOffset = 10U,
.baseLength = 4U,
};
FileConfig reg19_Is_Lock_Lna_After_PRD1 = {
.baseAddress = 0x198C,
.baseOffset = 9U,
.baseLength = 1U,
};
FileConfig reg19_After_PRD_Detect_Len1 = {
.baseAddress = 0x198C,
.baseOffset = 0U,
.baseLength = 9U,
};
FileConfig reg19_Is_Adjust_last_gain1 = {
.baseAddress = 0x1990,
.baseOffset = 25U,
.baseLength = 1U,
};
FileConfig reg19_Adjust_last_Gain_high_Thr1 = {
.baseAddress = 0x1990,
.baseOffset = 20U,
.baseLength = 5U,
};
FileConfig reg19_Adjust_last_Gain_low_Thr1 = {
.baseAddress = 0x1990,
.baseOffset = 15U,
.baseLength = 5U,
};
FileConfig reg19_Adjust_Last_High1 = {
.baseAddress = 0x1990,
.baseOffset = 10U,
.baseLength = 5U,
};
FileConfig reg19_Adjust_Last_Low1 = {
.baseAddress = 0x1990,
.baseOffset = 5U,
.baseLength = 5U,
};
FileConfig reg19_Adjust_Last_Norm1 = {
.baseAddress = 0x1990,
.baseOffset = 0U,
.baseLength = 5U,
};
FileConfig reg19_Agc_Set_Fixed_Gain = {
.baseAddress = 0x1994,
.baseOffset = 22U,
.baseLength = 1U,
};
FileConfig reg19_AGC_LNA1_Gain_1 = {
.baseAddress = 0x1994,
.baseOffset = 19U,
.baseLength = 3U,
};
FileConfig reg19_AGC_lna1_Bias2_1 = {
.baseAddress = 0x1994,
.baseOffset = 16U,
.baseLength = 3U,
};
FileConfig reg19_AGC_Lna2_Bias_1 = {
.baseAddress = 0x1994,
.baseOffset = 12U,
.baseLength = 4U,
};
FileConfig reg19_AGC_LNA2_Gain_1 = {
.baseAddress = 0x1994,
.baseOffset = 10U,
.baseLength = 2U,
};
FileConfig reg19_AGC_TIA_Gain_1 = {
.baseAddress = 0x1994,
.baseOffset = 6U,
.baseLength = 4U,
};
FileConfig reg19_AGC_VGA_Gain_1 = {
.baseAddress = 0x1994,
.baseOffset = 0U,
.baseLength = 6U,
};
FileConfig reg19_Diff_Sum_Len1 = {
.baseAddress = 0x1998,
.baseOffset = 20U,
.baseLength = 5U,
};
FileConfig reg19_Agc_Stable_Value1 = {
.baseAddress = 0x1998,
.baseOffset = 15U,
.baseLength = 5U,
};
FileConfig reg19_Set_Restore_Gain1 = {
.baseAddress = 0x1998,
.baseOffset = 10U,
.baseLength = 5U,
};
FileConfig reg19_Is_Restore_Gain_Switch_Ant1 = {
.baseAddress = 0x1998,
.baseOffset = 9U,
.baseLength = 1U,
};
FileConfig reg19_Ant_Id1 = {
 .baseAddress = 0x1998,
.baseOffset = 7U,
.baseLength = 2U,
};
FileConfig reg19_Switch_Ant_Threshold1 = {
.baseAddress = 0x1998,
.baseOffset = 2U,
.baseLength = 5U,
};
FileConfig reg19_AGC_Switch_Ant_Mode1 = {
.baseAddress = 0x1998,
.baseOffset = 0U,
.baseLength = 2U,
};
FileConfig reg19_RakeF_BurstCirMode1 = {
.baseAddress = 0x199C,
.baseOffset = 26U,
.baseLength = 1U,
};
FileConfig reg19_RakeF_BurstCirMode = {
.baseAddress = 0x199C,
.baseOffset = 25U,
.baseLength = 1U,
};
FileConfig reg19_RakeF_Lit = {
.baseAddress = 0x199C,
.baseOffset = 22U,
.baseLength = 3U,
};
FileConfig reg19_RakeF_Thres = {
.baseAddress = 0x199C,
.baseOffset = 18U,
.baseLength = 4U,
};
FileConfig reg19_RakeF_Gap = {
.baseAddress = 0x199C,
.baseOffset = 15U,
.baseLength = 3U,
};
FileConfig reg19_RakeF_SymbolMode = {
.baseAddress = 0x199C,
.baseOffset = 13U,
.baseLength = 2U,
};
FileConfig reg19_RakeF_Symbols = {
.baseAddress = 0x199C,
.baseOffset = 3U,
.baseLength = 10U,
};
FileConfig reg19_Rake_SelectLen = {
.baseAddress = 0x199C,
.baseOffset = 2U,
.baseLength = 1U,
};
FileConfig reg19_Rake_Mode = {
.baseAddress = 0x199C,
.baseOffset = 1U,
.baseLength = 1U,
};
FileConfig reg19_Rake_En = {
 .baseAddress = 0x199C,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg19_TiaAdjust1 = {
.baseAddress = 0x19A8,
.baseOffset = 21U,
.baseLength = 3U,
};
FileConfig reg19_VgaAdjust1 = {
.baseAddress = 0x19A8,
.baseOffset = 18U,
.baseLength = 3U,
};
FileConfig reg19_ManualSetGain1 = {
.baseAddress = 0x19A8,
.baseOffset = 13U,
.baseLength = 5U,
};
FileConfig reg19_DesireAfterAnt1 = {
.baseAddress = 0x19A8,
.baseOffset = 0U,
.baseLength = 13U,
};
FileConfig reg19_AgcOutToPreambThre1 = {
.baseAddress = 0x19AC,
.baseOffset = 27U,
.baseLength = 5U,
};
FileConfig reg19_DesireAfterLna1 = {
.baseAddress = 0x19AC,
.baseOffset = 14U,
.baseLength = 13U,
};
FileConfig reg19_SetRestAfterLnaSwitch1 = {
.baseAddress = 0x19AC,
.baseOffset = 9U,
.baseLength = 5U,
};
FileConfig reg19_isRestAfterLnaSwitch1 = {
.baseAddress = 0x19AC,
.baseOffset = 7U,
.baseLength = 2U,
};
FileConfig reg19_LnaSwitchThr1 = {
.baseAddress = 0x19AC,
.baseOffset = 2U,
.baseLength = 5U,
};
FileConfig reg19_LnaSwitchMode1 = {
.baseAddress = 0x19AC,
.baseOffset = 0U,
.baseLength = 2U,
};
FileConfig reg19_AntSwitchDelay1 = {
.baseAddress = 0x19B0,
.baseOffset = 12U,
.baseLength = 12U,
};
FileConfig reg19_LnaSwitchDelay1 = {
.baseAddress = 0x19B0,
.baseOffset = 0U,
.baseLength = 12U,
};
FileConfig reg19_DesireBaseOnBigWin1 = {
.baseAddress = 0x19B4,
.baseOffset = 30U,
.baseLength = 1U,
};
FileConfig reg19_WaitGbitMeanTime1 = {
.baseAddress = 0x19B4,
.baseOffset = 20U,
.baseLength = 10U,
};
FileConfig reg19_NormDesireLockTime1 = {
.baseAddress = 0x19B4,
.baseOffset = 12U,
.baseLength = 8U,
};
FileConfig reg19_AgcGainLockTime1 = {
.baseAddress = 0x19B4,
.baseOffset = 2U,
.baseLength = 10U,
};
FileConfig reg19_isGbitMean1 = {
.baseAddress = 0x19B4,
.baseOffset = 1U,
.baseLength = 1U,
};
FileConfig reg19_AntSwitchIsOnLna1 = {
.baseAddress = 0x19B4,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg19_WaitLnaswitchTime1 = {
.baseAddress = 0x19B8,
.baseOffset = 12U,
.baseLength = 12U,
};
FileConfig reg19_WaitAntSwitchTime1 = {
.baseAddress = 0x19B8,
.baseOffset = 0U,
.baseLength = 12U,
};
FileConfig reg19_PREAMBLE_SAT_SYMBOL1 = {
.baseAddress = 0x19BC,
.baseOffset = 12U,
.baseLength = 4U,
};
FileConfig reg19_PREAMLBE_SAT_THR1 = {
.baseAddress = 0x19BC,
.baseOffset = 0U,
.baseLength = 12U,
};
FileConfig reg19_Lna1Min1 = {
.baseAddress = 0x19C0,
.baseOffset = 21U,
.baseLength = 3U,
};
FileConfig reg19_Lna1Bias2Min1 = {
.baseAddress = 0x19C0,
.baseOffset = 18U,
.baseLength = 3U,
};
FileConfig reg19_Lna2BiasMin1 = {
.baseAddress = 0x19C0,
.baseOffset = 14U,
.baseLength = 4U,
};
FileConfig reg19_Lna2Min1 = {
.baseAddress = 0x19C0,
.baseOffset = 12U,
.baseLength = 2U,
};
FileConfig reg19_Lna1Max1 = {
.baseAddress = 0x19C0,
.baseOffset = 9U,
.baseLength = 3U,
};
FileConfig reg19_Lna1Bias2Max1 = {
.baseAddress = 0x19C0,
.baseOffset = 6U,
.baseLength = 3U,
};
FileConfig reg19_Lna2BiasMax1 = {
.baseAddress = 0x19C0,
.baseOffset = 2U,
.baseLength = 4U,
};
FileConfig reg19_Lna2Max1 = {
.baseAddress = 0x19C0,
.baseOffset = 0U,
.baseLength = 2U,
};
FileConfig reg19_DelayDisable = {
.baseAddress = 0x19C4,
.baseOffset = 7U,
.baseLength = 1U,
};
FileConfig reg19_Cache_Width = {
.baseAddress = 0x19C4,
.baseOffset = 4U,
.baseLength = 3U,
};
FileConfig reg19_Cache_Enable = {
.baseAddress = 0x19C4,
.baseOffset = 3U,
.baseLength = 1U,
};
FileConfig reg19_Dual_RX_Control = {
.baseAddress = 0x19C4,
.baseOffset = 2U,
.baseLength = 1U,
};
FileConfig reg19_RX1_ForceFlg = {
.baseAddress = 0x19C4,
.baseOffset = 1U,
.baseLength = 1U,
};
FileConfig reg19_RX1_Enabled = {
.baseAddress = 0x19C4,
.baseOffset = 0U,
.baseLength = 1U,
};
