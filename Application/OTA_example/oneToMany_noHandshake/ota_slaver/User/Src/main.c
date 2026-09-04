/*****************************************************************************
* File: main.c
* Descirption: this file contains the functions support rx test.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#include "hal_soc.h"
#include "range.h"


uint8_t g_soft_ver[4] = {0x20,0x26,0x06,0x01};
uint16_t g_packet_size = 32;//can packet is 32;uart is 256

int main(void)
{
    hal_soc_init();
    
    user_init();
    range_init();
    LOG_INFO("initial done");
    

    LOG_INFO("\r\n ota successed! g_soft_ver: 0x%x,0x%x,0x%x,0x%x\r\n", 
    g_soft_ver[0], g_soft_ver[1], g_soft_ver[2], g_soft_ver[3]);
    while (1)
    {
        range_loop();

        hal_uwb_check_and_restore_pll_clock(CHANNEL_9);
    }

    return 0;
}