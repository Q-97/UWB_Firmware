/*****************************************************************************
 *  File: timer.c
 *
 * Descirption: This file contains the functions support timer operations.
 *
 *  Copyright (C) : 2022 ultraception.com
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2023-4-17
 *
 *****************************************************************************/

#include "zn_timer.h"

/**
* timer_init
*
* @param[in] timConfig: TIMER config type pointer
* @return 0:Success
*
* @brief TIMER module initialize
*/
int32_t timer_init(TIMER_ConfigType *timConfig)
{
    uint8_t timerId = timConfig->timerId;
    IRQn_Type timeIrq = TIM0_IRQn+timConfig->timerId;
    if (timerId >= TIMER_NUM)
    {
        return -1;            
    }
   

    if (timConfig->timerMode)
    {
        /*Timer mode for TimerN-user-defined count mode. Timer loads the current value of the TimerNLoadCount register.*/
        TIMER->TimeChan[timerId].TimxControl |= TIMER_CONTROL_USER_MODE_MSK;
        TIMER->TimeChan[timerId].TimxLoadCount = timConfig->loadCnt;
    }
    else
    {
         /*Timer mode for TimerN-free-running mode.Free-running mode . Timer loads the maximum value.*/
         TIMER->TimeChan[timerId].TimxControl &= ~TIMER_CONTROL_USER_MODE_MSK;
    }


    
    if (timConfig->pwmEn)
    {
        /*
         Width of timer_N_toggle HIGH period = (TimerNLoadCount2 + 1) * timer_N_clk clock period
         Width of timer_N_toggle LOW period = (TimerNLoadCount + 1) * timer_N_clk clock period
        */
        TIMER->TimeChan[timerId].TimxControl |= TIMER_CONTROL_PWM_MSK;
        TIMER->TimeChan[timerId].TimxLoadCount = timConfig->loadCnt;
        TIMER->TimerNLoadCount2[timerId] = timConfig->loadCnt2;
    }
    else
    {
        TIMER->TimeChan[timerId].TimxControl &= ~TIMER_CONTROL_PWM_MSK;
    }
    
    if (timConfig->interruptEn)
    {

        NVIC_EnableIRQ(timeIrq);
        timer_enable_int(timerId);
    }
    else
    {
        NVIC_DisableIRQ(timeIrq);
        timer_disable_int(timerId);
    }
    
    if (timConfig->timerEn)
    {
        TIMER->TimeChan[timerId].TimxControl  |= TIMER_CONTROL_ENABLE_MSK;
    }
    else
    {
        TIMER->TimeChan[timerId].TimxControl  &= ~TIMER_CONTROL_ENABLE_MSK;
    }
    
    return 0;
}

/**
* timer_set_loadval
*
* * @param[in] timerId: TIMER ID(0~2)
* @param[in] loadValue: timer init value
* @return none
*
* @brief Set timer init value
*/
void timer_set_loadval(uint8_t timerId, uint32_t loadValue)
{
     TIMER->TimeChan[timerId].TimxLoadCount = loadValue;
}


/**
* timer_set_loadval2
*
* @param[in] timerId: TIMER ID(0~2)
* @param[in] loadValue2: timer init value
* @return none
*
* @brief Set timer loadValue2. This value determines the width of the HIGH period of the timer_N_toggle output.
*/
void timer_set_loadval2(uint8_t timerId, uint32_t loadValue2)
{
     TIMER->TimeChan[timerId].TimxLoadCount = loadValue2;
}


/**
* timer_reset_cnt
*
* @param[in] timerId: TIMER ID(0~2)
* @return 0:Success
*
* @brief reset timer cnt.
*/
int32_t timer_reset_cnt(uint8_t timerId)
{
    NVIC_DisableIRQ(TIM0_IRQn + timerId);
    TIMER->TimeChan[timerId].TimxControl &= ~TIMER_CONTROL_ENABLE_MSK;
    TIMER->TimeChan[timerId].TimxControl |= TIMER_CONTROL_ENABLE_MSK;
    NVIC_EnableIRQ(TIM0_IRQn + timerId);

    return 0;
}


/**
* timer_get_int_status
*
* @param[in] timerId: TIMER ID(0~2)
*
* @return flag: Timer channel interrupt Status
*
* @brief   Get timer channel interrupt status
*/
uint32_t timer_get_int_status(uint8_t timerId)
{
    uint32_t flag;

    flag = TIMER->TimeChan[timerId].TimxIntStatus;
    return flag;
}


/**
* timers_get_int_status
*
* @param[in] 
*
* @return flag: Timers channel interrupt Status
*
* @brief   Get timers channel interrupt status
*/
uint32_t timers_get_int_status(void)
{
    uint32_t flag;

    flag = TIMER->TimersIntStatus;
    return flag;
}

/**
* timer_get_int_flag
*
* @param[in] timerId: TIMER ID(0~2)
*
* @return flag: Timer channel interrupt Flag
*
* @brief   Get timer channel interrupt flag
*/
uint32_t timer_get_int_flag(uint8_t timerId)
{
    uint32_t flag;

    flag = TIMER->TimeChan[timerId].TimxIntStatus;
    return flag;
}

/**
* timer_get_curval
*
* @param[in] timerId: TIMER ID(0~2)
*
* @return flag: Timer channel Current Value
*
* @brief   Get timer channel Current Value
*/
uint32_t timer_get_curval(uint8_t timerId)
{
    uint32_t curVal;

    curVal = TIMER->TimeChan[timerId].TimxCurrentValue;
    return curVal;
}
/**
* timer_clr_int_flag
*
* @param[in] timerId: TIMER ID(0~2)
*
* @return none
*
* @brief clear timer channel interrrupt flag
*/
void timer_clr_int_flag(uint8_t timerId)
{
    TIMER->TimeChan[timerId].TimxEOI;

}

/**
* timer_set_callback
*
* @param[in]  timerId: TIMER ID(0~2)
* @param[in]  timeCallback: timer callback
* @return none
*
* @brief TIMER module set call back
*/
void timer_set_callback(uint8_t timerId, TIMER_CallbackType timeCallback)
{
    if (timerId<TIMER_NUM)
    {
        s_timerCallback[timerId]  = timeCallback;
    }
}


/**
* timer_deinit
*
* @param[in]timerId: TIMER ID(0~2)
*
* @return 0:Success
*
* @brief TIMER module de-initialize, reset TIMER register
*/
int32_t timer_deinit(uint8_t timerId)
{
    uint8_t i = 0;
    IRQn_Type timeIrq = TIM0_IRQn+timerId;


    NVIC_DisableIRQ(timeIrq);
    timer_set_loadval(timerId, 0);
    timer_set_loadval2(timerId, 0);
    timer_disable(timerId);
    timer_disable_int(timerId);
    timer_disable_usermode(timerId);
    timer_disable_pwm(timerId);
    timer_clr_int_flag(timerId);
    return 0;
}

/**
* TIMER0_IRQHandler
*
* @param[in] none
*
* @return none
*
* @brief TIMER0 interrupt service routine
*/
void TIMER0_IRQHandler(void)
{
    if (s_timerCallback[0])
    {
        timer_clr_int_flag(0);
        s_timerCallback[0](0);
    }
}

/**
* TIMER1_IRQHandler
*
* @param[in] none
*
* @return none
*
* @brief TIMER1 interrupt service routine
*/
void TIMER1_IRQHandler(void)
{
    if (s_timerCallback[1])
    {
        timer_clr_int_flag(1);
        s_timerCallback[1](1);
    }
}
/**
* TIMER2_IRQHandler
*
* @param[in] none
*
* @return none
*
* @brief TIMER2 interrupt service routine
*/
void TIMER2_IRQHandler(void)
{
    if (s_timerCallback[2])
    {
        timer_clr_int_flag(2);
        s_timerCallback[2](2);
    }
}
