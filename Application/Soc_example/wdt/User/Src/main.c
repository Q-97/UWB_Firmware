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
#include "wdt_test.h"




int main(void)
{
    hal_soc_init();
    
    user_init();
    LOG_INFO("initial done");

    LOG_INFO("wdt test start\r\n");
    while (1)
    {
        user_test();  
    }

    return 0;
}