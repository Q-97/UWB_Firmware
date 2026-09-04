
/*****************************************************************************
 *  File: zn_wdt_reg.h
 *
 *  Descirption: contains the functions support  Watchdog Timer.
 *
 *  Copyright (C) : 2023 ultraception.com.
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2023-4-24
 *
 *****************************************************************************/

#ifndef __ZN_WDT_REG_H__
#define __ZN_WDT_REG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_soc.h"



typedef struct 
{
    __IO uint32_t  WDT_CR;               /* WDT  Control Register */
    __IO uint32_t  WDT_TORR;             /* WDT Timeout Range Register, 3:0 Timeout period : 2^(16 + i)*/
    __I  uint32_t  WDT_CCVR;             /* WDT Current Counter Value Register */
    __O  uint32_t  WDT_CRR;              /* WDT Counter Restart Register */
    __I  uint32_t  WDT_STAT;             /* WDT Interrupt Status Register.bit0, 0-Interrupt is inactive, 1 - Interrupt is active regardless of polarity..*/
    __I  uint32_t  WDT_EOI;              /* WDT Interrupt Clear Register */
    __IO uint32_t  Rev[51];              /* 0x18 - 0xe0 */
    __I  uint32_t  WDT_COMP_PARAMS_5;    /* Component Parameters Register 5 */
    __I  uint32_t  WDT_COMP_PARAMS_4;    /* Component Parameters Register 4 */
    __I  uint32_t  WDT_COMP_PARAMS_3;    /* Component Parameters Register 3 */
    __I  uint32_t  WDT_COMP_PARAMS_2;    /* Component Parameters Register 2 */
    __I  uint32_t  WDT_COMP_PARAMS_1;    /* Component Parameters Register 1 */
    __I  uint32_t  WDT_COMP_VERSION;     /* Component Version Register */
    __I  uint32_t  WDT_COMP_TYPE;        /* Component Type Register */
} ZN_WdtType;


#define WDT                           ((ZN_WdtType        *) WDT_BASE_ADDR)
/*
 *  define the bits for WDT_CR(Control Register)
 */
/*WDT enable*/
#define CK_WDT_CR_ENABLE_POS        (0)
#define CK_WDT_CR_ENABLE_MSK        (1UL << 0) 

/*Response mode.
0 = Generate a system reset.
1 = First generate an interrupt and if it is not cleared by the time a second timeout 
occurs then generate a system reset.*/
#define CK_WDT_CR_RMOD_POS          (1)
#define CK_WDT_CR_RMOD_MSK          (1UL << 1) 





#define COUNTER_RST_CMD         0x76

#define WDT_SYSTEM_RST       0
#define WDT_INTC_RST         1



/**
 * wdt_feed
 *
 * @param none
 * @return none
 *
 * @brief This function restarts the Watchdog Timer counter.
 * 
 */
__STATIC_INLINE void wdt_feed(void)
{
    /*
    This register is used to restart the WDT counter. 
    As a safety feature to prevent accidental restarts, the value 0x76 must be written. 
    A restart also clears the WDT interrupt.
    */
    WDT->WDT_CRR = COUNTER_RST_CMD;
}

/**
 * wdt_clr_intc_flag
 *
 * @param none
 * @return none
 *
 * @brief This function clears the Watchdog Timer interrupt flag by writing to the WDT_EOI and WDT_STAT registers.
 */

__STATIC_INLINE void  wdt_clr_intc_flag(void)
{
    WDT->WDT_EOI;
}

/**
 * wdt_disable
 *
 * @param none
 * @return none
 *
 * @brief This function disables the Watchdog Timer by clearing the enable bit in the WDT_CR register. 
 */
__STATIC_INLINE void wdt_disable(void)
{
    /*To prevent a software bug from disabling the DW_apb_wdt, once this bit has been enabled, it can be cleared only by a system reset.*/
    WDT->WDT_CR &= ~CK_WDT_CR_ENABLE_MSK;
}

/**
 * wdt_enable
 *
 * @param none
 * @return none
 *
 * @brief This function enables the Watchdog Timer by setting the enable bit in the WDT_CR register. 
 */ 
__STATIC_INLINE void wdt_enable(void)
{
    WDT->WDT_CR |= CK_WDT_CR_ENABLE_MSK;
}

#ifdef __cplusplus
}
#endif

#endif

