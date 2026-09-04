
/******************************************************************************
 *  File: zn_timer_reg.h
 *
 *  Description: this file contains the functions support timer operations.
 *
 *  Copyright (C) : 2022 Hangzhou ultraception.com.
 *
 *  Author: wjy
 *  Date:   April 17 2023
 *
 *****************************************************************************/

#ifndef __ZN_TIMER_REG_H__
#define __ZN_TIMER_REG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_soc.h"


/*
 * define number of the timer
 */
#define TIMER_NUM   (3)

typedef struct 
{
    __IO  uint32_t  TimxLoadCount;     /* Timer Value to be loaded into Timer */
    __I   uint32_t  TimxCurrentValue;  /* Timer Current Value of Timer */
    __IO  uint32_t  TimxControl;       /* Timer Control Register for Timer */
    __I   uint32_t  TimxEOI;           /* Timer Clears the interrupt from Timer */
    __I   uint32_t  TimxIntStatus;     /* Timer Contains the interrupt status for Timer*/
} ZN_Timer;


/*Allocate the registers according to the 8 timers. Actually only 3 timers are supported*/
typedef struct 
{
    ZN_Timer TimeChan[8];   
    __I  uint32_t TimersIntStatus;    /*Timers Interrupt Status Register.Contains the interrupt status of all timers in the component.*/
    __I  uint32_t TimersEOI;         /*Timer Clears the interrupt from All Timers.*/
    __I  uint32_t TimersRawIntStatus;/*Timer Contains the interrupt status for All Timers*/
    __I  uint32_t TimersCompVersion; /*Current revision number of the DW_apb_timers component*/
    __IO uint32_t TimerNLoadCount2[8]; /*Value to be loaded into TimerN when timer_N_toggle output changes from 0 to 1. This value determines the width of the HIGH period of the timer_N_toggle output.*/
} ZN_TimerType;




/*Peripheral TIMER base pointer*/
#define TIMER                           ((ZN_TimerType        *) TIMER_BASE_ADDR)


/*
 *  define the bits for TimxControl
 */
#define TIMER_CONTROL_ENABLE_POS          (0)     
#define TIMER_CONTROL_ENABLE_MSK          (1UL << TIMER_CONTROL_ENABLE_POS)
#define TIMER_CONTROL_USER_MODE_POS       (1)
#define TIMER_CONTROL_USER_MODE_MSK       (1UL << TIMER_CONTROL_USER_MODE_POS)
#define TIMER_CONTROL_INTMASK_POS         (2)
#define TIMER_CONTROL_INTMASK_MSK         (1UL << TIMER_CONTROL_INTMASK_POS)
#define TIMER_CONTROL_PWM_POS             (3)
#define TIMER_CONTROL_PWM_MSK             (1UL << TIMER_CONTROL_PWM_POS)


/**
* timer_enable
*
* @param[in] id: TIMER ID(0~2)
*
* @return none
*
* @brief enable TIMER channel timer
*/
__STATIC_INLINE void timer_enable(uint8_t id)
{
    TIMER->TimeChan[id].TimxControl |= TIMER_CONTROL_ENABLE_MSK;
}


/**
* timer_disable
*
* @param[in] id: TIMER ID(0~2)
*
* @return none
*
* @brief disable TIMER channel timer
*/
__STATIC_INLINE void timer_disable(uint8_t id)
{
    TIMER->TimeChan[id].TimxControl &= ~TIMER_CONTROL_ENABLE_MSK;
}




/**
* timer_enable_int
*
* @param[in] id: TIMER ID(0~2)
*
* @return none
*
* @brief  enable TIMER channel timer interrupt
*/
__STATIC_INLINE void timer_enable_int(uint8_t id)
{  
    TIMER->TimeChan[id].TimxControl &= ~TIMER_CONTROL_INTMASK_MSK;
}


/**
* timer_disable_int
*
* @param[in] id: TIMER ID(0~2)
*
* @return none
*
* @brief disable TIMER channel timer interrupt
*/
__STATIC_INLINE void timer_disable_int(uint8_t id)

{
    TIMER->TimeChan[id].TimxControl |= TIMER_CONTROL_INTMASK_MSK;
}

/**
* timer_enable_usermode
*
* @param[in] id: TIMER ID(0~2)
*
* @return none
*
* @brief  enable TIMER channel user mode
*/
__STATIC_INLINE void timer_enable_usermode(uint8_t id)
{
    TIMER->TimeChan[id].TimxControl |= TIMER_CONTROL_USER_MODE_MSK;
}


/**
* timer_disable_usermode
*
* @param[in] id: TIMER ID(0~2)
*
* @return none
*
* @brief disable TIMER channel user mode
*/
__STATIC_INLINE void timer_disable_usermode(uint8_t id)

{
    TIMER->TimeChan[id].TimxControl &= ~TIMER_CONTROL_USER_MODE_MSK;
}



/**
* timer_enable_pwm
*
* @param[in] id: TIMER ID(0~2)
*
* @return none
*
* @brief  enable TIMER channel PWM
*/
__STATIC_INLINE void timer_enable_pwm(uint8_t id)
{
    TIMER->TimeChan[id].TimxControl |= TIMER_CONTROL_PWM_MSK;
}


/**
* timer_disable_pwm
*
* @param[in] id: TIMER ID(0~2)
*
* @return none
*
* @brief disable TIMER channel PWM
*/
__STATIC_INLINE void timer_disable_pwm(uint8_t id)

{
    TIMER->TimeChan[id].TimxControl &= ~TIMER_CONTROL_PWM_MSK;
}

#ifdef __cplusplus
}
#endif

#endif



