/*****************************************************************************
* File: hal_i2c.h
*
* Descirption: this file contains the i2c hal functions.
*
* Copyright (C) : 2025 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2025 - 5
*****************************************************************************/
#ifndef _HAL_I2C_H
#define _HAL_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "zn_i2c.h"

#define I2C_BASE(x)    ((0 == (x)) ? I2C0 : I2C1)
#define I2C_ID(x)      ((I2C0 == (x)) ? 0 : 1)

#define SPEED_STANDARD    100000
#define SPEED_FAST        400000
#define SPEED_FAST_PLUS   1000000
#define SPEED_MAX         3400000  

#define EVENT_MST_ON_HOLD   IC_MST_ON_HOLD
#define EVENT_GEN_CALL      IC_GEN_CALL
#define EVENT_START_DET     IC_START_DET
#define EVENT_STOP_DET      IC_STOP_DET
#define EVENT_ACTIVITY      IC_ACTIVITY
#define EVENT_RX_DONE       IC_RX_DONE
#define EVENT_TX_ABRT       IC_TX_ABRT
#define EVENT_RD_REQ        IC_RD_REQ
#define EVENT_TX_EMPTY      IC_TX_EMPTY
#define EVENT_TX_OVER       IC_TX_OVER
#define EVENT_RX_FULL       IC_RX_FULL
#define EVENT_RX_OVER       IC_RX_OVER
#define EVENT_RX_UNDER      IC_RX_UNDER

typedef struct hal_i2c
{
    uint8_t i2c_id;                   //i2c id, 0-1
    uint8_t i2c_group_sel;            //only used for i2c1, 0: use GPIOA5 GPIOA6 as SCL SDA, 1: use GPIOA9 GPIOA10 as SCL SDA
    uint8_t i2c_role;                 //0 slave  1 master
    uint8_t tx_fifo_trigger_level;    //range 0-63 corresponding is from 1 entry to 64 entries
    uint8_t rx_fifo_trigger_level;    //range 0-63 corresponding is from 1 entry to 64 entries
    uint8_t interrupt_en;             //0 disable  1 enable
    uint32_t interrupt_mask;          //interrupt mask, only used when interrupt en set 1
    uint32_t slaver_addr;             //i2c slaver address
    I2C_SPEED i2c_speed;              //i2c speed
    DeviceCallback_Type func;         //i2c interrupt callback
}hal_i2c_t;


typedef struct hal_i2c_info
{
    uint8_t i2c_id;
    uint8_t *buffer;
    uint8_t offset_size;
    uint32_t len;
    uint32_t offset;
    uint32_t dev_addr;
}hal_i2c_info_t;




ERROR_Type hal_i2c_init(hal_i2c_t *i2c_config);
ERROR_Type hal_i2c_write_poll(hal_i2c_info_t* i2c_info);
ERROR_Type hal_i2c_read_poll(hal_i2c_info_t* i2c_info);
void hal_i2c_write_byte(uint8_t i2c_id, uint8_t data);
uint8_t hal_i2c_read_byte(uint8_t i2c_id);
uint32_t hal_i2c_get_interrupt_state(uint8_t i2c_id);
void hal_i2c_clear_interrrupt_state(uint8_t i2c_id, uint32_t event);
#ifdef __cplusplus
}
#endif

#endif
