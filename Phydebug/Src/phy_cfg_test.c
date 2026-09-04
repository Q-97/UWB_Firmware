/*****************************************************************************
* File: cfg_test.c
*
* Descirption: this file contains the functions to test phy configuration.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 6
*****************************************************************************/
#include "zn_interface.h"
#include "zn_regs.h"
#include "base_addr.h"
#include "string.h"
#include "phy_cfg_test.h"


static zn_config_t s_config_set[CFG_NUM] = 
{
    {CHANNEL_5, 0, RFRAME_SP0, PREAMBLE_CODE_INDEX_9,  SFD_ID_LEGACY_SFD8, PSDU_RATE_850, BPRF_PHR_RATE_850, PREAMBLE_16,   PRF_624,  STS_SEG_1, STS_SEG_LEN_16},
    {CHANNEL_9, 0, RFRAME_SP1, PREAMBLE_CODE_INDEX_10, SFD_ID_SFD8,        PSDU_RATE_681, BPRF_PHR_RATE_850, PREAMBLE_64,   PRF_1248, STS_SEG_2, STS_SEG_LEN_32},
    {CHANNEL_9, 0, RFRAME_SP3, PREAMBLE_CODE_INDEX_11, SFD_ID_SFD16,       PSDU_RATE_272, BPRF_PHR_RATE_850, PREAMBLE_1024, PRF_2496, STS_SEG_3, STS_SEG_LEN_64},
    {CHANNEL_9, 0, RFRAME_SP1, PREAMBLE_CODE_INDEX_12, SFD_ID_SFD4,        PSDU_RATE_850, BPRF_PHR_RATE_850, PREAMBLE_4096, PRF_624,  STS_SEG_4, STS_SEG_LEN_128},
    {CHANNEL_9, 0, RFRAME_SP0, PREAMBLE_CODE_INDEX_13, SFD_ID_SFD8,        PSDU_RATE_850, BPRF_PHR_RATE_850, PREAMBLE_32,   PRF_624,  STS_SEG_1, STS_SEG_LEN_64},
    {CHANNEL_9, 0, RFRAME_SP0, PREAMBLE_CODE_INDEX_14, SFD_ID_SFD8,        PSDU_RATE_850, BPRF_PHR_RATE_850, PREAMBLE_128,  PRF_624,  STS_SEG_1, STS_SEG_LEN_64},
    {CHANNEL_9, 0, RFRAME_SP0, PREAMBLE_CODE_INDEX_15, SFD_ID_SFD8,        PSDU_RATE_850, BPRF_PHR_RATE_850, PREAMBLE_256,  PRF_624,  STS_SEG_1, STS_SEG_LEN_64},
    {CHANNEL_9, 0, RFRAME_SP0, PREAMBLE_CODE_INDEX_16, SFD_ID_SFD8,        PSDU_RATE_850, BPRF_PHR_RATE_850, PREAMBLE_512,  PRF_624,  STS_SEG_1, STS_SEG_LEN_64},
    {CHANNEL_9, 0, RFRAME_SP0, PREAMBLE_CODE_INDEX_17, SFD_ID_SFD8,        PSDU_RATE_850, BPRF_PHR_RATE_850, PREAMBLE_2048, PRF_624,  STS_SEG_1, STS_SEG_LEN_64},
    {CHANNEL_9, 0, RFRAME_SP0, PREAMBLE_CODE_INDEX_18, SFD_ID_SFD8,        PSDU_RATE_850, BPRF_PHR_RATE_850, PREAMBLE_2048, PRF_624,  STS_SEG_1, STS_SEG_LEN_64},
    {CHANNEL_9, 0, RFRAME_SP0, PREAMBLE_CODE_INDEX_32, SFD_ID_SFD8,        PSDU_RATE_850, BPRF_PHR_RATE_850, PREAMBLE_2048, PRF_624,  STS_SEG_1, STS_SEG_LEN_64}
};

static uint32_t s_register_data[CFG_NUM][REG_NUM] = 
{
    {0x1c401c4, 0x00080803, 0x298c8092, 0x00000100, 0x08400000, 0x00000000},
    {0x1c409c4, 0x0009090e, 0x508c8092, 0x00000201, 0x10500000, 0x00000001},
    {0x1c419c4, 0x000a0a16, 0x508c8092, 0x00000302, 0x20600000, 0x00000003},
    {0x1c409c4, 0x000b0b1e, 0x508c8092, 0x00000103, 0x40700000, 0x00000002},
    {0x1c401c4, 0x000c0c0e, 0x508c8092, 0x00000104, 0x20400000, 0x00000002},
    {0x1c401c4, 0x000d0d0e, 0x508c8092, 0x00000105, 0x20400000, 0x00000002},
    {0x1c401c4, 0x000e0e0e, 0x508c8092, 0x00000106, 0x20400000, 0x00000002},
    {0x1c401c4, 0x000f0f0e, 0x508c8092, 0x00000107, 0x20400000, 0x00000002},
    {0x1c401c4, 0x0010100e, 0x508c8092, 0x00000108, 0x20400000, 0x00000002},
    {0x1c401c4, 0x0011110e, 0x508c8092, 0x00000108, 0x20400000, 0x00000002},
    {0x1c401c4, 0x001f1f0e, 0x508c8092, 0x00000108, 0x20400000, 0x00000002}
};

static uint8_t register_data_check(uint8_t reg_idx)
{
    int32_t ret = 0;
    uint32_t reg_check[REG_NUM] = {0};
    
    reg_check[0] = zn_read_32bit_reg(UWB_BASE_ADDR + 0x1810);
    reg_check[1] = zn_read_32bit_reg(UWB_BASE_ADDR + 0x1828);
    reg_check[2] = zn_read_32bit_reg(UWB_BASE_ADDR + 0x0810);
    reg_check[3] = zn_read_32bit_reg(UWB_BASE_ADDR + 0x181c);
    reg_check[4] = zn_read_32bit_reg(UWB_BASE_ADDR + 0x1700);
    reg_check[5] = zn_read_32bit_reg(UWB_BASE_ADDR + 0x1878);
    
    ret = memcmp(reg_check, &s_register_data[reg_idx][0], sizeof(uint32_t) * REG_NUM);
    
    return ret;
}
int32_t config_set_scan_test(void)
{
    int32_t ret = 0;
    uint8_t cfg_idx = 0;
    for(cfg_idx = 0; cfg_idx < CFG_NUM; cfg_idx++)
    {
        zn_config((void*)&s_config_set[cfg_idx]);
        
        ret |= register_data_check(cfg_idx);
    }
    
    return ret;
}

    