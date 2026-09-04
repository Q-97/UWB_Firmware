/*****************************************************************************
 *  File: zn_log.c
 *
 * Descirption: This file contains the functions support log operations.
 *
 *  Copyright (C) : 2022 ultraception.com
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2023-4-17
 *
 *****************************************************************************/

#include "zn_log.h"

volatile int32_t g_log_level = LOG_LEVEL_INFO;

void set_log_level(log_level_t level)
{
    g_log_level = level;
}