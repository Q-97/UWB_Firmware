#ifndef _MSG_UCI_H_
#define _MSG_UCI_H_

#include <stdint.h>
#include "uci.h"

//int32_t uwbs_send_ntf_to_host(uint8_t *buf, uint8_t len);
int32_t host_get_ntf_from_uwbs(uint8_t *buf);
int32_t uci_msg_send(uci_msg_t *uci_msg);
int32_t uci_msg_get(uint8_t *buf, uint8_t msg_type);
uint8_t uwbs_have_cmd_msg(void);
uint8_t host_have_rsp_msg(void);
uint8_t host_have_ntf_msg(void);
void clear_msg_buf_flag(void);

#endif
