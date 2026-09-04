
/******************************************************************************
 *  File: zn_timer.h
 *
 *  Description: this file contains the functions support timer operations.
 *
 *  Copyright (C) : 2022 Hangzhou ultraception.com.
 *
 *  Author: wjy
 *  Date:   April 17 2023
 *
 *****************************************************************************/

#ifndef __ZN_TIMER_H__
#define __ZN_TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_soc.h"
#include "zn_timer_reg.h"

#define TIMER0 (0)
#define TIMER1 (1)
#define TIMER2 (2)
#define USEC_TO_COUNT(x, y)        ((x) * (uint64_t)(y) / 1000000UL)


typedef void (*TIMER_CallbackType)(uint8_t arg);             ///< TIMER callback type
static TIMER_CallbackType s_timerCallback[TIMER_NUM] = {(TIMER_CallbackType)NULL};

typedef struct
{
    uint8_t timerId;        /* timert ID, is 0,1,2*/
    uint8_t timerEn;        /* 0:disable;1:enable */
    uint8_t timerMode;      /* 0:free-running mode (Timer loads the maximum value,);1:user-defined count mode*/
    uint8_t interruptEn;    /* 0:disable timer interrupt ;1:enable  timer interrupt*/
    uint8_t pwmEn;          /* Pulse Width Modulation of timer_N_toggle output;0:disabled,1:enabled*/
    uint32_t loadCnt;       /* 32-bit channel load value*/
    uint32_t loadCnt2;      /* 32-bit channel load value*/
} TIMER_ConfigType;

int32_t timer_init(TIMER_ConfigType *timConfig);
void timer_set_loadval(uint8_t timerId, uint32_t loadValue);
void timer_set_loadval2(uint8_t timerId, uint32_t loadValue2);
int32_t timer_reset_cnt(uint8_t timerId);
uint32_t timer_get_int_flag(uint8_t timerId);
uint32_t timer_get_curval(uint8_t timerId);
void timer_clr_int_flag(uint8_t timerId);
uint32_t timer_get_int_status(uint8_t timerId);
uint32_t timers_get_int_status(void);
void timer_set_callback(uint8_t timerId, TIMER_CallbackType timeCallback);
int32_t timer_deinit(uint8_t timerId);
void TIMER0_IRQHandler(void);
void TIMER1_IRQHandler(void);
void TIMER2_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif
