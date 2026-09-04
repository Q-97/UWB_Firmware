/*****************************************************************************
* File: gconfig.h
*
* Descirption: this file contains the functions support range.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#ifndef _GCONFIG_H_
#define _GCONFIG_H_

#include "hal_uwb.h"
#include "hal_gp_timer.h"

//#define LOGIC_DEBUG

#define LED_PIN         GPIO_PIN3

#define ANT_DELAY       13147

#define LOW_POWE_EN

#define DEFAULT_CAN_ID  0xAA

#define RECIEVE_UCI_TEST_MODE_CAN_ID  0x781

#define SEND_UCI_TEST_MODE_CAN_ID  0x782

#define RECV_UPFRADE_CAN_ID        0X151   

typedef unsigned char    bool;

typedef enum work_mode
{
    WORK_MODE_RADAR = 0,    //default radar mode
    WORK_MODE_TEST,         //test mode
    WORK_MODE_PHYDEBUG,     //phy_debug
    WORK_MODE_NULL
}work_mode_t;
extern uint8_t g_work_mode;

typedef enum uci_mode       //uci interface
{
    UCI_UART = 0,
    UCI_CAN,
    UCI_SPI,
    UCI_NULL,
}uci_mode_t;
extern uci_mode_t  g_uci_mode;

typedef enum vga_ctrl_mode
{
    VGA_ONCE_POWERON = 0,
    VGA_ONCE_ERASE_FLASH
}vga_ctrl_mode_t;
extern uint8_t g_vga_ctrl;


extern hal_uwb_instance_t uwb_instance;
extern hal_uwb_instance_t test_mode_uwb_inst;


#define PIN_NUM_MAX 37
typedef struct
{
    uint8_t piunum;     /*gpio num*/
    uint8_t istest;     /*0-not test;1-test*/
    uint32_t padreg;
} GPIO_TestType;
extern GPIO_TestType g_gpioTestTab[PIN_NUM_MAX];

#endif
