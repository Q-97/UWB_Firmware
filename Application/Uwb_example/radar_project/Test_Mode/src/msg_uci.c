#include "msg_uci.h"

#include <string.h>
#include <stdint.h>

#include "uci.h"
#include "gconfig.h"
#include "per_init.h"


uint8_t g_host_to_uwbs_cmd_flag = 0;
uint8_t g_host_to_uwbs_cmd_len = 0;
uint8_t g_host_to_uwbs_cmd_buf[256] = {0};

uint8_t g_uwbs_to_host_rsp_flag = 0;
uint8_t g_uwbs_to_host_rsp_len = 0;
uint8_t g_uwbs_to_host_rsp_buf[256] = {0};

uint8_t g_uwbs_to_host_ntf_flag = 0;
uint8_t g_uwbs_to_host_ntf_len = 0;
uint8_t g_uwbs_to_host_ntf_buf[256] = {0};

int32_t host_send_cmd_to_uwbs(uint8_t *buf, uint8_t len)
{
    if(NULL == buf || 0 == len)
    {
        return -1;
    }

    if(0 == g_host_to_uwbs_cmd_flag)
    {
        memcpy(g_host_to_uwbs_cmd_buf, buf, len);
        g_host_to_uwbs_cmd_len = len;
        g_host_to_uwbs_cmd_flag = 1;
        return g_host_to_uwbs_cmd_len;
    }

    return 0;
}

int32_t uwbs_get_cmd_from_host(uint8_t *buf)
{
    if(NULL == buf)
    {
        return -1;
    }

    if(1 == g_host_to_uwbs_cmd_flag && g_host_to_uwbs_cmd_len > 0)
    {
        memcpy(buf, g_host_to_uwbs_cmd_buf, g_host_to_uwbs_cmd_len);
        g_host_to_uwbs_cmd_flag = 0;
        return g_host_to_uwbs_cmd_len;
    }

    return 0;
}

int32_t uwbs_send_to_host(uint8_t *buf, uint8_t len)
{
    if(NULL == buf || 0 == len)
    {
        return -1;
    }
    
    if(UCI_UART == g_uci_mode)
    {
        hal_uart_send_data(0, buf, len);
    }
    else if(UCI_CAN == g_uci_mode)
    {
        can_send_msg(buf, len, SEND_UCI_TEST_MODE_CAN_ID);
    }
    else if(UCI_SPI == g_uci_mode)
    {
        spi_send_msg(buf, len);
    }
    else
    {
    }

    return len;
}

int32_t host_get_rsp_from_uwbs(uint8_t *buf)
{
    if(NULL == buf)
    {
        return -1;
    }

    if(1 == g_uwbs_to_host_rsp_flag && g_uwbs_to_host_rsp_len > 0)
    {
        memcpy(buf, g_uwbs_to_host_rsp_buf, g_uwbs_to_host_rsp_len);
        g_uwbs_to_host_rsp_flag = 0;
        return g_uwbs_to_host_rsp_len;
    }

    return 0;
}


int32_t host_get_ntf_from_uwbs(uint8_t *buf)
{
    if(NULL == buf)
    {
        return -1;
    }

    if(1 == g_uwbs_to_host_ntf_flag && g_uwbs_to_host_ntf_len > 0)
    {
        memcpy(buf, g_uwbs_to_host_ntf_buf, g_uwbs_to_host_ntf_len);
        g_uwbs_to_host_ntf_flag = 0;
        return g_uwbs_to_host_ntf_len;
    }

    return 0;
}

int32_t uci_msg_send(uci_msg_t *uci_msg)
{
    int32_t ret          = 0;
    uint8_t msg_len      = 0;
    uint8_t msg_buf[255] = {0};

    memcpy(msg_buf, &uci_msg->msg_header, 4);
    memcpy(&msg_buf[4], &uci_msg->msg_data.core_dev_rst_cmd, uci_msg->msg_header.payload_len);

    msg_len = uci_msg->msg_header.payload_len + 4;
    
    switch(uci_msg->msg_header.msg_type)
    {
        case CTRL_MSG_CMD:
        {
            ret = host_send_cmd_to_uwbs(msg_buf, msg_len);
            break;
        }   
        case CTRL_MSG_RSP:
        {
            ret = uwbs_send_to_host(msg_buf, msg_len);
            break;
        }   
        case CTRL_MSG_NTF:
        {
            ret = uwbs_send_to_host(msg_buf, msg_len);
            break;
        }  
        default: 
        {
            ret = -1; 
            break;
        }
    }

    return ret;
}

int32_t uci_msg_get(uint8_t *buf, uint8_t msg_type)
{
    int32_t ret = 0;

    switch(msg_type)
    {
        case CTRL_MSG_CMD:
        {
            ret = uwbs_get_cmd_from_host(buf);
            break;
        }   
        case CTRL_MSG_RSP:
        {
            ret = host_get_rsp_from_uwbs(buf);
            break;
        }   
        case CTRL_MSG_NTF:
        {
            ret = host_get_ntf_from_uwbs(buf);
            break;
        }  
        default: 
        {
            ret = -1; 
            break;
        }
    }

    return ret;
}

void clear_msg_buf_flag(void)
{
    g_host_to_uwbs_cmd_flag = 0;
    g_uwbs_to_host_rsp_flag = 0;
    g_uwbs_to_host_ntf_flag = 0;
}

uint8_t uwbs_have_cmd_msg(void)
{
    if((1 == g_host_to_uwbs_cmd_flag) && (g_host_to_uwbs_cmd_len > 0))
    {
        return TRUE;
    }

    return FALSE;
}

uint8_t host_have_rsp_msg(void)
{
    if((1 == g_uwbs_to_host_rsp_flag) && (g_uwbs_to_host_rsp_len > 0))
    {
        return TRUE;
    }

    return FALSE;
}

uint8_t host_have_ntf_msg(void)
{
    if((1 == g_uwbs_to_host_ntf_flag) && (g_uwbs_to_host_ntf_len > 0))
    {
        return TRUE;
    }

    return FALSE;
}
