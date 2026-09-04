/*****************************************************************************
* File: user_app.h
*
* Descirption: this file contains the functions support range.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#ifndef _USER_APP_H_
#define _USER_APP_H_
#include "hal_radar.h"

#define MAX
void user_app_proc();
void user_radar_call_back(int32_t *buffer_i,int32_t *buffer_q,uint8_t ant_id);
void user_loop(void);
#endif