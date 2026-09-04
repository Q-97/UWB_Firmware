/*****************************************************************************
 *  File: zn_soc_hal.c
 *
 * Descirption: this file contains the functions support systick operations.
 *
 *  Copyright (C) : 2023 ultraception.com
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2023-6-12
 *
 *****************************************************************************/

#include "zn_sys_tick.h"
#include "zn_gpio.h"

volatile uint32_t g_sysTick;

/**
* sys_tick_init
*
* @param[in]  tick_cycle: The tick cycle in milliseconds
* @return 0
*
* @brief Initializes the system tick timer
*/
uint8_t sys_tick_init(SYS_TickCycle tick_cycle)
{
    uint32_t val      = sys_ctrl_read(SOC_CLK_CFG);
    uint8_t  clk_sel  = val & 0x00000003;
    uint8_t  clk_div  = (val & 0x000000f0) >> 4;
    uint32_t clk_freq = 0;


    if((val & 0x00000100) == 0x00000100)
    {
        clk_freq = 120000000 / (clk_div + 1);
    }
    else
    {
        clk_freq = 124800000 / (clk_div + 1);
    }

    SysTick_Config(clk_freq / tick_cycle); 
    /* Return function status */
    return 0;
}

/**
* sys_tick_inc
*
* @param[in]  none
* @return none
*
* @brief Increments the system tick counter
*/
void sys_tick_inc(void)
{
    g_sysTick++;
}

/**
* sys_tick_get
*
* @param[in]  none
* @return The current value of the system tick counter
*
* @brief Gets the current value of the system tick counter
*/
uint32_t sys_tick_get(void)
{
    return g_sysTick;
}


/**
* SysTick_Handler
*
* @param[in]  none
* @return none
*
* @brief System tick interrupt handler
*/
void sys_tick_delay(uint32_t delayMs)
{
    uint32_t tickstart = sys_tick_get();
    uint32_t wait = delayMs;

    /* Add a freq to guarantee minimum wait */
    if (wait < HAL_MAX_DELAY)
    {
        wait++;
    }

    while(sys_tick_get() < tickstart+wait)
    {
        
    }
}


/**
* SysTick_Handler
*
* @param[in]  none
* @return none
*
* @brief System tick interrupt handler
*/
void SysTick_Handler(void)
{

    sys_tick_inc();
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
