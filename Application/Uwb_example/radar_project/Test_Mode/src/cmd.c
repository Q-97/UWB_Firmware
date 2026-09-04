#include "cmd.h"

#include <string.h>
#include "gconfig.h"
#include "per_init.h"
#include "uci.h"
#include "msg_uci.h"

static void byte_convert(uint32_t *data, uint8_t len)
{
    uint32_t convert_data = 0;
    uint8_t  idx          = 0;

    for(idx = 0; idx < len; idx++)
    {
        convert_data = ((data[idx] & 0xff) << 24) | ((data[idx] & 0xff00) << 8) | ((data[idx] & 0xff0000) >> 8) | ((data[idx] & 0xff000000) >> 24);
        data[idx] = convert_data;
    }
}

void uwbs_parse_uci_cmd(uint32_t cmd_len, uint8_t *cmd_buf)
{
    uci_msg_t *uci_msg = NULL;
    int32_t   ret      = 0;

    if((0 == cmd_len)
        || (cmd_len >= UCI_MSG_RCV_BUFF_SIZE)
        || (!cmd_buf))
    {
        LOG_ERROR("Uwbs recv cmd len error!, cmd_len =%d", cmd_len);
        return;
    }

    uci_msg = (uci_msg_t *)cmd_buf;
    ret = uci_msg_send(uci_msg);

    if(ret <= 0)
    {
        LOG_ERROR("Uwbs send msg failed!");
        return;
    }

    return;
}

void uci_cmd_recv_loop(void)
{
    uart_update_flag();
    if(g_uart_rx_flag == 1)
    {
        if(g_uart_rcv_counter > 3 && g_uart_rcv_counter >= (g_uart_rx_buffer[3]+4))
        uwbs_parse_uci_cmd(g_uart_rcv_counter, (void *)g_uart_rx_buffer);
        g_uart_rcv_counter = 0;
        g_uart_rx_flag = 0;
    }
//    if(g_can_rx_msg_flag)
//    {
//        if(g_can_rx_message.can_id == RECIEVE_UCI_TEST_MODE_CAN_ID)
//        {
//            uwbs_parse_uci_cmd(CAN_MAX_LEN, (void *)g_can_rx_message.data);
//        }
//        else  if(g_can_rx_message.can_id == RECV_UPFRADE_CAN_ID)
//        {          
//            recv_can_msg_proc_loop();        
//        }
//        g_can_rx_msg_flag = 0;
//    }
//    if(g_spi_rx_msg_flag)
//    {
//        byte_convert(g_spi_rx_data_buff, SPI_RX_BUFF_LENGTH);
//        uwbs_parse_uci_cmd(SPI_RX_BUFF_LENGTH, (void *)g_spi_rx_data_buff);
//        g_spi_rx_msg_flag = 0;
//        g_spi_rx_index = 0;
//    }
}
