/*****************************************************************************
 *  File: aon.h
 *
 *  Descirption: aon_reg register interface.
 *
 *  Copyright (C) : 2025 ultraception.com
 *
 *  Author: WangJiying
 *  Mail:   
 *  Date:   2025-5-24
 *
 *****************************************************************************/

#ifndef __AON_REG_H__
#define __AON_REG_H__

#define     AON_WCFG                    (0x100)              
#define     AON_CFG                     (0x101)
#define     AON_SLEEP_CNT_BYTE0         (0x102)      /* little*/         
#define     AON_SLEEP_CNT_BYTE1         (0x103)              
#define     AON_SLEEP_CNT_BYTE2         (0x104)              
#define     AON_SLEEP_CNT_BYTE3         (0x105)              
#define     AON_ANALOG_CTRL             (0x106)    
#define     AON_WKUP_STATUS             (0x108)    
#define     AON_WKUP_CFG                (0x110)
#define     AON_RESETN_CFG              (0x111)
#define     AON_SPI0_CSN_CFG            (0x112)
#define     AON_SPI1_CSN_CFG            (0x113)
#define     AON_BOOT0_CFG               (0x114)
#define     AON_BOOT1_CFG               (0x115)
#define     AON_CAN_RXD_CFG             (0x116)
#define     AON_MEM_LDO_CONFIG          (0x117)
#define     AON_SRAM_CODE_PD            (0x118)
#define     AON_BOOT_RETENTION          (0x119)
#define     AON_DUMMY                   (0x120)
#define     AON_ANA_CFG                 (0x121)
#define     AON_XO_CFG                  (0x122)
#define     AON_SLP_LOAD_READ_CNT0      (0x123)
#define     AON_SLP_LOAD_READ_CNT1      (0x124)  
#define     AON_SLP_LOAD_READ_CNT2      (0x125)
#define     AON_SLP_LOAD_READ_CNT3      (0x126)
#define     AON_SLP_CNT_CONTRL          (0x127)
#define     AON_CAPTURE_CONTROL         (0x128)
#define     AON_D_BUCK_CONTROL3         (0x132)
#define     AON_D_BUCK_CONTROL4         (0x133)
#define     AON_TRIM_OVRD               (0x134)
#define     WAKEUP_CONFIG               (0x136)
#define     LATCH_CONFIG                (0x137)

#endif