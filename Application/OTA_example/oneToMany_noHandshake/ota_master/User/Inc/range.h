/*****************************************************************************
* File: range.h
*
* Descirption: this file contains the functions support range.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#ifndef _RANGE_H_
#define _RANGE_H_

#include "hal_uwb.h"
#include "hal_gp_timer.h"

#define LOGIC_DEBUG

#define _INITIATOR    0
#define _RESPONDER    1

//#define RANGE_ROLE      _INITIATOR
#define RANGE_ROLE      _RESPONDER

#define LED_PIN         GPIO_PIN3

#define VENDOR_LEN      3
#define POLL_MSG_LEN    8
#define RESP_MSG_LEN    7
#define FINAL_MSG_LEN   22

#define POLL_TS_IDX     7
#define RESP_TS_IDX     12
#define FINAL_TS_IDX    17

#define DST_ADDR_IDX    3
#define SRC_ADDR_IDX    5
#define ADDR_LEN        2

#define POLL_MSG_IDX    7

#define MAX_BUFFER_SIZE 30


#define MSG_GAP         2000       //gap between msg, uint us 两个消息间的间隔时间
#define RX_OFFSET       100
#define RX_TIMEOUT      1000     //unit us

#define RANGE_INTERVAL  100    //发送周期 ms  100ms: range frequency 10hz  max frequency is 100hz

#define ANT_DELAY       13147	//天线标定，影响测距 从发送到天线真正发送出的时间

#if(RANGE_ROLE == _INITIATOR)
#define LOCAL_ADDR      0x0001
#define REMOTE_ADDR     0xa001
#else
#define LOCAL_ADDR      0xa001
#define REMOTE_ADDR     0x0001
#endif

typedef enum
{
    INITIAL_STATE = 0,
    POLL_STATE,
    RESP_STATE,
    FINAL_STATE,
    FINISH_STATE
}range_state_e;

extern uint8_t g_poll_msg[POLL_MSG_LEN];
extern uint8_t g_resp_msg[RESP_MSG_LEN];
extern uint8_t g_final_msg[FINAL_MSG_LEN];
extern uint8_t g_recv_buf[MAX_BUFFER_SIZE];

extern hal_uwb_instance_t uwb_instance;
extern hal_gp_timer_t gp_timer;




void final_msg_get_ts(const uint8_t *ts_field, uint64_t *ts);
void final_msg_set_ts(uint8_t *ts_field, uint64_t ts);
void user_init(void);
void range_init(void);
void range_loop(void);
#endif
