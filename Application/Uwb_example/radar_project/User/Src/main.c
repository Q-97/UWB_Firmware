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
#include "gconfig.h"
#include "cm_backtrace.h"
#include "user_app.h"
#include "tuwb.h"
#include "per_init.h"

const char *filename = "radar";
const char *hardware_ver = "0626";
const char *software_ver = "0227";
extern uint8_t g_radar_done_flag;

int main(void)
{
    hal_soc_init();
   
    uwbs_init();  //for manufacture test mode init

    peripheral_init(); 
    
    LOG_INFO("radar initial done");

    while (1)
    {
        user_loop();
        
        hal_uwb_check_and_restore_pll_clock(uwb_instance.phy_config.channel_num);
    }

    return 0;
}