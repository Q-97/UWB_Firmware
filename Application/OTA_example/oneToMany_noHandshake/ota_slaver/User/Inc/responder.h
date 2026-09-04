/*****************************************************************************
* File: responder.h
*
* Descirption: this file contains the functions support responder.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#ifndef _RESPONDER_H_
#define _RESPONDER_H_

#define POLL_RX_TIMEOUT    (2 * RANGE_INTERVAL * 1000 + 100) 

void responder_init(void);
void responder_loop(void);
#endif
