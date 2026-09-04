#include "test_mode.h"

#include "zn_dca.h"
#include "hal_uwb.h"

#include "gconfig.h"
#include "uci.h"
#include "cmd.h"
#include "tuwb.h"


test_process_t testProc = {0};
test_ctrl_t test_ctrl = {0};


// ======================= uwb²âÊÔ»Øµ÷º¯Êý =========================
void test_tx_done_cb(const zn_cb_data_t *txd)
{
    testProc.cb_flag |= STATUS_TX_DONE;
    return;
}
void test_rx_ok_cb(const zn_cb_data_t *rxd)
{
    zn_driver_config_t* driver_config = zn_get_dirver_config_addr();
    if(RFRAME_SP3 == driver_config->phy_config.rf_cfg)
    {
        testProc.cb_flag |= STATUS_RX_DONE;
    }
    else
    {
        zn_read_rx_data(testProc.psduRxOk, rxd->data_length);
        testProc.psduLen = rxd->data_length - 2;
        testProc.cb_flag |= STATUS_RX_OK;
    }

    return;
}
void test_rx_timeout_cb(const zn_cb_data_t *rxd)
{
    testProc.cb_flag |= STATUS_RX_TO;
    return;
}
void test_rx_err_cb(const zn_cb_data_t *rxd)
{
    testProc.cb_flag |= STATUS_RX_ERR;
    return;
}
void test_rx_done_cb(const zn_cb_data_t *rxd)
{
    testProc.cb_flag |= STATUS_RX_DONE;
    return;
}
void test_sts_err_cb(const zn_cb_data_t *rxd)
{
    testProc.cb_flag |= STATUS_STS_ERR;
    return;
}
void test_rx_sfd_timeout_cb(const zn_cb_data_t *rxd)
{
    testProc.cb_flag |= STATUS_RX_TO;
    return;
}
void test_rx_phr_err_cb(const zn_cb_data_t *rxd)
{
    testProc.cb_flag |= STATUS_RX_ERR;
    return;
}


// ========================================================================================================

void zn_sts_config_for_test(void)
{
    device_inst_t *dev_inst = uci_get_dev_inst();
    uint32_t *key_value = ((uint32_t *)dev_inst->session_inst[0].session_cfg.static_key[3].key_value);
    uint32_t reg = 0;
    
    zn_write_32bit_reg(STS_IV_P0, *(key_value + 0)); //stsvcounter0_31
    zn_write_32bit_reg(STS_IV_P1, *(key_value + 1)); //cryptoStsIndex0_31
    zn_write_32bit_reg(STS_IV_P2, *(key_value + 2));//phyVUpper0_31
    zn_write_32bit_reg(STS_IV_P3, *(key_value + 3));//phyVUpper32_63
    
    key_value = ((uint32_t *)dev_inst->session_inst[0].session_cfg.static_key[4].key_value);
    zn_write_32bit_reg(STS_KEY_P0, *(key_value + 0)); //stskey0_31
    zn_write_32bit_reg(STS_KEY_P1, *(key_value + 1)); //stskey32_63
    zn_write_32bit_reg(STS_KEY_P2, *(key_value + 2)); //stskey64_95
    zn_write_32bit_reg(STS_KEY_P3, *(key_value + 3)); //stskey96_127

    reg = zn_read_32bit_reg(STS_CFG_ID);
    reg &= (~(STS_CPS_LEN_BIT_MASK | STS_DELTA_BIT_MASK));
    reg |= ((64 << STS_CPS_LEN_BIT_OFFSET) | (1 << STS_DELTA_BIT_OFFSET));
    zn_write_32bit_reg(STS_CFG_ID, reg);
    zn_sts_load_cfg();
}
uint16_t cal_sfd_to_value(uint8_t preamble_duration, uint8_t sfd_id)
{
    uint16_t dat = 0;
    switch(preamble_duration)
    {
        case PREAMBLE_16:   dat += 16;break;
        case PREAMBLE_64:   dat += 64;break;
        case PREAMBLE_1024: dat += 1024;break;
        case PREAMBLE_4096: dat += 4096;break;
        case PREAMBLE_32:   dat += 32;break;
        case PREAMBLE_128:  dat += 128;break;
        case PREAMBLE_256:  dat += 256;break;
        case PREAMBLE_512:  dat += 512;break;
        case PREAMBLE_2048: dat += 2048;break;
    }
    switch(sfd_id)
    {
        case SFD_ID_LEGACY_SFD8:
        case SFD_ID_SFD8:   dat += 8;break;
        case SFD_ID_SFD16:  dat += 16;break;
        case SFD_ID_SFD4:   dat += 4;break;
    }
    return dat;
}
void uwb_test_mode_config(void)
{
    device_inst_t *dev_inst = uci_get_dev_inst();
    hal_uwb_interrupt_callback_t* uwb_irq_callback = &test_mode_uwb_inst.interrupt_callback;
    
    test_mode_uwb_inst.phy_config.channel_num = dev_inst->session_inst[0].session_cfg.channel_no;//CH?
    test_mode_uwb_inst.phy_config.preamble_code_idx = dev_inst->session_inst[0].session_cfg.preamble_code_idx;
    test_mode_uwb_inst.phy_config.sfd_id = dev_inst->session_inst[0].session_cfg.sfd_id;//sfd_id
    test_mode_uwb_inst.phy_config.psdu_data_rate = dev_inst->session_inst[0].session_cfg.psdu_data_rate;
    test_mode_uwb_inst.phy_config.preamble_duration = dev_inst->session_inst[0].session_cfg.preamble_duration;
    test_mode_uwb_inst.phy_config.bprf_phr_data_rate = dev_inst->session_inst[0].session_cfg.bprf_phr_data_rate;
    test_mode_uwb_inst.phy_config.frame_type = dev_inst->test_cfg.frame_type;
    test_mode_uwb_inst.phy_config.sts_seg_num = dev_inst->session_inst[0].session_cfg.number_of_sts_segments;
    test_mode_uwb_inst.phy_config.sts_seg_len = dev_inst->session_inst[0].session_cfg.sts_len;
//    printf("\r\n%d %d %d %d %d %d %d %d %d\r\n",test_mode_uwb_inst.phy_config.channel_num,test_mode_uwb_inst.phy_config.preamble_code_idx,
//                                    test_mode_uwb_inst.phy_config.sfd_id,test_mode_uwb_inst.phy_config.psdu_data_rate,
//                                    test_mode_uwb_inst.phy_config.preamble_duration,test_mode_uwb_inst.phy_config.bprf_phr_data_rate,
//                                    test_mode_uwb_inst.phy_config.frame_type,test_mode_uwb_inst.phy_config.sts_seg_num,
//                                    test_mode_uwb_inst.phy_config.sts_seg_len);
    
    test_mode_uwb_inst.phy_config.sfd_to = cal_sfd_to_value(test_mode_uwb_inst.phy_config.preamble_duration, test_mode_uwb_inst.phy_config.sfd_id);
    if((dev_inst->device_cfg.rx_en == 0x02) || (dev_inst->device_cfg.rx_en == 0x03))//need rx2
    {
        test_mode_uwb_inst.aoa_config.aoa_en = 1;
        test_mode_uwb_inst.aoa_config.ant_sel = RX2_INPUT;
        zn_write_32bit_reg(0x19c4, 0x00000003);
        zn_set_bit(0x1810,15);
    }
    else
    {
        test_mode_uwb_inst.aoa_config.aoa_en = 0;
        zn_write_32bit_reg(0x19c4, 0x00000000);
        zn_clear_bit(0x1810,15);
    }
    
    uwb_irq_callback->cb_tx_done        = &test_tx_done_cb;
    uwb_irq_callback->cb_rx_ok          = &test_rx_ok_cb;
    uwb_irq_callback->cb_rx_timeout     = &test_rx_timeout_cb;
    uwb_irq_callback->cb_rx_err         = &test_rx_err_cb;
    uwb_irq_callback->cb_cp_err         = &test_sts_err_cb;
    uwb_irq_callback->cb_rx_done        = &test_rx_done_cb;
    uwb_irq_callback->cb_rx_sfd_timeout = &test_rx_sfd_timeout_cb;
    uwb_irq_callback->cb_rx_phr_err     = &test_rx_phr_err_cb;
    
    hal_force_uwb_off();
    hal_uwb_config_init(&test_mode_uwb_inst);
    if(RFRAME_SP0 != test_mode_uwb_inst.phy_config.frame_type)
    {
        zn_sts_config_for_test();
    }
}


void test_release(void)
{
    memset(&test_ctrl, 0, sizeof(test_ctrl));
    g_work_mode = WORK_MODE_TEST;
    zn_force_trx_off();
    zn_stop_send_cw();
    //hal_gp_timer_close(TIMER2);
}


void test_rx(void)
{
    device_inst_t  *dev_inst  = uci_get_dev_inst();
    uint32_t status;
    
    hal_force_uwb_off();
    if(!test_ctrl.trx_count)
    {
        hal_uwb_set_rx_timeout(1000*1000*2);
    }
    else
    {
        hal_uwb_set_rx_timeout(dev_inst->test_cfg.time_out*1000+500);
    }
    memset(&testProc, 0, sizeof(test_process_t));
    
    hal_uwb_immediate_rx();
    while(!testProc.cb_flag)
    {
       cpu_delay(1); 
    }
    
    if(testProc.cb_flag & STATUS_RX_TO)
    {
        status = 0x8000;
        uwbs_log_ntf_handler(TRUE, status);
        test_ctrl.rx_to_count++;
    }
    else if((testProc.cb_flag & STATUS_RX_ERR) || (testProc.cb_flag & STATUS_STS_ERR))
    {
        status = 0x010000;
        uwbs_log_ntf_handler(TRUE, status);
        test_ctrl.rx_err_count++;
    }
    else if(testProc.cb_flag & STATUS_RX_OK)
    {
        status = 0x02;
        if(RFRAME_SP0 == dev_inst->test_cfg.frame_type)
        {
            zn_read_rx_timestamp(testProc.rxTimeStampBuf);
        }
        else
        {
            zn_read_rx_timestamp_sts(testProc.rxTimeStampBuf);
        }
        uwbs_log_ntf_handler(TRUE, status);
        test_ctrl.rx_ok_count++;
    }
    else if(testProc.cb_flag & STATUS_RX_DONE)
    {
        status = 0x01;
        if(RFRAME_SP0 == dev_inst->test_cfg.frame_type)
        {
            zn_read_rx_timestamp(testProc.rxTimeStampBuf);
        }
        else
        {
            zn_read_rx_timestamp_sts(testProc.rxTimeStampBuf);
        }
        uwbs_log_ntf_handler(TRUE, status);
        test_ctrl.rx_done_count++;
    }

    test_ctrl.trx_count++;
    if(dev_inst->test_cfg.event_cout_max)
    {
        if(test_ctrl.trx_count == dev_inst->test_cfg.event_cout_max)
        {
            test_ctrl.test_start = FALSE;
            uwbs_test_stop_ntf_handler();
        }
    }
}

void test_tx(void)
{
    uint32_t delay_time = 0;
    device_inst_t  *dev_inst  = uci_get_dev_inst();
    
    memset(&testProc, 0, sizeof(test_process_t));
    test_ctrl.trx_count++;
    
    zn_force_trx_off();
    zn_write_tx_data(dev_inst->test_cfg.psdu_len, dev_inst->test_cfg.psdu, 0);
    zn_write_tx_frame_ctrl(dev_inst->test_cfg.psdu_len + 2, 0, dev_inst->test_cfg.phr_range_bit);
    
    if(test_ctrl.tx_timestamp == 0)
    {
        hal_uwb_immediate_tx();
    }
    else
    {
        delay_time = test_ctrl.tx_timestamp + FROM_US_TO_4NS(dev_inst->test_cfg.tx_cycle_time);
        if(delay_time > zn_get_sys_time())
        {
            hal_uwb_delay_tx(delay_time, &test_mode_uwb_inst);
        }
        else
        {
            hal_uwb_immediate_tx();
        }
    }
    
    while(!testProc.cb_flag)
    {
       cpu_delay(1); 
    }
    if(RFRAME_SP0 == dev_inst->test_cfg.frame_type)
    {
        zn_read_tx_timestamp(testProc.txTimeStampBuf);
    }
    else
    {
        zn_read_tx_timestamp_sts(testProc.txTimeStampBuf);
    }
    test_ctrl.tx_timestamp = *((uint32_t *)&testProc.txTimeStampBuf[1]);
    if(testProc.cb_flag | STATUS_TX_DONE)
    {
        uwbs_log_ntf_handler(FALSE, 0x01);
    }
    if(dev_inst->test_cfg.event_cout_max)
    {
        if(test_ctrl.trx_count == dev_inst->test_cfg.event_cout_max)
        {
            test_release();
            uwbs_test_stop_ntf_handler();
        }
    }
}

void test_cw(void)
{
    hal_uwb_immediate_tx();
    zn_start_send_cw();
    return;
}


void test_mode_loop(void)
{
    device_inst_t *dev_inst   = uci_get_dev_inst();
    
    if(g_work_mode != WORK_MODE_TEST || !test_ctrl.test_start)
    {
        return;
    }
    
    if(RECEIVE_MODE == dev_inst->test_cfg.test_mode)
    {
        test_rx();
    }
    else if(TRANSMIT_MODE == dev_inst->test_cfg.test_mode)
    {
        test_tx();
    }
    else if(CW_TRANSMIT_MODE == dev_inst->test_cfg.test_mode)
    {
        if(!test_ctrl.test_cw_start)
        {
            test_ctrl.test_cw_start = TRUE;
            test_cw();//CW²¨
        }
    }
}


