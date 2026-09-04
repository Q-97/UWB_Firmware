#include "tuwb.h"

#include <stdlib.h>
#include <string.h>

#include "zn_interface.h"
#include "phy_cmd.h"

#include "mem.h"
#include "test_mode.h"
#include "hal_radar.h"


device_inst_t g_dev_inst  = {0};

uint8_t uwbs_current_ctl_msg;//当前控制消息
uint8_t uwbs_test_current_cmd = OID_TEST_NULL;//当前测试指令

hal_uwb_instance_t  test_mode_uwb_inst = 
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
        .tia_level = TIA_LEVEL_5, //no fem :5  fem :0
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
        .aoa_en = 0,

        .aoa_mode = TYPE_AOA,
        .aoa_dimension_mode = TYPE_3D,
        .aoa_3d_ant_type = AOA_3D_ANTENNA_TYPE_CEILING_TYPE3,
        .ant_sel = RX2_INPUT,
        .phase_compen_rx0_rx1 = 0.0,
        .phase_compen_rx0_rx2 = 0.0,
        .ant_distance_rx0_rx1 = 1.8,
        .ant_distance_rx0_rx2 = 1.8,
        .ant_distance_rx1_rx2 = 1.8,
        .delay_rx0_rx1 = 0,
    },

};

device_inst_t *uci_get_dev_inst(void)
{
    return &g_dev_inst;
}

void uwbs_init(void)
{
    device_inst_t *dev_inst   = uci_get_dev_inst();
    uint8_t       session_idx = 0;

    for(session_idx = 0; session_idx < MAX_SESSION_NUM; session_idx++)
    {
        dev_inst->session_inst[session_idx].session_cfg.device_type = 0x01;
        dev_inst->session_inst[session_idx].session_cfg.ranging_round_usage = 0x02;
        dev_inst->session_inst[session_idx].session_cfg.channel_no = test_mode_uwb_inst.phy_config.channel_num;
        dev_inst->session_inst[session_idx].session_cfg.controlee_num = 1;
        dev_inst->session_inst[session_idx].session_cfg.mac_fcs_type = 0x00;
        dev_inst->session_inst[session_idx].session_cfg.range_role = 0x01;
        dev_inst->session_inst[session_idx].session_cfg.rframe_cfg = test_mode_uwb_inst.phy_config.frame_type;
        dev_inst->session_inst[session_idx].session_cfg.sfd_id = test_mode_uwb_inst.phy_config.sfd_id;
        dev_inst->session_inst[session_idx].session_cfg.preamble_code_idx = test_mode_uwb_inst.phy_config.preamble_code_idx;
        dev_inst->session_inst[session_idx].session_cfg.psdu_data_rate = test_mode_uwb_inst.phy_config.psdu_data_rate;
        dev_inst->session_inst[session_idx].session_cfg.key_rotation = 0x00;
        dev_inst->session_inst[session_idx].session_cfg.preamble_duration = test_mode_uwb_inst.phy_config.preamble_duration;
        dev_inst->session_inst[session_idx].session_cfg.prf_mode = test_mode_uwb_inst.phy_config.prf_mode;
        dev_inst->session_inst[session_idx].session_cfg.slots_per_ranging_round = 25;
        dev_inst->session_inst[session_idx].session_cfg.result_report_cfg = 0x00;
        dev_inst->session_inst[session_idx].session_cfg.bprf_phr_data_rate = test_mode_uwb_inst.phy_config.bprf_phr_data_rate;
        dev_inst->session_inst[session_idx].session_cfg.sts_cfg = 0x00;
        dev_inst->session_inst[session_idx].session_cfg.sts_len = test_mode_uwb_inst.phy_config.sts_seg_len;
        dev_inst->session_inst[session_idx].session_cfg.number_of_sts_segments = test_mode_uwb_inst.phy_config.sts_seg_num;
        dev_inst->session_inst[session_idx].session_cfg.vendor_id = 0x00;
        dev_inst->session_inst[session_idx].session_cfg.max_ranging_round_retry = 0x30;
        dev_inst->session_inst[session_idx].session_cfg.slot_duration = 2400;
        dev_inst->session_inst[session_idx].session_cfg.max_num_of_measurements = 0x00;
        dev_inst->session_inst[session_idx].session_cfg.ranging_interval = 200;
        dev_inst->session_inst[session_idx].session_cfg.key_rotation_rate = 0;
        dev_inst->session_inst[session_idx].session_cfg.uwb_init_time = 0;
        dev_inst->session_inst[session_idx].session_cfg.aoa_req = 0;
        dev_inst->session_inst[session_idx].session_cfg.range_data_ntf_cfg = 0x01;
        dev_inst->session_inst[session_idx].session_cfg.tx_adaptive_payload_power = 0x00;
        dev_inst->session_inst[session_idx].session_cfg.schedule_mode = 0x01;
        dev_inst->session_inst[session_idx].session_cfg.hopping_mode = 0x00;
        dev_inst->session_inst[session_idx].session_cfg.ranging_time_struct = 0x01;
        dev_inst->session_inst[session_idx].session_cfg.responder_slot_index = 0;
        dev_inst->session_inst[session_idx].session_cfg.ranging_round_ctrl = 0x03;
        dev_inst->session_inst[session_idx].session_cfg.priority = 50;
        dev_inst->session_inst[session_idx].session_cfg.sts_index0 = 0x00000000;
        dev_inst->session_inst[session_idx].session_cfg.sub_session_id = 0;
        dev_inst->session_inst[session_idx].session_cfg.uwb_init_time = 0;
        dev_inst->session_inst[session_idx].session_cfg.rcm_margin_time = 0;
        dev_inst->session_inst[session_idx].session_cfg.rcm_timeout = 0;
        dev_inst->session_inst[session_idx].session_state.cur_state = SESSION_STATE_DEINIT;
    }
    dev_inst->session_num = 0;
    dev_inst->device_state.cur_state = DEVICE_STATE_READY;
    dev_inst->core_capality.channel_mask = 0x11;
    dev_inst->core_capality.slot_bit_mask = 0x01 | 0x02 | 0x04 | 0x08 | 0x10 | 0x20 | 0x40 | 0x80;
    dev_inst->core_capality.hopping_config_mask = 0xf0;
    dev_inst->core_capality.support_protocol_verion = 0x0100;
    dev_inst->core_capality.support_uwb_config_id[0] = 0x0000;
    dev_inst->core_capality.support_uwb_config_id[1] = 0x0001;
    dev_inst->core_capality.sync_code_mask = 0x01E1FE00;
    dev_inst->core_capality.uwb_cambo_shape = 0x00;
    dev_inst->device_cfg.low_power_mode = 0;
    dev_inst->device_cfg.power_diff[0].ch = 0x05;
    dev_inst->device_cfg.power_diff[0].sign = 0x00;
    dev_inst->device_cfg.power_diff[0].offset = 0x00;
    dev_inst->device_cfg.power_diff[1].ch = 0x06;
    dev_inst->device_cfg.power_diff[1].sign = 0x00;
    dev_inst->device_cfg.power_diff[1].offset = 0x00;
    dev_inst->device_cfg.power_diff[2].ch = 0x08;
    dev_inst->device_cfg.power_diff[2].sign = 0x00;
    dev_inst->device_cfg.power_diff[2].offset = 0x00;
    dev_inst->device_cfg.power_diff[3].ch = 0x09;
    dev_inst->device_cfg.power_diff[3].sign = 0x00;
    dev_inst->device_cfg.power_diff[3].offset = 0x00;
    dev_inst->device_cfg.freq_diff[0].ch = 0x05;
    dev_inst->device_cfg.freq_diff[0].sign = 0x00;
    dev_inst->device_cfg.freq_diff[0].offset = 0x0000;
    dev_inst->device_cfg.freq_diff[1].ch = 0x06;
    dev_inst->device_cfg.freq_diff[1].sign = 0x00;
    dev_inst->device_cfg.freq_diff[1].offset = 0x0000;
    dev_inst->device_cfg.freq_diff[2].ch = 0x08;
    dev_inst->device_cfg.freq_diff[2].sign = 0x00;
    dev_inst->device_cfg.freq_diff[2].offset = 0x0000;
    dev_inst->device_cfg.freq_diff[3].ch = 0x09;
    dev_inst->device_cfg.freq_diff[3].sign = 0x00;
    dev_inst->device_cfg.freq_diff[3].offset = 0x0000;
    dev_inst->device_cfg.ant_diff[0].ch = 0x05;
    dev_inst->device_cfg.ant_diff[0].offset = 0x0000;
    dev_inst->device_cfg.ant_diff[1].ch = 0x06;
    dev_inst->device_cfg.ant_diff[1].offset = 0x0000;
    dev_inst->device_cfg.ant_diff[2].ch = 0x08;
    dev_inst->device_cfg.ant_diff[2].offset = 0x0000;
    dev_inst->device_cfg.ant_diff[3].ch = 0x09;
    dev_inst->device_cfg.ant_diff[3].offset = 0x0000;
    dev_inst->device_cfg.group_delay[0].index = 0x00;
    dev_inst->device_cfg.group_delay[0].NBIC_type = 0x00;
    dev_inst->device_cfg.group_delay[0].delay = 0x00;
    dev_inst->test_cfg.test_mode = RECEIVE_MODE;
    dev_inst->test_cfg.test_delay = 0x00;
    dev_inst->test_cfg.frame_type = test_mode_uwb_inst.phy_config.frame_type;
    dev_inst->test_cfg.time_out = 100;
    dev_inst->test_cfg.event_cout_max = 0x00;
    dev_inst->test_cfg.tx_cycle_time = 1000;
}



// =================================== 指令解析 =========================================

// gid = 0x00 , GID_UCI_CORE
uint8_t gid_uci_core_process(uint8_t oid)
{
    uint8_t status = STATUS_OK;

    switch(oid)
    {
        case OID_CORE_DEVICE_RESET:
        {
            uwbs_current_ctl_msg = CORE_DEVICE_RESET_CMD;
            break;
        }
        case OID_CORE_GET_DEVICE_INF:
        {
            uwbs_current_ctl_msg = CORE_GET_DEVICE_INFO_CMD;
            break;
        }
        case OID_CORE_GET_CAPS_INF:
        {
            uwbs_current_ctl_msg = CORE_GET_CAPS_INFO_CMD;
            break;
        }
        case OID_CORE_SET_CONFIG:
        {
            uwbs_current_ctl_msg = CORE_SET_CONFIG_CMD;
            break;
        }
        case OID_CORE_GET_CONFIG:
        {
            uwbs_current_ctl_msg = CORE_GET_CONFIG_CMD;
            break;
        }
        case OID_QUERY_DEVICE_CLOCK_TIMSTAMP:
        {
            uwbs_current_ctl_msg = QUERY_UWB_TIMESTAMP;
            break;
        }
        default:
        {
            status = STATUS_UNKNOWN_OID;
            break;
        }
    }
    return status;
}

// gid = 0x01 , GID_UWB_SESSION_CFG
uint8_t gid_uwb_session_cfg_process(uint8_t oid)
{
    uint8_t status = STATUS_OK;

    switch(oid)
    {
        case OID_SESSION_INIT:
        {
            uwbs_current_ctl_msg = SESSION_INIT_CMD;
            break;
        }
        case OID_SESSION_DEINIT:
        {
            uwbs_current_ctl_msg = SESSION_DEINIT_CMD;
            break;
        }
        case OID_SESSION_SET_APP_CONFIG:
        {
            uwbs_current_ctl_msg = SESSION_SET_APP_CONFIG_CMD;
            break;
        }
        case OID_SESSION_GET_APP_CONFIG:
        {
            uwbs_current_ctl_msg = SESSION_GET_APP_CONFIG_CMD;
            break;
        }
        case OID_SESSION_GET_COUNT:
        {
            uwbs_current_ctl_msg = SESSION_GET_COUNT_CMD;
            break;
        }
        case OID_SESSION_GET_STATE:
        {
            uwbs_current_ctl_msg = SESSION_GET_STATE_CMD;
            break;
        }
        case OID_SESSION_UPDATE_CONROLLER_MULTICAST_LIST:
        {
            uwbs_current_ctl_msg = SESSION_UPDATE_CONTROLLER_MULTICAST_LIST_CMD;
            break;
        }
        default:
        {
            status = STATUS_UNKNOWN_OID;
            break;
        }
    }
    return status;
}

// gid = 0x02 , GID_UWB_SESSION_CTRL
uint8_t gid_uwb_session_ctrl_process(uint8_t oid)
{
    uint8_t status = STATUS_OK;

    switch(oid)
    {
        case OID_RANGE_START:
        {
            uwbs_current_ctl_msg = RANGE_START_CMD;
            break;
        }
        case OID_RANGE_STOP:
        {
            uwbs_current_ctl_msg = RANGE_STOP_CMD;
            break;
        }
        case OID_RANGE_GET_RANGING_COUNT:
        {
            uwbs_current_ctl_msg = RANGE_GET_RANGING_COUNT_CMD;
            break;
        }
        default:
        {
            status = STATUS_UNKNOWN_OID;
            break;
        }
    }
    return status;
}

// gid = 0x0D , GID_FIRA_TEST
uint8_t GidTestProcess(uint8_t oid)
{
    uint8_t status = STATUS_OK;
    uwbs_current_ctl_msg = NULL_MSG;
    switch(oid)
    {
        case OID_TEST_CONFIG_SET:
        {
            uwbs_current_ctl_msg = TEST_CONFIG_SET_CMD;
            break;
        }
        case OID_TEST_CONFIG_GET:
        {
            uwbs_current_ctl_msg = TEST_CONFIG_GET_CMD;
            break;
        }
        case OID_TEST_PERIODIC_TX:
        {
            uwbs_current_ctl_msg = TEST_PERIODIC_TX_CMD;
            uwbs_test_current_cmd = oid;
            break;
        }
        case OID_TEST_PER_RX:
        {
            uwbs_current_ctl_msg = TEST_PER_RX_CMD;
            uwbs_test_current_cmd = oid;
            break;
        }
        case OID_TEST_RX:
        {
            uwbs_current_ctl_msg = TEST_RX_CMD;
            uwbs_test_current_cmd = oid;
            break;
        }
        case OID_TEST_LOOPBACK:
        {
            uwbs_current_ctl_msg = TEST_LOOPBACK_CMD;
            uwbs_test_current_cmd = oid;
            break;
        }
        case OID_TEST_SS_TWR:
        {
            uwbs_current_ctl_msg = TEST_SS_TWR_CMD;
            uwbs_test_current_cmd = oid;
            break;
        }
        case OID_TEST_STOP_SESSION:
        {
            uwbs_current_ctl_msg = TEST_STOP_SESSION_CMD;
            break;
        }
        case OID_TEST_DS_TWR:
        {
            uwbs_current_ctl_msg = TEST_DS_TWR_CMD;
            uwbs_test_current_cmd = oid;
            break;
        }
        case OID_TEST_CW:
        {
            uwbs_current_ctl_msg = TEST_CW_CMD;
            uwbs_test_current_cmd = oid;
            break;
        }
        case OID_TEST_CALIBRATION:
        {
            uwbs_current_ctl_msg = TEST_CALIBRATION_CMD;
            break;
        }
        default:
        {
            status = STATUS_UNKNOWN_OID;
            break;
        }
    }
    return status;
}

// gid = 0x0E , GID_PROPRIETARY_GROUP
uint8_t gid_uwb_proprietary_group_process(uint8_t oid)
{
    uint8_t status = STATUS_OK;

    switch(oid)
    {
        case OID_SET_APP_CFG_PAGE_VALUES_CMD:
        {
            uwbs_current_ctl_msg = SET_APP_CFG_PAGE_VALUES_CMD;
            break;
        }
        case OID_GET_APP_CFG_PAGE_VALUES_CMD:
        {
            uwbs_current_ctl_msg = GET_APP_CFG_PAGE_VALUES_CMD;
            break;
        }
        case OID_TEST_START_CMD:
        {
            uwbs_current_ctl_msg = TEST_START_CMD;
            break;
        }
        case OID_TEST_STOP_CMD:
        {
            uwbs_current_ctl_msg = TEST_STOP_CMD;
            break;
        }
        default:
        {
            status = STATUS_UNKNOWN_OID;
            break;
        }
    }
    return status;
}

// gid = 0x0F , GID_PHY_DEBUG
uint8_t gid_phy_debug_process(uint8_t oid)
{
    uint8_t status = STATUS_OK;

    uwbs_current_ctl_msg = NULL_MSG;

    switch(oid)
    {
        case OID_PHY_DEBUG_CAL:
        {
            uwbs_current_ctl_msg = TEST_PHY_DEBUG_CMD;
            break;
        }
        default:
        {
            status = STATUS_UNKNOWN_OID;
            break;
        }
    }
    return status;
}


int32_t invalid_gid_oid_rsp_handler(uci_msg_header_t *uci_msg_header, uint8_t status)
{
    mem_pool_t *mem_pool = NULL;
    uci_msg_t  *uci_msg  = NULL;
    int32_t    ret       = 0;

    mem_pool = mem_alloc();
    if(NULL == mem_pool)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("invalid_gid_oid_rsp_handler mem_alloc fail!");
        #endif
        return -1;
    }

    uci_msg = (uci_msg_t *)(mem_pool->buf);

    memcpy(&uci_msg->msg_header, uci_msg_header, sizeof(uci_msg_header_t));
    uci_msg->msg_header.payload_len = 1;
    uci_msg->msg_data.invalid_gid_oid_rsp.status = status;

    ret = uci_msg_send(uci_msg);

    mem_free(mem_pool);

    return ret;
}



// ======================================= 都会用的基础的 ===========================================

static void uwbs_device_status_ntf(uint8_t dev_state)
{
    mem_pool_t *mem_pool = NULL;
    uci_msg_t  *uci_msg  = NULL;

    mem_pool = mem_alloc();
    if(NULL == mem_pool)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uwbs_device_status_ntf mem_alloc fail!");
        #endif

        return;
    }

    uci_msg = (uci_msg_t *)(mem_pool->buf);
    uci_msg->msg_header.msg_type = CTRL_MSG_NTF;
    uci_msg->msg_header.gid = GID_UCI_CORE;
    uci_msg->msg_header.oid = OID_CORE_DEVICE_STATUS_NTF;
    uci_msg->msg_header.pbf = CTRL_MSG_COMPLETE;
    uci_msg->msg_header.payload_len = 1;
    uci_msg->msg_header.rsv = 0;
    uci_msg->msg_header.rsv1 = 0;

    uci_msg->msg_data.core_dev_status_ntf.dev_state = dev_state;

    if(uci_msg_send(uci_msg) <= 0)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("Uwbs Send OID_CORE_DEVICE_STATUS_NTF Fai led!");
        #endif
    }

    mem_free(mem_pool);

    #ifdef _MAC_DEBUG
    LOG_DEBUG("Uwbs send OID_CORE_DEVICE_STATUS_NTF devState = %d", dev_state);
    #endif

    return;
}
void uwbs_change_device_state(state_device_t new_cur_state)
{
    device_inst_t *dev_inst = uci_get_dev_inst();
 
//    if(dev_inst->device_state.cur_state == new_cur_state)
//    {
//        return;
//    }
    
    dev_inst->device_state.cur_state = new_cur_state;
   
    uwbs_device_status_ntf(dev_inst->device_state.cur_state);//发送当前状态
}
uint8_t uwbs_get_device_state(void)
{
    device_inst_t *dev_inst = uci_get_dev_inst();

    return dev_inst->device_state.cur_state;
}



// ======================================= 外部调用的 ============================================

int32_t uwbs_log_ntf_handler(uint8_t is_rx, uint32_t status)
{
    device_inst_t  *dev_inst  = uci_get_dev_inst();
    mem_pool_t *mem_pool = NULL;
    uci_msg_t  *uci_msg  = NULL;
    int32_t    ret       = 0;
    uint32_t  log_config = dev_inst->device_cfg.log_para_conf;
    uint8_t   para_num  = 0;
    uint8_t   *pbuf      = NULL;
    uint8_t   param_len  = 0;
    
    mem_pool = mem_alloc();
    if(NULL == mem_pool)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uwbs_core_set_config_rsp_handler mem_alloc fail!");
        #endif
        return -1;
    }
    memset(mem_pool->buf, 0, sizeof(MAX_MEM_POOL_SIZE));
    
    uci_msg = (uci_msg_t *)(mem_pool->buf);
    uci_msg->msg_header.msg_type = CTRL_MSG_NTF;
    uci_msg->msg_header.pbf = CTRL_MSG_COMPLETE;
    uci_msg->msg_header.gid = GID_PROPRIETARY_GROUP;
    uci_msg->msg_header.rsv = 0;
    uci_msg->msg_header.oid = OID_LOG_NTF;
    uci_msg->msg_header.rsv1 = 0;
    pbuf = uci_msg->msg_data.log_ntf.param;
    
    if(dev_inst->device_cfg.log_rx_phy_en && is_rx)
    {
        if(log_config & LOG_RX_STATUS_MASK)
        {
            *(pbuf + param_len++) = RX_STATUS;
            *(pbuf + param_len) = 4;
            param_len += 2;
            *((uint32_t *)(pbuf + param_len)) = status;
            param_len += 4;
            para_num++;
        }
        
        if(log_config & LOG_RX_TIMESTAMP_MASK)
        {
            *(pbuf + param_len++) = RX_TIMESTAMP;
            *(pbuf + param_len) = 26;
            param_len += 2;
            if(status == 0x01 || status== 0x02)
            {
                *((uint32_t *)(pbuf + param_len)) = *((uint32_t *)&testProc.rxTimeStampBuf[0]);
                param_len += 4;
                *((uint32_t *)(pbuf + param_len)) = *((uint32_t *)&testProc.rxTimeStampBuf[1]) / 2;
                param_len += 8;
                *(pbuf + param_len++) = RX1_TIMESTAMP;
            }
            else
            {
                memset(pbuf + param_len, 0xFF, 13);
                param_len += 13;
            }
            memset(pbuf + param_len, 0xFF, 13);
            param_len += 13;
            para_num++;
        }
        
        if(log_config & LOG_RX_PSDU_MASK)
        {
            if(status == 0x01 || status== 0x02)
            {
                *(pbuf + param_len++) = RX_PSDU;
                *(pbuf + param_len) = testProc.psduLen;
                param_len += 2;
                memcpy(pbuf + param_len, testProc.psduRxOk, testProc.psduLen);
                param_len += testProc.psduLen;
                para_num++;
            }
        }
        
        uci_msg->msg_header.payload_len = 1 + param_len;
        uci_msg->msg_data.log_ntf.para_num = para_num;
        
        ret = uci_msg_send(uci_msg);
    }
    if(dev_inst->device_cfg.log_tx_phy_en && !is_rx) //uci no this para when tx
    {
        if(log_config & LOG_TX_STATUS_MASK)
        {
            *(pbuf + param_len++) = TX_STATUS;
            *(pbuf + param_len) = 1;
            param_len += 2;
            *(pbuf + param_len++) = status& 0xFF;
 
            para_num++;
        }
        
        if(log_config & LOG_TX_TIMESTAMP_MASK)
        {
            *(pbuf + param_len++) = TX_TIMESTAMP;
            *(pbuf + param_len) = 13;
            param_len += 2;
            if(status == 0x01)
            {
                *((uint32_t *)(pbuf + param_len)) = *((uint32_t *)&testProc.txTimeStampBuf[0]);
                param_len += 4;
                *((uint32_t *)(pbuf + param_len)) = *((uint32_t *)&testProc.txTimeStampBuf[1]) / 2;
                param_len += 8;
                *(pbuf + param_len++) = TX1_TIMESTAMP;
            }
            else
            {
                memset(pbuf + param_len, 0xFF, 13);
                param_len += 13;
            }
            para_num++;
        }
        
        if(log_config & LOG_TX_PSDU_MASK)
        {
        }
        
        uci_msg->msg_header.payload_len = 1 + param_len;
        uci_msg->msg_data.log_ntf.para_num = para_num;
        
        ret = uci_msg_send(uci_msg);
    }
    mem_free(mem_pool);

    return ret;
}


// ===========================================  ===============================================

static bool is_find_session_id(uint32_t session_id, uint8_t *session_index)
{
    device_inst_t  *dev_inst     = uci_get_dev_inst();
    session_inst_t *session_inst = NULL;
    uint8_t        session_idx   = 0;

    for(session_idx = 0; session_idx < MAX_SESSION_NUM; session_idx++)
    {
        session_inst = &dev_inst->session_inst[session_idx];

        if(session_inst->session_is_used && (session_inst->session_id == session_id))
        {
            if(session_index != NULL)
            {
                *session_index = session_idx;
            }

            return TRUE;
        }        
    }
    return FALSE;
}

static bool release_session_by_index(uint8_t session_index)
{
    device_inst_t  *dev_inst     = uci_get_dev_inst();
    session_inst_t *session_inst = NULL;

    session_inst = &dev_inst->session_inst[session_index];
    memset(session_inst, 0, sizeof(session_inst_t));

    return TRUE;
}

static bool uwbs_alloc_idle_session_idx(uint8_t *session_index)
{
    device_inst_t  *dev_inst     = uci_get_dev_inst();
    session_inst_t *session_inst = NULL;
    uint8_t        index         = 0;

    for(index = 0; index < MAX_SESSION_NUM; index++)
    {
        session_inst = &dev_inst->session_inst[index];

        if(session_inst->session_state.cur_state == SESSION_STATE_DEINIT)
        {
            *session_index = index;
            dev_inst->session_num++;

            return TRUE;
        }        
    }
    return FALSE;
}

static int8_t uwbs_session_init_cmd_rsp_send(uint8_t status, session_inst_t *session_inst)
{
    device_inst_t *dev_inst = uci_get_dev_inst();
    mem_pool_t    *mem_pool = NULL;
    uci_msg_t     *uci_msg  = NULL;
    int8_t        ret       = -1;
  
    mem_pool = mem_alloc();
    if(NULL == mem_pool)
    {
        return -1;
    }

    uci_msg = (uci_msg_t *)(mem_pool->buf);

    uci_msg->msg_header.msg_type = CTRL_MSG_RSP;
    uci_msg->msg_header.gid = GID_UWB_SESSION_CFG;
    uci_msg->msg_header.oid = OID_SESSION_INIT;
    uci_msg->msg_header.pbf = CTRL_MSG_COMPLETE;
    uci_msg->msg_header.payload_len = 1+4;
    uci_msg->msg_header.rsv = 0;
    uci_msg->msg_header.rsv1 = 0;
    uci_msg->msg_data.session_init_rsp.status = status;
    uci_msg->msg_data.session_init_rsp.session_handle = session_inst->session_handle;

    ret = uci_msg_send(uci_msg);
    mem_free(mem_pool);

    return ret;
}

static void uwbs_delete_one_session(uint8_t session_index)
{
    device_inst_t *dev_inst = uci_get_dev_inst();


    if(session_index > MAX_SESSION_NUM)
    {
        return;
    }

    dev_inst->session_inst[session_index].session_is_used = 0;
    dev_inst->session_inst[session_index].session_state.cur_state = SESSION_STATE_DEINIT;


    if(dev_inst->session_num > 0)
    {
        dev_inst->session_num--;  
    }
}

static bool is_find_session_handle(uint32_t session_handle, uint8_t *session_index)
{
    device_inst_t  *dev_inst     = uci_get_dev_inst();
    session_inst_t *session_inst = NULL;
    uint8_t        session_idx   = 0;

    for(session_idx = 0; session_idx < MAX_SESSION_NUM; session_idx++)
    {
        session_inst = &dev_inst->session_inst[session_idx];

        if(session_inst->session_is_used && (session_inst->session_handle == session_handle))
        {
            if(session_index != NULL)
            {
                *session_index = session_idx;
            }
            return TRUE;
        }        
    }
    return FALSE;
}
static int8_t uwbs_session_deinit_cmd_rsp_send(uint32_t session_handle, uint8_t *session_idx)
{
    mem_pool_t *mem_pool = NULL;
    uci_msg_t  *uci_msg  = NULL;
    uint8_t    ret       = STATUS_OK;

    mem_pool = mem_alloc();
    if(NULL == mem_pool)
    {
        return -1;
    }

    uci_msg = (uci_msg_t *)(mem_pool->buf);

    uci_msg->msg_header.msg_type = CTRL_MSG_RSP;
    uci_msg->msg_header.gid = GID_UWB_SESSION_CFG;
    uci_msg->msg_header.oid = OID_SESSION_DEINIT;
    uci_msg->msg_header.pbf = CTRL_MSG_COMPLETE;
    uci_msg->msg_header.payload_len = 1;
    uci_msg->msg_header.rsv = 0;
    uci_msg->msg_header.rsv1 = 0;

    if(!is_find_session_handle(session_handle, session_idx))
    {
        ret = STATUS_ERROR_SESSION_NOT_EXIST;
    }
    else
    {
        ret = STATUS_OK;
    }

    uci_msg->msg_data.session_deinit_rsp.status = ret;

    if(uci_msg_send(uci_msg) <= 0)
    {
        mem_free(mem_pool);
        return -1;
    }
    
    mem_free(mem_pool);

    return ret;
}

static void uwbs_session_send_status_ntf(session_inst_t *session_inst)
{
    device_inst_t *dev_inst = uci_get_dev_inst();
    mem_pool_t *mem_pool = NULL;
    uci_msg_t  *uci_msg  = NULL;

    mem_pool = mem_alloc();
    if(NULL == mem_pool)
    {
        return;
    }

    uci_msg = (uci_msg_t *)(mem_pool->buf);

    uci_msg->msg_header.msg_type = CTRL_MSG_NTF;
    uci_msg->msg_header.gid = GID_UWB_SESSION_CFG;
    uci_msg->msg_header.oid = OID_SESSION_STATUS_NTF;
    uci_msg->msg_header.pbf = CTRL_MSG_COMPLETE;
    uci_msg->msg_header.payload_len = 6;
    uci_msg->msg_header.rsv = 0;
    uci_msg->msg_header.rsv1 = 0;
    uci_msg->msg_data.session_status_ntf.session_handle = session_inst->session_handle;
    uci_msg->msg_data.session_status_ntf.session_state = session_inst->session_state.cur_state;
    uci_msg->msg_data.session_status_ntf.reason_code = session_inst->session_reason_code;

    uci_msg_send(uci_msg);
    
    mem_free(mem_pool);

    return;
}
void uwbs_change_session_state(uint8_t session_index, state_session_t  new_cur_state)
{
    device_inst_t  *dev_inst     = uci_get_dev_inst();
    session_inst_t *session_inst = NULL;

    session_inst = &dev_inst->session_inst[session_index];    
    session_inst->session_state.cur_state = new_cur_state;
    uwbs_session_send_status_ntf(session_inst);
}

uint8_t uwbs_session_active_state_num(void)
{
    device_inst_t  *dev_inst     = uci_get_dev_inst();
    session_inst_t *session_inst = NULL;
    uint8_t        session_num   = 0;

    for(uint8_t index = 0; index < MAX_SESSION_NUM; index++)
    {
        if(SESSION_STATE_ACTIVE == dev_inst->session_inst[index].session_state.cur_state)
        {
            session_num++;
        }
    }
    return session_num;
}

void uwb_session_app_cfg_save(uint8_t session_idx, uint8_t tag, uint8_t len, uint8_t *value, uint8_t *fail_param, uint8_t *fail_param_len)
{
    device_inst_t *dev_inst    = uci_get_dev_inst();
    session_cfg_t *session_cfg = NULL;

    session_cfg = &dev_inst->session_inst[session_idx].session_cfg;
    switch((session_cfg_tag_t)tag)
    {
        case DEVICE_TYPE:
        {
            if(*value >= 0x02)
            {
                fail_param[(*fail_param_len)++] = (uint8_t)DEVICE_TYPE;
                fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                session_cfg->device_type = *value;
            }
            break;
        }
        case RANGING_ROUND_USAGE:
        {
            if((*value > 0x04) || (0x00 == *value))
            {
                fail_param[(*fail_param_len)++] = (uint8_t)RANGING_ROUND_USAGE;
                fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                session_cfg->ranging_round_usage = *value;
            }
            break;
        }
        case STS_CONFIG:
        {
            if(*value >= 0x03)
            {
                fail_param[(*fail_param_len)++] = (uint8_t)STS_CONFIG;
                fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                session_cfg->sts_cfg = *value;
            }
            break;
        }

        case CHANNEL_NUMBER:
        {
            if((*value > 15) || (*value < 5) || (7 == *value) ||(11 == *value))
            {
                fail_param[(*fail_param_len)++] = (uint8_t)CHANNEL_NUMBER;
                fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                session_cfg->channel_no = zn_uci_channel_num_to_zn_cfg(*value);
            }
            break;
        }
        case NUMBER_OF_CONTROLEES:
        {
            if((*value > MAX_CONTIOLEES_NUM) || (*value < 1))
            {
               session_cfg->controlee_num = MAX_CONTIOLEES_NUM; 
               fail_param[(*fail_param_len)++] = (uint8_t)NUMBER_OF_CONTROLEES;
               fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
               session_cfg->controlee_num = *value;
            }
            break;
        }
        case DEVICE_MAC_ADDRESS:
        {
            session_cfg->self_mac_addr = ((uint16_t)value[1] << 8) | value[0];
            break;
        }

        case SLOT_DURATION:
        {
            session_cfg->slot_duration = ((uint16_t)value[1] << 8) | value[0];
            break;
        }
        case RANGING_INTERVAL:
        {
            session_cfg->ranging_interval = ((uint32_t)value[3] << 24) | ((uint32_t)value[2] << 16) | ((uint16_t)value[1] << 8) | value[0]; 
            break;
        }
        case STS_INDEX:
        {
            session_cfg->sts_index0 = ((uint32_t)value[3] << 24) | ((uint32_t)value[2] << 16) | ((uint16_t)value[1] << 8) | value[0];                       
            break;
        }
        case MAC_FCS_TYPE:
        {
            if(*value >= 2)
            {
               fail_param[(*fail_param_len)++] = (uint8_t)MAC_FCS_TYPE;
               fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                session_cfg->mac_fcs_type = *value;
            }
            break;
        }
        case RANGING_ROUND_CONTROL:
        {
            session_cfg->ranging_round_ctrl = *value;
            break;
        }
        case AOA_RESULT_REQ:
        {
            if(*value >= 2)
            {
               fail_param[(*fail_param_len)++] = (uint8_t)AOA_RESULT_REQ;
               fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
               session_cfg->aoa_req = *value;
            }
            break;
        }
        case RANGE_DATA_NTF_CONFIG:
        {
            if(*value >= 3)
            {
               fail_param[(*fail_param_len)++] = (uint8_t)RANGE_DATA_NTF_CONFIG;
               fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                session_cfg->range_data_ntf_cfg = *value;
            }
            break;
        }

        case DEVICE_ROLE:
        {
            if(*value >= 2)
            {
               fail_param[(*fail_param_len)++] = (uint8_t)DEVICE_ROLE;
               fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                session_cfg->range_role = *value;
            }
            break;
        }
        case RFRAME_CONFIG:
        {
            if(*value >= 4)
            {
               fail_param[(*fail_param_len)++] = (uint8_t)RFRAME_CONFIG;
               fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                session_cfg->rframe_cfg = *value;
            }
            break;
        }
        case PREAMBLE_CODE_INDEX:
        {
            if(*value < 9)  //support all code (index>=9)
            {
               fail_param[(*fail_param_len)++] = (uint8_t)PREAMBLE_CODE_INDEX;
               fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                session_cfg->preamble_code_idx = zn_preamble_code_idx_to_zn_cfg(*value);
            }
            break;
        }
        case SFD_ID:
        {
            if((*value < 0) || (*value > 3))//support SFDID=0,1,2,3
            { 
               fail_param[(*fail_param_len)++] = (uint8_t)SFD_ID;
               fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                session_cfg->sfd_id = zn_uci_sfd_id_to_zn_cfg(*value);
            }
            break;
        }
        case PSDU_DATA_RATE:
        {
            if(*value >= 5)
            {
               fail_param[(*fail_param_len)++] = (uint8_t)PSDU_DATA_RATE;
               fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                session_cfg->psdu_data_rate = zn_psdu_data_rate_to_zn_cfg(*value);
            }
            break;
        }
        case PREAMBLE_DURATION:
        {
            if(*value >= 12)
            {
               fail_param[(*fail_param_len)++] = (uint8_t)PREAMBLE_DURATION;
               fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                session_cfg->preamble_duration = zn_preamble_duration_to_zn_cfg(*value);
            }
            break;
        }
        case RANGING_TIME_STRUCT:
        {
            break;
        }
        case SLOTS_PER_RR:
        {
            session_cfg->slots_per_ranging_round = *value;
            break;
        }
        case TX_ADAPTIVE_PAYLOAD_POWER:
        {
            if(*value >= 2)
            {
               fail_param[(*fail_param_len)++] = (uint8_t)TX_ADAPTIVE_PAYLOAD_POWER;
               fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                session_cfg->tx_adaptive_payload_power = *value;
            }
            break;
        }
        case RESPONDER_SLOT_INDEX:
        {
            session_cfg->responder_slot_index = *value;
            break;
        }
        case PRF_MODE:
        {
            if(*value >= 3)
            { 
               fail_param[(*fail_param_len)++] = (uint8_t)PRF_MODE;
               fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                session_cfg->prf_mode = *value;
            }
            break;
        }
        case SCHEDULED_MODE:
        {
            if(*value >= 2)
            {
               fail_param[(*fail_param_len)++] = (uint8_t)SCHEDULED_MODE;
               fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                session_cfg->schedule_mode = *value;
            }
            break;
        }
        case KEY_ROTATION:
        {
            if(*value >= 2)
            {
               fail_param[(*fail_param_len)++] = (uint8_t)KEY_ROTATION;
               fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                session_cfg->key_rotation = *value;
            }
            break;
        }
        case KEY_ROTATION_RATE:
        {
            if(*value >= 16)
            {
               fail_param[(*fail_param_len)++] = (uint8_t)KEY_ROTATION_RATE;
               fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                session_cfg->key_rotation_rate = *value;
            }
            break;
        }
        case SESSION_PRIORITY:
        {
            if((*value > 100) || (0 == *value))
            {
               fail_param[(*fail_param_len)++] = (uint8_t)SESSION_PRIORITY;
               fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                session_cfg->priority = *value;
            }
            break;
        }
        case MAC_ADDRESS_MODE:
        {
            break;
        }
        case VENDOR_ID:
        {
            session_cfg->vendor_id = ((uint16_t)value[1] << 8) | value[0];
            break;
        }

        case NUMBER_OF_STS_SEGMENTS:
        {
            if(*value > 4)
            {
               fail_param[(*fail_param_len)++] = (uint8_t)NUMBER_OF_STS_SEGMENTS;
               fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                session_cfg->number_of_sts_segments = zn_sts_seg_num_to_zn_cfg(*value);
            }
            break;
        }
        case MAX_RR_RETRY:
        {
            session_cfg->max_ranging_round_retry = ((uint16_t)value[1] << 8) | value[0];
            break;
        }
        case UWB_INITIATION_TIME:
        {
            uint32_t init_time = ((uint32_t)value[3] << 24) | ((uint32_t)value[2] << 16) | ((uint16_t)value[1] << 8) | value[0];
            if(init_time > 10000)
            {
                fail_param[(*fail_param_len)++] = (uint8_t)UWB_INITIATION_TIME;
                fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                session_cfg->uwb_init_time = init_time;
            } 
            break;
        }
        case HOPPING_MODE:
        {
            if(*value > 2)
            {
                fail_param[(*fail_param_len)++] = (uint8_t)HOPPING_MODE;
                fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                session_cfg->hopping_mode = *value;
            }
            break;
        }
        case RESULT_REPORT_CONFIG:
        {
            session_cfg->result_report_cfg = *value;
            break;
        }
        case RR_RETRY_THR:
        {
            session_cfg->rr_retry_thr = ((uint16_t)value[1] << 8) | value[0];
            break;
        }
        case TX_POWER_ID:
        {
            session_cfg->tx_power_id = *value;
            break;
        }

        case SUB_SESSION_ID:
        {
            session_cfg->sub_session_id = ((uint32_t)value[3] << 24) | ((uint32_t)value[2] << 16) | ((uint16_t)value[1] << 8) | value[0];
            break;
        }
        case BPRF_PHR_DATA_RATE:
        {
            if(*value >= 2)
            {
                fail_param[(*fail_param_len)++] = (uint8_t)BPRF_PHR_DATA_RATE;
                fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                session_cfg->bprf_phr_data_rate = zn_phr_data_rate_to_zn_cfg(*value);
            }
            break;
        }
        case MAX_NUMBER_OF_MEASURE:
        {
            session_cfg->max_num_of_measurements = ((uint16_t)value[1] << 8) | value[0];
            break;
        }
        case STS_LENGTH:
        {
            if(*value >= 3)
            {
                fail_param[(*fail_param_len)++] = (uint8_t)STS_LENGTH;
                fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                session_cfg->sts_len = zn_sts_segments_len_to_zn_cfg(*value);
            }
            break;
        }
        case HOP_MODE_KEY:
        {
            #if(CCC_MODE_EN)
            g_hopping_key = ((uint32_t)value[3] << 24) | ((uint32_t)value[2] << 16) | ((uint16_t)value[1] << 8) | value[0];
            #endif
            break;
        }
        case PROTOCOL_VER:
        {
            session_cfg->protocol_ver = ((uint16_t)value[1] << 8) | value[0];
            break;
        }
        case UWB_CONFIG_ID:
        {
            session_cfg->uwb_config_id = ((uint16_t)value[1] << 8) | value[0];
            break;
        }
        case PULSE_SHAPE_CAMBO:
        {
            session_cfg->pulse_cambo = value[0];
            break;
        }
        case STATIC_KEYS:
        {
            if(value[0] > 5)
            {
                fail_param[(*fail_param_len)++] = (uint8_t)STATIC_KEYS;
                fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                session_cfg->static_key[value[0]].key_type = value[0];
                session_cfg->static_key[value[0]].key_encry_info = value[1];
                memcpy(session_cfg->static_key[value[0]].key_value, &value[2], (value[0] == M_URSK)?32:16);
            }
            break;
        }
        case RXTX_ENABLE:
        {
            dev_inst->device_cfg.rx_en = *value;
            dev_inst->device_cfg.tx_en = *(value + 1);
            break;
        }
        case LOGGING_ENABLE:
        {
            dev_inst->device_cfg.log_radar_en = *value;
            dev_inst->device_cfg.log_rx_phy_en = *(value + 1);
            dev_inst->device_cfg.log_tx_phy_en = *(value + 2);
            break;
        }
        case LOG_PARAMS_CONF:
        {
            dev_inst->device_cfg.log_para_conf = *(uint32_t *)value;
            break;
        }
        default:
        {
            break;
        }
    }
}

static int8_t uwbs_session_set_app_config_cmd_rsp_send(uint8_t status, uint32_t session_handle, uint8_t *fail_cfg_param, uint8_t fail_cfg_param_len)
{
    mem_pool_t *mem_pool = NULL;
    uci_msg_t  *uci_msg  = NULL;
    int8_t     ret       = -1;

    mem_pool = mem_alloc();
    if(NULL == mem_pool)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uwbs_session_set_app_config_cmd_rsp_send mem_alloc fail!");
        #endif
        return -1;
    }

    uci_msg = (uci_msg_t *)(mem_pool->buf);

    uci_msg->msg_header.msg_type = CTRL_MSG_RSP;
    uci_msg->msg_header.gid = GID_UWB_SESSION_CFG;
    uci_msg->msg_header.oid = OID_SESSION_SET_APP_CONFIG;
    uci_msg->msg_header.pbf = CTRL_MSG_COMPLETE;
    uci_msg->msg_header.rsv = 0;
    uci_msg->msg_header.rsv1 = 0;
    uci_msg->msg_header.payload_len = fail_cfg_param_len + 2;

    uci_msg->msg_data.session_set_cfg_rsp.status = status;
    uci_msg->msg_data.session_set_cfg_rsp.app_cfg_num = fail_cfg_param_len / 2;
    memcpy(uci_msg->msg_data.session_set_cfg_rsp.app_cfg_param, fail_cfg_param, fail_cfg_param_len);

    if(uci_msg_send(uci_msg) <= 0)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("Uwbs Send SESSION_SET_APP_CONFIG_RSP Failed!");
        #endif
        mem_free(mem_pool);
        return -1;
    }
    
    mem_free(mem_pool);

    return ret;
}

static void uwb_session_app_cfg_get(uint8_t session_index, uint8_t tag, uint8_t *len, uint8_t *value)
{
    device_inst_t *dev_inst    = uci_get_dev_inst();
    session_cfg_t *session_cfg = NULL;

    session_cfg = &dev_inst->session_inst[session_index].session_cfg;

    switch((session_cfg_tag_t)tag)
    {
        case DEVICE_TYPE :
        {
            *len = sizeof(session_cfg->device_type);
            memcpy(value, &session_cfg->device_type, *len);
            break;
        }
        case RANGING_ROUND_USAGE:
        {
            *len = sizeof(session_cfg->ranging_round_usage);
            memcpy(value, &session_cfg->ranging_round_usage, *len);
            break;
        }
        case STS_CONFIG:
        {
            *len = sizeof(session_cfg->sts_cfg);
            memcpy(value, &session_cfg->sts_cfg, *len);
            break;
        }

        case CHANNEL_NUMBER:
        {
            *len = sizeof(session_cfg->channel_no);
            memcpy(value, &session_cfg->channel_no, *len);
            break;
        }
        case NUMBER_OF_CONTROLEES:
        {
            *len = sizeof(session_cfg->controlee_num);
            memcpy(value, &session_cfg->controlee_num, *len);
            break;
        }
        case DEVICE_MAC_ADDRESS:
        {
            *len = sizeof(session_cfg->self_mac_addr);
            memcpy(value, &session_cfg->self_mac_addr, *len);
            break;
        }

        case SLOT_DURATION:
        {
            *len = sizeof(session_cfg->slot_duration);
            memcpy(value, &session_cfg->slot_duration, *len);
            break;
        }
        case RANGING_INTERVAL:
        {
            *len = sizeof(session_cfg->ranging_interval);
            memcpy(value, &session_cfg->ranging_interval, *len);
            break;
        }
        case STS_INDEX:
        {
            *len = 4;
            memset(value, 0, 4);
            #ifdef CCC_MODE_EN
            memcpy(value, &g_sts_index0, *len);
            #endif
            break;
        }
        case MAC_FCS_TYPE:
        {
            *len = sizeof(session_cfg->mac_fcs_type);
            memcpy(value, &session_cfg->mac_fcs_type, *len);
            break;
        }
        case RANGING_ROUND_CONTROL:
        {
            *len = sizeof(session_cfg->ranging_round_ctrl);
            memcpy(value, &session_cfg->ranging_round_ctrl, *len);
            break;
        }
        case AOA_RESULT_REQ:
        {
            *len = sizeof(session_cfg->aoa_req);
            memcpy(value, &session_cfg->aoa_req, *len);
            break;
        }
        case RANGE_DATA_NTF_CONFIG:
        {
            *len = sizeof(session_cfg->range_data_ntf_cfg);
            memcpy(value, &session_cfg->range_data_ntf_cfg, *len);
            break;
        }

        case DEVICE_ROLE:
        {
            *len = sizeof(session_cfg->range_role);
            memcpy(value, &session_cfg->range_role, *len);
            break;
        }
        case RFRAME_CONFIG:
        {
            *len = sizeof(session_cfg->rframe_cfg);
            memcpy(value, &session_cfg->rframe_cfg, *len);
            break;
        }
        case PREAMBLE_CODE_INDEX:
        {
            *len = sizeof(session_cfg->preamble_code_idx);
            memcpy(value, &session_cfg->preamble_code_idx, *len);
            break;
        }
        case SFD_ID:
        {
            *len = sizeof(session_cfg->sfd_id);
            memcpy(value, &session_cfg->sfd_id, *len);
            break;
        }
        case PSDU_DATA_RATE:
        {
            *len = sizeof(session_cfg->psdu_data_rate);
            memcpy(value, &session_cfg->psdu_data_rate, *len);
            break;
        }
        case PREAMBLE_DURATION:
        {
            *len = sizeof(session_cfg->preamble_duration);
            memcpy(value, &session_cfg->preamble_duration, *len);
            break;
        }
        case RANGING_TIME_STRUCT:
        {
            *len = 1;
            memset(value, 1, *len);
            break;
        }
        case SLOTS_PER_RR:
        {
            *len = sizeof(session_cfg->slots_per_ranging_round);
            memcpy(value, &session_cfg->slots_per_ranging_round, *len);
            break;
        }
        case TX_ADAPTIVE_PAYLOAD_POWER:
        {
            *len = sizeof(session_cfg->tx_adaptive_payload_power);
            memcpy(value, &session_cfg->tx_adaptive_payload_power, *len);
            break;
        }
        case RESPONDER_SLOT_INDEX:
        {
            *len = 1;
            memset(value, 0, *len);
            break;
        }
        case PRF_MODE:
        {
            *len = sizeof(session_cfg->prf_mode);
            memcpy(value, &session_cfg->prf_mode, *len);
            break;
        }
        case SCHEDULED_MODE:
        {
            *len = sizeof(session_cfg->schedule_mode);
            memcpy(value, &session_cfg->schedule_mode, *len);
            break;
        }
        case KEY_ROTATION:
        {
            *len = sizeof(session_cfg->key_rotation);
            memcpy(value, &session_cfg->key_rotation, *len);
            break;
        }
        case KEY_ROTATION_RATE:
        {
            *len = sizeof(session_cfg->key_rotation_rate);
            memcpy(value, &session_cfg->key_rotation_rate, *len);
            break;
        }
        case SESSION_PRIORITY:
        {
            *len = sizeof(session_cfg->priority);
            memcpy(value, &session_cfg->priority, *len);
            break;
        }
        case MAC_ADDRESS_MODE:
        {
            *len = 1;
            memset(value, 0, 1);
            break;
        }
        case VENDOR_ID:
        {
            *len = sizeof(session_cfg->vendor_id);
            memcpy(value, &session_cfg->vendor_id, *len);
            break;
        }

        case NUMBER_OF_STS_SEGMENTS:
        {
            *len = 1;
            memset(value, 1, 1);
            break;
        }
        case MAX_RR_RETRY:
        {
            *len = sizeof(session_cfg->max_ranging_round_retry);
            memcpy(value, &session_cfg->max_ranging_round_retry, *len);
            break;
        }
        case UWB_INITIATION_TIME:
        {
            *len = sizeof(session_cfg->uwb_init_time);
            memcpy(value, &session_cfg->uwb_init_time, *len);
            break;
        }
        case HOPPING_MODE:
        {
            *len = sizeof(session_cfg->hopping_mode);
            memcpy(value, &session_cfg->hopping_mode, *len);
            break;
        }

        case RESULT_REPORT_CONFIG:
        {
            *len = sizeof(session_cfg->result_report_cfg);
            memcpy(value, &session_cfg->result_report_cfg, *len);
            break;
        }
        case TX_POWER_ID:
        {
            *len = sizeof(uint8_t);
            *value = session_cfg->tx_power_id;
             break;
        }

        case SUB_SESSION_ID:
        {
            *len = sizeof(session_cfg->sub_session_id);
            memcpy(value, &session_cfg->sub_session_id, *len);
            break;
        }
        case BPRF_PHR_DATA_RATE:
        {
            *len = sizeof(session_cfg->bprf_phr_data_rate);
            memcpy(value, &session_cfg->bprf_phr_data_rate, *len);
            break;
        }
        case MAX_NUMBER_OF_MEASURE:
        {
            *len = sizeof(session_cfg->max_num_of_measurements);
            memcpy(value, &session_cfg->max_num_of_measurements, *len);
            break;
        }
        case STS_LENGTH:
        {
            *len = sizeof(session_cfg->sts_len);
            memcpy(value, &session_cfg->sts_len, *len);
            break;
        }
        case PROTOCOL_VER:
        {
            *len = sizeof(session_cfg->protocol_ver);
            memcpy(value, &session_cfg->protocol_ver, *len);
            break;
        }
        case UWB_CONFIG_ID:
        {
            *len = sizeof(session_cfg->uwb_config_id);
            memcpy(value, &session_cfg->uwb_config_id, *len);
            break;
        }
        case PULSE_SHAPE_CAMBO:
        {
            *len = sizeof(session_cfg->pulse_cambo);
            memcpy(value, &session_cfg->pulse_cambo, *len);
            break;
        }
        default:
        {
            break;
        }
    }
}
static int32_t uwbs_session_get_app_config_rsp_handler(uint32_t session_handle, uint8_t app_cfg_num, uint8_t *cmd_tag)
{
    mem_pool_t *uci_msg_mem_pool   = NULL;
    mem_pool_t *cfg_param_mem_pool = NULL;
    uci_msg_t  *uci_msg            = NULL;
    uint8_t    *cfg_param          = NULL;
    int32_t    ret                 = 0;
    uint8_t    cfg_value[33]       = {0};
    uint8_t    session_index       = 0;
    uint8_t    rsp_status          = 0;
    uint8_t    cfg_len             = 0;
    uint8_t    cmd_app_cfg_num     = 0;
    uint8_t    cfg_idx             = 0;
    uint8_t    mem_idx             = 0;

    uci_msg_mem_pool = mem_alloc();
    if(NULL == uci_msg_mem_pool)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uwbs_session_get_app_config_rsp_handler mem_alloc fail!");
        #endif
        return -1;
    }

    uci_msg = (uci_msg_t *)(uci_msg_mem_pool->buf);

    cfg_param_mem_pool = mem_alloc();
    if(NULL == cfg_param_mem_pool)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("Uwbs SESSION_GET_APP_CONFIG_RSP cfg_param mem_alloc Failed!");
        #endif
        mem_free(uci_msg_mem_pool);
        return -1;
    }

    cfg_param = cfg_param_mem_pool->buf;

    if(!is_find_session_handle(session_handle, &session_index))
    {
        rsp_status = STATUS_ERROR_SESSION_NOT_EXIST;
        cmd_app_cfg_num = STATUS_ERROR_SESSION_NOT_EXIST;
    }
    else
    {
        rsp_status = STATUS_OK;
        cmd_app_cfg_num = (0 == app_cfg_num) ? 53 : app_cfg_num;

        do
        {
            uwb_session_app_cfg_get(session_index, cmd_tag[cfg_idx], &cfg_len, cfg_value);
            cfg_param[mem_idx++] = cmd_tag[cfg_idx];
            cfg_param[mem_idx++] = cfg_len;
            memcpy(&cfg_param[mem_idx], cfg_value, cfg_len);
            mem_idx += cfg_len;
            cfg_idx++;
        }while(cfg_idx < app_cfg_num);
    }

    uci_msg->msg_header.msg_type = CTRL_MSG_RSP;
    uci_msg->msg_header.pbf = CTRL_MSG_COMPLETE;
    uci_msg->msg_header.gid = GID_UCI_CORE;
    uci_msg->msg_header.rsv = 0;
    uci_msg->msg_header.oid = OID_SESSION_GET_APP_CONFIG;
    uci_msg->msg_header.rsv1 = 0;
    uci_msg->msg_header.payload_len = 2 + mem_idx;
    uci_msg->msg_data.session_get_cfg_rsp.status = rsp_status;
    uci_msg->msg_data.session_get_cfg_rsp.app_cfg_num = cmd_app_cfg_num;
    memcpy(uci_msg->msg_data.session_get_cfg_rsp.app_cfg_param, cfg_param, mem_idx);

    ret = uci_msg_send(uci_msg);
    mem_free(uci_msg_mem_pool);
    mem_free(cfg_param_mem_pool);

    return ret;
}

static int32_t uwbs_session_get_state_rsp_handler(uint8_t session_state)
{
    mem_pool_t *mem_pool = NULL;
    uci_msg_t  *uci_msg  = NULL;
    int32_t    ret       = 0;

    mem_pool = mem_alloc();
    if(NULL == mem_pool)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uwbs_session_get_state_rsp_handler mem_alloc fail!");
        #endif
        return -1;
    }

    uci_msg = (uci_msg_t *)(mem_pool->buf);

    uci_msg->msg_header.msg_type = CTRL_MSG_RSP;
    uci_msg->msg_header.pbf = CTRL_MSG_COMPLETE;
    uci_msg->msg_header.gid = GID_UWB_SESSION_CFG;
    uci_msg->msg_header.rsv = 0;
    uci_msg->msg_header.oid = OID_SESSION_GET_STATE;
    uci_msg->msg_header.rsv1 = 0;
    uci_msg->msg_header.payload_len = 2;
    uci_msg->msg_data.session_get_state_rsp.status = STATUS_OK;
    uci_msg->msg_data.session_get_state_rsp.session_state = session_state;

    ret = uci_msg_send(uci_msg);
    mem_free(mem_pool);

    return ret;
}

uint8_t uwbs_check_and_find_session_index(uint32_t session_handle, uint8_t *session_index)
{
    device_inst_t  *dev_inst     = uci_get_dev_inst();
    session_inst_t *session_inst = NULL;
    uint8_t        session_idx   = 0;
    uint8_t        status        = STATUS_OK;

    for(session_idx = 0; session_idx < MAX_SESSION_NUM; session_idx++)
    {
        session_inst = &dev_inst->session_inst[session_idx];

        if(session_inst->session_is_used && (session_inst->session_handle == session_handle))
        {
            if(session_index != NULL)
            {
                *session_index = session_idx;
            }
            break;
        }
    }

    if((session_idx == MAX_SESSION_NUM)
        || ((SESSION_TYPE_RANGE != dev_inst->session_inst[session_idx].session_type) \
        &&(SESSION_TYPE_TEST != dev_inst->session_inst[session_idx].session_type)))

    {
        status = STATUS_ERROR_SESSION_NOT_EXIST;
        return status;
    }

    if(FALSE == dev_inst->session_inst[session_idx].session_is_cfg)
    {
        status = STATUS_ERROR_SESSION_NOT_CONFIGURED;
        return status;
    }

    return status;
}

uint8_t uwbs_get_session_state(uint8_t session_index)
{
    device_inst_t *dev_inst = uci_get_dev_inst();

    for(uint8_t index = 0; index < MAX_SESSION_NUM; index++)
    {
        if(index == session_index)
        {
            return dev_inst->session_inst[session_index].session_state.cur_state;
        }
    }
    return SESSION_STATE_DEINIT;
}

static int8_t uwbs_range_start_cmd_rsp_send(uint8_t status)
{
    mem_pool_t *mem_pool = NULL;
    uci_msg_t  *uci_msg  = NULL;
    int8_t     ret       = -1;

    mem_pool = mem_alloc();
    if(NULL == mem_pool)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uwbs_range_start_cmd_rsp_send mem_alloc fail!");
        #endif
        return -1;
    }

    uci_msg = (uci_msg_t *)(mem_pool->buf);

    uci_msg->msg_header.msg_type = CTRL_MSG_RSP;
    uci_msg->msg_header.gid = GID_UWB_SESSION_CTRL;
    uci_msg->msg_header.oid = OID_RANGE_START;
    uci_msg->msg_header.pbf = CTRL_MSG_COMPLETE;
    uci_msg->msg_header.payload_len = 1;
    uci_msg->msg_header.rsv = 0;
    uci_msg->msg_header.rsv1 = 0;
    uci_msg->msg_data.range_start_rsp.status = status;

    ret = uci_msg_send(uci_msg);

    mem_free(mem_pool);

    return ret;
}

static int8_t uwbs_range_stop_cmd_rsp_send(uint32_t session_handle, uint8_t *session_index)
{
    mem_pool_t *mem_pool = NULL;
    uci_msg_t  *uci_msg  = NULL;
    int8_t     ret       = -1;

    mem_pool = mem_alloc();
    if(NULL == mem_pool)
    {
        return -1;
    }

    uci_msg = (uci_msg_t *)(mem_pool->buf);

    uci_msg->msg_header.msg_type = CTRL_MSG_RSP;
    uci_msg->msg_header.gid = GID_UWB_SESSION_CTRL;
    uci_msg->msg_header.oid = OID_RANGE_STOP;
    uci_msg->msg_header.rsv = 0;
    uci_msg->msg_header.pbf = CTRL_MSG_COMPLETE;
    uci_msg->msg_header.payload_len = 1;
    uci_msg->msg_header.rsv1 = 0;

    if(!is_find_session_handle(session_handle, session_index))
    {
        ret = STATUS_ERROR_SESSION_NOT_EXIST;
    }
    else if(DEVICE_STATE_READY == uwbs_get_session_state(*session_index))
    {
        ret = STATUS_REJECTED;
    }
    else
    {
        ret = STATUS_OK;
    } 

    uci_msg->msg_data.range_stop_rsp.status = ret;

    if(uci_msg_send(uci_msg) <= 0)
    {
        mem_free(mem_pool);
        return -1;
    }
    mem_free(mem_pool);

    return ret;
}

void uwbs_range_stop(uint32_t session_index)
{
    device_inst_t  *dev_inst     = uci_get_dev_inst();
    session_inst_t *session_inst = NULL;

    session_inst = &dev_inst->session_inst[session_index];
 
    uwbs_change_session_state(session_index, SESSION_STATE_IDLE);

    if(0 == uwbs_session_active_state_num())
    {
        uwbs_change_device_state(DEVICE_STATE_READY);
    }
}

static uint8_t uwbs_get_gain_index_by_value(uint8_t gain_value)
{
    uint8_t pa_gain_sel[MAX_PA_SET_NUM]  = {0, 1, 1, 3, 2, 5, 3, 7, 4, 5, 6, 7};
    uint8_t index = MAX_PA_SET_NUM -1;
    
    for(index = MAX_PA_SET_NUM -1; index > 0; index--)
    {
        if(pa_gain_sel[index] == gain_value)
        {
            return index;
        }
    }
    return index;
}
void uwbs_app_cfg_page_values_save(uint8_t tag_id, uint8_t *value, uint8_t tag_len, uint8_t *fail_param, uint8_t *fail_param_len, uint8_t *fail_param_num)
{
    device_inst_t *dev_inst = uci_get_dev_inst();
    uint8_t         count   = 0;
    uint8_t         index   = 0;
    tx_power_diff_t *pd = NULL;
    freq_diff_t     *fd = NULL;
    uint32_t        reg_value = 0;
    uint32_t        cur_value = 0;
    freq_offset_t   freq_value;
    uint8_t         pd_value = 0;
    uint8_t         diff_offset = 0;
    

    switch(tag_id)
    {
        case TX_POWER_DIFF:
        {
            count = tag_len/sizeof(tx_power_diff_t);
            for(index = 0; index < count; index++)
            {
                pd = (tx_power_diff_t *)(value + index*sizeof(tx_power_diff_t));
                if(0x09 == pd->ch)
                {
                    memcpy(&dev_inst->device_cfg.power_diff[3], pd, sizeof(tx_power_diff_t));
                    
                    if(pd->offset)
                    {
                        if(0 == pd->sign)//+
                        {
                            reg_value = zn_read_32bit_reg(TX_CTRL_ID);
                            reg_value &= (TX_CTRL_PA_GAIN_SEL_BIT_MASK);
                            cur_value = reg_value >> TX_CTRL_PA_GAIN_SEL_BIT_OFFSET;
                            cur_value = uwbs_get_gain_index_by_value(cur_value);
                            if(cur_value < (MAX_PA_SET_NUM - 1))
                            {
                                zn_pa_set(cur_value + 1);
                            }
                        }
                        else if(1 == pd->sign)//-
                        {
                            reg_value = zn_read_32bit_reg(TX_CTRL_ID);
                            reg_value &= (TX_CTRL_PA_GAIN_SEL_BIT_MASK);
                            cur_value = reg_value >> TX_CTRL_PA_GAIN_SEL_BIT_OFFSET;
                            cur_value = uwbs_get_gain_index_by_value(cur_value);
                            if(cur_value > 0)
                            {
                                zn_pa_set(cur_value - 1);
                            }
                        }  
                    }              
                }
            }
            break;
        }
        case FREQ_DIFF:
        {
            count = tag_len/sizeof(freq_diff_t);
            for(index = 0; index < count; index++)
            {
                fd = (freq_diff_t *)(value + index*sizeof(freq_diff_t));
                if(0x09 == fd->ch)
                {
                    memcpy(&dev_inst->device_cfg.freq_diff[3], fd, sizeof(freq_diff_t));
                    if(fd->offset)//need mod
                    {
                        if(0 == fd->sign)//+
                        {
                            reg_value = zn_read_32bit_reg(CLK_XO_ID);
                            freq_value.swc_value = (reg_value & D_XO_SWC_I_BIT_MASK)>>D_XO_SWC_I_BIT_OFFSET; 
                            diff_offset = fd->offset/20;
                            if(freq_value.swc_value > diff_offset)
                            {
                                freq_value.swc_value -= diff_offset;
                            }
                            else
                            {
                                freq_value.swc_value = 0;
                            }
                            zn_modify_swc(freq_value.swc_value);

                            freq_value.swf_value = (reg_value & D_XO_SWF_BIT_MASK)>>D_XO_SWF_BIT_OFFSET; 
                            diff_offset = fd->offset%20;
                            if(freq_value.swf_value > diff_offset)
                            {
                                freq_value.swf_value -= diff_offset;
                            }
                            else
                            {
                                freq_value.swf_value = 0;
                            }
                            zn_modify_swf(freq_value.swf_value);
                        }
                        else if(1 == fd->sign)//-
                        {
                            reg_value = zn_read_32bit_reg(CLK_XO_ID);
                            freq_value.swc_value = (reg_value & D_XO_SWC_I_BIT_MASK)>>D_XO_SWC_I_BIT_OFFSET; 
                            diff_offset = fd->offset/20;
                            if((freq_value.swc_value + diff_offset) < 63)
                            {
                                freq_value.swc_value += diff_offset;
                            }
                            else
                            {
                                freq_value.swc_value = 63;
                            }
                            zn_modify_swc(freq_value.swc_value);
                            
                            freq_value.swf_value = (reg_value & D_XO_SWF_BIT_MASK)>>D_XO_SWF_BIT_OFFSET; 
                            diff_offset = fd->offset%20;
                            if((freq_value.swf_value + diff_offset) < 63)
                            {
                                freq_value.swf_value += diff_offset;
                            }
                            else
                            {
                                freq_value.swf_value = 63;
                            }
                            
                            zn_modify_swf(freq_value.swf_value);
                        }
                    }
                }
            }
            break;
        }
        case ANTENNA_DELAY: //还没用到
        {
            count = tag_len/sizeof(antenna_diff_t);
            for(index = 0; index < count; index++)
            {
                dev_inst->device_cfg.ant_diff[3] = *(antenna_diff_t *)(value + index*sizeof(antenna_diff_t));
            }
            break;
        }
        case GROUP_DELAY:   //还没用到
        {
            count = tag_len/sizeof(group_delay_t);
            for(index = 0; index < count; index++)
            {
                dev_inst->device_cfg.group_delay[index] = *(group_delay_t *)(value + index*sizeof(group_delay_t));
            }
            break;
        }
        default:
        {
            #ifdef _MAC_DEBUG
            LOG_ERROR("Uwbs TagID ERROR!");
            #endif
            break;
        }
    }
}

static int32_t uwbs_set_app_cfg_page_values_rsp_handler(uint8_t *fail_cfg_param, uint8_t fail_param_len, uint8_t fail_param_num)
{
    mem_pool_t *mem_pool = NULL;
    uci_msg_t  *uci_msg  = NULL;
    int32_t    ret       = 0;

    mem_pool = mem_alloc();
    if(NULL == mem_pool)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uwbs_set_app_cfg_page_values_rsp_handler mem_alloc fail!");
        #endif
        return -1;
    }

    uci_msg = (uci_msg_t *)(mem_pool->buf);

    uci_msg->msg_header.msg_type = CTRL_MSG_RSP;
    uci_msg->msg_header.pbf = CTRL_MSG_COMPLETE;
    uci_msg->msg_header.gid = GID_PROPRIETARY_GROUP;
    uci_msg->msg_header.rsv = 0;
    uci_msg->msg_header.oid = OID_SET_APP_CFG_PAGE_VALUES_RSP;
    uci_msg->msg_header.rsv1 = 0;
    uci_msg->msg_header.payload_len = 2 + fail_param_len;
    uci_msg->msg_data.core_set_cfg_rsp.param_num = fail_param_num;
    memcpy(uci_msg->msg_data.core_set_cfg_rsp.param, fail_cfg_param, fail_param_len);
    
    if(0 == fail_param_len)
    {
        uci_msg->msg_data.core_set_cfg_rsp.status = STATUS_OK;
    }
    else
    {
        uci_msg->msg_data.core_set_cfg_rsp.status = STATUS_FAILED;
    }
    ret = uci_msg_send(uci_msg);
    mem_free(mem_pool);

    return ret;
}

static int32_t uwbs_set_app_cfg_page_values_ntf_handler(uint8_t status)
{
    mem_pool_t *mem_pool = NULL;
    uci_msg_t  *uci_msg  = NULL;
    int32_t    ret       = 0;

    mem_pool = mem_alloc();
    if(NULL == mem_pool)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uwbs_set_app_cfg_page_values_rsp_handler mem_alloc fail!");
        #endif

        return -1;
    }

    uci_msg = (uci_msg_t *)(mem_pool->buf);

    uci_msg->msg_header.msg_type = CTRL_MSG_NTF;
    uci_msg->msg_header.pbf = CTRL_MSG_COMPLETE;
    uci_msg->msg_header.gid = GID_PROPRIETARY_GROUP;
    uci_msg->msg_header.rsv = 0;
    uci_msg->msg_header.oid = OID_SET_APP_CFG_PAGE_VALUES_NTF;
    uci_msg->msg_header.rsv1 = 0;
    uci_msg->msg_header.payload_len = 2;
    uci_msg->msg_data.core_dev_status_ntf.dev_state = status;

    ret = uci_msg_send(uci_msg);
    mem_free(mem_pool);

    return ret;
}

void uwbs_get_app_cfg_page_values(uint8_t tag_id, uint8_t *param_buf, uint8_t *param_len)
{
    device_inst_t *dev_inst = uci_get_dev_inst();

    switch(tag_id)
    {
        case TX_POWER_DIFF:
        {
            param_buf[(*param_len)++] = TX_POWER_DIFF;
            param_buf[(*param_len)++] = 4*sizeof(tx_power_diff_t);
            memcpy((param_buf + (*param_len)), &dev_inst->device_cfg.power_diff[0],4*sizeof(tx_power_diff_t));
            (*param_len) += 4*sizeof(tx_power_diff_t);
            break;
        }
        case FREQ_DIFF:
        {
            param_buf[(*param_len)++] = FREQ_DIFF;
            param_buf[(*param_len)++] = 4*sizeof(freq_diff_t);
            memcpy((param_buf + (*param_len)), &dev_inst->device_cfg.freq_diff[0],4*sizeof(freq_diff_t));
            (*param_len) += 4*sizeof(freq_diff_t);
            break;
        }
        case ANTENNA_DELAY:
        {
            param_buf[(*param_len)++] = ANTENNA_DELAY;
            param_buf[(*param_len)++] = 4*sizeof(antenna_diff_t);
            memcpy((param_buf + (*param_len)), &dev_inst->device_cfg.ant_diff[0],4*sizeof(antenna_diff_t));
            (*param_len) += 4*sizeof(antenna_diff_t);
            break;
        }
//        case GROUP_DELAY:
//        {
////            param_buf[(*param_len)++] = GROUP_DELAY;
////            param_buf[(*param_len)++] = 1*sizeof(group_delay_t);
////            memcpy((param_buf + (*param_len)), &dev_inst->device_cfg.group_delay[0],sizeof(group_delay_t));
////            (*param_len) += sizeof(group_delay_t);
//            param_buf[(*param_len)++] = GROUP_DELAY;
//            param_buf[(*param_len)++] = 00;
////            memcpy((param_buf + (*param_len)), &dev_inst->device_cfg.group_delay[0],sizeof(group_delay_t));
////            (*param_len) += sizeof(group_delay_t);
//            break;
//        }
        default:
        {
            #ifdef _MAC_DEBUG
            LOG_ERROR("Uwbs tag_id Error!");
            #endif
            break;
        }
    }
}

static int32_t uwbs_get_app_cfg_page_values_rsp_handler(uint8_t *cfg_param, uint8_t cfg_param_len, uint8_t param_num)
{
    mem_pool_t *mem_pool = NULL;
    uci_msg_t  *uci_msg  = NULL;
    int32_t    ret       = 0;

    mem_pool = mem_alloc();
    if(NULL == mem_pool)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uwbs_set_app_cfg_page_values_rsp_handler mem_alloc fail!");
        #endif

        return -1;
    }

    uci_msg = (uci_msg_t *)(mem_pool->buf);

    uci_msg->msg_header.msg_type = CTRL_MSG_RSP;
    uci_msg->msg_header.pbf = CTRL_MSG_COMPLETE;
    uci_msg->msg_header.gid = GID_PROPRIETARY_GROUP;
    uci_msg->msg_header.rsv = 0;
    uci_msg->msg_header.oid = OID_GET_APP_CFG_PAGE_VALUES_RSP;
    uci_msg->msg_header.rsv1 = 0;
    uci_msg->msg_header.payload_len = 2 + cfg_param_len;
    uci_msg->msg_data.core_set_cfg_rsp.status = STATUS_OK;
    uci_msg->msg_data.core_set_cfg_rsp.param_num = param_num;
    memcpy(uci_msg->msg_data.core_set_cfg_rsp.param, cfg_param, cfg_param_len);

    ret = uci_msg_send(uci_msg);
    mem_free(mem_pool);

    return ret;
}


void uwbs_test_start_save(uint8_t tag, uint8_t len, uint8_t *value, uint8_t *fail_param, uint8_t *fail_param_len)
{
    device_inst_t *dev_inst = uci_get_dev_inst();

    switch(tag)
    {
        case MODE:
        {
            if(*value > 0x06)
            {
                fail_param[(*fail_param_len)++] = (uint8_t)MODE;
                fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                dev_inst->test_cfg.test_mode = *value;
            }
            break;
        }
        case DELAY:
        {
            dev_inst->test_cfg.test_delay = *(uint16_t *)value;
            break;
        }
        case FRAME_TYPE:
        {
            if(*value > 0x03)
            {
                fail_param[(*fail_param_len)++] = (uint8_t)FRAME_TYPE;
                fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                dev_inst->test_cfg.frame_type = zn_rframe_cfg_to_zn_cfg(*value);
            }
            break;
        }
        case PSDU:
        {
            memcpy(dev_inst->test_cfg.psdu, value, len);
            dev_inst->test_cfg.psdu_len = len;
            break;
        }
        case TIME_OUT:
        {
            dev_inst->test_cfg.time_out = *(uint16_t *)value;
            break;
        }
        case EVENT_COUNTER_MAX:
        {
            dev_inst->test_cfg.event_cout_max = *(uint32_t *)value;
            break;
        }
        case TX_CYCLE_TIME:
        {     
            if(((*(uint32_t *)value) > 0x989680) || ((*(uint32_t *)value) < 0x3E8))
            {
                fail_param[(*fail_param_len)++] = (uint8_t)TX_CYCLE_TIME;
                fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                dev_inst->test_cfg.tx_cycle_time = *(uint32_t *)value;
            }
            break;
        }
        case CRC_ENABLE:
        {     
            if((*value) > 2)
            {
                fail_param[(*fail_param_len)++] = (uint8_t)CRC_ENABLE;
                fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                dev_inst->test_cfg.crc_en = *value;
            }
            break;
        }
        case PHR_RANGING_BIT:
        {     
            if((*value) > 2)
            {
                fail_param[(*fail_param_len)++] = (uint8_t)PHR_RANGING_BIT;
                fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_PARAM;
            }
            else
            {
                dev_inst->test_cfg.phr_range_bit = *value;
            }
            break;
        }
        default:
        {
            #ifdef _MAC_DEBUG
            LOG_ERROR("Uwbs tag_id Error!");
            #endif
            break;
        }
    }
}
static int32_t uwbs_test_start_rsp_handler(uint8_t *fail_cfg_param, uint8_t fail_cfg_param_len)
{
    mem_pool_t *mem_pool    = NULL;
    uci_msg_t  *uci_msg     = NULL;
    int32_t    ret          = 0;
    uint8_t    cfg_idx      = 0;
    uint8_t    tag_id       = 0;
    uint8_t    cfg_len      = 0;
    uint8_t    cfg_value[20]    = {0};
    uint8_t    mem_idx          = 0;
    mem_pool = mem_alloc();
    if(NULL == mem_pool)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uwbs_core_set_config_rsp_handler mem_alloc fail!");
        #endif
        return -1;
    }

    uci_msg = (uci_msg_t *)(mem_pool->buf);
    uci_msg->msg_header.msg_type = CTRL_MSG_RSP;
    uci_msg->msg_header.pbf = CTRL_MSG_COMPLETE;
    uci_msg->msg_header.gid = GID_PROPRIETARY_GROUP;
    uci_msg->msg_header.rsv = 0;
    uci_msg->msg_header.oid = OID_TEST_START_RSP;
    uci_msg->msg_header.rsv1 = 0;
    uci_msg->msg_header.payload_len = 2 + fail_cfg_param_len;
    uci_msg->msg_data.core_set_cfg_rsp.param_num = fail_cfg_param_len / 2;
    
    memcpy(uci_msg->msg_data.core_set_cfg_rsp.param, fail_cfg_param, fail_cfg_param_len);

    if(0 == fail_cfg_param_len)
    {
        uci_msg->msg_data.core_set_cfg_rsp.status = STATUS_OK;
    }
    else
    {
        uci_msg->msg_data.core_set_cfg_rsp.status = STATUS_INVALID_RANGE;
    }
    
    ret = uci_msg_send(uci_msg);
    
    mem_free(mem_pool);

    return ret;
}


static int32_t uwbs_test_stop_rsp_handler()
{
    mem_pool_t *mem_pool = NULL;
    uci_msg_t  *uci_msg  = NULL;
    int32_t    ret       = 0;
    
    mem_pool = mem_alloc();
    if(NULL == mem_pool)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uwbs_core_set_config_rsp_handler mem_alloc fail!");
        #endif
        return -1;
    }

    uci_msg = (uci_msg_t *)(mem_pool->buf);

    uci_msg->msg_header.msg_type = CTRL_MSG_RSP;
    uci_msg->msg_header.pbf = CTRL_MSG_COMPLETE;
    uci_msg->msg_header.gid = GID_FIRA_TEST;
    uci_msg->msg_header.rsv = 0;
    uci_msg->msg_header.oid = OID_TEST_STOP_CMD;
    uci_msg->msg_header.rsv1 = 0;
    uci_msg->msg_header.payload_len = 1 ;
    uci_msg->msg_data.core_dev_rst_rsp.status = STATUS_OK;
    
    ret = uci_msg_send(uci_msg);
    
    mem_free(mem_pool);

    return ret;
}
int32_t uwbs_test_stop_ntf_handler(void)
{
    device_inst_t  *dev_inst  = uci_get_dev_inst();
    mem_pool_t *mem_pool = NULL;
    uci_msg_t  *uci_msg  = NULL;
    int32_t    ret       = 0;

    uwbs_change_device_state(DEVICE_STATE_READY);
    mdelay(50);
    
    mem_pool = mem_alloc();
    if(NULL == mem_pool)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uwbs_core_set_config_rsp_handler mem_alloc fail!");
        #endif
        return -1;
    }

    uci_msg = (uci_msg_t *)(mem_pool->buf);
    uci_msg->msg_header.msg_type = CTRL_MSG_NTF;
    uci_msg->msg_header.pbf = CTRL_MSG_COMPLETE;
    uci_msg->msg_header.gid = GID_FIRA_TEST;
    uci_msg->msg_header.rsv = 0;
    uci_msg->msg_header.oid = OID_TEST_STOP_CMD;
    uci_msg->msg_header.rsv1 = 0;
    uci_msg->msg_header.payload_len = 0;
    
    ret = uci_msg_send(uci_msg);
    
    mem_free(mem_pool);
    
    return ret;
}



// ====================================== 指令对应的操作函数 ============================================

static int32_t uwbs_core_device_reset_rsp_handler(void)
{
    mem_pool_t *mem_pool = NULL;
    uci_msg_t  *uci_msg  = NULL;
    int32_t    ret       = 0;

    mem_pool = mem_alloc();
    if(NULL == mem_pool)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uwbs_core_device_reset_rsp_handler mem_alloc fail!");
        #endif

        return -1;
    }

    uci_msg = (uci_msg_t *)(mem_pool->buf);

    uci_msg->msg_header.msg_type = CTRL_MSG_RSP;
    uci_msg->msg_header.pbf = CTRL_MSG_COMPLETE;
    uci_msg->msg_header.gid = GID_UCI_CORE;
    uci_msg->msg_header.rsv = 0;
    uci_msg->msg_header.oid = OID_CORE_DEVICE_RESET;
    uci_msg->msg_header.rsv1 = 0;
    uci_msg->msg_header.payload_len = 1;
    uci_msg->msg_data.core_dev_rst_rsp.status = STATUS_OK;

    ret = uci_msg_send(uci_msg);
    
    mem_free(mem_pool);

    return ret;
}
static void uwbs_core_device_reset_cmd_handler(uint8_t *uci_msg_payload, uint8_t payload_len)
{
    uci_core_dev_reset_cmd_t *uci_core_dev_reset_cmd = NULL;
    device_inst_t            *dev_inst               = uci_get_dev_inst();
    int32_t                  ret                     = 0;

    if(NULL == uci_msg_payload)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uci_msg_payload Is Null!");
        #endif
        return;
    }

    uci_core_dev_reset_cmd = (uci_core_dev_reset_cmd_t *)uci_msg_payload;
    if(0x00 != uci_core_dev_reset_cmd->reset_cfg)
    {
        return;
    }

    ret = uwbs_core_device_reset_rsp_handler();//通过CAN发送响应
    mdelay(50);
    uwbs_change_device_state(DEVICE_STATE_READY);
    test_release();
    
    memset(dev_inst, 0, sizeof(device_inst_t));
    
    uwbs_init();
}


static int32_t uwbs_core_get_device_info_rsp_handler(void)
{
    mem_pool_t *mem_pool = NULL;
    uci_msg_t  *uci_msg  = NULL;
    int32_t    ret       = 0;

    mem_pool = mem_alloc();
    if(NULL == mem_pool)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uwbs_core_get_device_info_rsp_handler mem_alloc fail!");
        #endif

        return -1;
    }

    uci_msg = (uci_msg_t *)(mem_pool->buf);

    uci_msg->msg_header.msg_type = CTRL_MSG_RSP;
    uci_msg->msg_header.pbf = CTRL_MSG_COMPLETE;
    uci_msg->msg_header.gid = GID_UCI_CORE;
    uci_msg->msg_header.rsv = 0;
    uci_msg->msg_header.oid = OID_CORE_GET_DEVICE_INF;
    uci_msg->msg_header.rsv1 = 0;
    uci_msg->msg_header.payload_len = 10;

    uci_msg->msg_data.core_get_dev_inf_rsp.status = STATUS_OK;
    uci_msg->msg_data.core_get_dev_inf_rsp.uci_generic_version = 0x0101;
    uci_msg->msg_data.core_get_dev_inf_rsp.mac_version = 0x0000;
    uci_msg->msg_data.core_get_dev_inf_rsp.phy_version = 0x0000;
    uci_msg->msg_data.core_get_dev_inf_rsp.uci_test_version = 0x0000;
    uci_msg->msg_data.core_get_dev_inf_rsp.vendor_spec_inf_len = 0;

    ret = uci_msg_send(uci_msg);
    
    mem_free(mem_pool);

    return ret;
}
static void uwbs_core_get_device_info_cmd_handler(uint8_t *uci_msg_payload, uint8_t payload_len)
{
    int32_t ret = 0;

    ret = uwbs_core_get_device_info_rsp_handler();
    if(ret <= 0)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("Uwbs Send CORE_GET_DEVICE_INFO_RSP Failed!");
        #endif
        return;
    }
}


void uwbs_core_set_config_save(uint8_t tag_id, uint8_t *value, uint8_t *fail_param, uint8_t *fail_param_len)
{
    device_inst_t *dev_inst = uci_get_dev_inst();

    switch(tag_id)
    {
        case DEVICE_STATE:
        {
            if(DEVICE_STATE_READY != *value && DEVICE_STATE_ACTIVE != *value && DEVICE_STATE_ERR != *value)
            {
                fail_param[(*fail_param_len)++] = (uint8_t)DEVICE_STATE;
                fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_RANGE;
            }
            else
            {
 //               dev_inst->device_state.cur_state = *value;
            }
            break;
        }
        case LOW_POWER_MODE:
        {
            if(LOW_POWER_MODE_DISABLE != *value && LOW_POWER_MODE_ENABLE != *value)
            {
                fail_param[(*fail_param_len)++] = (uint8_t)LOW_POWER_MODE;
                fail_param[(*fail_param_len)++] = (uint8_t)STATUS_INVALID_RANGE;
            }
            else
            {
                dev_inst->device_cfg.low_power_mode = *value;
            }
            break;
        }
        default:
        {
            break;
        }
    }
}
static int32_t uwbs_core_set_config_rsp_handler(uint8_t *fail_cfg_param, uint8_t fail_cfg_param_len)
{
    mem_pool_t *mem_pool = NULL;
    uci_msg_t  *uci_msg  = NULL;
    int32_t    ret       = 0;
    uint8_t    cfg_idx   = 0;
    uint8_t    tag_id   = 0;
    uint8_t    cfg_len   = 0;
    uint8_t    cfg_value[20] = {0};
    uint8_t    mem_idx             = 0;
    mem_pool = mem_alloc();
    if(NULL == mem_pool)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uwbs_core_set_config_rsp_handler mem_alloc fail!");
        #endif
        return -1;
    }

    uci_msg = (uci_msg_t *)(mem_pool->buf);

    uci_msg->msg_header.msg_type = CTRL_MSG_RSP;
    uci_msg->msg_header.pbf = CTRL_MSG_COMPLETE;
    uci_msg->msg_header.gid = GID_UCI_CORE;
    uci_msg->msg_header.rsv = 0;
    uci_msg->msg_header.oid = OID_CORE_SET_CONFIG;
    uci_msg->msg_header.rsv1 = 0;
    uci_msg->msg_header.payload_len = 2 + fail_cfg_param_len;
    uci_msg->msg_data.core_set_cfg_rsp.param_num = fail_cfg_param_len / 2;
    
    memcpy(uci_msg->msg_data.core_set_cfg_rsp.param, fail_cfg_param, fail_cfg_param_len);

    if(0 == fail_cfg_param_len)
    {
        uci_msg->msg_data.core_set_cfg_rsp.status = STATUS_OK;
    }
    else
    {
        uci_msg->msg_data.core_set_cfg_rsp.status = STATUS_INVALID_RANGE;
    }
    
    ret = uci_msg_send(uci_msg);
    
    mem_free(mem_pool);

    return ret;
}
static void uwbs_core_set_config_cmd_handler(uint8_t *uci_msg_payload, uint8_t payload_len)
{
    uci_core_set_cfg_cmd_t *uci_core_set_cfg_cmd = NULL;
    int32_t                ret                   = 0;
    uint8_t                fail_cfg_param[4]     = {0};
    uint8_t                value                 = 0;
    uint8_t                payload_idx           = 0;
    uint8_t                tag                   = 0;
    uint8_t                len                   = 0;
    uint8_t                fail_cfg_param_len    = 0;
    uint8_t                param_payload_len     = 0;

    if(NULL == uci_msg_payload)
    {
        return;
    }

    uci_core_set_cfg_cmd = (uci_core_set_cfg_cmd_t *)uci_msg_payload;
    param_payload_len = payload_len - 1;

    do
    {
        tag = uci_core_set_cfg_cmd->param[payload_idx++];
        len = uci_core_set_cfg_cmd->param[payload_idx++];

        memcpy(&value, &uci_core_set_cfg_cmd->param[payload_idx], len);
        payload_idx += len;

        uwbs_core_set_config_save(tag, &value, fail_cfg_param, &fail_cfg_param_len);
    }while(payload_idx < param_payload_len);

    ret = uwbs_core_set_config_rsp_handler(fail_cfg_param, fail_cfg_param_len);

    if(ret <= 0)
    {
        return;
    }
}


void uwbs_core_get_config(uint8_t tag_id, uint8_t *param_buf, uint8_t *param_len)
{
    device_inst_t *dev_inst = uci_get_dev_inst();

    switch(tag_id)
    {
        case DEVICE_STATE:
        {
            param_buf[(*param_len)++] = DEVICE_STATE;
            param_buf[(*param_len)++] = 1;
            param_buf[(*param_len)++] = dev_inst->device_state.cur_state;
            break;
        }
        case LOW_POWER_MODE:
        {
            param_buf[(*param_len)++] = LOW_POWER_MODE;
            param_buf[(*param_len)++] = 1;
            param_buf[(*param_len)++] = dev_inst->device_cfg.low_power_mode;
            break;
        }
        default:
        {
            break;
        }
    }
}
static int32_t uwbs_core_get_config_rsp_handler(uint8_t *param_buf, uint8_t param_len, uint8_t param_num)
{
    mem_pool_t    *mem_pool = NULL;
    uci_msg_t     *uci_msg  = NULL;
    device_inst_t *dev_inst = uci_get_dev_inst();
    int32_t       ret       = 0;

    mem_pool = mem_alloc();
    if(NULL == mem_pool)
    {
        return -1;
    }

    uci_msg = (uci_msg_t *)(mem_pool->buf);

    uci_msg->msg_header.msg_type = CTRL_MSG_RSP;
    uci_msg->msg_header.pbf = CTRL_MSG_COMPLETE;
    uci_msg->msg_header.gid = GID_UCI_CORE;
    uci_msg->msg_header.rsv = 0;
    uci_msg->msg_header.oid = OID_CORE_GET_CONFIG;
    uci_msg->msg_header.rsv1 = 0;
    uci_msg->msg_header.payload_len = param_len + 2;

    uci_msg->msg_data.core_get_cfg_rsp.status = STATUS_OK;
    uci_msg->msg_data.core_get_cfg_rsp.param_num = param_num;
    memcpy(&uci_msg->msg_data.core_get_cfg_rsp.param[0], param_buf, param_len);
    
    ret = uci_msg_send(uci_msg);
    mem_free(mem_pool);

    return ret;
}
static void uwbs_core_get_config_cmd_handler(uint8_t *uci_msg_payload, uint8_t payload_len)
{
    uci_core_get_cfg_cmd_t *uci_core_get_cfg_cmd = NULL;
    int32_t                ret                   = 0;
    uint8_t                param_buf[6]          = {0};
    uint8_t                tag_id                = 0;
    uint8_t                payload_index         = 0;
    uint8_t                param_len             = 0;
    uint8_t                param_num             = 0;

    if(NULL == uci_msg_payload)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uci_msg_payload Is Null!");
        #endif
        return;
    }

    uci_core_get_cfg_cmd = (uci_core_get_cfg_cmd_t *)uci_msg_payload;

    do
    {
        tag_id = uci_core_get_cfg_cmd->param[payload_index++];
        uwbs_core_get_config(tag_id, param_buf, &param_len);
        param_num++;
    }while(payload_index < (payload_len - 1));

    ret = uwbs_core_get_config_rsp_handler(param_buf, param_len, param_num);
    if(ret <= 0)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("Uwbs Send CORE_GET_CONFIG_RSP Failed!");
        #endif
    }
}


static void uwbs_session_init_cmd_handler(uint8_t *uci_msg_payload, uint8_t payload_len)
{
    device_inst_t          *dev_inst         = uci_get_dev_inst();
    uci_session_init_cmd_t *session_init_cmd = NULL;
    session_inst_t         *session_inst     = NULL;
    uint8_t                session_index     = 0;
    int8_t                 status            = STATUS_OK;
    
    if(NULL == uci_msg_payload)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uci_msg_payload Is Null!");
        #endif
        return;
    }
    session_init_cmd = (uci_session_init_cmd_t *)uci_msg_payload;

    if(is_find_session_id(session_init_cmd->session_id, &session_index))
    {
        release_session_by_index(session_index);
        status = STATUS_OK;
        //status = STATUS_ERROR_SESSION_DUPLICATE;
    }
    else if(!uwbs_alloc_idle_session_idx(&session_index))
    {
        status = STATUS_ERROR_MAX_SESSION_EXCEEDED;
    }
    else
    {
        status = STATUS_OK;
    }

    if(STATUS_OK == status)
    {
        if(SESSION_TYPE_TEST == session_init_cmd->session_type)
        {
            g_work_mode = WORK_MODE_TEST;
            //zn_vga_to_test_mode();    
            hal_radar_stop();
            g_log_level = LOG_LEVEL_OFF;
            //set_log_level(LOG_LEVEL_OFF);
        }
        else
        {
            g_work_mode = WORK_MODE_RADAR;
            //zn_vga_to_radar();
        }

        session_inst = &dev_inst->session_inst[session_index];
        session_inst->session_is_used = TRUE;
        session_inst->session_id = session_init_cmd->session_id;
        session_inst->session_type = session_init_cmd->session_type;
        session_inst->session_handle = session_init_cmd->session_id;// + (session_init_cmd->session_type << 24);
        session_inst->session_reason_code = STATE_CHANGE_WITH_SESSION_MANAGEMENT_COMMANDS;
    }
    
    if(uwbs_session_init_cmd_rsp_send(status, session_inst) <= 0)
    {
        uwbs_delete_one_session(session_index);

        #ifdef _MAC_DEBUG
        LOG_ERROR("Uwbs Send SESSION_INIT_RSP Failed!");
        #endif
        return;
    }
    if(STATUS_OK == status)
    {
        mdelay(50);
        uwbs_change_session_state(session_index, SESSION_STATE_INIT);
    }
    return;
}


static void uwbs_session_deinit_cmd_handler(uint8_t *uci_msg_payload, uint8_t payload_len)
{
    uci_session_deinit_cmd_t *session_deinit_cmd = NULL;
    device_inst_t            *dev_inst           = uci_get_dev_inst();
    session_inst_t           *session_inst       = NULL;
    uint8_t                  session_index       = 0;

    #ifdef _MAC_DEBUG
    LOG_DEBUG("Uwbs recv SESSION_DEINIT Cmd!");
    #endif

    if(NULL == uci_msg_payload)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uci_msg_payload Is Null!");
        #endif
        return;
    }

    session_deinit_cmd = (uci_session_deinit_cmd_t *)uci_msg_payload;

    if(STATUS_OK == uwbs_session_deinit_cmd_rsp_send(session_deinit_cmd->session_handle, &session_index))
    {
        session_inst = &dev_inst->session_inst[session_index];
        if(session_inst->session_type ==  SESSION_TYPE_TEST)
        {
            test_release();
            g_work_mode = WORK_MODE_RADAR;
        }
        else if(session_inst->session_type ==  SESSION_TYPE_RADAR)//如果当前会话是雷达测试
        {
            hal_gp_timer_close(TIMER2);//这个定时器用于给雷达定时发送
        }
        
        session_inst->session_reason_code = STATE_CHANGE_WITH_SESSION_MANAGEMENT_COMMANDS;
        dev_inst->session_inst[session_index].session_state.cur_state = SESSION_STATE_DEINIT;
        uwbs_delete_one_session(session_index);
    }
    if(0 == uwbs_session_active_state_num())//当前活动状态的会话不为0
    {
        
    }
}


static void uwbs_session_set_app_config_cmd_handler(uint8_t *uci_msg_payload, uint8_t payload_len)
{
    device_inst_t                 *dev_inst          = uci_get_dev_inst();
    uci_session_set_app_cfg_cmd_t *session_set_cfg   = NULL;
    session_inst_t                *session_inst      = NULL;
    mem_pool_t                    *mem_pool          = NULL;
    uint8_t                       *fail_cfg_param    = NULL;
    uint8_t                       value[64]          = {0};
    uint8_t                       session_index      = 0;
    uint8_t                       payload_idx        = 0;
    uint8_t                       tag                = 0;
    uint8_t                       len                = 0;
    uint8_t                       fail_cfg_param_num = 0;
    uint8_t                       param_payload_len  = 0;
    int8_t                        ret                = 0;
    int8_t                        status             = STATUS_OK;

    if((NULL == uci_msg_payload) || (payload_len < 5))
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uci_msg_payload Is Null!");
        #endif
        return;
    }

    session_set_cfg = (uci_session_set_app_cfg_cmd_t *)uci_msg_payload;
    param_payload_len =  payload_len - 5;

    mem_pool = mem_alloc();
    if(NULL == mem_pool)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uwbs_session_set_app_config_cmd_handler mem_alloc fail!");
        #endif
        return;
    }

    fail_cfg_param = mem_pool->buf;

    if(is_find_session_handle(session_set_cfg->session_handle, &session_index))
    {
        do
        {
            tag = session_set_cfg->app_cfg_param[payload_idx++];
            len = session_set_cfg->app_cfg_param[payload_idx++];

            memcpy(value, &session_set_cfg->app_cfg_param[payload_idx], len);
            payload_idx += len;

            uwb_session_app_cfg_save(session_index, tag, len, value, fail_cfg_param, &fail_cfg_param_num);
        }while(payload_idx < param_payload_len);

        dev_inst->session_inst[session_index].session_is_cfg = TRUE;
    }
    else
    {
        status = STATUS_ERROR_SESSION_NOT_EXIST;
    }

    uwbs_session_set_app_config_cmd_rsp_send(status, session_set_cfg->session_handle, fail_cfg_param, fail_cfg_param_num);

    mem_free(mem_pool);

    return;
}


static void uwbs_session_get_app_config_cmd_handler(uint8_t *uci_msg_payload, uint8_t payload_len)
{
    uci_session_get_app_cfg_cmd_t *app_cfg_cmd                 = NULL;
    int32_t                       ret                          = 0;

    if(NULL == uci_msg_payload)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uci_msg_payload Is Null!");
        #endif
        return;
    }

    app_cfg_cmd = (uci_session_get_app_cfg_cmd_t *)uci_msg_payload;

    ret = uwbs_session_get_app_config_rsp_handler(app_cfg_cmd->session_handle, app_cfg_cmd->app_cfg_num, app_cfg_cmd->app_cfg_param);
    if(ret <= 0)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("Uwbs Send SESSION_GET_APP_CONFIG_RSP Failed!");
        #endif
    }
}


static void uwbs_session_get_state_cmd_handler(uint8_t *uci_msg_payload, uint8_t payload_len)
{
    uci_session_get_state_cmd_t *uci_session_get_state_cmd = NULL;
    device_inst_t               *dev_inst                  = uci_get_dev_inst();
    uint8_t                     session_state              = SESSION_STATE_DEINIT;
    uint8_t                     session_index              = 0;
    int32_t                     ret                        = 0;

    if(NULL == uci_msg_payload)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uci_msg_payload Is Null!");
        #endif
        return;
    }

    uci_session_get_state_cmd = (uci_session_get_state_cmd_t *)uci_msg_payload;
    
    if(is_find_session_handle(uci_session_get_state_cmd->session_handle, &session_index))
    {
        session_state = dev_inst->session_inst[session_index].session_state.cur_state;
    }
    else
    {
        session_state = SESSION_STATE_DEINIT;
    }

    ret = uwbs_session_get_state_rsp_handler(session_state);
    if(ret <= 0)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("Uwbs Send SESSION_GET_STATE_RSP Failed!"); 
        #endif
    }
}


static void uwbs_range_start_cmd_handler(uint8_t *uci_msg_payload, uint8_t payload_len)
{
    uci_range_start_cmd_t *range_start_cmd = NULL;
    device_inst_t         *dev_inst        = uci_get_dev_inst();
    session_inst_t        *session_inst    = NULL;
    uint8_t               session_index    = 0;
    uint8_t               status           = STATUS_OK;
    uint8_t               value_1 = 0;

    if(NULL == uci_msg_payload)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uci_msg_payload Is Null!");
        #endif
        return;
    }

    range_start_cmd = (uci_range_start_cmd_t *)uci_msg_payload;
    status = uwbs_check_and_find_session_index(range_start_cmd->session_handle, &session_index);
    if(SESSION_STATE_ACTIVE == uwbs_get_session_state(session_index))
    {
        status = STATUS_REJECTED;
    }
    
    if(uwbs_range_start_cmd_rsp_send(status) <= 0)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("Uwbs Send RANGE_START_RSP Failed");
        #endif
        return;
    }
}


static void uwbs_range_stop_cmd_handler(uint8_t *uci_msg_payload, uint8_t payload_len)
{
    uci_range_stop_cmd_t *range_stop_cmd = NULL;
    device_inst_t        *dev_inst       = uci_get_dev_inst();
    session_inst_t       *session_inst   = NULL;
    uint8_t              session_index   = 0;

    if(NULL == uci_msg_payload)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uci_msg_payload Is Null!");
        #endif
        return;
    }

    range_stop_cmd = (uci_range_stop_cmd_t *)uci_msg_payload;

    if(STATUS_OK == uwbs_range_stop_cmd_rsp_send(range_stop_cmd->session_handle, &session_index))
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("Uwbs Send RANGE_STOP_RSP Failed!");
        #endif
    }
    uwbs_range_stop(session_index);
}

static void uwbs_set_app_cfg_page_values_cmd_handler(uint8_t *uci_msg_payload, uint8_t payload_len)
{
    uci_set_app_cfg_page_values_cfg_cmd_t *uci_set_app_cfg_page_values_cmd = NULL;
    device_inst_t               *dev_inst                  = uci_get_dev_inst();
    int32_t                     ret                        = 0;
    uint8_t                     fail_param[128]   = {0};
    uint8_t                     value                 = 0;
    uint8_t                     payload_idx           = 0;
    uint8_t                     tag                   = 0;
    uint8_t                     len                   = 0;
    uint8_t                     fail_param_len        = 0;
    uint8_t                     param_payload_len     = 0;
    uint8_t                     fail_param_num        = 0;
    
    if(NULL == uci_msg_payload)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uci_msg_payload Is Null!");
        #endif
        return;
    }

    uci_set_app_cfg_page_values_cmd = (uci_set_app_cfg_page_values_cfg_cmd_t *)uci_msg_payload;
    param_payload_len = payload_len - 1;
    
    do
    {
        tag = uci_set_app_cfg_page_values_cmd->param[payload_idx++];
        len = uci_set_app_cfg_page_values_cmd->param[payload_idx++];

        memcpy(&value, &uci_set_app_cfg_page_values_cmd->param[payload_idx], len);
        payload_idx += len;

        uwbs_app_cfg_page_values_save(tag, &value, len, fail_param, &fail_param_len, &fail_param_num);
    }while(payload_idx < param_payload_len);
    
    ret = uwbs_set_app_cfg_page_values_rsp_handler(fail_param, fail_param_len, fail_param_num);
    if(ret <= 0)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("Uwbs Send SESSION_GET_STATE_RSP Failed!"); 
        #endif
    }
    uwbs_set_app_cfg_page_values_ntf_handler(APPLIED);
    
    return;
}


static void uwbs_get_app_cfg_page_values_cmd_handler(uint8_t *uci_msg_payload, uint8_t payload_len)
{
    uci_get_app_cfg_page_values_cfg_cmd_t *uci_get_app_cfg_page_values_cmd = NULL;
    device_inst_t               *dev_inst                  = uci_get_dev_inst();
    int32_t                     ret                        = 0;
    uint8_t                     param_buf[256]          = {0};
    uint8_t                     tag_id                = 0;
    uint8_t                     payload_index         = 0;
    uint8_t                     param_num             = 0;
    uint8_t                     param_len             = 0;
    
    if(NULL == uci_msg_payload)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uci_msg_payload Is Null!");
        #endif
        return;
    }

    uci_get_app_cfg_page_values_cmd = (uci_get_app_cfg_page_values_cfg_cmd_t *)uci_msg_payload;

    do
    {
        tag_id = uci_get_app_cfg_page_values_cmd->param[payload_index++];
        uwbs_get_app_cfg_page_values(tag_id, param_buf, &param_len);
        param_num++;

    }while(payload_index < (payload_len -1));
    
    ret = uwbs_get_app_cfg_page_values_rsp_handler(param_buf, param_len, param_num - 1);
    if(ret <= 0)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uwbs_get_app_cfg_page_values_cmd_handler Failed!"); 
        #endif
    }
}


static void uwbs_test_start_cmd_handler(uint8_t *uci_msg_payload, uint8_t payload_len)
{
    uci_core_set_cfg_cmd_t        *test_start_cmd    = NULL;
    device_inst_t                 *dev_inst          = uci_get_dev_inst();
    mem_pool_t                    *mem_pool          = NULL;
    uint8_t                       *fail_cfg_param    = NULL;
    uint8_t                       value[64]          = {0};
    uint8_t                       payload_idx        = 0;
    uint8_t                       tag                = 0;
    uint8_t                       len                = 0;
    uint8_t                       fail_cfg_param_num = 0;
    uint8_t                       param_payload_len  = 0;  
    uint8_t                       param_num          = 0;   
    int32_t                       ret                = 0;

    if(NULL == uci_msg_payload)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uci_msg_payload Is Null!");
        #endif
        return;
    }

    test_start_cmd = (uci_core_set_cfg_cmd_t *)uci_msg_payload;
    param_payload_len =  payload_len - 1;
    
    mem_pool = mem_alloc();
    if(NULL == mem_pool)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uwbs_session_set_app_config_cmd_handler mem_alloc fail!");
        #endif
        return;
    }

    fail_cfg_param = mem_pool->buf;
    do
    {
        tag = test_start_cmd->param[payload_idx++];
        len = test_start_cmd->param[payload_idx++];

        memcpy(value, &test_start_cmd->param[payload_idx], len);
        payload_idx += len;
        param_num++;

        uwbs_test_start_save(tag, len, value, fail_cfg_param, &fail_cfg_param_num);
    }while((payload_idx < param_payload_len)&& (param_num < test_start_cmd->param_num));

    dev_inst->device_state.cur_state = DEVICE_STATE_ACTIVE;
    
    //配置test_mode
    memset(&test_ctrl, 0, sizeof(test_ctrl_t));
    test_ctrl.test_start = TRUE;//开启test_mode
    
    uwb_test_mode_config();//根据设置的参数配置UWB
    ret = uwbs_test_start_rsp_handler(fail_cfg_param, fail_cfg_param_num);

//    udelay(dev_inst->test_cfg.test_delay);
    mem_free(mem_pool);
    return;
}


static void uwbs_test_stop_cmd_handler(uint8_t *uci_msg_payload, uint8_t payload_len)
{
    uci_core_set_cfg_cmd_t        *test_start_cmd    = NULL;
    device_inst_t                 *dev_inst          = uci_get_dev_inst();
    mem_pool_t                    *mem_pool          = NULL;
    uint8_t                       *fail_cfg_param    = NULL;
    uint8_t                       value[64]          = {0};
    uint8_t                       payload_idx        = 0;
    uint8_t                       tag                = 0;
    uint8_t                       len                = 0;
    uint8_t                       fail_cfg_param_num = 0;
    uint8_t                       param_payload_len  = 0;  
    uint8_t                       param_num          = 0;   
    int32_t                       ret                = 0;

    ret = uwbs_test_stop_rsp_handler();
    mdelay(50);
    ret = uwbs_test_stop_ntf_handler();
    if(ret <= 0)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("uwbs_get_app_cfg_page_values_cmd_handler Failed!"); 
        #endif
    }
    test_release();
}


void uwbs_phydebug_cmd_handler(uint8_t *uciMsgPayload, uint8_t payloadLen)
{
    phy_cmd_t* phy_cmd = get_phy_cmd_addr();
    
    phy_cmd->msg_rx_buffer[0] = 0x2E;
    phy_cmd->msg_rx_buffer[1] = 0x20;
    phy_cmd->msg_rx_buffer[2] = 0x00;
    phy_cmd->msg_rx_buffer[3] = payloadLen;
    memcpy(phy_cmd->msg_rx_buffer+4, uciMsgPayload, payloadLen);
    phy_cmd->msg_recv_count = payloadLen+4;
    phy_cmd->msg_recv_flag = 1;
}



// ============================================================================================================

uwbs_msg_state_table_t uwbs_msg_state_table[] =
{
    {CORE_DEVICE_RESET_CMD,                        uwbs_core_device_reset_cmd_handler},
    {CORE_GET_DEVICE_INFO_CMD,                     uwbs_core_get_device_info_cmd_handler},
    {CORE_SET_CONFIG_CMD,                          uwbs_core_set_config_cmd_handler},
    {CORE_GET_CONFIG_CMD,                          uwbs_core_get_config_cmd_handler},
    {SESSION_INIT_CMD,                             uwbs_session_init_cmd_handler},
    {SESSION_DEINIT_CMD,                           uwbs_session_deinit_cmd_handler},
    {SESSION_SET_APP_CONFIG_CMD,                   uwbs_session_set_app_config_cmd_handler},
    {SESSION_GET_APP_CONFIG_CMD,                   uwbs_session_get_app_config_cmd_handler},
    {SESSION_GET_STATE_CMD,                        uwbs_session_get_state_cmd_handler},
    {RANGE_START_CMD,                              uwbs_range_start_cmd_handler},
    {RANGE_STOP_CMD,                               uwbs_range_stop_cmd_handler},
    {SET_APP_CFG_PAGE_VALUES_CMD,                  uwbs_set_app_cfg_page_values_cmd_handler},
    {GET_APP_CFG_PAGE_VALUES_CMD,                  uwbs_get_app_cfg_page_values_cmd_handler},
    {TEST_START_CMD,                               uwbs_test_start_cmd_handler},
    {TEST_STOP_CMD,                                uwbs_test_stop_cmd_handler},
    {TEST_PHY_DEBUG_CMD,                           uwbs_phydebug_cmd_handler},
};

void uwbs_loop(void)
{
    mem_pool_t *mem_pool    = NULL;
    uci_msg_t  *uci_msg_buf = NULL;
    int32_t    ret          = 0;
    uint8_t    index        = 0;
    uint8_t    status       = 0;
    uint8_t    uci_msg_gid  = 0;
    uint8_t    uci_msg_oid  = 0;

    if(!uwbs_have_cmd_msg())
    {
        return;
    }

    mem_pool = mem_alloc();
    if(NULL == mem_pool)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("UwbsLoop mem_alloc fail!");
        #endif
        return;
    }

    uci_msg_buf = (uci_msg_t *)(mem_pool->buf);

    ret = uci_msg_get((uint8_t *)uci_msg_buf, CTRL_MSG_CMD);//从g_host_to_uwbs_cmd_buf获取指令
    if(ret <= 0)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("Uwbs Receive Cmd Failed!");
        #endif
        mem_free(mem_pool);
        return;
    }

    if(CTRL_MSG_CMD != uci_msg_buf->msg_header.msg_type)
    {
        #ifdef _MAC_DEBUG
        LOG_ERROR("Uwbs Msg Is Not Cmd!");
        #endif
        mem_free(mem_pool);
        return;
    }

    uci_msg_gid = uci_msg_buf->msg_header.gid;
    uci_msg_oid = uci_msg_buf->msg_header.oid;

    switch(uci_msg_gid)
    {
        case GID_UCI_CORE:
        {
            status = gid_uci_core_process(uci_msg_oid);
            break;
        }
        case GID_UWB_SESSION_CFG:
        {
            status = gid_uwb_session_cfg_process(uci_msg_oid);
            break;
        }
        case GID_UWB_SESSION_CTRL:
        {
            status = gid_uwb_session_ctrl_process(uci_msg_oid);
            break;
        }
        case GID_FIRA_TEST:
        {
            status = GidTestProcess(uci_msg_oid);
            break;
        }
        case GID_PROPRIETARY_GROUP:
        {
            status = gid_uwb_proprietary_group_process(uci_msg_oid);
            break;
        }
        case GID_PHY_DEBUG:
        {
            status = gid_phy_debug_process(uci_msg_oid);
            break;
        }
        default:
        {
            status = STATUS_UNKNOWN_GID;
            break;
        }
    }

    if(STATUS_OK != status)
    {
        ret = invalid_gid_oid_rsp_handler(&uci_msg_buf->msg_header, status);
        if(ret <= 0)
        {
            #ifdef _MAC_DEBUG
            LOG_ERROR("Uwbs INVALID_GID_OID_RSP Send Failed!");
            #endif
        }
        clear_msg_buf_flag();
        mem_free(mem_pool);
        return;
    }

    for(index = 0; index < sizeof(uwbs_msg_state_table) / sizeof(uwbs_msg_state_table_t); index++)
    {
        if(uwbs_current_ctl_msg == uwbs_msg_state_table[index].uci_control_msg)
        {
            uwbs_msg_state_table[index].uci_control_msg_handler((uint8_t *)&uci_msg_buf->msg_data, uci_msg_buf->msg_header.payload_len);
            break;
        }
    }

    mem_free(mem_pool);
}



