/*****************************************************************************
* File: zntest.h
*
* Descirption: this file contains the functions support phy test.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#ifndef _PHY_TEST_H
#define _PHY_TEST_H

#include <stdint.h>

#define USER_MSG_LOG_LEVEL_OFF   0x00
#define USER_MSG_LOG_LEVEL_NEC   0x01
#define USER_MSG_LOG_LEVEL_ERROR 0x02
#define USER_MSG_LOG_LEVEL_WARN  0x03
#define USER_MSG_LOG_LEVEL_INFO  0x04
#define USER_MSG_LOG_LEVEL_DEBUG 0x05
#define USER_MSG_LOG_LEVEL_ALL   0x06


void phy_test_debug_switch(uint8_t *msg_payload, uint8_t msg_len);
void phy_test_register_operation(uint8_t *msg_payload, uint8_t msg_len);
void phy_test_transfer_operation(uint8_t *msg_payload, uint8_t msg_len);
void phy_test_user_defined_operation(uint8_t *msg_payload, uint8_t msg_len);
void phy_test_aon_register_operation(uint8_t *msg_payload, uint8_t msg_len);
void phy_test_full_register_operation(uint8_t *msg_payload, uint8_t msg_len);
void phy_test_loop(void);
#endif
