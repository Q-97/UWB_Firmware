/*****************************************************************************
* File: phy_cmd.c
*
* Descirption: this file contains the functions support phy test cmmonders.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/

#include "phy_cmd.h"

static phy_cmd_t phy_test_cmd = {0};
static uint8_t phy_cmd_header[PHY_CMD_HEADER_SIZE] = {0x2e, 0x20, 0x00};

phy_msg_state_table_t phy_msg_state_table[MSG_TYPE_MAX] =
{
    {MSG_TYPE_DEBUG_SWITCH,          phy_test_debug_switch},
    {MSG_TYPE_REGISTER_OPERATION,    phy_test_register_operation},
    {MSG_TYPE_TRANSFER_OPERATION,    phy_test_transfer_operation},
    {MSG_TYPE_USR_DEFINED_OPERATION, phy_test_user_defined_operation},
    {MSG_TYPE_AON_REGISTER_OPERATION, phy_test_aon_register_operation},
    {MSG_TYPE_FULL_REGISTER_OPERATION, phy_test_full_register_operation}
};


static void phy_test_cmd_handler(uint8_t *cmd, uint8_t len)
{
    phy_msg_type_e msg_type = MSG_TYPE_NULL;
    uint8_t        msg_len  = 0;
    uint8_t *      buffer   = NULL;
    
    if((phy_test_cmd.phy_debug_flag != WORK_MODE_PHY_DEBUG) && (0x03 != cmd[1]))
    {
        return;
    }
    
    if(len > PHY_MAX_BUFFER_SIZE)
    {
        LOG_ERROR("msg length error");
        return;
    }
    
    switch(cmd[1])
    {
        case 0x00 : 
        case 0x01 :
        {
            if(0xff == cmd[2])
            {
                msg_type = MSG_TYPE_TRANSFER_OPERATION;
                buffer = &cmd[3];
                msg_len = 2;
            }
            else
            {
                msg_type = MSG_TYPE_REGISTER_OPERATION;
                buffer = &cmd[1];
                msg_len = 7;
            }
            break;
        }
        case 0x02 :
        {
            msg_type = MSG_TYPE_USR_DEFINED_OPERATION;
            buffer = &cmd[2];
            msg_len = 3;
            break;
        }
        case 0x03:
        {
            msg_type = MSG_TYPE_DEBUG_SWITCH;
            buffer = &cmd[2];
            msg_len = 1;
            break;
        }
        case 0x04:
        {
            msg_type = MSG_TYPE_AON_REGISTER_OPERATION;
            buffer = &cmd[2];
            msg_len = 6;
            break;
        }
        case 0x05:
        {
            msg_type = MSG_TYPE_FULL_REGISTER_OPERATION;
            buffer = &cmd[2];
            msg_len = 0x0b;
            break;
        }
        default: msg_type = MSG_TYPE_NULL; break;
    }
    
    for(uint8_t index = 0; index < MSG_TYPE_MAX; index++)
    {
        if((msg_type != MSG_TYPE_NULL) && (msg_type == phy_msg_state_table[index].phy_msg_type))
        {
            phy_msg_state_table[index].phy_test_msg_handler(buffer, msg_len);
            break;
        }
    }
}

static void parse_phy_cmd(uint32_t count, uint8_t* buffer)
{
    uint8_t cmd_len = 0;
    
    if(0 == memcmp(buffer, phy_cmd_header, PHY_CMD_HEADER_SIZE))
    {
        cmd_len = buffer[PHY_CMD_LEN_INDEX];
        
        if(cmd_len > 0)
        {
            phy_test_cmd_handler(&buffer[PHY_CMD_HEADER_SIZE + 1], cmd_len);
        }
        else
        {
            LOG_ERROR("cmd_len is zero");
        }
    } 
}


phy_cmd_t* get_phy_cmd_addr(void)
{
    return &phy_test_cmd;
}



void phy_cmd_recv_loop(void)
{
    if(phy_test_cmd.msg_recv_flag)
    {
        parse_phy_cmd(phy_test_cmd.msg_recv_count, phy_test_cmd.msg_rx_buffer);
        phy_test_cmd.msg_recv_count = 0;
        phy_test_cmd.msg_recv_flag = 0;
    }
}