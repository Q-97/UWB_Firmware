#include "cali_reg.h"
FileConfig reg18_RIDTAG = {
  .baseAddress = 0x1800,
.baseOffset = 16U,
.baseLength = 16U,
};
FileConfig reg18_MODEL = {
   .baseAddress = 0x1800,
.baseOffset = 8U,
.baseLength = 8U,
};
FileConfig reg18_VER = {
     .baseAddress = 0x1800,
.baseOffset = 4U,
.baseLength = 4U,
};
FileConfig reg18_REV = {
     .baseAddress = 0x1800,
.baseOffset = 0U,
.baseLength = 4U,
};
FileConfig reg18_TX_STAMP_H32 = {
.baseAddress = 0x182C,
.baseOffset = 0U,
.baseLength = 32U,
};
FileConfig reg18_TX_STAMP_L8 = {
.baseAddress = 0x1830,
.baseOffset = 0U,
.baseLength = 8U,
};
FileConfig reg18_TX_RAW = {
  .baseAddress = 0x1834,
.baseOffset = 0U,
.baseLength = 32U,
};
FileConfig reg18_Ant_flag = {
.baseAddress = 0x1868,
.baseOffset = 30U,
.baseLength = 1U,
};
FileConfig reg18_agc_gain_cnt = {
.baseAddress = 0x1868,
.baseOffset = 24U,
.baseLength = 6U,
};
FileConfig reg18_agc_to_vga = {
.baseAddress = 0x1868,
.baseOffset = 0U,
.baseLength = 23U,
};
FileConfig reg18_agc_mem_index = {
.baseAddress = 0x1870,
.baseOffset = 9U,
.baseLength = 23U,
};
FileConfig reg18_rx_mem_index = {
.baseAddress = 0x1870,
.baseOffset = 0U,
.baseLength = 9U,
};
FileConfig reg18_Big_Detect_Value1 = {
.baseAddress = 0x188C,
.baseOffset = 16U,
.baseLength = 14U,
};
FileConfig reg18_Big_Detect_Value = {
.baseAddress = 0x188C,
.baseOffset = 0U,
.baseLength = 14U,
};
FileConfig reg18_AgcOutToPreamFlag = {
.baseAddress = 0x18E0,
.baseOffset = 24U,
.baseLength = 1U,
};
FileConfig reg18_AgcSmallWindowCounter = {
.baseAddress = 0x18E0,
.baseOffset = 8U,
.baseLength = 16U,
};
FileConfig reg18_isGitRamFull = {
.baseAddress = 0x18E0,
.baseOffset = 7U,
.baseLength = 1U,
};
FileConfig reg18_isIQFull = {
.baseAddress = 0x18E0,
.baseOffset = 6U,
.baseLength = 1U,
};
FileConfig reg18_LnaSwitchFlag = {
.baseAddress = 0x18E0,
.baseOffset = 5U,
.baseLength = 1U,
};
FileConfig reg18_DesireValueFreeze = {
.baseAddress = 0x18E0,
.baseOffset = 4U,
.baseLength = 1U,
};
FileConfig reg18_AGC_STATE = {
.baseAddress = 0x18E0,
.baseOffset = 0U,
.baseLength = 4U,
};
FileConfig reg18_EUI_64_L32 = {
.baseAddress = 0x1804,
.baseOffset = 0U,
.baseLength = 32U,
};
FileConfig reg18_EUI_64_H32 = {
.baseAddress = 0x1808,
.baseOffset = 0U,
.baseLength = 32U,
};
FileConfig reg18_PAN_ID   = {
.baseAddress = 0x180C,
.baseOffset = 16U,
.baseLength = 16U,
};
FileConfig reg18_SHORTADDR = {
.baseAddress = 0x180C,
.baseOffset = 0U,
.baseLength = 16U,
};
FileConfig reg18_PDOA_RX1_TIME_En = {
.baseAddress = 0x1810,
.baseOffset = 27U,
.baseLength = 1U,
};
FileConfig reg18_Extend_Antenna_Flg_RX0 = {
.baseAddress = 0x1810,
.baseOffset = 26U,
.baseLength = 1U,
};
FileConfig reg18_Extend_Antenna_Flg_RX1 = {
.baseAddress = 0x1810,
.baseOffset = 25U,
.baseLength = 1U,
};
FileConfig reg18_CP_RakeEn = {
.baseAddress = 0x1810,
.baseOffset = 24U,
.baseLength = 1U,
};
FileConfig reg18_IP_RakeEn = {
.baseAddress = 0x1810,
.baseOffset = 23U,
.baseLength = 1U,
};
FileConfig reg18_Resample_Flg = {
.baseAddress = 0x1810,
.baseOffset = 22U,
.baseLength = 1U,
};
FileConfig reg18_Phase_Flg = {
.baseAddress = 0x1810,
.baseOffset = 20U,
.baseLength = 2U,
};
FileConfig reg18_DIS_DCEn = {
.baseAddress = 0x1810,
.baseOffset = 19U,
.baseLength = 1U,
};
FileConfig reg18_FOC_Init = {
.baseAddress = 0x1810,
.baseOffset = 18U,
.baseLength = 1U,
};
FileConfig reg18_DIS_Rake = {
.baseAddress = 0x1810,
.baseOffset = 17U,
.baseLength = 1U,
};
FileConfig reg18_DIS_TRACK = {
.baseAddress = 0x1810,
.baseOffset = 16U,
.baseLength = 1U,
};
FileConfig reg18_PDOA_EN = {
 .baseAddress = 0x1810,
.baseOffset = 15U,
.baseLength = 1U,
};
FileConfig reg18_FOE_DIS = {
 .baseAddress = 0x1810,
.baseOffset = 14U,
.baseLength = 1U,
};
FileConfig reg18_FAST_AAT = {
.baseAddress = 0x1810,
.baseOffset = 13U,
.baseLength = 1U,
};
FileConfig reg18_CP_SPS = {
  .baseAddress = 0x1810,
.baseOffset = 11U,
.baseLength = 2U,
};
FileConfig reg18_AUTO_ACK = {
.baseAddress = 0x1810,
.baseOffset = 10U,
.baseLength = 1U,
};
FileConfig reg18_RXAUTR = {
  .baseAddress = 0x1810,
.baseOffset = 9U,
.baseLength = 1U,
};
FileConfig reg18_RXWTOE = {
  .baseAddress = 0x1810,
.baseOffset = 8U,
.baseLength = 1U,
};
FileConfig reg18_CIA_STS = {
 .baseAddress = 0x1810,
.baseOffset = 7U,
.baseLength = 1U,
};
FileConfig reg18_CIA_IPATOV = {
.baseAddress = 0x1810,
.baseOffset = 6U,
.baseLength = 1U,
};
FileConfig reg18_SPI_CRCEN = {
.baseAddress = 0x1810,
.baseOffset = 5U,
.baseLength = 1U,
};
FileConfig reg18_PHR_6M8 = {
 .baseAddress = 0x1810,
.baseOffset = 4U,
.baseLength = 1U,
};
FileConfig reg18_PHR_MODE = {
.baseAddress = 0x1810,
.baseOffset = 3U,
.baseLength = 1U,
};
FileConfig reg18_DIS_DRXB = {
.baseAddress = 0x1810,
.baseOffset = 2U,
.baseLength = 1U,
};
FileConfig reg18_DIS_FCST = {
.baseAddress = 0x1810,
.baseOffset = 1U,
.baseLength = 1U,
};
FileConfig reg18_FFEN = {
    .baseAddress = 0x1810,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg18_agc_clk_gaten = {
.baseAddress = 0x1814,
.baseOffset = 18U,
.baseLength = 1U,
};
FileConfig reg18_tx_clk125m_gaten = {
.baseAddress = 0x1814,
.baseOffset = 17U,
.baseLength = 1U,
};
FileConfig reg18_tx_clk500m_gaten = {
.baseAddress = 0x1814,
.baseOffset = 16U,
.baseLength = 1U,
};
FileConfig reg18_LSADRAPE = {
.baseAddress = 0x1814,
.baseOffset = 15U,
.baseLength = 1U,
};
FileConfig reg18_SSADRAPE = {
.baseAddress = 0x1814,
.baseOffset = 14U,
.baseLength = 1U,
};
FileConfig reg18_LE3_PEND = {
.baseAddress = 0x1814,
.baseOffset = 13U,
.baseLength = 1U,
};
FileConfig reg18_LE2_PEND = {
.baseAddress = 0x1814,
.baseOffset = 12U,
.baseLength = 1U,
};
FileConfig reg18_LE1_PEND = {
.baseAddress = 0x1814,
.baseOffset = 11U,
.baseLength = 1U,
};
FileConfig reg18_LE0_PEND = {
.baseAddress = 0x1814,
.baseOffset = 10U,
.baseLength = 1U,
};
FileConfig reg18_FFIB = {
    .baseAddress = 0x1814,
.baseOffset = 9U,
.baseLength = 1U,
};
FileConfig reg18_FFBC = {
    .baseAddress = 0x1814,
.baseOffset = 8U,
.baseLength = 1U,
};
FileConfig reg18_FFAE = {
    .baseAddress = 0x1814,
.baseOffset = 7U,
.baseLength = 1U,
};
FileConfig reg18_FFAF = {
    .baseAddress = 0x1814,
.baseOffset = 6U,
.baseLength = 1U,
};
FileConfig reg18_FFAMULT = {
 .baseAddress = 0x1814,
.baseOffset = 5U,
.baseLength = 1U,
};
FileConfig reg18_FFAR = {
    .baseAddress = 0x1814,
.baseOffset = 4U,
.baseLength = 1U,
};
FileConfig reg18_FFAM = {
    .baseAddress = 0x1814,
.baseOffset = 3U,
.baseLength = 1U,
};
FileConfig reg18_FFAA = {
    .baseAddress = 0x1814,
.baseOffset = 2U,
.baseLength = 1U,
};
FileConfig reg18_FFAD = {
    .baseAddress = 0x1814,
.baseOffset = 1U,
.baseLength = 1U,
};
FileConfig reg18_FFAB = {
    .baseAddress = 0x1814,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg18_TXBOFFS = {
 .baseAddress = 0x1818,
.baseOffset = 16U,
.baseLength = 10U,
};
FileConfig reg18_TR = {
      .baseAddress = 0x1818,
.baseOffset = 10U,
.baseLength = 1U,
};
FileConfig reg18_TFLEN = {
   .baseAddress = 0x1818,
.baseOffset = 0U,
.baseLength = 10U,
};
FileConfig reg18_TXBR = {
    .baseAddress = 0x181C,
.baseOffset = 8U,
.baseLength = 2U,
};
FileConfig reg18_TXPSR = {
   .baseAddress = 0x181C,
.baseOffset = 0U,
.baseLength = 4U,
};
FileConfig reg18_LE_ADDR1 = {
.baseAddress = 0x1820,
.baseOffset = 16U,
.baseLength = 16U,
};
FileConfig reg18_LE_ADDR0 = {
.baseAddress = 0x1820,
.baseOffset = 0U,
.baseLength = 16U,
};
FileConfig reg18_LE_ADDR3 = {
.baseAddress = 0x1824,
.baseOffset = 16U,
.baseLength = 16U,
};
FileConfig reg18_LE_ADDR2 = {
.baseAddress = 0x1824,
.baseOffset = 0U,
.baseLength = 16U,
};
FileConfig reg18_RX_PCODE = {
.baseAddress = 0x1828,
.baseOffset = 16U,
.baseLength = 5U,
};
FileConfig reg18_TX_PCODE = {
.baseAddress = 0x1828,
.baseOffset = 8U,
.baseLength = 5U,
};
FileConfig reg18_SFDTYPE = {
 .baseAddress = 0x1828,
.baseOffset = 3U,
.baseLength = 2U,
};
FileConfig reg18_CHAN = {
    .baseAddress = 0x1828,
.baseOffset = 0U,
.baseLength = 3U,
};
FileConfig reg18_RX_ANTD = {
 .baseAddress = 0x1838,
.baseOffset = 16U,
.baseLength = 16U,
};
FileConfig reg18_TX_ANTD = {
 .baseAddress = 0x1838,
.baseOffset = 0U,
.baseLength = 16U,
};
FileConfig reg18_b0b1_dff_2ns_sel = {
.baseAddress = 0x183C,
.baseOffset = 1U,
.baseLength = 1U,
};
FileConfig reg18_clk_500mhz_pn_edg_sel = {
.baseAddress = 0x183C,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg18_dfdmem_base = {
.baseAddress = 0x1840,
.baseOffset = 8U,
.baseLength = 12U,
};
FileConfig reg18_p2s_delay = {
.baseAddress = 0x1840,
.baseOffset = 0U,
.baseLength = 7U,
};
FileConfig reg18_txrx_test_en = {
.baseAddress = 0x1844,
.baseOffset = 31U,
.baseLength = 1U,
};
FileConfig reg18_rd_once = {
 .baseAddress = 0x1844,
.baseOffset = 30U,
.baseLength = 1U,
};
FileConfig reg18_rx_cobr = {
 .baseAddress = 0x1844,
.baseOffset = 29U,
.baseLength = 1U,
};
FileConfig reg18_rx_cibr = {
 .baseAddress = 0x1844,
.baseOffset = 28U,
.baseLength = 1U,
};
FileConfig reg18_tx_cobr = {
 .baseAddress = 0x1844,
.baseOffset = 27U,
.baseLength = 1U,
};
FileConfig reg18_tx_cibr = {
 .baseAddress = 0x1844,
.baseOffset = 26U,
.baseLength = 1U,
};
FileConfig reg18_rxwr_mode = {
.baseAddress = 0x1844,
.baseOffset = 23U,
.baseLength = 3U,
};
FileConfig reg18_wr_mode = {
 .baseAddress = 0x1844,
.baseOffset = 21U,
.baseLength = 2U,
};
FileConfig reg18_rx0rx1_sel = {
.baseAddress = 0x1844,
.baseOffset = 20U,
.baseLength = 1U,
};
FileConfig reg18_ram_wren = {
.baseAddress = 0x1844,
.baseOffset = 19U,
.baseLength = 1U,
};
FileConfig reg18_tx_rden = {
 .baseAddress = 0x1844,
.baseOffset = 18U,
.baseLength = 1U,
};
FileConfig reg18_txdata_sel = {
.baseAddress = 0x1844,
.baseOffset = 17U,
.baseLength = 1U,
};
FileConfig reg18_endian_sel = {
.baseAddress = 0x1844,
.baseOffset = 16U,
.baseLength = 1U,
};
FileConfig reg18_ciamem_base = {
.baseAddress = 0x1844,
.baseOffset = 0U,
.baseLength = 14U,
};
FileConfig reg18_dfd_tx_en = {
.baseAddress = 0x1848,
.baseOffset = 30U,
.baseLength = 1U,
};
FileConfig reg18_dfd_rx_en_2nd = {
.baseAddress = 0x1848,
.baseOffset = 29U,
.baseLength = 1U,
};
FileConfig reg18_dfd_rx_en = {
.baseAddress = 0x1848,
.baseOffset = 28U,
.baseLength = 1U,
};
FileConfig reg18_agcdebug_en_2nd = {
.baseAddress = 0x1848,
.baseOffset = 27U,
.baseLength = 1U,
};
FileConfig reg18_agcdebug_en = {
.baseAddress = 0x1848,
.baseOffset = 26U,
.baseLength = 1U,
};
FileConfig reg18_AgcMode = {
 .baseAddress = 0x1848,
.baseOffset = 24U,
.baseLength = 2U,
};
FileConfig reg18_Agc_G_Is_Set = {
.baseAddress = 0x1848,
.baseOffset = 23U,
.baseLength = 1U,
};
FileConfig reg18_Agc_G_Set_Value = {
.baseAddress = 0x1848,
.baseOffset = 16U,
.baseLength = 7U,
};
FileConfig reg18_AGC_input_7bit = {
.baseAddress = 0x1848,
.baseOffset = 15U,
.baseLength = 1U,
};
FileConfig reg18_agc_detector_big_len = {
.baseAddress = 0x1848,
.baseOffset = 8U,
.baseLength = 7U,
};
FileConfig reg18_agc_detector_len = {
.baseAddress = 0x1848,
.baseOffset = 0U,
.baseLength = 7U,
};
FileConfig reg18_agc_step = {
.baseAddress = 0x184C,
.baseOffset = 16U,
.baseLength = 14U,
};
FileConfig reg18_agc_detector_threshold_max = {
.baseAddress = 0x184C,
.baseOffset = 0U,
.baseLength = 14U,
};
FileConfig reg18_agc_quantiz_step = {
.baseAddress = 0x1850,
.baseOffset = 16U,
.baseLength = 14U,
};
FileConfig reg18_desire_value = {
.baseAddress = 0x1850,
.baseOffset = 0U,
.baseLength = 9U,
};
FileConfig reg18_agc_adj_high_power_thr = {
.baseAddress = 0x1854,
.baseOffset = 24U,
.baseLength = 6U,
};
FileConfig reg18_agc_adj_low_power_thr = {
.baseAddress = 0x1854,
.baseOffset = 16U,
.baseLength = 6U,
};
FileConfig reg18_agc_table_idx = {
.baseAddress = 0x1854,
.baseOffset = 12U,
.baseLength = 2U,
};
FileConfig reg18_agc_quantiz_min = {
.baseAddress = 0x1854,
.baseOffset = 0U,
.baseLength = 12U,
};
FileConfig reg18_agc_big_step = {
.baseAddress = 0x1858,
.baseOffset = 24U,
.baseLength = 3U,
};
FileConfig reg18_agc_high_power_adj = {
.baseAddress = 0x1858,
.baseOffset = 16U,
.baseLength = 6U,
};
FileConfig reg18_agc_low_power_adj = {
.baseAddress = 0x1858,
.baseOffset = 8U,
.baseLength = 6U,
};
FileConfig reg18_agc_nor_power_adj = {
.baseAddress = 0x1858,
.baseOffset = 0U,
.baseLength = 6U,
};
FileConfig reg18_agc_reset_init = {
.baseAddress = 0x185C,
.baseOffset = 16U,
.baseLength = 15U,
};
FileConfig reg18_Agc_Desire_HighPower_Threshold = {
.baseAddress = 0x185C,
.baseOffset = 8U,
.baseLength = 6U,
};
FileConfig reg18_Agc_Desire_LowPower_Threshold = {
.baseAddress = 0x185C,
.baseOffset = 0U,
.baseLength = 6U,
};
FileConfig reg18_Agc_HighPower_Desier = {
.baseAddress = 0x1860,
.baseOffset = 16U,
.baseLength = 13U,
};
FileConfig reg18_Agc_NormalPower_Desire = {
.baseAddress = 0x1860,
.baseOffset = 0U,
.baseLength = 13U,
};
FileConfig reg18_Agc_LowPower_Desire = {
.baseAddress = 0x1864,
.baseOffset = 16U,
.baseLength = 13U,
};
FileConfig reg18_Detector_Len_After_Preamble = {
.baseAddress = 0x1864,
.baseOffset = 8U,
.baseLength = 7U,
};
FileConfig reg18_Detcetor_BigLen_After_Preable = {
.baseAddress = 0x1864,
.baseOffset = 0U,
.baseLength = 7U,
};
FileConfig reg18_rx_clk_gate = {
.baseAddress = 0x1874,
.baseOffset = 0U,
.baseLength = 32U,
};
FileConfig reg18_rx_debug = {
.baseAddress = 0x1878,
.baseOffset = 0U,
.baseLength = 32U,
};
FileConfig reg18_Preamble_During_Bit = {
.baseAddress = 0x187C,
.baseOffset = 1U,
.baseLength = 1U,
};
FileConfig reg18_PHR_Extend_Mode_1 = {
.baseAddress = 0x187C,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg18_gain_delay = {
.baseAddress = 0x1880,
.baseOffset = 0U,
.baseLength = 32U,
};
FileConfig reg18_allRx_use_rx0_Lnaswitch_flag = {
.baseAddress = 0x1884,
.baseOffset = 29U,
.baseLength = 1U,
};
FileConfig reg18_After_PRD_Desier = {
.baseAddress = 0x1884,
.baseOffset = 16U,
.baseLength = 13U,
};
FileConfig reg18_Agc_gain_sel = {
.baseAddress = 0x1884,
.baseOffset = 15U,
.baseLength = 1U,
};
FileConfig reg18_is_Peak_Out = {
.baseAddress = 0x1884,
.baseOffset = 14U,
.baseLength = 1U,
};
FileConfig reg18_Peak_Out_Threshold = {
.baseAddress = 0x1884,
.baseOffset = 0U,
.baseLength = 14U,
};
FileConfig reg18_agc_detector_threshold_min = {
.baseAddress = 0x1888,
.baseOffset = 16U,
.baseLength = 14U,
};
FileConfig reg18_AgcVariableStep = {
.baseAddress = 0x1888,
.baseOffset = 0U,
.baseLength = 14U,
};
FileConfig reg18_Is_Peak_Detect = {
.baseAddress = 0x1894,
.baseOffset = 22U,
.baseLength = 1U,
};
FileConfig reg18_Default_Max_Gain = {
.baseAddress = 0x1894,
.baseOffset = 17U,
.baseLength = 5U,
};
FileConfig reg18_Last_gain_Bit_Max = {
.baseAddress = 0x1894,
.baseOffset = 12U,
.baseLength = 5U,
};
FileConfig reg18_Vga_max = {
 .baseAddress = 0x1894,
.baseOffset = 8U,
.baseLength = 4U,
};
FileConfig reg18_Tia_Max = {
 .baseAddress = 0x1894,
.baseOffset = 4U,
.baseLength = 4U,
};
FileConfig reg18_Agc_Out_Mode = {
.baseAddress = 0x1894,
.baseOffset = 2U,
.baseLength = 2U,
};
FileConfig reg18_Vga_Mode = {
.baseAddress = 0x1894,
.baseOffset = 1U,
.baseLength = 1U,
};
FileConfig reg18_Tia_Mode = {
.baseAddress = 0x1894,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg18_Tia_Fix_Gain_Idx = {
.baseAddress = 0x1898,
.baseOffset = 25U,
.baseLength = 4U,
};
FileConfig reg18_IQ_Full_Value = {
.baseAddress = 0x1898,
.baseOffset = 19U,
.baseLength = 6U,
};
FileConfig reg18_gBit_Ram_Len = {
.baseAddress = 0x1898,
.baseOffset = 15U,
.baseLength = 4U,
};
FileConfig reg18_OutPut_Choose_High_Gain = {
.baseAddress = 0x1898,
.baseOffset = 14U,
.baseLength = 1U,
};
FileConfig reg18_Adjust_Agc_Bit = {
.baseAddress = 0x1898,
.baseOffset = 10U,
.baseLength = 4U,
};
FileConfig reg18_Is_Lock_Lna_After_PRD = {
.baseAddress = 0x1898,
.baseOffset = 9U,
.baseLength = 1U,
};
FileConfig reg18_After_PRD_Detect_Len = {
.baseAddress = 0x1898,
.baseOffset = 0U,
.baseLength = 9U,
};
FileConfig reg18_Lna1Min = {
 .baseAddress = 0x189C,
.baseOffset = 26U,
.baseLength = 3U,
};
FileConfig reg18_Lna1Bias2Min = {
.baseAddress = 0x189C,
.baseOffset = 23U,
.baseLength = 3U,
};
FileConfig reg18_Lna2BiasMin = {
.baseAddress = 0x189C,
.baseOffset = 19U,
.baseLength = 4U,
};
FileConfig reg18_Lna2Min = {
 .baseAddress = 0x189C,
.baseOffset = 17U,
.baseLength = 2U,
};
FileConfig reg18_Lna1Max = {
 .baseAddress = 0x189C,
.baseOffset = 14U,
.baseLength = 3U,
};
FileConfig reg18_Lna1Bias2Max = {
.baseAddress = 0x189C,
.baseOffset = 11U,
.baseLength = 3U,
};
FileConfig reg18_Lna2BiasMax = {
.baseAddress = 0x189C,
.baseOffset = 7U,
.baseLength = 4U,
};
FileConfig reg18_Lna2Max = {
 .baseAddress = 0x189C,
.baseOffset = 5U,
.baseLength = 2U,
};
FileConfig reg18_Lna_Tia_Gain_Table0 = {
.baseAddress = 0x189C,
.baseOffset = 0U,
.baseLength = 5U,
};
FileConfig reg18_Lna_Tia_Gain_Table1 = {
.baseAddress = 0x18A0,
.baseOffset = 0U,
.baseLength = 5U,
};
FileConfig reg18_Lna_Tia_Gain_Table2 = {
.baseAddress = 0x18A4,
.baseOffset = 0U,
.baseLength = 5U,
};
FileConfig reg18_Lna_Tia_Gain_Table3 = {
.baseAddress = 0x18A8,
.baseOffset = 0U,
.baseLength = 5U,
};
FileConfig reg18_Lna_Tia_Gain_Table4 = {
.baseAddress = 0x18AC,
.baseOffset = 0U,
.baseLength = 5U,
};
FileConfig reg18_Lna_Tia_Gain_Table5 = {
.baseAddress = 0x18B0,
.baseOffset = 0U,
.baseLength = 5U,
};
FileConfig reg18_Lna_Tia_Gain_Table6 = {
.baseAddress = 0x18B4,
.baseOffset = 0U,
.baseLength = 5U,
};
FileConfig reg18_Lna_Tia_Gain_Table7 = {
.baseAddress = 0x18B8,
.baseOffset = 0U,
.baseLength = 5U,
};
FileConfig reg18_Lna_Tia_Gain_Table8 = {
.baseAddress = 0x18BC,
.baseOffset = 0U,
.baseLength = 5U,
};
FileConfig reg18_Lna_Tia_Gain_Table9 = {
.baseAddress = 0x18C0,
.baseOffset = 0U,
.baseLength = 5U,
};
FileConfig reg18_Lna_Tia_Gain_Table10 = {
.baseAddress = 0x18C4,
.baseOffset = 0U,
.baseLength = 5U,
};
FileConfig reg18_Lna_Tia_Gain_Table11 = {
.baseAddress = 0x18C8,
.baseOffset = 0U,
.baseLength = 5U,
};
FileConfig reg18_Lna_Tia_Gain_Table12 = {
.baseAddress = 0x18CC,
.baseOffset = 0U,
.baseLength = 5U,
};
FileConfig reg18_Is_Adjust_last_gain = {
.baseAddress = 0x18D0,
.baseOffset = 25U,
.baseLength = 1U,
};
FileConfig reg18_Adjust_last_Gain_high_Thr = {
.baseAddress = 0x18D0,
.baseOffset = 20U,
.baseLength = 5U,
};
FileConfig reg18_Adjust_last_Gain_low_Thr = {
.baseAddress = 0x18D0,
.baseOffset = 15U,
.baseLength = 5U,
};
FileConfig reg18_Adjust_Last_High = {
.baseAddress = 0x18D0,
.baseOffset = 10U,
.baseLength = 5U,
};
FileConfig reg18_Adjust_Last_Low = {
.baseAddress = 0x18D0,
.baseOffset = 5U,
.baseLength = 5U,
};
FileConfig reg18_Adjust_Last_Norm = {
.baseAddress = 0x18D0,
.baseOffset = 0U,
.baseLength = 5U,
};
FileConfig reg18_Agc_Set_Fixed_Gain = {
.baseAddress = 0x18D4,
.baseOffset = 22U,
.baseLength = 1U,
};
FileConfig reg18_AGC_LNA1_gain = {
.baseAddress = 0x18D4,
.baseOffset = 19U,
.baseLength = 3U,
};
FileConfig reg18_AGC_lna1_Bias2 = {
.baseAddress = 0x18D4,
.baseOffset = 16U,
.baseLength = 3U,
};
FileConfig reg18_AGC_Lna2_Bias = {
.baseAddress = 0x18D4,
.baseOffset = 12U,
.baseLength = 4U,
};
FileConfig reg18_AGC_LNA2_gain = {
.baseAddress = 0x18D4,
.baseOffset = 10U,
.baseLength = 2U,
};
FileConfig reg18_AGC_TIA_gain = {
.baseAddress = 0x18D4,
.baseOffset = 6U,
.baseLength = 4U,
};
FileConfig reg18_AGC_VGA_Gain = {
.baseAddress = 0x18D4,
.baseOffset = 0U,
.baseLength = 6U,
};
FileConfig reg18_Diff_Sum_Len = {
.baseAddress = 0x18D8,
.baseOffset = 20U,
.baseLength = 5U,
};
FileConfig reg18_Agc_Stable_Value = {
.baseAddress = 0x18D8,
.baseOffset = 15U,
.baseLength = 5U,
};
FileConfig reg18_Set_Restore_Gain = {
.baseAddress = 0x18D8,
.baseOffset = 10U,
.baseLength = 5U,
};
FileConfig reg18_Is_Restore_Gain_Switch_Ant = {
.baseAddress = 0x18D8,
.baseOffset = 9U,
.baseLength = 1U,
};
FileConfig reg18_Ant_Id = {
  .baseAddress = 0x18D8,
.baseOffset = 7U,
.baseLength = 2U,
};
FileConfig reg18_Switch_Ant_Threshold = {
.baseAddress = 0x18D8,
.baseOffset = 2U,
.baseLength = 5U,
};
FileConfig reg18_AGC_Switch_Ant_Mode = {
.baseAddress = 0x18D8,
.baseOffset = 0U,
.baseLength = 2U,
};
FileConfig reg18_AGC_Is_Control_Ant1 = {
.baseAddress = 0x18DC,
.baseOffset = 1U,
.baseLength = 1U,
};
FileConfig reg18_AGC_Is_Control_Ant = {
.baseAddress = 0x18DC,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg18_TiaAdjust = {
.baseAddress = 0x18E4,
.baseOffset = 21U,
.baseLength = 3U,
};
FileConfig reg18_VgaAdjust = {
.baseAddress = 0x18E4,
.baseOffset = 18U,
.baseLength = 3U,
};
FileConfig reg18_ManualSetGain = {
.baseAddress = 0x18E4,
.baseOffset = 13U,
.baseLength = 5U,
};
FileConfig reg18_DesireAfterAnt = {
.baseAddress = 0x18E4,
.baseOffset = 0U,
.baseLength = 13U,
};
FileConfig reg18_AgcOutToPreambThre = {
.baseAddress = 0x18E8,
.baseOffset = 27U,
.baseLength = 5U,
};
FileConfig reg18_DesireAfterLna = {
.baseAddress = 0x18E8,
.baseOffset = 14U,
.baseLength = 13U,
};
FileConfig reg18_SetRestAfterLnaSwitch = {
.baseAddress = 0x18E8,
.baseOffset = 9U,
.baseLength = 5U,
};
FileConfig reg18_isRestAfterLnaSwitch = {
.baseAddress = 0x18E8,
.baseOffset = 7U,
.baseLength = 2U,
};
FileConfig reg18_LnaSwitchThr = {
.baseAddress = 0x18E8,
.baseOffset = 2U,
.baseLength = 5U,
};
FileConfig reg18_LnaSwitchMode = {
.baseAddress = 0x18E8,
.baseOffset = 0U,
.baseLength = 2U,
};
FileConfig reg18_AntSwitchDelay = {
.baseAddress = 0x18EC,
.baseOffset = 12U,
.baseLength = 12U,
};
FileConfig reg18_LnaSwitchDelay = {
.baseAddress = 0x18EC,
.baseOffset = 0U,
.baseLength = 12U,
};
FileConfig reg18_DesireBaseOnBigWin = {
.baseAddress = 0x18F0,
.baseOffset = 30U,
.baseLength = 1U,
};
FileConfig reg18_WaitGbitMeanTime = {
.baseAddress = 0x18F0,
.baseOffset = 20U,
.baseLength = 10U,
};
FileConfig reg18_NormDesireLockTime = {
.baseAddress = 0x18F0,
.baseOffset = 12U,
.baseLength = 8U,
};
FileConfig reg18_AgcGainLockTime = {
.baseAddress = 0x18F0,
.baseOffset = 2U,
.baseLength = 10U,
};
FileConfig reg18_isGbitMean = {
.baseAddress = 0x18F0,
.baseOffset = 1U,
.baseLength = 1U,
};
FileConfig reg18_AntSwitchIsOnLna = {
.baseAddress = 0x18F0,
.baseOffset = 0U,
.baseLength = 1U,
};
FileConfig reg18_WaitLnaswitchTime = {
.baseAddress = 0x18F4,
.baseOffset = 12U,
.baseLength = 12U,
};
FileConfig reg18_WaitAntSwitchTime = {
.baseAddress = 0x18F4,
.baseOffset = 0U,
.baseLength = 12U,
};
FileConfig reg18_PREAMBLE_SAT_SYMBOL = {
.baseAddress = 0x18F8,
.baseOffset = 12U,
.baseLength = 4U,
};
FileConfig reg18_PREAMLBE_SAT_THR = {
.baseAddress = 0x18F8,
.baseOffset = 0U,
.baseLength = 12U,
};
