#ifndef _TUWB_H_
#define _TUWB_H_

#include "stdint.h"

#include "uci.h"
#include "msg_uci.h"
#include "gconfig.h"


typedef struct freq_offset
{
    uint8_t swc_value:6;
    uint8_t rev1:2;
    uint8_t swf_value:6;
    uint8_t rev2:2;
}freq_offset_t;



device_inst_t *uci_get_dev_inst(void);
void uwbs_change_device_state(state_device_t new_cur_state);
int32_t uwbs_log_ntf_handler(uint8_t is_rx, uint32_t status);
int32_t uwbs_test_stop_ntf_handler(void);

void uwbs_init(void);

void uwbs_loop(void);


#endif //_TUWB_H_
