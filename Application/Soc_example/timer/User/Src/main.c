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
#include "timer_test.h"




int main(void)
{
    hal_soc_init();
    
    user_init();
    LOG_INFO("initial done");

    LOG_INFO("timer test start, use LA to check GPIO_PIN0\r\n");
    
    user_test(); 
    
    while (1)
    {
        ;
    }

    return 0;
}