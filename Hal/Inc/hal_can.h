/*****************************************************************************
* File: hal_can.h
*
* Descirption: this file contains the i2c hal functions.
*
* Copyright (C) : 2025 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2025 - 5
*****************************************************************************/
#ifndef _HAL_CAN_H
#define _HAL_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "zn_can.h"

#define MAX_CAN_BUFFER_LEN    16
#define MAX_CAN_FILTER_NUM    CAN_MAX_FILTER_NUM

#define PRIMARY_SEND    0
#define SECONDARY_SEND  1

#define INITIALIZATION_MODE    0
#define NORMAL_MODE            1
#define RESTRICTED_MODE        2
#define MONITOR_MODE           3
#define LOOPBACK_INTERNAL_MODE 4
#define LOOPBACK_EXTERNAL_MODE 5

#define BUFF_EMPTY                          0x00
#define BUFF_BETWEEN_EMPTY_AND_ALMOST_FULL  0x01
#define BUFF_ALMOST_FULL                    0x10
#define BUFF_FULL                           0x11

/* =======================================================  TBUF/RBUF  ======================================================= */
#define MSG_INFO_ID_POS        CAN_INFO_ID_POS
#define MSG_INFO_ID_MASK       CAN_INFO_ID_MASK
#define MSG_INFO_TTSEN_POS     CAN_INFO_TTSEN_POS
#define MSG_INFO_TTSEN_MASK    CAN_INFO_TTSEN_MASK
#define MSG_INFO_DLC_POS       CAN_INFO_DLC_POS
#define MSG_INFO_DLC_MASK      CAN_INFO_DLC_MASK
#define MSG_INFO_BRS_POS       CAN_INFO_BRS_POS
#define MSG_INFO_BRS_MASK      CAN_INFO_BRS_MASK
#define MSG_INFO_FDF_POS       CAN_INFO_FDF_POS
#define MSG_INFO_FDF_MASK      CAN_INFO_FDF_MASK
#define MSG_INFO_RTR_POS       CAN_INFO_RTR_POS
#define MSG_INFO_RTR_MASK      CAN_INFO_RTR_MASK
#define MSG_INFO_IDE_POS       CAN_INFO_IDE_POS
#define MSG_INFO_IDE_MASK      CAN_INFO_IDE_MASK   

/* rate = CAN_CLOCK / (S_PRESC + 1) / ((S_SEG_1 + 2) + (S_SEG_2 + 1))     */
/* sample point = (S_SEG_1 + 2) / ((S_SEG_1 + 2) + (S_SEG_2 + 1))     */
typedef struct
{
    uint8_t presc;    //prescaler
    uint8_t seg_1;    //bit timing segment 1
    uint8_t seg_2;    //bit timing segment 2
    uint8_t sjw;      //synchronization jump width: sjw = seg_2 / 2 ~ seg_2 * 2 / 3
}baudrate_config_t;

typedef struct
{
    uint8_t index;    //filter index
    uint8_t enable;   //0: disable, 1: enable
    uint32_t code;    //code data
    uint32_t mask;    /*< Mask data . The register corresponding to mask ,bit0-bit30,  
                       bit 30:Acceptance mask IDE bit check enable
                        1 -  acceptance filter accepts either standard or extended as defined by AIDE
                        0 -  acceptance filter accepts both standard or extended frames
                        Only filter 0 is affected by the power-on reset. All other filters stay uninitialized.
                       bit 29 Acceptance mask IDE bit value
                        If AIDEE=1 then:
                        1 -  acceptance filter accepts only extended frames
                        0 -  acceptance filter accepts only standard frames
                        Only filter 0 is affected by the power-on reset. All other filters stay uninitialized.
                       other bit
                       1 -  acceptance check for these bits of receive identifier disabled
                       0 -  acceptance check for these bits of receive identifier enable
                    */
}filter_control_t;

typedef struct
{
    uint32_t can_mode     : 3;    //can mode 
    uint32_t clock_src    : 1;    //can clock source 0: pllclock, 1 xo clock
    uint32_t clock_div    : 4;    //can clock frequency div 0: no div, 1-15: 2-16 div
    uint32_t interrupt_en : 1;    //interrupt enable 0:disable, 1:enable
    uint32_t auto_reset   : 1;    //0:no reset,1:auto reset after bus off ot active
    uint32_t tpss         : 1;    //transmission primary single shot mode for ptb
    uint32_t tsss         : 1;    //transmission secondary single shot mode for stp
    uint32_t ts_mode      : 1;    //transmit buffer secondary operation mode
    uint32_t rom          : 1;    //receive buffer overflow mode
    uint32_t time_en      : 1;    //time stamp enable 0:disable, 1: enable
    uint32_t time_pos     : 1;    //time-stamping position 0: sof, 1:sof
    uint32_t fd_mode_en   : 1;    //fd mode enable 0:disable, 1:enable
    uint32_t fd_iso_en    : 1;    //fd iso mode enable 0:disable, 1: enable
    uint32_t tdc_en       : 1;    //tdc enbable(when data bitrate >= 1Mbps) 0:disable, 1:enable
    uint32_t ssp_offset   : 7;    //ssp offset
    uint32_t filter_en    : 1;    //filter function enable 0:disable, 1: enable
    uint32_t rsv          : 5;
    uint8_t filter_num;
    filter_control_t *filter_list;    //filter controller list
    DeviceCallback_Type func;         //can event callback function
}can_config_t;

typedef struct hal_can_msg_info
{
    uint32_t can_id;                      //can identifer
    uint8_t  esi;                         //transmit timestamp en or error state indicator
    uint8_t  dlc;                         //data length code
    uint8_t  brs;                         //bit rate switch
    uint8_t  fdf;                         //fd format indicator
    uint8_t  rtr;                         //remote transmission request
    uint8_t  ide;                         //identifier externsion
    uint32_t data[MAX_CAN_BUFFER_LEN];    //data
    uint32_t rts[2];                      //receive time stamps
}hal_can_msg_info_t;

typedef struct hal_can
{
    can_config_t      config;
    baudrate_config_t baudrate_config;
    baudrate_config_t datarate_config;
}hal_can_t;


ERROR_Type hal_can_init(hal_can_t *can_config);
void hal_can_deinit(void);
ERROR_Type hal_can_msg_send(hal_can_msg_info_t* msg_info, uint8_t type);
ERROR_Type hal_can_msg_read(hal_can_msg_info_t *msg_info);
uint8_t hal_can_wait_transmission_idle(uint8_t type);
uint8_t hal_can_get_payload_size(uint8_t dlc);
uint8_t hal_can_is_transmit_busy(uint8_t type);
uint8_t hal_can_is_transmit_idle(uint8_t type);
uint8_t hal_can_fd_dlc_to_len(uint8_t dlc);
uint8_t hal_can_fd_len_to_dlc(uint8_t len);
void hal_can_reset(uint8_t reset);
uint8_t hal_can_is_msg_in_rxbuff(void);
void hal_can_set_int_enalbe(uint8_t int_en, uint8_t err_int_en);
void hal_can_set_ewl(uint8_t ewl);
uint32_t hal_can_get_tts0(void);
uint32_t hal_can_get_tts1(void);

#ifdef __cplusplus
}
#endif

#endif
