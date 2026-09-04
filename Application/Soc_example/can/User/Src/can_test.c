/*****************************************************************************
* File: can_test.c
* Descirption: this file contains the functions support can test.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/

#include "can_test.h"
#include "hal_gpio.h"
#include "hal_delay.h"


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

uint8_t g_rx_msg_flag = 0;
hal_can_msg_info_t g_send_msg_Info = {0};
hal_can_msg_info_t g_recv_msg_info = {0};

static void can_irq_callback(void *device, uint32_t event, uint32_t err)
{
    if (event & CAN_EVENT_RECVMSG)
    {
        if(hal_can_is_msg_in_rxbuff())
        {
            hal_can_msg_read(&g_recv_msg_info);
            g_rx_msg_flag = TRUE;
        }
    }
}


static void can_test(void)
{
    uint32_t count = 0;
    uint8_t  idx   = 0;


    g_send_msg_Info.can_id = 0x100;
    g_send_msg_Info.dlc = 0x08;

    for (idx = 0; idx < g_send_msg_Info.dlc; idx++)
    {
        *((uint8_t *)g_send_msg_Info.data + idx) = idx;  // payload data
    }

    for (idx = 0; idx < 10; idx++)
    {
        hal_delay_ms(5);
        g_send_msg_Info.can_id = idx;
        printf("[TX] msgid=0x%0x\r\n",g_send_msg_Info.can_id);
        if(!can_is_transmit_busy(CAN0, TRANSMIT_SECONDARY))
        {
            hal_can_msg_send(&g_send_msg_Info, SECONDARY_SEND);
        }
    }

    g_recv_msg_info.can_id = 0;
    while(1)
    {
        if (g_rx_msg_flag)
        {
            g_rx_msg_flag = FALSE;
            printf("[RX] msgid=0x%0x, RTS[0]=0x%08x, RTS[1]=0x%08x\r\n",g_recv_msg_info.can_id,g_recv_msg_info.rts[0],g_recv_msg_info.rts[1]);
            for(idx = 0; idx < g_recv_msg_info.dlc; idx++)
            {
                printf("0x%02x ", *(((uint8_t *)g_recv_msg_info.data) + idx));
            }
            printf("\r\n");
            printf("\r\n[TX]LAST TTS[0]=0x%08x, TTS[1]=0x%08x\r\n",hal_can_get_tts0(), hal_can_get_tts1());	
            printf("\r\n");	
            //enable TTSEN	
            g_recv_msg_info.can_id |= (1<<31);			
            if(!hal_can_is_transmit_busy(SECONDARY_SEND))
            {
                if (SUCCESS == hal_can_msg_send(&g_recv_msg_info, SECONDARY_SEND))
                {
                    count++;
                }
                else
                {
                     hal_delay_ms(2);
                }
            }
            if ((g_recv_msg_info.can_id & MSG_INFO_ID_MASK) >= MSG_QUIT_ID)
            {
                break;
            }
        }
    }   
}


static void canfd_test(void)
{
    uint32_t count = 0;
    uint8_t  idx = 0;
    uint8_t  data_len = 0;
    
    g_send_msg_Info.dlc = 0x0f;
    
    for(idx = 0; idx < 64; idx++)
    {
        *((uint8_t *)g_send_msg_Info.data + idx) = idx;
    }
    g_send_msg_Info.can_id = 0xaa;
    g_send_msg_Info.fdf = 1;
    g_send_msg_Info.brs = 1;
    
    if(!hal_can_is_transmit_busy(PRIMARY_SEND))
    {
        hal_can_msg_send(&g_send_msg_Info, PRIMARY_SEND);
    }
    
    while(1)
    {
        if(g_rx_msg_flag)
        {
            g_rx_msg_flag = 0;
            
            printf("cnt=%d*****[RX] msgid=0x%0x,FDF=0x%x,BRS=0x%x,DLC=0x%0x\t,RTS[0]=0x%08x, RTS[1]=0x%08x\r\n",count,\
                    g_recv_msg_info.can_id,g_recv_msg_info.fdf,g_recv_msg_info.brs,g_recv_msg_info.dlc,g_recv_msg_info.rts[0],g_recv_msg_info.rts[1]);
            data_len = hal_can_fd_dlc_to_len(g_recv_msg_info.dlc);
            for(idx=0;idx < data_len; idx++)
            {
                printf("0x%02x ", *((uint8_t *)g_recv_msg_info.data + idx));
            }
            printf("\r\n");
            printf("\r\n[TX]LAST TTS[0]=0x%08x, TTS[1]=0x%08x\r\n",hal_can_get_tts0(), hal_can_get_tts1());	
            printf("\r\n");	
            
            g_recv_msg_info.can_id |= 1 << 31;
            
            if(! hal_can_is_transmit_busy(PRIMARY_SEND))
            {
                if(SUCCESS == hal_can_msg_send(&g_recv_msg_info, PRIMARY_SEND))
                {
                    count++;
                }
                else
                {
                    hal_delay_ms(2);
                }
            }
            
            if((g_recv_msg_info.can_id & MSG_INFO_ID_MASK) >= MSG_QUIT_ID)
            {
                break;
            }
        }
    }
}

void user_init(void)
{
    hal_uart_t uart_cfg = {0};
    
    uart_cfg.is_block_mode = 0;
    uart_cfg.is_tx_int_en = 0;
    uart_cfg.is_rx_int_en = 0;
    uart_cfg.baurdrate = B115200;
    hal_uart_init(&uart_cfg);
    
    hal_can_t can_cfg = {0};
    #if(CAN_TEST_MODE == CAN_TEST)
    can_cfg.baudrate_config.presc = 3;
    can_cfg.baudrate_config.seg_1 = 14;
    can_cfg.baudrate_config.seg_2 = 3;
    can_cfg.baudrate_config.sjw = 3;
    
    can_cfg.config.clock_src = 0;    //select 80M clock
    can_cfg.config.clock_div = 0;    
    can_cfg.config.interrupt_en = 1;
    can_cfg.config.tpss = 0;
    can_cfg.config.tsss = 0;
    can_cfg.config.can_mode = NORMAL_MODE;
    can_cfg.config.auto_reset = 1;
    can_cfg.config.filter_en = 0;
    can_cfg.config.filter_list = g_can_filter_tab;
    can_cfg.config.time_en = 1;
    can_cfg.config.time_pos = 1;
    can_cfg.config.func = (DeviceCallback_Type)&can_irq_callback;
    #elif(CAN_TEST_MODE == CANFD_TEST)
    can_cfg.baudrate_config.presc = 3;
    can_cfg.baudrate_config.seg_1 = 14;
    can_cfg.baudrate_config.seg_2 = 3;
    can_cfg.baudrate_config.sjw = 3;
    
    can_cfg.datarate_config.presc = 1;
    can_cfg.datarate_config.seg_1 = 14;
    can_cfg.datarate_config.seg_2 = 3;
    can_cfg.datarate_config.sjw = 3;
    
    can_cfg.config.clock_src = 0;    //select 80M clock
    can_cfg.config.clock_div = 0;
    can_cfg.config.interrupt_en = 1;
    can_cfg.config.tpss = 0;
    can_cfg.config.tsss = 0;
    can_cfg.config.can_mode = NORMAL_MODE;
    can_cfg.config.auto_reset = 1;
    can_cfg.config.filter_en = 0;
    can_cfg.config.filter_list = g_can_filter_tab;
    can_cfg.config.fd_mode_en = 1;
    can_cfg.config.ts_mode = 1;
    can_cfg.config.fd_iso_en = 1;
    can_cfg.config.tdc_en = 1;
    can_cfg.config.ssp_offset = can_cfg.datarate_config.seg_1 + 2;
    can_cfg.config.time_en = 1;
    can_cfg.config.time_pos = 1;
    can_cfg.config.func = (DeviceCallback_Type)&can_irq_callback;
    #endif
    
    hal_can_init(&can_cfg);
}


void user_test(void)
{
    #if(CAN_TEST_MODE == CAN_TEST)
    can_test();
    #elif(CAN_TEST_MODE == CANFD_TEST)
    canfd_test();
    #endif
    
}