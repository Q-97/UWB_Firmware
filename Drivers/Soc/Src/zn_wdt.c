/*****************************************************************************
 *  File: zn_wdt.c
 *
 *  Descirption: this file contains the functions support Watchdog Timer operations.
 *
 *  Copyright (C) : 2023 ultraception.com
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2023-4-24
 *
 *****************************************************************************/

#include "zn_wdt.h"


WDT_EventCallback s_wdtCallback = NULL;

/**
 * wdt_init
 *
 * @param[in]  config: Pointer to a WDT_ConfigType structure containing configuration details for the Watchdog Timer
 * @return none
 *
 * @brief This function initializes the Watchdog Timer with the given configuration.
 */
void wdt_init(WDT_ConfigType * config)
{
    /* wdt reset/interrupt after (2^(16+wdtTimeout)/fre_wdt_clk)s, wdtTimeout is 0-15*/
    WDT->WDT_TORR = config->wdtTimeout & 0xF; 
    
    /*restart the WDT counter*/
    WDT->WDT_CRR = COUNTER_RST_CMD;
    if (config->wdtEn)
    {
        WDT->WDT_CR |= CK_WDT_CR_ENABLE_MSK;
    }
    
    if (config->wdtRmode)
    {
        WDT->WDT_CR |= CK_WDT_CR_RMOD_MSK;
        NVIC_EnableIRQ(WDT_IRQn);
    }
    else
    {
        WDT->WDT_CR &= ~CK_WDT_CR_RMOD_MSK;
        NVIC_DisableIRQ(WDT_IRQn);
    }
    
}
/**
 * wdt_deinit
 *
 * @param none
 * @return none
 *
 * @brief This function deinitializes the Watchdog Timer.
 */
void wdt_deinit(void)
{    
    wdt_feed();
    WDT->WDT_CR = 0;    
    NVIC_DisableIRQ(WDT_IRQn);
    
}

/**
 * wdt_get_intc_flag
 *
 * @param none
 * @return uint32_t: The interrupt flag status of the Watchdog Timer
 *
 * @brief This function returns the interrupt flag status of the Watchdog Timer.
 */
uint32_t  wdt_get_intc_flag(void)
{
    uint32_t flag;
    flag = WDT->WDT_STAT;
    return flag;
}

/**
 * wdt_get_curval
 *
 * @param none
 * @return uint32_t: The current value of the Watchdog Timer's internal counter
 *
 * @brief This function returns the current value of the Watchdog Timer's internal counter. 
 */
uint32_t wdt_get_curval(void)
{
    uint32_t curVal;
    /* This register, when read, is the current value of the internal counter.*/
    curVal = WDT->WDT_CCVR;
    return curVal ;
}

/**
 * wdt_set_callback
 *
 * @param[in] callback: Pointer to a function of type WDT_EventCallback that will be called when a Watchdog Timer interrupt occurs
 * @return none
 *
 * @brief This function sets a callback function to be called when a Watchdog Timer interrupt occurs. 
 */
void wdt_set_callback(WDT_EventCallback callback)
{
    s_wdtCallback = callback;
}


/**
* WDT_IRQHandler
*
* @brief      WDT Interrupt Handler
*/
void WDT_IRQHandler(void)
{
    if (s_wdtCallback)
    {
        s_wdtCallback();
    }
   
}
