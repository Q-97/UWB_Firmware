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
#include "range.h"
#include "phy_cmd.h"
#include "phy_test.h"
#include "hal_uart.h"
#include "hal_gpio.h"
#include "ota.h"
#include "hal_can.h"

/*
POLL MSG:  len 9 bytes
BYTE 0 1 2 UZL ascii
BYTE 3 4   dst addr LSB
BYTE 5 6   src addr LSB
BYTE 7     poll index

RESP MSG:  len 7 byes
BYTE 0 1 2 UZL ascii
BYTE 3 4   dst addr LSB
BYTE 5 6   src addr LSB

FINAL MSG: len 22 bytes
BYTE 0 1 2 UZL ascii
BYTE 3 4   dst addr LSB
BYTE 5 6   src addr LSB
BYTE 7 8 9 10 11    poll tx timestamp  LSB
BYTE 12 13 14 15 16 resp rx timestamp  LSB
BYTE 17 18 19 20 21 final tx timestamp LSB
*/

uint8_t g_poll_msg[POLL_MSG_LEN] = {0x59, 0x5a, 0x4c, 0xff, 0xff, 0x01, 0x00, 0x00};
uint8_t g_resp_msg[RESP_MSG_LEN] = {0x59, 0x5a, 0x4c, 0x01, 0x00, 0xff, 0xff};
uint8_t g_final_msg[FINAL_MSG_LEN] = {0x59, 0x5a, 0x4c, 0xff, 0xff, 0x01, 0x00, 0x05};
uint8_t g_recv_buf[MAX_BUFFER_SIZE] = {0};
uint8_t can_cmd_buf[64] = {0};
uint8_t g_can_rx_flag = 0;
hal_can_msg_info_t g_can_recv_msg = {0};
uint16_t g_packet_size = 32;

hal_uwb_instance_t  uwb_instance = 
{
    .phy_config = 
    {
        .channel_num = CHANNEL_9,
        .tia_level = 4,
        .frame_type = RFRAME_SP0,
        .preamble_code_idx = PREAMBLE_CODE_INDEX_10,
        .sfd_id = SFD_ID_SFD8,
        .psdu_data_rate= PSDU_RATE_681,
        .bprf_phr_data_rate = BPRF_PHR_RATE_850,
        .preamble_duration = PREAMBLE_128,
        .prf_mode = PRF_624,
        .pa_level = PA_LEVEL_7,
        .sts_seg_num = STS_SEG_1,
        .sts_seg_len = STS_SEG_LEN_64,
        .sfd_to = 128 + 8, //preamble len + sfd len
        .ant_delay = ANT_DELAY,
        .rx_ts_left_find_len = 70,
        .rx_ts_thresold_len = 200,
    },
    
    .aoa_config = 
    {
        .aoa_en = 0,
        .aoa_mode = TYPE_AOA,
        .aoa_dimension_mode = TYPE_2D,
        .ant_sel = RX2_INPUT,
        .phase_compen_rx0_rx1 = 0.0,
        .phase_compen_rx0_rx2 = 0.0,
        .ant_distance_rx0_rx1 = 1.8,
        .ant_distance_rx0_rx2 = 1.8,
        .ant_distance_rx1_rx2 = 1.8,
        .delay_rx0_rx1 = 0,
    },

    .interrupt_config = 
    {
        .bits.bit0_int_en = 1,
        .bits.bit7_tx_frs = 1,
        .bits.bit8_rx_prd = 1,
        .bits.bit9_rx_sfdd = 1,
        .bits.bit14_rx_fcg = 1,
        .bits.bit13_rx_dfr = 1,
        .bits.bit28_rx_cperr = 1,
        .bits.bit17_rx_rfto = 1,
        .bits.bit26_rx_sfdto = 1,
    },

    .fem_en = 0,
    .rx_ts_retry_en = 1,
    .delay_mode = MODE_UNBLOCK,
    .driver_timer_id = TIMER0
};


hal_gp_timer_t gp_timer = {0};

static uint8_t user_recv_msg(uint8_t ch)
{
    phy_cmd_t* phy_cmd = get_phy_cmd_addr();
    
    static uint32_t last_tick=0;
    static uint32_t cur_tick=0;

    cur_tick = hal_get_cur_sys_time();

    if(cur_tick >= last_tick)
    {
        if((SYS_TO_US(cur_tick - last_tick) / 1000) > 200) //msg timeout 200ms
        {
            phy_cmd->msg_recv_count = 0;
        }
    }
    else
    {
        if((SYS_TO_US(0xffffffffUL - last_tick + cur_tick) / 1000) > 200) //msg timeout 20ms
        {
            phy_cmd->msg_recv_count = 0;
        }
    }
    last_tick = cur_tick;

    phy_cmd->msg_rx_buffer[phy_cmd->msg_recv_count++] = ch;
    if(phy_cmd->msg_recv_count > PHY_CMD_HEADER_SIZE)//recv msg
    {
        if((phy_cmd->msg_recv_count == phy_cmd->msg_rx_buffer[PHY_CMD_LEN_INDEX] + 4) && (0x2e == phy_cmd->msg_rx_buffer[0]))
        {
            phy_cmd->msg_recv_flag = 1;
        }
    }
    return 0;
}

static void user_uart_irq_callback( ZN_UartType *UARTx, uint32_t wpara, uint32_t lpara)
{
    uint8_t intc_state; 
	uint8_t data;
	intc_state = hal_uart_get_int_state(0);

	/* Received data available.
     * - Receiver data available (non-FIFO mode or FIFOs disabled) 
	 * - or RCVR FIFO trigger level reached (FIFO mode and FIFOs enabled)
	*/
	if (hal_uart_rx_buff_is_not_empty(0)) 
	{
		data = hal_uart_get_rx_data(0);
		
		OTA_Uart_Recv_Deal(data);
		if(ota_start_flag)return;
		
		user_recv_msg(data);
	}
}




void final_msg_get_ts(const uint8_t *ts_field, uint64_t *ts)
{
    int32_t i;
    *ts = 0;
    for (i = 0; i < 5; i++)
    {
        *ts += (uint64_t)ts_field[i] << (i * 8);
    }
}

void final_msg_set_ts(uint8_t *ts_field, uint64_t ts)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        ts_field[i] = (uint8_t) ts;
        ts >>= 8;
    }
}

filter_control_t g_can_filter_tab[MAX_CAN_FILTER_NUM] = 
{
    { 0, 1, 0x00000123, 0x00000000},   //receive ID 123,code = 0x123,mask = 0x00000000
    { 1, 1, 0x00000400, 0x000000FF},   //receive ID 0x400-0x4FF,other ID mask,code = 0x400,mask = 0x000000FF; 
    { 2, 1, 0x00000010, 0x00000000},   //receive ID 0x10
    { 3, 1, 0x00000020, 0x00000000},   
    { 4, 1, 0x00000030, 0x00000000},
    { 5, 1, 0x00000040, 0x00000000},
    { 6, 1, 0x00000050, 0x00000000},
    { 7, 1, 0x000007FF, 0x00000000},
};
static void can_irq_callback(void *device, uint32_t event, uint32_t err)
{
    if (event & CAN_EVENT_RECVMSG)
    {
        if(hal_can_is_msg_in_rxbuff())
        {
            hal_can_msg_read(&g_can_recv_msg);
            g_can_rx_flag = 1;
        }
    }
}
void user_init(void)
{
    hal_uart_t uart_cfg = {0};
    
    uart_cfg.is_block_mode = 0;
    uart_cfg.is_tx_int_en = 0;
    uart_cfg.is_rx_int_en = 1;
    uart_cfg.baurdrate = B115200;
    uart_cfg.func = (DeviceCallback_Type)&user_uart_irq_callback;
    
    hal_uart_init(&uart_cfg);
    
    hal_can_t can_cfg = {0};
    can_cfg.baudrate_config.presc = 3;
    can_cfg.baudrate_config.seg_1 = 14;
    can_cfg.baudrate_config.seg_2 = 3;
    can_cfg.baudrate_config.sjw = 3;
    
    can_cfg.datarate_config.presc = 1;
    can_cfg.datarate_config.seg_1 = 14;
    can_cfg.datarate_config.seg_2 = 3;
    can_cfg.datarate_config.sjw = 3;
    
    can_cfg.config.clock_src = 0;    //select pll clock
    can_cfg.config.clock_div = 0;    //clock div 2+1 124.8/3 = 41.6 Mhz
    can_cfg.config.interrupt_en = 1;
    can_cfg.config.tpss = 1;
    can_cfg.config.tsss = 1;
    can_cfg.config.can_mode = NORMAL_MODE;
    can_cfg.config.auto_reset = 1;
    can_cfg.config.filter_en = 0;
    //can_cfg.config.filter_list = g_can_filter_tab;
    can_cfg.config.fd_mode_en = 1;
    can_cfg.config.fd_iso_en = 1;
    can_cfg.config.tdc_en = 1;
    can_cfg.config.ssp_offset = can_cfg.datarate_config.seg_1 + 2;
    can_cfg.config.time_en = 1;
    can_cfg.config.time_pos = 1;
    can_cfg.config.func = (DeviceCallback_Type)&can_irq_callback;
    
    hal_can_init(&can_cfg);
}

void sts_init(void)
{
    uint32_t sts_iv[4]  = {0};
    uint32_t sts_key[4] = {0};
    uint8_t  index      = 0;

    for(index = 0; index < 4; index++)
    {
        sts_iv[index] = 0x11223344 + index;
    }

    zn_sts_iv_set(sts_iv);
    zn_sts_key_set(sts_key);
    zn_sts_load_cfg();
}

void uwb_gpio_debug_init(void)
{
    hal_gpio_set_tx_en_mode(GPIO_PIN13);
    hal_gpio_set_rx_en_mode(GPIO_PIN2);
    hal_gpio_set_output_default_config(GPIO_PIN12);
}

void range_init(void)
{  
    hal_uwb_phy_config_t*         uwb_phy_config   = &uwb_instance.phy_config;
    hal_uwb_interrupt_callback_t* uwb_irq_callback = &uwb_instance.interrupt_callback;
 
    hal_uwb_config_init(&uwb_instance);
    sts_init();
    uwb_gpio_debug_init();
}
uint32_t _change_32_to_8(uint32_t *data_in, uint8_t *data_out, uint32_t len)
{
    uint32_t idx = 0;
    uint32_t jdx = 0;

    for(idx = 0; idx < len; idx++)
    {
        jdx = idx * 4;
        data_out[jdx++] = (uint8_t)(data_in[idx] & 0xff);
        data_out[jdx++] = (uint8_t)((data_in[idx] >> 8) & 0xff);
        data_out[jdx++] = (uint8_t)((data_in[idx] >> 16) & 0xff);
        data_out[jdx++] = (uint8_t)((data_in[idx] >> 24) & 0xff);
    }

    return jdx;
}
void range_loop(void)
{
    memset(can_cmd_buf, 0, 64);
    phy_cmd_t* phy_cmd = get_phy_cmd_addr();    
    if(g_can_rx_flag == 1)
    {      
        g_can_rx_flag = 0;
        if(g_can_recv_msg.can_id == CAN_UPGRADE_ID)
        {
            g_packet_size = 32;
            _change_32_to_8(g_can_recv_msg.data,can_cmd_buf,16);
            OTA_Update_to_APP2(can_cmd_buf[3] + 4, can_cmd_buf);
        }    
    }
	if(ota_uart.pack_flag)
	{
        g_packet_size = 256;
		OTA_Update_to_APP2(ota_uart.len, ota_uart.buf);
		ota_uart.pack_flag = 0;
		ota_uart.len = 0;
	}
	if(ota_start_flag)
	{
		OTA_Loop();
        return;
	}
	
    phy_test_loop();
    if(phy_cmd->phy_debug_flag == WORK_MODE_PHY_DEBUG)
    {
        return;
    }
}

