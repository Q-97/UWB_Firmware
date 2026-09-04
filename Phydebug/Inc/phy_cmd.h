
/******************************************************************************
 *  File: phy_cmd.h
 *
 *  Description: this file contains the functions support phy test commonders.
 *
 *  Copyright (C) : 2022 Hangzhou ultraception.com.
 *
 *  Author: sxg
 *  Date:   May 13 2025
 *
 *****************************************************************************/

#ifndef __PHY_CMD_H__
#define __PHY_CMD_H__

#include "hal_uwb.h"
#include "phy_test.h"

#define MAX_FRAME_LEN    1024
#define MAX_TEST_NUM     1000

#define WORK_MODE_NORMAL       0
#define WORK_MODE_PHY_DEBUG    1

#define PHY_MAX_BUFFER_SIZE    255
#define PHY_CMD_HEADER_SIZE    3
#define PHY_CMD_LEN_INDEX      3

#define PHY_TRANSFER_SIGNLE    2
#define PHY_TRANSFER_LOOP      1
#define PHY_TRANSFER_STOP      0

typedef void (*phy_test_msg_handler_t)(uint8_t *msg_payload, uint8_t msg_len);

typedef enum
{
    MSG_TYPE_NULL = 0,
    MSG_TYPE_DEBUG_SWITCH,
    MSG_TYPE_REGISTER_OPERATION,
    MSG_TYPE_TRANSFER_OPERATION,
    MSG_TYPE_USR_DEFINED_OPERATION,
    MSG_TYPE_AON_REGISTER_OPERATION,
    MSG_TYPE_FULL_REGISTER_OPERATION,
    MSG_TYPE_MAX
}phy_msg_type_e;

typedef enum
{
    USER_MSG_TYPE_NULL = 0,
    USER_MSG_TYPE_TO_IDLE_STATE,
    USER_MSG_TYPE_AUTO_SLEEP,
    USER_MSG_TYPE_DEEP_SLEEP,
    USER_MSG_TYPE_CONTINUOUS_PULSE_SWITCH,
    USER_MSG_TYPE_SINE_WAVE_SWITCH,
    USER_MSG_TYPE_READ_ADC_MEM,
    USER_MSG_TYPE_READ_SFD_CIR_MEM_SWITCH,
    USER_MSG_TYPE_READ_STS_CIR_MEM_SWITCH,
    USER_MSG_TYPE_PSDU_LENGTH_SET,
    USER_MSG_TYPE_CALIB,
    USER_MSG_TYPE_VGA_RX0_ONETIME_CALC,
    USER_MSG_TYPE_VGA_RX1_ONETIME_CALC,
    USER_MSG_TYPE_VGA_RX0_AUTO_CALC,
    USER_MSG_TYPE_VGA_RX1_AUTO_CALC,
    USER_MSG_TYPE_AGC_MEM_SWITCH,
    USER_MSG_TYPE_AGC_MEM_READ,
    USER_MSG_TYPE_VGA_LOG_LEVEL_SET,
    USER_MSG_TYPE_SOFTWARE_RESET,
    USER_MSG_TYPE_PSDU_PRINT_SWITCH,
    USER_MSG_TYPE_QUICK_LOOP_SWITCH,
    USER_MSG_TYPE_RX_TIMEOUT_SET,
    USER_MSG_TYPE_TX_DELAY_SET,
    USER_MSG_TYPE_POWER_SAVE_SWITCH,
    USER_MSG_TYPE_RADAR_TIMER_SWITCH,
    USER_MSG_TYPE_MAX
}msg_type_user_defined_e;

typedef struct phy_cmd
{
    uint8_t  phy_debug_flag;
    uint8_t  msg_recv_flag;
    uint32_t msg_recv_count;
    uint8_t  msg_rx_buffer[PHY_MAX_BUFFER_SIZE];
    uint8_t  quick_loop_en;
    uint8_t  tx_flag;
    uint8_t  rx_flag;
    uint32_t packet_count;
    uint32_t ok_count;
    uint8_t  sfd_cir_mem_en;
    uint8_t  sts_cir_mem_en;
    uint8_t  agc_mem_en;
    uint8_t  psdu_print_en;
    uint8_t  interrupt_en;
    uint16_t psdu_len;
    uint16_t rx_timeout_ms;
    uint16_t tx_delay_ms;
    zn_local_data_t     loacal_data_back;
}phy_cmd_t;

typedef struct user_msg_state_table
{
    msg_type_user_defined_e    user_msg_type;
    phy_test_msg_handler_t     user_msg_handler;
}user_msg_state_table_t;

typedef struct phy_msg_state_table
{
    phy_msg_type_e            phy_msg_type;
    phy_test_msg_handler_t    phy_test_msg_handler;
}phy_msg_state_table_t;


phy_cmd_t* get_phy_cmd_addr(void);
void phy_cmd_recv_loop(void);














#endif