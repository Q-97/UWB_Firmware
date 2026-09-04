/*****************************************************************************
 *  File: hal_delay.c
 *
 * Descirption: this file contains the functions support delay operations.
 *
 *  Copyright (C) : 2025 ultraception.com
 *
 *  Author: sxg
 *  Mail:   
 *  Date:   2025-5-12
 *
 *****************************************************************************/
 
 #include "hal_delay.h"
 
 void hal_delay_us(uint32_t time_us)
 {
     udelay(time_us);
 }
 
 void hal_delay_ms(uint32_t time_ms)
 {
     mdelay(time_ms);
 }