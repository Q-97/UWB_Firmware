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
#include "uart_test.h"


int main(void)
{
    hal_soc_init();
    
    user_init();
    LOG_INFO("initial done");

    LOG_INFO("uart test start, output what input\r\n");
    while (1)
    {
        #ifdef POLL_REQUEST_TEST
        user_test();  
        #endif
    }

    return 0;
}